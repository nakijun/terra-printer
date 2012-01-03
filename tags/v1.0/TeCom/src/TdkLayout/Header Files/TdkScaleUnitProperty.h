/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkScaleUnitProperty.h
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
#ifndef __TDK_SCALE_UNIT_PROPERTY_H
#define __TDK_SCALE_UNIT_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkScaleUnitProperty
/*! Class to manipulate the scale unit property of object
*/
class TdkScaleUnitProperty : public TdkAbstractProperty
{
public :
	enum Unit
	{
		meters=0,			kilometers=1
	};
protected :
	Unit			_value;
public :

	//! \brief TdkScaleUnitProperty
	/*! Constructor
		\param		newVal		new width value
	*/
	TdkScaleUnitProperty(const Unit &newVal=meters);

	//! \brief Destructor
	virtual ~TdkScaleUnitProperty();

	//! \brief setValue
	/*! Method to set the new value
		to width property
		\param	newVal		new width value
	*/
	virtual void setValue(const Unit &newVal);
	
	//! \brief getValue
	/*! Method to return the scale unit
		\return returns the scale unit value of object
	*/
	virtual Unit getValue();

	//! \brief getValue
	/*! Method to return the scale unit
		by reference
	*/
	virtual void getValue(double &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkScaleUnitProperty object
		\return		returns the object with same values that old object
	*/
	TdkScaleUnitProperty& operator=(const TdkScaleUnitProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkScaleUnitProperty& operator=(const TdkAbstractProperty &other);
};


#endif
