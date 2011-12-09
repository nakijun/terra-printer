#include <TdkGdiPoint.h>
#include <TdkGdiLine.h>
#include <TdkGdiPolygon.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiPolygon::TdkGdiPolygon()
{
	_lineStyle=new TdkGdiLine();
	_polygonDecorator=NULL;
	_brush=new SolidBrush(Color(255,0,0));
}

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiPolygon::TdkGdiPolygon(TdkGdiLine *line)
{
	_lineStyle=line;
	_polygonDecorator=NULL;
	_brush=new SolidBrush(Color(255,0,0));
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiPolygon::~TdkGdiPolygon()
{
	if(_lineStyle)				delete _lineStyle;
	if(_polygonDecorator)		delete _polygonDecorator;
	if(_brush)					delete _brush;
}

///////////////////////////////////////////////////////////////////////////////
//draw a polygon
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPolygon::draw(GraphicsPath* polygon, Graphics* graphic)
{
	if(graphic!=NULL)
	{
		if(_brush)	graphic->FillPath(_brush,polygon);
		if(_lineStyle!=NULL)
		{
			_lineStyle->draw(polygon,graphic);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets the back color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPolygon::setColor(const Color &color)
{
	BrushType type;
	HatchStyle style;

	if(!_brush)	return;
	style=((HatchBrush*)_brush)->GetHatchStyle();
	type=_brush->GetType();

	if(_brush)	delete _brush;

	if(type == BrushTypeSolidColor)
	{
		_brush=new SolidBrush(color);
	}else 
	{	
		_brush=new HatchBrush(style,color,Color(0,0,0,0));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets the alpha color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPolygon::setAlpha(const int &alpha)
{
	Color	color;
	if(_brush)
	{
		((SolidBrush*)_brush)->GetColor(&color);
		((SolidBrush*)_brush)->SetColor(Color(alpha,color.GetR(),color.GetG(),color.GetB()));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets the border color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPolygon::setBorderColor(const Color &color)
{
	if(_lineStyle)
	{
		_lineStyle->setColor(color);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets the border alpha color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPolygon::setBorderAlpha(const int &alpha)
{
	if(_lineStyle)
	{
		_lineStyle->setAlpha(alpha);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets the border type
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPolygon::setBorderType(const LineSettings::DashStyle &type)
{
	if(_lineStyle)
	{
		_lineStyle->setType(type);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets the border width
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPolygon::setBorderWidth(const int &width)
{
	if(_lineStyle)
	{
		_lineStyle->setWidth((REAL)width);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets line style
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPolygon::setLine(TdkGdiLine* line)
{
	if(_lineStyle)	delete _lineStyle;
	_lineStyle=line;
}

///////////////////////////////////////////////////////////////////////////////
//Clear Line Style
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPolygon::clearLine()
{
	if(_lineStyle) delete _lineStyle;
	_lineStyle=NULL;
}

///////////////////////////////////////////////////////////////////////////////
//Clear Decorator
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

void TdkGdiPolygon::clearDecorator()
{
	if(_polygonDecorator) delete _polygonDecorator;
	_polygonDecorator=NULL;
}

///////////////////////////////////////////////////////////////////////////////
//Adding a new TdkGdiPolygon Decorator
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPolygon::add(TdkGdiPolygon* dec)
{
	if(_polygonDecorator) delete _polygonDecorator;
	_polygonDecorator=dec;
}

///////////////////////////////////////////////////////////////////////////////
//Sets the back ground type
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPolygon::setType(const backgroundStyle &type)
{
	Color	color;
	if(_brush)
	{
		if(_brush->GetType()==BrushTypeHatchFill)
		{
			((HatchBrush*)_brush)->GetForegroundColor(&color);
		}
		else
		{	
			((SolidBrush*)_brush)->GetColor(&color);
		}
	}

	if(_brush) delete _brush;
	

	if(type == Solid)
	{ 
		_brush=new SolidBrush(color);
	}else if(type == Transparent)
	{
		_brush=NULL;	
	}else
	{
		_brush=new HatchBrush((HatchStyle)type,color,Color(0,0,0,0));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Returns the current brush
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
Brush* TdkGdiPolygon::getBrush()
{
	return _brush;
}

///////////////////////////////////////////////////////////////////////////////
//Return the current Pen
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
Pen* TdkGdiPolygon::getPen()
{
	if(!_lineStyle)
	{
		_lineStyle=new TdkGdiLine();
	}
	return _lineStyle->getPen();
}

///////////////////////////////////////////////////////////////////////////////
//drawRectangle
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPolygon::drawRectangle(Graphics* graphic, const RectF &rect, const bool &xorOption)
{
	if(graphic)
	{
		if(!xorOption)	graphic->DrawRectangle(getPen(),rect);
		else			drawXorRectangle(graphic,rect);
	}
}

///////////////////////////////////////////////////////////////////////////////
//drawXorRectangle
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPolygon::drawXorRectangle(Graphics* graphic, const RectF &rect)
{

			Gdiplus::Region region;
			HRGN rgn;
			graphic->GetClip(&region);
			rgn = region.GetHRGN(graphic);

			// Extract the Win32 HDC from the Graphics object supplied.
			HDC hdc = graphic->GetHDC();
			
			// Create a pen with a dotted style to draw the border of the
			// rectangle.
			HPEN gdiPen = CreatePen(PS_SOLID,1,RGB(128,128,128));

			
    		SelectClipRgn(hdc,rgn);
			
			// Set the ROP cdrawint mode to XOR.
			SetROP2( hdc, R2_XORPEN );
			
			// Select the pen into the device context.
			HPEN oldPen =(HPEN) SelectObject( hdc, gdiPen );
			
			// Create a stock NULL_BRUSH brush and select it into the device
			// context so that the rectangle isn't filled.
			HBRUSH oldBrush =(HBRUSH) SelectObject( hdc, GetStockObject( NULL_BRUSH ) );
			
			// Now XOR the hollow rectangle on the Graphics object with
			// a dotted outline.
			Rectangle( hdc,(int) rect.X, (int) rect.Y, (int)(rect.X + rect.Width),(int)(rect.Y + rect.Height));
			
			// Put the old stuff back where it was.
			SelectObject( hdc, oldBrush ); // no need to delete a stock object
			SelectObject( hdc, oldPen );
			DeleteObject( gdiPen );		// but we do need to delete the pen
			
			DeleteObject(rgn);
			SelectClipRgn(hdc,0);
			// Return the device context to Windows.
			graphic->ReleaseHDC(hdc);

}