/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkMapScaleProperty.h
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

#ifndef __TDK_MAP_SCALE_PROPERTY_H
#define __TDK_MAP_SCALE_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkMapScaleProperty
/*! Class to represent the angle property
*/
class TdkMapScaleProperty : public TdkAbstractProperty
{
protected:
	double		_value;					//!< angle value
	bool		_externSetting;			//!< scale sets by user
public :

	//! \brief TdkMapScaleProperty
	/*! Constructor
		\param	newVale		new scale value
	*/
	TdkMapScaleProperty(const double &newVal=0.0);

	//! \brief ~TdkMapScaleProperty
	/*!	Destructor
	*/
	virtual ~TdkMapScaleProperty();

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
	TdkMapScaleProperty& operator=(const TdkMapScaleProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkMapScaleProperty& operator=(const TdkAbstractProperty &other);

	//! \brief setExternalScale
	/*! Method to indicate that scale
		was configured by user
	*/
	virtual void setExternalScale();

	//! \brief resetExternalScale
	virtual void resetExternalScale();

	//! \brief externalScaleStatus
	/*! Method to return the external 
		scale status, this way I know
		that user sets the scale
		\return	returns the external scale status
	*/
	virtual bool externalScaleStatus();
};

#endif

