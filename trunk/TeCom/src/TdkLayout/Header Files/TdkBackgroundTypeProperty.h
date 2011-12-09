
/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkBackgroundTypeProperty.h
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

#ifndef __TDK_BACKGROUND_TYPE_PROPERTY_H
#define __TDK_BACKGROUND_TYPE_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkBackgroundTypeProperty
/*! Class to represent the rectangle background type property
*/
class TdkBackgroundTypeProperty : public TdkAbstractProperty
{
protected:
	short		_value;			//!< rectangle background type value
public :

	//! \brief TdkBackgroundTypeProperty
	/*! Constructor
		\param	newVale		new rectangle background type value
	*/
	TdkBackgroundTypeProperty(const short &newVal=0.0);

	//! \brief ~TdkBackgroundTypeProperty
	/*!	Destructor
	*/
	virtual ~TdkBackgroundTypeProperty();

	//! \brief setValue
	/*! Method to set the new value to
		rectangle background type property
		\param		newVal		new angle value
	*/
	virtual void setValue(const short &newVal);

	//! \brief getValue
	/*! Method to return the rectangle background value
		\return		returns the angle value
	*/
	virtual short getValue();

	//! \brief getValue
	/*! Method to return the rectangle background value by reference
	*/
	virtual void getValue(double &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkBackgroundTypeProperty object
		\return		returns the object with same values that old object
	*/
	TdkBackgroundTypeProperty& operator=(const TdkBackgroundTypeProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkBackgroundTypeProperty& operator=(const TdkAbstractProperty &other);
};

#endif

