#include<TdkLayoutTypes.h>
#include <TdkWin32Decoder.h>
#include <TdkLeftProperty.h>
#include <TdkTopProperty.h>
#include <TdkWidthProperty.h>
#include <TdkHeightProperty.h>
#include <TdkAngleProperty.h>
#include <TdkTextFontNameProperty.h>
#include <TdkTextValueProperty.h>
#include <TdkTextSizeProperty.h>
#include <TdkTextBoldProperty.h>
#include <TdkTextItalicProperty.h>
#include <TdkTextForeColorRProperty.h>
#include <TdkTextForeColorGProperty.h>
#include <TdkTextForeColorBProperty.h>
#include <TdkMapScaleProperty.h>
#include <TdkMapFixedScaleProperty.h>
#include <TdkImageFileNameProperty.h>
#include <TdkLineWidthProperty.h>
#include <TdkLineTypeProperty.h>
#include <TdkBackgroundTypeProperty.h>
#include <TdkBackgroundRColorProperty.h>
#include <TdkBackgroundGColorProperty.h>
#include <TdkBackgroundBColorProperty.h>
#include <TdkRedColorProperty.h>
#include <TdkGreenColorProperty.h>
#include <TdkBlueColorProperty.h>
#include <TdkScaleUnitProperty.h>
#include <TdkNorthTypeProperty.h>
#include <TdkUserNameProperty.h>
#include <TdkPasswordProperty.h>
#include <TdkHostProperty.h>
#include <TdkDatabaseNameProperty.h>
#include <TdkDatabaseTypeProperty.h>
#include <TdkDatabaseConnectedProperty.h>
#include <TdkDatabaseConnectionProperty.h>
#include <TdkViewNameProperty.h>
#include <TdkViewUserProperty.h>
#include <TdkMapWorld_x1_Property.h>
#include <TdkMapWorld_y1_Property.h>
#include <TdkMapWorld_x2_Property.h>
#include <TdkMapWorld_y2_Property.h>
#include <TdkSelectedThemeProperty.h>
#include <TdkSelectedFeaturesProperty.h>
#include <TdkSelectionColorProperty.h>
#include <TdkSelectionTransparencyProperty.h>
#include <atlcomcli.h>
#include <comutil.h>


TdkWin32Decoder::TdkWin32Decoder()
{

}

TdkWin32Decoder::~TdkWin32Decoder()
{

}

