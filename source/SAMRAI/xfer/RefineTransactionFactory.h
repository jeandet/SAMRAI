/*************************************************************************
 *
 * This file is part of the SAMRAI distribution.  For full copyright 
 * information, see COPYRIGHT and COPYING.LESSER. 
 *
 * Copyright:     (c) 1997-2011 Lawrence Livermore National Security, LLC
 * Description:   Interface for factory objects that create transactions for
 *                refine schedules. 
 *
 ************************************************************************/

#ifndef included_xfer_RefineTransactionFactory
#define included_xfer_RefineTransactionFactory

#include "SAMRAI/SAMRAI_config.h"

#include "SAMRAI/tbox/DescribedClass.h"
#include "SAMRAI/tbox/Transaction.h"
#include "SAMRAI/hier/GridGeometry.h"
#include "SAMRAI/hier/PatchLevel.h"
#include "SAMRAI/xfer/RefineClasses.h"

namespace SAMRAI {
namespace xfer {

/*!
 * @brief Abstract base class defining the interface for all concrete transaction
 * factory objects that generate data transaction objects used with a RefineSchedule
 * object.  A concrete subclass will allocate new transaction objects.  This class
 * is an example of the ``Abstract Factory'' method described in the Design Patterns
 * book by Gamma, et al.
 *
 * To add a new type of Transaction object MyRefineTransaction:
 *
 * -# Implement a concrete RefineTransactionFactory object as a subclass
 *       that is derived from this RefineTransactionFactory base class.
 *       Implement the abstract virtual functions as appropriate for the
 *       concrete subclass; in particular, the allocate() function must return
 *       a new instance of the desired transaction object.
 * -# The type of the transaction allocated by the concrete factory is a
 *       Transaction<DIM>.  Thus, the new transaction object must be derived
 *       from the Transaction<DIM> base class and implement the abstract
 *       virtual functions declared by the base class.
 *
 * @see tbox::Transaction
 */

class RefineTransactionFactory:public tbox::DescribedClass
{
public:
   /*!
    * @brief Default constructor.
    */
   RefineTransactionFactory();

   /*!
    * @brief Virtual destructor.
    */
   virtual ~RefineTransactionFactory();

   /*!
    * @brief Pure virtual function to set the array of RefineClass::Data items
    * associated with the refine schedule.  Typical concrete transactions used by
    * the schedule use this information to communicate data.  This operation
    * is called by the refine schedule during the execution of the
    * RefineSchedule::fillData() routine before data communication
    * operations begin.
    */
   virtual void
   setRefineItems(
      const RefineClasses::Data** refine_items,
      int num_refine_items) = 0;

   /*!
    * @brief Pure virtual function to clear the array of RefineClass::Data items
    * associated with the refine schedule.  This operation is called by the
    * refine schedule after data communication operations are complete.
    */
   virtual void
   unsetRefineItems() = 0;

   /*!
    * @brief Pure virtual function to allocate a concrete refine transaction object.
    * This routine is called by the refine schedule during construction of the
    * schedule.
    *
    * @param dst_level      tbox::Pointer to destination patch level.
    * @param src_level      tbox::Pointer to source patch level.
    * @param overlap        tbox::Pointer to overlap region between patches.
    * @param dst_patch_id   Integer index of destination patch in destination
    *                       patch level.
    * @param src_patch_id   Integer index of source patch in source patch level.
    * @param ritem_id       Integer index of RefineClass::Data item associated
    *                       with transaction.
    * @param box            Optional const reference to box defining region of
    *                       refine transaction.  Default is an empty box.
    * @param use_time_interpolation  Optional boolean flag indicating whether the
    *                       refine transaction involves time interpolation.
    *                       Default is false.
    */
   virtual tbox::Pointer<tbox::Transaction>
   allocate(
      tbox::Pointer<hier::PatchLevel> dst_level,
      tbox::Pointer<hier::PatchLevel> src_level,
      tbox::Pointer<hier::BoxOverlap> overlap,
      const hier::MappedBox& dst_mapped_box,
      const hier::MappedBox& src_mapped_box,
      int ritem_id,
      const hier::Box& box,
      bool use_time_interpolation = false) const = 0;

   tbox::Pointer<tbox::Transaction>
   allocate(
      tbox::Pointer<hier::PatchLevel> dst_level,
      tbox::Pointer<hier::PatchLevel> src_level,
      tbox::Pointer<hier::BoxOverlap> overlap,
      const hier::MappedBox& dst_mapped_box,
      const hier::MappedBox& src_mapped_box,
      int ritem_id) const;

   /*!
    * @brief Virtual function to set simulation time for transaction objects.
    * This operation is called by the refine schedule during the execution of
    * the RefineSchedule::fillData() routine before data communication
    * operations begin.  This function is optional for the concrete transaction
    * factory object.  The default implementation is a no-op.
    */
   virtual void
   setTransactionTime(
      double fill_time);

   /*!
    * @brief Virtual function allowing transaction factory to preprocess scratch
    * space data before transactactions use it if they need to.  This function is
    * optional for the concrete transaction factory object.
    * The default implementation is a no-op.
    *
    * @param level        tbox::Pointer to patch level holding scratch data.
    * @param fill_time    Double value of simulation time corresponding to
    *                     RefineSchedule operations.
    * @param preprocess_vector Const reference to ComponentSelector that indicates
    *                     patch data array indices of scratch patch data objects
    *                     to preprocess.
    */
   virtual void
   preprocessScratchSpace(
      tbox::Pointer<hier::PatchLevel> level,
      double fill_time,
      const hier::ComponentSelector& preprocess_vector) const;

private:
   // The following two functions are not implemented
   RefineTransactionFactory(
      const RefineTransactionFactory&);
   void
   operator = (
      const RefineTransactionFactory&);

};

}
}
#endif