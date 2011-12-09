#include<TdkLayoutTypes.h>
#include <TdkBackgroundBColorProperty.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkBackgroundBColorProperty::TdkBackgroundBColorProperty(const unsigned char &newVal)
{
	_value=newVal;
	_propertyName="BackgroundBlue_Property";
	_type=PColor;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkBackgroundBColorProperty::~TdkBackgroundBColorProperty()
{

}

///////////////////////////////////////////////////////////////////////////////
//Set background Red Color Value
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkBackgroundBColorProperty::setValue(const unsigned char &newVal)
{
	_value=newVal;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the background Red Color value
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

unsigned char TdkBackgroundBColorProperty::getValue()
{
	return _value;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the background Red Color value by reference
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

void TdkBackgroundBColorProperty::getValue(unsigned char &value)
{
	value=_value;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkBackgroundBColorProperty& TdkBackgroundBColorProperty::operator=(const TdkBackgroundBColorProperty &other)
{
	_value=other._value;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkBackgroundBColorProperty& TdkBackgroundBColorProperty::operator=(const TdkAbstractProperty &other)
{
	_value=((TdkBackgroundBColorProperty&)other)._value;
	return *this;
}