/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkBackgroundGColorProperty.h
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
// Elaborated by Rui Mauricio Greg�rio

#ifndef __TDK_BACKGROUND_COLOR_G_PROPERTY_H
#define __TDK_BACKGROUND_COLOR_G_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkBackgroundGColorProperty
/*! Class to represent the background color property
*/
class TdkBackgroundGColorProperty : public TdkAbstractProperty
{
protected:
	unsigned char		_value;			//!< color value
public :

	//! \brief TdkBackgroundGColorProperty
	/*! Constructor
		\param	newVale		new fore color value
	*/
	TdkBackgroundGColorProperty(const unsigned char &newVal=0);

	//! \brief ~TdkBackgroundGColorProperty
	/*!	Destructor
	*/
	virtual ~TdkBackgroundGColorProperty();

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
		\param		other		other TdkBackgroundGColorProperty object
		\return		returns the object with same values that old object
	*/
	TdkBackgroundGColorProperty& operator=(const TdkBackgroundGColorProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkBackgroundGColorProperty& operator=(const TdkAbstractProperty &other);
};

#endif





