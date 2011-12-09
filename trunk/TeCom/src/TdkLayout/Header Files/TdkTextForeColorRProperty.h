
/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkTextForeColorRProperty.h
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

#ifndef __TDK_TEXT_FORE_COLOR_R_PROPERTY_H
#define __TDK_TEXT_FORE_COLOR_R_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkTextForeColorRProperty
/*! Class to represent the angle property
*/
class TdkTextForeColorRProperty : public TdkAbstractProperty
{
protected:
	unsigned char		_value;			//!< color value
public :

	//! \brief TdkTextForeColorRProperty
	/*! Constructor
		\param	newVale		new fore color value
	*/
	TdkTextForeColorRProperty(const unsigned char &newVal=0);

	//! \brief ~TdkTextForeColorRProperty
	/*!	Destructor
	*/
	virtual ~TdkTextForeColorRProperty();

	//! \brief setValue
	/*! Method to set the new value to
		fore color property
		\param		newVal		new angle value
	*/
	virtual void setValue(const unsigned char &newVal);

	//! \brief getValue
	/*! Method to return the fore color value
		\return		returns the fore color value
	*/
	virtual unsigned char getValue();

	//! \brief getValue
	/*! Method to return the fore color value
		by reference
	*/
	virtual void getValue(unsigned char &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkTextForeColorRProperty object
		\return		returns the object with same values that old object
	*/
	TdkTextForeColorRProperty& operator=(const TdkTextForeColorRProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkTextForeColorRProperty& operator=(const TdkAbstractProperty &other);
};

#endif





