
/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkGreenColorProperty.h
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

#ifndef __TDK_COLOR_GREEN_PROPERTY_H
#define __TDK_COLOR_GREEN_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkGreenColorProperty
/*! Class to represent the red color property
*/
class TdkGreenColorProperty : public TdkAbstractProperty
{
protected:
	unsigned char		_value;			//!< color value
public :

	//! \brief TdkGreenColorProperty
	/*! Constructor
		\param	newVale		new red color value
	*/
	TdkGreenColorProperty(const unsigned char &newVal=0);

	//! \brief ~TdkGreenColorProperty
	/*!	Destructor
	*/
	virtual ~TdkGreenColorProperty();

	//! \brief setValue
	/*! Method to set the new value to
		red color property
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
		\param		other		other TdkGreenColorProperty object
		\return		returns the object with same values that old object
	*/
	TdkGreenColorProperty& operator=(const TdkGreenColorProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkGreenColorProperty& operator=(const TdkAbstractProperty &other);
};

#endif






