/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkUserNameProperty.h
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

#ifndef __TDK_USER_NAME_PROPERTY_H
#define __TDK_USER_NAME_PROPERTY_H

#include <TdkAbstractProperty.h>

class TdkLayoutDatabaseObject;

//! \class TdkUserNameProperty
/*! Class to represent the user name property
*/


class TdkUserNameProperty : public TdkAbstractProperty
{
protected :

	std::string					_name;
	TdkLayoutDatabaseObject		*_object;

public :
			//! Constructor
			TdkUserNameProperty(TdkLayoutDatabaseObject *obj);

			//! Destructor
			~TdkUserNameProperty();

			//! \brief setValue
			/*! Method to set the new value to
				angle property
				\param		newVal		new angle value
			*/
			virtual void setValue(const std::string &newVal);

			//! \brief getValue
			/*! Method to return the user name value
				\return		returns the string value
			*/
			virtual std::string getValue();

			//! \brief getValue
			/*! Method to return the user name value
				by reference
			*/
			virtual void getValue(std::string &value);

			//! \brief operator
			/*! Operator = overload
				\param		other		other TdkAngleProperty object
				\return		returns the object with same values that old object
			*/
			TdkUserNameProperty& operator=(const TdkUserNameProperty &other);

			//! \brief operator
			/*! Operator = overload
				\param		other		other TdkAbstractProperty object
				\return		returns the object with same values that old object
			*/
			TdkUserNameProperty& operator=(const TdkAbstractProperty &other);
};


#endif

