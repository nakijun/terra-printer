/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkGraphicViewService.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2011/12/01 18:00:01 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório


#ifndef __TDK_GRAPHIC_VIEW_SERVICE_H
#define __TDK_GRAPHIC_VIEW_SERVICE_H

#include <tedatatypes.h>
#include <TeRasterParams.h>
#include <TeRasterRemap.h>

class TeAbstractTheme;
class TeTheme;
class TdkAbstractCanvasDraw;
class TeView;
class TeProjection;
class TdkAbstractEvents;
class TeRaster;
class TeRasterTransform;


#define ImageLimit	5500
#define SliceValue	1000
#define InvalidLegend -500

//! \class TdkGraphicViewService
/*! Class to draw geographics datas
	from a terralib database to view port
*/
class TdkGraphicViewService 
{
protected:
	TdkAbstractEvents*		_events;				//!<	abstract events of system

	TeRasterParams			_rasterParams;			//!< Raster parameters.
	TeRaster*				_backRaster;            //!< Raster

	bool*					_stopProcess;
	int						_lastLegend;
protected:

	//! \brief setVisual
	/*! Method to set the visual style according the terralib theme
		\param		theme		terralib theme
		\param		canvas		canvas pointer
		\param		rep			terrralib representation
	*/
	virtual void setVisual(TeTheme *theme, TdkAbstractCanvasDraw *canvas, const TeGeomRep &rep, TeVisual *vis=NULL);


	//! \brief setVisualForSelection
	/*! Method to set the visual style to selection
		\param		theme		terralib theme
		\param		canvas		canvas pointer
		\param		rep			terrralib representation
	*/
	virtual void setVisualForSelection(TeTheme *theme, TdkAbstractCanvasDraw *canvas, const TeGeomRep &rep,TeVisual *vis);

	//! \brief setCollectionVisual
	/*! Method to set the visual style according the terraView Collection
		\param		theme		terralib theme
		\param		canvas		canvas pointer
		\param		rep			terrralib representation
		\param		legend_id	Identify of collection to restore the visual
		\param		portal		terralib database portal
	*/
	virtual void setCollectionVisual(TeTheme *theme, TdkAbstractCanvasDraw *canvas, const TeGeomRep &rep, const int &legend_id);

	//! \brief validScale
	/*! Method to check if a theme's scale is valid to draw
		\param	viewProj		view projection
		\param	theme			terralib theme
		\param	canvas			canvas pointer
	*/
	virtual bool validScale(TeProjection *viewProj, TeAbstractTheme* theme, TdkAbstractCanvasDraw *canvas, const double &mapScale=0.0);

	//! \brief drawThemeRasters
	/*! Method to draw a theme raster
		\param		theme		abstract terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\return returns true whether sucess to draw the raster
	*/
	virtual bool drawThemeRasters(TeAbstractTheme* theme,TeProjection *outProj, TdkAbstractCanvasDraw* canvas);

	//! \brief drawThemeRasters
	/*! Method to draw a theme raster
		\param		theme		terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\return returns true whether sucess to draw the raster
	*/
	virtual bool drawThemeRasters(TeTheme* theme,TeProjection *outProj, TdkAbstractCanvasDraw* canvas);

	//! \brief drawThemePolygons
	/*! Method to draw a theme with polygons vector
		\param		theme		abstract terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\return returns true whether sucess to draw the  theme's polygon
	*/
	virtual bool drawThemePolygons(TeAbstractTheme* theme,TeProjection *outProj, TdkAbstractCanvasDraw* canvas);

	//! \brief drawThemePolygonsWithCollection
	/*! Method to draw a theme with polygons vector and TerraView Collection
		\param		theme		abstract terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\return returns true whether sucess to draw the  theme's polygon
	*/
	virtual bool drawThemePolygonsWithCollection(TeTheme* theme,TeProjection *outProj, TdkAbstractCanvasDraw* canvas);

	//! \brief drawThemePolygons
	/*! Method to draw a theme with polygons vector
		\param		theme		terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\return returns true whether sucess to draw the  theme's polygon
	*/
	virtual bool drawThemePolygons(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas);


	//! \brief drawThemePolygonsForSelectOperation
	/*! Method to draw a theme with polygons vector according to selected features
		\param		theme		terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\param		visual		terralib visual pointer
		\param		feature		selected features to highlight
		\return returns true whether sucess to draw the  theme's polygon
	*/
	virtual bool drawThemePolygonsForSelectOperation(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas, TeVisual *visual, const std::vector<std::string> &feature);

	//! \brief drawThemeLines
	/*! Method to draw the theme with lines vector
		\param		theme		abstract terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\return returns true whether sucess to draw the  theme's polygon
	*/
	virtual bool drawThemeLines(TeAbstractTheme* theme,TeProjection *outProj, TdkAbstractCanvasDraw* canvas);

	//! \brief drawThemeLines
	/*! Method to draw the theme with lines vector
		\param		theme		terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\return returns true whether sucess to draw the  theme's line
	*/
	virtual bool drawThemeLines(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas);

	//! \brief drawThemeLinesForSelectOperation
	/*! Method to draw the selected lines
		\param		theme		terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\param		visual		visual for selected lines
		\param		feature		features list
		\return returns true whether sucess to draw the  theme's line
	*/
	virtual bool drawThemeLinesForSelectOperation(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas,TeVisual *visual, const std::vector<std::string> &feature);

