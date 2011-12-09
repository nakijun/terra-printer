/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkGdiImage.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/09/10 18:28:45 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_GDI_IMAGE_H
#define __TDK_GDI_IMAGE_H

#include <TdkAbstractImage.h>
#include <windows.h>
#include <gdiplus.h>

class Bitmap;

using namespace Gdiplus;

class TdkGdiImage : public TdkAbstractImage
{
public :
	enum Encoders
	{
		BMP,
		JPEG,
		PNG,
		GIF,
		TIF
	};
protected :

	Gdiplus::Bitmap*				_bitMap;						//!< Image as bitmap

protected :

	//! \brief GetEncoderClsid
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

	//! \brief getEncoder
	/*! Method to return the image encoder
		\param	encoder Enum enconder
		\return returns the CLSID encoder
	*/
	virtual CLSID*  getEncoder(const Encoders encoder);
public :

	//! \brief Constructor
	TdkGdiImage(const std::string &fileName);

	//! \brief Constructor
	TdkGdiImage(LPCTSTR pName, LPCTSTR pType, HMODULE hInst);

	//! \brief Destructor
	virtual ~TdkGdiImage();

	//!	\brief	setHeight
	/*! Method to set the height image
		\param	value		height value
	*/
	virtual void setHeight(const double &value);

	//! \brief setWidth
	/*! Method to set the width image
		\param	value	width value
	*/
	virtual void setWidth(const double &value);

	//! \brief getHeight
	/*! Abstract method to return the image's height
		\return	returns the height value
	*/
	virtual double getHeight();

	//! \brief getWidth
	/*! Abstract method to return the image's width
		\return	returns the width value
	*/
	virtual double getWidth();

	//! \brief save
	/*! Method to save the image object to file
		\param fileName	file name
		\return returns true whether sucess
	*/
	virtual bool save(const std::string &fileName);

	//! \brief getBitmap
	/*! Method to return the gdi plus
		bitmap pointer
		\param	returns the gdiplus bitmap
	*/
	virtual Gdiplus::Bitmap* getBitmap();

	//! \brief Clear
	/*! Method to clear image from memory
	*/
	virtual void clear();

	//! \brief setFileName
	/*! Method to set the image's file name
		\param	fileName	String file name
	*/
	virtual void setFileName(const std::string &fileName);

	//! \brief setAbstractFileName
	/*! Method to set the abstract file name
		\param	fileName	String file name
	*/
	virtual void setAbstractFileName(const std::string &fileName);

	//! \brief getIstream
	/*! Method to returns the image as unsigned char array
	*/
	virtual unsigned char * getIstream(unsigned long &size);

	//! \brief setIStream
	/*! Method to create a new image from unsigned char array
	*/
	virtual bool setIStream(unsigned char *value, const unsigned long &size);

	//! \brief clone
	/*! Clone image object
	*/
	virtual TdkGdiImage* clone();

};

#endif
