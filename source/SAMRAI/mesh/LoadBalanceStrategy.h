/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright 
 * information, see COPYRIGHT and COPYING.LESSER. 
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   Strategy interface for box load balancing routines. 
 *
 ************************************************************************/

#ifndef included_mesh_LoadBalanceStrategy
#define included_mesh_LoadBalanceStrategy

#include "SAMRAI/SAMRAI_config.h"
#include "SAMRAI/hier/BoxList.h"
#include "SAMRAI/hier/IntVector.h"
#include "SAMRAI/hier/PatchHierarchy.h"
#include "SAMRAI/hier/ProcessorMapping.h"
#include "SAMRAI/tbox/Array.h"
#include "SAMRAI/tbox/Pointer.h"
#include "SAMRAI/tbox/RankGroup.h"

namespace SAMRAI {
namespace mesh {

/*!
 * @brief Class LoadBalanceStrategy is an abstract base class that
 * defines a Strategy pattern interface for operations that load
 * balance patches on a single AMR patch hierarchy level.  Typically,
 * such operations are invoked after the domain of a new hierarchy
 * level is determined (e.g., via some error estimation procedure) and
 * is applied to the collection of boxes that describe the domain.  The
 * load balancing process produces a set of boxes from which patches on
 * the new level are created and a processor mapping describing how the
 * new patches are mapped to processors.
 *
 * @see hier::PatchLevel
 * @see hier::ProcessorMapping
 */

class LoadBalanceStrategy:public tbox::DescribedClass
{
public:
   /*!
    * Construct load balance strategy object.
    */
   LoadBalanceStrategy();

   /*!
    * This virtual destructor does nothing interesting.
    */
   virtual ~LoadBalanceStrategy();

   /*!
    * Indicate whether load balancing procedure for given level depends on
    * patch data on mesh.  This can be used to determine whether a level
    * needs to be rebalanced although its box configuration is unchanged.
    *
    * @return Boolean value of true if load balance routines for level
    *        depend on patch data; false otherwise.
    *
    * @param level_number Integer level number.
    */
   virtual bool
   getLoadBalanceDependsOnPatchData(
      int level_number) const = 0;

   /*!
    * @brief Given a MappedBoxLevel, representing the domain of a specified
    * level in the AMR hierarchy, generate a new MappedBoxLevel from which the
    * patches for the level may be formed and update two Connectors
    * incident on the changed MappedBoxLevel.
    *
    * The union of the boxes in the balance_mapped_box_level is the same
    * before and after the the method call.
    *
    * @param[in,out] balance_mapped_box_level Input MappedBoxLevel.  On input, this is the pre-balance
    *  MappedBoxLevel.  On output, it is the balanced MappedBoxLevel.
    *
    * @param[in,out] balance_to_anchor Connector between the balance_mapped_box_level and
    *  some given "anchor mapped_box_level".
    *  This must be accurate on input.  On putput, connects the newly
    *  balanced balance_mapped_box_level to the anchor mapped_box_level.
    *
    * @param[in,out] anchor_to_balance Transpose of balance_to_anchor.
    *
    * @param[in] hierarchy The hierarchy where the work distribution
    * data lives.
    *
    * @param[in] level_number The number of the level where the work
    * distribution data lives.
    *
    * @param[in] unbalanced_to_attractor Connector between the
    * balance_mapped_box_level and an "attractor" MappedBoxLevel.
    * This data may be used to indicate preference for data locality.
    * The implementation should try to maximize overlaps between
    * attractor and balance cells owned by the same process.
    *
    * @param[in] attractor_to_unbalanced Transpose of unbalanced_to_attractor.
    *
    * @param[in] min_size hier::IntVector representing mimimum box size.
    *
    * @param[in] max_size hier::IntVector representing maximum box size.
    *
    * @param[in] domain_mapped_box_level Description of the domain.
    *
    * @param[in] bad_interval
    *  hier::IntVector indicating the length of an interval
    *  of cells along each side of the box where chopping
    *  the box may produce boxes with certain "bad" properties.
    *  For example, this is primiarily used to avoid generating
    *  ghost regions for patches that intersect the domain
    *  boundary in ways that may it difficult for a use to
    *  provide boundary values.  Thus, it is typically related
    *  to the maximum ghost cell width in the problem.  See
    *  hier::BoxUtilities header file for more information.
    *
    * @param[in] cut_factor
    *  hier::IntVector indicating factor for chopping
    *  each side of a box; i.e., after chopping a box,
    *  the number of cells along each direction of each
    *  piece must be an integer multiple of the corresponding
    *  entry in the cut factor vector.  For example, the
    *  cut factor may be related to the coarsen ratio between
    *  levels in the hierarchy in which case it may be used
    *  to produce boxes that can be coarsened by a certain
    *  factor if needed.  See hier::BoxUtilities header file
    *  for more information.
    *
    * @param[in] rank_group
    *  Input tbox::RankGroup indicating a set of ranks on which all boxes
    *  in the output balance_mapped_box_level will be restricted.  Some
    *  child classes may not make use of this argument.
    */
   virtual void
   loadBalanceMappedBoxLevel(
      hier::MappedBoxLevel& balance_mapped_box_level,
      hier::Connector& balance_to_anchor,
      hier::Connector& anchor_to_balance,
      const tbox::Pointer<hier::PatchHierarchy> hierarchy,
      const int level_number,
      const hier::Connector& unbalanced_to_attractor,
      const hier::Connector& attractor_to_unbalanced,
      const hier::IntVector& min_size,
      const hier::IntVector& max_size,
      const hier::MappedBoxLevel& domain_mapped_box_level,
      const hier::IntVector& bad_interval,
      const hier::IntVector& cut_factor, // Default v 2.x.x = hier::IntVector::getOne(tbox::Dimension(DIM))
      const tbox::RankGroup& rank_group = tbox::RankGroup()) const;

