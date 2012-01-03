/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) tdkAbstractImage.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/07/17 11:09:56 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_ABSTRACT_IMAGE_H
#define __TDK_ABSTRACT_IMAGE_H

#include <iostream>

using namespace std;

//! \class tdkAbstractImage
/*! Class to Images 
	manipulation
*/
class TdkAbstractImage
{
protected :
	
	std::string		_fileName;		//!< File Name String

public :
	
	TdkAbstractImage();

	virtual ~TdkAbstractImage();

	//!	\brief	setHeight
	/*! Method to set the height image
		\param	value		height value
	*/
	virtual void setHeight(const double &value) = 0;

	//! \brief setWidth
	/*! Method to set the width image
		\param	value	width value
	*/
	virtual void setWidth(const double &value) = 0;

	//! \brief getHeight
	/*! Abstract method to return the image's height
		\return	returns the height value
	*/
	virtual double getHeight() = 0;

	//! \brief getWidth
	/*! Abstract method to return the image's width
		\return	returns the width value
	*/
	virtual double getWidth() = 0;

	//! \brief save
	/*! Method to save the image object to file
		\param fileName	file name
		\return returns true whether sucess
	*/
	virtual bool save(const std::string &fileName) = 0;

	//! \brief Clear
	/*! Method to clear image from memory
	*/
	virtual void clear() = 0;

	//! \brief setFileName
	/*! Method to set the image's file name
		\param	fileName	String file name
	*/
	virtual void setFileName(const std::string &fileName);

	//! \brief getFileName
	/*! Method to returns a string that represents the
		image file name
		\param	returns the file name string
	*/
	virtual std::string getFileName();

};

#endif

