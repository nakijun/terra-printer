#include <TdkLayoutTypes.h>
#include <TdkSelectionTransparencyProperty.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkSelectionTransparencyProperty::TdkSelectionTransparencyProperty(bool *redraw,const double &newVal)
{
	_propertyName="SelectionTransparency_Property";
	_value=newVal;
	_redraw=redraw;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkSelectionTransparencyProperty::~TdkSelectionTransparencyProperty()
{

}

///////////////////////////////////////////////////////////////////////////////
//Set Selection Transparency Value
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkSelectionTransparencyProperty::setValue(const double &newVal)
{
	_value=newVal;
	if(_redraw) *_redraw=true;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the Transparency value
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

double TdkSelectionTransparencyProperty::getValue()
{
	return _value;
}

///////////////////////////////////////////////////////////////////////////////
//Return the Transparency value
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkSelectionTransparencyProperty::getValue(double &value)
{
	value=_value;
}


///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkSelectionTransparencyProperty& TdkSelectionTransparencyProperty::operator=(const TdkSelectionTransparencyProperty &other)
{
	_value=other._value;
	if(_redraw) *_redraw=true;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Greg�rio 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkSelectionTransparencyProperty& TdkSelectionTransparencyProperty::operator=(const TdkAbstractProperty &other)
{
	_value=((TdkSelectionTransparencyProperty&)other)._value;
	if(_redraw) *_redraw=true;
	return *this;
}

