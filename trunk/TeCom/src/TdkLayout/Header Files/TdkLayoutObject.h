/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutObject.h
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
#ifndef __TDK_LAYOUT_OBJECT_H
#define __TDK_LAYOUT_OBJECT_H

#include <TeVisual.h>
#include <TeBox.h>

#include <TdkAbstractProperty.h>
#include <TdkAbstractCanvasDraw.h>
#include <TdkObjectTypes.h>

class TdkMouseEvent;
class TdkAngleProperty;
class TdkLeftProperty;
class TdkTopProperty;
class TdkHeightProperty;
class TdkWidthProperty;



#define __undefinedTYPE		"__undefinedTYPE";
#define _constTolerance		297.0
#define __rotateSize		20

//! \class TdkLayoutObject
/*! Class to layout object 
	manipulation
*/
class TdkLayoutObject
{
protected :

		std::vector<TdkAbstractProperty*>	_properties;
		

protected:
	std::vector<TdkAbstractProperty*>	_decoratedPropertyList;
	TeColor						_backColor;					//!< back color
	bool						_visibleContourBox;			//!< visible contour box
	bool						_selected;					//!< selected option
	bool						_visible;					//!< visible option
	bool						_enabled;					//!< enable option
	TdkAngleProperty			*_angle;
	TeBox						_boundingBox;				//!< bounding box
	TdkAbstractCanvasDraw*		_canvas;					//!< canvas pointer
	unsigned int				_id;						//!< unique identify
	std::string					_objectName;				//!< object name
	objectType					_type;						//!< object type
	bool						_lockResize;				//!< lock resize update
	bool						_necessaryRedraw;			//!< Indicate when necessary a redraw

	TdkLeftProperty				*_left;						//!< Left value
	TdkTopProperty				*_top;						//!< Top value
	TdkHeightProperty			*_height;					//!< Height value
	TdkWidthProperty			*_width;					//!< Width value
	bool						_stopDispatch;				//!< Stop dispatch
	bool						_mousePress;				//!< Mouse press flag
	bool						_editable;
protected:

	//! \brief calculateHotPoint
	/*! Method to calculate the object's hot point
		\return		returns the list of coordinates
	*/
	virtual vector<TeCoord2D> calculateHotPoint();

	//! \brief boxToCoords
	/*! Method to convert a box to one coordinate list
		\param		box		box to convertion
		\return		returns the coordinate list
	*/
	virtual vector<TeCoord2D> boxToCoords(const TeBox &box);

	//! \brief setClipClientArea
	/*! Method to set the client area 
		valid to object
	*/
	virtual void setClipClientArea();

	//! \brief subtractRulerArea
	/*! Method to subtract ruler area
	*/
	virtual void subtractRulerArea();

	//! \brief setClipClientAreaW
	/*! Method to set the client area in 
		world coordinate
		\param		box client area
	*/
	virtual void setClipClientAreaW(const TeBox &box,TdkAbstractCanvasDraw* canvas=0);

