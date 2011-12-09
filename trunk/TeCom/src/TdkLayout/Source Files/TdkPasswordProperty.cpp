#include<TdkLayoutTypes.h>
#include <TdkPasswordProperty.h>
#include <TdkLayoutDatabaseObject.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
TdkPasswordProperty::TdkPasswordProperty(TdkLayoutDatabaseObject *obj)
{
	_propertyName="Password_Property";
	_password.clear();
	_type=PText;
	_object=obj;
}


///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
TdkPasswordProperty::~TdkPasswordProperty()
{


}

///////////////////////////////////////////////////////////////////////////////
//Set Password value
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkPasswordProperty::setValue(const std::string &newVal)
{
	_password=newVal;
	if(_object) _object->closeConnection();
}

///////////////////////////////////////////////////////////////////////////////
//Returns the password value
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
std::string TdkPasswordProperty::getValue()
{
	return _password;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the password value by reference
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkPasswordProperty::getValue(std::string &value)
{
	value=_password;
}

///////////////////////////////////////////////////////////////////////////////
//Operator
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
TdkPasswordProperty& TdkPasswordProperty::operator=(const TdkPasswordProperty &other)
{
	_password=other._password;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//Operator
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
TdkPasswordProperty& TdkPasswordProperty::operator=(const TdkAbstractProperty &other)
{
	_password=((TdkPasswordProperty&)other)._password;
	return *this;
}