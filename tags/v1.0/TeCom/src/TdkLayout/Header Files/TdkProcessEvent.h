/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkProcessEvent.h
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
#ifndef __TDK_PROCESS_EVENT_H
#define __TDK_PROCESS_EVENT_H

//! \class TdkProcessEvent
/*! Class to dispatch for user
	the process step such event
*/
class TdkProcessEvent
{
public:
		unsigned int	_maxValue;		//! maximum value of step operation
		unsigned int	_value;			//! current value of step operation
public:
	//! Constructor
	TdkProcessEvent();
	//! Destructor
	~TdkProcessEvent();
};


#endif

