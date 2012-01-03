/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutMTextObject.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/08/27 20:17:26 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_LAYOUT_MULTI_TEXT_OBJECT_H
#define __TDK_LAYOUT_MULTI_TEXT_OBJECT_H


#include "TdkLayoutTextObject.h"


#define __mTextTYPE		"__mTextTYPE"


//! \class TdkLayoutMTextObject
/*! Class to draw multi lines text
*/
class TdkLayoutMTextObject : public TdkLayoutTextObject
{
protected:

	//! \brief registerExtendProperties
	virtual void registerExtendProperties();

	//! \brief splitTextInTextLines
	/*! Split a simple text in text list vector
		\param	value		original text
		\return	returns the vector breaking the text where find '\n'
	*/
	virtual vector<std::string>	splitTextInTextLines(const std::string &value);

	//! \brief getTextHeight
	/*! Method to return the text height
		\param	canvas		canvas pointer
		\param	text		text to draw
		\return returns the double value
	*/
	virtual double getTextHeight(TdkAbstractCanvasDraw *canvas, const std::string &text);

	//! \brief calculateHrzAlignment
	/*! Method to calculate the horizontal alignment
		\param	x	new position (returns by reference)
		\param canvas canvas pointer
		\param	text used to calculate the alignment
		\return returns true whether sucess to calculate the new position on horizontal axle
	*/
	virtual bool calculateHrzAlignment(double &x,TdkAbstractCanvasDraw *canvas,const std::string &text);

public:

		//!	\brief Constructor
		/*! Constructor with unique id, canvas pointer and bounding box
			to creation
			\param		id			unique id
			\param		canvas		abstract canvas pointer
			\param		box			initial bounding box
			\param		textValue	string value
		*/
		TdkLayoutMTextObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas, const TeBox &box,const std::string textValue="");

		//! \brief Destructor
		virtual ~TdkLayoutMTextObject();

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

