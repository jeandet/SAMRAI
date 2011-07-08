/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright 
 * information, see COPYRIGHT and COPYING.LESSER. 
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   Templated operations for real node-centered patch data. 
 *
 ************************************************************************/

#ifndef included_math_PatchNodeDataOpsReal
#define included_math_PatchNodeDataOpsReal

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/pdat/NodeData.h"
#include "SAMRAI/math/PatchNodeDataBasicOps.h"
#include "SAMRAI/math/PatchNodeDataMiscellaneousOpsReal.h"
#include "SAMRAI/math/PatchNodeDataNormOpsReal.h"
#include "SAMRAI/hier/Box.h"
#include "SAMRAI/hier/Patch.h"
#include "SAMRAI/tbox/PIO.h"
#include "SAMRAI/tbox/Pointer.h"

#include <iostream>

namespace SAMRAI {
namespace math {

/**
 * Class PatchNodeDataOpsReal provides a collection of operations
 * to manipulate float and double numerical node-centered patch data.  The
 * operations include basic arithmetic, norms and ordering, and assorted
 * miscellaneous operations.  With the assertion of a few basic routines,
 * this class inherits its interface (and thus its functionality) from the
 * base classes PatchNodeDataBasicOps, PatchNodeDataNormOpsReal,
 * and PatchNodeDataMiscellaneousOpsReal from which it is derived.  The
 * name of each of these base classes is indicative of the set of
 * node-centered patch data operations that it provides.
 *
 * Note that this templated class should only be used to instantiate
 * objects with double or float as the template parameter.  A similar set of
 * operations is implemented for complex and integer patch data in the classes
 * PatchNodeDataOpsComplex and PatchNodeDataOpsInteger,
 * repsectively.
 *
 * @see math::PatchNodeDataBasicOps
 * @see math::PatchNodeDataMiscellaneousOpsReal
 * @see math::PatchNodeDataNormOpsReal
 */

template<class TYPE>
class PatchNodeDataOpsReal:
   public tbox::DescribedClass,
   public PatchNodeDataBasicOps<TYPE>,
   public PatchNodeDataMiscellaneousOpsReal<TYPE>,
   public PatchNodeDataNormOpsReal<TYPE>
{
public:
   /**
    * Empty constructor and destructor.
    */
   PatchNodeDataOpsReal();

   virtual ~PatchNodeDataOpsReal<TYPE>() {}

   /**
    * Copy dst data to src data over given box.
    */
   void
   copyData(
      tbox::Pointer<pdat::NodeData<TYPE> >& dst,
      const tbox::Pointer<pdat::NodeData<TYPE> >& src,
      const hier::Box& box) const;

   /**
    * Swap pointers for patch data objects.  Objects are checked for
    * consistency of depth, box, and ghost box.
    */
   void
   swapData(
      tbox::Pointer<hier::Patch> patch,
      const int data1_id,
      const int data2_id) const;

   /**
    * Print data entries over given box to given output stream.
    */
   void
   printData(
      const tbox::Pointer<pdat::NodeData<TYPE> >& data,
      const hier::Box& box,
      std::ostream& s = tbox::plog) const;

   /**
    * Initialize data to given scalar over given box.
    */
   void
   setToScalar(
      tbox::Pointer<pdat::NodeData<TYPE> >& dst,
      const TYPE& alpha,
      const hier::Box& box) const;

private:
   // The following are not implemented:
   PatchNodeDataOpsReal(
      const PatchNodeDataOpsReal<TYPE>&);
   void
   operator = (
      const PatchNodeDataOpsReal<TYPE>&);

};

}
}

#ifdef INCLUDE_TEMPLATE_IMPLEMENTATION
#include "SAMRAI/math/PatchNodeDataOpsReal.C"
#endif

#endif