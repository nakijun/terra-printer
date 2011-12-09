/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkBackgroundBColorProperty.h
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

#ifndef __TDK_BACKGROUND_COLOR_B_PROPERTY_H
#define __TDK_BACKGROUND_COLOR_B_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkBackgroundBColorProperty
/*! Class to represent the background color property
*/
class TdkBackgroundBColorProperty : public TdkAbstractProperty
{
protected:
	unsigned char		_value;			//!< color value
public :

	//! \brief TdkBackgroundBColorProperty
	/*! Constructor
		\param	newVale		new fore color value
	*/
	TdkBackgroundBColorProperty(const unsigned char &newVal=0);

	//! \brief ~TdkBackgroundBColorProperty
	/*!	Destructor
	*/
	virtual ~TdkBackgroundBColorProperty();

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
		\param		other		other TdkBackgroundBColorProperty object
		\return		returns the object with same values that old object
	*/
	TdkBackgroundBColorProperty& operator=(const TdkBackgroundBColorProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkBackgroundBColorProperty& operator=(const TdkAbstractProperty &other);
};

#endif





