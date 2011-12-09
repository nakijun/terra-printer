#include<TdkLayoutTypes.h>
#include <TdkAbstractProperty.h>
#include <TdkTextItalicProperty.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkTextItalicProperty::TdkTextItalicProperty(const bool &newVal)
{
	_propertyName="TextItalic_Property";
	_value=newVal;
	_type=PBoolean;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkTextItalicProperty::~TdkTextItalicProperty()
{

}

///////////////////////////////////////////////////////////////////////////////
//Sets Text Italic status
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkTextItalicProperty::setValue(const bool &newVal)
{
	_value=newVal;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the Text Italic status
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

bool TdkTextItalicProperty::getValue()
{
	return _value;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the Text Italic status by reference
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

void TdkTextItalicProperty::getValue(bool &value)
{
	value=_value;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkTextItalicProperty& TdkTextItalicProperty::operator=(const TdkTextItalicProperty &other)
{
	_value=other._value;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkTextItalicProperty& TdkTextItalicProperty::operator=(const TdkAbstractProperty &other)
{
	_value=((TdkTextItalicProperty&)other)._value;
	return *this;
}