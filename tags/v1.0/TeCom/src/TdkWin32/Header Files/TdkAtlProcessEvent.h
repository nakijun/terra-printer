/******************************************************************************
* FUNCATE - GIS development team
* 
* @(#) TdkAtlProcessEvent.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/03/22 20:42:38 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_ATL_PROCESS_EVENT_H
#define __TDK_ATL_PROCESS_EVENT_H

#include <TdkAbstractProcessEvent.h>

class COdExport;

//! \class TdkAtlProcessEvent
/*! Atl Class to process dialog
	\sa TdkAbstractProcessEvent
*/
class TdkAtlProcessEvent : public TdkAbstractProcessEvent
{
protected:
	COdExport	*_event;
public :

	//! \brief Constructor
	TdkAtlProcessEvent(COdExport *ev=0);

	//! \brief Destructor
	~TdkAtlProcessEvent();

	//! \brief processStatusEvent
	/*! Abstract method to show the process status
		\param	maxValue		maximum value
		\param	currentValue	current value
	*/
	virtual void processStatusEvent(const long &maxValue, const long &currentValue);

	//! \brief buildingGeometryEvent
	/*! Method to dispatch the building Geometry Event
		to informate the current geometry in building process
		\param	representation		representation type
		\param	geom_id				geometry identify
		\param	object_id			string identify
	*/
	virtual void buildingGeometryEvent(const short &representation, const long &geom_id, const std::string &object_id);
};

#endif

