#include <TdkLayoutTypes.h>
#include <TdkLayoutObject.h>
#include <TdkLayoutScaleObject.h>
#include <TdkCanvasTypes.h>
#include <TdkAngleProperty.h>
#include <TdkMapScaleProperty.h>
#include <TdkScaleUnitProperty.h>
#include <TdkTextForeColorRProperty.h>
#include <TdkTextForeColorGProperty.h>
#include <TdkTextForeColorBProperty.h>
#include <TdkRedColorProperty.h>
#include <TdkGreenColorProperty.h>
#include <TdkBlueColorProperty.h>
#include <TdkGeomTransformationUtils.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkLayoutScaleObject::TdkLayoutScaleObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box) :
TdkLayoutObject(id,canvas)
{
	_type=LT_SCALE;
	_objectName="Scale_" + Te2String(id,0);
	registerExtendProperties();
	_size=10;
	_unit=1;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkLayoutScaleObject::~TdkLayoutScaleObject()
{

}

///////////////////////////////////////////////////////////////////////////////
//Draw
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutScaleObject::draw()
{
	TePolygon pol;
	TePolygon polV;
	

	drawScaleRectangles(_canvas);
	
	this->convert2Polygon(_boundingBox,pol);
	TdkRotate(pol,_boundingBox.center(),_angle->getValue());
	_canvas->window2Viewport(pol,polV);
	_canvas->setClipArea(polV);
	subtractRulerArea();
	drawScaleTitle(_canvas);
	drawScaleText(_canvas);
	_canvas->deactivateClip();
}

///////////////////////////////////////////////////////////////////////////////
//Draw Scale's Rectangle
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutScaleObject::drawScaleRectangles(TdkAbstractCanvasDraw* canvas)
{
	TeLine2D	lneRectangle;
	double		position;
	bool		bAlternate=false;
	

	if(canvas==NULL)	return;

	canvas->setLineColor(_redColor->getValue(),_greenColor->getValue(),_blueColor->getValue(),255);
	canvas->setLineType(0);
	canvas->setLineWidth(1);

	canvas->setPolygonBorderColor(_redColor->getValue(),_greenColor->getValue(),_blueColor->getValue()	);
	canvas->setPolygonBorderType(LineSettings::DashStyleSolid);
	canvas->setPolygonColor(_redColor->getValue(),_greenColor->getValue(),_blueColor->getValue(),255);
	canvas->setPolygonType(PolygonSettings::Solid);
	
	for(position=_boundingBox.x1();position<_boundingBox.x2();position+=_size)
	{
		TePolygon pol;
		lneRectangle.clear();
		lneRectangle.add(TeCoord2D(position,_boundingBox.center().y() - _widthScale)); 
		lneRectangle.add(TeCoord2D(position + _size,_boundingBox.center().y() - _widthScale )); 
		lneRectangle.add(TeCoord2D(position + _size,_boundingBox.center().y())); 
		lneRectangle.add(TeCoord2D(position,_boundingBox.center().y())); 
		lneRectangle.add(TeCoord2D(position,_boundingBox.center().y() - _widthScale)); 
		if(_angle->getValue())	TdkRotate(lneRectangle,_boundingBox.center(),_angle->getValue());
		pol.add(lneRectangle);
		if(bAlternate)			canvas->drawPolygonW(pol);	
		else					canvas->drawLineW(lneRectangle);
		bAlternate=!bAlternate;
	}

	bAlternate=true;
	for(position=_boundingBox.x1();position<_boundingBox.x2();position+=_size)
	{
		TePolygon pol;
		lneRectangle.clear();
		lneRectangle.add(TeCoord2D(position,_boundingBox.center().y() + _widthScale)); 
		lneRectangle.add(TeCoord2D(position + _size,_boundingBox.center().y() + _widthScale )); 
		lneRectangle.add(TeCoord2D(position + _size,_boundingBox.center().y())); 
		lneRectangle.add(TeCoord2D(position,_boundingBox.center().y())); 
		lneRectangle.add(TeCoord2D(position,_boundingBox.center().y() + _widthScale)); 
		if(_angle->getValue())	TdkRotate(lneRectangle,_boundingBox.center(),_angle->getValue());
		pol.add(lneRectangle);
		if(bAlternate)			canvas->drawPolygonW(pol);	
		else					canvas->drawLineW(lneRectangle);
		bAlternate=!bAlternate;
	}
	_boundingBox=TeBox(_boundingBox.x1(),_boundingBox.y1(),position,_boundingBox.y2());
}

///////////////////////////////////////////////////////////////////////////////
//Draw Title
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutScaleObject::drawScaleTitle(TdkAbstractCanvasDraw* canvas)
{
	std::string	text;
	double		scale;
	TeCoord2D	coordOut;

	if(canvas==NULL) return;
	canvas->setTextFont("Verdana");
	canvas->setTextBold(false);
	canvas->setTextItalic(false);
	canvas->setTextAngle(-_angle->getValue());
	canvas->setTextColor(0,0,0,255);
	scale=canvas->getScale(0);
	canvas->setTextSize((int)(5 / scale));
	canvas->setTextAlign(1,1);
	canvas->setTextColor(_redTextColor->getValue(),_greenTextColor->getValue(),_blueTextColor->getValue());

	if(_unitType)
	{
		if(_unitType->getValue() == TdkScaleUnitProperty::meters)		text="(m)";
		else															text="(Km)";
	}
	TdkRotate(_boundingBox.center(),TeCoord2D(_boundingBox.center().x(),_boundingBox.center().y() + 6),_angle->getValue(),coordOut);
	canvas->drawTextW(coordOut.x(),coordOut.y(),text);
	
	canvas->setTextSize((int)(12 / scale));
	text="Escala (1/" + Te2String(_scale->getValue(),0) + ")";
	TdkRotate(_boundingBox.center(),TeCoord2D(_boundingBox.center().x(),_boundingBox.center().y() + 13),_angle->getValue(),coordOut);
	canvas->drawTextW(coordOut.x(),coordOut.y(),text);
}

///////////////////////////////////////////////////////////////////////////////
//Draw Scales Values
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutScaleObject::drawScaleText(TdkAbstractCanvasDraw* canvas)
{
	double			position;
	double			value;
	double			scale=0;
	double			canvasScale;
	std::string		strValue;
	TeCoord2D		coordOut;

	if(canvas==NULL) return;

	if(_unitType)
	{
		if(_unitType->getValue() == TdkScaleUnitProperty::meters)		_unit=1.0;
		else															_unit=1000.0;
	}

	canvas->setTextFont("Verdana");
	canvas->setTextBold(false);
	canvas->setTextItalic(false);
	canvasScale=canvas->getScale(0);
	canvas->setTextAngle(-_angle->getValue());
	canvas->setTextColor(0,0,0,255);
	canvas->setTextSize((int)(8 / canvasScale));
	canvas->setTextAlign(0,1);
	canvas->setTextColor(_redTextColor->getValue(),_greenTextColor->getValue(),_blueTextColor->getValue());

	for(position=_boundingBox.x1();position<_boundingBox.x2();position+=_size,scale+=_size)
	{
		value = ((scale/1000.) * _scale->getValue()) / _unit;
		strValue=Te2String(value,0);
		TdkRotate(_boundingBox.center(),TeCoord2D(position,_boundingBox.center().y() - 6),_angle->getValue(),coordOut);
		canvas->drawTextW(coordOut.x(),coordOut.y(),strValue);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Print
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutScaleObject::print(TdkAbstractCanvasDraw *canvas)
{
	TePolygon pol;
	TePolygon polV;
	this->convert2Polygon(_boundingBox,pol);

	drawScaleRectangles(canvas);
	
	TdkRotate(pol,_boundingBox.center(),_angle->getValue());
	canvas->window2Viewport(pol,polV);
	canvas->setClipArea(polV);
	subtractRulerArea();
	drawScaleTitle(canvas);
	drawScaleText(canvas);
	canvas->deactivateClip();
}

///////////////////////////////////////////////////////////////////////////////
//Register Extend Properties
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutScaleObject::registerExtendProperties()
{
	_scale=new TdkMapScaleProperty(10000);
	_properties.push_back((TdkAbstractProperty*)_scale);

	_unitType=new TdkScaleUnitProperty();
	_properties.push_back((TdkAbstractProperty*)_unitType);

	_redTextColor=new TdkTextForeColorRProperty(0);
	_properties.push_back((TdkAbstractProperty*)_redTextColor);

	_greenTextColor=new TdkTextForeColorGProperty(0);
	_properties.push_back((TdkAbstractProperty*)_greenTextColor);

	_blueTextColor=new TdkTextForeColorBProperty(0);
	_properties.push_back((TdkAbstractProperty*)_blueTextColor);


	_redColor=new TdkRedColorProperty(0);
	_properties.push_back((TdkAbstractProperty*)_redColor);

	_greenColor=new TdkGreenColorProperty(0);
	_properties.push_back((TdkAbstractProperty*)_greenColor);

	_blueColor=new TdkBlueColorProperty(0);
	_properties.push_back((TdkAbstractProperty*)_blueColor);

}

