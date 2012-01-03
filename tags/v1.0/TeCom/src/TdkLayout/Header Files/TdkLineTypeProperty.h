/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLineTypeProperty.h
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

#ifndef __TDK_LINE_TYPE_PROPERTY_H
#define __TDK_LINE_TYPE_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkLineTypeProperty
/*! Class to represent the rectangle border type property
*/
class TdkLineTypeProperty : public TdkAbstractProperty
{
protected:
	short		_value;			//!< rectangle border type value
public :

	//! \brief TdkLineTypeProperty
	/*! Constructor
		\param	newVale		new rectangle border type value
	*/
	TdkLineTypeProperty(const short &newVal=0.0);

	//! \brief ~TdkLineTypeProperty
	/*!	Destructor
	*/
	virtual ~TdkLineTypeProperty();

	//! \brief setValue
	/*! Method to set the new value to
		rectangle border type property
		\param		newVal		new angle value
	*/
	virtual void setValue(const short &newVal);

	//! \brief getValue
	/*! Method to return the rectangle border value
		\return		returns the angle value
	*/
	virtual short getValue();

	//! \brief getValue
	/*! Method to return the rectangle border value
		by reference
	*/
	virtual void getValue(double &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkLineTypeProperty object
		\return		returns the object with same values that old object
	*/
	TdkLineTypeProperty& operator=(const TdkLineTypeProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkLineTypeProperty& operator=(const TdkAbstractProperty &other);
};

#endif

