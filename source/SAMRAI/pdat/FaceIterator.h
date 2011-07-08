/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright 
 * information, see COPYRIGHT and COPYING.LESSER. 
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   Iterator for face centered patch data types 
 *
 ************************************************************************/

#ifndef included_pdat_FaceIterator
#define included_pdat_FaceIterator

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/hier/Box.h"
#include "SAMRAI/pdat/FaceGeometry.h"
#include "SAMRAI/pdat/FaceIndex.h"

namespace SAMRAI {
namespace pdat {

/**
 * Class FaceIterator is an iterator that provides methods for
 * stepping through the index space associated with a face centered box.
 * The indices are enumerated in column-major (e.g., Fortran) order.
 * The iterator should be used as follows:
 * \verbatim
 * hier::Box box;
 * ...
 * for (FaceIterator c(box, axis); c; c++) {
 *    // use index c of the box
 * }
 * \endverbatim
 * Note that the face iterator may not compile to efficient code, depending
 * on your compiler.  Many compilers are not smart enough to optimize the
 * looping constructs and indexing operations.
 *
 * @see pdat::FaceData
 * @see pdat::FaceGeometry
 * @see pdat::FaceIndex
 */

class FaceIterator
{
public:
   /**
    * Constructor for the face iterator.  The iterator will enumerate
    * the indices in the argument box.
    */
   explicit FaceIterator(
      const hier::Box& box,
      const int axis);

   /**
    * Copy constructor for the face iterator
    */
   FaceIterator(
      const FaceIterator& iterator);

   /**
    * Assignment operator for the face iterator.
    */
   FaceIterator&
   operator = (
      const FaceIterator& iterator);

   /**
    * Destructor for the face iterator.
    */
   ~FaceIterator();

   /**
    * Extract the face index corresponding to the iterator position in the box.
    */
   const FaceIndex&
   operator * () const;

   /**
    * Extract the face index corresponding to the iterator position in the box.
    */
   const FaceIndex&
   operator () () const;

   /**
    * Return true if the iterator points to a valid index within the box.
    */
   operator bool () const;

#ifndef LACKS_BOOL_VOID_RESOLUTION
   /**
    * Return a non-NULL if the iterator points to a valid index within the box.
    */
   operator const void
   * () const;
#endif

   /**
    * Return whether the iterator points to a valid index within the box.
    * This operator mimics the !p operation applied to a pointer p.
    */
   bool
   operator ! () const;

   /**
    * Increment the iterator to point to the next index in the box.
    */
   void
   operator ++ (
      int);

   /**
    * Test two iterators for equality (same index value).
    */
   bool
   operator == (
      const FaceIterator& iterator) const;

   /**
    * Test two iterators for inequality (different index values).
    */
   bool
   operator != (
      const FaceIterator& iterator) const;

private:
   FaceIndex d_index;
   hier::Box d_box;
};

}
}
#ifdef SAMRAI_INLINE
#include "SAMRAI/pdat/FaceIterator.I"
#endif
#endif