/* $Id: NITFImageManager.h 5124 2006-10-27 11:40:40Z lubia $ */
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

#ifndef NITFIMAGEMANAGER_H
#define NITFIMAGEMANAGER_H

// lt_lib_base
#include "lt_base.h"

// lt_lib_mrsid_core
#include "lti_geoImageReader.h"

LT_BEGIN_NAMESPACE(LizardTech)

class LTFileSpec;
class LTIOStreamInf;

class NITFImageReader;

class NITFFileHeader;
class NITFImageSegment;
class NITFGraphicSegment;
class NITFLabelSegment;
class NITFTextSegment;
class NITFDataSegment;
class NITFResSegment;
class NITFFileMetadata;
class NITFSecurityMetadata;

/**
 * class for reading an NITF file
 *
 * This class provides support for reading an NITF file, containing
 * one or more image segments.
 *
 * This class is used in conjunction with the NITFReader class.
 *
 * THIS CLASS SUBJECT TO SIGNIFICANT CHANGE IN SUBSEQUENT RELEASES.
 */
class NITFImageManager
{
public:
   /**
    * constructor
    *
    * Creates an NITFImageManager object from the given file.
    *
    * @param fileSpec  the NITF file to be opened
    * @param obsolete  (not used)
    */
   NITFImageManager(const LTFileSpec& fileSpec, bool obsolete=true);

   /**
    * destructor
    */
   ~NITFImageManager();

   /**
    * initialization
    */
   LT_STATUS initialize();

   /**
    * creates a reader for a single segment
    *
    * This function is used to create an NITFImageReader for a 
    * single given image segment, specified by number.
    *
    * The \a reader is allocated and initialized by this function,
    * but the caller has ownership of the object.
    * 
    * @param reader  the created segment reader
    * @param idx     index of the image segment
    * @param useWorldFile set to true to allow world file to correct geo position
    * @return status code
    */
   LT_STATUS createReader(NITFImageReader*& reader, lt_uint32 idx, bool useWorldFile=true);

   /**
    * creates a reader for all image segments
    *
    * This function is used to create an NITFImageReader for all
    * the image segments; they are presented in the form of a
    * standard SDK image mosaic.
    *
    * The \a stage is allocated and initialized by this function,
    * but the caller has ownership of the object.  Note that the 
    * \a stage is an LTIImageStage and not an NITFImageReader, as in
    * the first form of the createReader() function.
    * 
    * @param stage   the created segment stage
    * @return status code
    */
   LT_STATUS createReader(LTIImageStage*& stage);   // makes mosaic

   // not for general use
   void giveReaderOwnership(NITFImageReader* dummy=0);

   /**
    * COMRAT compliance control
    *
    * This function is used to control whether or not the COMRAT
    * field is to be read.  The 2500C specification requires
    * this field be present; the 2500B Note 2 specification does
    * not.  This function is used to indicate which version
    * of the specification this file adheres to.
    *
    * The default is false, i.e. 2500C formatting.
    *
    * This function must be called prior to initialize().
    *
    * @param use2500B set to true for 2500B/Note2 formatting
    */
   void setCompat_2500B_N2(bool use2500B);

   /**
    * COMRAT compliance setting
    *
    * Returns the 2500B compatability setting; see the
    * setCompat_2500B_N2() function for details.
    *
    * @return true iff 200B / Note 2 formatting is being used
    */
   bool getCompat_2500B_N2() const;

   lt_int64 getFileSize() const;

   /**
    * returns FileHeader metadata
    */
   const NITFFileHeader* getFileHeader() const;

   /**
    * returns number of image segments
    */
   lt_uint32 getNumImageSegments() const;

   // not for general use
   const NITFImageSegment* getImageSegment(lt_uint32 num) const;

   /**
    * returns the IID1 field of the given image segment
    */
   const char* getImageSegmentIID1(lt_uint32 num) const;

   /**
    * returns the number of graphic segments
    */
   lt_uint32 getNumGraphicSegments() const;

   // not for general use
   const NITFGraphicSegment* getGraphicSegment(lt_uint32 num) const;

   /**
    * returns the number of graphic segments
    */
   lt_uint32 getNumLabelSegments() const;

   // not for general use
   const NITFLabelSegment* getLabelSegment(lt_uint32 num) const;

   /**
    * returns the number of graphic segments
    */
   lt_uint32 getNumTextSegments() const;

   // not for general use
   const NITFTextSegment* getTextSegment(lt_uint32 num) const;

   /**
    * returns the number of graphic segments
    */
   lt_uint32 getNumDataSegments() const;

   // not for general use
   const NITFDataSegment* getDataSegment(lt_uint32 num) const;

   /**
    * returns the number of graphic segments
    */
   lt_uint32 getNumResSegments() const;

   // not for general use
   const NITFResSegment* getResSegment(lt_uint32 num) const;

   /**
    * returns NITF version information
    */
   const char* getVersionString() const;

   LTFileSpec* getFileSpec() const;

   /**
    * returns the file-level metadata
    */
   const NITFFileMetadata* getFileMetadata() const;

   /**
    * returns file-level security metadata
    */
   const NITFSecurityMetadata* getSecurityMetadata() const;

private:
   LTFileSpec* m_fileSpec;
   LTIOStreamInf* m_stream;
   lt_int64 m_fileSize;
   NITFImageReader* m_readerWithOwnership;

   NITFFileHeader* m_fileHeader;
   NITFImageSegment** m_imageSegments;
   NITFGraphicSegment** m_graphicSegments;
   NITFLabelSegment** m_labelSegments;
   NITFTextSegment** m_textSegments;
   NITFDataSegment** m_dataSegments;
   NITFResSegment** m_resSegments;
   lt_uint32 m_numImageSegments;
   lt_uint32 m_numGraphicSegments;
   lt_uint32 m_numLabelSegments;
   lt_uint32 m_numTextSegments;
   lt_uint32 m_numDataSegments;
   lt_uint32 m_numResSegments;

   NITFImageReader** m_readers;
   lt_uint32 m_numReaders;

   char* m_versionString;

   bool m_compat_2500B_N2;

   // nope
   NITFImageManager(NITFImageManager&);
   NITFImageManager& operator=(const NITFImageManager&);
};

LT_END_NAMESPACE(LizardTech)

#endif // NITFIMAGEMANAGER_H
