/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutController.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/09/17 16:46:19 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório



#ifndef __TDK_LAYOUT_CONTROLLER_H
#define __TDK_LAYOUT_CONTROLLER_H

#include <TeBox.h>



class TdkAbstractCanvasDraw;
class TdkPageSize;
class TdkLayoutRuler;
class TdkPage;
class TdkMouseEvent;
class TdkLayoutObjectList;
class TdkAbstractLayoutEvents;
class TdkAbstractCursor;
class TdkLayoutObject;
class TeDatabase;
class TdkAbstractProperty;
class TdkAbstractImage;
class TdkAbstractClipboard;


#define __ZOOM_EDGE		5

//! \class TdkLayoutController
/*! Class to control all interaction between 
	layout object and external events
*/
class TdkLayoutController
{
public :
	enum layoutKey
	{
		DEL	= 46
	};

	enum pageProcess
	{
		None,
		pageZoomOut,
		pageZoomArea,
		pagePan
	};
protected:
	TdkAbstractCanvasDraw*			_canvas;		//!< Abstract Canvas Pointer
	TdkPageSize*					_pageSize;		//!< pageSize pointer
	TdkLayoutRuler*					_ruler;			//!< ruler pointer
	TdkPage*						_page;			//!< page pointer
	TdkLayoutObjectList*			_objectList;	//!< pointer to object list
	TdkAbstractLayoutEvents*		_events;		//!< external events pointer
	double							_deltaZoom;		//!< zoom area delta
	TdkLayoutObject*				_newObject;		//!< new layout object to add the list
	TeDatabase*						_database;		//!< Terralib database
	TdkAbstractCursor *				_cursor;		//!< Abstract Cursor
	bool							_loked;			//!< loked flag to loke the mouse events
	bool							_stop;
	double							_zoomFactor;
	pageProcess						_process;
	TeCoord2D						_positionClicked;
	TeCoord2D						_positionClickedMM;
	TeCoord2D						_lastCoord;
	bool							_mouseDown;
	std::string						_fullPath;
	TdkAbstractImage				*_databaseLogo;
	TdkAbstractClipboard			*_clipboard;
	double							_pasteDisplacement;
protected:
	
	//! \brief Convert Viewport to Window
	/*! Method to convert viewport coordinates to window coordinate
		\param	x		coordinate on axle x
		\param	y		coordinate on axly y
	*/
	virtual void convertViewportToWindow(double& x, double &y);

	//! \brief Create Layout Object
	/*! Method to create a new layout object
		according the box create by user
	*/
	virtual void createLayoutObject();

	//! \brief pagePanProcess
	/*! Process the pan action
		\param		lastPos		last mouse position
		\param		newPos		new mouse position
	*/
	virtual void pagePanProcess(const TeCoord2D &lastPos, const TeCoord2D &newPos);

	//! \brief pageZoomAreaProcess
	/*! Process the zoom area action
		\param		firstPos	first mouse position
		\param		newPos		new mouse position
	*/
	virtual void pageZoomAreaProcess(const TeCoord2D &firstPos, const TeCoord2D &newPos);

	//! \brief pagePanEndProcess
	/*! Methodo finalize the pan process
		\param		init		initial position clicked for user
		\param		final		final position clicked for user
	*/
	virtual void pagePanEndProcess(const TeCoord2D &init, const TeCoord2D &final);

	//! \brief pageEndZoomArea
	/*! Methodo finalize the zoom area process
		\param		init		initial position clicked for user
		\param		final		final position clicked for user
	*/
	virtual void pageEndZoomArea(const TeCoord2D &firstPos, const TeCoord2D &newPos);

	//! \brief pageZoomOutProcess
	/*! Method to execute the zoom out process!
		This method adjust the center of client area
		to new position ( mouse click position )
		\param	e	Mouse click Position
	*/
	virtual void pageZoomOutProcess(TdkMouseEvent *e);

	
public:

	//! \brief Constructor
	/*! Constructor with canvas and events pointer parameter
		\param		canvas		abstract canvas pointer
		\param		e			abstract events
	*/
	TdkLayoutController(TdkAbstractCanvasDraw* canvas, TdkAbstractLayoutEvents *e=NULL);

	//! \brief Constructor
	/*! Cosntructor with abstract events pointer
		\param		e			abstract events pointer
		\param		cursor		abstract cursor
	*/
	TdkLayoutController(TdkAbstractLayoutEvents *e=NULL, TdkAbstractCursor *cursor=NULL);

	//! \brief Destructor
	virtual ~TdkLayoutController();

