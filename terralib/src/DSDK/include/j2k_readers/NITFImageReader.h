/* $Id: NITFImageReader.h 5124 2006-10-27 11:40:40Z lubia $ */
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

#ifndef NITFIMAGEREADER_H
#define NITFIMAGEREADER_H

// lt_lib_base
#include "lt_base.h"

// lt_lib_mrsid_core
#include "lti_geoImageReader.h"

// local
#include "nitf_types.h"

LT_BEGIN_NAMESPACE(LizardTech)

class LTFileSpec;
class LTIOStreamInf;
class NITFFileHeader;
class NITFImageManager;
class NITFImageSegment;
class LTReusableBuffer;
class LTIReusableBSQBuffer;
class NITFImageSegmentMetadata;
class NITFSecurityMetadata;

/**
 * class for reading an NITF JPEG 2000 image segment
 *
 * This class provides support for reading an NITF
 * image segment.  NITFImageManager objects are not
 * to be created directly; the NITFImageManager class
 * contains a createReader() function for this purpose.
 *
 * THIS CLASS SUBJECT TO SIGNIFICANT CHANGE IN SUBSEQUENT RELEASES.
 */
class NITFImageReader : public LTIGeoImageReader
{
public:
   // do not call - access only via the Manager
   NITFImageReader(LTIOStreamInf* stream,
                   NITFImageManager& manager,
                   const NITFImageSegment& imageSegment,
                   bool useWorldFile);

   virtual ~NITFImageReader();
   virtual LT_STATUS initialize() = 0;

   /**
    * returns the IID1 field for the segment
    */
   const char* getIID1() const;

   virtual lt_int64 getPhysicalFileSize() const;

   // not for general use
   NITFImageManager& getManager() const;
   // not for general use
   void takeOwnershipOfManager();

   /**
    * returns the compression format of the segment
    */
   NITFFormat getFormat() const;

   /**
    * returns the pixel layout of the segment
    */
   NITFLayout getLayout() const;

   /**
    * returns true iff the image segment is in blocked form
    */
   bool isBlocked() const;

   /**
    * returns true iff block masking is used in the image segment
    */
   bool isMasked() const;

   /**
    * returns the index of this image segment 
    */
  int getSegmentNumber() const;

   /**
    * returns the image segment metadata object for this segment
    */
  const NITFImageSegmentMetadata* getImageMetadata() const;

   /**
    * returns the secuirty metadata object for this segment
    */
  const NITFSecurityMetadata* getSecurityMetadata() const;

  virtual LT_STATUS getDimsAtMag(double mag,
                                 lt_uint32& width,
                                 lt_uint32& height) const =0;
  virtual LT_STATUS projectPointAtMag(double upperLeft,
                                      double mag,
                                      double& newUpperLeft) const =0;
  virtual LT_STATUS projectDimAtMag(double dim,
                                    double mag,
                                    double& newDim) const =0;

protected:
   LT_STATUS initializeBase();

   LT_STATUS addUnderlyingMetadata(const LTIImageReader&);

   virtual LT_STATUS decodeStrip(LTISceneBuffer& stripBuffer, const LTIScene& stripScene) =0;
   virtual LT_STATUS decodeBegin(const LTIScene& scene) =0;
   virtual LT_STATUS decodeEnd() =0;
   
   NITFImageManager& m_manager;
   LTIOStreamInf* m_dataStream;
   bool m_ownsTheManager;

   const NITFFileHeader* m_fileHeader;
   const NITFImageSegment& m_imageSegment;

   bool m_useTheWorldFile;

   // blocked image support
   LTIScene computeBlockedScene(const LTIScene& scene) const;
   LT_STATUS copyIntoUserBuffer(const LTIScene& dstScene,
                                LTISceneBuffer& dstBuffer) const;
   bool activeSceneContains(const LTIScene& scene) const;
   void putBlockIntoBuffer_SEQ(LTISceneBuffer& cBuffer,
                               lt_uint8* buf,
                               lt_uint32 blockRow,
                               lt_uint32 blockCol,
                               lt_uint32 blockBand) const;
   void putBlockIntoBuffer_BLOCK(LTISceneBuffer& cBuffer,
                                 lt_uint8* buf,
                                 lt_uint32 blockRow,
                                 lt_uint32 blockCol) const;
   void putBlockIntoBuffer_PIXEL(LTISceneBuffer& cBuffer,
                               lt_uint8* buf,
                               lt_uint32 blockRow,
                               lt_uint32 blockCol) const;
   void putBlockIntoBuffer_ROW(LTISceneBuffer& cBuffer,
                               lt_uint8* buf,
                               lt_uint32 blockRow,
                               lt_uint32 blockCol) const;

   LTReusableBuffer* m_reusableBuffer;
   LTIScene* m_activeScene;
   LTISceneBuffer* m_activeSceneBuffer;
   LTIReusableBSQBuffer* m_activeReusableBuffer;

private:
   // nope
   NITFImageReader(NITFImageReader&);
   NITFImageReader& operator=(const NITFImageReader&);
};

LT_END_NAMESPACE(LizardTech)

#endif // NITFIMAGEREADER_H