bool TdkWin32Decoder::decoder(TdkAbstractProperty *prop, VARIANT *pVal)
{
	if(typeid(*prop)==typeid(TdkLeftProperty))
	{
		(*pVal).dblVal=((TdkLeftProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkTopProperty))
	{
		(*pVal).dblVal=((TdkTopProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkWidthProperty))
	{
		(*pVal).dblVal=((TdkWidthProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkHeightProperty))
	{
		(*pVal).dblVal=((TdkWidthProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkAngleProperty))
	{
		(*pVal).dblVal=((TdkAngleProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkTextValueProperty))
	{
		CComBSTR	propValue=((TdkTextValueProperty*)prop)->getValue().c_str();
		(*pVal).bstrVal=propValue.Copy();
		(*pVal).vt=VT_BSTR;
	}else if(typeid(*prop) == typeid(TdkTextSizeProperty))
	{
		(*pVal).dblVal=((TdkTextSizeProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkTextFontNameProperty))
	{
		CComBSTR	propValue=((TdkTextFontNameProperty*)prop)->getValue().c_str();
		(*pVal).bstrVal=propValue.Copy();
		(*pVal).vt=VT_BSTR;
	}else if(typeid(*prop) == typeid(TdkTextBoldProperty))
	{
		(*pVal).boolVal=(VARIANT_BOOL)((TdkTextBoldProperty*)prop)->getValue();
		(*pVal).vt=VT_BOOL;
	}else if(typeid(*prop) == typeid(TdkTextItalicProperty))
	{
		(*pVal).boolVal=(VARIANT_BOOL)((TdkTextItalicProperty*)prop)->getValue();
		(*pVal).vt=VT_BOOL;
	}else if(typeid(*prop) == typeid(TdkMapFixedScaleProperty))
	{
		(*pVal).boolVal=(VARIANT_BOOL)((TdkMapFixedScaleProperty*)prop)->getValue();
		(*pVal).vt=VT_BOOL;
	}else if(typeid(*prop) == typeid(TdkTextForeColorRProperty))
	{
		(*pVal).dblVal=((TdkTextForeColorRProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}
	else if(typeid(*prop) == typeid(TdkTextForeColorGProperty))
	{
		(*pVal).dblVal=((TdkTextForeColorGProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkTextForeColorBProperty))
	{
		(*pVal).dblVal=((TdkTextForeColorBProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkMapScaleProperty))
	{
		(*pVal).dblVal=((TdkMapScaleProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkImageFileNameProperty))
	{
		CComBSTR	propValue=((TdkImageFileNameProperty*)prop)->getValue().c_str();
		(*pVal).bstrVal=propValue.Copy();
		(*pVal).vt=VT_BSTR;
	}else if(typeid(*prop) == typeid(TdkLineWidthProperty))
	{
		(*pVal).dblVal=((TdkLineWidthProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkLineTypeProperty))
	{
		(*pVal).dblVal=((TdkLineTypeProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkBackgroundTypeProperty))
	{
		(*pVal).dblVal=((TdkBackgroundTypeProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkBackgroundRColorProperty))
	{
		(*pVal).dblVal=((TdkBackgroundRColorProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkBackgroundGColorProperty))
	{
		(*pVal).dblVal=((TdkBackgroundGColorProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkBackgroundBColorProperty))
	{
		(*pVal).dblVal=((TdkBackgroundBColorProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkRedColorProperty))
	{
		(*pVal).dblVal=((TdkRedColorProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkGreenColorProperty))
	{
		(*pVal).dblVal=((TdkGreenColorProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkBlueColorProperty))
	{
		(*pVal).dblVal=((TdkBlueColorProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkScaleUnitProperty))
	{
		(*pVal).dblVal=(double)((TdkScaleUnitProperty*)prop)->getValue();
		(*pVal).vt=VT_R8;
	}else if(typeid(*prop) == typeid(TdkNorthTypeProperty))
	{
		CComBSTR	propValue=((TdkNorthTypeProperty*)prop)->getValue().c_str();
		(*pVal).bstrVal=propValue.Copy();
		(*pVal).vt=VT_BSTR;
	}else if(typeid(*prop) == typeid(TdkUserNameProperty))
	{
		CComBSTR	propValue=((TdkUserNameProperty*)prop)->getValue().c_str();
		(*pVal).bstrVal=propValue.Copy();
		(*pVal).vt=VT_BSTR;
	}else if(typeid(*prop) == typeid(TdkPasswordProperty))
	{
		CComBSTR	propValue=((TdkPasswordProperty*)prop)->getValue().c_str();
		(*pVal).bstrVal=propValue.Copy();
		(*pVal).vt=VT_BSTR;
	}else if(typeid(*prop) == typeid(TdkHostProperty))
	{
		CComBSTR	propValue=((TdkHostProperty*)prop)->getValue().c_str();
		(*pVal).bstrVal=propValue.Copy();
		(*pVal).vt=VT_BSTR;
	}else if(typeid(*prop) == typeid(TdkDatabaseNameProperty))
	{
		CComBSTR	propValue=((TdkDatabaseNameProperty*)prop)->getValue().c_str();
		(*pVal).bstrVal=propValue.Copy();
		(*pVal).vt=VT_BSTR;
	}else if(typeid(*prop) == typeid(TdkDatabaseTypeProperty))
	{
		(*pVal).dblVal=(double)((TdkDatabaseTypeProperty*)prop)->getValue();
		(*pVal).vt=VT_R8;
	}else if(typeid(*prop) == typeid(TdkDatabaseConnectedProperty))
	{
		(*pVal).boolVal=(VARIANT_BOOL)((TdkDatabaseConnectedProperty*)prop)->getValue();
		(*pVal).vt=VT_BOOL;
	}else if(typeid(*prop) == typeid(TdkDatabaseConnectionProperty))
	{
		CComBSTR	propValue=((TdkDatabaseConnectionProperty*)prop)->getValue().c_str();
		(*pVal).bstrVal=propValue.Copy();
		(*pVal).vt=VT_BSTR;
	}else if(typeid(*prop) == typeid(TdkViewNameProperty))
	{
		CComBSTR	propValue=((TdkViewNameProperty*)prop)->getValue().c_str();
		(*pVal).bstrVal=propValue.Copy();
		(*pVal).vt=VT_BSTR;
	}else if(typeid(*prop) == typeid(TdkViewUserProperty))
	{
		CComBSTR	propValue=((TdkViewUserProperty*)prop)->getValue().c_str();
		(*pVal).bstrVal=propValue.Copy();
		(*pVal).vt=VT_BSTR;
	}else if(typeid(*prop) == typeid(TdkMapWorld_x1_Property))
	{
		(*pVal).dblVal=((TdkMapWorld_x1_Property*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkMapWorld_x2_Property))
	{
		(*pVal).dblVal=((TdkMapWorld_x2_Property*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkMapWorld_y1_Property))
	{
		(*pVal).dblVal=((TdkMapWorld_y1_Property*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkMapWorld_y2_Property))
	{
		(*pVal).dblVal=((TdkMapWorld_y2_Property*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkSelectedThemeProperty))
	{
		CComBSTR	propValue=((TdkSelectedThemeProperty*)prop)->getValue().c_str();
		(*pVal).bstrVal=propValue.Copy();
		(*pVal).vt=VT_BSTR;
	}else if(typeid(*prop) == typeid(TdkSelectedFeaturesProperty))
	{
		CComBSTR	propValue=((TdkSelectedFeaturesProperty*)prop)->getValue().c_str();
		(*pVal).bstrVal=propValue.Copy();
		(*pVal).vt=VT_BSTR;
	}else if(typeid(*prop) == typeid(TdkSelectionColorProperty))
	{
		(*pVal).dblVal=((TdkSelectionColorProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}else if(typeid(*prop) == typeid(TdkSelectionTransparencyProperty))
	{
		(*pVal).dblVal=((TdkSelectionTransparencyProperty*)prop)->getValue();
		(*pVal).vt= VT_R8;
	}
	
	return false;
}

double	TdkWin32Decoder::getAsDoubleValue(VARIANT pVal)
{
	double		value=0;

	switch(pVal.vt)
	{
		case VT_I8 :	value=(double)pVal.llVal;
						break;
		case VT_I4 :	value=(double)pVal.lVal;
						break;
		case  VT_I2:	value=(double)pVal.iVal;
						break;	
		case  VT_R4:	value=(double)pVal.fltVal;
						break;	
		case  VT_R8:	value=(double)pVal.dblVal;
						break;	
		case  VT_CY:	value=(double)pVal.cyVal.int64;
						break;	
		case  VT_UI2:	value=(double)pVal.uiVal;
						break;	
		case  VT_UI4:	value=(double)pVal.ulVal;
						break;	
		case  VT_UI8:	value=(double)pVal.ullVal;
						break;	
		case  VT_UINT:	value=(double)pVal.uintVal;
						break;	
	}

	return value;
}


bool TdkWin32Decoder::encoder(TdkAbstractProperty *prop, VARIANT pVal)
{
	if(typeid(*prop)==typeid(TdkLeftProperty))
	{
		((TdkLeftProperty*)prop)->setValue(getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkTopProperty))
	{
		((TdkTopProperty*)prop)->setValue(getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkHeightProperty))
	{
		((TdkWidthProperty*)prop)->setValue(getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkWidthProperty))
	{
		((TdkWidthProperty*)prop)->setValue(getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkAngleProperty))
	{
		((TdkAngleProperty*)prop)->setValue(getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkTextValueProperty))
	{
		((TdkTextValueProperty*)prop)->setValue(std::string(bstr_t(pVal.bstrVal)));
	}else if(typeid(*prop) == typeid(TdkTextSizeProperty))
	{
		((TdkTextSizeProperty*)prop)->setValue(getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkTextFontNameProperty))
	{
		((TdkTextFontNameProperty*)prop)->setValue(std::string(bstr_t(pVal.bstrVal)));
	}else if(typeid(*prop) == typeid(TdkTextBoldProperty))
	{
		((TdkTextBoldProperty*)prop)->setValue((pVal.boolVal == FALSE ? false : true));
	}else if(typeid(*prop) == typeid(TdkTextItalicProperty))
	{
		((TdkTextItalicProperty*)prop)->setValue((pVal.boolVal == FALSE ? false : true));
	}else if(typeid(*prop) == typeid(TdkTextForeColorRProperty))
	{
		((TdkTextForeColorRProperty*)prop)->setValue((unsigned int) getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkTextForeColorGProperty))
	{
		((TdkTextForeColorGProperty*)prop)->setValue((unsigned int) getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkTextForeColorBProperty))
	{
		((TdkTextForeColorBProperty*)prop)->setValue((unsigned int) getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkMapScaleProperty))
	{
		((TdkMapScaleProperty*)prop)->setValue((unsigned int) getAsDoubleValue(pVal));
		((TdkMapScaleProperty*)prop)->setExternalScale();
	}else if(typeid(*prop) == typeid(TdkMapFixedScaleProperty))
	{
		((TdkMapFixedScaleProperty*)prop)->setValue((pVal.boolVal == FALSE ? false : true));
	}else if(typeid(*prop) == typeid(TdkImageFileNameProperty))
	{
		((TdkImageFileNameProperty*)prop)->setValue(std::string(bstr_t(pVal.bstrVal)));
	}else if(typeid(*prop) == typeid(TdkLineWidthProperty))
	{
		((TdkLineWidthProperty*)prop)->setValue((unsigned int) getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkLineTypeProperty))
	{
		((TdkLineTypeProperty*)prop)->setValue((unsigned int) getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkBackgroundTypeProperty))
	{
		((TdkBackgroundTypeProperty*)prop)->setValue((unsigned int) getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkBackgroundRColorProperty))
	{
		((TdkBackgroundRColorProperty*)prop)->setValue((unsigned int) getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkBackgroundGColorProperty))
	{
		((TdkBackgroundGColorProperty*)prop)->setValue((unsigned int) getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkBackgroundBColorProperty))
	{
		((TdkBackgroundBColorProperty*)prop)->setValue((unsigned int) getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkRedColorProperty))
	{
		((TdkRedColorProperty*)prop)->setValue((unsigned int) getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkGreenColorProperty))
	{
		((TdkGreenColorProperty*)prop)->setValue((unsigned int) getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkBlueColorProperty))
	{
		((TdkBlueColorProperty*)prop)->setValue((unsigned int) getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkScaleUnitProperty))
	{
		((TdkScaleUnitProperty*)prop)->setValue((TdkScaleUnitProperty::Unit)((int)getAsDoubleValue(pVal)));
	}
	else if(typeid(*prop) == typeid(TdkNorthTypeProperty))
	{
		((TdkNorthTypeProperty*)prop)->setValue(std::string(bstr_t(pVal.bstrVal)));
	}else if(typeid(*prop) == typeid(TdkUserNameProperty))
	{
		((TdkUserNameProperty*)prop)->setValue(std::string(bstr_t(pVal.bstrVal)));
	}else if( typeid(*prop) == typeid(TdkPasswordProperty) )
	{
		((TdkPasswordProperty*)prop)->setValue(std::string(bstr_t(pVal.bstrVal)));
	}else if(typeid(*prop) == typeid(TdkHostProperty))
	{
		((TdkHostProperty*)prop)->setValue(std::string(bstr_t(pVal.bstrVal)));
	}else if(typeid(*prop) == typeid(TdkDatabaseNameProperty))
	{
		((TdkDatabaseNameProperty*)prop)->setValue(std::string(bstr_t(pVal.bstrVal)));
	}else if(typeid(*prop) == typeid(TdkDatabaseTypeProperty))
	{
		int	value=(int)getAsDoubleValue(pVal);
		((TdkDatabaseTypeProperty*)prop)->setValue((connectionType)value);		
	}else if(typeid(*prop) == typeid(TdkDatabaseConnectedProperty))
	{
		((TdkDatabaseConnectedProperty*)prop)->setValue((pVal.boolVal == FALSE ? false : true));
	}else if(typeid(*prop) == typeid(TdkDatabaseConnectionProperty))
	{
		((TdkDatabaseConnectionProperty*)prop)->setValue(std::string(bstr_t(pVal.bstrVal)));
	}
	else if(typeid(*prop) == typeid(TdkViewNameProperty))
	{
		((TdkViewNameProperty*)prop)->setValue(std::string(bstr_t(pVal.bstrVal)));

	}else if(typeid(*prop) == typeid(TdkViewUserProperty))
	{
		((TdkViewUserProperty*)prop)->setValue(std::string(bstr_t(pVal.bstrVal)));

	}else if(typeid(*prop)==typeid(TdkMapWorld_x1_Property))
	{
		((TdkMapWorld_x1_Property*)prop)->setValue(getAsDoubleValue(pVal));

	}else if(typeid(*prop)==typeid(TdkMapWorld_y1_Property))
	{
		((TdkMapWorld_y1_Property*)prop)->setValue(getAsDoubleValue(pVal));

	}else if(typeid(*prop)==typeid(TdkMapWorld_x2_Property))
	{
		((TdkMapWorld_x2_Property*)prop)->setValue(getAsDoubleValue(pVal));

	}else if(typeid(*prop)==typeid(TdkMapWorld_y2_Property))
	{
		((TdkMapWorld_y2_Property*)prop)->setValue(getAsDoubleValue(pVal));

	}else if(typeid(*prop) == typeid(TdkSelectedThemeProperty))
	{
		((TdkSelectedThemeProperty*)prop)->setValue(std::string(bstr_t(pVal.bstrVal)));

	}else if(typeid(*prop) == typeid(TdkSelectedFeaturesProperty))
	{
		((TdkSelectedFeaturesProperty*)prop)->setValue(std::string(bstr_t(pVal.bstrVal)));
	}else if(typeid(*prop) == typeid(TdkSelectionColorProperty))
	{
		((TdkSelectionColorProperty*)prop)->setValue(getAsDoubleValue(pVal));
	}else if(typeid(*prop) == typeid(TdkSelectionTransparencyProperty))
	{
		((TdkSelectionTransparencyProperty*)prop)->setValue(getAsDoubleValue(pVal));
	}
	return true;
}