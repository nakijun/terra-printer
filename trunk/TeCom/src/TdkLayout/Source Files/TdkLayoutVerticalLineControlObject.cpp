#include <TdkLayoutTypes.h>
#include <TdkLayoutObject.h>
#include <TdkLayoutVerticalLineControlObject.h>
#include <TdkMouseEvent.h>
#include <TdkAbstractCursor.h>
#include <tegeometryalgorithms.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutVerticalLineControlObject::TdkLayoutVerticalLineControlObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box) : \
TdkLayoutObject(id,canvas)
{
	_type=LT_VLINE_CONTROL;
	_objectName="VLineControl_" + Te2String(id,0);
	_editable=false;
	_cursor=0;
}


///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutVerticalLineControlObject::~TdkLayoutVerticalLineControlObject()
{

}

///////////////////////////////////////////////////////////////////////////////
//Draw Vertical Line
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutVerticalLineControlObject::draw()
{
	TeLine2D		lneToDraw;
	TeBox			box;

	if(!_canvas)	return;


	_canvas->getWindow(box);

	if((_boundingBox.isValid() == false) || (_boundingBox == TeBox(0,0,0,0)) || (_boundingBox.width()==0) || (_boundingBox.height()==0))	_boundingBox=TeBox(box.center().x() -1,box.y1(), box.center().x() + 1, box.y2());
	else			_boundingBox=TeBox(_boundingBox.center().x() - 1, box.y1(), _boundingBox.center().x() + 1, box.y2());
	
	_canvas->setLineType(1);
	_canvas->setLineWidth(1);
	_canvas->setLineColor(100,100,100);

	lneToDraw.add(TeCoord2D(_boundingBox.center().x(),_boundingBox.y1()));
	lneToDraw.add(TeCoord2D(_boundingBox.center().x(),_boundingBox.y2()));
	_canvas->drawLineW(lneToDraw);

}

///////////////////////////////////////////////////////////////////////////////
//Print
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutVerticalLineControlObject::print(TdkAbstractCanvasDraw *canvas)
{
	//This object is just control - not printable

}

///////////////////////////////////////////////////////////////////////////////
//registerExtendProperties
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutVerticalLineControlObject::registerExtendProperties()
{
 //there are not extend properties
}

///////////////////////////////////////////////////////////////////////////////
//Draw Translate Process
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutVerticalLineControlObject::drawTranslateProcess(const double &dx, const double &dy)
{
	TeLine2D	lneVertical;
	lneVertical.add(TeCoord2D(_boundingBox.center().x() + dx,_boundingBox.y1()));
	lneVertical.add(TeCoord2D(_boundingBox.center().x() + dx,_boundingBox.y2()));
	this->drawXorLine(lneVertical,0);
}

///////////////////////////////////////////////////////////////////////////////
//drawSelection
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutVerticalLineControlObject::drawSelection(const TdkAbstractCanvasDraw::TdkCanvasBuffer &buffer)
{
	//not draw the selection box
}

///////////////////////////////////////////////////////////////////////////////
//Mouse Move
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutVerticalLineControlObject::mouseMove(TdkMouseEvent *e)
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
void TdkLayoutVerticalLineControlObject::setCursor(TdkAbstractCursor *cursor)
{
	_cursor=cursor;
}