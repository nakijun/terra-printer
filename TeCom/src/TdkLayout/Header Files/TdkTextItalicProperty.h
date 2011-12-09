/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkTextItalicProperty.h
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

#ifndef __TDK_TEXT_ITALIC_PROPERTY_H
#define __TDK_TEXT_ITALIC_PROPERTY_H

//! \class TdkTextItalicProperty
/*! Class to manipulate the italic text option
*/
class TdkTextItalicProperty  : public TdkAbstractProperty
{
protected :
	
	bool		_value;		//!<	italic status

public :

	//! \brief TdkTextItalicProperty
	/*! Constructor
		\pram	newVal		new italic status value
	*/
	TdkTextItalicProperty(const bool &newVal=false);

	//! \brief Destructor
	virtual ~TdkTextItalicProperty();

	//! \brief setValue
	/*! Method to set the italic value
		\param	newVal		new italic status value
	*/
	virtual void setValue(const bool &newVal);

	//! \brief getValue
	/*! Method to return the italic status
		\return returns the status value
	*/
	virtual bool getValue();

	//! \brief getValue
	/*! Method to return the italic status
		by reference
	*/
	virtual void getValue(bool &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkTextItalicProperty object
		\return		returns the object with same values that old object
	*/
	TdkTextItalicProperty& operator=(const TdkTextItalicProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkTextItalicProperty& operator=(const TdkAbstractProperty &other);
};

#endif