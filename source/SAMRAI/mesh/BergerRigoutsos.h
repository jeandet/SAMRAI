/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright 
 * information, see COPYRIGHT and COPYING.LESSER. 
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   Asynchronous Berger-Rigoutsos clustering algorithm. 
 *
 ************************************************************************/
#ifndef included_mesh_BergerRigoutsos
#define included_mesh_BergerRigoutsos

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/mesh/BoxGeneratorStrategy.h"
#include "SAMRAI/hier/Connector.h"
#include "SAMRAI/hier/MappedBoxLevel.h"
#include "SAMRAI/hier/PatchLevel.h"
#include "SAMRAI/tbox/Database.h"
#include "SAMRAI/tbox/Pointer.h"
#include "SAMRAI/tbox/Utilities.h"

namespace SAMRAI {
namespace mesh {

/*!
 * @brief Asynchronous Berger-Rigoutsos implementation.
 * This class is derived from the abstract base class
 * mesh::BoxGeneratorStrategy.  Thus, it serves as a concrete
 * implementation of the box generator Strategy pattern interface.
 *
 * This class uses the BergerRigoutsosNode class
 * to carry out the asynchronous Berger-Rigoutsos algorithm.
 * It handles aspects not central to that algorithm.  It:
 * - Implements the box generator Strategy pattern interface.
 * - Provides an interface with the input database for setting
 *   parameters influencing the implementation.
 * - Sorts the output data (if user requests).
 * - Performs some additional error checking.
 * For more details on the parallel implementation,
 * see mesh::BergerRigoutsosNode.
 *
 * User inputs (default):
 * - string @b algo_advance_mode ("ADVANCE_SOME"):
 *   Asynchronous algorithm advance mode.  The default has been
 *   empirically determined to scale best to higher numbers of
 *   processors and work adequately for lower numbers of processors.
 * - std::string @b owner_mode ("MOST_OVERLAP"):
 *   How to chose the owner from a dendogram node group.
 *   This std::string is used in BergerRigoutsosNode::setOwnerMode().
 * - bool @b sort_output_nodes (false):
 *   Whether to sort the output.  This makes the normally
 *   non-deterministic ordering deterministic and the results repeatable.
 * - bool @b max_box_size:
 *   The maximum cluster dimension allowed.  This parameter is not
 *   critical to clustering but limiting the cluster size may improve
 *   performance of load balancing algorithms (due to the excessive work
 *   required by the owner of huge clusters).
 * - bool @b check_min_box_size:
 *   A flag to control how to resolve an initial box that violates the
 *   minimum box size.  Set to one of these strings:
 *   @b "IGNORE" - violations will be quietly disregarded.
 *   @b "WARN" - violations will cause a warning but the
 *   code will continue anyway.
 *   @b "ERROR" - violations will cause an unrecoverable assertion.
 *   The default is "WARN".
 * - double @b max_lap_cut_from_center (1.0): Limit the Laplace cut to this
 *   fraction of the distance from the center plane to the end.
 *   Zero means cut only at the center plane.  One means unlimited.
 *   Under most situations, one is fine.  A lower setting helps prevent
 *   parallel slivers.
 *
 * Debugging inputs (default):
 * - bool @b log_node_history (false):
 *   Whether to log what certain actions of nodes in the dendogram.
 *   This degrades the performance but is a very useful debugging
 *   tool.
 * - bool @b log_cluster_summary (false):
 *   Whether to briefly log the results of the clustering.
 * - bool @b log_cluster (false):
 *   Whether to log the results of the clustering.
 */
class BergerRigoutsos:public mesh::BoxGeneratorStrategy
{

public:
   /*!
    * @brief Constructor.
    */
   BergerRigoutsos(
      const tbox::Dimension& dim,
      tbox::Pointer<tbox::Database> database =
         tbox::Pointer<tbox::Database>(NULL));

