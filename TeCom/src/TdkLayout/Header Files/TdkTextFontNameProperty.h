/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkTextFontNameProperty.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/08/23 13:21:20 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_TEXT_FONT_NAME_PROPERTY_H
#define __TDK_TEXT_FONT_NAME_PROPERTY_H

#include<TdkAbstractProperty.h>
#include <string>

using namespace std;

//! \class TdkTextFontNameProperty
/*! Class to manipulate the font name property
*/
class	TdkTextFontNameProperty : public TdkAbstractProperty
{
protected:

	std::string		_value;		//! string font name

public :

	//! \brief TdkTextFontNameProperty
	/*! Constructor
		\param		newVal		new string font name
	*/
	TdkTextFontNameProperty(const std::string &newVal="Verdana");

	//! \brief Destructor
	virtual ~TdkTextFontNameProperty();

	//! \brief setValue
	/*! Method to set the font name value
		\param	newVal		new string font name
	*/
	virtual void setValue(const std::string &newVal);

	//! \brief getValue
	/*! Method to return the string font name
		\return		returns the string font name
	*/
	virtual std::string getValue();

	//! \brief getValue
	/*! Method to return the string font name
		by reference
	*/
	virtual void getValue(std::string &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkTextFontNameProperty object
		\return		returns the object with same values that old object
	*/
	TdkTextFontNameProperty& operator=(const TdkTextFontNameProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkTextFontNameProperty& operator=(const TdkAbstractProperty &other);
};


#endif
