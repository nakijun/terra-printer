

/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkSelectionTransparencyProperty.h
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

#ifndef __TDK_SELECTION_TRANSPARENCY_PROPERTY_H
#define __TDK_SELECTION_TRANSPARENCY_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkSelectionTransparencyProperty
/*! Class set the transparency value
*/
class TdkSelectionTransparencyProperty : public TdkAbstractProperty
{
protected:
	double		_value;			//!< transparency value
	bool		*_redraw;		//!< necessary redraw
public :

	//! \brief TdkSelectionTransparencyProperty
	/*! Constructor
		\param	newVale		new transparency value
	*/
	TdkSelectionTransparencyProperty(bool *redraw,const double &newVal=0.0);

	//! \brief ~TdkSelectionTransparencyProperty
	/*!	Destructor
	*/
	virtual ~TdkSelectionTransparencyProperty();

	//! \brief setValue
	/*! Method to set the new value to
		angle property
		\param		newVal		new transparency value
	*/
	virtual void setValue(const double &newVal);

	//! \brief getValue
	/*! Method to return the transparency value
		\return		returns the transparency value
	*/
	virtual double getValue();

	//! \brief getValue
	/*! Method to return the transparency value
		by reference
	*/
	virtual void getValue(double &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkSelectionTransparencyProperty object
		\return		returns the object with same values that old object
	*/
	TdkSelectionTransparencyProperty& operator=(const TdkSelectionTransparencyProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkSelectionTransparencyProperty& operator=(const TdkAbstractProperty &other);
};

#endif

