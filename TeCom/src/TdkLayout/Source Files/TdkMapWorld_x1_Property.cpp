#include<TdkLayoutTypes.h>
#include<TdkMapWorld_x1_Property.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Greg�rio 
//Date : 07/2011
///////////////////////////////////////////////////////////////////////////////
TdkMapWorld_x1_Property::TdkMapWorld_x1_Property(double *newVal, bool *redraw) : TdkAbstractProperty()
{	
		_propertyName="MapWorld_X1_Property";
		_redraw=redraw;
		_value=newVal;
}


///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Greg�rio 
//Date : 07/2011
///////////////////////////////////////////////////////////////////////////////
TdkMapWorld_x1_Property::~TdkMapWorld_x1_Property()
{
	_value=0;
}

///////////////////////////////////////////////////////////////////////////////
//SetValue
//Author : Rui Mauricio Greg�rio 
//Date : 07/2011
///////////////////////////////////////////////////////////////////////////////
void TdkMapWorld_x1_Property::setValue(const double &newVal)
 {
	if(_value != 0)		*_value=newVal;
	if(_redraw != 0)	*_redraw=true;
 }

///////////////////////////////////////////////////////////////////////////////
//GetValue
//Author : Rui Mauricio Greg�rio 
//Date : 07/2011
///////////////////////////////////////////////////////////////////////////////
double TdkMapWorld_x1_Property::getValue()
{
	if(_value != 0) return *_value;
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//GetValue by Reference
//Author : Rui Mauricio Greg�rio 
//Date : 07/2011
///////////////////////////////////////////////////////////////////////////////
void TdkMapWorld_x1_Property::getValue(double &value)
{
	if(_value != 0) value=*_value;
	else			value=0;
}

///////////////////////////////////////////////////////////////////////////////
//Equal operator
//Author : Rui Mauricio Greg�rio 
//Date : 07/2011
///////////////////////////////////////////////////////////////////////////////
TdkMapWorld_x1_Property& TdkMapWorld_x1_Property::operator=(const TdkMapWorld_x1_Property &other)
{
	if(_value != 0)	*_value=*other._value;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Greg�rio 
//Date : 07/2011
///////////////////////////////////////////////////////////////////////////////
TdkMapWorld_x1_Property& TdkMapWorld_x1_Property::operator=(const TdkAbstractProperty &other)
{
	if(_value != 0)	*_value=*((TdkMapWorld_x1_Property&)other)._value;
	return *this;
}