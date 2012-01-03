#include <TdkAbstractCanvasDraw.h>
#include <TdkLayoutTypes.h>
#include <TeDatabase.h>
#include <TdkLayoutMapObject.h>
#include <TdkGraphicViewService.h>
#include <TeView.h>
#include <TdkAbstractLayoutEvents.h>
#include <TdkAbstractCursor.h>
#include <TdkAngleProperty.h>
#include <TdkMapScaleProperty.h>
#include <TdkMapFixedScaleProperty.h>
#include <TdkGeomTransformationUtils.h>
#include <TdkMouseEvent.h>
#include <TdkDatabaseConnectionProperty.h>
#include <TdkViewNameProperty.h>
#include <TdkViewUserProperty.h>
#include <TdkMapWorld_x1_Property.h>
#include <TdkMapWorld_y1_Property.h>
#include <TdkMapWorld_x2_Property.h>
#include <TdkMapWorld_y2_Property.h>
#include <TdkLayoutDatabaseObject.h>
#include <TdkSelectedThemeProperty.h>
#include <TdkSelectedFeaturesProperty.h>
#include <TdkSelectionColorProperty.h>
#include <TdkSelectionTransparencyProperty.h>

///////////////////////////////////////////////////////////////////////////////
// Layout Map Constructor
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkLayoutMapObject::TdkLayoutMapObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box, \
									   const TeBox &window,const std::string &viewName,const std::string &userName, TeDatabase *db,bool *stop) : TdkLayoutObject(id,canvas)
{
	_view=NULL;
	registerExtendProperties();
	_boundingBox=box;
	_window=window;
	_database=db;
	_mapPixmap=__initialPixmap + id;
	_canvas->addBuffer(_mapPixmap);
	_necessaryRedraw=true;
	_events=NULL;
	_cursor=NULL;
	_objectName="Map_" + Te2String(id,0);
	_type=LT_MAP;
	_mapMode=MapMode::None;
	_stop=stop;
	_viewName->setValue(viewName);
	_viewUser->setValue(userName);
	_lastVieName.clear();
	_lastViewUser.clear();
	if(_database != 0)	_internalDatabase=true;
	else				_internalDatabase=false;
}

///////////////////////////////////////////////////////////////////////////////
// Layout Map Destructor
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkLayoutMapObject::~TdkLayoutMapObject()
{
	_view=NULL;
	_canvas->removeBuffer(_mapPixmap);
}


