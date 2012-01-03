#include <TdkLayoutTypes.h>
#include <TdkLayoutPoliticalDivisionObject.h>
#include <TdkXmlPoliticalDivision.h>
#include <TdkAngleProperty.h>
#include <TdkGeomTransformationUtils.h>

TdkLayoutPoliticalDivisionObject::TdkLayoutPoliticalDivisionObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box, \
																   const std::string &path) : TdkLayoutObject(id,canvas)
{
	registerExtendProperties();
	_boundingBox=box;
	_mapPixmap=_initialPDPixmap + id;
	_canvas->addBuffer(_mapPixmap);
	_objectName="PoliticalDivision_" + Te2String(id,0);
	_type=LT_POLITICALDIVISION;
	_divisionFile= new TdkXmlPoliticalDivision();
	_divisionFile->open(path + "\\maps\\" + _dpFileName);
	_window=_divisionFile->getBox();
	_necessaryRedraw=true;
}


TdkLayoutPoliticalDivisionObject::~TdkLayoutPoliticalDivisionObject()
{
	if(_divisionFile)	delete _divisionFile;
}


void TdkLayoutPoliticalDivisionObject::draw()
{
	TeBox	mapViewport;
	TeBox	viewport,window;
	int		currPixmap;

	if(_divisionFile->isValid() == false) 
	{
		drawErrorLine();
		return;
	}
	
	mapViewport=getMapViewport(_canvas);
	_canvas->getViewport(viewport);
	_canvas->getWindow(window);
	if( (mapViewport.height() * mapViewport.width()) <(_fixedBox.height() * _fixedBox.width()))	_necessaryRedraw=true;
	
	if(_necessaryRedraw)
	{
		if( (mapViewport.height() * mapViewport.width()) < __MaxPixmapSize)
		{
			_fixedBox=TeBox(1,1,mapViewport.width() + 1,mapViewport.height() + 1);
			if( (mapViewport.width() > _canvas->getWidth()) || (mapViewport.height() > _canvas->getHeight()))
			_canvas->resizeBuffer(_mapPixmap,mapViewport.width(),mapViewport.height());
			
			_canvas->setViewport(TeBox(1,mapViewport.height() + 1,mapViewport.width() + 1,1));
			_canvas->setWindow(TdkCoordTransformer::adjustWindowBox(_window,_fixedBox));

			currPixmap=_canvas->getActiveBuffer();
			_canvas->setActiveBuffer(_mapPixmap);
			_canvas->setBackgroundColor(TeColor(255,255,255));
			_canvas->clear();
			_canvas->setClipArea(1,1,mapViewport.width() + 1,mapViewport.height() + 1);

			//desenha os poligonos
			draw(_canvas,_divisionFile);

			_canvas->deactivateClip();
			_canvas->setActiveBuffer(currPixmap);
			_canvas->setWindow(window);
			_canvas->setViewport(viewport);
		}
		_necessaryRedraw=false;
	}
	_canvas->writeBuffer(_mapPixmap,TdkAbstractCanvasDraw::cbrCache,1,1, \
		_fixedBox.width(),_fixedBox.height(),mapViewport.x1(),mapViewport.y1(),mapViewport.width(),\
		mapViewport.height(),_angle->getValue());
}


void TdkLayoutPoliticalDivisionObject::print(TdkAbstractCanvasDraw *canvas)
{

	TeBox					viewport;
	TeBox					window;
	TeBox					mapViewport;

	if(_divisionFile->isValid() == false) 
	{
		drawErrorLine();
		return;
	}
	mapViewport=getMapViewport(canvas);
	canvas->getViewport(viewport);
	canvas->getWindow(window);
	canvas->setViewport(TeBox(mapViewport.x1(),mapViewport.y2(),mapViewport.x2(),mapViewport.y1()));
	canvas->setWindow(TdkCoordTransformer::adjustWindowBox(_window,mapViewport));
	canvas->setClipArea(mapViewport.x1(),mapViewport.y1(),mapViewport.x2(),mapViewport.y2());
	draw(canvas,_divisionFile);
	canvas->deactivateClip();
	canvas->setWindow(window);
	canvas->setViewport(viewport);
	
}

void TdkLayoutPoliticalDivisionObject::registerExtendProperties()
{


}

///////////////////////////////////////////////////////////////////////////////
// Draw Error Line
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutPoliticalDivisionObject::drawErrorLine()
{
	TeLine2D	lneError;
	lneError.add(_boundingBox.lowerLeft());
	lneError.add(_boundingBox.upperRight());
	_canvas->setLineWidth(2);
	_canvas->setLineType(1);
	_canvas->setLineColor(255,200,200);
	if( (_angle != 0) && (_angle->getValue() != 0) )	TdkRotate(lneError,_boundingBox.center(),_angle->getValue());
	_canvas->drawLineW(lneError);
	lneError.clear();
	lneError.add(TeCoord2D(_boundingBox.x1(),_boundingBox.y2()));
	lneError.add(TeCoord2D(_boundingBox.x2(),_boundingBox.y1()));
	if( (_angle != 0) && (_angle->getValue() != 0) )	TdkRotate(lneError,_boundingBox.center(),_angle->getValue());
	_canvas->drawLineW(lneError);
	lneError.clear();
	lneError.add(TeCoord2D(_boundingBox.x1(),_boundingBox.y1()));
	lneError.add(TeCoord2D(_boundingBox.x2(),_boundingBox.y1()));
	lneError.add(TeCoord2D(_boundingBox.x2(),_boundingBox.y2()));
	lneError.add(TeCoord2D(_boundingBox.x1(),_boundingBox.y2()));
	lneError.add(TeCoord2D(_boundingBox.x1(),_boundingBox.y1()));
	if( (_angle != 0) && (_angle->getValue() != 0) )	TdkRotate(lneError,_boundingBox.center(),_angle->getValue());
	_canvas->drawLineW(lneError);
}


///////////////////////////////////////////////////////////////////////////////
// Returns the box with viewport according canvas
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TeBox	TdkLayoutPoliticalDivisionObject::getMapViewport(TdkAbstractCanvasDraw * canvas)
{
	double		llx,lly;
	double		urx,ury;

	if(!canvas)	throw "Invalid null canvas pointer";
	if((_boundingBox.width()<=1) && (_boundingBox.height()<=1))
	{
		_boundingBox=TeBox(0,0,100,100);
	}
	canvas->window2Viewport(_boundingBox.x1(),_boundingBox.y1(),llx,lly);
	canvas->window2Viewport(_boundingBox.x2(),_boundingBox.y2(),urx,ury);

	return TeBox(llx,lly,urx,ury);
}


void TdkLayoutPoliticalDivisionObject::draw(TdkAbstractCanvasDraw * canvas, TdkXmlPoliticalDivision *layer)
{
	TePolygonSet				plsRead;
	TePolygonSet::iterator		it;

	if( (canvas == 0) || (layer == 0)) return;

	canvas->setPolygonBorderColor(0,0,0);
	canvas->setPolygonBorderType(0);
	canvas->setPolygonType(-2);

	plsRead=layer->getPolygons();
	for(it=plsRead.begin();it!=plsRead.end();it++)
	{
		canvas->drawPolygonW((*it));
	}
}