	//! \brief drawThemeTexts
	/*! Method to draw the theme with texts vector
		\param		theme		abstract terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\return returns true whether sucess to draw the  theme's text
	*/
	virtual bool drawThemeTexts(TeAbstractTheme* theme,TeProjection *outProj, TdkAbstractCanvasDraw* canvas);


	//! \brief drawThemeTexts
	/*! Method to draw the theme with texts vector
		\param		theme		terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\return returns true whether sucess to draw the  theme's text
	*/	
	virtual bool drawThemeTexts(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas);

	//! \brief drawThemePoints
	/*! Method to draw the theme with points vector
		\param		theme		abstract terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\return returns true whether sucess to draw the  theme's point
	*/
	virtual bool drawThemePoints(TeAbstractTheme* theme,TeProjection *outProj, TdkAbstractCanvasDraw* canvas);

	//! \brief drawThemePoints
	/*! Method to draw the theme with points vector
		\param		theme		concret terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\return returns true whether sucess to draw the  theme's point
	*/
	virtual bool drawThemePoints(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas);


	//! \brief drawThemePointsForSelectOperation
	/*! Method to draw the selected points
		\param		theme		concret terralib theme
		\param		outProj		output projection
		\param		canvas		canvas pointer
		\param		visual		visual for selected features
		\param		feature		selected features
		\return returns true whether sucess to draw the  theme's point
	*/
	virtual bool drawThemePointsForSelectOperation(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas,TeVisual *visual, const std::vector<std::string> &feature);


	//! \brief buildRaster
	/*! Create a new raster pointer in memory
		\param	canvas		canvas pointer
		\return	returns true whether sucess
	*/
	virtual bool buildRaster(TdkAbstractCanvasDraw* canvas);

	//! \brief fillDecoder
	/*! Method to fill a terralib decoder
		\param	canvas		canvas pointer
		\param	raster		terralib raster pointer
		\param	trans		terralib raster transform
	*/
	virtual void fillDecoder(TdkAbstractCanvasDraw* canvas, TeRaster* raster, TeRasterTransform* transf );

	//! \brief processBlocks
	/*! Method to process the select block
		\param	raster					terralib raster pointer
		\param	parBlock				terralib raster params
		\param	remap					terralib raster remap
		\param	bboxIntersection		box intersection
		\param	res						image resolution
	*/
	virtual void processBlocks(TeRaster* raster, const TeRasterParams& parBlock,TeRasterRemap& remap, TeBox& bboxIntersection,
                                const int& res);

	//! \brief drawRasterSlice
	/*! Method to draw a raster to printer in slices
		\param	canvas			canvas pointer
		\param	raster			terralib raster
		\param	transform		terralib raster transform
		\param	angle			raster angle
		\param	rotatePoint		point of rotate
	*/
	virtual void drawRasterSlice(TdkAbstractCanvasDraw* canvas, TeRaster* raster, 
                                            TeRasterTransform* transform, const double& angle, 
											const TeCoord2D& rotatePoint);
	//! \brief resetBackRaster
	virtual void resetBackRaster();

	//! \brief setWorldRasterParams
	virtual void setWorldRasterParams(TeProjection* proj, TdkAbstractCanvasDraw* canvas);

	//! \brief drawSelectedFeaturesFromTheme
	/*!Method to draw the selected features from theme
		\param		theme		terralib theme pointer
		\param		proj		terralib projection pointer
		\param		canvas		abstract canvas
		\param		visual		terralib visual
		\param		features	selected features
		\retur		It returns true if sucess
	*/
	virtual bool drawSelectedFeaturesFromTheme(TeTheme *theme, TeProjection *outProj, TdkAbstractCanvasDraw *canvas, TeVisual *visual, const std::vector<std::string> &features);

	
public:

	//! \brief Constructor
	/*!
		\param		ev			abstract event from system to associate with servicer object
	*/
	TdkGraphicViewService(TdkAbstractEvents *ev=0, bool *stop=0);

	//! \brief Desctructor
	~TdkGraphicViewService();

	//! \brief drawView
	/*! Method to draw a specific view
		\param		view		terralib view to draw
		\param		canvas		canvas pointer
		\return		returns true whether sucess
	*/
	bool drawView(TeView *view, TdkAbstractCanvasDraw* canvas, const double &mapScale=0.0);

	//! \brief drawTheme
	/*! Method to draw a specific theme
		\param		theme		terralib theme to draw
		\param		outProj		projection to draw ( used to remap when necessary )
		\param		canvas		canvas pointer
		\return		returns true whether sucess
	*/
	bool drawTheme(TeAbstractTheme* theme,TeProjection *outProj, TdkAbstractCanvasDraw* canvas);

	//! \brief drawSelectedFeatures
	/*! Method to draw the selected features
		\param	view		TerraLib view
		\param	theme		TerraLib theme
		\param	visual		TerraLib visual
		\param	canvas		Canvas pointer to draw
		\param	mapScale	map scale, this attribute is used to decide if draw or not the features according to scale
		\param	features	features to draw
	*/
	bool drawSelectedFeatures(TeView *view,TeTheme *theme, TeVisual *visual, TdkAbstractCanvasDraw *canvas,const double &mapScale,const std::vector<std::string> &features );

};



#endif