///////////////////////////////////////////////////////////////////////////////
// Draw Error Line
//Author : Rui Mauricio Gregório 
//Date : 07/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutMapObject::drawErrorLine()
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
// Draw Method to draw the geographic map
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::draw()
{
	TdkGraphicViewService	grpService(_events,_stop);
	TeBox					viewport;
	TeBox					window;
	TeBox					mapViewport;
	int						currPixmap;

	if(_connection)
	{
		if(_connection->isChange())
			restartConnection();
	}

	if(_database)
	{
		std::string dbVersion;
		_database->loadVersionStamp(dbVersion);
		if( (dbVersion != "4.0.0") && (dbVersion != "4.1.0") && (dbVersion != "4.1.1"))
		{
			drawErrorLine();
			return ;
		}
	}

	if( (_lastVieName!=_viewName->getValue()) && (_database != 0) )
	{
		_view=loadView(_database,_viewName->getValue(),_viewUser->getValue());
		_selectedTheme->setView(_view);
		_lastVieName=_viewName->getValue();
		_necessaryRedraw=true;
	}
	if( (_lastViewUser != _viewUser->getValue()) && (_database !=0))
	{
		_view=loadView(_database,_viewName->getValue(),_viewUser->getValue());
		_selectedTheme->setView(_view);
		_lastViewUser=_viewUser->getValue();
		_necessaryRedraw=true;
	}

	if( (_view == NULL) || (_database == NULL) || ( (_database->isConnected() == false) && (_database->dbmsName() !="PostgreSQL") ) ) 
	{
		drawErrorLine();
		return ;
	}

	

	if(_mapScale)	
	{	
		bool recompute=false;
		if(_fixedScale && _necessaryRedraw)	 recompute=_fixedScale->getValue();
		if(_mapScale->externalScaleStatus() || recompute) recomputeBox(_mapScale->getValue(),_view->projection());
		_mapScale->resetExternalScale();
	}

	mapViewport=getMapViewport(_canvas);
	if(_necessaryRedraw)
	{
//////////////////////////////////////////////////////////////////////////////
//test
		TeVisual visual;
		visual.color(_selectionColor->getColor());
		visual.contourColor(_selectionColor->getColor());
		visual.transparency((int)_transparencyColor->getValue());
//////////////////////////////////////////////////////////////////////////////

		if(_cursor) _cursor->setCursor(CursorWait);
		_canvas->getViewport(viewport);
		_canvas->getWindow(window);

		if(!_window.isValid())  _window=getValidBox(_view);

		if( (mapViewport.width() > _canvas->getWidth()) || (mapViewport.height() > _canvas->getHeight()) )
		{
			_canvas->resizeBuffer(_mapPixmap,mapViewport.width(),mapViewport.height());
		}

		_fixedBox=TeBox(1,1,mapViewport.width() + 1,mapViewport.height() + 1);
		_canvas->setViewport(TeBox(1,mapViewport.height() + 1,mapViewport.width() + 1,1));
		_canvas->setWindow(TdkCoordTransformer::adjustWindowBox(_window,_fixedBox));

		currPixmap=_canvas->getActiveBuffer();
		_canvas->setActiveBuffer(_mapPixmap);
		_canvas->setBackgroundColor(TeColor(255,255,255));
		_canvas->clear();

		_canvas->setClipArea(1,1,mapViewport.width() + 1,mapViewport.height() + 1);
		
		double scale=0;
		if(_mapScale)	scale=_mapScale->getValue();
		grpService.drawView(_view,_canvas,scale);
		if(!_selectedFeatures->empty())	grpService.drawSelectedFeatures(_view,_selectedTheme->getTheme(),&visual,_canvas,scale,_selectedFeatures->getFeatures());
		_canvas->deactivateClip();
		_canvas->setActiveBuffer(currPixmap);

		_canvas->setWindow(window);
		_canvas->setViewport(viewport);
		_necessaryRedraw=false;
		if(_mapScale)	_mapScale->setValue(getScale(_view->projection()));
		if(_cursor) _cursor->setCursor(CursorNormal);
	} 
	_canvas->writeBuffer(_mapPixmap,TdkAbstractCanvasDraw::cbrCache,1,1, \
		_fixedBox.width(),_fixedBox.height(),mapViewport.x1(),mapViewport.y1(),mapViewport.width(),\
		mapViewport.height(),_angle->getValue());
}

///////////////////////////////////////////////////////////////////////////////
// Returns the box with viewport according canvas
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TeBox	TdkLayoutMapObject::getMapViewport(TdkAbstractCanvasDraw * canvas)
{
	double		llx,lly;
	double		urx,ury;

	if(!_canvas)	throw "Invalid null canvas pointer";
	if((_boundingBox.width()<=1) && (_boundingBox.height()<=1))
	{
		_boundingBox=TeBox(0,0,100,100);
	}
	canvas->window2Viewport(_boundingBox.x1(),_boundingBox.y1(),llx,lly);
	canvas->window2Viewport(_boundingBox.x2(),_boundingBox.y2(),urx,ury);

	return TeBox(llx,lly,urx,ury);
}

