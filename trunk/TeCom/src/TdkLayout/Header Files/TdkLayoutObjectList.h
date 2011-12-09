/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutObjectList.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/09/16 14:03:11 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_LAYOUT_OBJECT_LIST_H
#define __TDK_LAYOUT_OBJECT_LIST_H

#include <TdkLayoutTypes.h>

class TdkLayoutObject;
class TdkMouseEvent;
class TdkAbstractCanvasDraw;
class TdkAbstractCursor;

typedef vector<TdkLayoutObject*> objectList;

//! \class TdkLayoutObjectList
/*! Class to manipulate the objects creates
*/
class TdkLayoutObjectList
{
public :
	//! \enum LayoutProcess
	enum layoutProcess
	{
		None=0,					//!< No process
		MoveObject=1,			//!< Move Object process
		SelectByBox=2,			//!< Select object by box process
		ResizeLeftTop=3,		//!< Resize Box (left top corner)
		ResizeMiddleTop=4,		//!< Resize Box (Middle Top)
		ResizeRightTop=5,		//!< Resize	Box (Right Top corner)
		ResizeMiddleRight=6,	//!< Resize Box (Middle Right)
		ResizeBottomRight=7,	//!< Resize Box (Bottom Right corner)
		ResizeBottomMiddle=8,	//!< Resize Box (Bottom middle)
		ResizeLeftBottom=9,		//!< Resize Box (Left Bottom)
		ResizeLeftMiddle=10,	//!< Resize Box (Left Middle)
		RotateObject=12,		//!< Rotate Object Process
		CreateObject=13,		//!< Method to do a box to create one object with specific position
		ObjectProcess = 14		//!< Method to set that each object will be answear the event
	};

	enum cornerBoundingBox
	{

		Corner_LeftTop=0,
		Corner_LeftBottom=1,
		Corner_RightTop=2,
		Corner_RightBottom=3
	};

protected:

	objectList					_objectList;			//! objects creates 
	objectList					_selectObjectList;		//! object selected
	unsigned int				_autoNumber;			//!	auto number attribute
	TeCoord2D					_downClickCoord;		//! down click coordinate
	TeCoord2D					_lastCoord;				//! last click coordinate
	bool						_bMouseClicked;			//! mouse clicked status
	TdkAbstractCanvasDraw*		_canvas;				//! abstract canvas pointer
	layoutProcess				_process;				//! layout process
	TdkAbstractCursor*			_cursor;				//! Abstract mouse cursor
	TdkLayoutObject*			_objectEdition;			//! Object Edition
	bool						_createObject;			//! Create Object boolean
	TeBox						_createBox;				//! Box to create a new object
	unsigned int				_id;
	MapMode						_mapMode;

protected:

	//! \brief eraseSelected
	/*! Metod to erase 
		selected object
	*/
	virtual void eraseSelected();

	virtual void addVectorObject(objectList vector,const bool &back=true);

	//! \brief select
	/*! Method to select object by click
		\param	coord		click coordinate
		\return	returns truec whether selected
	*/
	virtual bool select(const TeCoord2D &coord, const bool &ctrl=false);

	
	//! \brief selectBox
	/*! Method to select object(s) by box
		\param	init		initial coordinate
		\param	end			final coordinate
		\return	returns true whether select any object
	*/
	virtual bool selectBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief insertRemove
	/*! Method to insert a object like selected or remove from selected list
		case already selected.
		\param	obj		layout object
	*/
	virtual void insertRemove(TdkLayoutObject* obj);

	//! \brief updateObjectsBoundingBox
	/*! Method with two coordinates calculate the displacement and
		apply on bounding box.
		This method update bounding box after translate process
		\param	init	initial coordinate
		\param	final	final coordinate
	*/
	virtual bool updateObjectsBoundingBox(const TeCoord2D &init, const TeCoord2D &final);

	//! \brief moveBoundingBox
	/*! Draw bounding box with XOR option
		\param e	mouse event
	*/
	virtual void moveBoundingBox(TdkMouseEvent *e);

	//! \brief clickOverSelected
	/*! Check whether click is over selected object
		\param	coord		click coordinate
		\return	returns true whether click is over object
	*/
	virtual bool clickOverSelected(const TeCoord2D &coord);

	//! \brief drawSelectBox
	/*! Method to draw selected box with XOR option
		\param	init	initial coordinate
		\param	end		final coordinate
	*/
	virtual void drawSelectBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief drawXorRotateBoundingBox
	/*! Method to draw rotate bounding box with XOR Option (rotate feedback)
		\param	e	mouse move event
	*/
	virtual void drawXorRotateBoundingBox(TdkMouseEvent *e);

