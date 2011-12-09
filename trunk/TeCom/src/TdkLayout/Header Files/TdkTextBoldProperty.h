/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkTextBoldProperty.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/08/23 13:21:20 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_TEXT_BOLD_PROPERTY_H
#define __TDK_TEXT_BOLD_PROPERTY_H


//! \class TdkTextBoldProperty
/*! Method to storage the bold property
*/
class TdkTextBoldProperty : public TdkAbstractProperty
{
protected :
	
	bool		_value;		//!< bold status

public :

	//! \brief TdkTextBoldProperty
	/*! Constructor
		\param	newVal		bold status
	*/
	TdkTextBoldProperty(const bool &newVal=false);

	//! \bried Destructor
	virtual ~TdkTextBoldProperty();

	//! \brief setValue
	/*! Method to set the new status
		to bold property
		\newVal		new value to bold status
	*/
	virtual void setValue(const bool &newVal);

	//! \brief getValue
	/*! Method to return the bold status value
		\return	returns the bold status
	*/
	virtual bool getValue();

	//! \brief getValue
	/*! Method to return the bold status value
		by reference
	*/
	virtual void getValue(bool &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkTextBoldProperty object
		\return		returns the object with same values that old object
	*/
	TdkTextBoldProperty& operator=(const TdkTextBoldProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkTextBoldProperty& operator=(const TdkAbstractProperty &other);
};

#endif


