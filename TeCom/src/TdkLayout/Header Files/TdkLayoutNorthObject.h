
/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutNorthObject.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/07/20 14:01:32 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_LAYOUT_NORTH_OBJECT_H
#define __TDK_LAYOUT_NORTH_OBJECT_H

#include <TdkLayoutObject.h>

class TdkAbstractCanvasDraw;
class TdkNorthTypeProperty;

#define __northTYPE		"__northTYPE"

//! \class TdkLayoutImageObject
/*! Class to wind roses manipulation
	\sa TdkLayoutObject
	\sa TdkLayoutImageObject
*/
class TdkLayoutNorthObject : public TdkLayoutImageObject 
{
protected:

	std::string					_path;	//!< path to north symbol
	TdkNorthTypeProperty		*_nortProperty;

protected:

	virtual void registerExtendProperties();

public :

	//! \brief Constructor
	/*! Constructor method
		\param		id			unique identify
		\param		canvas		canvas pointer
		\param		box			bounding box
		\param		fileName	string file name
	*/
	TdkLayoutNorthObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box, const std::string &pathName="");

	//! \brief Destructor
	virtual ~TdkLayoutNorthObject();

	//! \brief setImageFileName
	/*! Method to set the Image FileName
		\param		fileName		file name
	*/
	virtual void setNorthType(const std::string &type="North01");

	//! \brief draw
	/*! Method to draw the north object
	*/
	virtual void draw();
};


#endif

