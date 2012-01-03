#include<TdkLayoutTypes.h>
#include <TdkDatabaseTypeProperty.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkDatabaseTypeProperty::TdkDatabaseTypeProperty(const connectionType &newVal)
{
	_propertyName="DatabaseType_Property";
	_type=newVal;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkDatabaseTypeProperty::~TdkDatabaseTypeProperty()
{

}

///////////////////////////////////////////////////////////////////////////////
//Set Angle Value
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkDatabaseTypeProperty::setValue(const connectionType &newVal)
{
	_type=newVal;
}

void TdkDatabaseTypeProperty::setValue(const double &value)
{
	int type=(int)value;
	_type=(connectionType)type;
}
///////////////////////////////////////////////////////////////////////////////
//Returns the database type value
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

connectionType TdkDatabaseTypeProperty::getValue()
{
	return _type;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the database type value by reference
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkDatabaseTypeProperty::getValue(double &value)
{
	value=(double)_type;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkDatabaseTypeProperty& TdkDatabaseTypeProperty::operator=(const TdkDatabaseTypeProperty &other)
{
	_type=other._type;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkDatabaseTypeProperty& TdkDatabaseTypeProperty::operator=(const TdkAbstractProperty &other)
{
	_type=((TdkDatabaseTypeProperty&)other)._type;
	return *this;
}