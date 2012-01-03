#include<TdkAbstractCanvasDraw.h>
#include<TdkPageSize.h>
#include <TdkObjectTypes.h>
#include<TdkLayoutController.h>
#include<TdkLayoutRuler.h>
#include<TdkPage.h>
#include<TdkMouseEvent.h>
#include<TdkLayoutObjectList.h>
#include<TdkAbstractLayoutEvents.h>
#include<TdkAbstractCursor.h>
#include <TdkLayoutTextObject.h>
#include <TdkLayoutBarcodeObject.h>
#include <TdkLayoutMTextObject.h>
#include <TdkLayoutImageObject.h>
#include <TdkLayoutMapObject.h>
#include <TdkLayoutRectangleObject.h>
#include <TdkLayoutEllipseObject.h>
#include <TdkLayoutLineObject.h>
#include <TdkLayoutVerticalLineControlObject.h>
#include <TdkLayoutHorizontalLineControlObject.h>
#include <TdkLayoutScaleObject.h>
#include <TdkLayoutNorthObject.h>
#include <TdkLayoutDatabaseObject.h>
#include <TdkAbstractProperty.h>
#include <TdkXmlExportLayout.h>
#include <TdkXmlImportLayout.h>
#include <TdkLayoutPoliticalDivisionObject.h>
#include <TeDatabase.h>
#include <TdkAbstractImage.h>
#include <TdkAbstractClipboard.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor with canvas and event pointer as input parameter
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

TdkLayoutController::TdkLayoutController(TdkAbstractCanvasDraw* canvas, TdkAbstractLayoutEvents *e)
{
	_deltaZoom=0;
	_canvas=canvas;
	_events=e;
	_pageSize=new TdkPageSize();
	_canvas->addBuffer(TdkAbstractCanvasDraw::cbrBack);
	_canvas->addBuffer(TdkAbstractCanvasDraw::cbrCache);
	_canvas->setActiveBuffer(TdkAbstractCanvasDraw::cbrCache);
	_canvas->setBackgroundColor(TeColor(128,128,128));
	_canvas->clear();
	_ruler=new TdkLayoutRuler(_canvas,_pageSize);
	_page=new TdkPage(_canvas,_pageSize);
	_objectList=new TdkLayoutObjectList();
	_objectList->setCanvas(canvas);
	_newObject=NULL;
	_database=NULL;
	updatePageSize();
	_cursor=NULL;
	_loked=false; 
	_stop=false;
	_zoomFactor=0;
	_process=TdkLayoutController::None;
	_mouseDown=false;
	_lastCoord=TeCoord2D(0,0);
	_databaseLogo=0;
	_clipboard=0;
	_pasteDisplacement=5;	
}

///////////////////////////////////////////////////////////////////////////////
//Constructor with event input parameter
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

