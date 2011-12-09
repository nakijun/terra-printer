/* $Id: lti_multiresFilter.h 5124 2006-10-27 11:40:40Z lubia $ */
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

#ifndef LTI_MULTIRESFILTER_H
#define LTI_MULTIRESFILTER_H

// lt_lib_mrsid_core
#include "lti_imageFilter.h"
#include "lti_scene.h"

#if defined(LT_COMPILER_MS)
   #pragma warning(push,4)
#endif

LT_BEGIN_NAMESPACE(LizardTech)

class LTIResampler;

/**
 * add resolutions to the image
 *
 * Extends the magnification range of an image, to allow decodes at different
 * resolutions than the image stage would normally allow.
 *
 * Note that this class is not the same as at the LTIStaticZoomFilter class,
 * which scales the magnification statically for the pipeline when initially
 * constructed.  This class allows for the zoom level to be extended for an
 * individual decode operation.
 */
class LTIMultiResFilter : public LTIImageFilter
{
public:
   /**
    * constructor
    *
    * Creates an image stage which can be decoded at arbitrary magnifications.
    *
    * Normally image stages will only support a limited set of magnification
    * values for the LTIScene passed to LTIImageStage::read() -- often, only
    * 1.0.  This class will perform any needed resampling on the fly so that
    * arbitrary (power-of-two) magnifications are supported.
    *
    * @param  sourceImage     the base image
    * @param takeOwnership    set to true to have the filter delete the \a sourceImage
    */
   LTIMultiResFilter(LTIImageStage* sourceImage, bool takeOwnership);
   LTIMultiResFilter(LTIImageStage* sourceImage,
                     double deltaMag,
                     double minMag,
                     double maxMag,
                     bool takeOwnership);
   
   virtual ~LTIMultiResFilter();
   virtual LT_STATUS initialize();
   
   LT_STATUS setResampleMethod(LTIResampleMethod resampleMethod);

   virtual lt_int64 getEncodingCost(const LTIScene& scene) const;

   LT_STATUS projectPointAtMag(double upperLeft,
                               double mag,
                               double& newUpperLeft) const;
   
   LT_STATUS projectDimAtMag(double dim,
                             double mag,
                             double& newDim) const;

   LT_STATUS getDimsAtMag(double mag,
                          lt_uint32& width,
                          lt_uint32& height) const;


   bool getReaderScene(const LTIScene &decodeScene,
                       LTIScene &readerScene) const;


   // call this before initialize() if you want non-sq. pixels
   // (the deltaMag in the constructor is ignored)
   void setDeltaMagXY(double deltaMagX, double deltaMagY);

   static double magForIcon(const LTIImageStage &image,
                            lt_uint32 iconSize);

protected:
   LT_STATUS decodeBegin(const LTIScene& scene);
   LT_STATUS decodeStrip(LTISceneBuffer& stripBuffer,
                         const LTIScene& stripScene);
   LT_STATUS decodeEnd();


   enum Mode
   {
      MODE_INVALID,
      MODE_RESAMPLE,
      MODE_PASSTHROUGH,
      MODE_DOWNSAMPLE_FULLREAD,
      MODE_ALL_AT_ONCE
   };

   bool getChildScene(const LTIScene &scene,
                      Mode &mode,
                      double &scaleX,
                      double &scaleY,
                      LTIScene &childScene) const;
   
   enum
   {
      // The largest possible mag is based on the 2gb
      // scene limitation. Thus the largest scene we
      // should ever expect is approximately the square
      // root of (2gb / 3) pixels on a  side. If we
      // assume the smallest image we'll ever encounter
      // is 32x32 then the largest magnification can
      // be calculated. It's big, but we need a real number!
      kMaxMagnification = 512   // 51200% zoom!
   };

private:
   struct StripCache;

   double m_mrMinMag;
   double m_mrMaxMag;
   double m_deltaMagX;
   double m_deltaMagY;

   Mode m_mode;
   double m_scaleX;
   double m_scaleY;
   LTIScene m_childScene;
   double m_curY;
   
   lt_int32 m_childStrip;
   lt_int32 m_myStrip;

   StripCache *m_stripCache0;
   StripCache *m_stripCache1;
   
   LTIResampler *m_resampler;

   // nope
   LTIMultiResFilter(const LTIMultiResFilter&);
   LTIMultiResFilter& operator=(const LTIMultiResFilter&);
};


LT_END_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
	#pragma warning(pop)
#endif

#endif // LTI_MULTIRESFILTER_H
