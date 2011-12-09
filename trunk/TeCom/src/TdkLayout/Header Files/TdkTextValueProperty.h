/* TerraLib Components - TeCOM
* 
* @(#) TdkTextValueProperty.h
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

#ifndef __TDK_TEXT_VALUE_PROPERTY_H
#define __TDK_TEXT_VALUE_PROPERTY_H

#include<TdkAbstractProperty.h>
#include <string>

using namespace std;

//! \class TdkTextValueProperty
/*! Class to manipulate the text value
*/
class	TdkTextValueProperty : public TdkAbstractProperty
{
protected:

	std::string		_value;		//!< Text Value

public :

	//! \brief TdkTextValueProperty
	/*! Constructor
		\param	newVal		new text value
	*/
	TdkTextValueProperty(const std::string &newVal="");

	//! \brief Destructor
	virtual ~TdkTextValueProperty();

	//! \brief setValue
	/*! Method to set the text value
		\param	newVal	new text value
	*/
	virtual void setValue(const std::string &newVal);

	//! \brief getValue
	/*! Method to return the text value
		\return returns the text value
	*/
	virtual std::string getValue();

	
	//! \brief getValue
	/*! Method to return the text value
		by reference
	*/
	virtual void getValue(std::string &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkTextValueProperty object
		\return		returns the object with same values that old object
	*/
	TdkTextValueProperty& operator=(const TdkTextValueProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkTextValueProperty& operator=(const TdkAbstractProperty &other);
};


#endif