TdkLayoutController::TdkLayoutController(TdkAbstractLayoutEvents *e, TdkAbstractCursor *cursor)
{
	_deltaZoom=0;
	_events=e;
	_pageSize=new TdkPageSize();
	_cursor=cursor;
	_objectList=new TdkLayoutObjectList(_cursor);
	_canvas=NULL;
	_ruler=NULL;
	_page=NULL;
	_newObject=NULL;
	_database=NULL;
	_loked=false;
	_stop=false;
	_zoomFactor=0;
	_process = TdkLayoutController::None;
	_mouseDown=false;
	_lastCoord=TeCoord2D(0,0);
	_databaseLogo=0;
	_clipboard=0;
	_pasteDisplacement=5;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

TdkLayoutController::~TdkLayoutController()
{
	if(_objectList)		delete _objectList;
	if(_canvas)			delete _canvas;
	if(_pageSize)		delete _pageSize;
	if(_ruler)			delete _ruler;
	if(_page)			delete _page;
	if(_database)		delete _database;
	if(_newObject)		delete _newObject;
	if(_databaseLogo)	delete _databaseLogo; 
	if(_clipboard)		delete _clipboard;
}

///////////////////////////////////////////////////////////////////////////////
//Set Canvas Method
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::setCanvas(TdkAbstractCanvasDraw* canvas)
{
	if(_canvas)		delete _canvas;
	if(_ruler)		delete _ruler;
	if(_page)		delete _page;

	_canvas=canvas;
	_canvas->addBuffer(TdkAbstractCanvasDraw::cbrBack);
	_canvas->addBuffer(TdkAbstractCanvasDraw::cbrCache);
	_canvas->setActiveBuffer(TdkAbstractCanvasDraw::cbrCache);
	_canvas->setBackgroundColor(TeColor(128,128,128));
	_canvas->clear();
	if(_objectList) _objectList->setCanvas(canvas);
	

	updatePageSize();

	_ruler=new TdkLayoutRuler(_canvas,_pageSize);
	_page=new TdkPage(_canvas,_pageSize);
}

///////////////////////////////////////////////////////////////////////////////
//Returns the current canvas used by controller
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
TdkAbstractCanvasDraw* TdkLayoutController::getCanvas()
{
	return _canvas;
}


///////////////////////////////////////////////////////////////////////////////
//Update all layout objects
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::update()
{
	if(_canvas)
	{
		_loked=true;
		_canvas->clear(TdkAbstractCanvasDraw::cbrCache);
		_page->update();
		_objectList->update();
		_ruler->update();
		_canvas->writeBuffer(TdkAbstractCanvasDraw::cbrCache,TdkAbstractCanvasDraw::cbrBack);
		_objectList->updateSelection();
		_loked=false;
		_stop=false;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Update all objects when client area is resized
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::resize()
{
	if(_canvas)
	{
		if(_zoomFactor)	this->setZoomFactor(_zoomFactor);
		_canvas->Update();
		_canvas->resizeBuffer(TdkAbstractCanvasDraw::cbrCache,-1,-1);
		_canvas->resizeBuffer(TdkAbstractCanvasDraw::cbrBack,-1,-1);
		updatePageSize();
		update();
	}
}

///////////////////////////////////////////////////////////////////////////////
//Refresh Method ( Copy Back Buffer to Front )
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::refresh()
{
	if(_canvas!=NULL)
	{
		_canvas->writeBuffer(TdkAbstractCanvasDraw::cbrBack,TdkAbstractCanvasDraw::cbrFront);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Update Page Size
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::updatePageSize()
{
	double	dX, dY;
	double	w,h;
	
	if((_pageSize==NULL) || (_canvas==NULL))
	{
		return;
	}

	dX=_pageSize->getWidth() * 0.1;
	dY=_pageSize->getHeight() * 0.1;
	dX+=_deltaZoom;
	dY+=_deltaZoom;
	_canvas->getDimension(w,h);
	_canvas->setViewport(0,0,w,h);
	setWorld(-dX,-dY,_pageSize->getWidth() + dX, _pageSize->getHeight() + dY,_canvas);
	if(_zoomFactor)
		this->setZoomFactor(_zoomFactor);
}

///////////////////////////////////////////////////////////////////////////////
//Recompose Page Size
//Author : Rui Mauricio Gregório 
//Date : 03/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::recompose()
{
	_deltaZoom=0;
	_zoomFactor=0;
	updatePageSize();
	update();
	refresh();
}

///////////////////////////////////////////////////////////////////////////////
//Set World ( viewport )
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::setWorld(const double &x1, const double &y1, const double &x2, const double &y2, TdkAbstractCanvasDraw *canvas)
{
	double		w,h;
	double		win_rt;
	double		world_w;
	double		world_h;
	double		world_rt;
	double		xIni,yIni;
	double		xEnd,yEnd;
	double		dx,dy;

	if(_canvas==NULL) return;

	canvas->getDimension(w, h);
	win_rt = w / h;
	
	xIni=x1;
	yIni=y1;
	xEnd=x2;
	yEnd=y2;

	world_w = (xEnd - xIni);
	world_h = (yEnd - yIni);
	world_rt = world_w / world_h;

	if (world_rt < win_rt)
	{
		dx = world_h * win_rt - world_w;
		dx /= 2;
		xIni -= dx;
		xEnd += dx;
	}
	else
	{
		dy = world_w / win_rt - world_h;
		dy /= 2;
		yIni -= dy;
		yEnd += dy;
	}
	canvas->setWindow(xIni,yIni,xEnd,yEnd);
}

///////////////////////////////////////////////////////////////////////////////
//Set Paper Orientation
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::setPaperOrientation(const short &value)
{double	oldW,oldH;
	double  newW,newH;
	if(_pageSize) 
	{
		oldW=_pageSize->getWidth();
		oldH=_pageSize->getHeight();

		_deltaZoom=0.0;
		_pageSize->setOrientation((pageOrientation)value);
		_deltaZoom=0;
		_zoomFactor=0;
		
		newW=_pageSize->getWidth();
		newH=_pageSize->getHeight();
		_objectList->resizeAllObjects(oldW,oldH,newW,newH);
		updatePageSize();
	}
}

///////////////////////////////////////////////////////////////////////////////
//Returns the paper orientation
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
short TdkLayoutController::getPaperOrientation()
{
	if(_pageSize) return ((short)_pageSize->getOrientation());
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Set the paper size
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::setPaperSize(const short &value)
{
	double	oldW,oldH;
	double  newW,newH;
	if(_pageSize) 
	{
		oldW=_pageSize->getWidth();
		oldH=_pageSize->getHeight();

		_deltaZoom=0.0;
		_pageSize->setSize((pageSize)value);
		_deltaZoom=0;
		_zoomFactor=0;
		updatePageSize();

		newW=_pageSize->getWidth();
		newH=_pageSize->getHeight();
		_objectList->resizeAllObjects(oldW,oldH,newW,newH);
		
	}
}

///////////////////////////////////////////////////////////////////////////////
//Returns the paper size
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
short TdkLayoutController::getPaperSize()
{
	if(_pageSize) return ((short)_pageSize->getSize());
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the paper size
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::getPaperSize(double &width, double &height)
{
	if(_pageSize)
	{
		width=_pageSize->getWidth();
		height=_pageSize->getHeight();
	}
}

///////////////////////////////////////////////////////////////////////////////
//Mouse Move Events
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::mouseMove(TdkMouseEvent *e)
{
	double x,y;

	if(_loked) return;
	x=e->X;
	y=e->Y;
	convertViewportToWindow(e->X,e->Y);
	if(_process == TdkLayoutController::None)
	{
		if(_objectList)	_objectList->mouseMove(e);
	}else if((_process == TdkLayoutController::pagePan) && (_mouseDown == true))
	{
		pagePanProcess(_positionClicked,TeCoord2D(x,y));
	}else if( (_process == TdkLayoutController::pageZoomArea) && (_mouseDown == true))
	{
		pageZoomAreaProcess(_positionClickedMM,TeCoord2D(e->X,e->Y));
	}
	if(_events)		_events->mouseMove(e);
}

///////////////////////////////////////////////////////////////////////////////
//Mouse Down Events
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::mouseDown(TdkMouseEvent *e,const bool &ctrl)
{
	if(_loked) return;
	_positionClicked=TeCoord2D(e->X,e->Y);
	convertViewportToWindow(e->X,e->Y);
	_positionClickedMM=TeCoord2D(e->X,e->Y);
	_lastCoord=_positionClickedMM;
	_mouseDown=true;

	if(_process == TdkLayoutController::None)
	{
		if(_objectList)
		{
			_objectList->mouseDown(e,ctrl);
			if(_canvas)_canvas->writeBuffer(TdkAbstractCanvasDraw::cbrCache,TdkAbstractCanvasDraw::cbrBack);
			_objectList->updateSelection();
			refresh();
		}
	}
	if(_events)		_events->mouseDown(e);
}

///////////////////////////////////////////////////////////////////////////////
//Mouse Up Events
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::mouseUp(TdkMouseEvent *e,const bool &ctrl)
{
	_mouseDown=false;
	if(_loked) return;

	convertViewportToWindow(e->X,e->Y);
	if(_process == TdkLayoutController::pagePan)
		pagePanEndProcess(_positionClickedMM,TeCoord2D(e->X,e->Y));
	else if(_process == TdkLayoutController::pageZoomOut)
		pageZoomOutProcess(e);
	else if(_process == TdkLayoutController::pageZoomArea)
		pageEndZoomArea(_positionClickedMM,TeCoord2D(e->X,e->Y));

	if(_events)		_events->mouseUp(e);
	if(_objectList)	_objectList->mouseUp(e,ctrl);
	this->createLayoutObject();
	update();
	refresh();
	_events->endProcessEvent(false);
	
}

///////////////////////////////////////////////////////////////////////////////
//Create Text Object
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::createText(const TeBox &box,const std::string &textValue)
{
	_process=TdkLayoutController::None;
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*)new TdkLayoutTextObject (_objectList->getId(),_canvas,box,textValue);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Create Barcode Object
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::createBarcode(const TeBox &box,const std::string &textValue)
{
	_process=TdkLayoutController::None;
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*)new TdkLayoutBarcodeObject (_objectList->getId(),_canvas,box,textValue);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Create Multi Text Object
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::createMText(const TeBox &box,const std::string &textValue)
{
	_process=TdkLayoutController::None;
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*)new TdkLayoutMTextObject(_objectList->getId(),_canvas,box,textValue);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Create Image Object
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutController::createImage(const std::string &fileName,const TeBox &box)
{
	_process=TdkLayoutController::None;	
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*)new TdkLayoutImageObject(_objectList->getId(),_canvas,box,fileName);
	}
}


///////////////////////////////////////////////////////////////////////////////
//Create Map Object
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutController::createMap(const std::string &viewName, const std::string userName, const TeBox &boxWindow, const TeBox &box)
{
	_process=TdkLayoutController::None;	
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*) new TdkLayoutMapObject(_objectList->getId(),_canvas,box,boxWindow,viewName,userName,_database,&_stop);
		((TdkLayoutMapObject*)_newObject)->setEvent(_events);
		((TdkLayoutMapObject*)_newObject)->setCursor(_cursor);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Create Political Division Object
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::createPoliticalDivision(const TeBox &box)
{
	
	_process=TdkLayoutController::None;	
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*) new TdkLayoutPoliticalDivisionObject(_objectList->getId(),_canvas,box,_fullPath);
	}
}


///////////////////////////////////////////////////////////////////////////////
//Create Rectangle Object
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::createRectangle(const TeBox &box)
{
	_process=TdkLayoutController::None;	
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*) new TdkLayoutRectangleObject(_objectList->getId(),_canvas,box);
	}

}

///////////////////////////////////////////////////////////////////////////////
//Create Ellipse Object
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::createEllipse(const TeBox &box)
{
	_process=TdkLayoutController::None;	
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*) new TdkLayoutEllipseObject(_objectList->getId(),_canvas,box);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Create Line Object
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::createLine(const TeBox &box)
{
	_process=TdkLayoutController::None;	
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*) new TdkLayoutLineObject(_objectList->getId(),_canvas,box);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Create  Vertical Line Control Object
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::createVLineControl(const TeBox &box)
{
	_process=TdkLayoutController::None;	
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*) new TdkLayoutVerticalLineControlObject(_objectList->getId(),_canvas,box);
		((TdkLayoutVerticalLineControlObject*)_newObject)->setCursor(_cursor);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Create  Horizontal Line Control Object
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::createHLineControl(const TeBox &box)
{
	_process=TdkLayoutController::None;	
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*) new TdkLayoutHorizontalLineControlObject(_objectList->getId(),_canvas,box);
		((TdkLayoutHorizontalLineControlObject*)_newObject)->setCursor(_cursor);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Create Database Connection Object
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::createDatabase(const TeBox &box)
{
	_process=TdkLayoutController::None;	
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*) new TdkLayoutDatabaseObject(_objectList->getId(),_canvas,box,_databaseLogo);
	}
}


