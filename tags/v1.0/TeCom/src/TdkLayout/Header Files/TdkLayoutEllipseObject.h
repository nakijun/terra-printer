/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutEllipseObject.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/08/10 13:16:50 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_LAYOUT_ELLIPSE_OBJECT_H
#define __TDK_LAYOUT_ELLIPSE_OBJECT_H

#include <TdkLayoutRectangleObject.h>


//! \class TdkLayoutEllipseObject
/*! Class to ellipse manipulation
	\sa TdkLayoutObject
*/
class TdkLayoutEllipseObject : public TdkLayoutRectangleObject
{
protected :


public :
	//! \brief Constructor
	TdkLayoutEllipseObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box);

	//! \brief Destructor
	~TdkLayoutEllipseObject();

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

