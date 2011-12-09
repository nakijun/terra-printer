/* $Id: tiffio.h 7870 2009-05-21 14:48:39Z castejon $ */

/*
 * Copyright (c) 1988-1997 Sam Leffler
 * Copyright (c) 1991-1997 Silicon Graphics, Inc.
 *
 * Permission to use, copy, modify, distribute, and sell this software and 
 * its documentation for any purpose is hereby granted without fee, provided
 * that (i) the above copyright notices and this permission notice appear in
 * all copies of the software and related documentation, and (ii) the names of
 * Sam Leffler and Silicon Graphics may not be used in any advertising or
 * publicity relating to the software without the specific, prior written
 * permission of Sam Leffler and Silicon Graphics.
 * 
 * THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY 
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  
 * 
 * IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
 * ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#ifndef _TIFFIO_
#define	_TIFFIO_

#include "geotiff.h"

/*
 * TIFF I/O Library Definitions.
 */
#include "tiff.h"
#include "tiffvers.h"

/*
 * TIFF is defined as an incomplete type to hide the
 * library's internal data structures from clients.
 */
typedef	struct tiff TIFF;

/*
 * The following typedefs define the intrinsic size of
 * data types used in the *exported* interfaces.  These
 * definitions depend on the proper definition of types
 * in tiff.h.  Note also that the varargs interface used
 * to pass tag types and values uses the types defined in
 * tiff.h directly.
 *
 * NB: ttag_t is unsigned int and not unsigned short because
 *     ANSI C requires that the type before the ellipsis be a
 *     promoted type (i.e. one of int, unsigned int, pointer,
 *     or double) and because we defined pseudo-tags that are
 *     outside the range of legal Aldus-assigned tags.
 * NB: tsize_t is int32 and not uint32 because some functions
 *     return -1.
 * NB: toff_t is not off_t for many reasons; TIFFs max out at
 *     32-bit file offsets being the most important, and to ensure
 *     that it is unsigned, rather than signed.
 */
typedef	uint32 ttag_t;		/* directory tag */
typedef	uint16 tdir_t;		/* directory index */
typedef	uint16 tsample_t;	/* sample number */
typedef	uint32 tstrip_t;	/* strip number */
typedef uint32 ttile_t;		/* tile number */
typedef	int32 tsize_t;		/* i/o size in bytes */
typedef	void* tdata_t;		/* image data ref */
typedef	uint32 toff_t;		/* file offset */

#if !defined(__WIN32__) && (defined(_WIN32) || defined(WIN32))
#define __WIN32__
#endif

/*
 * On windows you should define USE_WIN32_FILEIO if you are using tif_win32.c
 * or AVOID_WIN32_FILEIO if you are using something else (like tif_unix.c).
 *
 * By default tif_unix.c is assumed.
 */

#if defined(_WINDOWS) || defined(__WIN32__) || defined(_Windows)
#  if !defined(__CYGWIN) && !defined(AVOID_WIN32_FILEIO) && !defined(USE_WIN32_FILEIO)
#    define AVOID_WIN32_FILEIO
#  endif
#endif

#if defined(USE_WIN32_FILEIO)
# define VC_EXTRALEAN
# include <windows.h>
# ifdef __WIN32__
DECLARE_HANDLE(thandle_t);	/* Win32 file handle */
# else
typedef	HFILE thandle_t;	/* client data handle */
# endif /* __WIN32__ */
#else
typedef	void* thandle_t;	/* client data handle */
#endif /* USE_WIN32_FILEIO */

#ifndef NULL
# define NULL	(void *)0
#endif

/*
 * Flags to pass to TIFFPrintDirectory to control
 * printing of data structures that are potentially
 * very large.   Bit-or these flags to enable printing
 * multiple items.
 */
#define	TIFFPRINT_NONE		0x0		/* no extra info */
#define	TIFFPRINT_STRIPS	0x1		/* strips/tiles info */
#define	TIFFPRINT_CURVES	0x2		/* color/gray response curves */
#define	TIFFPRINT_COLORMAP	0x4		/* colormap */
#define	TIFFPRINT_JPEGQTABLES	0x100		/* JPEG Q matrices */
#define	TIFFPRINT_JPEGACTABLES	0x200		/* JPEG AC tables */
#define	TIFFPRINT_JPEGDCTABLES	0x200		/* JPEG DC tables */

