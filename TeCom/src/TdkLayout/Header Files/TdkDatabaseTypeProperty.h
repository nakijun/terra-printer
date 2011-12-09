/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkDatabaseTypeProperty.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/08/27 13:45:08 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_DATABASE_TYPE_PROPERTY_H
#define __TDK_DATABASE_TYPE_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkDatabaseTypeProperty
/*! Class to represent the port property
*/

class TdkDatabaseTypeProperty : public TdkAbstractProperty
{
protected :

	connectionType		_type;

public :
			//! Constructor
			TdkDatabaseTypeProperty(const connectionType &newVal);

			//! Destructor
			~TdkDatabaseTypeProperty();

			//! \brief setValue
			/*! Method to set the new value to
				port property
				\param		newVal		new database type value
			*/
			virtual void setValue(const connectionType &newVal);

			//! \brief setValue
			/*! Method to set the new value to
				port property
				\param		newVal		new database type value
			*/
			virtual void setValue(const double &value);

			//! \brief getValue
			/*! Method to return the database type value
				\return		returns the connection Type
			*/
			virtual connectionType getValue();

			//! \brief getValue
			/*! Method to return the database type value
				by reference
			*/
			virtual void getValue(double &value);

			//! \brief operator
			/*! Operator = overload
				\param		other		other TdkDatabaseTypeProperty object
				\return		returns the object with same values that old object
			*/
			TdkDatabaseTypeProperty& operator=(const TdkDatabaseTypeProperty &other);

			//! \brief operator
			/*! Operator = overload
				\param		other		other TdkAbstractProperty object
				\return		returns the object with same values that old object
			*/
			TdkDatabaseTypeProperty& operator=(const TdkAbstractProperty &other);
};

#endif