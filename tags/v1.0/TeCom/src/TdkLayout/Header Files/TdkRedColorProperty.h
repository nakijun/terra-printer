/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkRedColorProperty.h
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

#ifndef __TDK_COLOR_RED_PROPERTY_H
#define __TDK_COLOR_RED_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkRedColorProperty
/*! Class to represent the red color property
*/
class TdkRedColorProperty : public TdkAbstractProperty
{
protected:
	unsigned char		_value;			//!< color value
public :

	//! \brief TdkRedColorProperty
	/*! Constructor
		\param	newVale		new red color value
	*/
	TdkRedColorProperty(const unsigned char &newVal=0);

	//! \brief ~TdkRedColorProperty
	/*!	Destructor
	*/
	virtual ~TdkRedColorProperty();

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
		\param		other		other TdkRedColorProperty object
		\return		returns the object with same values that old object
	*/
	TdkRedColorProperty& operator=(const TdkRedColorProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkRedColorProperty& operator=(const TdkAbstractProperty &other);
};

#endif