///////////////////////////////////////////////////////////////////////////////
// Draw the map direct to printer
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::print(TdkAbstractCanvasDraw *canvas)
{
	TdkGraphicViewService	grpService(_events);
	TeBox					viewport;
	TeBox					window;
	TeBox					mapViewport;

	if( (_view == NULL) || (_database == NULL) || ( (_database->isConnected() == false) && (_database->dbmsName() !="PostgreSQL")) ) 
	{
		drawErrorLine();
		return ;
	}

	mapViewport=getMapViewport(canvas);
	if(_cursor) _cursor->setCursor(CursorWait);
	
	canvas->getViewport(viewport);
	canvas->getWindow(window);

	if(!_window.isValid())	_window=_view->box(true);
	
	canvas->setViewport(TeBox(mapViewport.x1(),mapViewport.y2(),mapViewport.x2(),mapViewport.y1()));
	canvas->setWindow(TdkCoordTransformer::adjustWindowBox(_window,mapViewport));

	canvas->setClipArea(mapViewport.x1(),mapViewport.y1(),mapViewport.x2(),mapViewport.y2());
	
//////////////////////////////////////////////////////////////////////////////
//test
		TeVisual visual;
		visual.color(_selectionColor->getColor());
		visual.contourColor(_selectionColor->getColor());
		visual.transparency((int)_transparencyColor->getValue());
//////////////////////////////////////////////////////////////////////////////


	grpService.drawView(_view,canvas);
	if(!_selectedFeatures->empty())	grpService.drawSelectedFeatures(_view,_selectedTheme->getTheme(),&visual,canvas,0,_selectedFeatures->getFeatures());
	canvas->deactivateClip();
	canvas->setWindow(window);
	canvas->setViewport(viewport);
	
	if(_cursor) _cursor->setCursor(CursorNormal);
}

///////////////////////////////////////////////////////////////////////////////
// Returns the view pointer according view name and user name
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TeView *TdkLayoutMapObject::loadView(TeDatabase *db, const std::string viewName, const std::string &userName)
{
	TeViewMap::iterator		it;
	TeViewMap				viewMap;
	TeView					*view=NULL;

	if(!db) return false;

	viewMap=db->viewMap();
	for(it=viewMap.begin();it!=viewMap.end();it++)
	{
		if( ((*it).second->name()==viewName) && ((*it).second->user()==userName))
		{
			return (*it).second;
		}
	}

	view=new TeView(viewName,userName);
	if(!db->loadView(view))
	{
		delete view;
		view=NULL;
	}
	return view;
}

///////////////////////////////////////////////////////////////////////////////
// Set events
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::setEvent(TdkAbstractLayoutEvents* ev)
{
	_events=ev;
}

///////////////////////////////////////////////////////////////////////////////
// Sets cursor pointer
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::setCursor(TdkAbstractCursor * cursor)
{
	_cursor=cursor;
}

///////////////////////////////////////////////////////////////////////////////
// Register proprietaries properties
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::registerExtendProperties()
{
	_mapScale=new TdkMapScaleProperty();
	_properties.push_back((TdkAbstractProperty*)_mapScale);

	_fixedScale=new TdkMapFixedScaleProperty();
	_properties.push_back((TdkAbstractProperty*)_fixedScale);


	_connection=new TdkDatabaseConnectionProperty();
	_properties.push_back((TdkAbstractProperty*)_connection);

	_viewName=new TdkViewNameProperty();
	_properties.push_back(_viewName);

	_viewUser=new TdkViewUserProperty();
	_properties.push_back(_viewUser);

	_wx1= new TdkMapWorld_x1_Property(&_window.x1_, &_necessaryRedraw);
	_properties.push_back(_wx1);

	_wy1= new TdkMapWorld_y1_Property(&_window.y1_, &_necessaryRedraw);
	_properties.push_back(_wy1);

	_wx2= new TdkMapWorld_x2_Property(&_window.x2_, &_necessaryRedraw);
	_properties.push_back(_wx2);

	_wy2= new TdkMapWorld_y2_Property(&_window.y2_, &_necessaryRedraw);
	_properties.push_back(_wy2);

	_selectedTheme=new TdkSelectedThemeProperty(_view);
	_properties.push_back(_selectedTheme);

	_selectedFeatures= new TdkSelectedFeaturesProperty(&_necessaryRedraw);
	_properties.push_back(_selectedFeatures);

	_selectionColor= new TdkSelectionColorProperty(&_necessaryRedraw,RGB(255,0,0));
	_properties.push_back(_selectionColor);

	_transparencyColor= new TdkSelectionTransparencyProperty(&_necessaryRedraw,100);
	_properties.push_back(_transparencyColor);
}

