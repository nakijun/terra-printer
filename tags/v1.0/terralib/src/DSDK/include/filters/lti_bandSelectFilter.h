/* $Id: lti_bandSelectFilter.h 5124 2006-10-27 11:40:40Z lubia $ */
/* //////////////////////////////////////////////////////////////////////////
//                                                                         //
// This code is Copyright (c) 2005 LizardTech, Inc, 1008 Western Avenue,   //
// Suite 200, Seattle, WA 98104.  Unauthorized use or distribution         //
// prohibited.  Access to and use of this code is permitted only under     //
// license from LizardTech, Inc.  Portions of the code are protected by    //
// US and foreign patents and other filings. All Rights Reserved.          //
//                                                                         //
////////////////////////////////////////////////////////////////////////// */
/* PUBLIC */

#ifndef LTI_BANDSELECTFILTER_H
#define LTI_BANDSELECTFILTER_H

// lt_lib_mrsid_core
#include "lti_imageFilter.h"


LT_BEGIN_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
   #pragma warning(push,4)
#endif


/**
 * combine N different bands from M images into one N-banded image
 *
 * This class creates a single N-banded image which is a composition of N
 * different bands from a set of images.
 *
 * For example, an RGB image can be created from three (nominally grayscale)
 * images which represent the red, green, and blue bands of a dataset.
 * More generally, one can do things like construct a multispectral image 
 * from 1st and 2nd bands of one image and the 3rd and 4th bands of a second
 * image.
 */
class LTIBandSelectFilter : public LTIImageFilter
{
public:
   /**
    * general constructor
    *
    * Creates an image stage which composes the specified bands of the input images.
    *
    * The \a srcImages and \a srcImageBands arrays each contain \a numOutputBands
    * elements and serve to describe the bands of the desired output image.  That is,
    * band \a i of the output image will contain band \a srcImageBands[i] from
    * image \a srcImages[i].
    *
    * An element of \a srcImages may be NULL.  In this case, however, the corresponding
    * \a srcImageBands element must be set to (int)-'Z', indicating a band of
    * all zeros is to be used.
    * 
    * At least one of the \a srcImages elements must be non-NULL.
    *
    * Note: Data from \a srcImages and \a srcImageBands arrays are copied locally
    * after initialize() is called.
    *
    * @param  srcImages       input images, for each output band
    * @param  srcImageBands   band numbers, for each output band
    * @param  numOutputBands  number of output bands
    * @param  colorSpace      the colorspace of the output image
    * @param  takeOwnership   set to true to have the filter delete the \a sourceImages
    */
   LTIBandSelectFilter(LTIImageStage** srcImages,
                       const int* srcImageBands,
                       int numOutputBands,
                       LTIColorSpace colorSpace,
                       bool takeOwnership);

   /**
    * single image constructor
    *
    * Same as the above general constructor, except that (1) a single source
    * image is used, instead of an array of possibly different images, and (2)
    * the output image has the same number of bands and colorspace as the input
    * image.
    *
    * (This provides compatability with the old LTISampleMapTransformer class.)
    *
    * @param  srcImage        input image
    * @param  srcImageBands   band numbers, for each output band
    * @param  numOutputBands       band numbers, for each output band
    * @param  colorSpace      the colorspace of the output image
    * @param  takeOwnership   set to true to have the filter delete the \a sourceImages
    */
   LTIBandSelectFilter(LTIImageStage* srcImage,
                       const lt_uint16* srcImageBands,
                       lt_uint16 numOutputBands,
                       LTIColorSpace colorSpace,
                       bool takeOwnership);

   /**
    * LTIColorCompositeFilter constructor
    *
    * Same as the above general constructor, except that (1) each source image is 
    * either a one-banded image or NULL, and (2) the \a srcImageBands array is
    * constructed as the form [0,1,2...].
    *
    * (This provides compatability with the old LTIColorCompositeFilter class.)
    *
    * @param  srcImages    input images
    * @param  numOutputBands       band numbers, for each output band
    * @param  colorSpace      the colorspace of the output image
    * @param  takeOwnership   set to true to have the filter delete the \a sourceImages
    */
   LTIBandSelectFilter(LTIImageStage** srcImages,
                       lt_uint16 numOutputBands,
                       LTIColorSpace colorSpace,
                       bool takeOwnership);

   virtual ~LTIBandSelectFilter();

   virtual LT_STATUS initialize();

   virtual lt_uint32 getStripHeight() const;
   virtual lt_int64 getPhysicalFileSize() const;
   virtual LT_STATUS setStripHeight(lt_uint32 stripHeight);

   /**
    * parse band string
    *
    * Given a string such as "1,3-4,2", this function will return an array
    * like [1,3,4,2].
    *
    * The formal grammar of the input string is (ignoring whitespace):
    *   string := token? (comma token)*
    *   token  := letter | number | number hyphen number
    *   letter := 'Z'
    *   number := digit+
    *   digit  := '0' | '1' | ... '9'
    *   comma  := ','
    *   hyphen := '-'
    * Note that the range may be negative, i.e. "3-1" will be returned
    * as [3,2,1].  A band value of Z indicates a band of all zeros should
    * be used.
    *
    * The caller takes ownership of the returned array.
    *
    * Note that the caller may need to adjust the data in the returned array
    * to be zero-based.
    *
    * @param inputString  the string to parse
    * @param bandList     returned array of band numbers
    * @param numBands     length of bandList arrat
    * @return status code
    */
   static LT_STATUS parseString(const char* inputString,
                                lt_int32*& bandList,
                                lt_uint16& numBands);

protected:
   LT_STATUS decodeBegin(const LTIScene& scene);
   LT_STATUS decodeEnd();
   LT_STATUS decodeStrip(LTISceneBuffer& stripBuffer, const LTIScene& stripScene);

protected:
   LT_STATUS initArrays();
   LT_STATUS initSourceArray();
   LT_STATUS initOutputArray();
   int getImageNum(const LTIImageStage* ptr) const;
   
   enum SourcePixel
   {
      NodataPixel,
      BackgroundPixel,
      DRMinPixel,
      DRMaxPixel
   };
   void remapPixel(LTIPixel& pixel, SourcePixel name) const;

   LTIColorSpace m_colorSpace;         // from ctor
   int m_numOutputBands;               // from ctor
   LTIImageStage** m_srcImages;        // from ctor, [0..m_numOutputBands-1]
   const int* m_srcImageBands;         // from ctor, [0..m_numOutputBands-1]
   const lt_uint16* m_srcImageBands16;

   class OutputBandDesc;
   OutputBandDesc* m_outputBandDescs;  // [0..m_numOutputBands-1]

   class InputImageDesc;
   InputImageDesc* m_inputImageDesc;   // [0..m_numInputImages-1]
   int m_numInputImages;
   
   LTIReusableBSQBuffer* m_zeroBuffer; // strip buffer holding just 0's
   LTIReusableBSQBuffer* m_nullBuffer; // just strip buffer, for unused buffers

   LTIImageStage** m_localSrcImages;
   int* m_localSrcImageBands;

private:
   const int m_ctor;

   // nope
   LTIBandSelectFilter(const LTIBandSelectFilter&);
   LTIBandSelectFilter& operator=(const LTIBandSelectFilter&);
};


LT_END_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
	#pragma warning(pop)
#endif

#endif // LTI_BANDSELECTFILTER_H
