/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutScaleObject.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/08/13 13:42:48 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_LAYOUT_SCALE_OBJECT_H
#define __TDK_LAYOUT_SCALE_OBJECT_H

class TdkMapScaleProperty;
class TdkScaleUnitProperty;
class TdkTextForeColorRProperty;
class TdkTextForeColorGProperty;
class TdkTextForeColorBProperty;
class TdkRedColorProperty;
class TdkGreenColorProperty;
class TdkBlueColorProperty;

#define _widthScale 1.5

class TdkLayoutScaleObject : TdkLayoutObject
{
protected:
	double						_size;				//!<	size value of height rectangle
	TdkMapScaleProperty			*_scale;			//!<	scale value
	double						_unit;				//!<	unit value 1 to meter / 1000 to kilometer
	TdkScaleUnitProperty		*_unitType;			//!<	unit type meter or kilometer
	TdkTextForeColorRProperty	*_redTextColor;		//!<	text color to red channel
	TdkTextForeColorGProperty	*_greenTextColor;	//!<	text color to green channel
	TdkTextForeColorBProperty	*_blueTextColor;	//!<	text colot to blue channel
	TdkRedColorProperty			*_redColor;			//!<	rectangle color to red channel
	TdkGreenColorProperty		*_greenColor;		//!<	rectangle color to green channel
	TdkBlueColorProperty		*_blueColor;		//!<	rectangle color to blue channel

protected:
	//! \brief registerExtendProperties
	/*! Method to instance their properties
	*/
	virtual void registerExtendProperties();

	//! \brief drawScaleRectangles
	/*! Method to draw each rectangle of scale
		\param	canvas		abstract canvas to draw
	*/
	virtual void drawScaleRectangles(TdkAbstractCanvasDraw* canvas);

	//! \brief drawScaleTitle
	/*! Method to draw the scale title
		\param	canvas		abstract canvas to draw
	*/
	virtual void drawScaleTitle(TdkAbstractCanvasDraw* canvas);

	//! \brief drawScaleText
	/*! Method to draw the scale text according calculate value
		\param		canvas	abstract canvas to draw
	*/
	virtual void drawScaleText(TdkAbstractCanvasDraw* canvas);

public:
	//! \brief Constructor
	TdkLayoutScaleObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box);

	//! \brief Destructor
	~TdkLayoutScaleObject();

	//! \brief Draw
	/*! Method to draw the text object on 
		Back Buffer
	*/
	virtual void draw();

	//! \brief print
	/*! Method to print the object
		\param	canvas		canvas pointer
	*/
	virtual void print(TdkAbstractCanvasDraw *canvas);
};


#endif