/* 
 * Colour conversion stuff
 */

/* reference white */
#define D65_X0 (95.0470F)
#define D65_Y0 (100.0F)
#define D65_Z0 (108.8827F)

#define D50_X0 (96.4250F)
#define D50_Y0 (100.0F)
#define D50_Z0 (82.4680F)

/* Structure for holding information about a display device. */

typedef	unsigned char TIFFRGBValue;		/* 8-bit samples */

typedef struct {
	float d_mat[3][3]; 		/* XYZ -> luminance matrix */
	float d_YCR;			/* Light o/p for reference white */
	float d_YCG;
	float d_YCB;
	uint32 d_Vrwr;			/* Pixel values for ref. white */
	uint32 d_Vrwg;
	uint32 d_Vrwb;
	float d_Y0R;			/* Residual light for black pixel */
	float d_Y0G;
	float d_Y0B;
	float d_gammaR;			/* Gamma values for the three guns */
	float d_gammaG;
	float d_gammaB;
} TIFFDisplay;

typedef struct {				/* YCbCr->RGB support */
	TIFFRGBValue* clamptab;			/* range clamping table */
	int*	Cr_r_tab;
	int*	Cb_b_tab;
	int32*	Cr_g_tab;
	int32*	Cb_g_tab;
        int32*  Y_tab;
} TIFFYCbCrToRGB;

typedef struct {				/* CIE Lab 1976->RGB support */
	int	range;				/* Size of conversion table */
#define CIELABTORGB_TABLE_RANGE 1500
	float	rstep, gstep, bstep;
	float	X0, Y0, Z0;			/* Reference white point */
	TIFFDisplay display;
	float	Yr2r[CIELABTORGB_TABLE_RANGE + 1];  /* Conversion of Yr to r */
	float	Yg2g[CIELABTORGB_TABLE_RANGE + 1];  /* Conversion of Yg to g */
	float	Yb2b[CIELABTORGB_TABLE_RANGE + 1];  /* Conversion of Yb to b */
} TIFFCIELabToRGB;

/*
 * RGBA-style image support.
 */
typedef struct _TIFFRGBAImage TIFFRGBAImage;
/*
 * The image reading and conversion routines invoke
 * ``put routines'' to copy/image/whatever tiles of
 * raw image data.  A default set of routines are 
 * provided to convert/copy raw image data to 8-bit
 * packed ABGR format rasters.  Applications can supply
 * alternate routines that unpack the data into a
 * different format or, for example, unpack the data
 * and draw the unpacked raster on the display.
 */
typedef void (*tileContigRoutine)
    (TIFFRGBAImage*, uint32*, uint32, uint32, uint32, uint32, int32, int32,
	unsigned char*);
typedef void (*tileSeparateRoutine)
    (TIFFRGBAImage*, uint32*, uint32, uint32, uint32, uint32, int32, int32,
	unsigned char*, unsigned char*, unsigned char*, unsigned char*);
/*
 * RGBA-reader state.
 */
struct _TIFFRGBAImage {
	TIFF*	tif;				/* image handle */
	int	stoponerr;			/* stop on read error */
	int	isContig;			/* data is packed/separate */
	int	alpha;				/* type of alpha data present */
	uint32	width;				/* image width */
	uint32	height;				/* image height */
	uint16	bitspersample;			/* image bits/sample */
	uint16	samplesperpixel;		/* image samples/pixel */
	uint16	orientation;			/* image orientation */
	uint16	req_orientation;		/* requested orientation */
	uint16	photometric;			/* image photometric interp */
	uint16*	redcmap;			/* colormap pallete */
	uint16*	greencmap;
	uint16*	bluecmap;
						/* get image data routine */
	int	(*get)(TIFFRGBAImage*, uint32*, uint32, uint32);
	union {
	    void (*any)(TIFFRGBAImage*);
	    tileContigRoutine	contig;
	    tileSeparateRoutine	separate;
	} put;					/* put decoded strip/tile */
	TIFFRGBValue* Map;			/* sample mapping array */
	uint32** BWmap;				/* black&white map */
	uint32** PALmap;			/* palette image map */
	TIFFYCbCrToRGB* ycbcr;			/* YCbCr conversion state */
        TIFFCIELabToRGB* cielab;		/* CIE L*a*b conversion state */

