#include <TdkLayoutTypes.h>
#include <TdkLayoutRectangleObject.h>
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

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkLayoutRectangleObject::TdkLayoutRectangleObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box) : \
TdkLayoutObject(id,canvas)
{
	_type=LT_RECTANGLE;
	_objectName="Rectangle_" + Te2String(id,0);
	registerExtendProperties();
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkLayoutRectangleObject::~TdkLayoutRectangleObject()
{

}

///////////////////////////////////////////////////////////////////////////////
//Draw Method
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutRectangleObject::draw()
{
	TePolygon		pol;

	if(!_canvas)	return;

	if((_boundingBox.isValid() == false) || (_boundingBox == TeBox(0,0,0,0)) || (_boundingBox.width()==0) || (_boundingBox.height()==0)) 
		_boundingBox=TeBox(_boundingBox.x1() -50,_boundingBox.y1()-50, _boundingBox.x1() + 50, _boundingBox.y1() + 50);
	_canvas->setPolygonBorderType((int)_borderType->getValue());
	_canvas->setPolygonBorderWidth((int)_width->getValue());
	_canvas->setPolygonType((int)_backgroundType->getValue());
	_canvas->setPolygonBorderColor(_foreRColor->getValue(),_foreGColor->getValue(),_foreBColor->getValue(),255);
	_canvas->setPolygonAlpha(255);
	_canvas->setPolygonColor(TeColor(_backgroundRColor->getValue(),_backgroundGColor->getValue(),_backgroundBColor->getValue()),255);

	convert2Polygon(_boundingBox,pol);
	if(_angle->getValue())	TdkRotate(pol,pol.box().center(),_angle->getValue());
	_canvas->drawPolygonW(pol);
}

///////////////////////////////////////////////////////////////////////////////
//Print Method
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutRectangleObject::print(TdkAbstractCanvasDraw *canvas)
{
	TePolygon		pol;

	if(!canvas)	return;

	if((_boundingBox.isValid() == false) || (_boundingBox == TeBox(0,0,0,0)) || (_boundingBox.width()==0) || (_boundingBox.height()==0)) 
		_boundingBox=TeBox(_boundingBox.x1() -50,_boundingBox.y1()-50, _boundingBox.x1() + 50, _boundingBox.y1() + 50);
	canvas->setPolygonBorderType((int)_borderType->getValue());
	canvas->setPolygonBorderWidth((int)_width->getValue());
	canvas->setPolygonType((int)_backgroundType->getValue());
	canvas->setPolygonBorderColor(_foreRColor->getValue(),_foreGColor->getValue(),_foreBColor->getValue(),255);
	canvas->setPolygonAlpha(255);
	canvas->setPolygonColor(TeColor(_backgroundRColor->getValue(),_backgroundGColor->getValue(),_backgroundBColor->getValue()),255);

	convert2Polygon(_boundingBox,pol);
	if(_angle->getValue())	TdkRotate(pol,pol.box().center(),_angle->getValue());
	canvas->drawPolygonW(pol);

}

///////////////////////////////////////////////////////////////////////////////
//Register properties
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutRectangleObject::registerExtendProperties()
{
		_width=new TdkLineWidthProperty(1);
		_properties.push_back((TdkAbstractProperty*)_width);

		_borderType=new TdkLineTypeProperty();
		_properties.push_back((TdkAbstractProperty*)_borderType);

		_backgroundType=new TdkBackgroundTypeProperty(-2);
		_properties.push_back((TdkAbstractProperty*)_backgroundType);

		_backgroundRColor=new TdkBackgroundRColorProperty(255);
		_properties.push_back((TdkAbstractProperty*)_backgroundRColor);

		_backgroundGColor=new TdkBackgroundGColorProperty(255);
		_properties.push_back((TdkAbstractProperty*)_backgroundGColor);

		_backgroundBColor=new TdkBackgroundBColorProperty(255);
		_properties.push_back((TdkAbstractProperty*)_backgroundBColor);

		_foreRColor=new TdkRedColorProperty();
		_properties.push_back((TdkAbstractProperty*)_foreRColor);

		_foreGColor=new TdkGreenColorProperty();
		_properties.push_back((TdkAbstractProperty*)_foreGColor);

		_foreBColor=new TdkBlueColorProperty();
		_properties.push_back((TdkAbstractProperty*)_foreBColor);
}

