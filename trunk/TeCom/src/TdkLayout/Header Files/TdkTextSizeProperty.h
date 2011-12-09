/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkTextSizeProperty.h
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
#ifndef __TDK_TEXT_SIZE_PROPERTY_H
#define __TDK_TEXT_SIZE_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkTextSizeProperty
/*! Class to manipulate the text size property
*/
class TdkTextSizeProperty : public TdkAbstractProperty
{
protected :
	double		_value;		//!< text size value
public :
		//! \brief TdkTextSizeProperty
		/*!  Constructor 
			\param	newVal		new value to text size
		*/
		TdkTextSizeProperty(const double &newVal=5);

		//! \brief Destructor
		~TdkTextSizeProperty();

		//! \brief setValue
		/*! Method to set the new value to text size
			\param	newVal		new value to text size
		*/
		virtual void setValue(const double &newVal);

		//! \brief getValue
		/*! Method to return the text size
			\return		returns the text size value
		*/
		virtual double getValue();

		//! \brief getValue
		/*! Method to return the text size
			by reference
		*/
		virtual void getValue(double &value);

		//! \brief operator
		/*! Operator = overload
			\param		other		other TdkTextSizeProperty object
			\return		returns the object with same values that old object
		*/
		TdkTextSizeProperty& operator=(const TdkTextSizeProperty &other);

		//! \brief operator
		/*! Operator = overload
			\param		other		other TdkAbstractProperty object
			\return		returns the object with same values that old object
		*/
		TdkTextSizeProperty& operator=(const TdkAbstractProperty &other);
};


#endif