        int	row_offset;
        int     col_offset;
};

/*
 * Macros for extracting components from the
 * packed ABGR form returned by TIFFReadRGBAImage.
 */
#define	TIFFGetR(abgr)	((abgr) & 0xff)
#define	TIFFGetG(abgr)	(((abgr) >> 8) & 0xff)
#define	TIFFGetB(abgr)	(((abgr) >> 16) & 0xff)
#define	TIFFGetA(abgr)	(((abgr) >> 24) & 0xff)

/*
 * A CODEC is a software package that implements decoding,
 * encoding, or decoding+encoding of a compression algorithm.
 * The library provides a collection of builtin codecs.
 * More codecs may be registered through calls to the library
 * and/or the builtin implementations may be overridden.
 */
typedef	int (*TIFFInitMethod)(TIFF*, int);
typedef struct {
	char*		name;
	uint16		scheme;
	TIFFInitMethod	init;
} TIFFCodec;

#include <stdio.h>
#include <stdarg.h>

/* share internal LogLuv conversion routines? */
#ifndef LOGLUV_PUBLIC
#define LOGLUV_PUBLIC		1
#endif

#if defined(c_plusplus) || defined(__cplusplus)
extern "C" {
#endif
typedef	void (*TIFFErrorHandler)(const char*, const char*, va_list);
typedef	void (*TIFFErrorHandlerExt)(thandle_t, const char*, const char*, va_list);
typedef	tsize_t (*TIFFReadWriteProc)(thandle_t, tdata_t, tsize_t);
typedef	toff_t (*TIFFSeekProc)(thandle_t, toff_t, int);
typedef	int (*TIFFCloseProc)(thandle_t);
typedef	toff_t (*TIFFSizeProc)(thandle_t);
typedef	int (*TIFFMapFileProc)(thandle_t, tdata_t*, toff_t*);
typedef	void (*TIFFUnmapFileProc)(thandle_t, tdata_t, toff_t);
typedef	void (*TIFFExtendProc)(TIFF*); 

extern	const char* TIFFGetVersion(void);

extern	const TIFFCodec* TIFFFindCODEC(uint16);
extern	TIFFCodec* TIFFRegisterCODEC(uint16, const char*, TIFFInitMethod);
extern	void CPL_DLL TIFFUnRegisterCODEC(TIFFCodec*);
extern  int CPL_DLL TIFFIsCODECConfigured(uint16);
extern	TIFFCodec* TIFFGetConfiguredCODECs(void);

/*
 * Auxiliary functions.
 */

extern	tdata_t CPL_DLL _TIFFmalloc(tsize_t);
extern	tdata_t CPL_DLL _TIFFrealloc(tdata_t, tsize_t);
extern	void CPL_DLL _TIFFmemset(tdata_t, int, tsize_t);
extern	void CPL_DLL _TIFFmemcpy(tdata_t, const tdata_t, tsize_t);
extern	int CPL_DLL _TIFFmemcmp(const tdata_t, const tdata_t, tsize_t);
extern	void CPL_DLL _TIFFfree(tdata_t);

/*
** Stuff, related to tag handling and creating custom tags.
*/
extern  int  TIFFGetTagListCount( TIFF * );
extern  ttag_t TIFFGetTagListEntry( TIFF *, int tag_index );
    
#define	TIFF_ANY	TIFF_NOTYPE	/* for field descriptor searching */
#define	TIFF_VARIABLE	-1		/* marker for variable length tags */
#define	TIFF_SPP	-2		/* marker for SamplesPerPixel tags */
#define	TIFF_VARIABLE2	-3		/* marker for uint32 var-length tags */

#define FIELD_CUSTOM    65    

typedef	struct {
	ttag_t	field_tag;		/* field's tag */
	short	field_readcount;	/* read count/TIFF_VARIABLE/TIFF_SPP */
	short	field_writecount;	/* write count/TIFF_VARIABLE */
	TIFFDataType field_type;	/* type of associated data */
        unsigned short field_bit;	/* bit in fieldsset bit vector */
	unsigned char field_oktochange;	/* if true, can change while writing */
	unsigned char field_passcount;	/* if true, pass dir count on set */
	char	*field_name;		/* ASCII name */
} TIFFFieldInfo;

typedef struct _TIFFTagValue {
    const TIFFFieldInfo  *info;
    int             count;
    void           *value;
} TIFFTagValue;

extern	void CPL_DLL TIFFMergeFieldInfo(TIFF*, const TIFFFieldInfo[], int);
extern	const TIFFFieldInfo* TIFFFindFieldInfo(TIFF*, ttag_t, TIFFDataType);
extern  const TIFFFieldInfo* TIFFFindFieldInfoByName(TIFF* , const char *,
						     TIFFDataType);
extern	const TIFFFieldInfo* TIFFFieldWithTag(TIFF*, ttag_t);
extern	const TIFFFieldInfo* TIFFFieldWithName(TIFF*, const char *);

typedef	int (*TIFFVSetMethod)(TIFF*, ttag_t, va_list);
typedef	int (*TIFFVGetMethod)(TIFF*, ttag_t, va_list);
typedef	void (*TIFFPrintMethod)(TIFF*, FILE*, long);
    
typedef struct {
    TIFFVSetMethod	vsetfield;	/* tag set routine */
    TIFFVGetMethod	vgetfield;	/* tag get routine */
    TIFFPrintMethod	printdir;	/* directory print routine */
} TIFFTagMethods;
        
extern  TIFFTagMethods CPL_DLL *TIFFAccessTagMethods( TIFF * );
extern  void CPL_DLL *TIFFGetClientInfo( TIFF *, const char * );
extern  void CPL_DLL TIFFSetClientInfo( TIFF *, void *, const char * );

extern	void CPL_DLL TIFFCleanup(TIFF*);
extern	void CPL_DLL TIFFClose(TIFF*);
extern	int CPL_DLL TIFFFlush(TIFF*);
extern	int CPL_DLL TIFFFlushData(TIFF*);
extern	int CPL_DLL TIFFGetField(TIFF*, ttag_t, ...);
extern	int CPL_DLL TIFFVGetField(TIFF*, ttag_t, va_list);
extern	int CPL_DLL TIFFGetFieldDefaulted(TIFF*, ttag_t, ...);
extern	int CPL_DLL TIFFVGetFieldDefaulted(TIFF*, ttag_t, va_list);
extern	int CPL_DLL TIFFReadDirectory(TIFF*);
extern	int CPL_DLL TIFFReadCustomDirectory(TIFF*, toff_t, const TIFFFieldInfo[],
				    size_t);
extern	int CPL_DLL TIFFReadEXIFDirectory(TIFF*, toff_t);
extern	tsize_t CPL_DLL TIFFScanlineSize(TIFF*);
extern	tsize_t CPL_DLL TIFFRasterScanlineSize(TIFF*);
extern	tsize_t CPL_DLL TIFFStripSize(TIFF*);
extern	tsize_t CPL_DLL TIFFRawStripSize(TIFF*, tstrip_t);
extern	tsize_t CPL_DLL TIFFVStripSize(TIFF*, uint32);
extern	tsize_t CPL_DLL TIFFTileRowSize(TIFF*);
extern	tsize_t CPL_DLL TIFFTileSize(TIFF*);
extern	tsize_t CPL_DLL TIFFVTileSize(TIFF*, uint32);
extern	uint32 CPL_DLL TIFFDefaultStripSize(TIFF*, uint32);
extern	void CPL_DLL TIFFDefaultTileSize(TIFF*, uint32*, uint32*);
extern	int CPL_DLL TIFFFileno(TIFF*);
extern  int CPL_DLL TIFFSetFileno(TIFF*, int);
extern  thandle_t CPL_DLL TIFFClientdata(TIFF*);
extern  thandle_t CPL_DLL TIFFSetClientdata(TIFF*, thandle_t);
extern	int CPL_DLL TIFFGetMode(TIFF*);
extern	int CPL_DLL TIFFSetMode(TIFF*, int);
extern	int CPL_DLL TIFFIsTiled(TIFF*);
extern	int CPL_DLL TIFFIsByteSwapped(TIFF*);
extern	int CPL_DLL TIFFIsUpSampled(TIFF*);
extern	int CPL_DLL TIFFIsMSB2LSB(TIFF*);
extern	int CPL_DLL TIFFIsBigEndian(TIFF*);
extern	TIFFReadWriteProc CPL_DLL TIFFGetReadProc(TIFF*);
extern	TIFFReadWriteProc CPL_DLL TIFFGetWriteProc(TIFF*);
extern	TIFFSeekProc CPL_DLL TIFFGetSeekProc(TIFF*);
extern	TIFFCloseProc CPL_DLL TIFFGetCloseProc(TIFF*);
extern	TIFFSizeProc CPL_DLL TIFFGetSizeProc(TIFF*);
extern	TIFFMapFileProc CPL_DLL TIFFGetMapFileProc(TIFF*);
extern	TIFFUnmapFileProc CPL_DLL TIFFGetUnmapFileProc(TIFF*);
extern	uint32 CPL_DLL TIFFCurrentRow(TIFF*);
extern	tdir_t CPL_DLL TIFFCurrentDirectory(TIFF*);
extern	tdir_t CPL_DLL TIFFNumberOfDirectories(TIFF*);
extern	uint32 CPL_DLL TIFFCurrentDirOffset(TIFF*);
extern	tstrip_t CPL_DLL TIFFCurrentStrip(TIFF*);
extern	ttile_t CPL_DLL TIFFCurrentTile(TIFF*);
extern	int CPL_DLL TIFFReadBufferSetup(TIFF*, tdata_t, tsize_t);
extern	int CPL_DLL TIFFWriteBufferSetup(TIFF*, tdata_t, tsize_t);
extern	int CPL_DLL TIFFSetupStrips(TIFF *);
extern  int CPL_DLL TIFFWriteCheck(TIFF*, int, const char *);
extern	void CPL_DLL TIFFFreeDirectory(TIFF*);
extern  int CPL_DLL TIFFCreateDirectory(TIFF*);
extern	int CPL_DLL TIFFLastDirectory(TIFF*);
extern	int CPL_DLL TIFFSetDirectory(TIFF*, tdir_t);
extern	int CPL_DLL TIFFSetSubDirectory(TIFF*, uint32);
extern	int CPL_DLL TIFFUnlinkDirectory(TIFF*, tdir_t);
extern	int CPL_DLL TIFFSetField(TIFF*, ttag_t, ...);
extern	int CPL_DLL TIFFVSetField(TIFF*, ttag_t, va_list);
extern	int CPL_DLL TIFFWriteDirectory(TIFF *);
extern	int CPL_DLL TIFFCheckpointDirectory(TIFF *);
extern	int CPL_DLL TIFFRewriteDirectory(TIFF *);
extern	int CPL_DLL TIFFReassignTagToIgnore(enum TIFFIgnoreSense, int);

#if defined(c_plusplus) || defined(__cplusplus)
extern	void CPL_DLL TIFFPrintDirectory(TIFF*, FILE*, long = 0);
extern	int CPL_DLL TIFFReadScanline(TIFF*, tdata_t, uint32, tsample_t = 0);
extern	int CPL_DLL TIFFWriteScanline(TIFF*, tdata_t, uint32, tsample_t = 0);
extern	int CPL_DLL TIFFReadRGBAImage(TIFF*, uint32, uint32, uint32*, int = 0);
extern	int CPL_DLL TIFFReadRGBAImageOriented(TIFF*, uint32, uint32, uint32*,
				      int = ORIENTATION_BOTLEFT, int = 0);
#else
extern	void CPL_DLL TIFFPrintDirectory(TIFF*, FILE*, long);
extern	int CPL_DLL TIFFReadScanline(TIFF*, tdata_t, uint32, tsample_t);
extern	int CPL_DLL TIFFWriteScanline(TIFF*, tdata_t, uint32, tsample_t);
extern	int CPL_DLL TIFFReadRGBAImage(TIFF*, uint32, uint32, uint32*, int);
extern	int CPL_DLL TIFFReadRGBAImageOriented(TIFF*, uint32, uint32, uint32*, int, int);
#endif

extern	int CPL_DLL TIFFReadRGBAStrip(TIFF*, tstrip_t, uint32 * );
extern	int CPL_DLL TIFFReadRGBATile(TIFF*, uint32, uint32, uint32 * );
extern	int CPL_DLL TIFFRGBAImageOK(TIFF*, char [1024]);
extern	int CPL_DLL TIFFRGBAImageBegin(TIFFRGBAImage*, TIFF*, int, char [1024]);
extern	int CPL_DLL TIFFRGBAImageGet(TIFFRGBAImage*, uint32*, uint32, uint32);
extern	void CPL_DLL TIFFRGBAImageEnd(TIFFRGBAImage*);
extern	TIFF* TIFFOpen(const char*, const char*);
# ifdef __WIN32__
extern	TIFF* TIFFOpenW(const wchar_t*, const char*);
# endif /* __WIN32__ */
extern	TIFF* TIFFFdOpen(int, const char*, const char*);
extern	TIFF* TIFFClientOpen(const char*, const char*,
	    thandle_t,
	    TIFFReadWriteProc, TIFFReadWriteProc,
	    TIFFSeekProc, TIFFCloseProc,
	    TIFFSizeProc,
	    TIFFMapFileProc, TIFFUnmapFileProc);
extern	const char* TIFFFileName(TIFF*);
extern	const char* TIFFSetFileName(TIFF*, const char *);
extern	void CPL_DLL TIFFError(const char*, const char*, ...);
extern	void CPL_DLL TIFFErrorExt(thandle_t, const char*, const char*, ...);
extern	void CPL_DLL TIFFWarning(const char*, const char*, ...);
extern	void CPL_DLL TIFFWarningExt(thandle_t, const char*, const char*, ...);
extern	TIFFErrorHandler CPL_DLL TIFFSetErrorHandler(TIFFErrorHandler);
extern	TIFFErrorHandlerExt CPL_DLL TIFFSetErrorHandlerExt(TIFFErrorHandlerExt);
extern	TIFFErrorHandler CPL_DLL TIFFSetWarningHandler(TIFFErrorHandler);
extern	TIFFErrorHandlerExt CPL_DLL TIFFSetWarningHandlerExt(TIFFErrorHandlerExt);
extern	TIFFExtendProc CPL_DLL TIFFSetTagExtender(TIFFExtendProc);
extern	ttile_t CPL_DLL TIFFComputeTile(TIFF*, uint32, uint32, uint32, tsample_t);
extern	int CPL_DLL TIFFCheckTile(TIFF*, uint32, uint32, uint32, tsample_t);
extern	ttile_t CPL_DLL TIFFNumberOfTiles(TIFF*);
extern	tsize_t CPL_DLL TIFFReadTile(TIFF*,
	    tdata_t, uint32, uint32, uint32, tsample_t);
extern	tsize_t CPL_DLL TIFFWriteTile(TIFF*,
	    tdata_t, uint32, uint32, uint32, tsample_t);
extern	tstrip_t CPL_DLL TIFFComputeStrip(TIFF*, uint32, tsample_t);
extern	tstrip_t CPL_DLL TIFFNumberOfStrips(TIFF*);
extern	tsize_t  CPL_DLL TIFFReadEncodedStrip(TIFF*, tstrip_t, tdata_t, tsize_t);
extern	tsize_t CPL_DLL TIFFReadRawStrip(TIFF*, tstrip_t, tdata_t, tsize_t);
extern	tsize_t CPL_DLL TIFFReadEncodedTile(TIFF*, ttile_t, tdata_t, tsize_t);
extern	tsize_t CPL_DLL TIFFReadRawTile(TIFF*, ttile_t, tdata_t, tsize_t);
extern	tsize_t CPL_DLL TIFFWriteEncodedStrip(TIFF*, tstrip_t, tdata_t, tsize_t);
extern	tsize_t CPL_DLL TIFFWriteRawStrip(TIFF*, tstrip_t, tdata_t, tsize_t);
extern	tsize_t CPL_DLL TIFFWriteEncodedTile(TIFF*, ttile_t, tdata_t, tsize_t);
extern	tsize_t CPL_DLL TIFFWriteRawTile(TIFF*, ttile_t, tdata_t, tsize_t);
extern	int CPL_DLL TIFFDataWidth(TIFFDataType);    /* table of tag datatype widths */
extern	void CPL_DLL TIFFSetWriteOffset(TIFF*, toff_t);
extern	void CPL_DLL TIFFSwabShort(uint16*);
extern	void CPL_DLL TIFFSwabLong(uint32*);
extern	void CPL_DLL TIFFSwabDouble(double*);
extern	void CPL_DLL TIFFSwabArrayOfShort(uint16*, unsigned long);
extern	void CPL_DLL TIFFSwabArrayOfTriples(uint8*, unsigned long);
extern	void CPL_DLL TIFFSwabArrayOfLong(uint32*, unsigned long);
extern	void CPL_DLL TIFFSwabArrayOfDouble(double*, unsigned long);
extern	void CPL_DLL TIFFReverseBits(unsigned char *, unsigned long);
extern	const unsigned char* TIFFGetBitRevTable(int);

#ifdef LOGLUV_PUBLIC
#define U_NEU		0.210526316
#define V_NEU		0.473684211
#define UVSCALE		410.
extern	double LogL16toY(int);
extern	double LogL10toY(int);
extern	void XYZtoRGB24(float*, uint8*);
extern	int uv_decode(double*, double*, int);
extern	void LogLuv24toXYZ(uint32, float*);
extern	void LogLuv32toXYZ(uint32, float*);
#if defined(c_plusplus) || defined(__cplusplus)
extern	int LogL16fromY(double, int = SGILOGENCODE_NODITHER);
extern	int LogL10fromY(double, int = SGILOGENCODE_NODITHER);
extern	int uv_encode(double, double, int = SGILOGENCODE_NODITHER);
extern	uint32 LogLuv24fromXYZ(float*, int = SGILOGENCODE_NODITHER);
extern	uint32 LogLuv32fromXYZ(float*, int = SGILOGENCODE_NODITHER);
#else
extern	int LogL16fromY(double, int);
extern	int LogL10fromY(double, int);
extern	int uv_encode(double, double, int);
extern	uint32 LogLuv24fromXYZ(float*, int);
extern	uint32 LogLuv32fromXYZ(float*, int);
#endif
#endif /* LOGLUV_PUBLIC */
    
extern int CPL_DLL TIFFCIELabToRGBInit(TIFFCIELabToRGB*, TIFFDisplay *, float*);
extern void CPL_DLL TIFFCIELabToXYZ(TIFFCIELabToRGB *, uint32, int32, int32,
			    float *, float *, float *);
extern void CPL_DLL TIFFXYZToRGB(TIFFCIELabToRGB *, float, float, float,
			 uint32 *, uint32 *, uint32 *);

extern int CPL_DLL TIFFYCbCrToRGBInit(TIFFYCbCrToRGB*, float*, float*);
extern void CPL_DLL TIFFYCbCrtoRGB(TIFFYCbCrToRGB *, uint32, int32, int32,
			   uint32 *, uint32 *, uint32 *);

#if defined(c_plusplus) || defined(__cplusplus)
}
#endif

#endif /* _TIFFIO_ */

/* vim: set ts=8 sts=8 sw=8 noet: */
