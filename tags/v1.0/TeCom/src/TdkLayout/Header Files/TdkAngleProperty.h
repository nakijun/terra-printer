/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkAngleProperty.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/08/20 20:45:30 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_ANGLE_PROPERTY_H
#define __TDK_ANGLE_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkAngleProperty
/*! Class to represent the angle property
*/
class TdkAngleProperty : public TdkAbstractProperty
{
protected:
	double		_value;			//!< angle value
public :

	//! \brief TdkAngleProperty
	/*! Constructor
		\param	newVale		new angle value
	*/
	TdkAngleProperty(const double &newVal=0.0);

	//! \brief ~TdkAngleProperty
	/*!	Destructor
	*/
	virtual ~TdkAngleProperty();

	//! \brief setValue
	/*! Method to set the new value to
		angle property
		\param		newVal		new angle value
	*/
	virtual void setValue(const double &newVal);

	//! \brief getValue
	/*! Method to return the angle value
		\return		returns the angle value
	*/
	virtual double getValue();

	//! \brief getValue
	/*! Method to return the angle value
		by reference
	*/
	virtual void getValue(double &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAngleProperty object
		\return		returns the object with same values that old object
	*/
	TdkAngleProperty& operator=(const TdkAngleProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkAngleProperty& operator=(const TdkAbstractProperty &other);
};

#endif

