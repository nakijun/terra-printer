/* $Id: lti_dynamicRangeFilter.h 5124 2006-10-27 11:40:40Z lubia $ */
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

#ifndef LTI_DYNAMIC_RANGE_FILTER_H
#define LTI_DYNAMIC_RANGE_FILTER_H

// lt_lib_mrsid_core
#include "lti_imageFilter.h"


LT_BEGIN_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
   #pragma warning(push,4)
#endif

class LTIReusableBSQBuffer;

/**
 * change dynamic range or datatype of the samples of the image
 *
 * Adjusts the sample values to fit the given dynamic range and datatype.
 */

class LTIDynamicRangeFilter : public LTIImageFilter
{
public:

   /**
    * constructor
    *
    * Creates an image stage with the sample data adjusted according to the
    * given dynamic range values.
    *
    * @param  sourceImage    the base image
    * @param  srcDRMin       the min value of the sourceImage (will be mapped to the min value of dstDataType)
    * @param  srcDRMax       the max value of the sourceImage (will be mapped to the max value of dstDataType)
    * @param  dstDataType    the datatype of the new image stage
    * @param  takeOwnership  set to true to have the filter delete the \a sourceImage
    */
   LTIDynamicRangeFilter(LTIImageStage* sourceImage,
                         double srcDRMin,
                         double srcDRMax,
                         LTIDataType dstDataType,
                         bool takeOwnership);

   /**
    * constructor (for compatibly with old LTIDynamicRangeFilter)
    *
    * Creates an image stage with the sample data adjusted according to the
    * given dynamic range values.
    *
    * @param  sourceImage    the base image
    * @param  window         the number of units or "width" of the desired range
    * @param  level          the midpoint of the window; this effectively defines
    *                        the min and max sample values
    * @param  takeOwnership  set to true to have the filter delete the \a sourceImage
    */
   LTIDynamicRangeFilter(LTIImageStage* sourceImage,
                         double window,
                         double level,
                         bool takeOwnership);

   /**
   * constructor  (for compatibly with old LTIDynamicRangeFilter)
   *
   * Creates an image stage with the sample data adjusted according to the
   * dynamic range values inherit in the image, e.g. in the metadata.
   *
   * @param  sourceImage    the base image
   * @param  takeOwnership  set to true to have the filter delete the \a sourceImage
   */
   LTIDynamicRangeFilter(LTIImageStage* sourceImage,
                         bool takeOwnership);

   /**
    * constructor  (for compatibly with LTIDataTypeTransformer)
    *
    * Creates an image stage with the given datatype.  The sample values are
    * scaled as required to meet the range of the new datatype; that is, a
    * value of 65535 for a 16-bit datatype will map to a value of 255 for an
    * 8-bit datatype, and a value of 127 for an 8-bit datatype will map to
    * a value of 32767 for a 16-bit datatype.
    *
    * @note Only uint8, uint16, and float32 datatypes are supported.
    *
    * @param  sourceImage    the base image
    * @param  dstDataType    the datatype of the new image stage
    * @param  takeOwnership  set to true to have the filter delete the \a sourceImage
    */
   LTIDynamicRangeFilter(LTIImageStage* sourceImage,
                         LTIDataType dstDataType,
                         bool takeOwnership);

   virtual ~LTIDynamicRangeFilter(void);
   virtual LT_STATUS initialize(void);

   LT_STATUS setSrcMinMax(double srcMin, double srcMax);
   LT_STATUS setDstMinMax(double dstMin, double dstMax);

   static double getValue(const LTIPixel &pixel);
   
protected:
   LT_STATUS decodeBegin(const LTIScene& scene);
   LT_STATUS decodeEnd();
   LT_STATUS decodeStrip(LTISceneBuffer& stripBuffer,
                         const LTIScene& stripScene);

private:
   LT_STATUS transformBuffer(LTISceneBuffer &dstData,
                             LTISceneBuffer &srcData,
                             lt_uint32 numCols,
                             lt_uint32 numRows) const;
   LT_STATUS transformPixel(LTIPixel &newPixel,
                            const LTIPixel &oldPixel) const;

   const LTIDataType m_dstDataType;
   const LTIDataType m_srcDataType;
   
   double m_srcMin;
   double m_srcMax;
   double m_dstMin;
   double m_dstMax;

   LTIReusableBSQBuffer* m_buffer;

   // nope
   LTIDynamicRangeFilter(const LTIDynamicRangeFilter &);
   LTIDynamicRangeFilter &operator=(const LTIDynamicRangeFilter &);
};


LT_END_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
	#pragma warning(pop)
#endif

#endif // LTI_DYNAMIC_RANGE_FILTER_H
