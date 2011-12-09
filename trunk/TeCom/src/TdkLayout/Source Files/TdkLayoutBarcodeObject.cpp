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
#include<TdkLayoutBarcodeObject.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutBarcodeObject::TdkLayoutBarcodeObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas, const TeBox &box,const std::string textValue) : TdkLayoutTextObject(id,canvas,box,textValue)
{
	_type=LT_BARCODE;
	if(textValue.empty())	_text->setValue("1234567890");
	else					_text->setValue(textValue);
	_objectName="Barcode_" + Te2String(id,0);
	_size->setValue(2.5);//mm
	_fontName->setValue("Free 3 of 9 Extended");
	registerExtendProperties();
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutBarcodeObject::~TdkLayoutBarcodeObject()
{
	if(_fontName)		delete _fontName;
}

///////////////////////////////////////////////////////////////////////////////
//Register Properties Method
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutBarcodeObject::registerExtendProperties()
{
	_properties.erase(_properties.end() - 6); // remove _fontName
}