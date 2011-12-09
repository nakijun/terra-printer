/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkPage.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/08/13 13:31:59 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório


#ifndef __TDK_PAGE_H
#define __TDK_PAGE_H

class TdkAbstractCanvasDraw;
class TdkPageSize;

//! \class TdkPage
/*! Class to manipulate the Page
*/
class TdkPage
{
protected:
	TdkAbstractCanvasDraw*	_canvas;		//!< canvas pointer
	TdkPageSize*			_pageSize;		//!< page size pointer

	double					_leftMargin;
	double					_topMargin;
	double					_rightMargin;
	double					_bottomMargin;
	double					_minimumHrzMargin;
	double					_minimumVrtMargin;
protected:

	//! \brief drawPageShadow
	/*! Method to draw shadow
	*/
	virtual void drawPageShadow();
	
	//! \brief drawPage
	/*! Method to draw Page area
		(white page)
	*/
	virtual void drawPage();

	//! \brief 	clearClientArea
	/*! Method to clear client area
	*/
	virtual void clearClientArea();

	virtual void drawMargin();
public:

	//! \brief Constructor
	/*! Constructor with canvas and page size pointer
		\param		canvas		abstract canvas pointer
		\param		pageSize	pageSize pointer
	*/
	TdkPage(TdkAbstractCanvasDraw* canvas,TdkPageSize* pageSize);

	//! \brief Destructor
	virtual ~TdkPage();

	//! \brief Update
	/*! Method to udpate the page visualization
	*/
	virtual void update();

	//! \brief setMarginMinimum
	/*! Method to set the minimum margin
		of page according the printer limit
	*/
	virtual void setMarginMinimum(const double &horz, const double &vert);

	//! \brief setMargin
	/*! Set the Margin page
		\param	left		left margin
		\param	top			top margin
		\param	right		right margin
		\param	bottom		bottom margin
	*/
	virtual void setMargin(const double &left, const double &top, const double &right, const double &bottom);

	//! \brief getMargin
	/*! Returns the Margin page
		\param	left		left margin
		\param	top			top margin
		\param	right		right margin
		\param	bottom		bottom margin
	*/
	virtual void getMargin(double &left, double &top, double &right, double &bottom);

};


#endif

