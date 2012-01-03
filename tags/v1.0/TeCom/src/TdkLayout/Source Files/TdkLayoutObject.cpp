#include <TdkAbstractCanvasDraw.h>
#include <TdkCanvasTypes.h>
#include <TdkLayoutTypes.h>
#include <TdkLayoutObject.h>
#include <TdkGeomTransformationUtils.h>
#include <TeGeometryAlgorithms.h>
#include <TdkMouseEvent.h>
#include <TdkLeftProperty.h>
#include <TdkTopProperty.h>
#include <TdkWidthProperty.h>
#include <TdkHeightProperty.h>
#include <TdkAngleProperty.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor with canvas pointer such as parameter
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
TdkLayoutObject::TdkLayoutObject(const int &id, TdkAbstractCanvasDraw *canvas)
{
	_decoratedPropertyList.clear();
	_canvas=canvas;
	_backColor=TeColor(255,255,255);
	_visibleContourBox=true;
	_selected=false;
	_visible=true;
	_enabled=false;
	_angle=0;
	_boundingBox=TeBox();
	_id=0;
	_objectName="layout_object_" + Te2String(id,0);
	_type=LT_UNDEFINED;
	_lockResize=false;
	_id=id;
	_necessaryRedraw=true;
	_stopDispatch=false;
	_mousePress=false;
	_editable=true;
	registerProperties();
	
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

TdkLayoutObject::~TdkLayoutObject()
{
	std::vector<TdkAbstractProperty*>::iterator it;
	for(it=_properties.begin();it!=_properties.end();it++)
	{
		delete (*it);
	}
	_properties.clear();
	_angle=NULL;
	disassociateObjectProperty();

}

///////////////////////////////////////////////////////////////////////////////
//Register Default Properties
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::registerProperties()
{
	_left=new TdkLeftProperty();
	_left->_value=&_boundingBox.x1_;
	_left->_rightValue=&_boundingBox.x2_;
	_properties.push_back((TdkAbstractProperty*)_left);

	_top=new TdkTopProperty();
	_top->_value=&_boundingBox.y1_;
	_top->_bottomValue=&_boundingBox.y2_;
	_properties.push_back(_top);

	_width= new TdkWidthProperty();
	_width->_x1=&_boundingBox.x1_;
	_width->_x2=&_boundingBox.x2_;
	_width->_redraw=&_necessaryRedraw;
	_properties.push_back((TdkAbstractProperty*)_width);

	_height=new TdkHeightProperty();
	_height->_y1=&_boundingBox.y1_;
	_height->_y2=&_boundingBox.y2_;
	_height->_redraw=&_necessaryRedraw;
	_properties.push_back((TdkAbstractProperty*)_height);

	_angle= new TdkAngleProperty();
	_properties.push_back((TdkAbstractProperty*)_angle);

}

///////////////////////////////////////////////////////////////////////////////
//getPropertyValue according the index
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
TdkAbstractProperty * TdkLayoutObject::getPropertyValue(const unsigned int &index)
{
	if(index>=_properties.size()) return NULL;
	return _properties[index];
}

///////////////////////////////////////////////////////////////////////////////
//getPropertyValue according the property name
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
TdkAbstractProperty * TdkLayoutObject::getPropertyValue(const std::string &propertyName)
{
	std::vector<TdkAbstractProperty*>::iterator it;

	for(it=_properties.begin();it!=_properties.end();it++)
	{
		if((TeConvertToUpperCase(propertyName).compare(TeConvertToUpperCase((*it)->name()))==0))
		{
			return (*it);
		}
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
//Set object back color
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setBackColor(const TeColor &color)
{
	_backColor=color;
}

///////////////////////////////////////////////////////////////////////////////
//Set Visible ContourBox
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::setVisibleContourBox(const bool &status)
{
	_visibleContourBox=status;
}

///////////////////////////////////////////////////////////////////////////////
//Set Visible Object
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setVisible(const bool &status)
{
	_visible=status;
}

///////////////////////////////////////////////////////////////////////////////
//Set Enable Object
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setEnabled(const bool &status)
{
	_enabled=status;
}

///////////////////////////////////////////////////////////////////////////////
//Set Angle's object
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setAngle(const double &angle)
{
	_angle->setValue(angle);
}

///////////////////////////////////////////////////////////////////////////////
//Set Bounding Box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setBoundingBox(const TeBox &box)
{
	if( (!box.isValid()) ||	(box.width() == 0 )  || (box.height() == 0) ) \
		_boundingBox=TeBox(box.center().x() - 20,box.center().y() - 10, box.center().x() + 20, box.center().y() + 10);
	else				_boundingBox=box;
}

///////////////////////////////////////////////////////////////////////////////
//Set canvas pointer
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setCanvas(TdkAbstractCanvasDraw* canvas)
{
	_canvas=canvas;
}

///////////////////////////////////////////////////////////////////////////////
//Convert a box to coordinate list
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
vector<TeCoord2D> TdkLayoutObject::boxToCoords(const TeBox &box)
{
	vector<TeCoord2D> points;

	points.push_back(TeCoord2D(box.x1(),box.y1()));
	points.push_back(TeCoord2D(box.center().x(),box.y1()));
	points.push_back(TeCoord2D(box.x2(),box.y1()));
	points.push_back(TeCoord2D(box.x2(),box.center().y()));
    points.push_back(TeCoord2D(box.x2(),box.y2()));
	points.push_back(TeCoord2D(box.center().x(),box.y2()));
	points.push_back(TeCoord2D(box.x1(),box.y2()));
	points.push_back(TeCoord2D(box.x1(),box.center().y()));
	points.push_back(TeCoord2D(box.x1(),box.y1()));
	return points;
}

///////////////////////////////////////////////////////////////////////////////
//Set clip area
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setClipClientArea()
{
	double	w,h;
	if(!_canvas)	return;
	_canvas->getDimension(w,h);
	_canvas->setClipArea(rulerSize3D ,rulerSize3D,w,h);
}

///////////////////////////////////////////////////////////////////////////////
//Subtract Ruler Area from client area
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::subtractRulerArea()
{
	double	w,h;
	if(!_canvas)	return;

	_canvas->getDimension(w,h);
	_canvas->subtractClipArea(0,0,w,30);
	_canvas->subtractClipArea(0,0,30,h);
}

///////////////////////////////////////////////////////////////////////////////
//Set clip area in world coordinate
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setClipClientAreaW(const TeBox &box, TdkAbstractCanvasDraw* canvas)
{
	double	llx,lly;
	double	urx,ury;

	if(canvas == 0) canvas=_canvas;

	if(!canvas)	return;

	canvas->window2Viewport(box.x1(),box.y1(),llx,lly);
	canvas->window2Viewport(box.x2(),box.y2(),urx,ury);
	if(_angle==0)
	{
		canvas->setClipArea(llx,lly,urx,ury);
	}else
	{
		TeLine2D	lneBox;
		TePolygon	polBox;
		lneBox.add(TeCoord2D(llx,lly));
		lneBox.add(TeCoord2D(urx,lly));
		lneBox.add(TeCoord2D(urx,ury));
		lneBox.add(TeCoord2D(llx,ury));
		polBox.add(lneBox);
		TdkRotate(polBox,polBox.box().center(),_angle->getValue());
		canvas->setClipArea(polBox);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Calculate Hot Point
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
vector<TeCoord2D> TdkLayoutObject::calculateHotPoint()
{
	vector<TeCoord2D>	hotPoints;
	hotPoints=boxToCoords(_boundingBox);
	if(_angle!=0)
		{
			//rotate the coordinates
		}
	return hotPoints;
}

///////////////////////////////////////////////////////////////////////////////
//Draw Selection Bounding Box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::drawSelectionBoundingBox(const TdkAbstractCanvasDraw::TdkCanvasBuffer &buffer)
{
	int						activeBuffer;
	unsigned int			i;
	vector<TeCoord2D>		hotPoints;

	if(!_canvas) return;
	activeBuffer=_canvas->getActiveBuffer();
	_canvas->setActiveBuffer(buffer);
	hotPoints=this->calculateHotPoint();
	TeLine2D	lneBounding;
	for(i=0;i<hotPoints.size();i++)	lneBounding.add(hotPoints[i]);

	TdkRotate(lneBounding,_boundingBox.center(),_angle->getValue());

	this->setClipClientArea();
	this->subtractRulerArea();

	
	if(_editable)
		drawRotateControlPoint(lneBounding[1],lneBounding[2]);

	_canvas->setLineColor(0,0,0);
	_canvas->setLineWidth(1);
	_canvas->setLineType(LineSettings::DashStyleSolid);
	_canvas->drawLineW(lneBounding);

	if(_editable)
	{
		_canvas->setPointColor(100,255,100);
		_canvas->setPointSize(4);
		_canvas->setPointType(PointSettings::FILL_CIRCLE);
		for(i=0;i<lneBounding.size();i++)		_canvas->drawPointW(lneBounding[i]);
		_canvas->setPointColor(0,0,0);
		_canvas->setPointType(PointSettings::CIRCLE);
		for(i=0;i<lneBounding.size();i++)		_canvas->drawPointW(lneBounding[i]);
	}

	
	
	_canvas->deactivateClip();
	_canvas->setActiveBuffer(activeBuffer);
}

///////////////////////////////////////////////////////////////////////////////
//Draw rotate control point 
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::drawRotateControlPoint(const TeCoord2D &init, const TeCoord2D &end)
{
	TeCoord2D	coordRotate;

	if(!_canvas)	return;

	coordRotate=calculateRotateControlPoint(init,end);

	_canvas->setLineColor(0,0,0);
	_canvas->setLineType(LineSettings::DashStyleSolid);
	_canvas->setLineWidth(1);
	_canvas->drawLineSegmentW(init,coordRotate);
	
	_canvas->setPointType(PointSettings::FILL_CIRCLE);
	_canvas->setPointColor(100,255,100);
	_canvas->setPointSize(4);
	_canvas->drawPointW(coordRotate);

	_canvas->setPointType(PointSettings::CIRCLE);
	_canvas->setPointColor(0,0,0);
	_canvas->drawPointW(coordRotate);
}



///////////////////////////////////////////////////////////////////////////////
//Draw Translate Process
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::drawTranslateProcess(const double &dx, const double &dy)
{

	TeBox		box;
	TeCoord2D	coordOut;

	if(!_canvas)	return;
	
	box=TeBox(_boundingBox.x1() + dx, _boundingBox.y1() + dy, _boundingBox.x2() + dx, _boundingBox.y2() + dy);
	drawXorBox(box,box.center(),_angle->getValue());
}

///////////////////////////////////////////////////////////////////////////////
//Draw Resize Process
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::drawResizeProcess()
{

}

///////////////////////////////////////////////////////////////////////////////
//Returns the object type
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
objectType TdkLayoutObject::getType()
{
	return _type;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the object id
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
unsigned int TdkLayoutObject::getId()
{
	return _id;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the object name
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
std::string TdkLayoutObject::getName()
{
	return _objectName;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the object whether selected
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

bool TdkLayoutObject::isSelected()
{
	return _selected;
}

///////////////////////////////////////////////////////////////////////////////
// Selects the object
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::setSelect(const bool &sel)
{
	_selected=sel;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the object's bounding box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
TeBox TdkLayoutObject::getBox()
{
	return _boundingBox;
}

///////////////////////////////////////////////////////////////////////////////
//Adjust left corner bounding box 
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setLeftBox(const TeBox &box)
{
	double	width;
	width=_boundingBox.width();
	_boundingBox=TeBox(box.x1(),_boundingBox.y1(),box.x1() + width, _boundingBox.y2());
}

///////////////////////////////////////////////////////////////////////////////
//Adjust right corner from bounding box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setRightBox(const TeBox &box)
{
	double	width;
	width=_boundingBox.width();
	_boundingBox=TeBox(box.x2() - width,_boundingBox.y1(),box.x2(), _boundingBox.y2());
}

///////////////////////////////////////////////////////////////////////////////
//Adjust the bottom to bounding box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setBottomBox(const TeBox &box)
{
	double height;
	height=_boundingBox.height();
	_boundingBox=TeBox(_boundingBox.x1(),box.y2() - height, _boundingBox.x2(),box.y2());
}

///////////////////////////////////////////////////////////////////////////////
//Adjust the top to bounding box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setTopBox(const TeBox &box)
{
	double height;
	height=_boundingBox.height();
	_boundingBox=TeBox(_boundingBox.x1(),box.y1(), _boundingBox.x2(),box.y1() + height );
}

///////////////////////////////////////////////////////////////////////////////
//Set object to horizontal center page
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setHorizontalCenter(const double &xc)
{
	double dx;

	dx=_boundingBox.center().x() - xc;
	_boundingBox=TeBox(_boundingBox.x1() - dx, _boundingBox.y1(),_boundingBox.x2() - dx,_boundingBox.y2());
}

///////////////////////////////////////////////////////////////////////////////
//Set object to vertical center page
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setVerticalCenter(const double &yc)
{
	double dy;
	dy=_boundingBox.center().y() - yc;
	_boundingBox=TeBox(_boundingBox.x1(),_boundingBox.y1() - dy, _boundingBox.x2(), _boundingBox.y2() - dy);
}

///////////////////////////////////////////////////////////////////////////////
//Not used
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::mouseMove(TdkMouseEvent *e)
{

}

///////////////////////////////////////////////////////////////////////////////
//Not used
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::mouseDown(TdkMouseEvent *e)
{
	_mousePress=true;
}

///////////////////////////////////////////////////////////////////////////////
//Not used
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::mouseUp(TdkMouseEvent *e)
{
	_mousePress=false;
}

///////////////////////////////////////////////////////////////////////////////
//Update object ( re-draw )
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::update()
{
	TeBox	box;
	if(_canvas) 
	{
		_canvas->getWindow(box);
		if(TeDisjoint(_boundingBox,box)) return;
		this->draw();
	}
}

///////////////////////////////////////////////////////////////////////////////
//Update Selection ( redraw selection)
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::drawSelection(const TdkAbstractCanvasDraw::TdkCanvasBuffer &buffer)
{
	int bufferId;
	if( !_canvas )	return;
	bufferId=_canvas->getActiveBuffer();
	_canvas->setActiveBuffer(buffer);
	this->setClipClientAreaW(_boundingBox);
	this->subtractRulerArea();
	drawSelectionBoundingBox(buffer);
	_canvas->deactivateClip();
	_canvas->setActiveBuffer(bufferId);
}

///////////////////////////////////////////////////////////////////////////////
//Update Selection
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::updateSelection()
{
	this->drawSelection();
}

///////////////////////////////////////////////////////////////////////////////
//Check whether click is over object
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutObject::clickOver(const TeCoord2D &coord)
{
	std::vector<TeCoord2D>					coords;
	std::vector<TeCoord2D>::iterator		it;
	TeLine2D								lneBox;
	TePolygon								polBox;

	coords=boxToCoords(_boundingBox);
	for(it=coords.begin();it!=coords.end();it++) lneBox.add((*it));
	polBox.add(lneBox);
	TdkRotate(polBox,polBox.box().center(),_angle->getValue());
	
	if(TeRelation(coord,polBox)!=TeOUTSIDE)	return true;
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Check whether box is over object
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutObject::boxOver(const TeBox &box)
{
	return TeWithin(_boundingBox,box);
}

///////////////////////////////////////////////////////////////////////////////
//calculateRotateControlPoint
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
TeCoord2D TdkLayoutObject::calculateRotateControlPoint(const TeCoord2D &init, const TeCoord2D &end)
{
	TeCoord2D		coordRotate;
	TeCoord2D		p0,p1;
	double			x,y;
	TeCoord2D		vInit;
	TeCoord2D		vEnd;
	
	if(_canvas == 0) return coordRotate;

	_canvas->window2Viewport(init.x(),init.y(),x,y);
	vInit=TeCoord2D(x,y);

	_canvas->window2Viewport(end.x(),end.y(),x,y);
	vEnd=TeCoord2D(x,y);

	TdkRotate(vInit,vEnd,-90,coordRotate);
	TdkAdjustCoordinate(vInit,coordRotate,__rotateSize,p0,p1);
	_canvas->viewport2Window(p1.x(),p1.y(),x,y);
	p1=TeCoord2D(x,y);
	return p1;
}

///////////////////////////////////////////////////////////////////////////////
//Check whether coordinate is over hot point
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutObject::hotPointOver(const TeCoord2D &coord, hotPoint &ctrl)
{
	double									tolerance=1.0;
	TeBox									box;
	std::vector<TeCoord2D>					vecCoord;
	unsigned int							i;
	TeLine2D								lneBoundingBox;
	TeLine2D::iterator						itLne;
	std::vector<TeCoord2D>::iterator		it;
	
	if(!_canvas || !_editable)	return false;
	
	_canvas->getWindow(box);
	tolerance*=((box.height()>box.width() ? box.height() : box.width())/_constTolerance);
	box=TeBox(coord.x() - tolerance, coord.y() - tolerance, coord.x() + tolerance, coord.y() + tolerance);
	vecCoord=boxToCoords(_boundingBox);

	for(it=vecCoord.begin();it!=vecCoord.end();it++)	lneBoundingBox.add(*it);
	TdkRotate(lneBoundingBox,_boundingBox.center(),_angle->getValue());
	vecCoord.clear();
	for(itLne=lneBoundingBox.begin();itLne!=lneBoundingBox.end();itLne++) vecCoord.push_back(*itLne);
	vecCoord.push_back(calculateRotateControlPoint(vecCoord[1],vecCoord[2]));
	for(i=0;i<vecCoord.size();i++)
	{
		if(!TeDisjoint(vecCoord[i],box))
		{
			ctrl=(hotPoint)i;
			return true;
		}
	}
	ctrl=NonePoint;
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Get Displacement
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::getDisplacement(const TeCoord2D &init, const TeCoord2D &end, const TeCoord2D &center,\
									  const double &angle, double &dx, double &dy)
{
	TeCoord2D	initRotated=init;
	TeCoord2D	endRotated=end;;
	if(angle)
	{
		TdkRotate(center,init,-_angle->getValue(),initRotated);
		TdkRotate(center,end,-_angle->getValue(),endRotated);
	}
	dy=endRotated.y()-initRotated.y();
	dx=endRotated.x()-initRotated.x();
}

///////////////////////////////////////////////////////////////////////////////
//Draw Up Bounding Box Resize Process
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::drawUpBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox		box;
	double		dy;
	double		dx;

	getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
	if((_boundingBox.y1() + dy)>_boundingBox.y2()) return;
	box=TeBox(_boundingBox.x1() , _boundingBox.y1() + dy, _boundingBox.x2() , _boundingBox.y2());
	drawXorBox(box,_boundingBox.center(),_angle->getValue());
}

///////////////////////////////////////////////////////////////////////////////
//Update Up Bounding Box size
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::updateUpBoundingBox(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox						box;
	double						dy;
	double						dx;
	std::vector<TeCoord2D>		coordsBox;
	std::vector<TeCoord2D>		coordsBoundingBox;
	TeLine2D					lneBox,lneBoundingBox;
	unsigned int				i;

	if(!_lockResize)
	{
		getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
		if(_angle==0) dx=0;
		if((_boundingBox.y1() + dy)>_boundingBox.y2()) return;
		box=TeBox(_boundingBox.x1(), _boundingBox.y1() + dy, _boundingBox.x2(), _boundingBox.y2());

		if(_angle==0)
		{
			_boundingBox=box;	
		}
		else
		{
			coordsBox=this->boxToCoords(box);
			coordsBoundingBox=this->boxToCoords(_boundingBox);
			for(i=0;i<coordsBox.size();i++)
			{
				lneBox.add(coordsBox[i]);
				lneBoundingBox.add(coordsBoundingBox[i]);
			}
			TdkRotate(lneBox,lneBox.box().center(),_angle->getValue());
			TdkRotate(lneBoundingBox,lneBoundingBox.box().center(),_angle->getValue());

			dx=lneBox[4].x() - lneBoundingBox[4].x();
			dy=lneBox[4].y() - lneBoundingBox[4].y();
			lneBox=TdkTranslate(lneBox,dx,dy);
			TdkRotate(lneBox,lneBox.box().center(),-_angle->getValue());
			_boundingBox=lneBox.box();
		}
		_necessaryRedraw=true;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw Down BoundingBox Resize Process
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::drawDownBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox	box;
	double	dy;
	double  dx;

	getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
	if((_boundingBox.y2() + dy)<_boundingBox.y1()) return;
	box=TeBox(_boundingBox.x1() , _boundingBox.y1(), _boundingBox.x2() , _boundingBox.y2() + dy);
	drawXorBox(box,_boundingBox.center(),_angle->getValue());
}

///////////////////////////////////////////////////////////////////////////////
//Update Down Bounding Box size
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::updateDownBoundingBox(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox						box;
	double						dy;
	double						dx;
	std::vector<TeCoord2D>		coordsBox;
	std::vector<TeCoord2D>		coordsBoundingBox;
	TeLine2D					lneBox,lneBoundingBox;
	unsigned int				i;

	if(!_lockResize)
	{
		getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
		if((_boundingBox.y2() + dy)<_boundingBox.y1()) return;
		box=TeBox(_boundingBox.x1() , _boundingBox.y1(), _boundingBox.x2() , _boundingBox.y2() + dy);
		if(_angle==0)
		{
			_boundingBox=box;	
		}
		else
		{
			coordsBox=this->boxToCoords(box);
			coordsBoundingBox=this->boxToCoords(_boundingBox);
			for(i=0;i<coordsBox.size();i++)
			{
				lneBox.add(coordsBox[i]);
				lneBoundingBox.add(coordsBoundingBox[i]);
			}
			TdkRotate(lneBox,lneBox.box().center(),_angle->getValue());
			TdkRotate(lneBoundingBox,lneBoundingBox.box().center(),_angle->getValue());

			dx=lneBox[0].x() - lneBoundingBox[0].x();
			dy=lneBox[0].y() - lneBoundingBox[0].y();
			lneBox=TdkTranslate(lneBox,dx,dy);
			TdkRotate(lneBox,lneBox.box().center(),-_angle->getValue());
			_boundingBox=lneBox.box();
		}
		_necessaryRedraw=true;
	}
}


///////////////////////////////////////////////////////////////////////////////
//Draw Left Middle Bounding box Resize Process
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::drawLeftMiddleBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox	box;
	double	dx;
	double  dy;

	getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
	if((_boundingBox.x1() + dx)>_boundingBox.x2()) return;
	box=TeBox(_boundingBox.x1()  + dx, _boundingBox.y1(), _boundingBox.x2() , _boundingBox.y2());
	drawXorBox(box,_boundingBox.center(),_angle->getValue());
}

///////////////////////////////////////////////////////////////////////////////
//Draw Right Middle Bounding Box Resize Process
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::drawRightMiddleBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox	box;
	double	dx;
	double  dy;

	getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
	if((_boundingBox.x2() + dx)<_boundingBox.x1()) return;
	box=TeBox(_boundingBox.x1() , _boundingBox.y1(), _boundingBox.x2()  + dx, _boundingBox.y2());
	drawXorBox(box,_boundingBox.center(),_angle->getValue());
}

///////////////////////////////////////////////////////////////////////////////
//Update right Bounding Box 
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::updateRightBoundingBox(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox						box;
	std::vector<TeCoord2D>		coordsBox;
	std::vector<TeCoord2D>		coordsBoundingBox;
	TeLine2D					lneBox,lneBoundingBox;
	unsigned int				i;
	double						dx,dy;
	
	if(!_lockResize)
	{
		getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
		if((_boundingBox.x2() + dx)<_boundingBox.x1()) return;
		box=TeBox(_boundingBox.x1() , _boundingBox.y1() , _boundingBox.x2() + dx, _boundingBox.y2());
		if(_angle==0)
		{
			_boundingBox=box;	
		}
		else
		{
			coordsBox=this->boxToCoords(box);
			coordsBoundingBox=this->boxToCoords(_boundingBox);
			for(i=0;i<coordsBox.size();i++)
			{
				lneBox.add(coordsBox[i]);
				lneBoundingBox.add(coordsBoundingBox[i]);
			}
			TdkRotate(lneBox,lneBox.box().center(),_angle->getValue());
			TdkRotate(lneBoundingBox,lneBoundingBox.box().center(),_angle->getValue());

			dx=lneBox[0].x() - lneBoundingBox[0].x();
			dy=lneBox[0].y() - lneBoundingBox[0].y();
			lneBox=TdkTranslate(lneBox,dx,dy);
			TdkRotate(lneBox,lneBox.box().center(),-_angle->getValue());
			_boundingBox=lneBox.box();
		}
		_necessaryRedraw=true;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw Left Top Bounding Box Resize Process
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::drawLeftTopBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox	box;
	double	dx;
	double	dy;

	getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
	if((_boundingBox.x1() + dx)>_boundingBox.x2() || (_boundingBox.y1() + dy>_boundingBox.y2())) return;
	box=TeBox(_boundingBox.x1() + dx , _boundingBox.y1() + dy, _boundingBox.x2(), _boundingBox.y2());
	drawXorBox(box,_boundingBox.center(),_angle->getValue());
}

///////////////////////////////////////////////////////////////////////////////
//update corner left top bounding box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::updateLeftTopBoundingBox(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox						box;
	std::vector<TeCoord2D>		coordsBox;
	std::vector<TeCoord2D>		coordsBoundingBox;
	TeLine2D					lneBox,lneBoundingBox;
	unsigned int				i;
	double						dx,dy;

	if(!_lockResize)
	{
		getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
		if((_boundingBox.x1() + dx)>_boundingBox.x2() || (_boundingBox.y1() + dy>_boundingBox.y2())) return;
		box=TeBox(_boundingBox.x1() + dx , _boundingBox.y1() + dy, _boundingBox.x2(), _boundingBox.y2());
		if(_angle==0)
		{
			_boundingBox=box;	
		}
		else
		{
			coordsBox=this->boxToCoords(box);
			coordsBoundingBox=this->boxToCoords(_boundingBox);
			for(i=0;i<coordsBox.size();i++)
			{
				lneBox.add(coordsBox[i]);
				lneBoundingBox.add(coordsBoundingBox[i]);
			}
			TdkRotate(lneBox,lneBox.box().center(),_angle->getValue());
			TdkRotate(lneBoundingBox,lneBoundingBox.box().center(),_angle->getValue());

			dx=lneBox[4].x() - lneBoundingBox[4].x();
			dy=lneBox[4].y() - lneBoundingBox[4].y();
			lneBox=TdkTranslate(lneBox,dx,dy);
			TdkRotate(lneBox,lneBox.box().center(),-_angle->getValue());
			_boundingBox=lneBox.box();
		}
		_necessaryRedraw=true;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw Left Bottom Box Resize Process
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::drawLeftBottomBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox	box;
	double	dx;
	double	dy;

	getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
	if((_boundingBox.x1() + dx)>_boundingBox.x2() || (_boundingBox.y2() + dy<_boundingBox.y1())) return;
	box=TeBox(_boundingBox.x1() + dx , _boundingBox.y1(),  _boundingBox.x2() , _boundingBox.y2() + dy);
	drawXorBox(box,_boundingBox.center(),_angle->getValue());
}

///////////////////////////////////////////////////////////////////////////////
//Update left bottom bounding box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::updateLeftBottomBoundingBox(const TeCoord2D &init, const TeCoord2D &end)
{	
	TeBox						box;
	std::vector<TeCoord2D>		coordsBox;
	std::vector<TeCoord2D>		coordsBoundingBox;
	TeLine2D					lneBox,lneBoundingBox;
	unsigned int				i;
	double						dx,dy;
	
	if(!_lockResize)
	{
		getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
		if((_boundingBox.x1() + dx)>_boundingBox.x2() || (_boundingBox.y2() + dy<_boundingBox.y1())) return;
		box=TeBox(_boundingBox.x1() + dx , _boundingBox.y1(),  _boundingBox.x2() , _boundingBox.y2() + dy);
		if(_angle==0)
		{
			_boundingBox=box;	
		}
		else
		{
			coordsBox=this->boxToCoords(box);
			coordsBoundingBox=this->boxToCoords(_boundingBox);
			for(i=0;i<coordsBox.size();i++)
			{
				lneBox.add(coordsBox[i]);
				lneBoundingBox.add(coordsBoundingBox[i]);
			}
			TdkRotate(lneBox,lneBox.box().center(),_angle->getValue());
			TdkRotate(lneBoundingBox,lneBoundingBox.box().center(),_angle->getValue());

			dx=lneBox[2].x() - lneBoundingBox[2].x();
			dy=lneBox[2].y() - lneBoundingBox[2].y();
			lneBox=TdkTranslate(lneBox,dx,dy);
			TdkRotate(lneBox,lneBox.box().center(),-_angle->getValue());
			_boundingBox=lneBox.box();
		}
		_necessaryRedraw=true;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Update left bounding box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::updateLeftBoundingBox(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox						box;
	std::vector<TeCoord2D>		coordsBox;
	std::vector<TeCoord2D>		coordsBoundingBox;
	TeLine2D					lneBox,lneBoundingBox;
	unsigned int				i;
	double						dx,dy;
	
	if(!_lockResize)
	{
		getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
		if((_boundingBox.x1() + dx)>_boundingBox.x2()) return;
		box=TeBox(_boundingBox.x1()  + dx, _boundingBox.y1() , _boundingBox.x2() , _boundingBox.y2());
		if(_angle==0)
		{
			_boundingBox=box;	
		}
		else
		{
			coordsBox=this->boxToCoords(box);
			coordsBoundingBox=this->boxToCoords(_boundingBox);
			for(i=0;i<coordsBox.size();i++)
			{
				lneBox.add(coordsBox[i]);
				lneBoundingBox.add(coordsBoundingBox[i]);
			}
			TdkRotate(lneBox,lneBox.box().center(),_angle->getValue());
			TdkRotate(lneBoundingBox,lneBoundingBox.box().center(),_angle->getValue());

			dx=lneBox[2].x() - lneBoundingBox[2].x();
			dy=lneBox[2].y() - lneBoundingBox[2].y();
			lneBox=TdkTranslate(lneBox,dx,dy);
			TdkRotate(lneBox,lneBox.box().center(),-_angle->getValue());
			_boundingBox=lneBox.box();
		}
		_necessaryRedraw=true;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw Right Top Box Resize Process
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::drawRightTopBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox	box;
	double	dx;
	double	dy;

	getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
	if((_boundingBox.x2() + dx)<_boundingBox.x1() || (_boundingBox.y1() + dy>_boundingBox.y2())) return;
	box=TeBox(_boundingBox.x1(), _boundingBox.y1() + dy,  _boundingBox.x2() + dx, _boundingBox.y2());
	drawXorBox(box,_boundingBox.center(),_angle->getValue());
}

///////////////////////////////////////////////////////////////////////////////
//update right top bounding box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::updateRightTopBoundingBox(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox						box;
	std::vector<TeCoord2D>		coordsBox;
	std::vector<TeCoord2D>		coordsBoundingBox;
	TeLine2D					lneBox,lneBoundingBox;
	unsigned int				i;
	double						dx,dy;
	
	if(!_lockResize)
	{
		getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
		if((_boundingBox.x2() + dx)<_boundingBox.x1() || (_boundingBox.y1() + dy>_boundingBox.y2())) return;
		box=TeBox(_boundingBox.x1(), _boundingBox.y1() + dy,  _boundingBox.x2() + dx, _boundingBox.y2());
		if(_angle==0)
		{
			_boundingBox=box;	
		}
		else
		{
			coordsBox=this->boxToCoords(box);
			coordsBoundingBox=this->boxToCoords(_boundingBox);
			for(i=0;i<coordsBox.size();i++)
			{
				lneBox.add(coordsBox[i]);
				lneBoundingBox.add(coordsBoundingBox[i]);
			}
			TdkRotate(lneBox,lneBox.box().center(),_angle->getValue());
			TdkRotate(lneBoundingBox,lneBoundingBox.box().center(),_angle->getValue());

			dx=lneBox[6].x() - lneBoundingBox[6].x();
			dy=lneBox[6].y() - lneBoundingBox[6].y();
			lneBox=TdkTranslate(lneBox,dx,dy);
			TdkRotate(lneBox,lneBox.box().center(),-_angle->getValue());
			_boundingBox=lneBox.box();
		}
		_necessaryRedraw=true;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw Right Bottom Box Resize Process
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::drawRightBottomBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox	box;
	double	dx;
	double	dy;

	getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
	if((_boundingBox.x2() + dx)<_boundingBox.x1() || (_boundingBox.y2() + dy<_boundingBox.y1())) return;
	box=TeBox(_boundingBox.x1(), _boundingBox.y1(),  _boundingBox.x2() + dx, _boundingBox.y2() + dy);
	drawXorBox(box,_boundingBox.center(),_angle->getValue());
}

///////////////////////////////////////////////////////////////////////////////
//Update right bottom bounding box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::updateRightBottomBoundingBox(const TeCoord2D &init, const TeCoord2D &end)
{
	TeBox	box;
	std::vector<TeCoord2D>		coordsBox;
	std::vector<TeCoord2D>		coordsBoundingBox;
	TeLine2D					lneBox,lneBoundingBox;
	unsigned int				i;
	double						dx,dy;
	
	if(!_lockResize)
	{
		getDisplacement(init,end,_boundingBox.center(),_angle->getValue(),dx,dy);
		if((_boundingBox.x2() + dx)<_boundingBox.x1() || (_boundingBox.y2() + dy<_boundingBox.y1())) return;
		box=TeBox(_boundingBox.x1(), _boundingBox.y1(),  _boundingBox.x2() + dx, _boundingBox.y2() + dy);
		if(_angle->getValue()==0)
		{
			_boundingBox=box;	
		}
		else
		{
			coordsBox=this->boxToCoords(box);
			coordsBoundingBox=this->boxToCoords(_boundingBox);
			for(i=0;i<coordsBox.size();i++)
			{
				lneBox.add(coordsBox[i]);
				lneBoundingBox.add(coordsBoundingBox[i]);
			}
			TdkRotate(lneBox,lneBox.box().center(),_angle->getValue());
			TdkRotate(lneBoundingBox,lneBoundingBox.box().center(),_angle->getValue());

			dx=lneBox[0].x() - lneBoundingBox[0].x();
			dy=lneBox[0].y() - lneBoundingBox[0].y();
			lneBox=TdkTranslate(lneBox,dx,dy);
			TdkRotate(lneBox,lneBox.box().center(),-_angle->getValue());
			_boundingBox=lneBox.box();
		}
		_necessaryRedraw=true;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw Xor Box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::drawXorBox(TeBox box, const TeCoord2D &center,const double &angle)
{
	int										bufferId;
	int										paintMode;
	double									w,h;
	std::vector<TeCoord2D>					vecCoord;
	std::vector<TeCoord2D>::iterator		it;
	TeLine2D								lneBoundingBox;

	if(!_canvas)	return;

	bufferId=_canvas->getActiveBuffer();
	_canvas->setActiveBuffer(TdkAbstractCanvasDraw::cbrFront);
	paintMode=_canvas->getPaintMode();
	_canvas->setPaintMode(TdkAbstractCanvasDraw::pmdXOR);
	vecCoord=this->boxToCoords(box);
	for(it=vecCoord.begin();it!=vecCoord.end();it++) lneBoundingBox.add(*it);
	TdkRotate(lneBoundingBox,center,angle);

	_canvas->getDimension(w,h);
	_canvas->setClipArea(29,29,w,h);

	_canvas->drawLineW(lneBoundingBox);
	_canvas->setPaintMode(paintMode);
	_canvas->deactivateClip();
	_canvas->setActiveBuffer(bufferId);
}

void TdkLayoutObject::drawXorLine(const TeLine2D &line, const double &angle)
{

	int										bufferId;
	int										paintMode;
	double									w,h;
	std::vector<TeCoord2D>					vecCoord;
	std::vector<TeCoord2D>::iterator		it;
	TeLine2D								lneToDraw;
	

	if(!_canvas)	return;

	lneToDraw.copyElements(line);
	bufferId=_canvas->getActiveBuffer();
	_canvas->setActiveBuffer(TdkAbstractCanvasDraw::cbrFront);
	paintMode=_canvas->getPaintMode();
	_canvas->setPaintMode(TdkAbstractCanvasDraw::pmdXOR);
	TdkRotate(lneToDraw,lneToDraw.box().center(),angle);

	_canvas->getDimension(w,h);
	_canvas->setClipArea(29,29,w,h);

	_canvas->drawLineW(lneToDraw);
	_canvas->setPaintMode(paintMode);
	_canvas->deactivateClip();
	_canvas->setActiveBuffer(bufferId);



}

///////////////////////////////////////////////////////////////////////////////
//Draw Rotate Process
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::drawRotateProcess(const TeCoord2D &init, const TeCoord2D &end)
{

	int								bufferId;
	int								paintMode;
	vector<TeCoord2D>				coords;
	vector<TeCoord2D>::iterator		it;
	TeLine2D						lneBoundingBox;
	double							angle;
	TeCoord2D						coordRotate;
	TeLine2D						lneControlRotate;

	if(!_canvas)	return;

	bufferId=_canvas->getActiveBuffer();
	_canvas->setActiveBuffer(TdkAbstractCanvasDraw::cbrFront);
	paintMode=_canvas->getPaintMode();
	_canvas->setPaintMode(TdkAbstractCanvasDraw::pmdXOR);

	angle=TdkAngle(end,_boundingBox.center());
	angle-=TdkAngle(init,_boundingBox.center());
	angle+=_angle->getValue();

	coords=boxToCoords(_boundingBox);
	for(it=coords.begin();it!=coords.end();it++) lneBoundingBox.add(*it);
	
	TdkRotate(lneBoundingBox,lneBoundingBox.box().center(),angle);
	_canvas->drawLineW(lneBoundingBox);

	coordRotate=calculateRotateControlPoint(lneBoundingBox[1],lneBoundingBox[2]);

	lneControlRotate.add(lneBoundingBox[1]);
	lneControlRotate.add(coordRotate);
	_canvas->drawLineW(lneControlRotate);

	_canvas->setPaintMode(paintMode);
	_canvas->setActiveBuffer(bufferId);
}

///////////////////////////////////////////////////////////////////////////////
//Set object angle
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::setAngle(const TeCoord2D &init, const TeCoord2D &end)
{
	_angle->setValue(_angle->getValue() + TdkAngle(end,_boundingBox.center()) - TdkAngle(init,_boundingBox.center()));
	if(_angle->getValue()<0)			_angle->setValue(_angle->getValue() + 360);
	else if(_angle->getValue()>=360)	_angle->setValue(_angle->getValue() - 360);
}

///////////////////////////////////////////////////////////////////////////////
//Draw Boundig Box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::draw()
{
	double		llx,lly;
	double		urx,ury;
	double		cx,cy;
	TeLine2D	lneBox;

	if( (_visibleContourBox == false) || (_canvas == NULL)) return;
	_canvas->window2Viewport(_boundingBox.x1(),_boundingBox.y1(),llx,lly);
	_canvas->window2Viewport(_boundingBox.x2(),_boundingBox.y2(),urx,ury);
	_canvas->window2Viewport(_boundingBox.center().x(),_boundingBox.center().y(),cx,cy);
	_canvas->setLineColor(0,0,0);
	_canvas->setLineWidth(2);
	_canvas->setLineType(LineSettings::DashStyleSolid);
	lneBox.add(TeCoord2D(llx,lly));
	lneBox.add(TeCoord2D(urx,lly));
	lneBox.add(TeCoord2D(urx,ury));
	lneBox.add(TeCoord2D(llx,ury));
	lneBox.add(TeCoord2D(llx,lly));
	if(_angle) TdkRotate(lneBox,TeCoord2D(cx,cy),_angle->getValue());
	_canvas->drawLine(lneBox);

}

///////////////////////////////////////////////////////////////////////////////
// Return the properties quantity
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
unsigned int TdkLayoutObject::getPropertiesCount()
{
	return ((unsigned int)_properties.size());
}

///////////////////////////////////////////////////////////////////////////////
// Returns the property name according index
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
std::string TdkLayoutObject::getPropertyName(const unsigned int &index)
{
	if(index>=_properties.size()) throw "Invalid index value";
	return _properties[index]->name();
}


bool TdkLayoutObject::getStopDispatch()
{
	bool status;
	status=_stopDispatch;
	_stopDispatch=false;
	return status;
}

///////////////////////////////////////////////////////////////////////////////
//Convert box to polygon
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::convert2Polygon(const TeBox &box, TePolygon &pol)
{
	TeLine2D	lne;

	lne.add(TeCoord2D(box.x1(),box.y1()));
	lne.add(TeCoord2D(box.x2(),box.y1()));
	lne.add(TeCoord2D(box.x2(),box.y2()));
	lne.add(TeCoord2D(box.x2(),box.y2()));
	lne.add(TeCoord2D(box.x1(),box.y2()));

	pol.add(lne);
}

///////////////////////////////////////////////////////////////////////////////
//set a necessary full update
//Author : Rui Mauricio Gregório 
//Date : 07/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::setNecessaryUpdate()
{
	_necessaryRedraw=true;
}

///////////////////////////////////////////////////////////////////////////////
//associate one property from different object with this object
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::associateObjectProperty(TdkAbstractProperty *propertyObject)
{
	TdkAbstractProperty *temp;

	std::vector<TdkAbstractProperty*>::iterator it=_decoratedPropertyList.begin();
	while(it!=_decoratedPropertyList.end())
	{
		if((*it) == propertyObject) 
		{
			temp=(*it);
			_decoratedPropertyList.erase(it);
			temp->disassociateObject();
			it=_decoratedPropertyList.begin();
		}else it++;
	}
	_decoratedPropertyList.push_back(propertyObject);
}

///////////////////////////////////////////////////////////////////////////////
//Disassociate property from object
//Author : Rui Mauricio Gregório 
//Date : 07/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutObject::disassociateObjectProperty(TdkAbstractProperty *propertyObject)
{
	TdkAbstractProperty *temp;
	std::vector<TdkAbstractProperty*>::iterator it=_decoratedPropertyList.begin();
	while(it!=_decoratedPropertyList.end())
	{
		if( ((*it) == propertyObject) || (propertyObject == NULL))
		{
			temp=(*it);
			_decoratedPropertyList.erase(it);
			temp->disassociateObject();
			it=_decoratedPropertyList.begin();
		}else	it++;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Returns the properties list
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
std::vector<TdkAbstractProperty*> TdkLayoutObject::getProperties()
{
	return _properties;
}

///////////////////////////////////////////////////////////////////////////////
//sets the object name
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::setName(const std::string &name)
{
	_objectName=name;

}

///////////////////////////////////////////////////////////////////////////////
//sets the object id
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutObject::setId(const unsigned int &id)
{
	_id=id;
}