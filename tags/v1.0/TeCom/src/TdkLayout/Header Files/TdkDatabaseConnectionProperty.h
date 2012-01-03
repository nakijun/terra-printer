/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkDatabaseConnectionProperty.h
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

#ifndef __TDK_DATABASE_CONNECTION_PROPERTY_H
#define __TDK_DATABASE_CONNECTION_PROPERTY_H

#include <TdkAbstractProperty.h>

//! \class TdkDatabaseConnectionProperty
/*! Class to represent the connection database property with database layout object
*/
class TdkDatabaseConnectionProperty : public TdkAbstractProperty
{
protected:
	std::string		_value;

public :

	//! \brief TdkDatabaseConnectionProperty
	/*! Constructor
		\param	newVale		new object name value
	*/
	TdkDatabaseConnectionProperty(const std::string &newVal="");

	//! \brief ~TdkDatabaseConnectionProperty
	/*!	Destructor
	*/
	virtual ~TdkDatabaseConnectionProperty();

	//! \brief setValue
	/*! Method to set the new value to
		object namey
		\param		newVal		new object name value
	*/
	virtual void setValue(const std::string &newVal);

	//! \brief getValue
	/*! Method to return the object name value
		\return		returns the object name value
	*/
	virtual std::string getValue();

	//! \brief getValue
	/*! Method to return the object name value
		by reference
	*/
	virtual void getValue(std::string &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkDatabaseConnectionProperty object
		\return		returns the object with same values that old object
	*/
	TdkDatabaseConnectionProperty& operator=(const TdkDatabaseConnectionProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkDatabaseConnectionProperty object
		\return		returns the object with same values that old object
	*/
	TdkDatabaseConnectionProperty& operator=(const TdkAbstractProperty &other);


	//! \brief associateObject
	/*! Method to associate the property with other object
		\param		obj				layout object
		\param		objName			layout object name
	*/
	virtual void associateObject(TdkLayoutObject *obj, std::string objName);

	//! \brief getObject
	/*! Returns the decorated object
	*/
	virtual TdkLayoutObject* getObject();

	virtual bool isChange();

	virtual void disassociateObject();
};

#endif

