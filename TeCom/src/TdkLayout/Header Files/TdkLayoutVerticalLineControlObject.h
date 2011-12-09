/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutVerticalLineControlObject.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/09/17 17:24:38 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_LAYOUT_VERTICAL_LINE_CONTROL_OBJECT_H
#define __TDK_LAYOUT_VERTICAL_LINE_CONTROL_OBJECT_H

class TdkAbstractCursor;



//! \class TdkLayoutVerticalLineControlObject
/*! Control line used to auxiliary user
*/
class TdkLayoutVerticalLineControlObject : public TdkLayoutObject
{
protected:
		TdkAbstractCursor *					_cursor;		//!< cursor pointer used to change the cursor icon
public:
		//! brief Constructor
		TdkLayoutVerticalLineControlObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box);

		//! \brief Destructor
		~TdkLayoutVerticalLineControlObject();

		//! \brief Draw
		virtual void draw();

		//! \brief Print
		virtual void print(TdkAbstractCanvasDraw *canvas);

		//! \brief registerExtendProperties
		virtual void registerExtendProperties();

		//! \brief drawTranslateProcess
		/*! Method to draw translate process
			\param	dx		x displacement 
			\param	dy		y displacement
		*/
		virtual void drawTranslateProcess(const double &dx, const double &dy);

		//! \brief drawSelectionBoundingBox
		/*! Method to draw selection
		*/
		virtual void drawSelection(const TdkAbstractCanvasDraw::TdkCanvasBuffer &buffer);

		//! \brief mouseMove Event
		virtual void mouseMove(TdkMouseEvent *e);

		//! \brief setCursor
		virtual void setCursor(TdkAbstractCursor *cursor);
};

#endif


