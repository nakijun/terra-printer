

/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkBlueColorProperty.h
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

#ifndef __TDK_COLOR_BLUE_PROPERTY_H
#define __TDK_COLOR_BLUE_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkBlueColorProperty
/*! Class to represent the blue color property
*/
class TdkBlueColorProperty : public TdkAbstractProperty
{
protected:
	unsigned char		_value;			//!< color value
public :

	//! \brief TdkBlueColorProperty
	/*! Constructor
		\param	newVale		new blue color value
	*/
	TdkBlueColorProperty(const unsigned char &newVal=0);

	//! \brief ~TdkBlueColorProperty
	/*!	Destructor
	*/
	virtual ~TdkBlueColorProperty();

	//! \brief setValue
	/*! Method to set the new value to
		blue color property
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
		\param		other		other TdkBlueColorProperty object
		\return		returns the object with same values that old object
	*/
	TdkBlueColorProperty& operator=(const TdkBlueColorProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkBlueColorProperty& operator=(const TdkAbstractProperty &other);
};

#endif






