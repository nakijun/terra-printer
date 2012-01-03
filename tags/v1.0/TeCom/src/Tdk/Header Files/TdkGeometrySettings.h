/******************************************************************************
* FUNCATE - GIS development team
* 
* @(#) TdkGeometrySettings.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/04/08 17:56:01 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_GEOMETRY_SETTINGS_H
#define __TDK_GEOMETRY_SETTINGS_H

#include <TeVisual.h>
#include <string>

using namespace std;

//! \class TdkGeometrySettings
/*! Class to storage the geometries settings
*/
class TdkGeometrySettings
{
protected:
	TeColor			_lineColor;					//!<	line color
	short			_lineType;					//!<	line type
	double			_lineWidth;					//!<	line width
	TeColor			_polygonColor;				//!<	polygon color
	short			_polygonType;				//!<	polygon type
	double			_polygonWidth;				//!<	polygon width
	TeColor			_pointColor;				//!<	point color
	double			_pointSize;					//!<	point size
	short			_pointType;					//!<	point type
	std::string		_pointExternFileType;		//!<	file name associate with point as symbol
	TeColor			_textColor;					//!<	text color
	double			_textSize;					//!<	text size
	double			_textAngle;
	std::string		_fontName;					//!<	font name
	bool			_isPolygon;					//!<	set current setting as polygon
public:
	
	//! \brief Constructor
	TdkGeometrySettings();

	//! \brief Destructor
	virtual ~TdkGeometrySettings();

	//! \brief setLineColor
	/*! Set the line color
		\param	color		color value
	*/
	virtual void setLineColor(const TeColor &color);

	//! \brief getLineColor
	/*! Gets the line color
		\return returns the line color
	*/
	virtual TeColor getLineColor();

	//! \brief setLineType
	/*! Sets the line type
		\param	type	line type
	*/
	virtual void setLineType(const short &type);

	//! \brief getLineType
	/*! Method to return the line type
		\return returns the short value
	*/
	virtual short getLineType();

	//! \brief setLineWidth
	/*! Method to set the line width
		\param	width	width value
	*/
	virtual void setLineWidth(const double &width);

	//! \brief getLineWidth
	/*! Method to return the line width
		\return	returns the line width value
	*/
	virtual double getLineWidth();

	//! \brief setPolygonColor
	/*! Method to set the polygon color
		\param	color	color value
	*/
	virtual void setPolygonColor(const TeColor &color);

	//! \brief getPolygonColor
	/*! Method to return the polygon color
		\return	returns the polygon color value
	*/
	virtual TeColor getPolygonColor();

	//! \brief setPolygonType
	/*! Method to set the polygon type
		\param	type		polygon type value
	*/
	virtual void setPolygonType(const short &type);

	//! \brief getPolygonType
	/*! Method to reteurn the polygon type
		\return	returns the polygon type value
	*/
	virtual short getPolygonType();

	//! \brief setPolygonWidth
	/*! Method to set the polygon width
		\param	width	polygon width value
	*/
	virtual void setPolygonWidth(const double &width);

	//! \brief getPolygonWidth
	/*! Method to return the polygon width
		\return	returns the polygon width value
	*/
	virtual double getPolygonWidth();

	//! \brief setPointColor
	/*! Method to set the point color
		\param	color		color value
	*/
	virtual void setPointColor(const TeColor &color);

	//! \brief getPointColor
	/*! Method to return the point color
		\return returns the point color value
	*/
	virtual TeColor getPointColor();
	
	//! \brief setPointType
	/*! Method to set the point type
		\param	type		point type value
	*/
	virtual void setPointType(const short &type);

	//! \brief getPointType
	/*! Method to returns the point type
		\return	returns the point type value
	*/
	virtual short getPointType();

	//! \brief setPointSize
	/*! Method to set the point size value
		\param	size	double value
	*/
	virtual void setPointSize(const double &size);

	//! \brief getPointSize
	/*! Method to return the point size value
		\return returns the double value 
	*/
	virtual double getPointSize();

	//! \brief setPointExternalFileName
	/*! Method to setting the external file (dwg, dxf)
		used as point symbol
		\param	fileName		file name
	*/
	virtual void setPointExternalFileName(const std::string &fileName);

	//! \brief getPointExternalFileName
	/*! Method to return the externa file associate with
		point to use as symbol
		\return	returns the file name
	*/
	virtual std::string getPointExternalFileName();

	//! \brief setTextColor
	/*! Method to set the text color 
		\param	color color value
	*/
	virtual void setTextColor(const TeColor &color);

	//! \brief getTextColor
	/* Method to return the text color
		\return	 returns the color value
	*/
	virtual TeColor getTextColor();

	//! \brief setTextSize
	/*! Method to sets the text size
		\param	textSize		text size value
	*/
	virtual void setTextSize(const double &textSize);

	//! \brief getTextSize
	/*! Method to return the text size
		\return	returns the text size value
	*/
	virtual double getTextSize();

	//! \brief setTextFontName
	/*! Method to set the font name of text
		\param	fontName		font name
	*/
	virtual void setTextFontName(const std::string &fontName);

	//! \brief getTextFontName
	/*! Method to return the font name associate with text
		\return	returns the font name
	*/
	virtual std::string getTextFontName();

	//! \brief setTextAngle
	/*! Method to set the text angle
		\param	angle		angle value
	*/
	virtual void setTextAngle(const double &angle);

	//! \brief getTextAngle
	/*! Method to returns the text angle
	*/
	virtual double getTextAngle();

	//! \brief setIsPolygon
	/*! Method to set the current setting like
		polygon process
		\param	status		boolean value
	*/
	virtual void setIsPolygon(const bool &status);

};

#endif
