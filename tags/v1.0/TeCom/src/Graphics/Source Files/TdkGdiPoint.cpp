
#include "TdkGdiPoint.h"


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiPoint::TdkGdiPoint()
{
	_pointSize=10;
	_pointChar='R';
	_pointPen=new Pen(Color(0,0,255));
	_pointBrush=new SolidBrush(Color(0,0,255));
	_fontCaracter=new Font(L"Verdana",10);
	_pointType=CIRCLE;
	_pointDecorator=NULL;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiPoint::~TdkGdiPoint()
{

	if(_pointPen)		delete _pointPen;
	if(_pointBrush)		delete _pointBrush;
	if(_fontCaracter)	delete _fontCaracter;
	if(_pointDecorator) delete _pointDecorator;

	_pointPen=NULL;
	_pointDecorator=NULL;
}


///////////////////////////////////////////////////////////////////////////////
//draw Caracter
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

void TdkGdiPoint::drawCaracter(const double &x, const double &y, Graphics *graphic)
{
	WCHAR			caracter;
	StringFormat	format(StringAlignmentCenter);
	PointF			pt((REAL)x,(REAL)y);

	if((graphic!=NULL) && (_pointBrush!=NULL) && (_fontCaracter!=NULL))
	{
		caracter=_pointChar;
		graphic->DrawString(&caracter,1,_fontCaracter,pt,_pointBrush);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw the cross
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void  TdkGdiPoint::drawCross(const double &x, const double &y, Graphics *graphic)
{
	PointF  pX[2];
	PointF  pY[2];

	if((graphic!=NULL) && (_pointPen!=NULL))
	{
		pX[0]=PointF((REAL)(x - (_pointSize/2.0)),(REAL)y);
		pX[1]=PointF((REAL)(x + (_pointSize/2.0)),(REAL)y);

		pY[0]=PointF((REAL)x,(REAL)(y - _pointSize/2.0));
		pY[1]=PointF((REAL)x,(REAL)(y + _pointSize/2.0));
		graphic->DrawLine(_pointPen,pX[0],pX[1]);
		graphic->DrawLine(_pointPen,pY[0],pY[1]);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a diagonal cross
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::drawDiagonalCross(const double &x, const double &y, Graphics *graphic)
{
	PointF  pDown[2];
	PointF  pUp[2];

	if((graphic!=NULL) && (_pointPen!=NULL))
	{
		pDown[0]=PointF((REAL)(x - (_pointSize/2.0)),(REAL)(y - (_pointSize/2.0)));
		pDown[1]=PointF((REAL)(x + (_pointSize/2.0)),(REAL)(y + (_pointSize/2.0)));

		pUp[0]=PointF((REAL)(x - (_pointSize/2.0)),(REAL)(y + (_pointSize/2.0)));
		pUp[1]=PointF((REAL)(x + (_pointSize/2.0)),(REAL)(y - (_pointSize/2.0)));

		graphic->DrawLine(_pointPen,pDown[0],pDown[1]);
		graphic->DrawLine(_pointPen,pUp[0],pUp[1]);
	}
}

///////////////////////////////////////////////////////////////////////////////
//draw a hollow square
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::drawSquare(const double &x, const double &y, Graphics *graphic)
{
	if((graphic!=NULL) && (_pointPen!=NULL))
	{
		graphic->DrawRectangle(_pointPen,(REAL)(x - (_pointSize/2.0)), \
			(REAL)(y - (_pointSize/2.0)),(REAL)_pointSize,(REAL)_pointSize);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a fill square
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::drawFillSquare(const double &x, const double &y, Graphics *graphic)
{
	if((graphic!=NULL) && (_pointBrush!=NULL))
	{
		graphic->FillRectangle(_pointBrush,(REAL)(x - (_pointSize/2.0)), \
			(REAL)(y - (_pointSize/2.0)),(REAL)_pointSize,(REAL)_pointSize);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a hollow circle
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::drawCircle(const double &x, const double &y, Graphics *graphic)
{
	if((graphic!=NULL) && (_pointPen!=NULL))
	{
		graphic->DrawEllipse(_pointPen,(REAL)(x - (_pointSize/2.0)),(REAL)(y - (_pointSize/2.0)), \
			(REAL)(_pointSize),(REAL)(_pointSize));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a fill square
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::drawFillCircle(const double &x, const double &y, Graphics *graphic)
{
	if((graphic!=NULL) && (_pointBrush!=NULL))
	{
		graphic->FillEllipse(_pointBrush,(REAL)(x - (_pointSize/2.0)),(REAL)(y - (_pointSize/2.0)), \
			(REAL)(_pointSize),(REAL)(_pointSize));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a hollow diamond
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::drawDiamond(const double &x, const double &y, Graphics *graphic)
{
	if((graphic!=NULL) && (_pointPen!=NULL))
	{
		graphic->TranslateTransform((REAL)(x - (_pointSize/2.0)),(REAL)(y - (_pointSize/2.0)));
		graphic->RotateTransform(45);
		graphic->DrawRectangle(_pointPen,0.0,0.0,(REAL)_pointSize,(REAL)_pointSize);
		graphic->ResetTransform();
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a fill diamond
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::drawFillDiamond(const double &x, const double &y, Graphics *graphic)
{
	if((graphic!=NULL) && (_pointBrush!=NULL))
	{
		graphic->TranslateTransform((REAL)(x - (_pointSize/2.0)),(REAL)(y - (_pointSize/2.0)));
		graphic->RotateTransform(45);
		graphic->FillRectangle(_pointBrush,0.0,0.0,(REAL)_pointSize,(REAL)_pointSize);
		graphic->ResetTransform();
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a point
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::draw(const double &x, const double &y,Graphics *graphic)
{

	switch(_pointType)
	{
		case CROSS:					drawCross(x,y,graphic);
									break;
		case CIRCLE:				drawCircle(x,y,graphic);
									break;
		case DIAGONAL_CROSS:		drawDiagonalCross(x,y,graphic);
									break;
		case SQUARE:				drawSquare(x,y,graphic);
									break;
		case FILL_CIRCLE:			drawFillCircle(x,y,graphic);
									break;
		case FILL_SQUARE:			drawFillSquare(x,y,graphic);
									break;
		case CARACTER:				drawCaracter(x,y,graphic);
									break;
		case DIAMOND:				drawDiamond(x,y,graphic);
									break;
		case FILL_DIAMOND:			drawFillDiamond(x,y,graphic);
									break;
		case UNKNOW:				break;
		default:					drawCircle(x,y,graphic);
	}
	if(_pointDecorator)
	{
		_pointDecorator->draw(x,y,graphic);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a fill square
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::addDecorator(TdkGdiPoint *dec)
{
	if(_pointDecorator)	delete _pointDecorator;
	_pointDecorator=dec;
}

///////////////////////////////////////////////////////////////////////////////
//Sets point color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::setColor(const Color &color)
{
	if((_pointPen!=NULL) && (_pointBrush!=NULL))
	{
		_pointPen->SetColor(color);
		((SolidBrush*)_pointBrush)->SetColor(color);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets the point size
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::setSize(const int &size)
{
	_pointSize=size;
}

///////////////////////////////////////////////////////////////////////////////
//sets set the point caracter
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::setChar(const char &caracter)
{
	_pointChar=caracter;
}

///////////////////////////////////////////////////////////////////////////////
//Sets the point type
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::setType(const pointType &type)
{
	_pointType=type;
}

///////////////////////////////////////////////////////////////////////////////
//Set the alpha color to point
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::setAlpha(const int &alpha)
{
	Color	color;
	if((_pointPen!=NULL) && (_pointBrush!=NULL))
	{
		_pointPen->GetColor(&color);
		_pointPen->SetColor(Color(alpha,color.GetR(),color.GetG(),color.GetB()));
		((SolidBrush*)_pointBrush)->SetColor(Color(alpha,color.GetR(),color.GetG(),color.GetB()));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Clear decorator
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiPoint::clearDecorator()
{
	if(_pointDecorator) delete _pointDecorator;
	_pointDecorator=NULL;
}