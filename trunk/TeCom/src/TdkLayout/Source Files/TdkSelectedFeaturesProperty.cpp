#include<TdkLayoutTypes.h>
#include <TdkSelectedFeaturesProperty.h>


///////////////////////////////////////////////////////////////////////////////
// Constructor
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkSelectedFeaturesProperty::TdkSelectedFeaturesProperty(bool *necessaryRedraw, const std::string &value)
{
	_propertyName="SelectedFeatures_Property";
	_type=PText;
	_value=value;
	_necessaryRedraw=necessaryRedraw;
}

///////////////////////////////////////////////////////////////////////////////
// Destructor
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkSelectedFeaturesProperty::~TdkSelectedFeaturesProperty()
{

}

///////////////////////////////////////////////////////////////////////////////
// setValue
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkSelectedFeaturesProperty::setValue(const std::string &newVal)
{
	_value=newVal;
	*_necessaryRedraw=true;
}

///////////////////////////////////////////////////////////////////////////////
// getValue
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
std::string TdkSelectedFeaturesProperty::getValue()
{
	return _value;
}

///////////////////////////////////////////////////////////////////////////////
// getValue by reference
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkSelectedFeaturesProperty::getValue(std::string &value)
{
	value=_value;

}

///////////////////////////////////////////////////////////////////////////////
// Equal operator
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkSelectedFeaturesProperty& TdkSelectedFeaturesProperty::operator=(const TdkSelectedFeaturesProperty &other)
{
	this->_value=other._value;
	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Equal operator
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkSelectedFeaturesProperty& TdkSelectedFeaturesProperty::operator=(const TdkAbstractProperty &other)
{
	this->_value=((TdkSelectedFeaturesProperty&)other)._value;
	return *this;
}


///////////////////////////////////////////////////////////////////////////////
// Split the selected features to n strings in vector
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
std::vector<std::string> TdkSelectedFeaturesProperty::split(const std::string &value)
{
	std::vector<std::string>	values;
	std::string					curValue;
	unsigned int i;

	for(i=0;i<value.size();i++)
	{
		if(value[i]==';')
		{
			values.push_back(curValue);
			curValue.clear();
		}else
			curValue+=value[i];
	}
	if(!curValue.empty()) values.push_back(curValue);
	return values;
}

///////////////////////////////////////////////////////////////////////////////
// Get splited features
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

std::vector<std::string> TdkSelectedFeaturesProperty::getFeatures()
{
	return this->split(_value);
}

///////////////////////////////////////////////////////////////////////////////
// Returns if vector of features are empty
//Author : Rui Mauricio Greg�rio 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkSelectedFeaturesProperty::empty()
{
	return _value.empty();
}