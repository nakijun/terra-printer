/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkMapWorld_y1_Property.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2011/07/08 14:34:27 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Greg�rio

#ifndef __TDK_MAP_WORLD_Y1_PROPERTY_H
#define __TDK_MAP_WORLD_Y1_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkMapWorld_y1_Property
/*! Class to represent the initial position of wolrd map
*/
class TdkMapWorld_y1_Property : public TdkAbstractProperty
{
protected:
	double		*_value;	
	bool		*_redraw;
public :

	//! \brief TdkMapWorld_y1_Property
	/*! Constructor
		\param	newVale		new scale value
	*/
	TdkMapWorld_y1_Property(double *newVal, bool *redraw);

	//! \brief ~TdkMapWorld_y1_Property
	/*!	Destructor
	*/
	virtual ~TdkMapWorld_y1_Property();

	//! \brief setValue
	/*! Method to set the new value to
		scale property
		\param		newVal		new angle value
	*/
	virtual void setValue(const double &newVal);

	//! \brief getValue
	/*! Method to return the scale value
		\return		returns the scale value
	*/
	virtual double getValue();

	//! \brief getValue
	/*! Method to return the scale value
		by reference
	*/
	virtual void getValue(double &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAngleProperty object
		\return		returns the object with same values that old object
	*/
	TdkMapWorld_y1_Property& operator=(const TdkMapWorld_y1_Property &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkMapWorld_y1_Property& operator=(const TdkAbstractProperty &other);
};

#endif

