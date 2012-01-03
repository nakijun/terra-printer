#include <TdkLayoutTypes.h>
#include <TdkSelectionColorProperty.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkSelectionColorProperty::TdkSelectionColorProperty(bool *redraw, const double &newVal)
{
	_propertyName="SelectionColor_Property";
	_value=newVal;
	_redraw=redraw;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkSelectionColorProperty::~TdkSelectionColorProperty()
{

}

///////////////////////////////////////////////////////////////////////////////
//Set Selection Color Value
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkSelectionColorProperty::setValue(const double &newVal)
{
	if(_redraw) *_redraw=true;
	_value=newVal;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the Color value
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

double TdkSelectionColorProperty::getValue()
{
	return _value;
}

///////////////////////////////////////////////////////////////////////////////
//Return the Color value
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkSelectionColorProperty::getValue(double &value)
{
	value=_value;
}


///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkSelectionColorProperty& TdkSelectionColorProperty::operator=(const TdkSelectionColorProperty &other)
{
	_value=other._value;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkSelectionColorProperty& TdkSelectionColorProperty::operator=(const TdkAbstractProperty &other)
{
	_value=((TdkSelectionColorProperty&)other)._value;
	return *this;
}

TeColor TdkSelectionColorProperty::getColor()
{
	unsigned int value;
	value=(unsigned int)_value;
	unsigned char blue=(value&0x00ff0000)>>16;
	unsigned char green=(value&0x0000ff00)>>8;
	unsigned char red=value&0x000000ff;
	return TeColor(red,green,blue);
}