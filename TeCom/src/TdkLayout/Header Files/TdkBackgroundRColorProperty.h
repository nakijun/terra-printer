/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkBackgroundRColorProperty.h
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

#ifndef __TDK_BACKGROUND_COLOR_R_PROPERTY_H
#define __TDK_BACKGROUND_COLOR_R_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkBackgroundRColorProperty
/*! Class to represent the background color property
*/
class TdkBackgroundRColorProperty : public TdkAbstractProperty
{
protected:
	unsigned char		_value;			//!< color value
public :

	//! \brief TdkBackgroundRColorProperty
	/*! Constructor
		\param	newVale		new fore color value
	*/
	TdkBackgroundRColorProperty(const unsigned char &newVal=0);

	//! \brief ~TdkBackgroundRColorProperty
	/*!	Destructor
	*/
	virtual ~TdkBackgroundRColorProperty();

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
	/*! Method to return the fore color value by reference
	*/
	virtual void getValue(unsigned char &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkBackgroundRColorProperty object
		\return		returns the object with same values that old object
	*/
	TdkBackgroundRColorProperty& operator=(const TdkBackgroundRColorProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkBackgroundRColorProperty& operator=(const TdkAbstractProperty &other);
};

#endif





