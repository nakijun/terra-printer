/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkPageSize.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/07/17 11:09:54 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório



#ifndef __TDK_PAGE_SIZE_H
#define __TDK_PAGE_SIZE_H

#include <map>
#include "TdkLayoutTypes.h"


using namespace std;

//! \class TdkPageSize
/*! Class to manipulate page size
*/
class TdkPageSize
{
public:

//! \struct Dimension Struct
typedef struct Dimension
{
	double width;		//!< width value
	double height;		//!< height value
}dimension;


//!< mapDimension
typedef map<pageSize,dimension> mapDimension;

protected:

	pageSize						_pageSize;			//!< page size 
	pageOrientation					_pageOrientation;	//!< page orientation
	mapDimension					_sizeValue;			//!< page dimension (always in portrait option)
	
public:
		//! \brief Constructor
		TdkPageSize();

		//! \brief Destructor
		virtual ~TdkPageSize();

		//! \brief setOrientation
		/*! Method to define the page orientation
			\param	orientation			orientation option (portrait or landscape)
		*/
		virtual void setOrientation(const pageOrientation &orientation);

		//! \brief getOrientation
		/*! Method to return the page orientation
			\return		returns the orientation page
		*/
		virtual pageOrientation getOrientation();

		//! \brief setSize
		/*! Method to define the page size (A0,A1,A2...)
			\param	size	size type
		*/
		virtual void setSize(const pageSize &size);

		//! \brief getSize
		/*! Method to return the page size (A0,A1,A2...)
			\return returns the page size type
		*/
		virtual pageSize getSize();

		//! \brief setCustomSize
		/*! Method to define the custo size to page
			When this method is executed the pageSize is toggled to Custom
			\param	width		width value
			\param	height		height value
		*/
		virtual void setCustomSize(const double &width, const double &height);

		//! \brief getWidth
		/*! Method to return the width value according page size
			Example to A4 pageSize with portrait orientation the value to
			return is 210, case A4 with landscape this value is 297
			\return returns the width value
		*/
		virtual double getWidth();

		//! \brief getHeight
		/*! Method to return the height value according page size
			Example to A4 page size with portrait orientation the value to
			return is 297, case A4 with landscape this value is 210
			\return returns the height value
		*/
		virtual double getHeight();

		//! \brief getCenterWidth
		/*!
			Method to return the center x
			\return	returns the center on axle x
		*/
		virtual double getCenterWidth();

		//! \brief getCenterHeight
		/*! Method to return the center y
			\return returns the center on axle y
		*/
		virtual double getCenterHeight();

};



#endif
