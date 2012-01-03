

/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkDatabaseConnectedProperty.h
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

#ifndef __TDK_DATABASE_CONNECTED_PROPERTY_H
#define __TDK_DATABASE_CONNECTED_PROPERTY_H

#include <TdkAbstractProperty.h>

class TdkLayoutDatabaseObject;

//! \class TdkDatabaseConnectedProperty
/*! Class to represent the angle property
*/
class TdkDatabaseConnectedProperty : public TdkAbstractProperty
{
protected:
	bool							_value;			//!< connected boolean value
	
	TdkLayoutDatabaseObject			*_object;

public :

	//! \brief TdkDatabaseConnectedProperty
	/*! Constructor
		\param	newVale		new angle value
	*/
	TdkDatabaseConnectedProperty(TdkLayoutDatabaseObject *obj, const bool &newVal=false);

	//! \brief ~TdkDatabaseConnectedProperty
	/*!	Destructor
	*/
	virtual ~TdkDatabaseConnectedProperty();

	//! \brief setValue
	/*! Method to set the new database connect status
		\param		newVal		new status
	*/
	virtual void setValue(const bool &newVal);

	//! \brief getValue
	/*! Method to return the connect status value
		\return		returns the angle value
	*/
	virtual bool getValue();

	//! \brief getValue
	/*! Method to return the connect status value by 
		reference
	*/
	virtual void getValue(bool &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkDatabaseConnectedProperty object
		\return		returns the object with same values that old object
	*/
	TdkDatabaseConnectedProperty& operator=(const TdkDatabaseConnectedProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkDatabaseConnectedProperty& operator=(const TdkAbstractProperty &other);

	virtual void closedConnection();
};

#endif

