/* $Id: lti_geoImageReader.h 5124 2006-10-27 11:40:40Z lubia $ */
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

#ifndef LTI_GEOIMAGEREADER_H
#define LTI_GEOIMAGEREADER_H

// lt_lib_mrsid_core
#include "lti_imageReader.h"


LT_BEGIN_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
   #pragma warning(push,4)
#endif

class LTFileSpec;
class LTIOStreamInf;

/**
 * abstract class for implementing a geo image reader
 *
 * The LTIGeoImageReader abstract class extends the LTIImageReader so that it
 * allows whether world files are used or ignored for setting up geo 
 * information.
 */
class LTIGeoImageReader : public LTIImageReader
{
public:
   /**
    * constructor
    */
   LTIGeoImageReader(bool useWorldFile);

   /**
    * destructor
    */
   virtual ~LTIGeoImageReader();

protected:
   bool getUseWorldFile() const;

   LT_STATUS readWorldFile(const LTFileSpec& file, bool& bFound);
   LT_STATUS readWorldFile(const LTFileSpec *file,
                           LTIOStreamInf *stream,
                           bool &foundWorldFile);
private:
   bool m_useWorldFile;

   // nope
   LTIGeoImageReader(LTIGeoImageReader&);
   LTIGeoImageReader& operator=(const LTIGeoImageReader&);
};


LT_END_NAMESPACE(LizardTech)

#if defined(LT_COMPILER_MS)
	#pragma warning(pop)
#endif

#endif // LTI_GEOIMAGEREADER_H
