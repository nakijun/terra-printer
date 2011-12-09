#include <TdkLayoutTypes.h>
#include <TdkLayoutTextObject.h>
#include <TdkAbstractCanvasDraw.h>
#include <TdkGdiCanvasDraw.h>
#include <TdkGeomTransformationUtils.h>
#include <TdkAngleProperty.h>
#include <TdkTextValueProperty.h>
#include <TdkTextSizeProperty.h>
#include <TdkTextFontNameProperty.h>
#include <TdkTextBoldProperty.h>
#include <TdkTextItalicProperty.h>
#include <TdkTextForeColorRProperty.h>
#include <TdkTextForeColorGProperty.h>
#include <TdkTextForeColorBProperty.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor with Object Id, Canvas Pointer and Box to creation
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

TdkLayoutTextObject::TdkLayoutTextObject(const unsigned int &id,TdkAbstractCanvasDraw* canvas,const TeBox &box, \
										 const std::string textValue):TdkLayoutObject(id,canvas)
{
	_type=LT_TEXT;
	registerExtendProperties();
	if(textValue.empty())	_text->setValue("Label" + Te2String(id));
	else					_text->setValue(textValue);
	_objectName="Text_" + Te2String(id,0);
	_size->setValue(2.5);//mm
	_fontName->setValue("Verdana");
	_autoSize=true;
	_lockResize=true;
	_horizontalAlign=hLeft;
	_verticalAlign=vTop;
	_visibleContourBox=false;
	if((box.width()==0) || (box.height()==0))	
	{
		_boundingBox=TeBox(box.x1() + (id*2),box.y1() + (id*2),20,10);
	}
	else										
	{
		_boundingBox=box;
	}
	_objectName="Text_" + Te2String(id,0);
	
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

TdkLayoutTextObject::~TdkLayoutTextObject()
{

}

///////////////////////////////////////////////////////////////////////////////
//Draw Method
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutTextObject::draw()
{
	int				activeBuffer;
	double			x,y;
	double			txtVwYInit, txtVwYEnd;
	double			txtVw;
	TeCoord2D		coordRotated;
	
	if(!_canvas)	return;
	
	_canvas->window2Viewport(0,0,txtVw,txtVwYInit);
	_canvas->window2Viewport(_size->getValue(),_size->getValue(),txtVw,txtVwYEnd);

	activeBuffer=_canvas->getActiveBuffer();
	_canvas->setActiveBuffer(TdkAbstractCanvasDraw::cbrCache);

	double scale=_canvas->getScale(NULL);
	
	_canvas->setTextBold(_bold->getValue());
	_canvas->setTextItalic(_italic->getValue());
	_canvas->setTextPixelSize((int)fabs( txtVwYEnd - txtVwYInit));//  (int)(_size->getValue() / scale));
	_canvas->setTextFont(_fontName->getValue());
	_canvas->setTextColor(TeColor(_foreRColor->getValue(),_foreGColor->getValue(),_foreBColor->getValue()),255);
	_canvas->setTextAlign(0,2);
	_canvas->setTextAngle(-_angle->getValue());

	if(_autoSize) calculateBox(_canvas);

	this->setClipClientAreaW(_boundingBox);
	this->subtractRulerArea();

	calculateCoordinate(x,y,_canvas);
	TdkRotate(_boundingBox.center(),TeCoord2D(x,y),_angle->getValue(),coordRotated);
	_canvas->drawTextW(coordRotated.x(),coordRotated.y(),_text->getValue());
	TdkLayoutObject::draw();
	_canvas->deactivateClip();
	_canvas->setActiveBuffer(activeBuffer);
}


///////////////////////////////////////////////////////////////////////////////
//Method to calculate the bounding box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutTextObject::calculateBox(TdkAbstractCanvasDraw *canvas)
{
	double	w,h;
	double	wx,wy;
	double	x,y;

	if(!canvas)	return;
	canvas->getTextDimension(_text->getValue(),w,h);
	canvas->window2Viewport(_boundingBox.x1(),_boundingBox.y1(),x,y);
	canvas->viewport2Window((x+w),(y+h),wx,wy);
	_boundingBox=TeBox(_boundingBox.x1(),_boundingBox.y1(),wx,wy);
}

///////////////////////////////////////////////////////////////////////////////
//Method to calculate the text position according alignment
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////

bool TdkLayoutTextObject::calculateCoordinate(double &x, double &y,TdkAbstractCanvasDraw *canvas)
{
	double		w,h;
	double		wx,wy;

	if(!canvas)	
	{
		x=0;
		y=0;
		return false;
	}

	canvas->getTextDimension(_text->getValue(),w,h);
	canvas->window2Viewport(_boundingBox.x1(),_boundingBox.y1(),x,y);
	canvas->viewport2Window((x+w),(y+h),wx,wy);
	wy=fabs(wy-_boundingBox.y1());
	wx=fabs(wx-_boundingBox.x1());

	switch(_horizontalAlign)
	{
		case hLeft:
					x=_boundingBox.x1();
					break;
		case hCenter:
					x=_boundingBox.center().x() - wx/2.0;
					break;
		case hRight:
					x=_boundingBox.x2() - wx;
					break;
	}
	
	switch(_verticalAlign)
	{
		case vTop:			
					y=_boundingBox.y1();
					break;
		case vCenter:		
					y=_boundingBox.center().y() - wy/2.0;
					break;
		case vBottom:		
					y=_boundingBox.y2() - wy;
					break;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Set Auto Size bounding box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutTextObject::setAutoSize(const bool &status)
{
	
	_autoSize=status;
	_lockResize=status;
	if(status==true)
	{
		_horizontalAlign=hLeft;
		_verticalAlign=vTop;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set ratio text font size
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutTextObject::setRatio(const double &ratioSize)
{
	double ratio;

	if(_size != 0) 
	{
		ratio=_size->getValue();
		ratio*=ratioSize;
		if(ratio>0) _size->setValue(ratio);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Print Method
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutTextObject::print(TdkAbstractCanvasDraw *canvas)
{
	double			x,y;
	TeCoord2D		coordRotated;
	TeBox			currentBox;
	double			txtVw;
	double			txtVwYInit,txtVwYEnd;


	if(!canvas)	return;

	canvas->window2Viewport(0,0,txtVw,txtVwYInit);
	canvas->window2Viewport(_size->getValue(),_size->getValue(),txtVw,txtVwYEnd);


	canvas->setTextBold(_bold->getValue());
	canvas->setTextItalic(_italic->getValue());
	canvas->setTextPixelSize((int)fabs( txtVwYEnd - txtVwYInit));   ///(int)_size->getValue());
	canvas->setTextFont(_fontName->getValue());
	canvas->setTextColor(TeColor(_foreRColor->getValue(),_foreGColor->getValue(),_foreBColor->getValue()),255);
	canvas->setTextAlign(0,2);
	canvas->setTextAngle(-_angle->getValue());
	calculateCoordinate(x,y,canvas);
	
	x=_boundingBox.x1();
	y=_boundingBox.y1();
	TdkRotate(_boundingBox.center(),TeCoord2D(x,y),_angle->getValue(),coordRotated);
	canvas->drawTextW(coordRotated.x(),coordRotated.y(),_text->getValue());
}

///////////////////////////////////////////////////////////////////////////////
//Set Bounding Box
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutTextObject::setBoundingBox(const TeBox &box)
{
	_boundingBox=box;
}


///////////////////////////////////////////////////////////////////////////////
//Register Properties Method
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutTextObject::registerExtendProperties()
{
	_text=new TdkTextValueProperty();
	_properties.push_back((TdkAbstractProperty*)_text);

	_size=new TdkTextSizeProperty();
	_properties.push_back((TdkAbstractProperty*)_size);

	_fontName= new TdkTextFontNameProperty();
	_properties.push_back((TdkAbstractProperty*)_fontName);

	_bold = new TdkTextBoldProperty();
	_properties.push_back((TdkAbstractProperty*)_bold);

	_italic = new TdkTextItalicProperty();
	_properties.push_back((TdkAbstractProperty*)_italic);

	_foreRColor = new TdkTextForeColorRProperty();
	_properties.push_back((TdkAbstractProperty*)_foreRColor);

	_foreGColor = new TdkTextForeColorGProperty();
	_properties.push_back((TdkAbstractProperty*)_foreGColor);

	_foreBColor = new TdkTextForeColorBProperty();
	_properties.push_back((TdkAbstractProperty*)_foreBColor);



}