	//! \brief setCanvas
	/*! Set the canvas pointer to controller
		\param	canvas abstract canvas pointer
	*/
	virtual void setCanvas(TdkAbstractCanvasDraw* canvas);

	//! \brief getCanvas
	/*! Method to return the current canvas pointer
		\return	returns a canvas pointer or NULL
	*/
	virtual TdkAbstractCanvasDraw* getCanvas();

	//! \brief Update
	/*! Update layout component, redraw ruler, 
		page and all objects ( just update CacheBuffer )
	*/
	virtual void update();

	//! \brief Refresh
	/*! Copy backBuffer to front buffer
	*/
	virtual void refresh();

	//! \brief Update Page Size
	/*! Method is called when page size 
		is changed
	*/
	virtual void updatePageSize();

	//! \brief Recompose 
	/*!
		Page Size to extend area
	*/
	virtual void recompose();

	//! \brief setWorld
	/*! Method to set the world
		\param		x1		inital x coordinate
		\param		y1		inital y coordinate
		\param		x2		final x coordinate
		\param		y2		final y coordinate
		\param		canvas	canvas pointer
	*/
	virtual void setWorld(const double &x1, const double &y1, const double &x2, const double &y2, TdkAbstractCanvasDraw *canvas);

	//! \brief setPaperOrientation
	/*! Method to change page orientation
		\param	value		page orientation value (portrait or landscape)
	*/
	virtual void setPaperOrientation(const short &value);

	//! \brief getPaperOrientation
	/*! Method to return the current page orientation
		\param	returns the page orientation
	*/
	virtual short getPaperOrientation();

	//! \brief setPaperSize
	/*! Method to set the paper size
		\param		value		paper size value (A4,A3,A2....)
	*/
	virtual void setPaperSize(const short &value);

	//! \brief getPaperSize
	/*! Method to return the paper size
		\param	 returns the paper size
	*/
	virtual short getPaperSize();

	//! \brief getPaperSize
	/*! Method to return the paper size (width and height)
		\param	width			width value
		\param	height			height value
	*/
	virtual void getPaperSize(double &width, double &height);

	//! \brief setAlignment
	/*! Method to set the object alignment
		\param	value	align value
	*/
	virtual void setAlignment(const TdkAlignment &value);

	//! \brief print
	/*! Method to print layout page
		\param	canvas	printer canvas
	*/
	virtual void print(TdkAbstractCanvasDraw *canvas, const double &x=0, const double &y=0);

	//! \brief setDatabase
	/*! Method to sets the database pointer
		\param	db		terralib database pointer
	*/
	virtual void setDatabase(TeDatabase *db);

	//! \brief getObjectCount
	/*! Method to return the object count
		\return		returns the total of layout object
	*/
	virtual unsigned int getObjectCount();

	//! \brief getSelectObjectCount
	/*! Method to return the selects object count
		\return		returns the total of select layout object
	*/
	virtual unsigned int getSelectObjectCount();

	//! \brief getSelectObjectName
	/*! Method to return the select object name according
		the index
		\param	index		object index
		\return	returns the object name
	*/
	virtual std::string getSelectObjectName(const unsigned int &index);

	//! \brief getObjectName
	/*! Method to return the object name
		according the index value
	*/
	virtual std::string getObjectName(const unsigned int &index);

	//! \brief getPropertiesCount
	/*! Method to return the quantity of properties according to object name
		\param		objectName		object name
		\return		returns a unsigned int value
	*/
	virtual unsigned int getPropertiesCount(const std::string &objectName);

	//! \brief getPropertyName
	/*! Method to return the property name according object name and a index value
		\param		objectName		object name
		\param		index			index value (position) of property in list
		\return		return the property name
	*/
	virtual std::string getPropertyName(const std::string &objectName, const unsigned int &index);

	//! \brief TdkAbstractProperty
	/*! Method to return the property value
		by object name and your index
		\param		objectName			object Name
		\param		index				index of list
		\return		returns the abstract property
	*/
	virtual TdkAbstractProperty * getPropertyValue(const std::string &objectName, const unsigned int &index);

	//! \brief TdkAbstractProperty
	/*! Method to return the property value
		by object name and your property name
		\param		objectName			object Name
		\param		propertyName		property name
		\return		returns the abstract property
	*/
	virtual TdkAbstractProperty * getPropertyValue(const std::string &objectName, const std::string &propertyName);

	//! \brief associatePropertyObject
	/*! Method to associate the property with a layout object
		\param		objectName			object Name
		\param		propertyName		property name
	*/
	virtual void associatePropertyObject(TdkAbstractProperty *propertyObj, const std::string &objectName);

public :// events

