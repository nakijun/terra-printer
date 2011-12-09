/* TerraLib Components - TeCOM
* 
* @(#) TdkImageFileNameProperty.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/08/23 13:21:19 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_IMAGE_FILE_NAME_PROPERTY_H
#define __TDK_IMAGE_FILE_NAME_PROPERTY_H

#include<TdkAbstractProperty.h>
#include <string>

using namespace std;

//! \class TdkImageFileNameProperty
/*! Class to manipulate the image file name
*/
class	TdkImageFileNameProperty : public TdkAbstractProperty
{
protected:

	std::string		_value;		//!< fileName

public :

	//! \brief TdkImageFileNameProperty
	/*! Constructor
		\param	newVal		new text value
	*/
	TdkImageFileNameProperty(const std::string &newVal="");

	//! \brief Destructor
	virtual ~TdkImageFileNameProperty();

	//! \brief setValue
	/*! Method to set the image file name
		\param	newVal	new text value
	*/
	virtual void setValue(const std::string &newVal);

	//! \brief getValue
	/*! Method to return the image file name
		\return returns the image file name
	*/
	virtual std::string getValue();

	//! \brief getValue
	/*! Method to return the image file name
		by file name
	*/
	virtual void getValue(std::string &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkImageFileNameProperty object
		\return		returns the object with same values that old object
	*/
	TdkImageFileNameProperty& operator=(const TdkImageFileNameProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkImageFileNameProperty& operator=(const TdkAbstractProperty &other);
};


#endif
