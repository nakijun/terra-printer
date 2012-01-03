/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) tdkLayoutObjectList.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2009/07/17 11:09:53 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_ABSTRACT_CURSOR_H
#define __TDK_ABSTRACT_CURSOR_H

//! \class tdkAbstractCursor
/*! Abstract Class to set cursor mode
*/
class TdkAbstractCursor
{
protected:

public :
	//! \brief Constructor
	TdkAbstractCursor(){};

	//! \brief Destructor
	~TdkAbstractCursor(){};

	//! \brief setCursor
	/*! Method to set cursor mode
		\param	cursorMode		cursor
	*/
	virtual void setCursor(const cursorMode &cursor){};
};


#endif

