/* $Id: lti_staticZoomFilter.h 5124 2006-10-27 11:40:40Z lubia $ */
/* //////////////////////////////////////////////////////////////////////////
//                                                                         //
// This code is Copyright (c) 2004 LizardTech, Inc, 1008 Western Avenue,   //
// Suite 200, Seattle, WA 98104.  Unauthorized use or distribution         //
// prohibited.  Access to and use of this code is permitted only under     //
// license from LizardTech, Inc.  Portions of the code are protected by    //
// US and foreign patents and other filings. All Rights Reserved.          //
//                                                                         //
////////////////////////////////////////////////////////////////////////// */
/* PUBLIC */

#ifndef LTI_STATICZOOMFILTER_H
#define LTI_STATICZOOMFILTER_H

// lt_lib_mrsid_imageFilter
#include "lti_multiresFilter.h"


LT_BEGIN_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
   #pragma warning(push,4)
#endif

/**
 * magnifies the image by a fixed amount
 *
 * This class magnifies the image by a fixed amount.  In effect this simply changes the
 * width and height of the image statically, i.e. for the life of the
 * pipeline.  The resampling is performed internally by the LTIMultiresFilter
 * class.
 */
class LTIStaticZoomFilter : public LTIMultiResFilter
{
public:
   /**
    * constructor
    *
    * Magnifies the image by the scale factor given.  The image width, height,
    * geographic resolution, etc, are all updated accordingly.
    *
    * A positive scale factor performs a "res-up" operation, while a negative
    * scale factor will reduce the image.  That is, a scale factor of 2 will
    * double the image size, e.g. from a magnification of 1.0 to 2.0, while a
    * scale factor of -2 will halve the image size, e.g. from a magnification
    * of 1.0 to 0.5.
    * 
    * @param  sourceImage   the base image
    * @param  scaleFactor    the integer scale factor
    * @param takeOwnership  set to true to have the filter delete the \a sourceImage
    */
   LTIStaticZoomFilter(LTIImageStage* sourceImage,
                       lt_int8 scaleFactor,
                       bool takeOwnership);

   LTIStaticZoomFilter(LTIImageStage* sourceImage,
                       double deltaMag,
                       double minMag,
                       double maxMag,
                       bool takeOwnership);
   
protected:

private:

   // nope
   LTIStaticZoomFilter(const LTIStaticZoomFilter&);
   LTIStaticZoomFilter& operator=(const LTIStaticZoomFilter&);
};


LT_END_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
	#pragma warning(pop)
#endif

#endif // LTI_STATICZOOMFILTER_H
