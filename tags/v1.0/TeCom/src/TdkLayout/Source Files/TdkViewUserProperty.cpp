#include<TdkLayoutTypes.h>
#include <TdkViewUserProperty.h>


///////////////////////////////////////////////////////////////////////////////
// Constructor
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkViewUserProperty::TdkViewUserProperty(const std::string &value)
{
	_propertyName="ViewUser_Property";
	_type=PText;
	_userName=value;
}

///////////////////////////////////////////////////////////////////////////////
// Destructor
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkViewUserProperty::~TdkViewUserProperty()
{

}

///////////////////////////////////////////////////////////////////////////////
// setValue
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkViewUserProperty::setValue(const std::string &newVal)
{
	_userName=newVal;
}

///////////////////////////////////////////////////////////////////////////////
// getValue
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
std::string TdkViewUserProperty::getValue()
{
	return _userName;
}

///////////////////////////////////////////////////////////////////////////////
// getValue by reference
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkViewUserProperty::getValue(std::string &value)
{
	value=_userName;

}

///////////////////////////////////////////////////////////////////////////////
// Equal operator
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkViewUserProperty& TdkViewUserProperty::operator=(const TdkViewUserProperty &other)
{
	this->_userName=other._userName;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Equal operator
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkViewUserProperty& TdkViewUserProperty::operator=(const TdkAbstractProperty &other)
{
	this->_userName=((TdkViewUserProperty&)other)._userName;
	return *this;
}