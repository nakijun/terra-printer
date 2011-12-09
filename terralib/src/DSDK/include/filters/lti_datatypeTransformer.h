/* $Id: lti_datatypeTransformer.h 5124 2006-10-27 11:40:40Z lubia $ */
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

#ifndef LTI_DATATYPETRANSFORMER_H
#define LTI_DATATYPETRANSFORMER_H

// lt_lib_mrsid_imageFilters
#include "lti_dynamicRangeFilter.h"


LT_BEGIN_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
   #pragma warning(push,4)
#endif

// we support only float, uint8, uint16

class LTIReusableBSQBuffer;

#if defined LT_COMPILER_GCC
#warning "** LTIDataTypeTransformer is deprecated -- use LTIDynamicRangeFilter"
#elif defined LT_COMPILER_MS
#pragma message( "*******************************************" )
#pragma message( "*  LTIDataTypeTransformer is deprecated   *" )
#pragma message( "*       use LTIDynamicRangeFilter         *" )
#pragma message( "*******************************************" )
#endif
/**
 * changes the datatype of the samples of the image
 *
 * This class changes the datatype of the samples of the image.
 *
 * The values of the samples are scaled as required to meet the range of the
 * new datatype.
 */
class LTIDataTypeTransformer : public LTIDynamicRangeFilter
{
public:
   /**
    * constructor
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
   LTIDataTypeTransformer(LTIImageStage* sourceImage,
                          LTIDataType dstDataType,
                          bool takeOwnership) :
      LTIDynamicRangeFilter(sourceImage, dstDataType, takeOwnership)
   {
   }

private:
   // nope
   LTIDataTypeTransformer(const LTIDataTypeTransformer&);
   LTIDataTypeTransformer& operator=(const LTIDataTypeTransformer&);
};


LT_END_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
	#pragma warning(pop)
#endif

#endif // LTI_DATATYPETRANSFORMER_H
