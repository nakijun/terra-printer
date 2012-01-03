
/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutTypes.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/09/17 16:46:19 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_LAYOUT_DATA_TYPES_H
#define __TDK_LAYOUT_DATA_TYPES_H

#define rulerSize		30
#define rulerSize3D		rulerSize + 1 

//! \enum pageOrientation
/*! Enum to define page orientation */
typedef enum pageOrientation
{
	portrait=0,	//!< portrait option	
	landscape=1 //!< landscape option
} Orientation;

//! \enum	pageSize
/*! Enum to define page type */	
typedef enum pageSize
{
	A0=0,//!< A0 page size		
	A1=1,//!< A1 page size		
	A2=2,//!< A2 page size		
	A3=3,//!< A3 page size		
	A4=4,//!< A4 page size		
	A5=5,//!< A5 page size
	A6=6,//!< A6 page size
	Custom=7//!< custom page size
}PaperSize;


typedef enum Alignment
{
	Left_Align=0,
	Right_Align=1,
	Top_Align=2,
	Bottom_Align=3,
	Horizontal_Center_Align=4,
	Vertical_Center_Align=5
}TdkAlignment;

typedef enum horizontalTextAlignment
{
	hLeft=0,		hCenter=1,		hRight=2
}hrzTextAlign;

typedef enum verticalTextAlignment
{
	vTop=0,			vCenter=1,		vBottom=2
}vertTextAlign;


typedef enum MOVE_KEYS
{
	TDK_LEFT = 0x25,
	TDK_UP	 = 0x26,
	TDK_RIGHT = 0x27,
	TDK_DOWN  = 0x28
}moveKeys;


typedef enum HOT_POINTS
	{
		LeftTop=0,		
		MiddleTop=1,
		RightTop=2,
		MiddleRight=3,
		RightBottom=4,
		MiddleBottom=5,
		LeftBottom=6,
		MiddleLeft=7,
		NonePoint=8,
		RotatePoint=9
	}hotPoint;

typedef enum CURSOR_MODE
{
	CursorNormal	= 0,
	CursorWait		= 1,
	CursorCross		= 2,
	CursorNWSE		= 3,
	CursorNESW		= 4,
	CursorWE		= 5,
	CursorNS		= 6,
	CursorAll		= 7,
	CursorHand		= 8,
	CursorZoom		= 9,
	CursorZoomOut	= 10,
	CursorFinger	= 11
} cursorMode;


typedef enum CONNECTION_TYPE
{
	Access			= 0,
	SqlServer		= 1,
	Oracle			= 2,
	FireBird		= 3,
	PostgreSQL		= 4
}connectionType;



typedef enum MAP_MODE
{
	None		= 0,
	Pan			= 1,
	ZoomIn		= 2,
	ZoomOut		= 3,
	ZoomArea	= 4,
	FullExtend	= 5
}MapMode;


typedef enum LAYOUT_MODE
{
	LNone		= 0,
	LZoomOut	= 1,
	LZoomArea	= 2,
	LPan		= 3
}layoutMode;


typedef enum PROPERTY_TYPE
{
	PNumber		= 0,
	PBoolean	= 1,
	PText		= 2,
	PColor		= 3,
	PBinary		= 4
}propertyType;




#endif

