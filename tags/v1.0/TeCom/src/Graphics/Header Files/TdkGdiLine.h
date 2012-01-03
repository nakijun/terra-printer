/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkGdiLine.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/07/17 11:09:50 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_GDI_LINE_H
#define __TDK_GDI_LINE_H

#include "TdkCanvasTypes.h"

class TdkGdiPoint;

using namespace LineSettings;

class TdkGdiLine
{
protected:
	
	TdkGdiPoint*				_pointStyle;		//!< attribute to draw line's point
	TdkGdiLine*					_lineDecorator;		//!< line decorator to draw a line with composite mode
	Pen*						_pen;				//!< pen to draw a line
	LineSettings::DashStyle		_type;				//!< dash type
public:
	//! \brief Constructor	
	TdkGdiLine();

	//! \brief Constructor
	/*! Constructor with point style
	*/
	TdkGdiLine(TdkGdiPoint *pointStyle);

	//! \brief Destructor
	virtual ~TdkGdiLine();

	//! \brief setColor
	/*! Method to set the line color
		\param	color		line color value
	*/
	virtual void setColor(const Color &color);

	//! \brief setType
	/*! Method to set the pen dash
		\param	type		dash line value
	*/
	virtual void setType(const LineSettings::DashStyle &type);

	//! \brief setWidth
	/*! Method to set width line
		\param	width		line's width value
	*/
	virtual void setWidth(const REAL &width);

	//! \brief dash
	/*! Method to set custom dash pattern
		\param	dashArray		array with dash values
		\param	size			dash values quantity
	*/
	virtual void dash(double *dashArray, const int &size);

	//! \brief add
	/*! Method to add a new TdkGdiLine to modify draw
		operation
		\param	decorator			TdkGdiLine pointer
	*/
	virtual void add(TdkGdiLine* decorator);

	//! \brief draw
	/*! Method to draw a line
		\param	line		line's points
		\param	size		quantity of point
		\param	graphic		graphic point to draw
		\param	xorOption	enable xor mode to draw
	*/
	virtual void draw(PointF *line, const int &size, Graphics *graphic, const bool &xorOption=false);

	//! \brief draw
	/*! Method to draw a segment line
		\param		x1			initial coordinate x
		\param		y1			initial coordinate y
		\param		x2			final coordinate x
		\param		y2			final coordinate y
	*/
	virtual void draw(const double &x1, const double &y1, const double &x2, const double &y2, Graphics *graphic);

	//! \brief draw
	/*! Method to draw a path
		\param	path		
		\param	graphic
	*/
	virtual void draw(GraphicsPath* path, Graphics* graphic);

	//! \brief setPointStyle
	/*! Method to set the point style to draw
		\param	pointStyle		pointer to draw a point
	*/
	virtual void setPointStyle(TdkGdiPoint *pointStyle);

	//! \brief setAlpha
	/*! Methodo to set the alpha value
		\param	alpha	alpha value
	*/
	virtual void setAlpha(const int &alpha);

	//! \brief clearPointStyle
	/*! Method to clear the point style
		associate with line
	*/
	virtual void clearPointStyle();

	//! \brief clearDecorator
	/*! Method to clear the decorator line
		associate with line
	*/
	virtual void clearDecorator();
	
	//! \brief getPen
	/*! Method to return the pen associate
		with draw process
		\return		returns pen pointer
	*/
	virtual Pen* getPen();

	//! \brief showPointLine
	/*! Method to set whether points of line
		will appear
		\param	value		boolean value
	*/
	virtual void showPointLine(const bool &value);

	//! \brief drawXorLine
	/*! Draw a line in xor mode 
		\param	graphic		gdi plus pointer
		\param	line		points line
		\param	size		line size
	*/
	virtual void drawXorLine(Graphics* graphic, PointF *line, const int &size );
};


#endif

