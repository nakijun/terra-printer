
#include <TdkXmlItem.h>
#include <TeUtils.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

TdkXmlItem::TdkXmlItem()
{
	_name="ROOT";
	_currentItem=this;
	_value.clear();
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

TdkXmlItem::~TdkXmlItem()
{
	std::vector<TdkXmlItem*>::iterator it;
	
	for(it=_subItem.begin();it!=_subItem.end();it++)
		delete (*it);
	_subItem.clear();
}

///////////////////////////////////////////////////////////////////////////////
//Add new subItem
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

void TdkXmlItem::addItem(TdkXmlItem *item)
{
	_currentItem->_subItem.push_back(item);
	_currentItem=item;
}

///////////////////////////////////////////////////////////////////////////////
//Close the current subItem
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkXmlItem::close()
{
	_currentItem=this;
}


///////////////////////////////////////////////////////////////////////////////
//verify item whether has a subitems
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlItem::hasSubItem()
{
	return !this->_subItem.empty();
}

///////////////////////////////////////////////////////////////////////////////
//locate a xml item
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
TdkXmlItem* TdkXmlItem::locateItem(TdkXmlItem *xmlItem, const std::string &name)
{
	std::vector<TdkXmlItem*>::iterator	it;
	std::vector<TdkXmlItem*> subItem;

	subItem=xmlItem->_subItem;

	for(it=subItem.begin();it!=subItem.end();it++)
	{
		if(TeConvertToUpperCase((*it)->getName()) == TeConvertToUpperCase(name))	return (*it);
		if((*it)->hasSubItem())
		{
			TdkXmlItem *item = locateItem((*it),name);
			if(item !=0) return item;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//locate xml item
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

TdkXmlItem* TdkXmlItem::searchItem(const std::string &name)
{
	return locateItem(this,name);
}

///////////////////////////////////////////////////////////////////////////////
//Returns the current item
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

TdkXmlItem* TdkXmlItem::getItem()
{
	return _currentItem;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the item name
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
std::string TdkXmlItem::getName()
{
	return _currentItem->_name;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the sub item list
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
std::vector<TdkXmlItem*> TdkXmlItem::getSubItem()
{
	return this->_subItem;
}

///////////////////////////////////////////////////////////////////////////////
//Sets item name
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkXmlItem::setName(const std::string &value)
{
	_currentItem->_name=value;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the item value
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
std::string TdkXmlItem::getValue()
{
	return _currentItem->_value;
}

///////////////////////////////////////////////////////////////////////////////
//Sets the item value
//Author : Rui Mauricio Greg�rio 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkXmlItem::setValue(const std::string &value)
{
	_currentItem->_value=value;
}