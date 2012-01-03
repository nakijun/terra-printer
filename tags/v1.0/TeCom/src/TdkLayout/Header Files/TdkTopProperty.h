/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkTopProperty.h
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
#ifndef __TDK_TOP_PROPERTY_H
#define __TDK_TOP_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkTopProperty
/*! Class to manipulate the top property of object
*/
class TdkTopProperty : public TdkAbstractProperty
{
public:

	double		*_value;			//!< pointer to access the y1 _boundingBox
	double		*_bottomValue;		//!< pointer to access the y2 _boundingBox

public :

	//! \brief TdkTopProperty Constructor
	TdkTopProperty();

	//! \brief Destructor
	virtual ~TdkTopProperty();

	//! \brief setValue
	/*! Method to set the new top value to object
		\param	newVal		new top value
	*/
	virtual void setValue(const double &newVal);

	//! \brief getValue
	/*! Method to return the top value
		\return	returns the double value of top property
	*/
	virtual double getValue();

	//! \brief getValue
	/*! Method to return the top value
		by reference
	*/
	virtual void getValue(double &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkTopProperty object
		\return		returns the object with same values that old object
	*/
	TdkTopProperty& operator=(const TdkTopProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkTopProperty& operator=(const TdkAbstractProperty &other);
};


#endif
