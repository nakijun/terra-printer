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
#include <TdkLayoutMTextObject.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutMTextObject::TdkLayoutMTextObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas, const TeBox &box,const std::string textValue) :
TdkLayoutTextObject(id,canvas,box,textValue)
{
	_type=LT_MTEXT;
	registerExtendProperties();
	_objectName="MText_" + Te2String(id,0);
	_autoSize=false;
	_lockResize=false;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutMTextObject::~TdkLayoutMTextObject()
{

}

///////////////////////////////////////////////////////////////////////////////
//Split text in multi lines
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
vector<std::string>	TdkLayoutMTextObject::splitTextInTextLines(const std::string &value)
{
	std::vector<std::string>		linesText;
	std::string						lineText;
	unsigned int					i;

	for(i=0;i<value.size();i++)
	{
		if(value[i] == '\n')
		{
			linesText.push_back(lineText);
			lineText.clear();
		}else
		{
			lineText+=value[i];
		}
	}
	if(lineText.empty() == false)	linesText.push_back(lineText);
	return linesText;
}

///////////////////////////////////////////////////////////////////////////////
//get Text Height
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
double TdkLayoutMTextObject::getTextHeight(TdkAbstractCanvasDraw *canvas, const std::string &text)
{
	double	w,h;
	double	wx,wy;
	double	x,y;

	if(!canvas)	return 10;
	canvas->getTextDimension(text,w,h);
	canvas->viewport2Window(0,0,x,y);
	canvas->viewport2Window(w,h,wx,wy);
	h=fabs(y-wy);
	return h;
}

///////////////////////////////////////////////////////////////////////////////
//draw
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutMTextObject::draw()
{
	int									activeBuffer;
	double								x,y;
	double								txtVwYInit, txtVwYEnd;
	double								txtVw;
	TeCoord2D							coordRotated;
	vector<std::string>					texts;
	vector<std::string>::iterator		it;
	TeBox								box;
	
	if(!_canvas)	return;
	
	_canvas->window2Viewport(0,0,txtVw,txtVwYInit);
	_canvas->window2Viewport(_size->getValue(),_size->getValue(),txtVw,txtVwYEnd);

	activeBuffer=_canvas->getActiveBuffer();
	_canvas->setActiveBuffer(TdkAbstractCanvasDraw::cbrCache);

	double scale=_canvas->getScale(NULL);
	
	_canvas->setTextBold(_bold->getValue());
	_canvas->setTextItalic(_italic->getValue());
	_canvas->setTextPixelSize((int)fabs( txtVwYEnd - txtVwYInit));
	_canvas->setTextFont(_fontName->getValue());
	_canvas->setTextColor(TeColor(_foreRColor->getValue(),_foreGColor->getValue(),_foreBColor->getValue()),255);
	_canvas->setTextAlign(0,2);
	_canvas->setTextAngle(-_angle->getValue());

	this->setClipClientAreaW(_boundingBox);
	this->subtractRulerArea();

	calculateCoordinate(x,y,_canvas);
	texts=this->splitTextInTextLines(_text->getValue());
	for(it=texts.begin();it!=texts.end(); it++)
	{
		calculateHrzAlignment(x,_canvas,(*it));
		TdkRotate(_boundingBox.center(),TeCoord2D(x,y),_angle->getValue(),coordRotated);
		_canvas->drawTextW(coordRotated.x(),coordRotated.y(),(*it));
		y+=getTextHeight(_canvas,(*it));
	}
	TdkLayoutObject::draw();
	_canvas->deactivateClip();
	_canvas->setActiveBuffer(activeBuffer);

}

///////////////////////////////////////////////////////////////////////////////
//Print
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutMTextObject::print(TdkAbstractCanvasDraw *canvas)
{
	double								x,y;
	double								txtVwYInit, txtVwYEnd;
	double								txtVw;
	TeCoord2D							coordRotated;
	vector<std::string>					texts;
	vector<std::string>::iterator		it;
	TeBox								box;
	
	if(!canvas)	return;
	
	canvas->window2Viewport(0,0,txtVw,txtVwYInit);
	canvas->window2Viewport(_size->getValue(),_size->getValue(),txtVw,txtVwYEnd);
	
	canvas->setTextBold(_bold->getValue());
	canvas->setTextItalic(_italic->getValue());
	canvas->setTextPixelSize((int)fabs( txtVwYEnd - txtVwYInit));
	canvas->setTextFont(_fontName->getValue());
	canvas->setTextColor(TeColor(_foreRColor->getValue(),_foreGColor->getValue(),_foreBColor->getValue()),255);
	canvas->setTextAlign(0,2);
	canvas->setTextAngle(-_angle->getValue());

	this->setClipClientAreaW(_boundingBox,canvas);
	calculateCoordinate(x,y,canvas);
	texts=this->splitTextInTextLines(_text->getValue());
	for(it=texts.begin();it!=texts.end(); it++)
	{
		calculateHrzAlignment(x,canvas,(*it));
		TdkRotate(_boundingBox.center(),TeCoord2D(x,y),_angle->getValue(),coordRotated);
		canvas->drawTextW(coordRotated.x(),coordRotated.y(),(*it));
		y+=getTextHeight(canvas,(*it));
	}
	canvas->deactivateClip();
}


void TdkLayoutMTextObject::registerExtendProperties()
{
	
}

///////////////////////////////////////////////////////////////////////////////
//calculateHrzAlignment
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutMTextObject::calculateHrzAlignment(double &x,TdkAbstractCanvasDraw *canvas,const std::string &text)
{
	double		w,h;
	double		wx,wy;
	double		y;

	if(!canvas)	
		return false;

	canvas->getTextDimension(text,w,h);
	canvas->window2Viewport(_boundingBox.x1(),_boundingBox.y1(),x,y);
	canvas->viewport2Window((x+w),(y+h),wx,wy);

	wy=fabs(wy-_boundingBox.y1());
	wx=fabs(wx-_boundingBox.x1());

	switch(_horizontalAlign)
	{
		case hLeft:			x=_boundingBox.x1();
							break;
		case hCenter:		x=_boundingBox.center().x() - wx/2.0;
							break;
		case hRight:		x=_boundingBox.x2() - wx;
							break;
	}
	return true;
}
