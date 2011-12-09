/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkGdiText.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/08/07 11:34:38 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_GDI_TEXT_H
#define __TDK_GDI_TEXT_H

#include <windows.h>
#include <gdiplus.h>
#include <string>

using namespace Gdiplus;
using namespace std;

class TdkGdiText
{
public :
	enum horzAlignment
	{
		leftHorz,			centerHorz,			rightHorz
	};

	enum vertAlignment
	{
		bottomVert,			centerVert,			topVert
	};

protected:
	Font*			_font;

	FontFamily*		_fontFamily;

	Brush*			_brush;

	Brush*			_backGroundBrush;

	double			_angle;

	horzAlignment	_horizontalAlign;

	vertAlignment	_verticalAlign;
	
protected:
	virtual std::wstring transformString2WChar(const std::string &text);

	virtual RectF getRectangle(const double &x, const double &y,const SizeF &size);

	virtual void getPointRotate(const RectF &rect, PointF &ptRotate, PointF &ptOrig);

	
public:

	TdkGdiText();

	~TdkGdiText();


	virtual void draw(const double &x, const double &y,const std::string &text, Graphics *graphic);

	virtual void draw(const RectF &box,const std::string &text, Graphics *graphic);

	virtual void setColor(const Color &color);

	virtual void setBackColor(const Color &color);

	virtual void setAlpha(const int &alpha);

	virtual void setBackAlpha(const int &alpha);

	virtual void setFontName(const std::string &name);

	virtual void setFontSize(const float &size);

	virtual void setAngle(const double &angle);

	virtual void setTextBold(const bool &b);

	virtual void setTextItalic(const bool &it);

	virtual void setHorizontalAligment(const horzAlignment &align);

	virtual void setVerticalAlignment(const vertAlignment &align);

	virtual SizeF MeasureString(const std::string &text, Graphics *graphic);
	
	virtual double getHeightFontMetrics(const std::string &text);
};



#endif

