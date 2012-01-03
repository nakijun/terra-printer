#include <TdkGdiText.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiText::TdkGdiText()
{
	_angle=0.0;
	_font=new Font(L"Verdana",10,FontStyleRegular,UnitPixel);
	_brush=new SolidBrush(Color(0,0,0));
	_backGroundBrush=new SolidBrush(Color(0,0,0));
	_fontFamily=new FontFamily(L"Verdana");
	_horizontalAlign=centerHorz;
	_verticalAlign=centerVert;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiText::~TdkGdiText()
{
	if(_font)				delete _font;
	if(_brush)				delete _brush;
	if(_fontFamily)			delete _fontFamily;
	if(_backGroundBrush)	delete _backGroundBrush;
}

///////////////////////////////////////////////////////////////////////////////
//Sets text color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiText::setColor(const Color &color)
{
	if(_brush)
	{
		((SolidBrush*)_brush)->SetColor(color);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets the text back color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiText::setBackColor(const Color &color)
{
	if(_backGroundBrush)
	{
		((SolidBrush*)_backGroundBrush)->SetColor(color);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets the text font name
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiText::setFontName(const std::string &name)
{
	WCHAR*			text;
	REAL			textSize=10;
	FontStyle		style=FontStyleRegular;
	std::wstring	wsString;

	wsString=transformString2WChar(name);
	text=(WCHAR*)wsString.c_str();
	if(_font) 
	{
		textSize=_font->GetSize();
		style=(FontStyle)_font->GetStyle();
		delete _font;
	}
	_font=new Font(text,textSize,style,UnitPixel);
}
///////////////////////////////////////////////////////////////////////////////
//Sets the font size
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiText::setFontSize(const float &size)
{
	WCHAR			familyName[LF_FACESIZE];
	FontFamily		family;
	FontStyle		style=FontStyleRegular;

	if(_font)
	{
		_font->GetFamily(&family);
		style=(FontStyle)_font->GetStyle();
		family.GetFamilyName(familyName);
		delete _font;
	}
	_font=new Font(familyName,size,style,UnitPixel);//UnitPixel);
	
}

///////////////////////////////////////////////////////////////////////////////
//Draw a fill square
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
std::wstring TdkGdiText::transformString2WChar(const std::string &text)
{

	 std::wstring		output;
	 size_t				needed;
	
	 needed = ::mbstowcs(NULL,&text[0],text.length());
	 output.resize(needed);
	 ::mbstowcs(&output[0],&text[0],text.length());
	 return output;
}	

///////////////////////////////////////////////////////////////////////////////
//Sets the text alpha color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiText::setAlpha(const int &alpha)
{
	if(_brush)
	{
		Color color;
		((SolidBrush*)_brush)->GetColor(&color);
		((SolidBrush*)_brush)->SetColor(Color(alpha,color.GetR(),color.GetG(),color.GetB()));
	}
	else
	{
		_brush= new SolidBrush(Color(alpha,255,0,0));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a fill square
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiText::setBackAlpha(const int &alpha)
{
	if(_backGroundBrush)
	{
		Color color;
		((SolidBrush*)_backGroundBrush)->GetColor(&color);
		((SolidBrush*)_backGroundBrush)->SetColor(Color(alpha,color.GetR(),color.GetG(),color.GetB()));
	}
	else
	{
		_backGroundBrush= new SolidBrush(Color(alpha,255,0,0));
	}

}

///////////////////////////////////////////////////////////////////////////////
//Sets text
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiText::setAngle(const double &angle)
{
	_angle=angle;
}

///////////////////////////////////////////////////////////////////////////////
//Sets Text Bold
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiText::setTextBold(const bool &b)
{
	WCHAR			familyName[LF_FACESIZE];
	FontFamily		family;
	FontStyle		style=FontStyleRegular;
	REAL			size=10;

	if(_font)
	{
		_font->GetFamily(&family);
		size=_font->GetSize();
		style=(FontStyle)_font->GetStyle();
		family.GetFamilyName(familyName);
		delete _font;
	}
	if(b==true)		style=(FontStyle) (style | FontStyleBold);
	else			style=(FontStyle) (style & FontStyleItalic);

	_font=new Font(familyName,size,style,UnitPixel);
}


///////////////////////////////////////////////////////////////////////////////
//Sets text italic
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiText::setTextItalic(const bool &it)
{
	WCHAR			familyName[LF_FACESIZE];
	FontFamily		family;
	FontStyle		style=FontStyleRegular;
	REAL			size=10;

	if(_font)
	{
		_font->GetFamily(&family);
		size=_font->GetSize();
		style=(FontStyle)_font->GetStyle();
		family.GetFamilyName(familyName);
		delete _font;
	}
	if(it==true)		style=(FontStyle) (style | FontStyleItalic);
	else				style=(FontStyle) (style & FontStyleBold);

	_font=new Font(familyName,size,style,UnitPixel);
}

///////////////////////////////////////////////////////////////////////////////
//Set Horizontal Aligment
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiText::setHorizontalAligment(const horzAlignment &align)
{
	_horizontalAlign=align;
}

///////////////////////////////////////////////////////////////////////////////
//Draw a fill square
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

void TdkGdiText::setVerticalAlignment(const vertAlignment &align)
{
	_verticalAlign=align;
}

///////////////////////////////////////////////////////////////////////////////
//Get Text rectangle
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
RectF TdkGdiText::getRectangle(const double &x, const double &y, const SizeF &size)
{

	RectF	rect;

	switch(_horizontalAlign)
	{
		case leftHorz:		rect.X=(REAL)x;
							break;
		case centerHorz:	rect.X=(REAL)(x - (size.Width/2.0));
							break;
		case rightHorz:		rect.X=(REAL)(x-size.Width);
							break;

	}
	switch(_verticalAlign)
	{
		case bottomVert:	rect.Y=(REAL)y - size.Height;
							break;
		case centerVert:	rect.Y=(REAL)(y - (size.Height/2.0));
							break;
		case topVert:		rect.Y=(REAL)y ;
							break;
	}
	rect.Width=size.Width;
	rect.Height=size.Height;
	return rect;				   
}

///////////////////////////////////////////////////////////////////////////////
//getPointRotate
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiText::getPointRotate(const RectF &rect, PointF &ptRotate, PointF &ptOrig)
{
	switch(_horizontalAlign)
	{
		case leftHorz:		ptRotate.X=rect.X;
							ptOrig.X=0;
							break;
		case centerHorz:	
							ptRotate.X=(REAL)(rect.X + rect.Width/2.0);
							ptOrig.X=(REAL)(-rect.Width/2.0);
							break;
		case rightHorz:		ptRotate.X=rect.X + rect.Width;
							ptOrig.X=-rect.Width;
							break;
	}

	switch(_verticalAlign)
	{
		case bottomVert:	ptRotate.Y=rect.Y + rect.Height;
							ptOrig.Y=-rect.Height;
							break;
		case centerVert:	ptRotate.Y=(REAL)(rect.Y + (rect.Height/(REAL)2.0));
							ptOrig.Y=(REAL)(-rect.Height/2.0);
							break;
		case topVert:		ptRotate.Y=rect.Y;
							ptOrig.Y=0;
							break;
	}


}

///////////////////////////////////////////////////////////////////////////////
//draw
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiText::draw(const double &x, const double &y,const std::string &text, Graphics *graphic)
{
	WCHAR			*wText=NULL;
	PointF			ptR;
	PointF			ptO;
	RectF			rect;
	std::wstring	wsString;
	StringFormat	format;

	if(graphic)
	{
			
		format.SetAlignment(StringAlignmentCenter);
		format.SetDigitSubstitution(LANG_NEUTRAL,StringDigitSubstituteUser);
		format.SetHotkeyPrefix(HotkeyPrefixNone);
		format.SetTabStops(0,0,0);
		SizeF size=MeasureString(text,graphic);

		rect=getRectangle(x,y,size);
		if(_angle)
		{
			getPointRotate(rect,ptR,ptO);
			graphic->TranslateTransform(ptR.X, ptR.Y);
			graphic->RotateTransform((REAL)-_angle);
			rect=RectF(ptO.X,ptO.Y,size.Width,size.Height);
			
		}
		wsString=transformString2WChar(text);
		wText=(WCHAR*)wsString.c_str();
		graphic->DrawString(wText,(INT)text.size(),_font,rect,&format,_brush);
		if(_angle)	graphic->ResetTransform();
	}
}


void TdkGdiText::draw(const RectF &box,const std::string &text, Graphics *graphic)
{
	WCHAR			*wText=NULL;
	PointF			ptR;
	PointF			ptO;
	RectF			rect;
	std::wstring	wsString;
	StringFormat	format;

	if(graphic)
	{
			
		format.SetAlignment(StringAlignmentCenter);
		format.SetDigitSubstitution(LANG_NEUTRAL,StringDigitSubstituteUser);
		format.SetHotkeyPrefix(HotkeyPrefixNone);
		format.SetTabStops(0,0,0);
		SizeF size=MeasureString(text,graphic);

		rect=box;
		if(_angle)
		{
			getPointRotate(rect,ptR,ptO);
			graphic->TranslateTransform(ptR.X, ptR.Y);
			graphic->RotateTransform((REAL)-_angle);
			rect=RectF(ptO.X,ptO.Y,size.Width,size.Height);
		}
		wsString=transformString2WChar(text);
		wText=(WCHAR*)wsString.c_str();
		graphic->DrawString(wText,(INT)text.size(),_font,rect,&format,_brush);
		if(_angle)	graphic->ResetTransform();
	}


}

///////////////////////////////////////////////////////////////////////////////
//Returns the measure of string
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
SizeF TdkGdiText::MeasureString(const std::string &text, Graphics *graphic)
{
	RectF				box(0,0,0,0);
	RectF				doubleBox(0,0,0,0);
	PointF				origin(0.0f, 0.0f);
	WCHAR*				wText;
	std::wstring		wsString;
	StringFormat	format;

	if(graphic)
	{

		format.SetAlignment(StringAlignmentCenter);
		format.SetDigitSubstitution(LANG_NEUTRAL,StringDigitSubstituteUser);
		format.SetHotkeyPrefix(HotkeyPrefixNone);
		format.SetTabStops(0,0,0);

		wsString=transformString2WChar(text);
		wText=(WCHAR*)wsString.c_str();
		graphic->MeasureString(wText,(INT)text.size(),_font,origin,&format,&box);
	}
	return SizeF(box.Width,box.Height);
}

///////////////////////////////////////////////////////////////////////////////
//Returns the font height
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
double TdkGdiText::getHeightFontMetrics(const std::string &text)
{
	double			ascentPixel;
	double			ascent;
	FontFamily		family;

	_font->GetFamily(&family);
	ascent =family.GetCellAscent(FontStyleRegular);
	ascentPixel=_font->GetSize() * ascent / family.GetEmHeight(FontStyleRegular);
	return ascentPixel;
}