   /*!
    * @brief Destructor.
    *
    * Deallocate internal data.
    */
   ~BergerRigoutsos(
      void);

   /*!
    * @brief Set the MPI communication object.
    *
    * Duplicate the communicator in the given for private use.  A private
    * communicator isolates the complex communications used by the
    * asynchronous algorithm from other communications.  Duplicating
    * the communicator is expensive but should only be need once.  All
    * processes in the communicator must participate.  The duplicate
    * communicator is active until this object is destructed.
    * Using a duplicated MPI communicator is optional but recommended.
    * When a duplicate MPI communicator is in use, it must be congruent
    * with the communicator associated with the tag level.
    *
    * If the communicator is not set, the parallel clustering
    * algorithm uses the communicator of the input tag
    * mapped_box_level.  If it is set, then the algorithm only works
    * for input tag mapped_box_levels with a congruent communicator.
    *
    * If communicator is SAMRAI_MPI::commNull, it is the same as not
    * using a duplicate communicator.
    */
   void
   setMPI(
      const tbox::SAMRAI_MPI& mpi);

   /*!
    * @brief Implement the mesh::BoxGeneratorStrategy interface
    * method of the same name.
    */
   void
   findBoxesContainingTags(
      hier::MappedBoxLevel& new_mapped_box_level,
      hier::Connector& tag_to_new,
      hier::Connector& new_to_tag,
      const tbox::Pointer<hier::PatchLevel> tag_level,
      const int tag_data_index,
      const int tag_val,
      const hier::Box& bound_box,
      const hier::IntVector& min_box,
      const double efficiency_tol,
      const double combine_tol,
      const hier::IntVector& max_gcw,
      const hier::BlockId& block_id) const;

private:
   const tbox::Dimension d_dim;

   void
   assertNoMessageForPrivateCommunicator() const;

   void
   sortOutputMappedBoxes(
      hier::MappedBoxLevel& new_mapped_box_level,
      hier::Connector& tag_to_new,
      hier::Connector& new_to_tag) const;

   /*!
    * @brief Set up things for the entire class.
    *
    * Only called by StartupShutdownManager.
    */
   static void
   initializeCallback();

   /*!
    * @brief Free static timers.
    *
    * Only called by StartupShutdownManager.
    */
   static void
   finalizeCallback();

   //! @brief Communication object.
   tbox::SAMRAI_MPI d_mpi;

   //! @brief Max box size constraint used by BergerRigoutsosNode.
   hier::IntVector d_max_box_size;

   //! @brief Max distance from center for Laplace cut.
   double d_max_lap_cut_from_center;

   //! @brief Whether to log execution node allocation and deallocation.
   bool d_log_node_history;

   //! @brief Whether to briefly log cluster summary.
   bool d_log_cluster_summary;

   //! @brief Whether to log cluster summary.
   bool d_log_cluster;

   //! @brief How to select the owner of a node.
   std::string d_owner_mode;

   //! @brief Asynchronous mode for advancing algorithm.
   std::string d_algo_advance_mode;

   //! @brief Whether to sort results to make them deterministic.
   bool d_sort_output_nodes;

   //! @brief How to resolve initial boxes smaller than min box size.
   char d_check_min_box_size;

   //@{
   //! @name Used for evaluating performance;
   bool d_barrier_before;
   bool d_barrier_after;
   //@}

   static tbox::Pointer<tbox::Timer> t_barrier_before;
   static tbox::Pointer<tbox::Timer> t_barrier_after;
   static tbox::Pointer<tbox::Timer> t_find_boxes_with_tags;
   static tbox::Pointer<tbox::Timer> t_run_abr;
   static tbox::Pointer<tbox::Timer> t_global_reductions;
   static tbox::Pointer<tbox::Timer> t_sort_output_nodes;

   static tbox::StartupShutdownManager::Handler
   s_initialize_finalize_handler;

};

}
}

#endif  // included_mesh_BergerRigoutsos