	//! \brief resize
	/*! Resize Events, dispatch when 
		client area is changed
	*/
	virtual void resize();

	//! \brief mouseMove
	/*! Mouse move event dispatch when mouse cursor
		is moved over client area
		\param	e	mouse event parameter
	*/
	virtual void mouseMove(TdkMouseEvent *e);

	//! \brief mouseDown
	/*! Mouse down event dispatch when mouse cursor
		is clicked over client area
		\param	e		mouse event parameter
		\param	ctrl	boolean to control key press
	*/
	virtual void mouseDown(TdkMouseEvent *e,const bool &ctrl=false);

	//! \brief mouseUp
	/*! Mouse up event dispatch when mouse cursor
		is release from click on client area
		\param	e	mouse event parameter
		\param	bCtrl		Control boolean
	*/
	virtual void mouseUp(TdkMouseEvent *e,const bool &ctrl);

	//! \brief moveKey
	/*! Move object using accelerator keys
		\param	key		(left,right, up, down)
	*/
	virtual void moveKey(const moveKeys &key,const bool &ctrl=false);

	//! \brief keyUp
	/*! Key Up event
		\param	key				key up
		\param	control			key control
	*/
	virtual void keyUp(const long &key, const bool &control);

	//! \brief keyDown
	/*! Key Down event
		\param	key				key down
		\param	control			key control
	*/
	virtual void keyDown(const long &key, const bool &control);

	//! \brief zoom
	/*! Executes the zoom with delta value (Mouse Wheel)
		\param	delta value
	*/
	virtual void zoom(const int &delta);

public ://create objects

	//! \brief createText
	/*! Method to create a layout text object
		\param	box				box to creation
		\param	textValue		string text
	*/
	virtual void createText(const TeBox &box=TeBox(0,0,0,0),const std::string &textValue="");

	//! \brief createBarcode
	/*! Method to create the barcode object to layout
		\param	box				box to creation
		\param	textValue		string text
	*/
	void createBarcode(const TeBox &box,const std::string &textValue="0123456789");

	//! \brief createMText
	/*! Method to create a layout multi line text object
		\param	box				box to creation
		\param	textValue		string text
	*/
	virtual void createMText(const TeBox &box,const std::string &textValue);

	//! \brief createImage
	/*! Method to create a layout image object
		\param	box				box to creation
		\param	fileName		image file name
	*/
	virtual void createImage(const std::string &fileName,const TeBox &box=TeBox(0,0,0,0));

	//! \brief createMap
	/*! Method to create the map layout object
		\param	viewName		view name to load
		\param	userName		user name to specific the view
		\param	boxWindow		bounding box of world
		\param	box				bounding box of component
	*/
	virtual void createMap(const std::string &viewName, const std::string userName, const TeBox &boxWindow, const TeBox &box);

	//! \brief createPoliticalDivision
	/*! Method to create the political division object
		\param	box		bounding box
	*/
	virtual void createPoliticalDivision(const TeBox &box);

	//! \brief createRectangle
	/*! Method to create a rectangle object
		\param	box		initial bounding box
	*/
	virtual void createRectangle(const TeBox &box=TeBox(0,0,0,0));

	//! \brief createEllipse
	/*! Method to create a ellipse object
		\param	box		initial bounding box
	*/
	virtual void createEllipse(const TeBox &box=TeBox(0,0,0,0));

	//! \brief createLine
	/*! Method to create a line object
		\param	box		initial bounding box
	*/
	virtual void createLine(const TeBox &box=TeBox(0,0,0,0));

	//! \brief createDatabase
	/*! Method to create the database object
	*/
	virtual void createDatabase(const TeBox &box=TeBox(0,0,0,0));

	//! \brief createVLineControl
	/*! Method to create the vertical line
		control
	*/
	virtual void createVLineControl(const TeBox &box);

	//! \brief createHLineControl
	/*! Method to create the horizontal line
		control
	*/
	virtual void createHLineControl(const TeBox &box);

	//! \brief createScale
	/*! Method to create a scale object
		\param	box		initial bounding box
	*/
	virtual void createScale(const TeBox &box=TeBox(0,0,0,0));

	//! \brief createNorth
	/*! Method to create the north object
		\param	pathName		application path 
		\param	box				initial bounding box
	*/
	virtual void createNorth(const std::string &pathName,const TeBox &box=TeBox(0,0,0,0));

