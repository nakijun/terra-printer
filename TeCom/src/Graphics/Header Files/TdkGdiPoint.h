/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkGdiPoint.h
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

#ifndef __TDK_GDI_POINT_H
#define __TDK_GDI_POINT_H

#include <windows.h>
#include <gdiplus.h>
#include "TdkCanvasTypes.h"

using namespace Gdiplus;
using namespace PointSettings;

class TdkGdiPoint
{
public :

protected:
	//!< Point Size attribute
	int						_pointSize;
	//!< Caracter to represent a point
	char					_pointChar;
	//<! Pen attribute
	Pen*					_pointPen;

	Brush*					_pointBrush;

	Font*					_fontCaracter;

	//<! New styleWO to draw
	TdkGdiPoint*			_pointDecorator;
	//!< Point type attribute
	pointType				_pointType;

protected:

	//! \brief drawCross
	/*! Method to draw a point such as cross format
		\param	x			center coordinate on axle x
		\param	y			center coordinate on axle y
		\param	graphic		graphic point to draw
	*/
	virtual void drawCross(const double &x, const double &y, Graphics *graphic);

	//! \brief drawCircle
	/*! Method to draw a point such as circle format
		\param	x			center coordinate on axle x
		\param	y			center coordinate on axle y
		\param	graphic		graphic point to draw
	*/
	virtual void drawCircle(const double &x, const double &y, Graphics *graphic);

	//! \brief drawFillCircle
	/*! Method to draw a point such as fill circle format
		\param	x			center coordinate on axle x
		\param	y			center coordinate on axle y
		\param	graphic		graphic point to draw
	*/
	virtual void drawFillCircle(const double &x, const double &y, Graphics *graphic);

	//! \brief drawDiagonalCross
	/*! Method to draw a point such as diagonal cross format
		\param	x			center coordinate on axle x
		\param	y			center coordinate on axle y
		\param	graphic		graphic point to draw
	*/
	virtual void drawDiagonalCross(const double &x, const double &y, Graphics *graphic);

	//! \brief drawSquare
	/*! Method to draw a point such as square format
		\param	x			center coordinate on axle x
		\param	y			center coordinate on axle y
		\param	graphic		graphic point to draw
	*/
	virtual void drawSquare(const double &x, const double &y, Graphics *graphic);

	//! \brief drawFillSquare
	/*! Method to draw a point such as fill square format
		\param	x			center coordinate on axle x
		\param	y			center coordinate on axle y
		\param	graphic		graphic point to draw
	*/
	virtual void drawFillSquare(const double &x, const double &y, Graphics *graphic);

	//! \brief drawCaracter
	/*! Method to draw a point such as caracter format
		\param	x			center coordinate on axle x
		\param	y			center coordinate on axle y
		\param	graphic		graphic point to draw
	*/
	virtual void drawCaracter(const double &x, const double &y, Graphics *graphic);

	//! \brief drawDiamond
	/*! Method to draw a point such as diamond format
		\param	x			center coordinate on axle x
		\param	y			center coordinate on axle y
		\param	graphic		graphic point to draw
	*/
	virtual void drawDiamond(const double &x, const double &y, Graphics *graphic);

	//! \brief drawFillDiamond
	/*! Method to draw a point such as fill diamond format
		\param	x			center coordinate on axle x
		\param	y			center coordinate on axle y
		\param	graphic		graphic point to draw
	*/
	virtual void drawFillDiamond(const double &x, const double &y, Graphics *graphic);

public:

	//! \brief Constructor
	TdkGdiPoint();
	
	//! Destructor
	~TdkGdiPoint();

	//! \brief Draw
	/*! Method to draw a point
		\param	x			coordinate on axle x
		\param	y			coordinate on axle y
		\param	graphic		Graphics pointer to draw
	*/
	virtual void draw(const double &x, const double &y, Graphics *graphic);

	//! \brief addDecorator
	/*! Method to add new styles to draw
		\param	dec		decorator pointer
	*/
	virtual void addDecorator(TdkGdiPoint *dec);

	//! \brief setColor
	/*! Method to set the color point to draw
		\param	color		Gdiplus color
	*/
	virtual void setColor(const Color &color);

	//! \brief setSize
	/*! Method to set point size to draw
		\param	size		point size value
	*/
	virtual void setSize(const int &size);

	//! \brief setChar
	/*! Method to set the caracter to represent a point
		\param		caracter		caracter value
	*/
	virtual void setChar(const char &caracter);

	//! \brief setType
	/*! Method to set the point type
		\param	type		point type value
	*/
	virtual void setType(const pointType &type);

	//! \brief setAlpha
	/*! Method to set the alpha value to color
		\param	alpha		alpha value
	*/
	virtual void setAlpha(const int &alpha);

	//! \brief Remove decorator pointer from memory
	virtual void clearDecorator();

};


#endif

