/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkXmlItem.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/08/24 14:17:09 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_XML_ITEM_H
#define __TDK_XML_ITEM_H

#include <string>
#include <vector>

using namespace std;

//! \class TdkXmlItem
/*! Class to organize the xml
	in tree format
*/
class TdkXmlItem
{
protected:

	std::string					_name;			//!< item name
	std::string					_value;			//!< item value
	std::vector<TdkXmlItem*>	_subItem;		//!< sub item
	TdkXmlItem*					_currentItem;	//!< current Item

protected:

	//! \brief locateItem
	/*! Locate xml Item according your name
		\param TdkXmlItem		xml tree
		\param name				item name to locate
		\return		return the item object with your sub items
	*/
	virtual TdkXmlItem *locateItem(TdkXmlItem *xmlItem, const std::string &name);

	//! \brief hasSubItem
	/*! Verify whether item has a sub item
		\return returns true whether item has one or many sub items
	*/
	virtual bool hasSubItem();

public:
	//! \brief Constructor
	TdkXmlItem();

	//! \brief Destructor
	virtual ~TdkXmlItem();

	//! \brief addItem
	/*! Add a new item as sub item from
		current item
		\param	item	TdkXmlItem pointer
	*/
	virtual void addItem(TdkXmlItem *item);

	//! \brief Close
	/*! Method to close the current subItem
	*/
	virtual void close();

	//! \brief searchItem
	/*! Method to search the item according your
		name
		\param	name		item name
		\return	returns the TdkXmlItem object
	*/
	virtual TdkXmlItem* searchItem(const std::string &name);

	//! \brief getItem
	/*! Method to return the
		current item
		\return	returns the TdkXmlItem pointer
	*/
	virtual TdkXmlItem* getItem();

	//! \brief getName
	/*! Method to return the name item
		\returns returns the name item
	*/
	virtual std::string getName();

	//! \brief setName
	/*! Sets the item name
		\param	value new name for current item
	*/
	virtual void setName(const std::string &value);

	//! \brief getValue
	/*!
		\return returns the current item value
	*/
	virtual std::string getValue();

	//! \brief setValue
	/*! Method to set the current item value
		\param	value	new value
	*/
	virtual void setValue(const std::string &value);

	//! \brief getSubItem
	/*! 
		\return	returns the subItem list
	*/
	std::vector<TdkXmlItem*> getSubItem();

};

#endif