///////////////////////////////////////////////////////////////////////////////
// Return the valid box according themes of view
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TeBox TdkLayoutMapObject::getValidBox(TeView *view)
{
	TeBox									box;
	std::vector<TeViewNode*>::iterator		it;

	if(!view)	return box;

	box=view->getCurrentBox();
	if(box.isValid() && box!=TeBox(0,0,0,0))	return box;

   for(it=view->themes().begin(); it!=view->themes().end();it++)
   {
		if((*it)->type() == TeTHEME)
			updateBox(box,((TeTheme*)(*it))->layer()->box());	
   }
   return box;
}



///////////////////////////////////////////////////////////////////////////////
// Return the map scale
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

double TdkLayoutMapObject::getScale(TeProjection *proj)
{
	double		fx;
	double		fy;
	double		wMM;
	double		factor;
	double		area;

	if(!proj)	return 1;

	wMM = _boundingBox.width();
	fx = _boundingBox.width()/_window.width();
	fy =-_boundingBox.height()/_window.height();//esta com o negativo pois inverti a origem do boundingBox
	
	if (fx > fy)
	{
		factor = fy;
		area = (int)(factor * _window.width() + .5);
	}
	else
	{
		factor = fx;
		area = (int)(factor * _window.height() + .5);
	}
		
	if (proj)
	{
		const string unit = proj->units();
		if (TeConvertToUpperCase(unit) == "METERS")
			wMM /= 1000.;
		else if (TeConvertToUpperCase(unit) == "KILOMETERS")
			wMM /= 1000000.;
		else if (TeConvertToUpperCase(unit) == "CENTIMETERS")
			wMM /= 100.;
		else if (TeConvertToUpperCase(unit) == "FEET")
			wMM /= (12. * 25.4);
		else if (TeConvertToUpperCase(unit) == "INCHES")
			wMM /= 25.4;
		else if (TeConvertToUpperCase(unit) == "DECIMALDEGREES")
			wMM /= 110000000.;
	}
	return (1. / factor ) /(wMM / area);
}

///////////////////////////////////////////////////////////////////////////////
// Calculate the new box according scale value
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::recomputeBox(const double &scale, TeProjection* usedProjection)
{
	double wMM=fabs(_boundingBox.width());
	TdkRecalculateBox(_window, wMM, usedProjection, scale,getScale(usedProjection));
	_necessaryRedraw=true;
}


