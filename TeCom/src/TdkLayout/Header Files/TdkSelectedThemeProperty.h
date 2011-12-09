

/* TerraLib Components - TeCOM
* 
* @(#) TdkSelectedThemeProperty.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2011/11/30 13:37:49 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_SELECTED_THEME_PROPERTY_H
#define __TDK_SELECTED_THEME_PROPERTY_H

#include<TdkAbstractProperty.h>
#include <string>

using namespace std;

class TeView;
class TeTheme;

/*! /class TdkSelectedThemeProperty
	The Class TdkSelectedThemeProperty store the theme name
	used to show the selected itens.
	When the user choice a theme, I check if theme name is
	valid, looking for in view for theme.
	Whether view pointer is null, I just store the theme name
	and I don't check if is valid.
*/
class TdkSelectedThemeProperty : public TdkAbstractProperty
{
protected :
	std::string			_value;
	TeView				*_view;

protected:
	//! /brief locateTheme
	/*! Method to locate a theme from current view
	*/
	virtual bool locateTheme(const std::string &name);
public:
	//! \brief constructor
	TdkSelectedThemeProperty(TeView *view=0, const std::string &value="");

	//! \brief Destructor
	~TdkSelectedThemeProperty();

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
		\param		other		other TdkSelectedThemeProperty object
		\return		returns the object with same values that old object
	*/
	TdkSelectedThemeProperty& operator=(const TdkSelectedThemeProperty &other);

	//! \brief operator
	/*! Operator = overload
		\param		other		other TdkAbstractProperty object
		\return		returns the object with same values that old object
	*/
	TdkSelectedThemeProperty& operator=(const TdkAbstractProperty &other);


	//! \brief getTheme
	/*! Method to return the selected theme
		\return returns the terralib theme
	*/
	virtual TeTheme *getTheme();

	//! \brief setView
	/*! Sets the views used to 
		show the datas
		\param	view		terralib view
	*/
	virtual void setView(TeView *view);

};


#endif

