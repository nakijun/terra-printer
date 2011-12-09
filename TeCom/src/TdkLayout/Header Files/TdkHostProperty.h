/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkHostProperty.h
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

#ifndef __TDK_HOST_PROPERTY_H
#define __TDK_HOST_PROPERTY_H

#include <TdkAbstractProperty.h>

class TdkLayoutDatabaseObject;

//! \class TdkHostProperty
/*! Class to represent the host property
*/

class TdkHostProperty : public TdkAbstractProperty
{
protected :

	std::string						_host;
	TdkLayoutDatabaseObject			*_object;
public :
			//! Constructor
			TdkHostProperty(TdkLayoutDatabaseObject *obj);

			//! Destructor
			~TdkHostProperty();

			//! \brief setValue
			/*! Method to set the new value to
				port property
				\param		newVal		new host value
			*/
			virtual void setValue(const std::string &newVal);

			//! \brief getValue
			/*! Method to return the host value
				\return		returns the string value
			*/
			virtual std::string getValue();

			//! \brief getValue
			/*! Method to return the host value
				by reference
			*/
			virtual void getValue(std::string &value);

			//! \brief operator
			/*! Operator = overload
				\param		other		other TdkHostProperty object
				\return		returns the object with same values that old object
			*/
			TdkHostProperty& operator=(const TdkHostProperty &other);

			//! \brief operator
			/*! Operator = overload
				\param		other		other TdkAbstractProperty object
				\return		returns the object with same values that old object
			*/
			TdkHostProperty& operator=(const TdkAbstractProperty &other);
};

#endif