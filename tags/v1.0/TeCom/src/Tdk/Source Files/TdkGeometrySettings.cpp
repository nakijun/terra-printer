#include <TdkGeometrySettings.h>

TdkGeometrySettings::TdkGeometrySettings()
{
	_lineColor=TeColor(0,0,0);
	_lineType=0;
	_lineWidth=1;
	_polygonColor=TeColor(0,0,0);
	_polygonType=1;
	_polygonWidth=1;		
	_pointColor=TeColor(0,0,0);
	_pointSize=1;
	_pointType=1;
	_pointExternFileType="";
	_textColor=TeColor(0,0,0);
	_textSize=10;
	_fontName="Verdana";
	_textAngle=0;

}

TdkGeometrySettings::~TdkGeometrySettings()
{

}

void TdkGeometrySettings::setLineColor(const TeColor &color)
{
	_lineColor=color;
}

TeColor TdkGeometrySettings::getLineColor()
{
	return _lineColor;
}

void TdkGeometrySettings::setLineType(const short &type)
{
	_lineType=type;
}

short TdkGeometrySettings::getLineType()
{
	return _lineType;
}

void TdkGeometrySettings::setLineWidth(const double &width)
{
	_lineWidth=width;
}

double TdkGeometrySettings::getLineWidth()
{
	return _lineWidth;
}

void TdkGeometrySettings::setPolygonColor(const TeColor &color)
{
	_polygonColor=color;
}

TeColor TdkGeometrySettings::getPolygonColor()
{
	return _polygonColor;
}

void TdkGeometrySettings::setPolygonType(const short &type)
{
	_polygonType=type;
}

short TdkGeometrySettings::getPolygonType()
{
	return _polygonType;
}

void TdkGeometrySettings::setPolygonWidth(const double &width)
{
	_polygonWidth=width;
}

double TdkGeometrySettings::getPolygonWidth()
{
	return _polygonWidth;
}

void TdkGeometrySettings::setPointColor(const TeColor &color)
{
	_pointColor=color;
}

TeColor TdkGeometrySettings::getPointColor()
{
	return _pointColor;
}

void TdkGeometrySettings::setPointType(const short &type)
{
	_pointType=type;
}

short TdkGeometrySettings::getPointType()
{
	return _pointType;
}

void TdkGeometrySettings::setPointSize(const double &size)
{
	_pointSize=size;
}

double TdkGeometrySettings::getPointSize()
{
	return _pointSize;
}

void TdkGeometrySettings::setPointExternalFileName(const std::string &fileName)
{
	_pointExternFileType=fileName;
}

std::string TdkGeometrySettings::getPointExternalFileName()
{
	return _pointExternFileType;
}

void TdkGeometrySettings::setTextColor(const TeColor &color)
{
	_textColor=color;
}

TeColor TdkGeometrySettings::getTextColor()
{
	return _textColor;
}

void TdkGeometrySettings::setTextSize(const double &textSize)
{
	_textSize=textSize;
}

double TdkGeometrySettings::getTextSize()
{
	return _textSize;
}

void TdkGeometrySettings::setTextFontName(const std::string &fontName)
{
	_fontName=fontName;
}

std::string TdkGeometrySettings::getTextFontName()
{
	return _fontName;
}

void TdkGeometrySettings::setTextAngle(const double &angle)
{
	_textAngle=angle;
}

double TdkGeometrySettings::getTextAngle()
{
	return _textAngle;	
}

void TdkGeometrySettings::setIsPolygon(const bool &status)
{
	_isPolygon=status;
}