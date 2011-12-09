#include<TdkLayoutTypes.h>
#include <TdkDatabaseConnectionProperty.h>
#include <TdkLayoutObject.h>
#include <TdkLayoutDatabaseObject.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkDatabaseConnectionProperty::TdkDatabaseConnectionProperty(const std::string &newVal)
{
	_propertyName="Connection_Property";
	_value=newVal;
	_updated=false;
	_type=PText;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkDatabaseConnectionProperty::~TdkDatabaseConnectionProperty()
{

}

///////////////////////////////////////////////////////////////////////////////
//Set Angle Value
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkDatabaseConnectionProperty::setValue(const std::string &newVal)
{
	_value=newVal;
	if(_value.empty())		
	{
		disassociateObject();
		_updated=true;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Returns the string connection value
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

std::string TdkDatabaseConnectionProperty::getValue()
{
	return _value;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the string connection value by reference
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
void TdkDatabaseConnectionProperty::getValue(std::string &value)
{
	value=_value;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkDatabaseConnectionProperty& TdkDatabaseConnectionProperty::operator=(const TdkDatabaseConnectionProperty &other)
{
	_value=other._value;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkDatabaseConnectionProperty& TdkDatabaseConnectionProperty::operator=(const TdkAbstractProperty &other)
{
	_value=((TdkDatabaseConnectionProperty&)other)._value;
	return *this;
}

void TdkDatabaseConnectionProperty::associateObject(TdkLayoutObject *obj, std::string objName)
{
	if(typeid(*obj) == typeid(TdkLayoutDatabaseObject))
	{
		if(_objDecorated) _objDecorated->disassociateObjectProperty();
		_objDecorated=obj;
		_objDecorated->associateObjectProperty(this);
		_value=objName;
		_updated=true;
	}
}

TdkLayoutObject* TdkDatabaseConnectionProperty::getObject()
{
		return _objDecorated;
}

bool TdkDatabaseConnectionProperty::isChange()
{
	bool status;
	status=_updated;
	_updated=false;
	return status;
}

void TdkDatabaseConnectionProperty::disassociateObject()
{
	TdkAbstractProperty::disassociateObject();
	_value.clear();
	_updated=true;
}