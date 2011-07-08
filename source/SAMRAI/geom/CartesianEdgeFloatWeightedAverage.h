/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright 
 * information, see COPYRIGHT and COPYING.LESSER. 
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   Weighted averaging operator for edge-centered float data on
 *                a Cartesian mesh. 
 *
 ************************************************************************/

#ifndef included_geom_CartesianEdgeFloatWeightedAverage
#define included_geom_CartesianEdgeFloatWeightedAverage

#include "SAMRAI/SAMRAI_config.h"
#include "SAMRAI/hier/Box.h"
#include "SAMRAI/hier/IntVector.h"
#include "SAMRAI/hier/Patch.h"
#include "SAMRAI/tbox/Pointer.h"
#ifndef included_String
#include <string>
#define included_String
#endif
#include "SAMRAI/hier/CoarsenOperator.h"

namespace SAMRAI {
namespace geom {

/**
 * Class CartesianEdgeFloatWeightedAverage implements conservative
 * edge-weighted averaging for edge-centered float patch data defined over a
 * Cartesian mesh.  It is derived from the hier::CoarsenOperator base class.
 * The numerical operations for theaveraging use FORTRAN numerical routines.
 *
 * The findCoarsenOperator() operator function returns true if the input
 * variable is edge-centered float, and the std::string is "CONSERVATIVE_COARSEN".
 *
 * @see hier::CoarsenOperator
 */

class CartesianEdgeFloatWeightedAverage:
   public hier::CoarsenOperator
{
public:
   /**
    * Uninteresting default constructor.
    */
   explicit CartesianEdgeFloatWeightedAverage(
      const tbox::Dimension& dim);

   /**
    * Uninteresting virtual destructor.
    */
   virtual ~CartesianEdgeFloatWeightedAverage();

   /**
    * Return true if the variable and name std::string match the edge-centered
    * float weighted averaging; otherwise, return false.
    */
   bool
   findCoarsenOperator(
      const tbox::Pointer<hier::Variable>& var,
      const std::string& op_name) const;

   /**
    * The priority of edge-centered float weighted averaging is 0.
    * It will be performed before any user-defined coarsen operations.
    */
   int
   getOperatorPriority() const;

   /**
    * The stencil width of the weighted averaging operator is the vector of
    * zeros.  That is, its stencil does not extend outside the fine box.
    */
   hier::IntVector
   getStencilWidth() const;

   /**
    * Coarsen the source component on the fine patch to the destination
    * component on the coarse patch using the edge-centered float weighted
    * averaging operator.  Coarsening is performed on the intersection of
    * the destination patch and the coarse box.  It is assumed that the
    * fine patch contains sufficient data for the stencil width of the
    * coarsening operator.
    */
   void
   coarsen(
      hier::Patch& coarse,
      const hier::Patch& fine,
      const int dst_component,
      const int src_component,
      const hier::Box& coarse_box,
      const hier::IntVector& ratio) const;
};

}
}
#endif