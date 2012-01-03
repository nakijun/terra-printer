/******************************************************************************
* FUNCATE - GIS development team
* 
* Tdk Framework
* 
* @(#) TdkGeomTransformationUtils.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/07/17 11:09:56 $:
******************************************************************************/

#ifndef TDK_GEOMTRANSFORMATION_UTILS_H
#define TDK_GEOMTRANSFORMATION_UTILS_H

/*
** ---------------------------------------------------------------
** Includes:
*/

//TDK include files
#include <Tdk.h>

/*
** ---------------------------------------------------------------
** Definitions:
*/
class TePolygon;
class TeLine2D;
class TeCoord2D;
class TeProjection;
struct TeBox;

//foward declarations

  /*! 
   * 
   * \file TdkGeomTransformationUtils.h
   *
   * \brief Functions related to TerraLib geometries, that can be used by all tdk modules
   *
   * \author Frederico Augusto Bedê <frederico.bede@funcate.org.br>
   * \version 1.0
   *
   * \addtogroup utils
   *
   * \todo
   *  @{
   */

/*! \brief Rotate Coordinate
	Method to rotate a coordinate using a control point.
	Note the angle is Degree! The function convert to radius internally
	\param		coordControl			coordinate used as control
	\param		coordToRotate			coordinate that 'll be rotate
	\param		angle					rotation angle
	\param		coordOut				coordinate rotated
*/
TDK_API void TdkRotate(const TeCoord2D &coordControl, const TeCoord2D &coordToRotate, const double &angle, TeCoord2D &coordOut);

/*! \brief Rotate Line
	Method to rotate each coordinate of line.
	The Angle should in decimal degree.
	\param		lneInOut		line to rotate
	\param		coordControl	coordinate used such control point
	\param		angle			angle value in decimal degree
*/
TDK_API void TdkRotate(TeLine2D& lneInOut, const TeCoord2D &coordControl,const double& angle);


/*! \brief Rotate Polygon
	Method to rotate each line that composite the polygon
	The Angle should in decimal degree.
	\param		polInOut		polygon to to rotate
	\param		coordControl	coordinate used such control point
	\param		angle			angle value in decimal degree
*/
TDK_API void TdkRotate(TePolygon& polInOut, const TeCoord2D &coordControl, const double& angle);


/*!	\brief Adjust Coordinate
	This function adjust the size between two segments
	\param		P0						first coordinate
	\param		P1						seconde coordinate
	\param		distance				new distance between coordinates
	\param		P0out					first coordinate adjusted, equal the original ( ouput param )
	\param		P1out					second coordinate adjusted, this coordinate can was modified ( ouput param )
*/
TDK_API void TdkAdjustCoordinate(const TeCoord2D &P0, const TeCoord2D &P1,const double &distance, TeCoord2D &P0out, TeCoord2D &P1out);

/**	\brief Given some attributes, recalculates box. This method is called on change canvas scale.
  *	This function adjust the size between two segments
  *	\param		box						Box to recalculate (Output)
  *	\param		wMM						Canvas width in millimeters. (Input)
  *	\param		usedProjection			Box's projection. (Input)
  *	\param		newScale				The new canvas scale. (Input)
  *	\param		scaleApx				The older canvas scale. (Input)
  */
TDK_API void TdkRecalculateBox(TeBox& box, const double& wMM, TeProjection* usedProjection, 
                       const double& newScale, const double& scaleApx);

/** \brief Translate Coord
	\param	crdInput	coord to translate
	\param	dx			displacement on axle x
	\param	dy			displacmente on axle y
	\return	returns a coord 2D translated
*/
TDK_API TeCoord2D TdkTranslate(const TeCoord2D& crdInput, const double &dx, const double &dy);

/** \brief Translate Line
	\param	lneInput	line to translate
	\param	dx			displacement on axle x
	\param	dy			displacmente on axle y
	\return	returns a line 2D translated
*/
TDK_API TeLine2D TdkTranslate(const TeLine2D& lneInput, const double &dx, const double &dy);

/** \brief Translate Polygon	
	\param	polInput	polygon to translate
	\param	dx			displacement on axle x
	\param	dy			displacmente on axle y
	\return	returns a polygon translated
*/
TDK_API TePolygon TdkTranslate(const TePolygon& polInput, const double &dx, const double &dy);


/** \brief Calculates the angle between two coordinates
	\param	coord1		first coordinate
	\param	coord2		second coordinate
	\return	returns the double value in decimal degree
*/
TDK_API double TdkAngle(const TeCoord2D &coord1, const TeCoord2D &coord2);
//@}

#endif // TDK_GEOMTRANSFORMATION_UTILS_H

/*
** ---------------------------------------------------------------
** End:
*/
