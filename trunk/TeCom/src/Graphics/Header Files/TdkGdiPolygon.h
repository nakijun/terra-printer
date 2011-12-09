/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkGdiPolygon.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/07/17 11:09:51 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_GDI_POLYGON_H
#define __TDK_GDI_POLYGON_H

#include "TdkCanvasTypes.h"

class TdkGdiLine;

using namespace PolygonSettings;

class TdkGdiPolygon
{
protected:
	//!< line style to polygon contour
	TdkGdiLine*		_lineStyle;
	//!< polygon decorator
	TdkGdiPolygon*	_polygonDecorator;
	//! brush point to polygon draw
	Brush*			_brush;

protected:

	void drawXorRectangle(Graphics* graphic, const RectF &rect);
	
public:
	//! \brief Empty Constructor
	TdkGdiPolygon();

	//! \brief Constructor
	/*! Constructor with line pointer to contour
	*/
	TdkGdiPolygon(TdkGdiLine* line);

	//! \brief Destructor
	~TdkGdiPolygon();

	//! \brief draw
	/*! Method to draw a polygon
		\param	polygon		polygon (path)
		\param	graphic		graphic pointer
	*/
	virtual void draw(GraphicsPath* polygon, Graphics* graphic);
	
	//! \brief setColor
	/*! Method to set the polygon background color
		\param	color		background color
	*/
	virtual void setColor(const Color &color);

	//! \brief setAlpha
	/*! Method to set the alpha channel
		\param	alpha	alpha value
	*/
	virtual void setAlpha(const int &alpha);

	//! \brief setBorderColor
	/*! Method to set the polygon border color
		\param	color		border color value
	*/
	virtual void setBorderColor(const Color &color);

	//! \brief setBorderAlpha
	/*! Method to set the border alpha value
		\param	alpha	alpha value
	*/
	virtual void setBorderAlpha(const int &alpha);

	//! \brief setBorderType
	/*! Method to set the border type (line style)
		\param	type		border type value
	*/
	virtual void setBorderType(const LineSettings::DashStyle &type);


	//! \brief setBorderWidth
	/*! Method to set the width border for polygon
		\param	width		integer value
	*/
	virtual void setBorderWidth(const int &width);

	//! \brief setLine
	/*! Method to associate the line style to
		border polygon
		\param	line		line pointer
	*/
	virtual void setLine(TdkGdiLine* line);

	//! \brief clearLine
	/*! Method to remove from memory the line
		pointer associate with polygon border
	*/
	virtual void clearLine();

	//! \brief clearDecorator
	virtual void clearDecorator();

	//! \brief add
	/*! Method to add a polygon decorator
		to draw the polygon with new style
		\param	dec		decorator pointer
	*/
	virtual void add(TdkGdiPolygon* dec);

	//! \brief setType
	/*! Method to set the background type
	*/
	virtual void setType(const backgroundStyle &type);

	//! \brief getBrush
	/*! Method to return the brush pointer
		associate with gdi polygon
		\return	returns the Gdiplus Brush pointer
	*/
	virtual Brush* getBrush();

	//! \brief getPen
	/*! Method to return the pen pointer
		associate with gdi polygon used to
		draw the border
		\param	returns the Gdiplus pen pointer
	*/
	virtual Pen* getPen();

	virtual void drawRectangle(Graphics* graphic, const RectF &rect, const bool &xorOption=false);
};

#endif