///////////////////////////////////////////////////////////////////////////////
// Mouse Move Event
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::mouseMove(TdkMouseEvent *e)
{
	TeCoord2D	coord=TeCoord2D(e->X,e->Y);
	if(_mapMode==MapMode::Pan)		
	{
		if(TeWithin(coord,_boundingBox) && _cursor)	_cursor->setCursor(CursorHand);
		drawMapTranslate(coord);	
	}else if(_mapMode == MapMode::ZoomIn || _mapMode == MapMode::ZoomOut)
	{
		if(TeWithin(coord,_boundingBox) && _cursor)_cursor->setCursor(CursorCross);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Mouse Down Event
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::mouseDown(TdkMouseEvent *e)
{
	if(e->Button==TdkMouseEvent::Left && TeWithin(TeCoord2D(e->X,e->Y),_boundingBox))	
	{
		if(_mapMode==MapMode::Pan)	_coordClick=TeCoord2D(e->X,e->Y);
		_mousePress=true;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Mouse Up Event
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::mouseUp(TdkMouseEvent *e)
{
	if(_mapMode == MapMode::Pan)				recomputeTranslate(TeCoord2D(e->X,e->Y));
	else if(_mapMode == MapMode::ZoomIn)		zoomIn(TeCoord2D(e->X,e->Y));
	else if(_mapMode == MapMode::ZoomOut)		zoomOut(TeCoord2D(e->X,e->Y));
	_mousePress=false;
		
}

///////////////////////////////////////////////////////////////////////////////
// Draw A translate map
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::drawMapTranslate(const TeCoord2D &coord)
{
	double			x,y;
	double			dx,dy;
	TeBox			mapViewport;
	int				currentBuffer;

	if(!_canvas)	return;

	if(TeWithin(coord,_boundingBox) && _mousePress)
	{
		_canvas->window2Viewport(_coordClick.x(),_coordClick.y(),x,y);
		_canvas->window2Viewport(coord.x(),coord.y(),dx,dy);
		dx-=x;//displacement
		dy-=y;

		mapViewport=getMapViewport(_canvas);
		currentBuffer=_canvas->getActiveBuffer();

		_canvas->setActiveBuffer(TdkAbstractCanvasDraw::cbrFront);
		
		_canvas->setClipArea(mapViewport.x1() + 1 ,mapViewport.y1() + 1, mapViewport.x2() -1, mapViewport.y2() -1);
		this->subtractRulerArea();

		_canvas->setPolygonColor(255,255,255,255);
		_canvas->setPolygonBorderType(0);
		_canvas->setPolygonBorderColor(255,255,255,255);
		_canvas->setPolygonType(-1);

		if(dx>0)		_canvas->fillRect(mapViewport.x1() ,mapViewport.y1(), mapViewport.x1() + dx, mapViewport.y2());
		if(dy>0)		_canvas->fillRect(mapViewport.x1() ,mapViewport.y1() , mapViewport.x2() , mapViewport.y1() + dy);
		if(dx<0)		_canvas->fillRect(mapViewport.x2() + dx ,mapViewport.y1(), mapViewport.x2(), mapViewport.y2());
		if(dy<0)		_canvas->fillRect(mapViewport.x1() ,mapViewport.y2() + dy , mapViewport.x2() , mapViewport.y2());
		
		_canvas->writeBuffer(_mapPixmap,TdkAbstractCanvasDraw::cbrFront,1,1, \
			_fixedBox.width(),_fixedBox.height(),mapViewport.x1() + dx,mapViewport.y1() + dy ,mapViewport.width(),\
			mapViewport.height(),_angle->getValue());	
		_canvas->deactivateClip();
		_canvas->setActiveBuffer(currentBuffer);
		this->drawSelection(TdkAbstractCanvasDraw::cbrFront);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Recompute Translate map's box
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::recomputeTranslate(const TeCoord2D &coord)
{
	double	x,y;
	double	dx,dy;
	TeBox	viewport;
	TeBox	window;

	if(!_canvas)	return;

	if(TeWithin(coord,_boundingBox) && _mousePress)
	{
		_canvas->window2Viewport(_coordClick.x(),_coordClick.y(),x,y);
		_canvas->window2Viewport(coord.x(),coord.y(),dx,dy);

		_canvas->getViewport(viewport);
		_canvas->getWindow(window);
			
		TeBox box=getMapViewport(_canvas);
		_canvas->setViewport(box);
		_canvas->setWindow(TdkCoordTransformer::adjustWindowBox(_window,box));

		_canvas->viewport2Window(x,y,x,y);
		_canvas->viewport2Window(dx,dy,dx,dy);

		dx-=x;
		dy-=y;
		_window=TeBox(_window.x1() - dx , _window.y1() + dy , _window.x2() - dx, _window.y2() + dy );
		_canvas->setViewport(viewport);
		_canvas->setWindow(window);
		_necessaryRedraw=true;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Set Map Mode
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::setMapMode(const MapMode &mode)
{
	if( (mode == FullExtend) && (_view !=0))
	{
		_window=_view->box(true);
		_mapMode=None;
		_necessaryRedraw=true;
	}
	else _mapMode=mode;
}

///////////////////////////////////////////////////////////////////////////////
// Zoom In 
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::zoomIn(const TeCoord2D &coord,const double &factor)
{
	TeBox	viewport;
	TeBox	window;
	double	x,y;
	TeBox	box;

	if(_mousePress && _canvas)
	{
		_canvas->getViewport(viewport);
		_canvas->getWindow(window);
		_canvas->window2Viewport(coord.x(),coord.y(),x,y);

		box=getMapViewport(_canvas);
		_canvas->setViewport(box);
		_canvas->setWindow(TdkCoordTransformer::adjustWindowBox(_window,box));
		_canvas->viewport2Window(x,y,x,y);
		
		x-=_window.center().x();
		y-=_window.center().y();
		_window=TeBox(_window.x1() + x, _window.y1() - y, _window.x2() + x, _window.y2() - y);
		::zoomIn(_window,factor);
		_canvas->setViewport(viewport);
		_canvas->setWindow(window);
		_necessaryRedraw=true;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Zoom Out
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::zoomOut(const TeCoord2D &coord,const double &factor)
{
	TeBox	viewport;
	TeBox	window;
	double	x,y;
	TeBox	box;

	if(_mousePress && _canvas)
	{
		_canvas->getViewport(viewport);
		_canvas->getWindow(window);
		_canvas->window2Viewport(coord.x(),coord.y(),x,y);

		box=getMapViewport(_canvas);
		_canvas->setViewport(box);
		_canvas->setWindow(TdkCoordTransformer::adjustWindowBox(_window,box));
		_canvas->viewport2Window(x,y,x,y);
		
		x-=_window.center().x();
		y-=_window.center().y();
		_window=TeBox(_window.x1() + x, _window.y1() - y, _window.x2() + x, _window.y2() - y);
		::zoomOut(_window,factor);
		_canvas->setViewport(viewport);
		_canvas->setWindow(window);
		_necessaryRedraw=true;
	}
}

///////////////////////////////////////////////////////////////////////////////
// restartConnection
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutMapObject::restartConnection()
{
	TeDatabase					*db;
	TdkLayoutDatabaseObject		*obj;

	if((_connection == 0) || (_internalDatabase == true) ) return;
	obj=(TdkLayoutDatabaseObject*)_connection->getObject();
	if( ( obj != NULL ) && ((db=obj->getTerralibDatabase()) != NULL ) && ( db->isConnected() == true ))
	{
		_database=db;
		 if(_viewName->getValue().empty())	_viewName->setValue(getViewName(_database,_viewUser->getValue()));
		 if(_viewUser->getValue().empty())	_viewUser->setValue(obj->getUser());
		_view=loadView(_database,_viewName->getValue(),_viewUser->getValue());
		_window=TeBox();
	}else
	{
		_database=NULL;
		_view=NULL;
	}
}

///////////////////////////////////////////////////////////////////////////////
// restartConnection
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

std::string TdkLayoutMapObject::getViewName(TeDatabase *db, const std::string &user)
{
	std::string			strSQL;
	std::string			viewName;
	TeDatabasePortal	*dbPortal;

	if( db == NULL ) return "";
	strSQL="select name from te_view where ";
	if(!user.empty()) strSQL+=" user_name='" + user + "' and ";
	strSQL+=" visibility=1 order by view_id desc";

	dbPortal=db->getPortal();
	if(dbPortal->query(strSQL) && dbPortal->fetchRow())
	{
		viewName=dbPortal->getData("name");
	}
	delete dbPortal;
	return viewName;
}