   /*!
    * @brief Gather workloads in an MPI group and write out a summary
    * of load balance efficiency.
    *
    * To be used for performance evaluation.  Not recommended for general use.
    *
    * @param[in] local_workload Workload of the local process
    *
    * @param[in] mpi Represents all processes involved in the load balancing.
    *
    * @param[in] output_stream
    *
    * TODO: This method is a utility that doesn't strictly belong in a
    * strategy design pattern.  It should be moved elsewhere.
    */
   void
   gatherAndReportLoadBalance(
      double local_workload,
      const tbox::SAMRAI_MPI& mpi,
      std::ostream& output_stream = tbox::plog) const;

   /*!
    * @brief Gather a sequence of workloads in an MPI group and write
    * out a summary of load balance efficiency.
    *
    * Each value in the sequence of workloads represent a certain load
    * the local process had over a sequence of load balancings.
    *
    * To be used for performance evaluation.  Not recommended for general use.
    *
    * @param[in] local_workloads Sequence of workloads of the local
    * process.  The size of @c local_loads is the number times load
    * balancing has been used.  It must be the same across all
    * processors in @c mpi.
    *
    * @param[in] mpi Represents all processes involved in the load balancing.
    *
    * @param[in] output_stream
    *
    * TODO: This method is a utility that doesn't strictly belong in a
    * strategy design pattern.  It should be moved elsewhere.
    */
   void
   gatherAndReportLoadBalance(
      const std::vector<double>& local_loads,
      const tbox::SAMRAI_MPI& mpi,
      std::ostream& output_stream = tbox::plog) const;

protected:

   /*!
    * @brief Write load data to log for postprocessing later.
    *
    * For development only.  Not for general use.
    *
    * @param[in] rank
    *
    * @param[in] load
    *
    * @param[in] nbox
    *
    * TODO: This method does not belong in a strategy base class and
    * should be moved elsewhere.
    */
   static void
   markLoadForPostprocessing(
      int rank,
      double load,
      int nbox);

   /*!
    * @brief Write out a short report of how well load is balanced.
    *
    * Given the workloads of a number of processes, format and write
    * out a brief report for assessing how well balanced the workloads
    * are.
    *
    * @param[in] workloads One value for each process.  The number of
    * processes is taken to be the size of this container.
    *
    * @param[in] output_stream
    *
    * TODO: This method does not belong in a strategy base class and
    * should be moved elsewhere.
    */
   static void
   reportLoadBalance(
      const std::vector<double>& workloads,
      std::ostream& output_stream);

private:
   // The following are not implemented:
   LoadBalanceStrategy(
      const LoadBalanceStrategy&);
   void
   operator = (
      const LoadBalanceStrategy&);

   struct RankAndLoad { int rank;
                        double load;
   };

   static int s_sequence_number;
   static int
   qsortRankAndLoadCompareAscending(
      const void* v,
      const void* w);
   static int
   qsortRankAndLoadCompareDescending(
      const void* v,
      const void* w);

};

}
}
#endif