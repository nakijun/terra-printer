#include <TdkAbstractCanvasDraw.h>
#include <TdkPageSize.h>
#include <TdkPage.h>
#include <TdkCanvasTypes.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor with canvas and pageSize pointer
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
TdkPage::TdkPage(TdkAbstractCanvasDraw* canvas,TdkPageSize* pageSize)
{
	_canvas=canvas;
	_pageSize=pageSize;
	_leftMargin=8;
	_topMargin=8;
	_rightMargin=8;
	_bottomMargin=8;

	_minimumHrzMargin=0;
	_minimumVrtMargin=0;
}


///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
TdkPage::~TdkPage()
{

}

///////////////////////////////////////////////////////////////////////////////
//Update Page ( redraw )
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkPage::update()
{
	if(_canvas) _canvas->setActiveBuffer(TdkAbstractCanvasDraw::cbrCache);
	clearClientArea();
	drawPageShadow();
	drawPage();
}

///////////////////////////////////////////////////////////////////////////////
//Clear Client Area
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkPage::clearClientArea()
{
	double	w,h;
	if((_canvas==NULL) || (_pageSize==NULL))	return;

	_canvas->getDimension(w,h);
	_canvas->setClipArea(rulerSize + 1,rulerSize + 1,w,h);

	_canvas->getDimension(w,h);
	_canvas->setPolygonColor(128,128,128,255);
	_canvas->setPolygonBorderColor(128,128,128,255);
	_canvas->setPolygonType(PolygonSettings::Solid);
	_canvas->setPolygonBorderType(0);
	_canvas->fillRect(rulerSize,rulerSize,w,h);
	_canvas->deactivateClip();

}

///////////////////////////////////////////////////////////////////////////////
//Draw the page like back ( shadow )
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkPage::drawPageShadow()
{
	double	w,h;
	double	delta;

	if((_canvas==NULL) || (_pageSize==NULL))	return;

	_canvas->getDimension(w,h);
	_canvas->setClipArea(rulerSize + 1,rulerSize + 1,w,h);

	w=_pageSize->getWidth();
	h=_pageSize->getHeight();
	
	delta=(w<h ? w * 0.02 : h * 0.02);

	_canvas->setPolygonColor(0,0,0);
	_canvas->setPolygonBorderColor(0,0,0);
	_canvas->setPolygonType(PolygonSettings::Solid);
	_canvas->setPolygonBorderType(0);
	_canvas->fillRectW(delta,delta,w + delta,h + delta);
	_canvas->deactivateClip();
}

///////////////////////////////////////////////////////////////////////////////
//Draw White page
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkPage::drawPage()
{
	double	w,h;
	if((_canvas==NULL) || (_pageSize==NULL))	return;

	_canvas->getDimension(w,h);
	_canvas->setClipArea(rulerSize + 1,rulerSize + 1,w,h);

	w=_pageSize->getWidth();
	h=_pageSize->getHeight();

	_canvas->setPolygonColor(255,255,255);
	_canvas->setPolygonBorderColor(255,255,255);
	_canvas->setPolygonType(PolygonSettings::Solid);
	_canvas->setPolygonBorderType(0);
	_canvas->fillRectW(0,0,w,h);
	drawMargin();
	_canvas->deactivateClip();
}

///////////////////////////////////////////////////////////////////////////////
//Sets the minimum margin of printer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

void TdkPage::setMarginMinimum(const double &horz, const double &vert)
{
	if(_canvas==NULL) return;
	_minimumHrzMargin=horz;
	_minimumVrtMargin=vert;

}

void TdkPage::setMargin(const double &left, const double &top, const double &right, const double &bottom)
{
	_leftMargin=left;
	_topMargin=top;
	_rightMargin=right;
	_bottomMargin=bottom;
}


void TdkPage::getMargin(double &left, double &top, double &right, double &bottom)
{
	left=_leftMargin;
	top=_topMargin;
	right=_rightMargin;
	bottom=_bottomMargin;
}

///////////////////////////////////////////////////////////////////////////////
//draw the Margin
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

void TdkPage::drawMargin()
{
	double w,h;

	if(_leftMargin<=_minimumHrzMargin)		_leftMargin=_minimumHrzMargin;
	if(_rightMargin<=_minimumHrzMargin)		_rightMargin=_minimumHrzMargin;
	if(_topMargin<=_minimumVrtMargin)		_topMargin=_minimumVrtMargin;
	if(_bottomMargin<=_minimumVrtMargin)	_bottomMargin=_minimumVrtMargin;

	if((_leftMargin!=0) && (_topMargin!=0) && (_rightMargin!=0) && (_bottomMargin!=0))
	{
		if(_canvas)
		{
			w=_pageSize->getWidth();
			h=_pageSize->getHeight();
			_canvas->setPolygonBorderColor(230,230,230);
			_canvas->setPolygonBorderType(0);
			_canvas->setPolygonBorderWidth(1);
			if(_pageSize)	_canvas->drawRectW(_leftMargin,_topMargin,w - _rightMargin,h - _bottomMargin);
		}
	}
}