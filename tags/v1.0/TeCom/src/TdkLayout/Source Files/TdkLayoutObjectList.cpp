#include <TdkLayoutTypes.h> 
#include <TdkLayoutObject.h>
#include <TdkLayoutObjectList.h>
#include <TdkMouseEvent.h>
#include <TeGeometryAlgorithms.h>
#include <TdkAbstractCanvasDraw.h>
#include <TdkCanvasTypes.h>
#include <TdkAbstractCursor.h>


///////////////////////////////////////////////////////////////////////////////
//Empty Constructor
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

TdkLayoutObjectList::TdkLayoutObjectList(TdkAbstractCursor *cursor)
{
	_autoNumber=1;
	_bMouseClicked=false;
	_canvas=NULL;
	_process=None;
	_cursor=cursor;
	_objectEdition=NULL;
	_createObject=false;
	_id=1;
	_mapMode=MapMode::None;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

TdkLayoutObjectList::~TdkLayoutObjectList()
{
	clear();
}

///////////////////////////////////////////////////////////////////////////////
//Set canvas pointer
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::setCanvas(TdkAbstractCanvasDraw* canvas)
{
	_canvas=canvas; 
}

///////////////////////////////////////////////////////////////////////////////
//Add new Layout Object for List
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::add(TdkLayoutObject* object, const bool &isSelected)
{
	_objectList.push_back(object);
	if(isSelected == true)	_selectObjectList.push_back(object);
	_autoNumber++;
}

///////////////////////////////////////////////////////////////////////////////
//Sets the max id
//Author	: Rui Maurício Gregório
//Date		: 08/2010
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::setMaxId(const unsigned int &id)
{
	if(id>=_id)	_id= id + 1;
}

///////////////////////////////////////////////////////////////////////////////
//Remove a layout object from List by your unique id
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::remove(const unsigned int id)
{
	vector<TdkLayoutObject*>::iterator it;

	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)
	{
		if((*it)->getId()==id)		_selectObjectList.erase(it);
	}

	for(it=_objectList.begin();it!=_objectList.end();it++)
	{
		if((*it)->getId()==id)
		{
			delete (*it);
			_objectList.erase(it);
		}
	}
	
}

