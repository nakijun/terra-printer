#include <TdkLayoutTypes.h>
#include <TdkLayoutObject.h>
#include <TdkLayoutHorizontalLineControlObject.h>
#include <TdkMouseEvent.h>
#include <TdkAbstractCursor.h>
#include <tegeometryalgorithms.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutHorizontalLineControlObject::TdkLayoutHorizontalLineControlObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box) : \
TdkLayoutObject(id,canvas)
{
	_type=LT_HLINE_CONTROL;
	_objectName="HLineControl_" + Te2String(id,0);
	_editable=false;
	_cursor=0;
}


///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutHorizontalLineControlObject::~TdkLayoutHorizontalLineControlObject()
{

}

///////////////////////////////////////////////////////////////////////////////
//Draw Vertical Line
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutHorizontalLineControlObject::draw()
{
	TeLine2D		lneToDraw;
	TeBox			box;

	if(!_canvas)	return;


	_canvas->getWindow(box);

	if((_boundingBox.isValid() == false) || (_boundingBox == TeBox(0,0,0,0)) || (_boundingBox.width()==0) || (_boundingBox.height()==0))	_boundingBox=TeBox(box.x1(),box.center().y() - 1, box.x2(), box.center().y() + 1);
	else			_boundingBox=TeBox(box.x1(), _boundingBox.center().y() - 1, box.x2(), _boundingBox.center().y() + 1);
	
	_canvas->setLineType(1);
	_canvas->setLineWidth(1);
	_canvas->setLineColor(100,100,100);

	lneToDraw.add(TeCoord2D(_boundingBox.x1(),_boundingBox.center().y()));
	lneToDraw.add(TeCoord2D(_boundingBox.x2(),_boundingBox.center().y()));
	_canvas->drawLineW(lneToDraw);

}

///////////////////////////////////////////////////////////////////////////////
//Print
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutHorizontalLineControlObject::print(TdkAbstractCanvasDraw *canvas)
{
	//This object is just control - not printable

}

///////////////////////////////////////////////////////////////////////////////
//registerExtendProperties
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutHorizontalLineControlObject::registerExtendProperties()
{
 //there are not extend properties
}

///////////////////////////////////////////////////////////////////////////////
//Draw Translate Process
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutHorizontalLineControlObject::drawTranslateProcess(const double &dx, const double &dy)
{
	TeLine2D	lneHorizontal;
	lneHorizontal.add(TeCoord2D(_boundingBox.x1(),_boundingBox.center().y() + dy));
	lneHorizontal.add(TeCoord2D(_boundingBox.x2(),_boundingBox.center().y() + dy));
	this->drawXorLine(lneHorizontal,0);
}

///////////////////////////////////////////////////////////////////////////////
//drawSelection
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutHorizontalLineControlObject::drawSelection(const TdkAbstractCanvasDraw::TdkCanvasBuffer &buffer)
{
	//not draw selection box
}

///////////////////////////////////////////////////////////////////////////////
//Mouse Move
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutHorizontalLineControlObject::mouseMove(TdkMouseEvent *e)
{
	if( (TeWithin(TeCoord2D(e->X,e->Y),_boundingBox) == true) && (e->Button == TdkMouseEvent::None) )
	{
		if(_cursor !=0) _cursor->setCursor(CursorAll);
	}
}

///////////////////////////////////////////////////////////////////////////////
//set Cursor
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutHorizontalLineControlObject::setCursor(TdkAbstractCursor *cursor)
{
	_cursor=cursor;
}