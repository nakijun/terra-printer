#include <TdkLayoutTypes.h>
#include <TdkLayoutObject.h>
#include <TdkBlueColorProperty.h>
#include <TdkGreenColorProperty.h>
#include <TdkRedColorProperty.h>
#include <TdkLineTypeProperty.h>
#include <TdkLineWidthProperty.h>
#include <TdkLayoutLineObject.h>
#include <TdkAngleProperty.h>
#include <TdkGeomTransformationUtils.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkLayoutLineObject::TdkLayoutLineObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box) : \
TdkLayoutObject(id,canvas)
{
	_type=LT_LINE;
	_objectName="Line_" + Te2String(id,0);
	registerExtendProperties();
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkLayoutLineObject::~TdkLayoutLineObject()
{

}

///////////////////////////////////////////////////////////////////////////////
//draw line
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutLineObject::draw()
{
	TeLine2D		lneToDraw;
	if(!_canvas)	return;

	if((_boundingBox.isValid() == false) || (_boundingBox == TeBox(0,0,0,0)) || (_boundingBox.width()==0) || (_boundingBox.height()==0)) 
		_boundingBox=TeBox(_boundingBox.x1() -50,_boundingBox.y1()-50, _boundingBox.x1() + 50, _boundingBox.y1() + 50);
	
	_canvas->setLineType((int)_borderType->getValue());
	_canvas->setLineWidth((int)_width->getValue());
	_canvas->setLineColor((int)_foreRColor->getValue(),(int)_foreGColor->getValue(),(int)_foreBColor->getValue());
	_canvas->setPolygonAlpha(255);

	lneToDraw.add(TeCoord2D(_boundingBox.x1(),_boundingBox.center().y()));
	lneToDraw.add(TeCoord2D(_boundingBox.x2(),_boundingBox.center().y()));
	if(_angle)	TdkRotate(lneToDraw,lneToDraw.box().center(),_angle->getValue());
	_canvas->drawLineW(lneToDraw);
	
}

///////////////////////////////////////////////////////////////////////////////
//Print a line method
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutLineObject::print(TdkAbstractCanvasDraw *canvas)
{
	TeLine2D		lneToDraw;
	if(!canvas)	return;

	canvas->setLineType((int)_borderType->getValue());
	canvas->setLineWidth((int)_width->getValue());
	canvas->setLineColor((int)_foreRColor->getValue(),(int)_foreGColor->getValue(),(int)_foreBColor->getValue());
	canvas->setPolygonAlpha(255);

	lneToDraw.add(TeCoord2D(_boundingBox.x1(),_boundingBox.center().y()));
	lneToDraw.add(TeCoord2D(_boundingBox.x2(),_boundingBox.center().y()));
	if(_angle)	TdkRotate(lneToDraw,lneToDraw.box().center(),_angle->getValue());
	canvas->drawLineW(lneToDraw);
}

///////////////////////////////////////////////////////////////////////////////
//Register properties
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutLineObject::registerExtendProperties()
{
	_width=new TdkLineWidthProperty(1);
	_properties.push_back((TdkAbstractProperty*)_width);

	_borderType=new TdkLineTypeProperty();
	_properties.push_back((TdkAbstractProperty*)_borderType);

	_foreRColor=new TdkRedColorProperty();
	_properties.push_back((TdkAbstractProperty*)_foreRColor);

	_foreGColor=new TdkGreenColorProperty();
	_properties.push_back((TdkAbstractProperty*)_foreGColor);

	_foreBColor=new TdkBlueColorProperty();
	_properties.push_back((TdkAbstractProperty*)_foreBColor);
}