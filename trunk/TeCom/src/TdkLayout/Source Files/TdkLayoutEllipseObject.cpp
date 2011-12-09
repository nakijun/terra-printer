#include <TdkLayoutTypes.h>
#include <TdkAbstractCanvasDraw.h>
#include <TdkCanvasTypes.h>
#include <TdkLineWidthProperty.h>
#include <TdkLineTypeProperty.h>
#include <TdkBackgroundTypeProperty.h>
#include <TdkAngleProperty.h>
#include <TdkBackgroundRColorProperty.h>
#include <TdkBackgroundGColorProperty.h>
#include <TdkBackgroundBColorProperty.h>
#include <TdkRedColorProperty.h>
#include <TdkGreenColorProperty.h>
#include <TdkBlueColorProperty.h>
#include <TdkGeomTransformationUtils.h>
#include <TdkLayoutEllipseObject.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkLayoutEllipseObject::TdkLayoutEllipseObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box) :TdkLayoutRectangleObject(id, canvas,box)
{
	_objectName="Ellipse_" + Te2String(id,0);
	_type=LT_ELLIPSE;

}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkLayoutEllipseObject::~TdkLayoutEllipseObject()
{

}

///////////////////////////////////////////////////////////////////////////////
//Draw
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutEllipseObject::draw()
{
	if(!_canvas)	return;

	if((_boundingBox.isValid() == false) || (_boundingBox == TeBox(0,0,0,0)) || (_boundingBox.width()==0) || (_boundingBox.height()==0)) 
		_boundingBox=TeBox(_boundingBox.x1() -50,_boundingBox.y1()-50, _boundingBox.x1() + 50, _boundingBox.y1() + 50);
	_canvas->setPolygonBorderType((int)_borderType->getValue());
	_canvas->setPolygonBorderWidth((int)_width->getValue());
	_canvas->setPolygonType((int)_backgroundType->getValue());
	_canvas->setPolygonBorderColor(_foreRColor->getValue(),_foreGColor->getValue(),_foreBColor->getValue(),255);
	_canvas->setPolygonAlpha(255);
	_canvas->setPolygonColor(TeColor(_backgroundRColor->getValue(),_backgroundGColor->getValue(),_backgroundBColor->getValue()),255);
	if(_backgroundType->getValue()!=PolygonSettings::Transparent)	
		_canvas->fillEllipseW(_boundingBox.center().x(),_boundingBox.center().y(),\
		_boundingBox.width()/2.0,_boundingBox.height()/2.0,_angle->getValue());
	_canvas->drawEllipseW(_boundingBox.center().x(),_boundingBox.center().y(),_boundingBox.width()/2.0,_boundingBox.height()/2.0,_angle->getValue());
}

///////////////////////////////////////////////////////////////////////////////
//Print
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutEllipseObject::print(TdkAbstractCanvasDraw *canvas)
{
	if(!canvas)	return;

	canvas->setPolygonBorderType((int)_borderType->getValue());
	canvas->setPolygonBorderWidth((int)_width->getValue());
	canvas->setPolygonType((int)_backgroundType->getValue());
	canvas->setPolygonBorderColor(_foreRColor->getValue(),_foreGColor->getValue(),_foreBColor->getValue(),255);
	canvas->setPolygonAlpha(255);
	canvas->setPolygonColor(TeColor(_backgroundRColor->getValue(),_backgroundGColor->getValue(),_backgroundBColor->getValue()),255);
	if(_backgroundType->getValue()!=PolygonSettings::Transparent)	
		canvas->fillEllipseW(_boundingBox.center().x(),_boundingBox.center().y(),\
		_boundingBox.width()/2.0,_boundingBox.height()/2.0,_angle->getValue());
	canvas->drawEllipseW(_boundingBox.center().x(),_boundingBox.center().y(),_boundingBox.width()/2.0,_boundingBox.height()/2.0,_angle->getValue());
}