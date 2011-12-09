/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutRuler.h
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


#ifndef __TDK_LAYOUT_RULER_H
#define __TDK_LAYOUT_RULER_H

class TdkAbstractCanvasDraw;
class TdkPageSize;



class TdkLayoutRuler
{
protected:
	TdkAbstractCanvasDraw*	_canvas;		//!< canvas pointer
	TdkPageSize*			_pageSize;		//!< page size pointer
	bool					_bShowRuler;	//!< show ruler flag
	
protected:

	//! \brief drawVerticalRuler
	/*! Method to draw vertical ruler without tickets and text
	*/
	virtual void drawVerticalRuler();

	//! \brief drawHorizontalRuler
	/*! Method to draw horizontal ruler without tickets and text
	*/
	virtual void drawHorizontalRuler();

	//! \brief drawExternBorder
	/*! Method to draw extern border to do 3D appear
	*/
	virtual void drawExternBorder();

	//! \brief drawHorizontalClientArea
	/*! Method to draw the blank horizontal area
	*/
	virtual void drawHorizontalClientArea();

	//! \brief drawVerticalClientArea
	/*! Method to draw the blank vertical area
	*/
	virtual void drawVerticalClientArea();

	//! \brief drawHorizontalText
	/*! Method to draw the horizontal text
		for ruler
	*/
	virtual void drawHorizontalText();

	//! \brief drawVerticalText
	/*! Method to draw the vertical text
		for ruler
	*/
	virtual void drawVerticalText();

	//! \brief getFactor
	/*! Method to return the visualization factor
	*/
	virtual int getFactor();
public:
	//! \brief Constructor
	TdkLayoutRuler(TdkAbstractCanvasDraw* canvas,TdkPageSize* pageSize);

	//! \brief Destructor
	virtual ~TdkLayoutRuler();

	//! \brief Update
	/*! Method to udpate the ruler visualization
	*/
	virtual void update();

	//! \brief setVisible
	/*! Method to set visible status
		\param	status		boolean value to define whether ruler is visible
	*/
	virtual void setVisible(const bool &status=true);
};



#endif

