/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLeftProperty.h
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

#ifndef __TDK_LEFT_PROPERTY_H
#define __TDK_LEFT_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkLeftProperty
/*! Method to storage the left property
*/
class TdkLeftProperty : public TdkAbstractProperty
{
public:

	double		*_value;			//! pointer to access the x1 coordinate of _boundingbox
	double		*_rightValue;		//! pointer to access the x2 coordinate	of _boundingbox	

public :

	//! \brief Constructor
	TdkLeftProperty();

	//! \brief Destructor
	virtual ~TdkLeftProperty();

	//! \brief setValue
	/*! Method to set the new value
		to left property
		\param	newVal		new left value
	*/
	virtual void setValue(const double &newVal);

	//! \brief getValue
	/*! Method to return the left object value
		\return	returns the left value
	*/
	virtual double getValue();

	//! \brief getValue
	/*! Method to return the left object value
		by reference
	*/
	virtual void getValue(double &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkLeftProperty object
		\return		returns the object with same values that old object
	*/
	TdkLeftProperty& operator=(const TdkLeftProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkLeftProperty& operator=(const TdkAbstractProperty &other);
};


#endif