///////////////////////////////////////////////////////////////////////////////
//Create scale Object
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::createScale(const TeBox &box)
{
	_process=TdkLayoutController::None;	
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*) new TdkLayoutScaleObject(_objectList->getId(),_canvas,box);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Create north Object
//Author : Rui Mauricio Gregório 
//Date : 12/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::createNorth(const std::string &pathName,const TeBox &box)
{
	_process=TdkLayoutController::None;	
	if(_canvas)
	{
		if(_newObject)	delete _newObject;
		_objectList->createLayoutObjectMode();
		_newObject=(TdkLayoutObject*)new TdkLayoutNorthObject(_objectList->getId(),_canvas,box,pathName);
	}
}


///////////////////////////////////////////////////////////////////////////////
//Convert Viewport to Window coordinates
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutController::convertViewportToWindow(double& x, double &y)
{
	if(_canvas)
	{
		double wx,wy;
		_canvas->viewport2Window(x,y,wx,wy);
		x=wx;
		y=wy;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set alignment for each object
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutController::setAlignment(const TdkAlignment &value)
{
	if(_objectList)	
	{
		switch(value)
		{
			case Left_Align:					_objectList->leftAlignment();
												break;
			case Right_Align:					_objectList->rightAlignment();
												break;
			case Top_Align:						_objectList->topAlignment();
												break;
			case Bottom_Align:					_objectList->bottomAlignment();
												break;
			case Horizontal_Center_Align:		_objectList->horizontalCenter(_pageSize->getCenterWidth());
												break;
			case Vertical_Center_Align:			_objectList->verticalCenter(_pageSize->getCenterHeight());
												break;
		}
		update();
		refresh();
	}
}

///////////////////////////////////////////////////////////////////////////////
//Move object using key accelerator
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::moveKey(const moveKeys &key,const bool &ctrl)
{
	if(_objectList) 
	{
		_objectList->moveKey(key,ctrl);
		update();
		refresh();
	}
}

///////////////////////////////////////////////////////////////////////////////
//Mouse Wheel Zoom
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::zoom(const int &delta)
{
	double	llx, lly, urx, ury;
	TeBox	box;
	if(_pageSize)
	{
		if(_canvas) _canvas->getWindow(llx,lly,urx,ury);
		box=TeBox(llx,lly,urx,ury);
		if(delta<0) ::zoomIn(box,0.9);
		else		::zoomOut(box,0.9);
		this->setWorld(box.x1(),box.y1(),box.x2(),box.y2(),_canvas);		
		update();
		refresh();
	}
}

///////////////////////////////////////////////////////////////////////////////
//Horizontal Displacement
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::hDisplacement(const double &value)
{
	double	llx, lly, urx, ury;
	TeBox	box;
	if(_pageSize)
	{
		if(_canvas) _canvas->getWindow(llx,lly,urx,ury);
		box=TeBox(llx + value,lly,urx + value,ury);
		this->setWorld(box.x1(),box.y1(),box.x2(),box.y2(),_canvas);		
		update();
		refresh();
	}

}

///////////////////////////////////////////////////////////////////////////////
//Vertical Displacement
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::vDisplacement(const double &value)
{
	double	llx, lly, urx, ury;
	TeBox	box;
	if(_pageSize)
	{
		if(_canvas) _canvas->getWindow(llx,lly,urx,ury);
		box=TeBox(llx,lly,urx,ury);
		this->setWorld(box.x1(),box.y1() + value,box.x2(),box.y2() + value,_canvas);		
		update();
		refresh();
	}

}

///////////////////////////////////////////////////////////////////////////////
// Print method
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutController::print(TdkAbstractCanvasDraw *canvas,const double &x, const double &y)
{
	double		w,h;
	double		wv, hv;
	double		x1,y1;
	

	_loked=true;
	
	w=_pageSize->getWidth();
	h=_pageSize->getHeight();

	canvas->setWindow(0,0,w,h);

	wv=(w/inch10) * canvas->getDpiX();
	hv=(h/inch10) * canvas->getDpiY();
	//calculate the values without margin edges	
	canvas->setViewport(0,0,wv,hv);

	//translate the viewport according margin values
	canvas->window2Viewport(x,y,x1,y1);	
	canvas->setViewport(-x1,-y1,wv-x1,hv-y1);

	_objectList->print(canvas);
	_loked=false;
}

///////////////////////////////////////////////////////////////////////////////
// Create a new Layout Object  method
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutController::createLayoutObject()
{
	if(_newObject)
	{
		 _loked=true;
		_newObject->setBoundingBox(_objectList->getCreateBox());
		_objectList->add(_newObject);		
		_objectList->resetLayoutObjectMode();
		_newObject=NULL;
		_loked=false;
		if(_events)	_events->insertObjectEvent();
	}
}

///////////////////////////////////////////////////////////////////////////////
// Keyboard event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutController::keyUp(const long &key,  const bool &control)
{
	layoutKey	lKey;

	lKey=(layoutKey) key;
	switch(lKey)
	{
		case	DEL :	if(control == false)	removeSelectedItems();
						break;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Keyboard event
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::keyDown(const long &key, const bool &control)
{
	
}
///////////////////////////////////////////////////////////////////////////////
// sets database pointer
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::setDatabase(TeDatabase *db)
{
	if(_database)	delete _database;
	_database=db;
}

///////////////////////////////////////////////////////////////////////////////
// Returns the total of layout object
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
unsigned int TdkLayoutController::getObjectCount()
{
	return (_objectList!=0 ? _objectList->size() : 0);
}

///////////////////////////////////////////////////////////////////////////////
// Returns the total of select layout object
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
unsigned int TdkLayoutController::getSelectObjectCount()
{
	return (_objectList!=0 ? (unsigned int) _objectList->getSelectObject().size() : 0);
}

///////////////////////////////////////////////////////////////////////////////
// Returns the select object name according the index
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
std::string TdkLayoutController::getSelectObjectName(const unsigned int &index)
{
	return (_objectList!=0 ? _objectList->getSelectObjectName(index) : "");
}

///////////////////////////////////////////////////////////////////////////////
// Returns the object name according index value
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
std::string TdkLayoutController::getObjectName(const unsigned int &index)
{
	return (_objectList!=0 ? _objectList->getObjectName(index) : "");
}

///////////////////////////////////////////////////////////////////////////////
// Returns the property quantity of layout object according your name
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
unsigned int TdkLayoutController::getPropertiesCount(const std::string &objectName)
{
	TdkLayoutObject *obj;
	 obj=_objectList->getObject(objectName);
	 return (obj!=NULL ? obj->getPropertiesCount() : 0);
}

///////////////////////////////////////////////////////////////////////////////
// Returns the property name according object name and you index (used together getPropertiesCount)
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

std::string TdkLayoutController::getPropertyName(const std::string &objectName, const unsigned int &index)
{
	TdkLayoutObject *obj;
	 if((obj=_objectList->getObject(objectName)))
	 {
		 return obj->getPropertyName(index);
	 }
	 return "";
}

///////////////////////////////////////////////////////////////////////////////
// Returns the property value of object according object name and your index (used together getPropertiesCount)
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkAbstractProperty * TdkLayoutController::getPropertyValue(const std::string &objectName, const unsigned int &index)
{
	TdkLayoutObject *obj;
	if((obj=_objectList->getObject(objectName)))	 return obj->getPropertyValue(index);
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Asssociate the property with layout object
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::associatePropertyObject(TdkAbstractProperty *propertyObj, const std::string &objectName)
{
	TdkLayoutObject *obj;
	if((obj=_objectList->getObject(objectName)))	 
	{
		propertyObj->associateObject(obj,objectName);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Returns the property value of object according object and property name to set the property value
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
TdkAbstractProperty * TdkLayoutController::getPropertyValue(const std::string &objectName, const std::string &propertyName)
{
	TdkLayoutObject *obj;
	if((obj=_objectList->getObject(objectName)))	 return obj->getPropertyValue(propertyName);
	return NULL;

}

///////////////////////////////////////////////////////////////////////////////
// SetMapMode
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::setMapMode(const MapMode &mode)
{
	if(_objectList)	_objectList->setMapProcess(mode);
}


///////////////////////////////////////////////////////////////////////////////
// Send Select Objects to Back
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::sendToBack()
{
	if(_objectList) _objectList->sendToBack();
}

///////////////////////////////////////////////////////////////////////////////
// Bring the Select Objects to front
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::bringToFront()
{
	if(_objectList) _objectList->bringToFront();
}

///////////////////////////////////////////////////////////////////////////////
//Sets the minimum margin of printer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::setMarginMinimum(const double &horz, const double &vert)
{
	if(_page) _page->setMarginMinimum(horz,vert);
}

///////////////////////////////////////////////////////////////////////////////
//Stop the draw process
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::Stop()
{
	_stop=true;
}

///////////////////////////////////////////////////////////////////////////////
//Set the margin
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::setMargin(const double &left, const double &top, const double &right, const double &bottom)
{
	if(_page) _page->setMargin(left,top,right,bottom);
}

///////////////////////////////////////////////////////////////////////////////
//Return the margin page
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::getMargin(double &left, double &top, double &right, double &bottom)
{
	if(_page) _page->getMargin(left,top,right,bottom);
}

///////////////////////////////////////////////////////////////////////////////
//Select the object by your name
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutController::select(const std::string &objName)
{
	if(_objectList) return _objectList->select(objName);
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the zoom factor in percent
//Author : Rui Mauricio Gregório 
//Date : 03/2010
///////////////////////////////////////////////////////////////////////////////
double TdkLayoutController::getZoomFactor()
{
	double	w,h;
	TeBox	box;
	double	scale=1.0;

	if(_canvas)
	{
		_canvas->getDimensionMM(w,h);
		_canvas->getWindow(box);
		scale=h/box.height(); 
	}
	return (scale * 100);//returns in percent
} 

///////////////////////////////////////////////////////////////////////////////
//Returns the zoom factor in percent
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////
double TdkLayoutController::getZoomFactor(const TeBox &box)
{
	double	w,h;
	double	scale=1.0;

	if(_canvas)
	{
		_canvas->getDimensionMM(w,h);
		scale=h/box.height(); 
	}
	return (scale * 100);//returns in percent

}

///////////////////////////////////////////////////////////////////////////////
//Sets the zoom factor in percent
//Author : Rui Mauricio Gregório 
//Date : 03/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::setZoomFactor(const double &value)
{
	double			curFactor,newFactor;
	TeBox			window;
	TeBox			newBox;
	double			cX,cY;

	curFactor=getZoomFactor();
	newFactor=value/curFactor;

	if(_canvas)
	{
		_canvas->getWindow(window);
		cX=window.center().x();
		cY=window.center().y();
		newBox=TeBox(cX - (window.width()/2.0) / newFactor, cY - (window.height()/2.0) / newFactor, \
					 cX + (window.width()/2.0) / newFactor, cY + (window.height()/2.0) / newFactor);
		_canvas->setWindow(newBox);
		_zoomFactor=value;
		update();
		this->refresh();
	}
}

///////////////////////////////////////////////////////////////////////////////
//Returns the client area in millimeter
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////

TeBox TdkLayoutController::getBoundingBox()
{
	TeBox		box;

	if(_canvas)	_canvas->getWindow(box);
	return box;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the center client area in millimeter
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////
TeCoord2D TdkLayoutController::getCenterViewPortWindow()
{
	TeCoord2D	center;
	TeBox		box;
	double		wx,wy;

	if(_canvas)
	{
		_canvas->getViewport(box);
		center=box.center();
		_canvas->viewport2Window(center.x(),center.y(),wx,wy);
		center=TeCoord2D(wx,wy);
	}
	return center;
}


///////////////////////////////////////////////////////////////////////////////
//Remove the selected itens from layout
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::removeSelectedItems()
{
	if(_objectList) 
	{
		_objectList->removeSelected();
		update();
		refresh();
	}
}

///////////////////////////////////////////////////////////////////////////////
//Returns the object type
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////
objectType TdkLayoutController::getObjectType(const std::string &name)
{
	TdkLayoutObject *obj;
	if((obj=_objectList->getObject(name)))	 return obj->getType();
	return LT_UNDEFINED;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the get property type
//Author : Rui Mauricio Gregório 
//Date : 07/2010
///////////////////////////////////////////////////////////////////////////////
propertyType TdkLayoutController::getPropertyType(const std::string &objName, const std::string &propName)
{
	TdkLayoutObject			*obj;
	TdkAbstractProperty		*prop;
	
	if((obj=_objectList->getObject(objName)))	 
	{
		if((prop=obj->getPropertyValue(propName)))
		{
			return prop->getType();
		}
	}
	return PNumber;
}

///////////////////////////////////////////////////////////////////////////////
//Method to execute the pan process
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::pagePanProcess(const TeCoord2D &lastPos, const TeCoord2D &newPos)
{
	double dx, dy;
	double w,h;

	if(_canvas!=NULL)
	{
		dx=lastPos.x() - newPos.x();
		dy=lastPos.y() - newPos.y();
		_canvas->getDimension(w,h);
		int currentBuffer=_canvas->getActiveBuffer();
		_canvas->setActiveBuffer(TdkAbstractCanvasDraw::cbrFront);
		
		_canvas->setClipArea(rulerSize3D,rulerSize3D,w,h);
		_canvas->setPolygonColor(128,128,128,255);

		if(dx<0)	_canvas->fillRect(0,0,-dx + rulerSize3D ,h);
		else		_canvas->fillRect(w - dx, 0, w, h);
		if(dy<0)	_canvas->fillRect(0,0,w ,rulerSize3D - dy);
		else		_canvas->fillRect(0,h - dy, w, h);

		_canvas->writeBuffer(TdkAbstractCanvasDraw::cbrBack,TdkAbstractCanvasDraw::cbrFront,rulerSize3D,rulerSize3D,w - rulerSize3D,h - rulerSize3D,rulerSize3D - dx,rulerSize3D - dy,0);
		
		_canvas->deactivateClip();
		_canvas->setActiveBuffer(currentBuffer);
		
	}
}

///////////////////////////////////////////////////////////////////////////////
//Method to execute the zoom area process
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::pageZoomAreaProcess(const TeCoord2D &firstPos, const TeCoord2D &newPos)
{
	int				currentBuffer=_canvas->getActiveBuffer();
	double			w,h;

	_canvas->getDimension(w,h);
	_canvas->setActiveBuffer(TdkAbstractCanvasDraw::cbrFront);
	_canvas->setClipArea(rulerSize3D,rulerSize3D,w,h);
	_canvas->setPolygonColor(128,128,128,255);
	_canvas->setPaintMode(TdkAbstractCanvasDraw::pmdXOR);

	if(!TeEquals(newPos,_lastCoord))
	{
		_canvas->drawRectW(firstPos.x(),firstPos.y(),_lastCoord.x(),_lastCoord.y());
	}
	_canvas->drawRectW(firstPos.x(),firstPos.y(),newPos.x(),newPos.y());
	_canvas->deactivateClip();
	_canvas->setPaintMode(TdkAbstractCanvasDraw::pmdREPLACE);
	_canvas->setActiveBuffer(currentBuffer);
	_lastCoord=newPos;
}

///////////////////////////////////////////////////////////////////////////////
//Method to finalize the end zoom area process
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::pageEndZoomArea(const TeCoord2D &firstPos, const TeCoord2D &newPos)
{
	
	TeLine2D	lneBox;
	TeBox		box;

	lneBox.add(firstPos);
	lneBox.add(TeCoord2D(newPos.x(),firstPos.y()));
	lneBox.add(TeCoord2D(newPos.x(),newPos.y()));
	lneBox.add(TeCoord2D(firstPos.x(),newPos.y()));
	box=lneBox.box();
	if( (box.width() > __ZOOM_EDGE) && (box.height() > __ZOOM_EDGE) )
	{
		this->setWorld(box.x1(),box.y1(),box.x2(),box.y2(),_canvas);		
		update();
		refresh();
		if(_events) _events->zoomAreaEvent();
	}else if( (box.width() == 0) && (box.height() == 0) )
	{
		_canvas->getWindow(box);
		::zoomIn(box,0.8);
		if( (box.width() > __ZOOM_EDGE) && (box.height() > __ZOOM_EDGE) )
		{
			this->setWorld(box.x1(),box.y1(),box.x2(),box.y2(),_canvas);		
			update();
			refresh();
			if(_events) _events->zoomAreaEvent();
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
//Method to finalize the pan process
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::pagePanEndProcess(const TeCoord2D &init, const TeCoord2D &final)
{
		double dx,dy;
		double	llx, lly, urx, ury;
		TeBox	box;

		if( (_pageSize != NULL) && (_canvas != NULL) )
		{
			dx=init.x() - final.x();
			dy=init.y() - final.y();
			_canvas->getWindow(llx,lly,urx,ury);
			box=TeBox(llx + dx,lly + dy,urx + dx,ury + dy);
			this->setWorld(box.x1(),box.y1(),box.x2(),box.y2(),_canvas);		
			update();
			refresh();
			if(_events)	_events->panEvent(dx,dy);
		}
}

///////////////////////////////////////////////////////////////////////////////
//Method to zoom out process
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutController::pageZoomOutProcess(TdkMouseEvent *e)
{
	TeBox		box;
	double		dx,dy;

	if(_canvas)
	{
		_canvas->getWindow(box);
		dx=box.center().x() - e->X;
		dy=box.center().y() - e->Y;
		box=TeBox(box.x1() - dx, box.y1() - dy, box.x2() - dx, box.y2() - dy);
		::zoomOut(box,0.8);
		if(getZoomFactor(box) > 5)
		{
			this->setWorld(box.x1(),box.y1(),box.x2(),box.y2(),_canvas);		
			update();
			refresh();
			if(_events) _events->zoomOutEvent();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Method to sets the layoutMode
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::setLayoutMode(const pageProcess &mode)
{
	_process=mode;
	if(_cursor)
	{
		switch(_process)
		{
			case None:	_cursor->setCursor(CursorNormal);
						break;
			case pageZoomOut:_cursor->setCursor(CursorZoomOut);
						break;
			case pageZoomArea:_cursor->setCursor(CursorZoom);
						break;
			case pagePan:	_cursor->setCursor(CursorHand);
						break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Method to full update to redraw
//Author : Rui Mauricio Gregório 
//Date : 07/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::fullRedraw()
{
	_objectList->setFullUpdate();
	_canvas->resizeBuffer(TdkAbstractCanvasDraw::cbrCache,-1,-1);
	_canvas->resizeBuffer(TdkAbstractCanvasDraw::cbrBack,-1,-1);
	update();
	refresh();
}

///////////////////////////////////////////////////////////////////////////////
//Method to save layout status
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutController::save(const std::string &fileName)
{
	TdkXmlExportLayout exportT(this);
	return exportT.save(fileName);
}

///////////////////////////////////////////////////////////////////////////////
//Method to load layout settings
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutController::open(const std::string &fileName)
{
	TdkXmlImportLayout importT(this);
	return importT.open(fileName);
}

///////////////////////////////////////////////////////////////////////////////
//Method to return the object list
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutObjectList* TdkLayoutController::getList()
{
	return _objectList;
}


///////////////////////////////////////////////////////////////////////////////
//Create a new empty layout page
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::newPage()
{
	if(_pageSize)
	{
		_pageSize->setOrientation(portrait);
		_pageSize->setSize(A4);
	}
	_objectList->clear();
}

///////////////////////////////////////////////////////////////////////////////
//createLayoutObjects
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutObject* TdkLayoutController::createLayoutObject(const short &type)
{
	TdkLayoutObject*	obj=0;
	objectType			objType;

	objType=(objectType)type;
	switch(objType)
	{
		case LT_LINE:					obj=(TdkLayoutObject*) new TdkLayoutLineObject(_objectList->getId(),_canvas,TeBox());
										break;
		case LT_RECTANGLE:				obj=(TdkLayoutObject*) new TdkLayoutRectangleObject(_objectList->getId(),_canvas,TeBox());
										break;
		case LT_ELLIPSE:				obj=(TdkLayoutObject*) new TdkLayoutEllipseObject(_objectList->getId(),_canvas,TeBox());
										break;
		case LT_IMAGE:					obj=(TdkLayoutObject*) new TdkLayoutImageObject(_objectList->getId(),_canvas,TeBox());
										break;
		case LT_TEXT :					obj=(TdkLayoutObject*) new TdkLayoutTextObject(_objectList->getId(),_canvas,TeBox());
										break;
		case LT_SCALE:					obj=(TdkLayoutObject*) new TdkLayoutScaleObject(_objectList->getId(),_canvas,TeBox());
										break;
		case LT_NORTH :					obj=(TdkLayoutObject*) new TdkLayoutNorthObject(_objectList->getId(),_canvas,TeBox(),_fullPath);
										break;
		case LT_MAP:					obj=(TdkLayoutObject*) new TdkLayoutMapObject(_objectList->getId(),_canvas,TeBox(),TeBox(),"","",_database,&_stop);
										((TdkLayoutMapObject*)obj)->setEvent(_events);
										((TdkLayoutMapObject*)obj)->setCursor(_cursor);
										break;
		case LT_DATABASE:				obj=(TdkLayoutObject*) new TdkLayoutDatabaseObject(_objectList->getId(),_canvas,TeBox(),_databaseLogo);
										break;
		case LT_MTEXT:					obj=(TdkLayoutObject*) new TdkLayoutMTextObject(_objectList->getId(),_canvas,TeBox());
										break;
		case LT_POLITICALDIVISION:		obj=(TdkLayoutObject*) new TdkLayoutPoliticalDivisionObject(_objectList->getId(),_canvas,TeBox(),_fullPath);
										break;
		case LT_BARCODE:				obj=(TdkLayoutObject*) new TdkLayoutBarcodeObject(_objectList->getId(),_canvas,TeBox());
										break;
		case LT_VLINE_CONTROL:			obj=(TdkLayoutObject*) new TdkLayoutVerticalLineControlObject(_objectList->getId(),_canvas,TeBox());
										((TdkLayoutVerticalLineControlObject*)obj)->setCursor(_cursor);
										break;
		case LT_HLINE_CONTROL:			obj=(TdkLayoutObject*) new TdkLayoutHorizontalLineControlObject(_objectList->getId(),_canvas,TeBox());
										((TdkLayoutHorizontalLineControlObject*)obj)->setCursor(_cursor);
										break;
	}
	return obj;
}

///////////////////////////////////////////////////////////////////////////////
//Insert Object To List
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::insertObjectToList(TdkLayoutObject *obj, const bool &isSelected)
{
	if(obj == 0 ) return;

	_objectList->add(obj,isSelected);		
	_objectList->setMaxId(obj->getId());
	_objectList->resetLayoutObjectMode();
	_newObject=NULL;
	_loked=false;
}

///////////////////////////////////////////////////////////////////////////////
//Set Application Path
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::setPath(const std::string &path)
{
	_fullPath=path;
}

///////////////////////////////////////////////////////////////////////////////
//Set Databse logo
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::setDatabaseLogo(TdkAbstractImage *logo)
{
	_databaseLogo=logo;
}

///////////////////////////////////////////////////////////////////////////////
//Set Clipboard object
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::setClipboard(TdkAbstractClipboard *clipboard)
{
	_clipboard=clipboard;
}

///////////////////////////////////////////////////////////////////////////////
//Copy Layout Objects to memory
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::copyToClipboard()
{
	unsigned char *buffer;
	unsigned int  size;
	TdkXmlExportLayout exportT(this);
	buffer=exportT.exportToMemory(size);
	if( (buffer != 0) && (_clipboard !=0) )
	{
		_clipboard->copy(buffer,size);
		delete buffer;
		_pasteDisplacement=5;
	}
	if(_events)		_events->endProcessEvent(false);
}

///////////////////////////////////////////////////////////////////////////////
//Paste layout objects from Memory
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutController::pasteFromClipboard()
{
	TdkXmlImportLayout		importT(this);
	unsigned char			*buffer=0;
	unsigned int			size;

	if(_clipboard != 0)
	{
		buffer=_clipboard->paste(size);
		if(buffer)
		{
			this->_objectList->unSelectAll();
			importT.importFromMemory(buffer,size,_pasteDisplacement,_pasteDisplacement,true);
			delete buffer;
			update();
			refresh();
			_pasteDisplacement+=5;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Returns if clipboard is empty (to layout objects)
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
bool  TdkLayoutController::clipboardIsEmpty()
{
	if(_clipboard != 0) 
		return _clipboard->isEmpty();
	return true;
}