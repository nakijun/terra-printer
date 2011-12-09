/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) tdkAbstractLayoutEvents.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/05/26 14:21:26 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_ABSTRACT_LAYOUT_EVENTS_H
#define __TDK_ABSTRACT_LAYOUT_EVENTS_H 

#include <TdkAbstractEvents.h>

class TdkMouseEvent;

//! \class tdkAbstractLayoutEvents
/*! Class to abstract events dispatch to
	high level (VB, DELPHI, C#)
*/
class TdkAbstractLayoutEvents : public TdkAbstractEvents
{
public:
	enum Cursor
	{
		Cur_Normal,		
		Cur_ZoomArea,	
		Cur_Voo,	
		Cur_Help,	
		Cur_Wait,	
		Cur_Cross
	};

public:
	//! \brief Constructor
	TdkAbstractLayoutEvents();

	//! \brief Destructor
	virtual ~TdkAbstractLayoutEvents();

	//! \brief Mouse Move Event
	/*! Mouse Move event to internal use
		\param	e	mouse object parameter
	*/
	virtual void mouseMove(TdkMouseEvent *e);

	//! \brief Mouse Down Event
	/*! Mouse Down event to internal use
		\param	e	mouse object parameter
	*/
	virtual void mouseDown(TdkMouseEvent *e);

	//! \brief Mouse Up Event
	/*! Mouse Up Event to internal use
		\param	e	mouse object parameter
	*/
	virtual void mouseUp(TdkMouseEvent *e);

	//! \brief Mouse Up Event
	/*! Event dispatch to informate the 
		process status
		\param	e process event
	*/
	virtual void processEvent(TdkProcessEvent *e);


	//! \brief ATL  End Process Event
	/*! Event to atl for indicate the final process
		\para	partial		indicate whether is end all process or just partial
	*/
	virtual void endProcessEvent(const bool &partial=true);

	//! \brief Select Event
	/*! Event to indicate the user that one operation was executed
		\param	selectItem		boolean to indicate the select operation realized
	*/
	virtual void selectEvent(const bool &selectItem);

	//! \brief insertObjectEvent
	/*! Method to dispatch that one object is inserted on
		layout 
	*/
	virtual void insertObjectEvent();

	//! \brief panEvent
	/*! Event dispatch when a pan event was
		finalized
	*/
	virtual void panEvent( double dx,  double dy);


	//! \brief zoomAreaEvent
	/*! Event dispatched when a zoom area event
		is finalized
	*/
	virtual void zoomAreaEvent();

	//! \brief zoomOutEvent
	/*! Event dispatched when a zoom out event
		is finalized
	*/
	virtual void zoomOutEvent();

public : // virtual pure methods

	//! \brief ATL Mouse Move Event
	/*!	Atl mouse move event
		\param		x		coordinate on axle x
		\param		y		coordinate on axle y
	*/
	virtual long Fire_mouseMove( double x,  double y)=0;

	//! \brief ATL Mouse Down Event
	/*! Atl mouse down vent
		\param		button		
		\param		x		coordinate on axle x
		\param		y		coordinate on axle y
	*/
	virtual long Fire_mouseDown(long button,  double x,  double y)=0;

	//! \brief ATL Mouse Up Event
	/*! Atl mouse up event
		\param		button		
		\param		x		coordinate on axle x
		\param		y		coordinate on axle y
	*/
	virtual long Fire_mouseUp(long button, double x, double y)=0;

	//! \brief ATL Process Event
	/*! Atl process event 
		\param		stop		parameter to stop the process
		\param		maxValue	max value to process
		\param		value		current value 
	*/
	virtual long Fire_processEvent(long maxValue,  long value)=0;

	//! \brief ATL  End Process Event
	/*! Event to atl for indicate the final process
		\para	partial		indicate whether is end all process or just partial
	*/
	virtual long Fire_endProcess( short partial)=0;

	//! \brief ATL Select Object
	/*! Event to atl for indicate the select operation was realized
		\param	selItem		indicate whether a layout object was selected or not
	*/
	virtual long Fire_selectObject( short selItem)=0;

	//! \brief ATL insertObjectEvent
	/*! Event dispatch when a new object is inserted
		on layout area
	*/
	virtual long Fire_insertObjectEvent() = 0;

	//! \brief ATL Fire_panEvent
	/*! Event dispatch when a pan event was
		finalized
	*/
	virtual long Fire_panEvent( double dx,  double dy) = 0;

	//! \brief ATL Fire_zoomAreaEvent
	/*! Event dispatched when a pan event is
		finalized
	*/
	virtual long Fire_zoomAreaEvent() = 0;

	//! \brief ATL Fire_zoomOutEvent
	/*! Event dispatched when a zoom out
		event is finalized
	*/
	virtual long Fire_zoomOutEvent() = 0;
};


#endif

