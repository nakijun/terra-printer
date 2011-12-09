/* TerraLib Components - TeCOM
* 
* @(#) TdkDatabaseNameProperty.h
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

#ifndef __TDK_DATABASE_NAME_PROPERTY_H
#define __TDK_DATABASE_NAME_PROPERTY_H

#include<TdkAbstractProperty.h>
#include <string>

using namespace std;

class TdkLayoutDatabaseObject;

//! \class TdkDatabaseNameProperty
/*! Class to manipulate the database name value
*/
class	TdkDatabaseNameProperty : public TdkAbstractProperty
{
protected:

	std::string					_value;		//!< Text Value
	TdkLayoutDatabaseObject		*_object;

public :

	//! \brief TdkDatabaseNameProperty
	/*! Constructor
		\param	newVal		new database name value
	*/
	TdkDatabaseNameProperty(TdkLayoutDatabaseObject *obj,const std::string &newVal="");

	//! \brief Destructor
	virtual ~TdkDatabaseNameProperty();

	//! \brief setValue
	/*! Method to set the database name value
		\param	newVal	new database name value
	*/
	virtual void setValue(const std::string &newVal);

	//! \brief getValue
	/*! Method to return the database name value
		\return returns the database name value
	*/
	virtual std::string getValue();

	//! \brief getValue
	/*! Method to return the database name value
		by reference
	*/
	virtual void getValue(std::string &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkDatabaseNameProperty object
		\return		returns the object with same values that old object
	*/
	TdkDatabaseNameProperty& operator=(const TdkDatabaseNameProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkDatabaseNameProperty& operator=(const TdkAbstractProperty &other);
};


#endif