///////////////////////////////////////////////////////////////////////////////
//Remove a layout object from list by your name
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::remove(const std::string &name)
{
	vector<TdkLayoutObject*>::iterator it;

	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)
	{
		if((name.compare((*it)->getName())==0))		_selectObjectList.erase(it);
	}


	for(it=_objectList.begin();it!=_objectList.end();it++)
	{
		if((name.compare((*it)->getName())==0))
		{
			delete (*it);
			_objectList.erase(it);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Remove selecteds layout object from list
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::removeSelected()
{
	vector<TdkLayoutObject*>::iterator it;

	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)
	{
		(*it)->setSelect();
	}

	it=_objectList.begin();
	while(it!=_objectList.end())
	{
		if((*it)->isSelected()==true)
		{
			delete (*it);
			_objectList.erase(it);
			it=_objectList.begin();
		}else it++;
	}
	_selectObjectList.clear();
}

///////////////////////////////////////////////////////////////////////////////
//Clear object List - remove and destroy all objects
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::clear()
{
	vector<TdkLayoutObject*>::iterator it;
	_selectObjectList.clear();
	for(it=_objectList.begin();it!=_objectList.end();it++)	delete (*it);
	_objectList.clear();
	_id=1;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the layout object by your unique identify
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

TdkLayoutObject* TdkLayoutObjectList::getObject(const unsigned int &id)
{
	vector<TdkLayoutObject*>::iterator it;

	for(it=_objectList.begin();it!=_objectList.end();it++)
	{
		if((*it)->getId()==id)
		{
			return (*it);
		}
	}
	return NULL;
}


///////////////////////////////////////////////////////////////////////////////
//Returns the layout object by your name
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

TdkLayoutObject* TdkLayoutObjectList::getObject(const std::string &name)
{
	vector<TdkLayoutObject*>::iterator it;

	for(it=_objectList.begin();it!=_objectList.end();it++)
	{
		if((TeConvertToUpperCase(name).compare(TeConvertToUpperCase((*it)->getName()))==0))
		{
			return (*it);
		}
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the layout object list selected
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

objectList TdkLayoutObjectList::getSelectObject()
{
	return _selectObjectList;
}

///////////////////////////////////////////////////////////////////////////////
//Erase selected layout object
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::eraseSelected()
{
	int i;

	for(i=(int)_objectList.size()-1; i>=0 ;i--)
	{
		if(_objectList[i]->isSelected()==true)	
			_objectList.erase(_objectList.begin() + i);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Add a layout object vector to front or back list
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::addVectorObject(objectList vector,const bool &back)
{
	objectList::iterator it;
	for(it=vector.begin();it!=vector.end();it++)
	{
		if(back)	_objectList.push_back(*it);
		else		_objectList.insert(_objectList.begin(),*it);
	}
}

///////////////////////////////////////////////////////////////////////////////
//
////tem que reimplementar
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::sendToBack()
{
	vector<TdkLayoutObject*> selected;

	selected=getSelectObject();
	eraseSelected();
	addVectorObject(selected,false);
}

///////////////////////////////////////////////////////////////////////////////
//
////tem que reimplementar
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::bringToFront()
{
	vector<TdkLayoutObject*> selected;

	selected=getSelectObject();
	eraseSelected();
	addVectorObject(selected);
}

///////////////////////////////////////////////////////////////////////////////
//Align the layout objects selected in left side
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::leftAlignment()
{
	objectList::iterator	it;
	TeBox					box;
	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)	updateBox(box,(*it)->getBox());
	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)	(*it)->setLeftBox(box);
}

///////////////////////////////////////////////////////////////////////////////
//Align the layout objects selected in right side
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::rightAlignment()
{
	objectList::iterator	it;
	TeBox					box;
	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)	updateBox(box,(*it)->getBox());
	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)	(*it)->setRightBox(box);
}

///////////////////////////////////////////////////////////////////////////////
//Align the layout objects selected in bottom side
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::bottomAlignment()
{
	objectList::iterator	it;
	TeBox					box;
	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)	updateBox(box,(*it)->getBox());
	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)	(*it)->setBottomBox(box);
}

///////////////////////////////////////////////////////////////////////////////
//Align the layout objects selected in top side
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::topAlignment()
{
	objectList::iterator	it;
	TeBox					box;
	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)	updateBox(box,(*it)->getBox());
	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)	(*it)->setTopBox(box);
}

///////////////////////////////////////////////////////////////////////////////
//Align the select objects in page center
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::horizontalCenter(const double &cx)
{
	objectList::iterator	it;
	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)	(*it)->setHorizontalCenter(cx);
}

///////////////////////////////////////////////////////////////////////////////
//Align the select objects in page center
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::verticalCenter(const double &cy)
{
	objectList::iterator	it;
	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)	(*it)->setVerticalCenter(cy);
}

