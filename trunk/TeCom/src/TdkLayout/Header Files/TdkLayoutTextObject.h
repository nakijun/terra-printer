/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutTextObject.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/09/16 17:37:20 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_LAYOUT_TEXT_OBJECT_H
#define __TDK_LAYOUT_TEXT_OBJECT_H

#include <TdkLayoutObject.h>

class TdkAbstractCanvasDraw;
class TdkTextValueProperty;
class TdkTextSizeProperty;
class TdkTextFontNameProperty;
class TdkTextBoldProperty;
class TdkTextItalicProperty;
class TdkTextForeColorRProperty;
class TdkTextForeColorGProperty;
class TdkTextForeColorBProperty;

#define __textTYPE		"__textTYPE"

//! \class TdkLayoutTextObject
/*! Class to text manipulation
	\sa TdkLayoutObject
*/
class TdkLayoutTextObject : public TdkLayoutObject
{
protected :
	TdkTextValueProperty			*_text;						//!< Strint to draw
	TdkTextSizeProperty				*_size;						//!< font size
	TdkTextFontNameProperty			*_fontName;					//!< font name
	TdkTextBoldProperty				*_bold;						//!< Bold style
	TdkTextItalicProperty			*_italic;					//!< Italic style
	TdkTextForeColorRProperty		*_foreRColor;
	TdkTextForeColorGProperty		*_foreGColor;
	TdkTextForeColorBProperty		*_foreBColor;
	bool							_autoSize;					//!< Auto size option
	hrzTextAlign					_horizontalAlign;			//!< horizontal alignment
	vertTextAlign					_verticalAlign;				//!< vertical alignment
protected:
	//! \brief calculateBox
	/*! Method used with autosize option to calculate
		the real box from text according your font
	*/
	virtual void calculateBox(TdkAbstractCanvasDraw *canvas);

	//! \brief calculateCoordinate
	/*! Method to calculate the real coordinate according alignment settings
		\param		x		coordinate
		\param		y		coordinate
		\param		canvas	abstract canvas pointer
		\return		true whether calculate the position
	*/
	virtual bool calculateCoordinate(double &x,double &y,TdkAbstractCanvasDraw *canvas);

	//! \brief registerExtendProperties
	/*! Register the extend properties
	*/
	virtual void registerExtendProperties();

public :
		//!	\brief Constructor
		/*! Constructor with unique id, canvas pointer and bounding box
			to creation
			\param		id			unique id
			\param		canvas		abstract canvas pointer
			\param		box			initial bounding box
			\param		textValue	string value
		*/
	TdkLayoutTextObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas, const TeBox &box,const std::string textValue="");

		//! \brief Destructor
		virtual ~TdkLayoutTextObject();

		//! \brief Draw
		/*! Method to draw the text object on 
			Back Buffer
		*/
		virtual void draw();

		//! \brief setAutoSize
		/*! Method to calculate the automatic bounding box
			\param		status		boolean parameter
		*/
		virtual void setAutoSize(const bool &status);

		//! \brief print
		/*! Method to print the object
			\param	canvas		canvas pointer
		*/
		virtual void print(TdkAbstractCanvasDraw *canvas);

		//! \brief setBoundingBox
		/*! Method to set the object bounding box
			\param		box		terralib bounding box
		*/
		virtual void setBoundingBox(const TeBox &box);

		//! \brief setTextSize
		virtual void setRatio(const double &ratioSize);
};


#endif
