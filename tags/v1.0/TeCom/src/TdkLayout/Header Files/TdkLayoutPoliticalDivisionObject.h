/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutPoliticalDivisionObject.h
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

#ifndef __TDK_LAYOUT_POLITICAL_DIVISION_OBJECT_H
#define __TDK_LAYOUT_POLITICAL_DIVISION_OBJECT_H


#include <TdkLayoutObject.h>

class TdkAbstractCanvasDraw;
class TdkXmlPoliticalDivision;

#define _dpFileName			"estados.gml"
#define _initialPDPixmap	8192
#define __MaxPixmapSize		100000000

class TdkLayoutPoliticalDivisionObject : public  TdkLayoutObject
{
protected:
	
	TdkXmlPoliticalDivision				*_divisionFile;
	unsigned int						_mapPixmap;		//!< pixmap number used by object to draw the map
	TeBox								_window;
	TeBox								_fixedBox;

protected:
	//! \brief registerExtendProperties
	/*! Method to register your extend properties
	*/
	virtual void registerExtendProperties();

	virtual void drawErrorLine();

	virtual TeBox getMapViewport(TdkAbstractCanvasDraw * canvas);

	virtual void draw(TdkAbstractCanvasDraw * canvas, TdkXmlPoliticalDivision *layer);
public:

	TdkLayoutPoliticalDivisionObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box, const std::string &path);

	~TdkLayoutPoliticalDivisionObject();


	//! \brief Draw
	/*! Method to draw the text object on 
		Back Buffer
	*/
	virtual void draw();

	//! \brief print
	/*! Method to print the object
		\param	canvas		canvas pointer
	*/
	virtual void print(TdkAbstractCanvasDraw *canvas);
};



#endif


