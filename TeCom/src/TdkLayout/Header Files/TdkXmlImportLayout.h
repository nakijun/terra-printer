/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkXmlImportLayout.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/09/16 14:03:11 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório


#ifndef __TDK_XML_IMPORT_LAYOUT_H
#define __TDK_XML_IMPORT_LAYOUT_H

#include <string>
#include <libxml/xmlreader.h>


#ifdef LIBXML_READER_ENABLED

//! forward
class TdkLayoutController;
class TdkXmlItem;
class TdkLayoutObject;

using namespace std;

#define __version "1.0"
#define __application "TePrinter"
#define _ENCODING_IMPORT "ISO-8859-1"

//! \class TdkXmlImportLayout
/*! 
	A class to import a xml file
	to set the layout
*/
class TdkXmlImportLayout
{
public :
	//! XmlNodeType
	/*! 
		Enum for node type
		*/
	enum XmlNodeType
	{
		Element = 1 ,			//!<	Node as element
		Text = 3,				//!<	Node as Text
		Comment = 8,			//!<	Node as Comments
		EndElement = 15,		//!<	Node as end element
	};
protected :

	TdkLayoutController*	_controller;		//!<	pointer controller

	std::string				_errorMessage;		//!<	string error Message

protected:

// Header Attributes
	std::string				_version;				//!<	xml layout version
	std::string				_application;			//!<	xml layout application
	unsigned int			_objectQtd;				//!<	xml quantity of layout objects

//! Page Attributes
	int						_pageSize;				//!<	xml layout page size
	int						_pageWidth;				//!<	xml layout page width
	int						_pageHeight;			//!<	xml layout page height
	int						_pageOrientation;		//!<	xml layout page orientation

public :

	//! \brief Constructor
	TdkXmlImportLayout(TdkLayoutController *control);

	//! \brief Destructor
	virtual ~TdkXmlImportLayout();

protected:

	//! \brief openXmlFile
	/*! Method to open a xml file
		\param	fileName		file name
		\return		returns the xml pointer to file
	*/
	virtual xmlTextReaderPtr openXmlFile(const std::string &fileName);

	//! \brief readHeader
	/*! Read a xml header
		\param	xmlItem		xml pointer in memory
		\return returns true whether sucess
	*/
	virtual bool readHeader(TdkXmlItem *xmlItem);

	//! \brief readPage
	/*! Read from xml in memory
		the page settings
		\param	xmlItem	xml pointer in memory
		\return returns true whether sucess
	*/
	virtual bool readPage(TdkXmlItem *xmlItem);

	//! \brief loadToMemory
	/*! Load all xml to memory
		in tree format
		\param	xml		xml pointer
		\param	item	xml item pointer
		\return	returns true whether sucess
	*/
	virtual bool loadToMemory(xmlTextReaderPtr xml, TdkXmlItem* item);

	//! \brief checkHeader
	/*! Verify whether header information has
		valids paramethers
		\return	returns true whether is valid header
	*/
	virtual bool checkHeader();

	//! \brief setLayoutPage
	/*! Sets layout page paramethers
		\return returns true whether sucess
	*/
	virtual bool setLayoutPage();

	//! \brief getObjects
	/*! Returns list of layout objects from xml
		\param	xmlItem		xml item pointer
		\return	returns the list of layout objects
	*/
	virtual std::vector<TdkXmlItem*> getObjects(TdkXmlItem* xmlItem);

	//! \brief getObjects from Memory
	/*! Returns list of layout objects from memory xml
		\param	xmlItem		xml item pointer
		\return	returns the list of layout objects
	*/
	virtual std::vector<TdkXmlItem*> getObjectsFromMemory(TdkXmlItem* xmlItem);

	//! \brief checkObjects
	/*! Verify is the valids objects
	*/
	virtual bool checkObjects(std::vector<TdkXmlItem*> objs);

	//! \brief createLayoutObjects
	virtual bool createLayoutObjects(std::vector<TdkXmlItem*> objs, const bool &fromMemory=false,const double &dx=0.0, const double &dy=0.0,const bool &isSelected=false);
	
	//! \brief set layout properties
	virtual bool setLayoutObject(TdkLayoutObject *obj, TdkXmlItem *item, const bool &fromMemory=false);

	//! \brief convert xml string from specific encoding
	virtual std::string convertOutput(const std::string &strIn, const char *encoding);

	//! \brief set object displacement
	virtual void displacement(TdkLayoutObject *obj, const double &dx, const double &dy);
public :
	//! \brief open
	/*! Open and sets the layout settings
		\param	fileName		xml file name
		\return returns true whether sucess
	*/
	virtual bool open(const std::string &fileName);

	//! \brief importFromMemory
	/*! Import layout objects from memory
		\param		buffer		xml data
		\param		size		buffer size
		\param		dx			displacement x
		\param		dy			displacement y
		\return		returns true whether sucess
	*/
	virtual bool importFromMemory(unsigned char *buffer, const unsigned int &size, const double &dx=0, const double &dy=0,const bool &isSelected=false);
};

#endif

#endif
