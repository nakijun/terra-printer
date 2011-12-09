/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutLineObject.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/08/10 14:10:16 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_LAYOUT_LINE_OBJECT_H
#define __TDK_LAYOUT_LINE_OBJECT_H



class TdkLineWidthProperty;
class TdkLineTypeProperty;
class TdkRedColorProperty;
class TdkGreenColorProperty;
class TdkBlueColorProperty;


class TdkLayoutLineObject : public TdkLayoutObject
{
protected:
	TdkLineWidthProperty		*_width;				//!< width rectangle
	TdkLineTypeProperty			*_borderType;			//!< border type of rectangle
	TdkRedColorProperty			*_foreRColor;			//!< fore color	( red channel )
	TdkGreenColorProperty		*_foreGColor;			//!< fore color ( green channel )
	TdkBlueColorProperty		*_foreBColor;			//!< fore color	( blue channel )
protected:
	//! \brief registerExtendProperties
	/*! Method to instance their properties
	*/
	virtual void registerExtendProperties();
public :
	//! \brief Constructor
	TdkLayoutLineObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box);

	//! \brief Destructor
	~TdkLayoutLineObject();

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

