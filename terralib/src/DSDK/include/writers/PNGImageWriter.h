/* $Id: PNGImageWriter.h 5124 2006-10-27 11:40:40Z lubia $ */
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

#ifndef PNGIMAGEWRITER_H
#define PNGIMAGEWRITER_H

// lt_lib_mrsid_core
#include "lti_geoFileImageWriter.h"

#if defined(LT_COMPILER_MS)
   #pragma warning(push,4)
#endif

struct png_struct_def;
struct png_info_struct;

LT_BEGIN_NAMESPACE(LizardTech)

class LTFileSpec;
class LTReusableBuffer;

/**
 * writes an image stage to a PNG file
 *
 * This class writes an image stage to a PNG file.
 */
class PNGImageWriter : public LTIGeoFileImageWriter
{
public:
   PNGImageWriter(LTIImageStage* image);
   virtual ~PNGImageWriter();
   
   LT_STATUS initialize();

   LT_STATUS setWriteTransparencyColor(bool write);


   LT_STATUS writeBegin(const LTIScene& scene);
   LT_STATUS writeStrip(LTISceneBuffer& stripBuffer, const LTIScene& stripScene);
   LT_STATUS writeEnd();

private:
   typedef LTIGeoFileImageWriter Super;

   LT_STATUS checkImpedance() const;

   struct png_struct_def *m_png;
   struct png_info_struct *m_info;
   bool m_writeTransparencyColor;
   char *m_errorMessage;

   LTReusableBuffer *m_stripBuffer;

   // nope
   PNGImageWriter(PNGImageWriter&);
   PNGImageWriter& operator=(const PNGImageWriter&);
};


LT_END_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
	#pragma warning(pop)
#endif

#endif // PNGIMAGEWRITER_H
