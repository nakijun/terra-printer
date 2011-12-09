/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkXmlExportLayout.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/09/14 14:52:12 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório


#ifndef __TDK_XML_EXPORT_LAYOUT_H
#define __TDK_XML_EXPORT_LAYOUT_H

#include <string>
#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>

#if defined(LIBXML_WRITER_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)

#define _ENCODING_EXPORT "ISO-8859-1"


using namespace std;


class TdkLayoutController;
class TdkLayoutObject;
class TdkLayoutObjectList;
class TdkAbstractProperty;


//! \class TdkXmlExportLayout
/*! Class to export the layout module
	to a xml file.
	This class will be export the
	page size, page orientation
	and all layout objects
*/
class TdkXmlExportLayout
{
protected :

	TdkLayoutController		*_controller;				//! layout controller

	std::string				_errorMessage;				//!	Error Message

public :

	//! \brief Constructor
	TdkXmlExportLayout(TdkLayoutController *control);

	//! \brief Destructor
	virtual ~TdkXmlExportLayout();

protected :

	//! \brief exportHeader
	/*! Create the header to xml file
		\param xml	xml pointer
	*/
	virtual bool exportHeader(xmlTextWriterPtr xml);

	//! \brief exportPage
	/*! Method to export the information about
		page layout
		\param		xml		xml pointer
		\return		returns true whether sucess
	*/
	virtual bool exportPage(xmlTextWriterPtr xml);

	//! \brief exportPropertyList
	/*! Method to export a properties list
		\param		properties			properties list
		\param		xml		xml pointer
		\return		returns true whether sucess
	*/
	virtual bool exportPropertyList(std::vector<TdkAbstractProperty*> properties,xmlTextWriterPtr xml);

	//! \brief exportSingleProperty
	/*! Method to export a single property
		to xml format
		\param		prop		property pointer
		\param		xml		xml pointer
		\return		returns true whether sucess
	*/
	virtual bool exportSingleProperty(TdkAbstractProperty* prop,xmlTextWriterPtr xml);

	//! \brief exportSingleObject
	/*! Method to export a single object
		\param	obj		single layout object
		\param		xml		xml pointer
		\return		returns true whether sucess
	*/
	virtual bool exportSingleObject(TdkLayoutObject *obj, xmlTextWriterPtr xml);

	//! \brief exportObjectList
	/*! Method to export the list of layout objects
		\param		objList		list of layout objects
		\param		xml		xml pointer
		\return		returns true whether sucess
	*/
	virtual bool exportObjectList(TdkLayoutObjectList *objList, xmlTextWriterPtr xml);

	//! \brief exportSelectObjectList
	/*! Method to export the list of selecteds layout objects
		\param		objList		list of layout objects
		\param		xml		xml pointer
		\return		returns true whether sucess
	*/
	virtual bool exportSelectObjectList(TdkLayoutObjectList *objList, xmlTextWriterPtr xml);

	//! \brief xmlTextWriterPtr
	/*! Open a xml file
		\param	fileName		file name
	*/
	virtual xmlTextWriterPtr open(const std::string &fileName);

	//! \ brief ConvertInput
	/*! Convert the string to correct xml encoding
		\param		in				string to conversion
		\param		encoding		encoding name
		\return		returns the new xml string according encoding
	*/
	virtual xmlChar* ConvertInput(const char *in, const char *encoding);
	
public :

	//! \brief Save
	/*! Save layout settings
		to xml file
		\param		fileName		file Name
		\return		returns true whether sucess
	*/
	virtual bool save(const std::string &fileName);

	//! \brief exportToMemory
	virtual unsigned char* exportToMemory(unsigned int &size);

	//! \brief getErrorMessage
	virtual std::string getErrorMessage();
	
};


#endif

#endif
