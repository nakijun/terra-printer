/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkHeightProperty.h
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

#ifndef __TDK_HEIGHT_PROPERTY_H
#define __TDK_HEIGHT_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkHeightProperty
/*! Class to set the Height property of object
*/
class TdkHeightProperty : public TdkAbstractProperty
{
public :
	double		*_y1;				//! pointer to y coordinate from _boundingBox
	double		*_y2;				//! pointer to y coordinate from _boundingBox
	bool		*_redraw;			//! pointer to indicate that object is necessary redraw
public :

	//! \brief Constructor
	TdkHeightProperty();

	//! \brief Destructor
	virtual ~TdkHeightProperty();

	//! \brief setValue
	/*! Set the new value to height property, this
		method will calculate the new position to
		y2 coordinate.
		\param		newVal		new height value
	*/
	virtual void setValue(const double &newVal);

	//! \brief getValue
	/*! Method to return the height value
		of object
		\return		returns the new height value
	*/
	virtual double getValue();

	//! \brief getValue
	/*! Method to return the height value
		of object by reference
	*/
	virtual void getValue(double &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkHeightProperty object
		\return		returns the object with same values that old object
	*/
	TdkHeightProperty& operator=(const TdkHeightProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkHeightProperty& operator=(const TdkAbstractProperty &other);
};


#endif
