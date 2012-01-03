/*
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
* $Date: 2009/07/28 10:50:43 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_ABSTRACT_EVENTS_H
#define __TDK_ABSTRACT_EVENTS_H 

class TdkMouseEvent;
class TdkProcessEvent;

//! \class tdkAbstractEvents
/*! Class to abstract events dispatch to
	high level (VB, DELPHI, C#)
*/
class TdkAbstractEvents
{
public:
	//! \brief Constructor
	TdkAbstractEvents(){};

	//! \brief Destructor
	virtual ~TdkAbstractEvents() {};

	//! \brief Mouse Move Event
	/*! Mouse Move event to internal use
		\param	e	mouse object parameter
	*/
	virtual void mouseMove(TdkMouseEvent *e) = 0;

	//! \brief Mouse Down Event
	/*! Mouse Down event to internal use
		\param	e	mouse object parameter
	*/
	virtual void mouseDown(TdkMouseEvent *e) = 0;

	//! \brief Mouse Up Event
	/*! Mouse Up Event to internal use
		\param	e	mouse object parameter
	*/
	virtual void mouseUp(TdkMouseEvent *e) = 0;

	//! \brief Mouse Up Event
	/*! Event dispatch to informate the 
		process status
		\param	e process event
	*/
	virtual void processEvent(TdkProcessEvent *e){};

	//! \brief  End Process Event
	/*! Event to indicate the final process
		\para	partial		indicate whether is end all process or just partial
	*/
	virtual void endProcessEvent(const bool &partial=true){};

	//! \brief Select Event
	/*! Event to indicate the user that one operation was executed
		\param	selectItem		boolean to indicate the select operation realized
	*/
	virtual void selectEvent(const bool &selectItem){};
};

#endif

