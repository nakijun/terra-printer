#include<TdkPageSize.h>
#include <TdkObjectTypes.h>
#include <TdkAbstractProperty.h>
#include<TdkLayoutController.h>

#include <TdkXmlExportLayout.h>
#include <TdkLayoutObject.h>
#include <TdkLayoutObjectList.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

TdkXmlExportLayout::TdkXmlExportLayout(TdkLayoutController *control)
{
	_controller=control;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
TdkXmlExportLayout::~TdkXmlExportLayout()
{
	_controller=0;
	 xmlMemoryDump();
}

///////////////////////////////////////////////////////////////////////////////
//Export Header
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlExportLayout::exportHeader(xmlTextWriterPtr xml)
{
	xmlChar		*msg=0;

	if(xmlTextWriterStartDocument(xml, NULL, _ENCODING_EXPORT, NULL)<0)
	{
		_errorMessage="Error at write xml encoding";
		return false;
	}

	if(xmlTextWriterStartElement(xml, BAD_CAST "Layout")<0)
	{
		_errorMessage="Error at write Layout Header";
		return false;
	}
	if((msg=ConvertInput("TePrinter Layout Export",_ENCODING_EXPORT)) == 0)
	{
		_errorMessage="Error to alloc memory to xml message";
		return false;
	}
	if(xmlTextWriterWriteComment(xml,msg)<0)
	{
		_errorMessage="Error to write header comments";
		if(msg != 0) xmlFree(msg);
		return false;
	}

	if(msg != 0) xmlFree(msg);
	xmlTextWriterStartElement(xml, BAD_CAST "Header");
	if(xmlTextWriterWriteElement(xml, BAD_CAST "version",BAD_CAST "1.0")<0)
	{
		_errorMessage="Error to write header version";
		return false;
	}
	if(xmlTextWriterWriteElement(xml, BAD_CAST "Application",BAD_CAST "TePrinter")<0)
	{
		_errorMessage="Error to write header Application";
		return false;
	}

	if((msg=ConvertInput("Rui Maurício Gregório",_ENCODING_EXPORT)) == 0)
	{
		_errorMessage="Error to alloc memory to xml message";
		return false;
	}
	if(xmlTextWriterWriteElement(xml, BAD_CAST "Author",msg)<0)
	{
		_errorMessage="Error to write header Author";
		xmlFree(msg);
		return false;
	}
	if(msg != 0) xmlFree(msg);
	if(_controller)
	{
		if(xmlTextWriterWriteFormatElement(xml, BAD_CAST "Objects","%d",_controller->getObjectCount())<0)
		{	
			_errorMessage="Error to write header object quantity";
			return false;
		}
	}
	xmlTextWriterEndElement(xml);
	
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Export Page Information
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlExportLayout::exportPage(xmlTextWriterPtr xml)
{
	double width,height;

	xmlTextWriterStartElement(xml, BAD_CAST "Page");

	if(xmlTextWriterWriteFormatElement(xml, BAD_CAST "Size","%d",_controller->getPaperSize())<0)
	{
		_errorMessage="Error to write page size";
		return false;
	}
	_controller->getPaperSize(width,height);
	if(xmlTextWriterWriteFormatElement(xml, BAD_CAST "Width","%d",(int)width)<0)
	{
		_errorMessage="Error to write page width";
		return false;
	}
	if(xmlTextWriterWriteFormatElement(xml, BAD_CAST "Height","%d",(int)height)<0)
	{
		_errorMessage="Error to write page height";
		return false;
	}
	if(xmlTextWriterWriteFormatElement(xml, BAD_CAST "Orientation","%d",(int)_controller->getPaperOrientation())<0)
	{
		_errorMessage="Error to write page orientation";
		return false;
	}
	xmlTextWriterEndElement(xml);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Export Single Layout Object
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlExportLayout::exportSingleObject(TdkLayoutObject *obj, xmlTextWriterPtr xml)
{
	if(obj == 0) return false;
	
	xmlTextWriterStartElement(xml, BAD_CAST "Object");
	
	if(xmlTextWriterWriteFormatElement(xml, BAD_CAST "Type","%d",obj->getType())<0)
	{
		_errorMessage="Error to write object type";
		return false;
	}

	if(xmlTextWriterWriteFormatElement(xml, BAD_CAST "Id","%d",obj->getId())<0)
	{
		_errorMessage="Error to write object id";
		return false;
	}

	if(xmlTextWriterWriteElement(xml, BAD_CAST "Name", BAD_CAST obj->getName().c_str())<0)
	{
		_errorMessage="Error to write object" + obj->getName();
		return false;
	}
	exportPropertyList(obj->getProperties(),xml);
	xmlTextWriterEndElement(xml);
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Export List of properties
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlExportLayout::exportPropertyList(std::vector<TdkAbstractProperty*> properties,xmlTextWriterPtr xml)
{
	std::vector<TdkAbstractProperty*>::iterator	it;
	bool											status=false;

	xmlTextWriterStartElement(xml, BAD_CAST "Properties");
	for(it=properties.begin();it!=properties.end();it++)
	{
		status|=exportSingleProperty((*it),xml);
	}
	xmlTextWriterEndElement(xml);
	return status;
}

///////////////////////////////////////////////////////////////////////////////
//Export Single Property
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

bool TdkXmlExportLayout::exportSingleProperty(TdkAbstractProperty* prop,xmlTextWriterPtr xml)
{
	if(prop == 0) return false;

	if(prop->getType() == PNumber) 
	{
		double value;
		prop->getValue(value);
		if(xmlTextWriterWriteFormatElement(xml, BAD_CAST prop->name().c_str(),"%f",value)<0)
		{
			_errorMessage="Error to write " + prop->name();
			return false;
		}
	}else if(prop->getType() == PText)
	{
		std::string		value;
		xmlChar			*msg=0;

		prop->getValue(value);
		if((msg=ConvertInput(value.c_str(),_ENCODING_EXPORT)) == 0)
		{
			_errorMessage="Error to alloc memory to xml message";
			return false;
		}
		if(xmlTextWriterWriteElement(xml, BAD_CAST prop->name().c_str(), msg)<0)
		{
			_errorMessage="Error to write " + prop->name();
			if(msg)	xmlFree(msg);
			return false;
		}
		if(msg)	xmlFree(msg);
	}else if(prop->getType() == PColor)
	{
		unsigned char value;
		prop->getValue(value);
		if(xmlTextWriterWriteFormatElement(xml, BAD_CAST prop->name().c_str(),"%d",value)<0)
		{
			_errorMessage="Error to write " + prop->name();
			return false;
		}
	}else if(prop->getType() == PBoolean)
	{
		bool value;
		prop->getValue(value);
		if(xmlTextWriterWriteFormatElement(xml, BAD_CAST prop->name().c_str(),"%d",value)<0)
		{
			_errorMessage="Error to write " + prop->name();
			return false;
		}
	}else if(prop->getType() == PBinary)
	{
		unsigned char *value;
		unsigned long size;
		value=prop->getArrayValue(size);
		if(value != 0)
		{
			int written;
			xmlTextWriterStartElement(xml, BAD_CAST prop->name().c_str());
			if((written=xmlTextWriterWriteBinHex(xml,(const char*)value,0,(int)size))<0)
			{
				_errorMessage="Error to write " + prop->name();
				delete value;
				return false;
			}
			xmlTextWriterEndElement(xml);
			delete value;
		}
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Export All Objects in Layout
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlExportLayout::exportObjectList(TdkLayoutObjectList *objList, xmlTextWriterPtr xml)
{
	objectList					list;
	objectList::iterator		it;

	list=objList->getList();
	if(list.empty()) return false;
	for(it=list.begin();it!=list.end();it++)
	{
		exportSingleObject((*it),xml);
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Export select Objects in Layout
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlExportLayout::exportSelectObjectList(TdkLayoutObjectList *objList, xmlTextWriterPtr xml)
{
	objectList					list;
	objectList::iterator		it;

	list=objList->getSelectObject();
	if(list.empty()) return false;
	for(it=list.begin();it!=list.end();it++)
	{
		exportSingleObject((*it),xml);
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Open
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
xmlTextWriterPtr TdkXmlExportLayout::open(const std::string &fileName)
{
	xmlTextWriterPtr xml;
	xml=xmlNewTextWriterFilename((char*)fileName.c_str(), 0);
	return xml;
}

///////////////////////////////////////////////////////////////////////////////
//Save
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlExportLayout::save(const std::string &fileName)
{
	xmlTextWriterPtr	xml;
	bool				status=false;

	_errorMessage.clear();
	if(fileName.empty())
	{
		_errorMessage="Invalid null file name";
		return false;
	}

	if((xml=this->open(fileName)))
	{
		if(exportHeader(xml) == true)
		{
			if(exportPage(xml) == true)
			{
				if(_controller)
				{
					if(this->exportObjectList(_controller->getList(),xml))
					{
						status=true;
					}
				}else status=true;
			}
		}
	}
	xmlTextWriterEndDocument(xml);	
	xmlFreeTextWriter(xml);
	return status;
}

///////////////////////////////////////////////////////////////////////////////
//exportToMemory
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
unsigned char* TdkXmlExportLayout::exportToMemory(unsigned int &size)
{
	xmlTextWriterPtr	xml;
	xmlBufferPtr		buf;
	unsigned char		*result=0;
	bool				status=false;


	buf = xmlBufferCreate();
    if (buf == NULL) 
	{
        _errorMessage="Error creating the xml buffer";
        return 0;
    }

    xml = xmlNewTextWriterMemory(buf, 0);
    if (xml == NULL) 
	{
        _errorMessage="Error creating the xml writer";
        return 0;
    }
    if(xmlTextWriterStartDocument(xml, NULL, _ENCODING_EXPORT, NULL)>=0)
	{
		xmlTextWriterStartElement(xml,BAD_CAST "ROOT");
		if(_controller)
		{
			status=this->exportSelectObjectList(_controller->getList(),xml);
		}
		xmlTextWriterEndElement(xml);
		xmlTextWriterEndDocument(xml);
		size=buf->use;
		result=new unsigned char[size];		
	}
	xmlFreeTextWriter(xml);
	memcpy(result,buf->content,sizeof(unsigned char) * size);
	xmlBufferFree(buf);
	if(status == false) 
	{
		delete result;
		result=0;
		size=0;
	}
	return result;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the error message
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
std::string TdkXmlExportLayout::getErrorMessage()
{
	return _errorMessage;
}

///////////////////////////////////////////////////////////////////////////////
//Convert Input  string according encoding
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
xmlChar* TdkXmlExportLayout::ConvertInput(const char *in, const char *encoding)
{
    xmlChar *out;
    int ret;
    int size;
    int out_size;
    int temp;

    xmlCharEncodingHandlerPtr handler;

    if (in == 0)	return 0;
    handler = xmlFindCharEncodingHandler(encoding);

    if (!handler) 
	{
		_errorMessage="ConvertInput: no encoding handler found for ";
		_errorMessage+= (encoding ? encoding : "");
        return 0;
    }
    size = (int) strlen(in) + 1;
    out_size = size * 2 - 1;
    out = (unsigned char *) xmlMalloc((size_t) out_size);
    if (out != 0) 
	{
        temp = size - 1;
        ret = handler->input(out, &out_size, (const xmlChar *) in, &temp);
        if ((ret < 0) || (temp - size + 1)) 
		{
            _errorMessage="ConvertInput: conversion wasn't successful.";
            xmlFree(out);
            out = 0;
        } else 
		{
            out = (unsigned char *) xmlRealloc(out, out_size + 1);
            out[out_size] = 0;  
        }
    } 
	else 
	_errorMessage="ConvertInput: no mem\n";
    return out;
}