///////////////////////////////////////////////////////////////////////////////
//Mouse Move Event
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::mouseMove(TdkMouseEvent *e)
{
	
	mouseProcessMove(e);
	//if(_process==ObjectProcess)	
	{
		objectList::iterator	it;
		if(_bMouseClicked) e->Button=TdkMouseEvent::Left;
		for(it=_objectList.begin();it!=_objectList.end();it++) (*it)->mouseMove(e);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Mouse Down Event
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::mouseDown(TdkMouseEvent *e,const bool &bCtrl)
{
	hotPoint				ctrl;
	
	_bMouseClicked=true;
	_downClickCoord=TeCoord2D(e->X,e->Y);
	_lastCoord=_downClickCoord;


	if( (e->Button == TdkMouseEvent::Left) && (_createObject) && ( bCtrl == false) )
	{
		_process=CreateObject;
	}else if(((clickOverHotPoint(TeCoord2D(e->X,e->Y),ctrl))==true) && (e->Button==TdkMouseEvent::Left))
	{
		_process=(layoutProcess) (ctrl + 3);
	}else if(clickOverSelected(_downClickCoord) && (e->Button==TdkMouseEvent::Left) && (_mapMode!=MapMode::None))
	{	
		_process=ObjectProcess;
	}else if(clickOverSelected(_downClickCoord)  && (e->Button==TdkMouseEvent::Left) && ( bCtrl == false))
	{
		_process=MoveObject;
		if(_cursor) _cursor->setCursor(CursorAll);
	}else if(select(_downClickCoord,bCtrl) && (e->Button==TdkMouseEvent::Left))
	{
		_process=MoveObject;
		if(_cursor) _cursor->setCursor(CursorAll);
	}else if( (e->Button == TdkMouseEvent::Left) && (bCtrl == false) )
	{
		_process=SelectByBox;
	}
   
	if(_process==ObjectProcess)
	{
		setMapProcess(_mapMode);
		objectList::iterator	it;
		for(it=_objectList.begin();it!=_objectList.end();it++) (*it)->mouseDown(e);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Mouse Up Event
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::mouseUp(TdkMouseEvent *e, const bool &bCtrl)
{
	 mouseProcessUp(e,bCtrl);
	_bMouseClicked=false;
	//if(_cursor) _cursor->setCursor(CursorNormal);
	_objectEdition=NULL;
	if(_process==ObjectProcess)
	{
		objectList::iterator	it;
		for(it=_objectList.begin();it!=_objectList.end();it++) (*it)->mouseUp(e);
	}
	_process=None;
}

///////////////////////////////////////////////////////////////////////////////
//Update objects ( re-draw)
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::update()
{
	objectList::iterator	it;

	for(it=_objectList.begin();it!=_objectList.end();it++) (*it)->update();
}

///////////////////////////////////////////////////////////////////////////////
//Update select objects ( re-draw selection )
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::updateSelection()
{
	objectList::iterator	it;

	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++) (*it)->updateSelection();
}

///////////////////////////////////////////////////////////////////////////////
//Returns the object's quantity
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
unsigned int TdkLayoutObjectList::size()
{
	return (unsigned int)_objectList.size();
}

///////////////////////////////////////////////////////////////////////////////
//Select Object by click
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutObjectList::select(const TeCoord2D &coord, const bool &ctrl)
{
	objectList::reverse_iterator	it;
	
	if(!ctrl)	
	{
		objectList::iterator ito;
		for(ito=_selectObjectList.begin();ito!=_selectObjectList.end();ito++)	(*ito)->setSelect(false);
		_selectObjectList.clear();
	}
	for(it=_objectList.rbegin();it!=_objectList.rend();it++) 
	{
		if((*it)->clickOver(coord) == true)
		{
			insertRemove(*it);
			return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Select Object by name
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutObjectList::select(const std::string &objName)
{
	objectList::iterator			it;

	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)	(*it)->setSelect(false);
	_selectObjectList.clear();

	for(it=_objectList.begin();it!=_objectList.end();it++)
	{
		if(!(*it)->getName().compare(objName))
		{
			insertRemove(*it);
			return true;
		}
	}
	return false;

}

///////////////////////////////////////////////////////////////////////////////
//Select Objects by Box
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutObjectList::selectBox(const TeCoord2D &init, const TeCoord2D &end)
{
	TeLine2D						lneBox;
	TeBox							box;
	bool							status=false;
	objectList::reverse_iterator	it;

	lneBox.add(init);
	lneBox.add(TeCoord2D(end.x(),init.y()));
	lneBox.add(TeCoord2D(end.x(),end.y()));
	lneBox.add(TeCoord2D(init.x(),end.y()));
	box=lneBox.box();

	objectList::iterator ito;
	for(ito=_selectObjectList.begin();ito!=_selectObjectList.end();ito++)	(*ito)->setSelect(false);
	_selectObjectList.clear();
	
	for(it=_objectList.rbegin();it!=_objectList.rend();it++) 
	{
		if((*it)->boxOver(box)==true)	
		{
			status=true;
			insertRemove(*it);
		}
	}
	return status;
}

///////////////////////////////////////////////////////////////////////////////
//Check whether click is over object
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutObjectList::clickOverSelected(const TeCoord2D &coord)
{
	objectList::reverse_iterator	it;

	for(it=_selectObjectList.rbegin();it!=_selectObjectList.rend();it++) 
	{
		if((*it)->clickOver(coord)==true)
		{

			objectList::reverse_iterator	ito;
			for(ito=_objectList.rbegin();ito!=_objectList.rend();ito++) 
				{
					if((*ito)->clickOver(coord) == true)
					{

						if((*ito)->getName()!=(*it)->getName())		return false;
						else										return true;
					}
				}
			return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Insert object or remove when this added in object list
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::insertRemove(TdkLayoutObject* obj)
{
	objectList::iterator	it;

	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)
	{
		if((*it)->getId() == obj->getId())
			break;
	}
	if(it==_selectObjectList.end())	
	{
		_selectObjectList.push_back(obj);
		obj->setSelect();
	}
	else							
	{
		obj->setSelect(false);
		_selectObjectList.erase(it);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Update bounding box each object selected
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutObjectList::updateObjectsBoundingBox(const TeCoord2D &init, const TeCoord2D &final)
{
	objectList::iterator	it;
	double					dx;
	double					dy;
	TeBox					box;

	dx=final.x() - init.x();
	dy=final.y() - init.y();

	if( (dx == 0) && (dy == 0) ) return false;


	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)
	{
		box=(*it)->getBox();
		box=TeBox(box.x1() + dx, box.y1() + dy, box.x2() + dx, box.y2() + dy);
		(*it)->setBoundingBox(box);
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Move the bounding Box for each object selected
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::moveBoundingBox(TdkMouseEvent *e)
{
	objectList::iterator	it;
	double					dx,dy;
	TeCoord2D				coord;

	if(_cursor) _cursor->setCursor(CursorAll);
	coord=TeCoord2D(e->X,e->Y);

	if(!TeEquals(coord,_lastCoord))
	{
		dx=_lastCoord.x() - _downClickCoord.x();
		dy=_lastCoord.y() - _downClickCoord.y();
		for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++) (*it)->drawTranslateProcess(dx,dy);
	}
	_lastCoord=coord;
	dx=_lastCoord.x() - _downClickCoord.x();
	dy=_lastCoord.y() - _downClickCoord.y();
	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++) (*it)->drawTranslateProcess(dx,dy);
}

///////////////////////////////////////////////////////////////////////////////
//Draw Select box for each object selected
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::drawSelectBox(const TeCoord2D &init, const TeCoord2D &end)
{
	int		bufferId;
	double	w,h;

	if(!_canvas)	return;

	bufferId=_canvas->getActiveBuffer();
	_canvas->setActiveBuffer(TdkAbstractCanvasDraw::cbrFront);
	_canvas->setLineColor(128,128,128);
	_canvas->setLineType(LineSettings::DashStyleSolid);
	_canvas->setPaintMode(TdkAbstractCanvasDraw::pmdXOR);
	_canvas->getDimension(w,h);
	_canvas->setClipArea(28,28,w,h);
	
	if(!TeEquals(end,_lastCoord))
	{
		_canvas->drawRectW(init.x(),init.y(),_lastCoord.x(),_lastCoord.y());
	}
	_canvas->drawRectW(init.x(),init.y(),end.x(),end.y());
	_canvas->setPaintMode(TdkAbstractCanvasDraw::pmdREPLACE);
	_canvas->deactivateClip();
	_canvas->setActiveBuffer(bufferId);
	_lastCoord=end;
}

///////////////////////////////////////////////////////////////////////////////
//Method to move selected objects using arrow keys
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::moveKey(const moveKeys &key,const bool &ctrl)
{
	TeBox					box;
	objectList::iterator	it;
	double					dx=0.0,dy=0.0;
	
	switch(key)
	{
		case TDK_LEFT : dx=(ctrl==false ? -10 : -1);
						break;
		case TDK_UP:	dy=(ctrl==false ? -10 : -1);
						break;
		case TDK_RIGHT:	dx=(ctrl==false ? 10 : 1);
						break;
		case TDK_DOWN:	dy=(ctrl==false ? 10 : 1);
						break;
	}
	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++) 
	{
		box=(*it)->getBox();
		box=TeBox(box.x1() + dx, box.y1() + dy, box.x2() + dx, box.y2() + dy);
		(*it)->setBoundingBox(box);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Method to check whether click is over control point (hot point)
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

bool TdkLayoutObjectList::clickOverHotPoint(const TeCoord2D &coord,hotPoint &controlPoint)
{
	objectList::iterator	it;
	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++) 
	{
		if((*it)->hotPointOver(coord,controlPoint))
		{
			_objectEdition=(*it);
			return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Method to change cursor by according control point (hot point)
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::setMouseCursor(const hotPoint &controlPoint )
{
	if(_cursor)
	{
		switch(controlPoint)
		{
			case LeftTop:	
			case RightBottom:
								_cursor->setCursor(CursorNWSE);
								break;
			case MiddleTop:
			case MiddleBottom:
								_cursor->setCursor(CursorNS);
								break;
			case RightTop:
			case LeftBottom:	_cursor->setCursor(CursorNESW);
								break;
			case NonePoint:		_cursor->setCursor(CursorNormal);
								break;
			case RotatePoint:	_cursor->setCursor(CursorFinger);
								break;
			case MiddleRight:
			case MiddleLeft:	_cursor->setCursor(CursorWE);
								break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Feedback to resize middle vertical bounding box
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::resizeMiddleVerticalBoundingBox(TdkMouseEvent *e, const bool &up)
{
	TeCoord2D				coord;

	if(_objectEdition == NULL) return;

	coord=TeCoord2D(e->X,e->Y);
	if(!TeEquals(coord,_lastCoord))
	{
		if(up == true)	_objectEdition->drawUpBoundingBoxProcess(_downClickCoord,_lastCoord);
		else			_objectEdition->drawDownBoundingBoxProcess(_downClickCoord,_lastCoord);
	}
	_lastCoord=coord;
	if(up == true)	_objectEdition->drawUpBoundingBoxProcess(_downClickCoord,_lastCoord);
	else			_objectEdition->drawDownBoundingBoxProcess(_downClickCoord,_lastCoord);
}


///////////////////////////////////////////////////////////////////////////////
//Feedback to resize middle horizontal bounding box
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::resizeHorizontalBoundingBox(TdkMouseEvent *e, const bool &left)
{
	double					dx;
	TeCoord2D				coord;

	if(_objectEdition == NULL) return;
	coord=TeCoord2D(e->X,e->Y);
	if(!TeEquals(coord,_lastCoord))
	{
		dx=_lastCoord.x() - _downClickCoord.x();
		if(left == true )		_objectEdition->drawLeftMiddleBoundingBoxProcess(_downClickCoord,_lastCoord);
		else					_objectEdition->drawRightMiddleBoundingBoxProcess(_downClickCoord,_lastCoord);
	}
	_lastCoord=coord;
	dx=_lastCoord.x() - _downClickCoord.x();
	if(left == true )		_objectEdition->drawLeftMiddleBoundingBoxProcess(_downClickCoord,_lastCoord);
	else					_objectEdition->drawRightMiddleBoundingBoxProcess(_downClickCoord,_lastCoord);
}

///////////////////////////////////////////////////////////////////////////////
//Feedback to resize by corner bounding box
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::resizeCornerBoundingBox(TdkMouseEvent *e, const cornerBoundingBox &corner)
{
	double					dx,dy;
	TeCoord2D				coord;

	if(_objectEdition == NULL) return;
	coord=TeCoord2D(e->X,e->Y);
	if(!TeEquals(coord,_lastCoord))
	{
		dx=_lastCoord.x() - _downClickCoord.x();
		dy=_lastCoord.y() - _downClickCoord.y();
		switch(corner)
			{ 
				case Corner_LeftTop:		_objectEdition->drawLeftTopBoundingBoxProcess(_downClickCoord,_lastCoord);
											break;
				case Corner_LeftBottom:		_objectEdition->drawLeftBottomBoundingBoxProcess(_downClickCoord,_lastCoord);
											break;
				case Corner_RightTop:		_objectEdition->drawRightTopBoundingBoxProcess(_downClickCoord,_lastCoord);
											break;
				case Corner_RightBottom:	_objectEdition->drawRightBottomBoundingBoxProcess(_downClickCoord,_lastCoord);
											break;
			}
	}
	_lastCoord=coord;
	dx=_lastCoord.x() - _downClickCoord.x();
	dy=_lastCoord.y() - _downClickCoord.y();
	switch(corner)
			{ 
				case Corner_LeftTop:		_objectEdition->drawLeftTopBoundingBoxProcess(_downClickCoord,_lastCoord);
											break;
				case Corner_LeftBottom:		_objectEdition->drawLeftBottomBoundingBoxProcess(_downClickCoord,_lastCoord);
											break;
				case Corner_RightTop:		_objectEdition->drawRightTopBoundingBoxProcess(_downClickCoord,_lastCoord);
											break;
				case Corner_RightBottom:	_objectEdition->drawRightBottomBoundingBoxProcess(_downClickCoord,_lastCoord);
											break;
			}
}

///////////////////////////////////////////////////////////////////////////////
//Update top bounding box
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::updateUpBoundingBox(const TeCoord2D &init, const TeCoord2D &end)
{
	if(_objectEdition)		_objectEdition->updateUpBoundingBox(init,end);;
}

///////////////////////////////////////////////////////////////////////////////
//Update Bottom bounding box
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::updateBottomBoundingBox(const TeCoord2D &init, const TeCoord2D &end)
{
	if(_objectEdition)		_objectEdition->updateDownBoundingBox(init,end);
}

///////////////////////////////////////////////////////////////////////////////
//Update Left bounding box
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::updateLeftBoundingBox(const TeCoord2D &init, const TeCoord2D &end)
{
	if(_objectEdition)		_objectEdition->updateLeftBoundingBox(init,end);
}

///////////////////////////////////////////////////////////////////////////////
//Update Right bounding box
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::updateRightBoundingBox(const TeCoord2D &init, const TeCoord2D &end)
{
	if(_objectEdition)		_objectEdition->updateRightBoundingBox(init,end);
}

///////////////////////////////////////////////////////////////////////////////
//Update Corner Bounding box
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::updateCornerBoundingBox(const TeCoord2D &init, const TeCoord2D &end, const cornerBoundingBox &corner)
{
	if(_objectEdition)
	{
		switch(corner)
		{
			case Corner_LeftTop:		_objectEdition->updateLeftTopBoundingBox(init,end);
										break;
			case Corner_LeftBottom:		_objectEdition->updateLeftBottomBoundingBox(init,end);
										break;
			case Corner_RightTop:		_objectEdition->updateRightTopBoundingBox(init,end);
										break;
			case Corner_RightBottom:	_objectEdition->updateRightBottomBoundingBox(init,end);
										break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Mouse Up Processing
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::mouseProcessUp(TdkMouseEvent *e, const bool &bCtrl)
{
	switch(_process)
	{
		case MoveObject	:			if(updateObjectsBoundingBox(_downClickCoord,TeCoord2D(e->X,e->Y)) == false && (bCtrl == false))	select(_downClickCoord,bCtrl);
									break;
		case SelectByBox:			selectBox(_downClickCoord,TeCoord2D(e->X,e->Y));
									break;
		case ResizeMiddleTop:		updateUpBoundingBox(_downClickCoord,TeCoord2D(e->X,e->Y));
									break;
		case ResizeBottomMiddle:	updateBottomBoundingBox(_downClickCoord,TeCoord2D(e->X,e->Y));
									break;
		case ResizeLeftMiddle:		updateLeftBoundingBox(_downClickCoord,TeCoord2D(e->X,e->Y));
									break;
		case ResizeMiddleRight:		updateRightBoundingBox(_downClickCoord,TeCoord2D(e->X,e->Y));
									break;
		case ResizeLeftTop:			updateCornerBoundingBox(_downClickCoord,TeCoord2D(e->X,e->Y),Corner_LeftTop);
									break;
		case ResizeLeftBottom:		updateCornerBoundingBox(_downClickCoord,TeCoord2D(e->X,e->Y),Corner_LeftBottom);
									break;
		case ResizeRightTop:		updateCornerBoundingBox(_downClickCoord,TeCoord2D(e->X,e->Y),Corner_RightTop);
									break;
		case ResizeBottomRight:		updateCornerBoundingBox(_downClickCoord,TeCoord2D(e->X,e->Y),Corner_RightBottom);
									break;
		case RotateObject:			updateObjectAngle(_downClickCoord,TeCoord2D(e->X,e->Y));
									break;
		case CreateObject:			
								{
									if( (_downClickCoord.x() < e->X) && (_downClickCoord.y() < e->Y) )			
										_createBox=TeBox(_downClickCoord,TeCoord2D(e->X,e->Y));
									else if((_downClickCoord.x() > e->X) && (_downClickCoord.y() < e->Y) )		
										_createBox=TeBox(TeCoord2D(e->X,_downClickCoord.y()),TeCoord2D(_downClickCoord.x(),e->Y));
									else if((_downClickCoord.x() < e->X) && (_downClickCoord.y() > e->Y) )		
										_createBox=TeBox(TeCoord2D(_downClickCoord.x(),e->Y),TeCoord2D(e->X,_downClickCoord.y()));
									else _createBox=TeBox(TeCoord2D(e->X,e->Y),_downClickCoord);
								}break;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Mouse Move Processing
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::mouseProcessMove(TdkMouseEvent *e)
{
	hotPoint				ctrl;
	if((_process == ResizeMiddleTop) && (_bMouseClicked == true))				resizeMiddleVerticalBoundingBox(e);
	else if((_process == ResizeBottomMiddle) && (_bMouseClicked == true))		resizeMiddleVerticalBoundingBox(e,false);
	else if((_process == ResizeLeftMiddle)	&& (_bMouseClicked == true))	    resizeHorizontalBoundingBox(e);
	else if((_process == ResizeMiddleRight) && (_bMouseClicked == true))		resizeHorizontalBoundingBox(e,false);
	else if((_process == ResizeLeftTop)	&& (_bMouseClicked == true))			resizeCornerBoundingBox(e,Corner_LeftTop);
	else if((_process == ResizeLeftBottom) && (_bMouseClicked == true))			resizeCornerBoundingBox(e,Corner_LeftBottom);
	else if((_process == ResizeRightTop) && (_bMouseClicked == true))			resizeCornerBoundingBox(e,Corner_RightTop);
	else if((_process == ResizeBottomRight) && (_bMouseClicked == true))		resizeCornerBoundingBox(e,Corner_RightBottom);
	else if((_process == MoveObject) && (_bMouseClicked == true))				moveBoundingBox(e);
	else if((_process == SelectByBox) && (_bMouseClicked == true) )				drawSelectBox(_downClickCoord,TeCoord2D(e->X,e->Y));
	else if((_process == CreateObject) && (_bMouseClicked == true))				drawSelectBox(_downClickCoord,TeCoord2D(e->X,e->Y));
	else if((_process == RotateObject) && (_bMouseClicked == true))				drawXorRotateBoundingBox(e);
	else if (clickOverHotPoint(TeCoord2D(e->X,e->Y),ctrl) == true)				setMouseCursor(ctrl);
	else if(_process == None)													setMouseCursor(NonePoint);
}

///////////////////////////////////////////////////////////////////////////////
//Draw Xor Rotate Bounding Box
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::drawXorRotateBoundingBox(TdkMouseEvent *e)
{

	TeCoord2D				coord;

	if(_cursor) _cursor->setCursor(CursorAll);
	coord=TeCoord2D(e->X,e->Y);

	if(!TeEquals(coord,_lastCoord))
	{
		if(_objectEdition) _objectEdition->drawRotateProcess(_downClickCoord,_lastCoord);	
	}
	_lastCoord=coord;
	if(_objectEdition) _objectEdition->drawRotateProcess(_downClickCoord,_lastCoord);	
}

///////////////////////////////////////////////////////////////////////////////
//Update object's angle
//Author	: Rui Maurício Gregório
//Date		: 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::updateObjectAngle(const TeCoord2D &init, const TeCoord2D &end)
{
	if(_objectEdition) _objectEdition->setAngle(init,end);	
}

///////////////////////////////////////////////////////////////////////////////
//Print layout object to printer
//Author	: Rui Maurício Gregório
//Date		: 06/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::print(TdkAbstractCanvasDraw *canvas)
{
	objectList::iterator	it;
	for(it=_objectList.begin();it!=_objectList.end();it++)
	{
		(*it)->print(canvas);		
	}
}

///////////////////////////////////////////////////////////////////////////////
// Returns the box to create a new layout Object
//Author	: Rui Maurício Gregório
//Date		: 06/2009
///////////////////////////////////////////////////////////////////////////////

TeBox TdkLayoutObjectList::getCreateBox()
{
	return _createBox;
}

///////////////////////////////////////////////////////////////////////////////
//createLayoutObjectMode
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::createLayoutObjectMode()
{
	_createObject=true;
}

///////////////////////////////////////////////////////////////////////////////
//resetLayoutObjectMode
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObjectList::resetLayoutObjectMode()
{
	_createObject=false;
}

///////////////////////////////////////////////////////////////////////////////
// Returns the unique id
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
unsigned int TdkLayoutObjectList::getId()
{
	unsigned int id;
	
	id=_id++; 
	return id;
}

///////////////////////////////////////////////////////////////////////////////
// Returns the object name by index
//Author : Rui Mauricio Gregório
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
std::string TdkLayoutObjectList::getObjectName(const unsigned int &index)
{
	if(index<_objectList.size())	return	_objectList[index]->getName();
	throw "Invalid index value";
}

///////////////////////////////////////////////////////////////////////////////
// Returns the select object name by index
//Author : Rui Mauricio Gregório
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
std::string TdkLayoutObjectList::getSelectObjectName(const unsigned int &index)
{
	if(index<_selectObjectList.size())	return _selectObjectList[index]->getName();
	throw "Invalid index value";
}

///////////////////////////////////////////////////////////////////////////////
// Returns The object list process mode
//Author : Rui Mauricio Gregório
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

TdkLayoutObjectList::layoutProcess TdkLayoutObjectList::getProcess()
{
	return _process;
}

///////////////////////////////////////////////////////////////////////////////
// Reset the process of object list
//Author : Rui Mauricio Gregório
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void  TdkLayoutObjectList::resetProcess()
{
	_process=TdkLayoutObjectList::None;
}

///////////////////////////////////////////////////////////////////////////////
// Set the map process
//Author : Rui Mauricio Gregório
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::setMapProcess(const MapMode &mode)
{
	_mapMode=mode;

	vector<TdkLayoutObject*>::iterator it;

	for(it=_objectList.begin();it!=_objectList.end();it++)
	{
		(*it)->setMapMode(mode);
	}
} 

///////////////////////////////////////////////////////////////////////////////
// Set the full update
//Author : Rui Mauricio Gregório
//Date : 07/2010
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObjectList::setFullUpdate()
{
	vector<TdkLayoutObject*>::iterator it;

	for(it=_selectObjectList.begin();it!=_selectObjectList.end();it++)
	{
		(*it)->setNecessaryUpdate();
	}
}

objectList TdkLayoutObjectList::getList()
{
	return _objectList;
}



void TdkLayoutObjectList::resizeAllObjects(const double &oldW, const double &oldH, const double &newW, const double &newH)
{
	vector<TdkLayoutObject*>::iterator			it;
	TeBox										box;
	double										x1,x2;
	double										y1,y2;

	for(it=_objectList.begin();it!=_objectList.end();it++)
	{
		box=(*it)->getBox();
		x1= (box.x1() * newW)/oldW;
		x2= (box.x2() * newW)/oldW;
		y1= (box.y1() * newH)/oldH;
		y2= (box.y2() * newH)/oldH;
		(*it)->setBoundingBox(TeBox(x1,y1,x2,y2));
		(*it)->setRatio(newH/oldH);
		(*it)->setNecessaryUpdate();
	}
}


void TdkLayoutObjectList::unSelectAll()
{
	_selectObjectList.clear();
}