/******************************************************************************
* FUNCATE - GIS development team
* 
* Tdk Framework
* 
* @(#) TdkProjectionUtils.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/07/17 11:09:56 $:
******************************************************************************/
#ifndef TDK_PROJECTION_UTILS_H
#define TDK_PROJECTION_UTILS_H

/*
** ---------------------------------------------------------------
** Includes:
*/

//TDK include files
#include <tdk.h>

//STL include files
#include <string>

/*
** ---------------------------------------------------------------
** Definitions:
*/
//foward declarations
class TeProjection;
class TeDatabase;
class TeLayer;
class TeView;
class TeViewNode;
class TePolygon;
class TePolygonSet;
class TeLine2D;
class TeLineSet;
class TeCoord2D;
class TePoint;
class TePointSet;
struct TeBox;

  /*! 
   * 
   * \file TdkProjectionUtils.h
   *
   * \brief Functions related to objects projection, that can be used by all tdk modules
   *
   * \author Frederico Augusto Bedê <frederico.bede@funcate.org.br>
   * \version 1.0
   *
   * \addtogroup utils
   *
   * \todo
   * 1)comment function tetrahedronBBox()
   *  @{
   */

/** \brief 
    \param pt0
    \param pt1
    \param pt2
    \param pt3
    \return Box
  */
TDK_API TeBox tetrahedronBBox(const TeCoord2D& pt0, const TeCoord2D& pt1, const TeCoord2D& pt2, 
                                  const TeCoord2D& pt3);

/** \brief Changes the TeBox projection.
    \param fromProj Source projection.
    \param toProj Destination projection.
    \param box Box to be reprojected.
  */
TDK_API void changeProjection(TeProjection* fromProj, TeProjection* toProj, TeBox& box);
 
/** \brief Changes the TeCoord2D projection.
    \param fromProj Source projection.
    \param toProj Destination projection.
    \param coord Coordinate to be reprojected.
  */
TDK_API void changeProjection(TeProjection* fromProj, TeProjection* toProj, TeCoord2D& coord);

/** \brief Changes the TePoint projection.
    \param fromProj Source projection.
    \param toProj Destination projection.
    \param point TePoint to be reprojected.
  */
TDK_API void changeProjection(TeProjection* fromProj, TeProjection* toProj, TePoint& point);

/** \brief Changes the projection of a set of points.
    \param fromProj Source projection.
    \param toProj Destination projection.
    \param pointSet A set of points to be reprojected.
  */
TDK_API void changeProjection(TeProjection* fromProj, TeProjection* toProj, TePointSet& pointSet);

/** \brief Changes the TeLine2D projection.
    \param fromProj Source projection.
    \param toProj Destination projection.
    \param line Line to be reprojected.
  */
TDK_API void changeProjection(TeProjection* fromProj, TeProjection* toProj, TeLine2D& line);

/** \brief Changes the projection of a set of lines.
    \param fromProj Source projection.
    \param toProj Destination projection.
    \param lineSet A set of lines to be reprojected.
  */
TDK_API void changeProjection(TeProjection* fromProj, TeProjection* toProj, TeLineSet& lineSet);

/** \brief Changes the TePolygon projection.
    \param fromProj Source projection.
    \param toProj Destination projection.
    \param poly Polygon to be reprojected.
  */
TDK_API void changeProjection(TeProjection* fromProj, TeProjection* toProj, TePolygon& poly);

/** \brief Changes the projection of a set of polygons.
    \param fromProj Source projection.
    \param toProj Destination projection.
    \param polygonSet A set of polygons to be reprojected.
  */
TDK_API void changeProjection(TeProjection* fromProj, TeProjection* toProj, TePolygonSet& polygonSet);

/** \brief Changes the projection of a Layer.
    \param fromProj Source projection.
    \param toProj Destination projection.
    \param layer a to be reprojected.
  */
TDK_API void changeLayerProjection(TeLayer& layer, TeProjection* toProj);

/** \brief Changes the view projection and updates that in the database.
  * \param view TeView to change projection.
  * \param newProjection New view projection.
  * \param db Database driver being used.
  */
TDK_API void changeViewProjection(TeView* view, TeProjection* newProjection, TeDatabase* db);

/**	@brief
 *	@param node
 *	@return
 */
TDK_API TeProjection* findProjection(TeViewNode* node);

TDK_API bool isProjectionsCompatible(TeProjection* viewProj, TeProjection* layerProj, 
									 std::string& errorMsg);

TDK_API void DD2DMS(const double& decimalDegrees, int& degrees, int& minutes, double& seconds);

TDK_API double DMS2DD(const int& degrees, const int& minutes, const double& seconds);

TDK_API std::string DD2DMSLabel(const double& decimalDegrees);

TDK_API std::string DMSLabel(const int& degrees, const int& minutes, const double& seconds);
//@}

#endif //TDK_PROJECTION_UTILS_H
