#include<TdkLayoutTypes.h>
#include <TdkSelectedThemeProperty.h>

#include <TeView.h>
#include <TeViewNode.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkSelectedThemeProperty::TdkSelectedThemeProperty(TeView *view, const std::string &newVal)
{
	_propertyName="SelectedThemeName_Property";
	_view=view;
	_value=newVal;
	_type=PText;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkSelectedThemeProperty::~TdkSelectedThemeProperty()
{

}

///////////////////////////////////////////////////////////////////////////////
//Sets text Value
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkSelectedThemeProperty::setValue(const std::string &newVal)
{
	_value=newVal;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the text value
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

std::string TdkSelectedThemeProperty::getValue()
{
	return _value;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the text value by reference
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkSelectedThemeProperty::getValue(std::string &value)
{
	value=_value;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkSelectedThemeProperty& TdkSelectedThemeProperty::operator=(const TdkSelectedThemeProperty &other)
{
	_value=other._value;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
//Equal Operator
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkSelectedThemeProperty& TdkSelectedThemeProperty::operator=(const TdkAbstractProperty &other)
{
	_value=((TdkSelectedThemeProperty&)other)._value;
	return *this;
}


bool TdkSelectedThemeProperty::locateTheme(const std::string &name)
{
	std::vector<TeViewNode*> themes;
	std::vector<TeViewNode*>::iterator it;

	if(_view == 0) return false;
	themes=_view->themes();
	for(it=themes.begin();it!=themes.end();it++)
		if(TeConvertToUpperCase((*it)->name()) == TeConvertToUpperCase(name) ) return true;
	return false;
}

void TdkSelectedThemeProperty::setView(TeView *view)
{
	_view=view;
}


TeTheme *TdkSelectedThemeProperty::getTheme()
{
	std::vector<TeViewNode*> themes;
	std::vector<TeViewNode*>::iterator it;

	if(_view == 0) return 0;
	themes=_view->themes();
	for(it=themes.begin();it!=themes.end();it++)
		if(TeConvertToUpperCase((*it)->name()) == TeConvertToUpperCase(_value) ) return ((TeTheme*)(*it));
	return 0;
}