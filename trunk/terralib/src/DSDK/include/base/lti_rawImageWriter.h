/* $Id: lti_rawImageWriter.h 5124 2006-10-27 11:40:40Z lubia $ */
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

#ifndef LTIRAWIMAGEWRITER_H
#define LTIRAWIMAGEWRITER_H

// lt_lib_mrsid_core
#include "lti_geoFileImageWriter.h"


LT_BEGIN_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
   #pragma warning(push,4)
#endif

class LTIReusableBSQBuffer;

/**
 * class for writing RAW files
 *
 * This class writes an image to a stream in RAW format.
 *
 * The RAW format used is simple packed BIP form.
 */
class LTIRawImageWriter : public LTIGeoFileImageWriter
{
public:
   /**
    * default constructor
    *
    * This constructor creates an LTIRawImageWriter which will write the
    * pixels of the given image to the given stream.
    *
    * @param  image   the image to be read from  
    */
   LTIRawImageWriter(LTIImageStage* image);

   /**
    * destructor
    */
   virtual ~LTIRawImageWriter();

   /**
    * initializer
    */
   virtual LT_STATUS initialize();

   LTILayout getLayout() const { return m_layout; };

   virtual LT_STATUS writeBegin(const LTIScene& scene);
   virtual LT_STATUS writeStrip(LTISceneBuffer& stripBuffer, const LTIScene& stripScene);

   /**
    * set layout
    *
    * This function is used to determine the layout of the output
    * image, i.e. BIP or BIL or BSQ.
    *
    * @param layout the layout to use
    */
   void setLayout(LTILayout layout);

   /**
    * set byte order
    *
    * This function is used to determine byte ordering of the output file.
    *
    * @param byteOrder the byte ordering to use
    */
   void setByteOrder(LTIEndian byteOrder);

protected:
   LTILayout m_layout;
   LTIEndian m_byteOrder;

private:
   lt_uint32 m_fullWidth;
   lt_uint32 m_fullHeight;
   lt_uint32 m_curRow;
   LTIReusableBSQBuffer* m_stripBuffer;

   // nope
   LTIRawImageWriter(LTIRawImageWriter&);
   LTIRawImageWriter& operator=(const LTIRawImageWriter&);
};


LT_END_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
	#pragma warning(pop)
#endif

#endif // LTIRAWIMAGEWRITER_H
