/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkXmlPoliticalDivision.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/09/09 18:58:37 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_XML_POLITICAL_DIVISION_H
#define __TDK_XML_POLITICAL_DIVISION_H


#include <string>
#include <libxml/xmlreader.h>
#include <tegeometry.h>


#ifdef LIBXML_READER_ENABLED


class TdkXmlItem;


/*! \class TdkXmlPoliticalDivision
	class to load the political division
	from gml file
*/
class TdkXmlPoliticalDivision
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
		Undefined = 14,			//!<	Undefined type
		EndElement = 15			//!<	Node as end element
	};
protected :

	TePolygonSet		_plsStates;		//!< polygons list
	TeLineSet			_lnsStates;		//!< lines list
	TePointSet			_ptsStates;		//!< points list

protected:

	//! \brief openXmlFile
	/*! Method to open a xml file
		\param	fileName		file name
		\return		returns the xml pointer to file
	*/
	virtual xmlTextReaderPtr openXmlFile(const std::string &fileName);


	//! \brief loadToMemory
	/*! Load all xml to memory
		in tree format
		\param	xml		xml pointer
		\param	item	xml item pointer
		\return	returns true whether sucess
	*/
	virtual bool loadToMemory(xmlTextReaderPtr xml, TdkXmlItem* item);

	//! \brief getPolygons
	/*! Method to return the polygon list from
		xml item on memory
		\param		xmlItem		xml item in memory
		\return		returns the terralib polygon set
	*/
	virtual TePolygonSet getPolygons(TdkXmlItem* xmlItem);

	//! \brief decoderPolygon
	/*! Method to decoder the string value from gml
		in polygon
		\param	value		coordinates in string separation
		\return		returns the terralib polygon
	*/
	virtual TePolygon decoderPolygon(const std::string &value);

public :

	//! \brief Constructor
	TdkXmlPoliticalDivision();

	//! \brief Destructor
	~TdkXmlPoliticalDivision();

	//! \brief getPolygons
	/*! Returns the polygon list from
		gml file
	*/
	virtual TePolygonSet getPolygons();

	//! \brief getLines
	/*! Returns the lines list from
		gml file
	*/
	virtual TeLineSet	getLines();

	//! \brief getPoints
	/*! Returns the points list from
		gml file
	*/
	virtual TePointSet	getPoints();

	//! \brief open
	/*! Open gml file
	*/
	virtual bool open(const std::string &fileName);

	//! \brief isValid
	virtual bool isValid();

	virtual TeBox getBox();
};

#endif //LIBXML_READER_ENABLED

#endif //__TDK_XML_POLITICAL_DIVISION_H