	//! \brief drawRotateControlPoint
	/*! Method to draw Rotate control point
		\param	init	initial coordinate to control point
		\param	end		final coordinate to control point
	*/
	virtual void drawRotateControlPoint(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief draw
	/*! Abstract Method to draw 
		the object
	*/
	virtual void draw();

	//! \brief drawSelection
	/*! Method to draw selection
	*/
	virtual void drawSelection(const TdkAbstractCanvasDraw::TdkCanvasBuffer &buffer=TdkAbstractCanvasDraw::cbrBack);

	//! \brief calculateRotateControlPoint
	/*! Method to calculate the rotate control point
		\param		init		initial coordinate
		\param		end			final coordinate
		\return		returns the control point coordinate
	*/
	virtual TeCoord2D calculateRotateControlPoint(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief drawXorBox
	/*! Draw a box with xor draw option
		\param	box			bounding box
		\param	center		center coordinate
		\param	angle		angle of rotation
	*/
	virtual void drawXorBox(TeBox box,const TeCoord2D &center, const double &angle=0.0 );

	//! \brief drawXorLine
	/*! Draw a line with xor draw option
		\param	line		terralib line
		\param	angle		angle of rotation
	*/
	virtual void drawXorLine(const TeLine2D &line, const double &angle=0.0);

	//! \brief getDisplacement
	/*! Method to returns the object displacement
		\param	init		initial coordinate
		\param	end			final coordinate
		\param	center		center coordinate
		\param	angle		angle rotation
		\param	dx			displacement on axle x
		\param	dy			displacement on axle y
	*/
	virtual void getDisplacement(const TeCoord2D &init, const TeCoord2D &end, const TeCoord2D &center,\
		const double &angle, double &dx, double &dy);

	//! \brief registerProperties
	/*! Method to register the main properties
	*/
	virtual void registerProperties();

	//! \brief registerExtendProperties
	/*! Method to register the extend properties
		for each object
	*/
	virtual void registerExtendProperties() = 0;

	
	//! \brief convert2Polygon
	/*! Method to convert a box to a polygon
		to allow draw the rectangle with angle
		\param		box		input box
		\param		pol		polygon represented a box
	*/
	virtual void convert2Polygon(const TeBox &box, TePolygon &pol);
public:
	//! \brief Constructor
	/*! Constructor with canvas pointer
		\param		canvas pointer associate with object
	*/
	TdkLayoutObject(const int &id, TdkAbstractCanvasDraw* canvas);
	
	//! \brief Destructor
	virtual ~TdkLayoutObject();

	//! \brief setBackColor
	/*! Method to set the object back color
		\param	color		terralib color (RGB)
	*/
	virtual void setBackColor(const TeColor &color);

	//! \brief setVisibleContourBox
	/*! Method to enable visible contour box 
		\param		status		boolean value
	*/
	virtual void setVisibleContourBox(const bool &status);

	//! \brief setVisible
	/*! Method to enable visible object
		\param		status		boolean value
	*/
	virtual void setVisible(const bool &status);

	//! \brief setEnabled
	/*! Method to enable objedt
		\param	status	boolean value
	*/
	virtual void setEnabled(const bool &status);

	//! \brief setAngle
	/*! Method to set angle object
		\param		angle		angle value (degree)
	*/
	virtual void setAngle(const double &angle);

	//! \brief setBoundingBox
	/*! Method to set the object bounding box
		\param		box		terralib bounding box
	*/
	virtual void setBoundingBox(const TeBox &box);

	//! \brief setCanvas
	/*! Method to set Canvas pointer
		\param	canvas		abstract canvas pointer
	*/
	virtual void setCanvas(TdkAbstractCanvasDraw* canvas);

	//! \brief drawSelectionBoundingBox
	/*! Method to draw selection
	*/
	virtual void drawSelectionBoundingBox(const TdkAbstractCanvasDraw::TdkCanvasBuffer &buffer=TdkAbstractCanvasDraw::cbrBack);

	//! \brief drawTranslateProcess
	/*! Method to draw translate process
		\param	dx		x displacement 
		\param	dy		y displacement
	*/
	virtual void drawTranslateProcess(const double &dx, const double &dy);

	//! \brief drawResizeProcess
	/*! Method to draw Resize 
		process to object
	*/
	virtual void drawResizeProcess();

	//! \brief getType
	/*! Method to return the object type
		\return		returns the object type
	*/
	virtual objectType getType();

	//! \brief getId
	/*! Method to return the unique id associate
		with object
		\return	returns the unsigned int
	*/
	virtual unsigned int getId();

	//! \brief getName
	/*! Method to return the object
		name
		\return	returns the string associate with object
	*/
	virtual std::string getName();

	//! \brief isSelected
	/*! Returns whether object is selected
		\return returns selection status
	*/
	virtual bool isSelected();

	//! \brief setSelect
	/*! Sets the object to select status
	*/
	virtual void setSelect(const bool &sel=true);

	//! \brief getBox
	/*! Method to return the bounding box
		\return returns the object bounding box
	*/
	virtual TeBox getBox();

	//! \brief setLeftBox
	/*! Method to set the left box
		\param	box	terralib box
	*/
	virtual void setLeftBox(const TeBox &box);

	//! \brief setRightBox
	/*! Method to set right box
		\param	box terralib box
	*/
	virtual void setRightBox(const TeBox &box);

	//! \brief setBottomBox
	/*! Method to set bottom box
		\param	box terralib box
	*/
	virtual void setBottomBox(const TeBox &box);

	//! \brief setTopBox
	/*! Method to set top box
		\param	box terralib box
	*/
	virtual void setTopBox(const TeBox &box);

	//! \brief setHorizontalCenter
	/*! Method to set horizontal center
		\param	box terralib box
	*/
	virtual void setHorizontalCenter(const double &xc);

	//! \brief setVertical Center
	/*! Method to set vertical center
		\param	box terralib box
	*/
	virtual void setVerticalCenter(const double &yc);

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

	//! \brief update
	/*! Method to update the 
		object visualization
	*/
	virtual void update();

	//! \brief updateSelection
	/*! Method to update the visualization
		for object selection
	*/
	virtual void updateSelection();

	//! \brief clickOver
	/*! Method to check whether click is over
		object
		\param	coord		coordinate of click
		\return	returns true whether click is over object
	*/
	virtual bool clickOver(const TeCoord2D &coord);

	//! \brief boxOver
	/*! Method to check whether the box is over
		object
		\param	box		terralib box
		\return	returns true whether sucess
	*/
	virtual bool boxOver(const TeBox &box);

	//! \brief hotPointOver
	/*! Method to check whether the coordinate
		is over a hot point
		\param	coord	mouse coordinate
		\param	ctrl	hot point selected
		\return	returns true whether over hot point
	*/
	virtual bool hotPointOver(const TeCoord2D &coord, hotPoint &ctrl);

	//! \brief drawUpBoundingBoxProcess
	/*! Method to draw Up Bounding Box Resize Process
		\param	init		initial coordinate
		\param	end			final coordinate
	*/
	virtual void drawUpBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief update Up Bounding Box
	/*! Method to update top of bounding box
		\param	init		initial displacement
		\param	end			final displacement
	*/
	virtual void updateUpBoundingBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief updateDownBoundingBox
	/*! Method to Update the Bottom Bounding Box
		\param	init		initial coordinate
		\param	end			final coordinate
	*/
	virtual void updateDownBoundingBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief updateLeftBoundingBox
	/*! Method to update left bounding box
		\param	init		initial displacement
		\param	end			final displacement
	*/
	virtual void updateLeftBoundingBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief updateRightBoundingBox
	/*! Method to update right bounding box
		\param	init		initial displacement
		\param	end			final displacement
	*/
	virtual void updateRightBoundingBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief updateLeftTopBoundingBox
	/*! Method to update corner left top bounding box
		\param	init	initial displacement
		\param	final	final displacement
	*/
	virtual void updateLeftTopBoundingBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief leftBottomBoundingBox
	/*! Method to update corner left bottom bounding box
		\param init		initial displacement
		\param end		final displacement
	*/
	virtual void updateLeftBottomBoundingBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief updateRightTopBoundingBox
	/*! Method to udpate corner right top bounding box
		\param init		initial displacement
		\param end		final displacement
	*/
	virtual void updateRightTopBoundingBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief updateRightBottomBoundingBox
	/*! Method to update corner right bottom bounding box
		\param init		initial displacement
		\param end		final displacement
	*/	
	virtual void updateRightBottomBoundingBox(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief drawDownBoundingBoxProcess
	/*! Method to draw the down bounding box resize process
		\param	init	initial coordinate
		\param	end		final coordinate
	*/
	virtual void drawDownBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief drawLeftMiddleBoundingBoxProcess
	/*! Method to draw the left middle bounding box resize process
		\param	init		initial coordinate
		\param	end			final coordinate
	*/
	virtual void drawLeftMiddleBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief drawRightMiddleBoundingBoxProcess
	/*! Method to draw right middle bounding box resize process
		\param	init		initial coordinate
		\param	end			final coordinate
	*/
	virtual void drawRightMiddleBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief drawLeftTopBoundingBoxProcess
	/*! Method to draw left top bounding box resize process
		\param	init		initial coordinate
		\param	end			final coordinate
	*/
	virtual void drawLeftTopBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief drawLeftBottomBoundingBoxProcess
	/*! Method to draw left bottom bounding box resize process
		\param	init		initial coordinate
		\param	end			final coordinate
	*/
	virtual void drawLeftBottomBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief drawRightTopBoundingBoxProcess
	/*! Method to draw right top bounding box resize process
		\param	init		initial coordinate
		\param	end			final coordinate
	*/
	virtual void drawRightTopBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief drawRightBottomBoundingBoxProcess
	/*! Method to draw right bottom bounding box resize process
		\param	init		initial coordinate
		\param	end			final coordinate
	*/
	virtual void drawRightBottomBoundingBoxProcess(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief drawRotateProcess
	/*! Method to draw rotate feedback
		\param	init		initial coordinate
		\param	end			initial coordinate
	*/
	virtual void drawRotateProcess(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief setAngle
	/*! Method to set angle rotation by according 2 points
		\param	init		initial coordinate
		\param	end			final coordinate
	*/
	virtual void setAngle(const TeCoord2D &init, const TeCoord2D &end);

	//! \brief print
	/*! Method to print the object
		\param	canvas		canvas pointer
	*/
	virtual void print(TdkAbstractCanvasDraw *canvas)=0;

	//! \brief getPropertiesCount
	/*! Method to return the properties count
	*/
	virtual unsigned int getPropertiesCount();

	//! \brief getPropertyValue
	/*! Method to return the property value
		\param	index		index value of property in the list
		\return returns the property of object pointer
	*/
	virtual TdkAbstractProperty * getPropertyValue(const unsigned int &index);

	//! \brief getPropertyValue
	/*! Method to return the property value
		\param	propertyName	property name
		\return returns the property of object pointer
	*/
	virtual TdkAbstractProperty * getPropertyValue(const std::string &propertyName);

	//! \brief getPropertyName
	/*! Method to return the property name according the index
		\param		index		index value
		\return		returns the property name
	*/
	virtual std::string getPropertyName(const unsigned int &index);

	//! \brief getStopDispatch
	/*! Method to return the stop dispatch status
	*/
	virtual bool getStopDispatch();

	//! \brief setMapMode
	/*! Method to set the map mode
	*/
	virtual void setMapMode(const MapMode &mode){};

	//! \brief setNecessaryUpdate
	/* Method to set to layout object
		that is necessary a full redraw
	*/
	virtual void setNecessaryUpdate();

	//! \brief associateObjectProperty
	/*! Associate one property from a object with other object
	*/
	virtual void associateObjectProperty(TdkAbstractProperty *propertyObject);

	//! \brief disassociateObjectProperty
	virtual void disassociateObjectProperty(TdkAbstractProperty *propertyObject=NULL);

	//! \brief getProperties
	/*! Returns the property list
		associate with layout object
	*/
	virtual std::vector<TdkAbstractProperty*> getProperties();

	//! \brief setName
	/*! Set the object name
		\param	name	object name
	*/
	virtual void setName(const std::string &name);

	//! \brief setId
	/*! Set the object id
		\param		id		new object id
	*/
	virtual void setId(const unsigned int &id);

	//! \brief setRatio
	virtual void setRatio(const double &ratioSize){/* not implemented here */}

};



#endif


