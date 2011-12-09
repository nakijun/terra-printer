/* $Id: lti_mosaicFilter.h 5124 2006-10-27 11:40:40Z lubia $ */
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

#ifndef LTI_MOSAICFILTER_H
#define LTI_MOSAICFILTER_H

// lt_lib_mrsid_core
#include "lti_imageFilter.h"
#include "lti_imageStageManager.h"


LT_BEGIN_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
   #pragma warning(push,4)
#endif

class LTIRTree;
class LTIEmbeddedImage;
class LTIReusableBSQBuffer;

/**
 * create a single mosaicked image from a set of images
 *
 * This class create a single mosaicked image from a set of images.
 *
 * The set of input images are all assumed to be in the same coordinate
 * space.  In general, all the images must have the same resolution;
 * differences that are within a small epsilon or exactly a power of two
 * are optionally allowed.
 */
class LTIMosaicFilter : public LTIImageFilter
{
public:
   /**
    * constructor
    *
    * Creates an image stage which is a mosaic of the set of input images.
    *
    * The "res correct" feature allows images with slightly different
    * resolutions to be mosaicked.  This allows for proper handling of
    * situations where one image has a resolution of 0.5000 and another has a
    * resolution of 0.4999.
    *
    * The "multires" feature allows images whose resolutions which differ by
    * a power of two to be mosaicked together.  (The LTIStaticZoomFilter class
    * is used to implement this feature.)
    *
    * NoData and background pixel settings are honored by the mosaic process.
    *
    * @param  imageStageManager ?????
    * @param  backgroundPixel   color of the background pixel for the new image stage
    * @param  useResCorrect     allow images to have slightly different resolutions
    * @param  useMultires       allow images whose resolutions differ by a power of two
    * @param  takeOwnership     set to true to have the filter delete the \a sourceImage
    */
   LTIMosaicFilter(LTIImageStageManager *imageStageManager,
                   const LTIPixel* backgroundPixel,
                   bool useResCorrect,
                   bool useMultires,
                   bool takeOwnership);
   virtual ~LTIMosaicFilter();
   virtual LT_STATUS initialize();

   void setUsingFuzzyNoData(bool fuzzy);
   bool getUsingFuzzyNoData(void) const;

   void setDeleteImages(bool deleteImages);
   bool getDeleteImages(void) const;

   lt_int64 getPhysicalFileSize() const;

   lt_uint32 getStripHeight() const;
   LT_STATUS setStripHeight(lt_uint32 stripHeight);

   lt_int64 getEncodingCost(const LTIScene& scene) const;

   LT_STATUS projectPointAtMag(double upperLeft,
                               double mag,
                               double& newUpperLeft) const;
   
   LT_STATUS projectDimAtMag(double dim,
                             double mag,
                             double& newDim) const;

   LT_STATUS getDimsAtMag(double mag,
                          lt_uint32& width,
                          lt_uint32& height) const;

   bool getReaderScene(const LTIScene &decodeScene, LTIScene &readerScene) const;

   bool getReaderScene(lt_uint32 child,
                       const LTIScene &decodeScene,
                       LTIScene &mosaicScene,
                       LTIScene &readerScene) const;
#if 1
   class InSceneCallback
   {
   public:
      virtual LT_STATUS found(const LTIScene &scene,
                              lt_uint32 imageNum,
                              LTIEmbeddedImage &embedded,
                              LTIImageStage &image) = 0;   
   };

   LT_STATUS forEachImageStageInScene(const LTIScene &scene,
                                      InSceneCallback &callback);
#endif
   /**
    * Check if a set of images can be mosaicked together.  The parameters to
    * this function mirror those of the constructor: this function will
    * return LT_STS_Success if and only if the images' resolutions are such
    * that a mosaic can be produced.
    *
    * @param  imageStageManager ?????
    * @param  useResCorrect    allow images to have slightly different resolutions
    * @param  useMultires      allow images whose resolutions differ by a power of two
    * @return status code indicating success or failure
    */
   static LT_STATUS checkResolutionConformance(LTIImageStageManager *imageStageManager,
                                               bool useResCorrect,
                                               bool useMultires);

   // these functions are used the Callbacks
   LT_STATUS loadImage(lt_uint32 i,
                       LTIEmbeddedImage *&embedded,
                       LTIImageStage *&raw);

   LT_STATUS closeImage(lt_uint32 i);

protected:
   virtual LT_STATUS decodeBegin(const LTIScene& scene);
   virtual LT_STATUS decodeStrip(LTISceneBuffer& stripBuffer, const LTIScene& stripScene);
   virtual LT_STATUS decodeEnd();

   LT_STATUS buildRTree(LTIImageStageManager &imageStageManager,
                        LTIMetadataDatabase &metadata);

private:
   class ListImageStagesInSceneCallback;

   LTIImageStageManager *m_imageStageManager;
   LTIPixel* m_userBackgroundPixel;
   bool m_useResCorrect;
   bool m_useMultires;

   lt_int64 m_physicalFileSize;

   LTIRTree *m_rtree;

   // open image book keeping
   LTIImageStage **m_rImage;
   LTIImageStage **m_fImage;
   int *m_sImage;
   bool m_fuzzyNoData;
   bool m_deleteImages;
   lt_uint32 m_stripHeight;
   LTIPixel *m_zeroPixel;
   LTIReusableBSQBuffer *m_workBuffer;

   // imageInScene
   lt_uint32 *m_inSceneList;

   // nope
   LTIMosaicFilter(const LTIMosaicFilter&);
   LTIMosaicFilter& operator=(const LTIMosaicFilter&);
};

LT_END_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
	#pragma warning(pop)
#endif

#endif // LTI_MOSAICFILTER_H
