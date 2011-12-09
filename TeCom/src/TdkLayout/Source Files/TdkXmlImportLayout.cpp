#include<TdkPageSize.h>
#include<TdkObjectTypes.h>
#include<TdkAbstractProperty.h>
#include<TdkLayoutController.h>
#include<TdkLayoutObject.h>
#include<TdkAbstractProperty.h>
#include<TeUtils.h>

#include <TdkXmlImportLayout.h>
#include <TdkXmlItem.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

TdkXmlImportLayout::TdkXmlImportLayout(TdkLayoutController *control)
{
	_controller=control;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

TdkXmlImportLayout::~TdkXmlImportLayout()
{

}

///////////////////////////////////////////////////////////////////////////////
//Open XML File
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
xmlTextReaderPtr TdkXmlImportLayout::openXmlFile(const std::string &fileName)
{
	xmlTextReaderPtr xml;
    xml = xmlReaderForFile(fileName.c_str(), NULL, 0);
	return xml;
}

///////////////////////////////////////////////////////////////////////////////
//Load all xml file to memory
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlImportLayout::loadToMemory(xmlTextReaderPtr xml, TdkXmlItem* item)
{
	int				type;
	int				isEmpty;
	const			xmlChar *name, *value;
	TdkXmlItem		*subItem=0;
	bool			status=true;
	
	if(item == 0) item=new TdkXmlItem();
	do
	{
		if(xmlTextReaderRead(xml) != 1)	break;
		name = xmlTextReaderConstName(xml);
		if (name == NULL)	name = BAD_CAST "0";
		value = xmlTextReaderConstValue(xml);
		type=xmlTextReaderNodeType(xml);
		isEmpty=xmlTextReaderIsEmptyElement(xml);

		if(type == Element)
		{
			subItem=new TdkXmlItem();
			subItem->setName(std::string((char*)name));
			item->addItem(subItem);
		}else if(type == Text)
		{
			item->getItem()->setValue(std::string((char*)value));
			continue;
		}
		else if(type == Comment)	continue;
		else if(type == EndElement)	return true;
		if((status=loadToMemory(xml,item->getItem())) == true)
			item->close();

	}while(status);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Read Header Information
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlImportLayout::readHeader(TdkXmlItem *xmlItem)
{	
	TdkXmlItem							*item=0;
	std::vector<TdkXmlItem*>::iterator	it;
	std::vector<TdkXmlItem*>			subItem;	
	short								sCount=0;

	_version.clear();
	_application.clear();
	_objectQtd=0;

	if(xmlItem == 0) return false;

	if((item=xmlItem->searchItem("HEADER")) == 0)	return false;
	
	subItem=item->getSubItem();
	for(it=subItem.begin();it!=subItem.end();it++)
	{
		if( TeConvertToUpperCase((*it)->getName()) == "VERSION" )
		{
			_version=(*it)->getValue();
			sCount++;
		}else if( TeConvertToUpperCase((*it)->getName()) == "APPLICATION" )
		{
			_application=(*it)->getValue();
			sCount++;
		}else if( TeConvertToUpperCase((*it)->getName()) == "OBJECTS" )
		{
			_objectQtd=atoi((*it)->getValue().c_str());
			sCount++;
		}
	}
	return (sCount == 3 ? true : false) ;
}

///////////////////////////////////////////////////////////////////////////////
//Read Page Information
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlImportLayout::readPage(TdkXmlItem *xmlItem)
{
	TdkXmlItem							*item=0;
	std::vector<TdkXmlItem*>::iterator	it;
	std::vector<TdkXmlItem*>			subItem;
	short								sCount=0;

	if(xmlItem == 0) return false;

	if((item=xmlItem->searchItem("PAGE")) == 0)	return false;
	
	subItem=item->getSubItem();
	for(it=subItem.begin();it!=subItem.end();it++)
	{
		if( TeConvertToUpperCase((*it)->getName()) == "SIZE" )
		{
			_pageSize=atoi((*it)->getValue().c_str());
			sCount++;
		}else if( TeConvertToUpperCase((*it)->getName()) == "WIDTH" )
		{
			_pageWidth=atoi((*it)->getValue().c_str());
			sCount++;
		}else if( TeConvertToUpperCase((*it)->getName()) == "HEIGHT" )
		{
			_pageHeight=atoi((*it)->getValue().c_str());
			sCount++;
		}else if( TeConvertToUpperCase((*it)->getName()) == "ORIENTATION" )
		{
			_pageOrientation=atoi((*it)->getValue().c_str());
			sCount++;
		}
	}
	return (sCount == 4 ? true : false);
}


///////////////////////////////////////////////////////////////////////////////
//Open XML File Settings
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlImportLayout::open(const std::string &fileName)
{
	xmlTextReaderPtr	xml;
	TdkXmlItem*			xmlMemory=0;
	_errorMessage.clear();
	if((xml=openXmlFile(fileName)) != 0)
	{
		xmlMemory=new TdkXmlItem();
		loadToMemory(xml,xmlMemory);
		xmlTextReaderClose(xml);
		if(readHeader(xmlMemory) == true)
		{
			if(checkHeader() == true)
			{
				if(readPage(xmlMemory) == true)
				{
					if(setLayoutPage() == true)
					{
						std::vector<TdkXmlItem*> objs=this->getObjects(xmlMemory);
						if(checkObjects(objs) == true)
						{
							return createLayoutObjects(objs);
						}
						else _errorMessage="Invalid layout objects";
					}
				}else _errorMessage="Error to read page settings";
			}
		}else _errorMessage="Invalid xml header of file";
		delete xmlMemory;
	}else
		_errorMessage="Error to open xml file";
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Verify file header
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlImportLayout::checkHeader()
{
	if(_version != __version)
	{
		_errorMessage="Invalid file version";
		return false;
	}
	
	if(TeConvertToUpperCase(_application) != TeConvertToUpperCase(__application))
	{
		_errorMessage="Invalid file application";
		return false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Sets page's layout
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlImportLayout::setLayoutPage()
{
	if(_controller == 0) 
	{
		_errorMessage="Invalid null controller";
		return false;
	}
	_controller->newPage();
	_controller->setPaperOrientation((short) _pageOrientation);
	_controller->setPaperSize((short) _pageSize);
	_controller->recompose();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Check whether quantity of objecst is equal the number read at header
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

bool TdkXmlImportLayout::checkObjects(std::vector<TdkXmlItem*> objs)
{
	return (objs.size() == _objectQtd ? true : false);
}

///////////////////////////////////////////////////////////////////////////////
//Returns the objects list
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
std::vector<TdkXmlItem*> TdkXmlImportLayout::getObjects(TdkXmlItem* xmlItem)
{
	TdkXmlItem								*item;
	std::vector<TdkXmlItem*>				subItem;
	std::vector<TdkXmlItem*>::iterator		it;
	std::vector<TdkXmlItem*>				objects;


	if((item=xmlItem->searchItem("LAYOUT")) == 0)	return objects;

	subItem=item->getSubItem();
	for(it=subItem.begin();it!=subItem.end();it++)
	{
			if(TeConvertToUpperCase((*it)->getName()) == "OBJECT")
				objects.push_back((*it));
	}
	return objects;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the objects list from memory
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
std::vector<TdkXmlItem*> TdkXmlImportLayout::getObjectsFromMemory(TdkXmlItem* xmlItem)
{
	std::vector<TdkXmlItem*>				subItem;
	std::vector<TdkXmlItem*>::iterator		it;
	std::vector<TdkXmlItem*>				objects;

	subItem=xmlItem->getSubItem();
	for(it=subItem.begin();it!=subItem.end();it++)
	{
			if(TeConvertToUpperCase((*it)->getName()) == "OBJECT")
				objects.push_back((*it));
	}
	return objects;
}

///////////////////////////////////////////////////////////////////////////////
//Create the layout objects
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

bool TdkXmlImportLayout::createLayoutObjects(std::vector<TdkXmlItem*> objs,const bool &fromMemory, const double &dx, const double &dy, const bool &isSelected)
{
	std::vector<TdkXmlItem*>::iterator		it;
	TdkXmlItem*								element;
	TdkLayoutObject							*layoutObj;

	if(_controller == 0) return false;
	for(it=objs.begin();it!=objs.end();it++)
	{
		if((element=(*it)->searchItem("TYPE")) != 0)
		{
			if((layoutObj=_controller->createLayoutObject((short) atoi(element->getValue().c_str()))) != 0)
			{
				if(setLayoutObject(layoutObj, (*it), fromMemory)) 
				{
					if( (dx != 0) && (dy !=0) ) displacement(layoutObj,dx,dy);
					_controller->insertObjectToList(layoutObj,isSelected);
					layoutObj=0;
				}else if(layoutObj != 0)
				{
					delete layoutObj;
				}
			}
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Sets the properties for layout object
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlImportLayout::setLayoutObject(TdkLayoutObject *obj, TdkXmlItem *item,const bool &fromMemory)
{
	TdkXmlItem*								properties;
	std::vector<TdkXmlItem*>				subItem;
	TdkXmlItem								*idItem;
	TdkXmlItem								*nameItem;
	std::vector<TdkXmlItem*>::iterator		it;
	TdkAbstractProperty						*prop;

	if(obj == 0) return false;
	
	if((properties=item->searchItem("PROPERTIES")) == 0) return false;

	if(	((idItem=item->searchItem("ID")) != 0) && (fromMemory == false) )
	{
		obj->setId(atoi(idItem->getValue().c_str()));
	}

	if( ((nameItem=item->searchItem("NAME")) != 0 ) && (fromMemory == false))
	{
		obj->setName(nameItem->getValue());
	}
	
	subItem=properties->getSubItem();
	for(it=subItem.begin();it!=subItem.end();it++)
	{
		if((prop=obj->getPropertyValue((*it)->getName())) != 0)
		{
			switch(prop->getType())
			{
				case PNumber:	
								prop->setValue((double)atof((*it)->getValue().c_str()));
								break;
				case PText:		
								prop->setValue(convertOutput((*it)->getValue(),_ENCODING_IMPORT)); 
								break;
				case PBoolean:	
								prop->setValue(( atoi((*it)->getValue().c_str()) == 0 ? false : true));
								break;
				case PColor:	
								prop->setValue((unsigned char) atoi((*it)->getValue().c_str()));
								break;
				case PBinary:	
								prop->setValue((*it)->getValue());
								break;
			}
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Convert text from specific encoding
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
std::string TdkXmlImportLayout::convertOutput(const std::string &strIn, const char *encoding)
{
	std::string		result;
    xmlChar *out;
	xmlChar *in;
    int ret;
    int size;
    int out_size;

	result=strIn;

    xmlCharEncodingHandlerPtr handler;
	size=(int)strIn.size() + 1;
	in=(unsigned char*)xmlMalloc((size_t) size);
	strcpy((char*)in,strIn.c_str());
	if (in == 0)	return result;

	handler = xmlFindCharEncodingHandler(encoding);
	if (!handler) 
	{
		_errorMessage="ConvertInput: no encoding handler found for ";
		_errorMessage+= (encoding ? encoding : "");
        return result;
    }
	out=(unsigned char*)xmlMalloc((size_t) size);
	out_size=size;
	if (out != 0) 
	{
		ret = handler->output(out,&out_size,in,&size);
		result=std::string((char*)out);
		xmlFree(out);
	}
	xmlFree(in);
	return result;
}


///////////////////////////////////////////////////////////////////////////////
//importFromMemory
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlImportLayout::importFromMemory(unsigned char *buffer, const unsigned int &size, const double &dx, const double &dy,const bool &isSelected)
{
	xmlTextReaderPtr	xml;
	TdkXmlItem*			xmlMemory=0;
	TdkXmlItem*			root;
	bool				status;

	if( (xml=xmlReaderForMemory((const char*) buffer, (int) size,0,_ENCODING_IMPORT,XML_PARSE_NOBLANKS)) == 0 )
		return false;

	xmlMemory=new TdkXmlItem();
	loadToMemory(xml,xmlMemory);
	if((root=xmlMemory->searchItem("ROOT")) == 0) return false;
	std::vector<TdkXmlItem*> objs=this->getObjectsFromMemory(root);
	status=createLayoutObjects(objs,true,dx,dy,isSelected);
	if(xmlMemory)	delete xmlMemory;
	return status;
}

///////////////////////////////////////////////////////////////////////////////
//set object displacement
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkXmlImportLayout::displacement(TdkLayoutObject *obj, const double &dx, const double &dy)
{
	TeBox		box;
	if(obj == 0 ) return;

	box=obj->getBox();
	box=TeBox( box.x1() + dx, box.y1() + dy, box.x2() + dx, box.y2() + dy);
	obj->setBoundingBox(box);
}