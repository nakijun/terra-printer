/* TerraLib Components - TeCOM
* 
* @(#) TdkViewNameProperty.h
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

#ifndef __TDK_VIEW_NAME_PROPERTY_H
#define __TDK_VIEW_NAME_PROPERTY_H


#include<TdkAbstractProperty.h>
#include <string>

using namespace std;

//! \class TdkViewNameProperty
/*! Class to manipulate the
	view name
*/
class TdkViewNameProperty : public TdkAbstractProperty
{
protected:
	std::string		_viewName;			//!< view name used to draw the geographics data
public:

	//! \brief constructor
	TdkViewNameProperty(const std::string &value="");

	//! \brief destructor
	~TdkViewNameProperty();

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
		\param		other		other TdkViewNameProperty object
		\return		returns the object with same values that old object
	*/
	TdkViewNameProperty& operator=(const TdkViewNameProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkViewNameProperty& operator=(const TdkAbstractProperty &other);
};


#endif
