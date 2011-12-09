
/*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2011/11/30 13:37:49 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_SELECTED_FEATURES_PROPERTY_H
#define __TDK_SELECTED_FEATURES_PROPERTY_H

#include<TdkAbstractProperty.h>
#include <string>
#include <vector>

using namespace std;

/*! /class TdkSelectedFeaturesProperties
	The Class TdkSelectedFeaturesProperty store the feature's
	identify.
	The identifies are separate by semicolon
*/
class TdkSelectedFeaturesProperty : public TdkAbstractProperty
{
protected :
	std::string			_value;

	std::vector<std::string> split(const std::string &value);

	bool				*_necessaryRedraw;
public:
	//! \brief constructor
	TdkSelectedFeaturesProperty(bool *necessaryRedraw, const std::string &value="");

	//! \brief Destructor
	~TdkSelectedFeaturesProperty();

	//! \brief setValue
	/*! Method to set the theme name
		\param	newVal	new text value
	*/
	virtual void setValue(const std::string &newVal);

	//! \brief getValue
	/*! Method to return the theme name
		\return returns the theme name
	*/
	virtual std::string getValue();

	//! \brief getValue
	/*! Method to return the theme name
		by file name
	*/
	virtual void getValue(std::string &value);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkSelectedFeaturesProperty object
		\return		returns the object with same values that old object
	*/
	TdkSelectedFeaturesProperty& operator=(const TdkSelectedFeaturesProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkSelectedFeaturesProperty& operator=(const TdkAbstractProperty &other);

	//! \brief getFeatures
	/*! Returns the selected features in
		list
		\return		returns the list of string
	*/
	virtual std::vector<std::string> getFeatures();

	//! \brief empty
	/*! This method return if selected features
		are empty
	*/
	virtual bool empty();
	
};


#endif

