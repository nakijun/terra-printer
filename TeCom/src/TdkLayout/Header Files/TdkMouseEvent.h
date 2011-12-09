/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkMouseEvent.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/07/17 11:09:53 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_EVENTS_H
#define __TDK_EVENTS_H

//! \class TdkMouseEvent
/*! Class to mouse events
*/
class TdkMouseEvent
{
public:
//! \enum mouse Button
enum mouseButton
	{
		None=0,		//!< none button pressed
		Left=1,		//!< left button pressed
		Right=2,	//!< right button pressed
		Middle=3,	//!< middle button pressed
		XButton1=4,	//!< XButton1 pressed
		XButton2=5	//!< XButton2 pressed
	};
public:
	double			X;			//! horizontal coordinate
	double			Y;			//! vertical coordinate
	mouseButton		Button;		//! mouse pressed
public:
		//! Constructor
		TdkMouseEvent();		
		//! Destructor
		~TdkMouseEvent();
};



#endif