	//! \brief clickOverHotPoint
	/*! Method to search the control point
		\param		coord			window coordinate
		\param		controlPoint	control point found
		\return	returns true whether found any control point
	*/
	virtual bool clickOverHotPoint(const TeCoord2D &coord,hotPoint &controlPoint);

	//! \brief setMouseCursor
	/*! Method to set cursor mode
		\param		controlPoint	cursor mode according hotpoint
	*/
	virtual void setMouseCursor(const hotPoint &controlPoint );

	//! \brief resizeMiddleVerticalBoundingBox
	/*! Method to resize a vertical bounding box
		\param	e	Tdk mouse event
		\param	up	boolean to indicate whether top or bottom bounding box to resize
	*/
	virtual void resizeMiddleVerticalBoundingBox(TdkMouseEvent *e, const bool &up=true);

	//! \brief resizeHorizontalBoundingBox
	/*! Method to resize the vertical bounding box
		\param	e		Tdk mouse event
		\param	left	boolean to indicate whether left or right side of bounding box
	*/
	virtual void resizeHorizontalBoundingBox(TdkMouseEvent *e, const bool &left=true);

	//! \brief resizeCornerBoundingBox
	/*! Method to resize bounding box by corner
		\param	e		Tdk mouse event
		\param	corner	left (up/down) or right (up/down) corner
	*/
	virtual void resizeCornerBoundingBox(TdkMouseEvent *e, const cornerBoundingBox &corner);

	//! \brief updateUpBoundingBox
	/*! Method to update top bounding box
		\param	init		initial coordinate
		\param	end			final coordinate
	*/
	virtual void updateUpBoundingBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief updateBottomBoundingBox
	/*! Method to update bottom bounding box
		\param	init		intial coordinate
		\param	end			final coordinate
	*/
	virtual void updateBottomBoundingBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief updateLeftBoundingBox
	/*! Method to update left bounding box
		\param	init		initial coordinate
		\param	end			final coordinate
	*/
	virtual void updateLeftBoundingBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief updateRightBoundingBox
	/*! Method to update right bounding box
		\param	init		initial coordinate
		\param	end			final coordinate
	*/
	virtual void updateRightBoundingBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief updateCornerBoundingBox
	/*! Method to update corner bounding box (up/donw/left/right)
		\param	init		initial coordinate
		\param	end			final coordinate
		\param	corner		selected corner
	*/
	virtual void updateCornerBoundingBox(const TeCoord2D &init, const TeCoord2D &end, const cornerBoundingBox &corner);

	//! \brief mouseProcessUp
	/*! Method to execute the mouse operation with object
		\param	e			mouse event
		\param	bCtrl		Control boolean
	*/
	virtual void mouseProcessUp(TdkMouseEvent *e, const bool &bCtrl);

	//! \brief mouseProcessDown
	/*! Method to execute the mouse operation with object
		\param	e	mouse event
	*/
	virtual void mouseProcessMove(TdkMouseEvent *e);

	//! \brief updateObjectAngle
	/*! Method to update object's angle
		\param		init initial coordinate
		\param		end  final coordinate
	*/
	virtual void updateObjectAngle(const TeCoord2D &init, const TeCoord2D &end);
	
public://methods
	//! \brief TdkLayoutObjectList
	/*! Empty Constructor
	*/
	TdkLayoutObjectList(TdkAbstractCursor *cursor=NULL);

	//! \brief Destructor
	virtual ~TdkLayoutObjectList();

	//! \brief setCanvas
	/*! Associate abstract canvas with layout object
		\param	canvas		abstract canvas pointer
	*/
	virtual void setCanvas(TdkAbstractCanvasDraw* canvas);

	//! \brief add
	/*! Method to add a new layout object to list
		\param	object		layout object
	*/
	virtual void add(TdkLayoutObject* object,const bool &isSelected=false);

	//! \brief setMaxId
	/*! Update the maximum id! Used when
		user add a object from gpl file
		\param	id	object id
	*/
	virtual void setMaxId(const unsigned int &id);

	//! \brief Remove
	/*! Remove a layout object from list by your unique id
		\param	id		unique identify
	*/
	virtual void remove(const unsigned int id);
	
	//! \brief Remove
	/*! Remove a layout object from list by name
		\param	name	object name
	*/
	virtual void remove(const std::string &name);

	//! \brief removeSelected
	/*! Method to remove selecteds 
		objects from select list (not erase object)
	*/
	virtual void removeSelected();

	//! \brief clear
	/*! Method to erase (delete) layout object
	*/
	virtual void clear();

