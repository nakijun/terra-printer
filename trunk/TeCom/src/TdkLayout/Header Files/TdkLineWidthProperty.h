/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLineWidthProperty.h
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

#ifndef __TDK_LINE_WIDTH_PROPERTY_H
#define __TDK_LINE_WIDTH_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkLineWidthProperty
/*! Class to represent the rectangle border property
*/
class TdkLineWidthProperty : public TdkAbstractProperty
{
protected:
	double		_value;			//!< rectangle border value
public :

	//! \brief TdkLineWidthProperty
	/*! Constructor
		\param	newVale		new rectangle border value
	*/
	TdkLineWidthProperty(const double &newVal=0.0);

	//! \brief ~TdkLineWidthProperty
	/*!	Destructor
	*/
	virtual ~TdkLineWidthProperty();

	//! \brief setValue
	/*! Method to set the new value to
		rectangle border property
		\param		newVal		new angle value
	*/
	virtual void setValue(const double &newVal);

	//! \brief getValue
	/*! Method to return the rectangle border value
		\return		returns the angle value
	*/
	virtual double getValue();

	//! \brief getValue
	/*! Method to return the rectangle border value
		by reference
	*/
	virtual void getValue(double &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkLineWidthProperty object
		\return		returns the object with same values that old object
	*/
	TdkLineWidthProperty& operator=(const TdkLineWidthProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkLineWidthProperty& operator=(const TdkAbstractProperty &other);
};

#endif