	//! \brief setMapMode
	/*! Sets the map mode
		\param	mode  - pan, zoom in, zoom out
	*/
	virtual void setMapMode(const MapMode &mode);

	//! \brief sendToBack
	/*! Send the select object to back
	*/
	virtual void sendToBack();

	//! \brief bringToFront
	/*! bring the select objects to
		front
	*/
	virtual void bringToFront();

	//! \brief setMarginMinimum
	/*! Sets the minimum margin supported by
		default printer
		\param		horz		left/right border
		\param		vert		top/bottom border
	*/
	virtual void setMarginMinimum(const double &horz, const double &vert);

	//! \brief Stop
	/*! Method to stop the current process
	*/
	virtual void Stop();

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

	//! \brief Select
	/*! Method to select the object by your name
		\param		objName		object name
		\return		returns true whether sucess
	*/
	virtual bool select(const std::string &objName);

	//! \brief setZoomFactor
	/*! Method to set the Zoom Factor
		\param	value		zoom value in percent
	*/
	virtual void setZoomFactor(const double &value);

	//! \brief getZoomFactor
	/*! Method to return the zoom factor
		\return	returns the zoom value in percent
	*/
	virtual double getZoomFactor();

	//! \brief getZoomFactor
	/*! Method to return the zoom factor
		\return	returns the zoom value in percent
	*/
	virtual double getZoomFactor(const TeBox &box);

	//! \brief hDisplacement
	/*! Sets the horizontal displacement
		\param	value		horizontal displacement in millimeter
	*/
	virtual void hDisplacement(const double &value);

	//! \brief vDisplacement
	/*! Sets the vertical displacement
		\param	value		vertical displacement in millimeter
	*/
	virtual void vDisplacement(const double &value);

	//! \brief getBoundingBox
	/*! Method to return the bounding box
		of client area
	*/
	virtual TeBox getBoundingBox();

	//! \brief getCenterViewPortWindow
	/*! Method to calculate the viewport center, after
		this it transform to millimeter
	*/
	virtual TeCoord2D getCenterViewPortWindow();

	//! \brief removeSelectedItems
	/*! Remove the selected layout objects
		from memory
	*/
	virtual void removeSelectedItems();

	//! \brief getObjectType
	/*! Method to return the object type
		according to object name
		\return		object type
	*/
	virtual objectType getObjectType(const std::string &name);

	//! \brief 	setLayoutMode
	/*! Method to sets the layout mode
		\param	mode layout mode
	*/
	virtual void setLayoutMode(const pageProcess &mode);

	//! \brief 	getPropertyType
	/*! Method to returns the property type
		\param	objName		object name
		\param	propName	property name
		\return	returns the property type
	*/
	virtual propertyType getPropertyType(const std::string &objName, const std::string &propName);

	//! \brief fullRedraw
	/*! Update all objects in list updating
		with your database when necessary
	*/
	virtual void fullRedraw();
	
	//! \brief save
	/*! Save the current layout settings
		and all objects.
	*/
	virtual bool save(const std::string &fileName);

	//! \brief open
	/*! Open a xml file with layout settings
		\param		fileName		file name
		\return		returns true whether sucess
	*/
	virtual bool open(const std::string &fileName);

	//! \brief	getList
	/*! Returns the all objects list
		adding to controller
	*/
	virtual TdkLayoutObjectList* getList();

	//! \brief newPage
	/*! Create a new empty page layout
	*/
	virtual void newPage();

	//! \brief createLayoutObject
	/*! Method to create a new layout object
		according type
		\param	type		object type
		\return	returns the object created
	*/
	virtual TdkLayoutObject* createLayoutObject(const short &type);

	//! \brief insertObjectToList
	/*! Insert a new layout object to control list
		\param	obj		new layout object
	*/
	virtual void insertObjectToList(TdkLayoutObject *obj, const bool &isSelected=false);

	//! \brief Sets the application path
	virtual void setPath(const std::string &path);

	//! \brief setDatabaseLogo
	virtual void setDatabaseLogo(TdkAbstractImage *logo);

	//! \brief setClipboard
	virtual void setClipboard(TdkAbstractClipboard *clipboard);

	//! \brief copyToClipBoard
	/*! Copy selecteds items to clipboard
		area
	*/
	virtual void copyToClipboard();

	//! \brief pasteFromClipboard
	/*! paste objects from clipboard
	*/
	virtual void pasteFromClipboard();

	//! \brief clipboardIsEmpty
	/*!
	*/
	virtual bool  TdkLayoutController::clipboardIsEmpty();

};


#endif