	//! \brief getObject
	/*! Returns the layout object from your unique id
		\param	id		unique id
		\return	returns the layout object pointer
	*/
	virtual TdkLayoutObject* getObject(const unsigned int &id);

	//! \brief getObject
	/*! Returns the layout object from your name
		\param	name	object name
		\return	returns the layout object pointer
	*/
	virtual TdkLayoutObject* getObject(const std::string &name);

	//! \brief getSelectObject
	/*! Returns the object list from 
	*/
	virtual objectList getSelectObject();

	//! \brief sendToBack
	/*! Method to send the selected 
		objects to back
	*/
	virtual void sendToBack();
	
	//! \brief bringToFront
	/*! Method to brint the selected
		object to front
	*/
	virtual void bringToFront();

	//! \brief leftAlignment
	/*! Align selected object in 
		left border
	*/
	virtual void leftAlignment();
	
	//! \brief rightAlignment
	/*! Align selected objects n
		right border
	*/
	virtual void rightAlignment();

	//! \brief bottomAlignment
	/*! Align selected objects in
		bottom border
	*/
	virtual void bottomAlignment();

	//! \brief topAlignment
	/*! Align selected object in
		top border
	*/
	virtual void topAlignment();

	//! \brief horizontalCenter
	/*! Center selected objects 
		in horizontal position
		\param	cx	center x
	*/
	virtual void horizontalCenter(const double &cx);

	//! \brief verticalCenter
	/*! Center selected objects 
		in vertical position
		\param	cy	center y
	*/
	virtual void verticalCenter(const double &cy);

	//! \brief size
	/*! Return the quantity of object 
		in list
		\return	return unsigned int
	*/
	virtual unsigned int size();

	//! \brief select
	/*! Method to select the object by your name
		\param	objName		object name
		\return	returns true whether sucess
	*/
	virtual bool TdkLayoutObjectList::select(const std::string &objName);


public : //events

	//! \brief mouseMove
	/*! Mouse Move Event
		\param	e	mouse move atributtes
	*/
	virtual void mouseMove(TdkMouseEvent *e);

	//! \brief mouseDown
	/*! Mouse Down Event
		\param	e	mouse donw atributtes
	*/
	virtual void mouseDown(TdkMouseEvent *e, const bool &bCtrl=false);

	//! \brief mouseUp
	/*! Mouse Up Event
		\param	e	mouse up atributtes
	*/
	virtual void mouseUp(TdkMouseEvent *e, const bool &bCtrl);

	//! \brief update
	/*! Update object 
		visualization
	*/
	virtual void update();

	//! \brief updateSelection
	/*! Update selected object
		visualization
	*/
	virtual void updateSelection();

	//! \brief createText
	/*! Method to create a layout text object
		\param	box		box to creation
	*/
	virtual void moveKey(const moveKeys &key,const bool &ctrl=false);

	//! \brief print
	/*! Method to object print
		\param	canvas	canvas pointer
	*/
	virtual void print(TdkAbstractCanvasDraw *canvas);

	//! \brief getCreateBox
	/*! Method to return the box to create a new
		layout object
	*/
	virtual TeBox getCreateBox();

	//! \brief createLayoutObjectMode
	/*! Method to set the environment mode to create layout object
	*/
	virtual void createLayoutObjectMode();

	//! \brief resetLayoutObjectMode
	/*! Method to reset the environment mode
	*/
	virtual void resetLayoutObjectMode();
	
	//! \brief getId
	/*! Method to return the next id to 
		associate with layout object
	*/
	virtual unsigned int getId();

	//! \brief getObjectName
	/*! Method to return the object name
		according the index value
	*/
	virtual std::string  getObjectName(const unsigned int &index);

	//! \brief getSelectObjectName
	/*! Method to return the select object name
		according the index value
	*/
	virtual std::string getSelectObjectName(const unsigned int &index);

	//! \brief getProcess
	/*! Method to return the current process of layout object list class
		\return return the process
	*/
	virtual layoutProcess getProcess();

	//! \brief resetProcess
	/*! Method to reset the current process
	*/
	virtual void resetProcess();

	//! \brief setMapProcess
	/*! Method to set the map process
	*/
	virtual void setMapProcess(const MapMode &mode);

	//! \brief setFullUpdate
	/*! Method to set for each object
		that is necessary a full update
		the next draw
	*/
	virtual void setFullUpdate();

	//! \brief getList
	/* Returns all objects
	*/
	virtual objectList getList();

	virtual void resizeAllObjects(const double &oldW, const double &oldH, const double &newW, const double &newH);

	virtual void unSelectAll();

};

#endif

