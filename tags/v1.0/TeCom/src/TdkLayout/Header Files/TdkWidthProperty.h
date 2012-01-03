/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkWidthProperty.h
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
#ifndef __TDK_WIDTH_PROPERTY_H
#define __TDK_WIDTH_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkWidthProperty
/*! Class to manipulate the width property of object
*/
class TdkWidthProperty : public TdkAbstractProperty
{
public :
	double  *_x1;			//!< pointer to access the x1 of _boundingBox
	double	*_x2;			//!< pointer to access the x2 of _boundingBox
	bool	*_redraw;		//!< pointer to access the indicator of redraw operation
public :

	//! \brief TdkWidthProperty
	/*! Constructor
		\param		newVal		new width value
	*/
	TdkWidthProperty(const double &newVal=0.0);

	//! \brief Destructor
	virtual ~TdkWidthProperty();

	//! \brief setValue
	/*! Method to set the new value
		to width property
		\param	newVal		new width value
	*/
	virtual void setValue(const double &newVal);
	
	//! \brief getValue
	/*! Method to return the width value
		\return returns th width value of object
	*/
	virtual double getValue();

	//! \brief getValue
	/*! Method to return the width value
		by reference
	*/
	void getValue(double &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkWidthProperty object
		\return		returns the object with same values that old object
	*/
	TdkWidthProperty& operator=(const TdkWidthProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkWidthProperty& operator=(const TdkAbstractProperty &other);
};


#endif
