
/*********************************************************
* FUNCATE - GIS development team
* 
* @(#) TdkAtlOdImportProcessEvent.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/03/25 14:07:02 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_ATL_OD_IMPORT_PROCESS_EVENT_H
#define __TDK_ATL_OD_IMPORT_PROCESS_EVENT_H

#include <TdkAbstractProcessEvent.h>

class COdImport;

//! \class TdkAtlOdImportProcessEvent
/*! Atl Class to process dialog
	\sa TdkAbstractProcessEvent
*/
class TdkAtlOdImportProcessEvent : public TdkAbstractProcessEvent
{
protected:
	COdImport	*_event;
public :

	//! \brief Constructor
	TdkAtlOdImportProcessEvent(COdImport *ev=0);

	//! \brief Destructor
	~TdkAtlOdImportProcessEvent();

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
	virtual void buildingGeometryEvent(const short &representation, const long &geom_id, const std::string &object_id){}
};

#endif

