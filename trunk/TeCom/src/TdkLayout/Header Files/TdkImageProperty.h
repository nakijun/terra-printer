/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkImageProperty.h
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

#ifndef __TDK_IMAGE_PROPERTY_H
#define __TDK_IMAGE_PROPERTY_H

#include <TdkAbstractProperty.h>

class TdkGdiImage;

//! \class TdkImageProperty
/*! Class to represent the image property
*/
class TdkImageProperty : public TdkAbstractProperty
{
protected:
	TdkGdiImage		*_image;			//!< image value
public :

	//! \brief TdkImageProperty
	/*! Constructor
	*/
	TdkImageProperty();

	//! \brief ~TdkImageProperty
	/*!	Destructor
	*/
	virtual ~TdkImageProperty();

	//! \brief setValue
	/*! Method to set the new value to
		angle property
		\param		newVal		new raw image value
	*/
	virtual void setValue(const std::string &value);

	//! \brief getArrayValue
	/*! Method to return the array values
		\return		returns the array values
	*/
	virtual unsigned char *getArrayValue(unsigned long &size);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkImageProperty object
		\return		returns the object with same values that old object
	*/
	TdkImageProperty& operator=(const TdkImageProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkImageProperty& operator=(const TdkAbstractProperty &other);
public :

	//! \brief Create
	/*! Method to create a new tdk gdiImage
		\param	fileName	file Name
	*/
	virtual void Create(const std::string &fileName);

	//! \brief getImage
	/*! Returns the TdkGdiImage
	*/
	virtual TdkGdiImage* getImage();

	//! \brief Clear
	virtual void Clear();

	//! \brief getWidth
	/*! Returns the real width
	*/
	virtual double getWidth();

	//! \brief getHeight
	/*! Returns the real height
	*/
	virtual double getHeight();

	//! \brief getFileName
	/*! Returns the image file name
	*/
	virtual std::string getFileName();

	//! \brief setFileName
	/*! sets the image file name
	*/
	virtual void setFileName(const std::string &fileName);

	//! \brief setAbstractFileName
	/*! sets the abstract file name
	*/
	virtual void setAbstractFileName(const std::string &fileName);
};

#endif

