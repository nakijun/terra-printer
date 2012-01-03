/* TerraLib Components - TeCOM
* 
* @(#) TdkViewUserProperty.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/08/30 14:23:37 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_VIEW_USER_PROPERTY_H
#define __TDK_VIEW_USER_PROPERTY_H

#include<TdkAbstractProperty.h>
#include <string>

using namespace std;


class TdkViewUserProperty : public TdkAbstractProperty
{
protected :
	std::string			_userName;
public:

	//! \brief constructor
	TdkViewUserProperty(const std::string &value="");

	//! \brief Destructor
	~TdkViewUserProperty();

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
		\param		other		other TdkViewUserProperty object
		\return		returns the object with same values that old object
	*/
	TdkViewUserProperty& operator=(const TdkViewUserProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkViewUserProperty& operator=(const TdkAbstractProperty &other);

};


#endif

