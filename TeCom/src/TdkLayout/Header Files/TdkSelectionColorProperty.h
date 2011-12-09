/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkSelectionColorProperty.h
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

#ifndef __TDK_SELECTION_COLOR_PROPERTY_H
#define __TDK_SELECTION_COLOR_PROPERTY_H

#include <TdkAbstractProperty.h>
#include <TeVisual.h>


//! \class TdkSelectionColorProperty
/*! Class to represent the rgb color
*/
class TdkSelectionColorProperty : public TdkAbstractProperty
{
protected:
	double		_value;			//!< rgb color value
	bool		*_redraw;		//!< pointer to do redraw
public :

	//! \brief TdkSelectionColorProperty
	/*! Constructor
		\param	newVale		new angle value
	*/
	TdkSelectionColorProperty(bool *redraw, const double &newVal=0.0);

	//! \brief ~TdkAngleProperty
	/*!	Destructor
	*/
	virtual ~TdkSelectionColorProperty();

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
		\param		other		other TdkSelectionColorProperty object
		\return		returns the object with same values that old object
	*/
	TdkSelectionColorProperty& operator=(const TdkSelectionColorProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkSelectionColorProperty& operator=(const TdkAbstractProperty &other);

	//! \brief getColor
	/*! Method to return the terralib color
	*/
	 TeColor getColor();
};

#endif

