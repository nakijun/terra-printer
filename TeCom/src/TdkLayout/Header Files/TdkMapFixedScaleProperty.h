/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkMapFixedScaleProperty.h
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

#ifndef __TDK_MAP_FIXED_SCALE_PROPERTY_H
#define __TDK_MAP_FIXED_SCALE_PROPERTY_H


//! \class TdkMapFixedScaleProperty
/*! Method to storage the fixed map scale property
*/
class TdkMapFixedScaleProperty : public TdkAbstractProperty
{
protected :
	
	bool		_value;		//!< bold status

public :

	//! \brief TdkTextBoldProperty
	/*! Constructor
		\param	newVal		bold status
	*/
	TdkMapFixedScaleProperty(const bool &newVal=false);

	//! \bried Destructor
	virtual ~TdkMapFixedScaleProperty();

	//! \brief setValue
	/*! Method to set the new status
		to fixed scale property
		\newVal		new value to bold status
	*/
	virtual void setValue(const bool &newVal);

	//! \brief getValue
	/*! Method to return the fixed scale status value
		\return	returns the bold status
	*/
	virtual bool getValue();

	//! \brief getValue
	/*! Method to return the fixed scale status 
		value by reference
	*/
	virtual void getValue(bool &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkTextBoldProperty object
		\return		returns the object with same values that old object
	*/
	TdkMapFixedScaleProperty& operator=(const TdkMapFixedScaleProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkMapFixedScaleProperty& operator=(const TdkAbstractProperty &other);
};

#endif


