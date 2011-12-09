/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutRectangleObject.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/08/12 14:15:34 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_LAYOUT_RECTANGLE_OBJECT_H
#define __TDK_LAYOUT_RECTANGLE_OBJECT_H

#include <TdkLayoutObject.h>

class TdkAbstractCanvasDraw;
class TdkLineWidthProperty;
class TdkLineTypeProperty;
class TdkBackgroundTypeProperty;
class TdkBackgroundRColorProperty;
class TdkBackgroundGColorProperty;
class TdkBackgroundBColorProperty;
class TdkRedColorProperty;
class TdkGreenColorProperty;
class TdkBlueColorProperty;

#define __rectangleTYPE		"__rectangleTYPE"

//! \class TdkLayoutRectangleObject
/*! Class to rectangle manipulation
	\sa TdkLayoutObject
*/
class TdkLayoutRectangleObject : public TdkLayoutObject
{
protected:

	TdkLineWidthProperty		*_width;				//!< width rectangle
	TdkLineTypeProperty			*_borderType;			//!< border type of rectangle
	TdkBackgroundTypeProperty	*_backgroundType;		//!< background type of rectangle
	TdkBackgroundRColorProperty	*_backgroundRColor;		//!< background color ( red channel )
	TdkBackgroundGColorProperty *_backgroundGColor;		//!< background color ( green channel )
	TdkBackgroundBColorProperty	*_backgroundBColor;		//!< background color ( blue channel )
	TdkRedColorProperty			*_foreRColor;			//!< fore color	( red channel )
	TdkGreenColorProperty		*_foreGColor;			//!< fore color ( green channel )
	TdkBlueColorProperty		*_foreBColor;			//!< fore color	( blue channel )

protected:

	//! \brief registerExtendProperties
	/*! Method to instance their properties
	*/
	virtual void registerExtendProperties();

	

public:

	//! \brief Constructor
	TdkLayoutRectangleObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box);

	//! \brief Destructor
	~TdkLayoutRectangleObject();

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

