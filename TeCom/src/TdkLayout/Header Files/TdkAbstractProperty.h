/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkAbstractProperty.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/09/10 17:38:44 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_ABSTRACT_PROPERTY_H
#define __TDK_ABSTRACT_PROPERTY_H

#include<string>


using namespace std;

class TdkLayoutObject;

//! \class TdkAbstractProperty
/*! Abstract Class of properties
*/
class TdkAbstractProperty
{
protected :
	std::string		_propertyName;		//! property name
	propertyType	_type;
	TdkLayoutObject	*_objDecorated;
	bool			_updated;
public :

	//! \brief TdkAbstractProperty
	/*! Empty Constructor
	*/
	TdkAbstractProperty();

	//! \brief Destructor
	~TdkAbstractProperty();

	//! \brief name
	/*! Method to return the
		string property name
		\return		returns the property name
	*/
	virtual std::string name();

	//! \brief getType
	/*! Returns the property type
	*/
	virtual propertyType getType();

	//! \brief associateObject
	virtual void associateObject(TdkLayoutObject *obj, std::string objName);

	//! \brief disassociateObject
	virtual void disassociateObject();

	//! \brief update
	virtual void update();

	//! \brief getValue
	virtual void getValue(double &value);

	//! \brief setValue
	virtual void setValue(const double &value);

	//! \brief getValue
	virtual void getValue(std::string &value);

	//! \brief setValue
	virtual void setValue(const std::string &value);

	//! \brief getValue
	virtual void getValue(bool &value);

	//! \brief setValue
	virtual void setValue(const bool &value);

	//! \brief getValue
	virtual void getValue(unsigned char &value);

	//! \brief setValue
	virtual void setValue(const unsigned char &value);

	//! \brief getArrayValue
	/*! Method to return the array values
		\return		returns the array values
	*/
	virtual unsigned char *getArrayValue(unsigned long &);
};


#endif


