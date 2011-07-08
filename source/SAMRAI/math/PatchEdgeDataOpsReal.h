/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright 
 * information, see COPYRIGHT and COPYING.LESSER. 
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   Templated operations for real edge-centered patch data. 
 *
 ************************************************************************/

#ifndef included_math_PatchEdgeDataOpsReal
#define included_math_PatchEdgeDataOpsReal

#include "SAMRAI/pdat/EdgeData.h"
#include "SAMRAI/math/PatchEdgeDataBasicOps.h"
#include "SAMRAI/math/PatchEdgeDataMiscellaneousOpsReal.h"
#include "SAMRAI/math/PatchEdgeDataNormOpsReal.h"
#include "SAMRAI/hier/Box.h"
#include "SAMRAI/hier/Patch.h"

#include "SAMRAI/tbox/PIO.h"
#include "SAMRAI/tbox/Pointer.h"

#include <iostream>

namespace SAMRAI {
namespace math {

/**
 * Class PatchEdgeDataOpsReal provides a collection of operations
 * to manipulate float and double numerical edge-centered patch data.  The
 * operations include basic arithmetic, norms and ordering, and assorted
 * miscellaneous operations.  With the assertion of a few basic routines,
 * this class inherits its interface (and thus its functionality) from the
 * base classes PatchEdgeDataBasicOps, PatchEdgeDataNormOpsReal,
 * and PatchEdgeDataMiscellaneousOpsReal from which it is derived.  The
 * name of each of these base classes is indicative of the set of
 * edge-centered patch data operations that it provides.
 *
 * Note that this templated class should only be used to instantiate
 * objects with double or float as the template parameter.  A similar set of
 * operations is implemented for complex and integer patch data in the classes
 * PatchEdgeDataOpsComplex and PatchEdgeDataOpsInteger,
 * repsectively.
 *
 * @see math::PatchEdgeDataBasicOps
 * @see math::PatchEdgeDataMiscellaneousOpsReal
 * @see math::PatchEdgeDataNormOpsReal
 */

template<class TYPE>
class PatchEdgeDataOpsReal:
   public tbox::DescribedClass,
   public PatchEdgeDataBasicOps<TYPE>,
   public PatchEdgeDataMiscellaneousOpsReal<TYPE>,
   public PatchEdgeDataNormOpsReal<TYPE>
{
public:
   /**
    * Empty constructor and destructor.
    */
   PatchEdgeDataOpsReal();

   virtual ~PatchEdgeDataOpsReal<TYPE>() {}

   /**
    * Copy dst data to src data over given box.
    */
   void
   copyData(
      tbox::Pointer<pdat::EdgeData<TYPE> >& dst,
      const tbox::Pointer<pdat::EdgeData<TYPE> >& src,
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
      const tbox::Pointer<pdat::EdgeData<TYPE> >& data,
      const hier::Box& box,
      std::ostream& s = tbox::plog) const;

   /**
    * Initialize data to given scalar over given box.
    */
   void
   setToScalar(
      tbox::Pointer<pdat::EdgeData<TYPE> >& dst,
      const TYPE& alpha,
      const hier::Box& box) const;

private:
   // The following are not implemented:
   PatchEdgeDataOpsReal(
      const PatchEdgeDataOpsReal<TYPE>&);
   void
   operator = (
      const PatchEdgeDataOpsReal<TYPE>&);

};

}
}

#ifdef INCLUDE_TEMPLATE_IMPLEMENTATION
#include "SAMRAI/math/PatchEdgeDataOpsReal.C"
#endif

#endif