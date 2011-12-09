
/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkPasswordProperty.h
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

#ifndef __TDK_PASSWORD_PROPERTY_H
#define __TDK_PASSWORD_PROPERTY_H

#include <TdkAbstractProperty.h>

class TdkLayoutDatabaseObject;

//! \class TdkPasswordProperty
/*! Class to represent the password property
*/

class TdkPasswordProperty : public TdkAbstractProperty
{
protected :

	std::string					_password;
	TdkLayoutDatabaseObject		*_object;

public :
			//! Constructor
			TdkPasswordProperty(TdkLayoutDatabaseObject *obj);

			//! Destructor
			~TdkPasswordProperty();

			//! \brief setValue
			/*! Method to set the new value to
				password property
				\param		newVal		new angle value
			*/
			virtual void setValue(const std::string &newVal);

			//! \brief getValue
			/*! Method to return the password value
				\return		returns the string value
			*/
			virtual std::string getValue();

			//! \brief getValue
			/*! Method to return the password value
				by reference
			*/
			virtual void getValue(std::string &value);

			//! \brief operator
			/*! Operator = overload
				\param		other		other TdkPasswordProperty object
				\return		returns the object with same values that old object
			*/
			TdkPasswordProperty& operator=(const TdkPasswordProperty &other);

			//! \brief operator
			/*! Operator = overload
				\param		other		other TdkAbstractProperty object
				\return		returns the object with same values that old object
			*/
			TdkPasswordProperty& operator=(const TdkAbstractProperty &other);
};

#endif