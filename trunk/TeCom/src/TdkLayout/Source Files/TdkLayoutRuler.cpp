#include <TdkAbstractCanvasDraw.h>
#include <TdkPageSize.h>
#include <TdkLayoutRuler.h>
#include <TdkCanvasTypes.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor whit canvas and pagesize pointer such as parameter
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
TdkLayoutRuler::TdkLayoutRuler(TdkAbstractCanvasDraw* canvas,TdkPageSize* pageSize)
{
	_canvas=canvas;
	_pageSize=pageSize;
	_bShowRuler=true;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
TdkLayoutRuler::~TdkLayoutRuler()
{

}

///////////////////////////////////////////////////////////////////////////////
//Draw Vertical Client Area to Ruler ( Valid Vertical Paper Area )
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutRuler::drawVerticalClientArea()
{
		double	initX,initY;
	double	endX,endY;

	if((_canvas==NULL) || (_pageSize==NULL))	return;

	_canvas->setPolygonColor(255,255,255);
	_canvas->setPolygonBorderColor(255,255,255);
	_canvas->setPolygonType(PolygonSettings::Solid);

	_canvas->window2Viewport(0,0,initX,initY);
	_canvas->window2Viewport(_pageSize->getWidth(),_pageSize->getHeight(),endX,endY);

	_canvas->setClipArea(5,initY, rulerSize-6, endY);
	_canvas->fillRect(5,initY, rulerSize-6, endY);
	_canvas->deactivateClip();
}

///////////////////////////////////////////////////////////////////////////////
//Draw Vertical Ruler
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutRuler::drawVerticalRuler()
{
	double		w,h;

	if(!_canvas) return;

	
	_canvas->getDimension(w,h);
	_canvas->setPolygonType(PolygonSettings::Solid);
	_canvas->setPolygonColor(212,208,200,255);
	_canvas->setPolygonBorderColor(212,208,200,255);
	_canvas->setPolygonBorderWidth(1);

	_canvas->setLineColor(128,128,128);
	_canvas->setLineType(LineSettings::DashStyleSolid);
	_canvas->setLineWidth(1);

	_canvas->fillRect(0,0,rulerSize,h);
	_canvas->drawLineSegment(rulerSize-1,rulerSize,rulerSize-1,h);
	_canvas->setLineColor(64,64,64);
	_canvas->drawLineSegment(rulerSize,rulerSize,rulerSize,h);

	_canvas->setClipArea(0,rulerSize +1 ,rulerSize -1, h);
	_canvas->setPolygonColor(128,128,128);
	_canvas->fillRect(5,rulerSize + 6, rulerSize - 6, h -5);
	_canvas->deactivateClip();

	drawVerticalClientArea();
	drawVerticalText();

}

///////////////////////////////////////////////////////////////////////////////
//Draw Vertical Text to Ruler
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutRuler::drawVerticalText()
{
	double	w,h;
	double	llx,lly,urx,ury;
	double	x,y,xmm10,xmm5,xmm;
	int		i;

	if((_canvas==NULL) || (_pageSize==NULL))	return;

	_canvas->setLineColor(0,0,0);
	_canvas->setLineType(LineSettings::DashStyleSolid);
	_canvas->setLineWidth(1);
	_canvas->setTextAngle(0);
	_canvas->setTextSize(6);
	_canvas->setTextColor(0,0,0);
	_canvas->setTextAlign(1,0);
	_canvas->setTextFont("Arial");
	_canvas->setTextAngle(90);

	_canvas->getDimension(w,h);

	//primeiro pego o comeco e fim de X
	_canvas->getWindow(llx,lly,urx,ury);
	//clipo a area para desenho
	_canvas->setClipArea(0,rulerSize + 10 ,rulerSize -1, h - 10);

	//!descubro a posicao inicial X
	_canvas->viewport2Window(rulerSize-7,lly,x,y);
	//!descubro a posicao final de X para 10 mm
	_canvas->viewport2Window(rulerSize-15,llx,xmm10,y);
	//!descubro a posicao final de X para cada 5 mm
	_canvas->viewport2Window(rulerSize-13,llx,xmm5,y);
	//!descubro a posicao final de X para cada mm
	_canvas->viewport2Window(rulerSize-10,llx,xmm,y);

	for(i=(int)lly;i<ury;i++)
	{
		if((i%(10 * getFactor()))==0)
		{
			_canvas->drawLineSegmentW(x,i,xmm10,i);
			_canvas->drawTextW(xmm10,i,Te2String(i));
		}
		else if((i%(5 * getFactor()))==0)
		{
			_canvas->drawLineSegmentW(x,i,xmm5,i);
		}
		else if((i%(getFactor()))==0)
		{
			_canvas->drawLineSegmentW(x,i,xmm,i);
		}
	}
	_canvas->deactivateClip();
}

///////////////////////////////////////////////////////////////////////////////
//Draw Horizontal Client Area ( Valid Horizontal Paper Area )
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutRuler::drawHorizontalClientArea()
{
	double	initX,initY;
	double	endX,endY;

	if((_canvas==NULL) || (_pageSize==NULL))	return;

	_canvas->setPolygonColor(255,255,255);
	_canvas->setPolygonBorderColor(255,255,255);
	_canvas->setPolygonType(PolygonSettings::Solid);

	_canvas->window2Viewport(0,0,initX,initY);
	_canvas->window2Viewport(_pageSize->getWidth(),_pageSize->getHeight(),endX,endY);

	_canvas->setClipArea(rulerSize, 5, endX, rulerSize - 6);
	_canvas->fillRect(initX, 5, endX, rulerSize - 6);
	_canvas->deactivateClip();

}

///////////////////////////////////////////////////////////////////////////////
//Draw Horizontal Text to Ruler
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutRuler::drawHorizontalText()
{
	int		i;
	double	llx,lly,urx,ury;
	double	w,h;
	double	x,ymm10,ymm5,ymm,y;

	if((_canvas==NULL) || (_pageSize==NULL))	return;

	_canvas->setLineColor(0,0,0);
	_canvas->setLineType(LineSettings::DashStyleSolid);
	_canvas->setLineWidth(1);
	_canvas->setTextAngle(0);
	_canvas->setTextSize(6);
	_canvas->setTextColor(0,0,0);
	_canvas->setTextAlign(1,0);
	_canvas->setTextFont("Arial");
	

	_canvas->getDimension(w,h);

	//primeiro pego o comeco e fim de X
	_canvas->getWindow(llx,lly,urx,ury);
	//clipo a area para desenho
	_canvas->setClipArea(rulerSize + 10 , 5 ,w - 10 , rulerSize - 7);
	//descubro onde é o ponto inicial de Y de viewport para window
	_canvas->viewport2Window(0,rulerSize,x,y);
	//descubro o ponto Y (a cada 10 mm) de viewport para window
	_canvas->viewport2Window(0, rulerSize - 15,x,ymm10);
	//descubro o ponto Y (a cada 5 mm) de viewport para window
	_canvas->viewport2Window(0,rulerSize-13,x,ymm5);
	//descubro o ponto Y (a cada  mm) de viewport para window
	_canvas->viewport2Window(0,rulerSize-10,x,ymm);

	
	for(i=(int)llx;i<urx;i++)
	{
		if((i%(10 * getFactor()))==0)
		{
			_canvas->drawLineSegmentW(i,y,i,ymm10);
			_canvas->drawTextW(i,ymm10,Te2String(i));
		}else if((i%(5 * getFactor()))==0)
		{
			_canvas->drawLineSegmentW(i,y,i,ymm5);
		}
		else if(i%(getFactor())==0)
		{
			_canvas->drawLineSegmentW(i,y,i,ymm);
		}
	}
	
	_canvas->deactivateClip();
}

///////////////////////////////////////////////////////////////////////////////
//Draw Horizontal Ruler
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutRuler::drawHorizontalRuler()
{
	double	w,h;
	if(!_canvas) return;

	_canvas->getDimension(w,h);
	_canvas->setPolygonColor(212,208,200);
	_canvas->setPolygonBorderColor(212,208,200);
	_canvas->setPolygonType(PolygonSettings::Solid);

	_canvas->setLineColor(128,128,128);
	_canvas->setLineType(LineSettings::DashStyleSolid);
	_canvas->setLineWidth(1);

	_canvas->fillRect(0,0,w,rulerSize);
	_canvas->drawLineSegment(rulerSize-1,rulerSize-1,w,rulerSize-1);
	_canvas->setLineColor(64,64,64);
	_canvas->drawLineSegment(rulerSize-1,rulerSize,w,rulerSize);

	_canvas->setPolygonColor(128,128,128);
	_canvas->setClipArea(rulerSize +1 , 5 ,w -5 , rulerSize - 6);
	_canvas->fillRect(rulerSize + 6, 5, w - 6, rulerSize - 6);
	_canvas->deactivateClip();


	drawHorizontalClientArea();
	drawHorizontalText();

	

}

///////////////////////////////////////////////////////////////////////////////
//Draw Extern Border to Ruler ( 3D Efect )
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutRuler::drawExternBorder()
{
	double w,h;

	if(_canvas)
	{
		_canvas->getDimension(w,h);
		_canvas->setLineColor(128,128,128);
		_canvas->setLineType(LineSettings::DashStyleSolid);
		_canvas->setLineWidth(1);

		_canvas->drawLineSegment(0,0,w,0);
		_canvas->drawLineSegment(0,0,0,h);

		
		_canvas->drawLineSegment(0,h-1,rulerSize,h-1);
		_canvas->drawLineSegment(w-1,0,w-1,rulerSize);


		_canvas->setPolygonBorderColor(128,128,128);
		_canvas->drawRect(5,8,20,23);
		_canvas->setLineColor(255,255,255);
		_canvas->drawLineSegment(6,24,20,24);
		_canvas->drawLineSegment(21,9,21,23);

		_canvas->setLineColor(0,0,0);
		_canvas->setLineWidth(2);
		_canvas->drawLineSegment(9,12,9,20);
		_canvas->drawLineSegment(8,20,16,20);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Update Ruler ( redraw)
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutRuler::update()
{
	if(_bShowRuler)
	{
		if(_canvas) _canvas->setActiveBuffer(TdkAbstractCanvasDraw::cbrCache);
		drawVerticalRuler();
		drawHorizontalRuler();
		drawExternBorder();
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set whether Ruler is Visible
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutRuler::setVisible(const bool &status)
{
	_bShowRuler=status;
}

///////////////////////////////////////////////////////////////////////////////
//Return the factor to draw Ruler according Page
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
int TdkLayoutRuler::getFactor()
{
	double		pageValue;
	double		factorView;
	double		llx,lly,urx,ury;


	if((_pageSize==NULL) || (_canvas==NULL))
	{
		return 1;
	}

	pageValue=(_pageSize->getOrientation() == portrait ? 210 : 297);
	if(_pageSize->getWidth()>_pageSize->getHeight())
	{
		pageValue=_pageSize->getWidth()/pageValue;
	}else
	{
		pageValue=_pageSize->getHeight()/pageValue;
	}
	if(pageValue<1) 
		pageValue=1;

	_canvas->getViewport(llx,lly,urx,ury);
	if(fabs(ury-lly) == 0) return 1;
	factorView=1.0/(733.0/(fabs(ury-lly)/2.));
	if(factorView == 0) return 1;
	factorView=1.0/factorView;
	if(factorView<1) factorView=1.0;
	return (int)(pageValue * factorView);
}


