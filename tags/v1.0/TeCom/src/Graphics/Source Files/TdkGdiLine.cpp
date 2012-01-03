#include <TdkGdiPoint.h>
#include <TdkGdiLine.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiLine::TdkGdiLine()
{
	_pointStyle=NULL;
	_lineDecorator=NULL;
	_pen=new Pen(Color(255,0,0));
}

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiLine::TdkGdiLine(TdkGdiPoint *pointStyle)
{
	_pointStyle=pointStyle;
	_lineDecorator=NULL;
	_pen=new Pen(Color(255,0,0));
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiLine::~TdkGdiLine()
{
	if(_pointStyle!=NULL)		delete _pointStyle;
	if(_lineDecorator!=NULL)	delete _lineDecorator;
	if(_pen!=NULL)				delete _pen;
}

///////////////////////////////////////////////////////////////////////////////
//Sets Line Color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::setColor(const Color &color)
{
	if(_pen!=NULL)
	{
		_pen->SetColor(color);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets line type
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::setType(const LineSettings::DashStyle &type)
{
	_type=type;
	if(_pen!=NULL)
	{
		_pen->SetDashStyle((Gdiplus::DashStyle)_type);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets line width
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::setWidth(const REAL &width)
{
	if(_pen!=NULL)
	{
		_pen->SetWidth(width);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets Line Dash
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::dash(double *dashArray, const int &size)
{
	float *dash;
	int		i;

	if(_pen!=NULL)
	{
		 dash=new float[size];
		 for(i=0;i<size;i++) dash[i]=(REAL)dashArray[i];
		_pen->SetDashStyle(Gdiplus::DashStyleCustom);
		_pen->SetDashPattern(dash,size);
		delete dash;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Add Line Decorator
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::add(TdkGdiLine* decorator)
{
	if(_lineDecorator) delete _lineDecorator;
	_lineDecorator=decorator;
}

///////////////////////////////////////////////////////////////////////////////
//Draw a line
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::draw(PointF *line, const int &size, Graphics *graphic,const bool &xorOption)
{
	if((graphic!=NULL) && (_pen!=NULL))
	{
		if(xorOption)		drawXorLine(graphic,line,size);
		else
		{
			graphic->DrawLines(_pen,line,size);
			if(_pointStyle)
			{
				int i;
				for(i=0;i<size;i++)
				{
					_pointStyle->draw(line[i].X,line[i].Y,graphic);
				}
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a Line Path
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::draw(GraphicsPath* path, Graphics* graphic)
{
	if((graphic!=NULL) && (_pen!=NULL))
	{
		graphic->DrawPath(_pen,path);
		if(_pointStyle)
		{
			int			pointCount;
			int			i;
			PointF		*points;
			pointCount=path->GetPointCount();
			points=new PointF[pointCount];
			path->GetPathPoints(points,pointCount);
			for(i=0;i<pointCount;i++)
			{
				_pointStyle->draw(points[i].X,points[i].Y,graphic);
			}
			delete []points;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set Line Point Style
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::setPointStyle(TdkGdiPoint *pointStyle)
{
	if(_pointStyle) delete _pointStyle;
	_pointStyle=pointStyle;
}

///////////////////////////////////////////////////////////////////////////////
//Clear Line Point Style
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::clearPointStyle()
{
	if(_pointStyle!=NULL)
	{
		delete _pointStyle;
		_pointStyle=NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Clear Line Decorator
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::clearDecorator()
{
	if(_lineDecorator!=NULL) 
	{
		delete _lineDecorator;
		_lineDecorator=NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets Line alpha
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::setAlpha(const int &alpha)
{
	if(_pen!=NULL)
	{
		Color color;
		_pen->GetColor(&color);
		_pen->SetColor(Color(color.GetR(),color.GetG(),color.GetB(),alpha));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a fill square
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::draw(const double &x1, const double &y1, const double &x2, const double &y2,Graphics *graphic)
{
	graphic->DrawLine(_pen,(REAL)x1,(REAL)y1,(REAL)x2,(REAL)y2);
	if(_pointStyle)
		{
			_pointStyle->draw(x1,y1,graphic);
			_pointStyle->draw(x2,y2,graphic);
		}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a fill square
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

Pen* TdkGdiLine::getPen()
{
	return _pen;
}

///////////////////////////////////////////////////////////////////////////////
//Draw a fill square
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::showPointLine(const bool &value)
{
	if(value==true)
	{
		if(_pointStyle==NULL)
		{
			Color color;
			if(_pen) _pen->GetColor(&color);
			_pointStyle=new TdkGdiPoint();
			_pointStyle->setType(PointSettings::FILL_CIRCLE);
			_pointStyle->setSize(5);
			_pointStyle->setColor(color);
		}
	}else
	{
		if(_pointStyle!=NULL)
		{
			delete _pointStyle;
			_pointStyle=NULL;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw A Xor Line
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiLine::drawXorLine(Graphics* graphic, PointF *line, const int &size )
{
			POINT		*points=new POINT[size];
			int			i;


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
			
			for(i=0;i<size;i++)	
			{
				points[i].x=(long)line[i].X;
				points[i].y=(long)line[i].Y;
			}
			// Now XOR the hollow rectangle on the Graphics object with
			// a dotted outline.
			MoveToEx(hdc,points[0].x,points[0].y,(LPPOINT) NULL); 
			PolylineTo(hdc,points,size);

			delete points;

			// Put the old stuff back where it was.
			SelectObject( hdc, oldBrush ); // no need to delete a stock object
			SelectObject( hdc, oldPen );
			DeleteObject( gdiPen );		// but we do need to delete the pen
			
			DeleteObject(rgn);
			SelectClipRgn(hdc,0);
			// Return the device context to Windows.
			graphic->ReleaseHDC(hdc);

}