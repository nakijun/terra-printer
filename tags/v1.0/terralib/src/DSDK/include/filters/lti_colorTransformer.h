/* $Id: lti_colorTransformer.h 5124 2006-10-27 11:40:40Z lubia $ */
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

#ifndef LTI_COLORTRANSFORMER_H
#define LTI_COLORTRANSFORMER_H

// lt_lib_mrsid_core
#include "lti_imageFilter.h"


LT_BEGIN_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
   #pragma warning(push,4)
#endif

class LTIReusableBSQBuffer;

/**
 * change the colorspace of the image
 *
 * This class changes the colorspace of the image.
 *
 * The supported color transforms are:
 * \li from RGB to CMYK, GRAYSCALE, or YIQ
 * \li from GRAYSCALE to RGB
 * \li from CMYK to RGB, RGBK, or YIQK
 * \li from YIQ to RGB
 * \li from YIQK to CMYK
 */
class LTIColorTransformer : public LTIImageFilter
{
public:
   /**
    * constructor
    *
    * Creates an image stage with the given colorspace.  The sample values
    * will undergo the requisite color transform function to map from the
    * input colorspace to the output colorspace.
    *
    * @note The value of \a dstNumBands image is set according to the
    * \a dstColorSpace, as is in the constructor for the LTIPixel class.
    *
    * @param  sourceImage    the base image
    * @param  dstColorSpace  the colorspace of the new image
    * @param  dstNumBands    the number of bands in the new image
    * @param  takeOwnership  set to true to have the filter delete the \a sourceImage
    */
   LTIColorTransformer(LTIImageStage* sourceImage,
                       LTIColorSpace dstColorSpace,
                       lt_uint16 dstNumBands,
                       bool takeOwnership);
   virtual ~LTIColorTransformer();
   virtual LT_STATUS initialize();

protected:
   LT_STATUS decodeBegin(const LTIScene& scene);
   LT_STATUS decodeEnd();
   LT_STATUS decodeStrip(LTISceneBuffer& stripBuffer, const LTIScene& stripScene);

private:
   bool isSupportedTransform(void) const;
   LT_STATUS transformBuffer(LTISceneBuffer &dstData,
                             LTISceneBuffer &srcData,
                             lt_uint32 width,
                             lt_uint32 height) const;

   LT_STATUS transformPixel(LTIPixel &newPixel,
                            const LTIPixel &oldPixel) const;


   const LTIColorSpace m_dstColorSpace;
   const lt_uint16 m_dstNumBands;
   LTIColorSpace m_srcColorSpace;
   lt_uint16 m_srcNumBands;
   bool m_isIdentity;

   LTIReusableBSQBuffer* m_buffer;

   // nope
   LTIColorTransformer(const LTIColorTransformer&);
   LTIColorTransformer& operator=(const LTIColorTransformer&);
};


LT_END_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
	#pragma warning(pop)
#endif

#endif // LTI_COLORTRANSFORMER_H
