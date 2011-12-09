/******************************************************************************
* FUNCATE - GIS development team
* 
* @(#) TdkAbstractProcessEvent.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/03/22 12:13:07 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_ABSTRACT_PROCESS_EVENT
#define __TDK_ABSTRACT_PROCESS_EVENT


#include <string>

using namespace std;


//! \class TdkAbstractProcessEvent
/*! Abstract class to create a process
	status dialog
*/
class TdkAbstractProcessEvent
{
public :

	//! \brief Constructor
	TdkAbstractProcessEvent(){};

	//! \brief Destructor
	virtual ~TdkAbstractProcessEvent(){};

	//! \brief processStatusEvent
	/*! Abstract method to show the process status
		\param	maxValue		maximum value
		\param	currentValue	current value
	*/
	virtual void processStatusEvent(const long &maxValue, const long &currentValue) = 0;

	//! \brief buildingGeometryEvent
	/*! Method to dispatch the building Geometry Event
		to informate the current geometry in building process
		\param	representation		representation type
		\param	geom_id				geometry identify
		\param	object_id			string identify
	*/
	virtual void buildingGeometryEvent(const short &representation, const long &geom_id, const std::string &object_id)=0;
};

#endif

