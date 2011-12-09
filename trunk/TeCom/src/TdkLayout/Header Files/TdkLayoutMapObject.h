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
* $Date: 2011/11/30 13:37:49 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório


#ifndef __TDK_LAYOUT_MAP_OBJECT_H
#define __TDK_LAYOUT_MAP_OBJECT_H


#include <TdkLayoutObject.h>

class TdkAbstractCanvasDraw;
class TeDatabase;
class TeView;
class TdkAbstractLayoutEvents;
class TdkAbstractCursor;
class TeProjection;
class TdkMapScaleProperty;
class TdkMapFixedScaleProperty;
class TdkDatabaseConnectionProperty;
class TdkViewNameProperty;
class TdkViewUserProperty;
class TdkMapWorld_x1_Property;
class TdkMapWorld_x2_Property;
class TdkMapWorld_y1_Property;
class TdkMapWorld_y2_Property;
class TdkSelectedThemeProperty;
class TdkSelectedFeaturesProperty;
class TdkSelectionColorProperty;
class TdkSelectionTransparencyProperty;

#define __mapTYPE			"__mapTYPE"
#define __initialPixmap		4096

//! \class TdkLayoutMapObject
/*! Class to create a new map object
	for terralib database
*/
class TdkLayoutMapObject : public TdkLayoutObject
{
protected:

	TeView*								_view;					//!< TeView pointer
	TeBox								_window;				//!< window box
	TeBox								_fixedBox;				//!< box fixed to draw the map in specific position on proprietary pixmap
	TeDatabase*							_database;				//!< Terra Lib database
	unsigned int						_mapPixmap;				//!< pixmap number used by object to draw the map
	TdkAbstractLayoutEvents				*_events;				//!< abstract events used to dispatch information to user
	TdkAbstractCursor					*_cursor;				//!< cursor pointer used to change the cursor icon
	TdkMapScaleProperty					*_mapScale;				//!< map scale
	TdkMapFixedScaleProperty			*_fixedScale;			//!< fixed scale value
	TdkSelectedThemeProperty			*_selectedTheme;		//!< Selected theme to draw selected features when necessary
	TdkSelectedFeaturesProperty			*_selectedFeatures;		//!< Selected features to draw in special mode
	TdkSelectionColorProperty			*_selectionColor;		//!< Color used to select the features
	TdkSelectionTransparencyProperty	*_transparencyColor;	//!< Sets the transparency color for selection operation
	TdkDatabaseConnectionProperty		*_connection;
	TdkViewNameProperty					*_viewName;
	TdkViewUserProperty					*_viewUser;
	TdkMapWorld_x1_Property				*_wx1;
	TdkMapWorld_y1_Property				*_wy1;
	TdkMapWorld_x2_Property				*_wx2;
	TdkMapWorld_y2_Property				*_wy2;
	TeCoord2D							_coordClick;	//!< coordinate of click
	MapMode								_mapMode;		//!< Map mode (Pan, zoom in, zoom out)
	bool								*_stop;			//!< Stop process pointer
	std::string							_lastVieName;
	std::string							_lastViewUser;
	bool								_internalDatabase;


protected:

	//! \brief loadView
	/*! Method to load view acoording of view name 
		and user name, whether unsucess returns NULL
		\param	db				database pointer
		\param	viewName		view name to load
		\param	userName		user name to view
		\return returns the view pointer whether sucess, otherwise returns NULL
		*/
	virtual TeView *loadView(TeDatabase *db, const std::string viewName, const std::string &userName);

	//! \brief getMapViewport
	/*! Returns the viewport box according client area
		\param	canvas		canvas pointer
		\return	return a new box
	*/
	virtual TeBox	getMapViewport(TdkAbstractCanvasDraw * canvas);

	//! \brief registerExtendProperties
	/*! Method to register your extend properties
	*/
	virtual void registerExtendProperties();

	//! \brief getValidBox
	/*! Method to return the valid box according
		the terralib view
		\param	view		a terralib view
		\return	returns a valid box
	*/
	virtual TeBox getValidBox(TeView *view);

	
	//! \brief getScale
	/*! Method to return the current scale
		of map object
		\param	proj			terralib projection
		\return	returns the scale
	*/
	virtual double getScale(TeProjection *proj);

	//! \brief recomputeBox
	/*! Method to recompute the correct box
		\param	scale				scale used to recompute the box
		\param	usedProjection		terralib projection used to recompute box
	*/
	virtual void recomputeBox(const double &scale, TeProjection* usedProjection);

	//! \brief drawMapTranslate
	/*! Method to draw the map translate process when
		use move the object with mouse
		\param coord		coordinate to translate
	*/
	virtual void drawMapTranslate(const TeCoord2D &coord);

	//! \brief recomputeTranslate
	/*! Method to compute the translate process
		\param	coord		end coordinate
	*/
	virtual void recomputeTranslate(const TeCoord2D &coord);

	//! \brief zoomIn
	/*! Method to execute the zoom in operation
		with map object
		\param		coord		click coordinate to zoom
		\param		factor		zoom factor
	*/
	virtual void zoomIn(const TeCoord2D &coord, const double &factor=0.5);

	//! \brief zoomOut
	/*! Method to execute the zoom out operation
		with map object
		\param		coord		click coordinate to zoom
		\param		factor		zoom factor
	*/
	virtual void zoomOut(const TeCoord2D &coord, const double &factor=0.5);

	//! \brief drawErrorLine
	/*! Method to draw a error line
		when there not a current view
	*/
	virtual void drawErrorLine();

	virtual void restartConnection();

	virtual std::string getViewName(TeDatabase *db, const std::string &user);

public :
		//! \brief Constructor
		/*! Constructor Method
			\param		id				unique identify
			\param		canvas			canvas pointer
			\param		box				bounding box
			\param		viewName		view name to load
			\param		userName		user name of view
			\param		db				Database pointer
		*/
		TdkLayoutMapObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box, \
			const TeBox &window, const std::string &viewName, const std::string &userName, TeDatabase *db, bool *stop=NULL);

		//! \brief Destructor
		~TdkLayoutMapObject();

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

		//!	\brief setEvent
		/*! Method to associate the system events to
			map object
			\param	ev		abstract event
		*/
		virtual void setEvent(TdkAbstractLayoutEvents* ev);

		//! \brief setCursor
		/*! Method to associate the mouse cursor with
			map object
			\param	cursor		abstract cursor
		*/
		virtual void setCursor(TdkAbstractCursor * cursor);

		//! \brief MouseMove
		/*! Not used yet
		*/
		virtual void mouseMove(TdkMouseEvent *e);

		//! \brief mouseDown
		/*! Not used yet
		*/	
		virtual void mouseDown(TdkMouseEvent *e);

		//! \brief mouseUp
		/*! Not used yet
		*/
		virtual void mouseUp(TdkMouseEvent *e);

		//! \brief setMapMode
		/*! Set Map Object to specific mode
			\param		mode		map mode
		*/
		virtual void setMapMode(const MapMode &mode);

};


#endif
