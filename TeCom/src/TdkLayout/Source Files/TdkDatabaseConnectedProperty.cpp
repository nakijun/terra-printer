#include<TdkLayoutTypes.h>
#include <TdkDatabaseConnectedProperty.h>
#include <TdkLayoutDatabaseObject.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkDatabaseConnectedProperty::TdkDatabaseConnectedProperty(TdkLayoutDatabaseObject *obj,const bool &newVal)
{
	_propertyName="DatabaseConnected_Property";
	_value=newVal;
	_type=PBoolean;
	_object=obj;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkDatabaseConnectedProperty::~TdkDatabaseConnectedProperty()
{

}

///////////////////////////////////////////////////////////////////////////////
//Sets text Value
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkDatabaseConnectedProperty::setValue(const bool &newVal)
{
	if(_object)		
	{
		if(newVal == false) _value=!_object->closeConnection();
		else				_value=_object->connect();
	}
	else			_value=false;
}

void TdkDatabaseConnectedProperty::closedConnection()
{
	_value=false;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the connection Status
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

bool TdkDatabaseConnectedProperty::getValue()
{
	return _value;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the connection Status by reference
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

void TdkDatabaseConnectedProperty::getValue(bool &value)
{
	value=_value;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkDatabaseConnectedProperty& TdkDatabaseConnectedProperty::operator=(const TdkDatabaseConnectedProperty &other)
{
	_value=other._value;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkDatabaseConnectedProperty& TdkDatabaseConnectedProperty::operator=(const TdkAbstractProperty &other)
{
	_value=((TdkDatabaseConnectedProperty&)other)._value;
	return *this;
}