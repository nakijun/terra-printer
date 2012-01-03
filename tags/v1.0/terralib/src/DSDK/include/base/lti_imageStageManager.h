/* $Id: lti_imageStageManager.h 5124 2006-10-27 11:40:40Z lubia $ */
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

#ifndef LTI_IMAGESTAGEMANAGER_H
#define LTI_IMAGESTAGEMANAGER_H

// lt_lib_mrsid_core
#include "lti_imageStage.h"


LT_BEGIN_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
   #pragma warning(push,4)
#endif


/**
 * abstract class for managing file formats with multiply images/tiles
 */
class LTIImageStageManager
{
public:

   /**
    * destructor
    */
   virtual ~LTIImageStageManager();

   /**
    * create an image stage
    *
    * Note when done with the image stage call deleteImageStage() because the
    * may cache the image stage.
    *
    * @param  imageNumber  id/number of the image
    * @param  imageStage   a pointer to the created image stage
    */
   virtual LT_STATUS createImageStage(lt_uint32 imageNumber,
                                      LTIImageStage *&imageStage) = 0;

   /**
    * give the image stage back to the manager
    *
    * @param  imageNumber  id/number of the image
    * @param  imageStage   a pointer to the image stage to delete
    */
   virtual LT_STATUS deleteImageStage(lt_uint32 imageNumber,
                                      LTIImageStage *imageStage) = 0;

   /**
    * get the number of images/tiles the object is managing
    */
   lt_uint32 getNumImages(void) const;

protected:
   LTIImageStageManager(void);
   void setNumImages(lt_uint32 numImages);

private:
   lt_uint32 m_numImages;

   // nope
   LTIImageStageManager(const LTIImageStageManager &);
   LTIImageStageManager& operator=(const LTIImageStageManager &);
};


LT_END_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
	#pragma warning(pop)
#endif

#endif // LTI_IMAGESTAGEMANAGER_H
