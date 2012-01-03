/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutTextObject.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/09/10 18:28:45 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_LAYOUT_IMAGE_OBJECT_H
#define __TDK_LAYOUT_IMAGE_OBJECT_H

#include <TdkLayoutObject.h>

class TdkAbstractCanvasDraw;
class TdkAbstractImage;
class TdkImageFileNameProperty;
class TdkImageProperty;


#define __imageTYPE		"__imageTYPE"

//! \class TdkLayoutImageObject
/*! Class to Image manipulation
	\sa TdkLayoutObject
*/
class TdkLayoutImageObject : public TdkLayoutObject
{
protected :
	
	//TdkAbstractImage*				_bitMap;						//!< Image as bitmap
	TdkImageProperty				*_bitMap;
	TdkImageFileNameProperty		*_fileName;						//!< File Name string
protected:

	//! \brief registerExtendProperties
	virtual void registerExtendProperties();

	//! \brief extractFileName
	virtual std::string extractFileName(const std::string &fileName);

public :

	//! \brief Constructor
	/*! Constructor method
		\param		id			unique identify
		\param		canvas		canvas pointer
		\param		box			bounding box
		\param		fileName	string file name
	*/
	TdkLayoutImageObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box, const std::string &fileName="");

	//! \brief Destructor
	virtual ~TdkLayoutImageObject();

	//! \brief setImageFileName
	/*! Method to set the Image FileName
		\param		fileName		file name
	*/
	virtual void setImageFileName(const std::string &fileName="");

	//! \brief Draw
		/*! Method to draw the text object on 
			Back Buffer
		*/
	virtual void draw();

	//! \brief print
		/*! Method to print the object
			\param	canvas		canvas pointer
		*/
	virtual void print(TdkAbstractCanvasDraw *canvas);

	//! \brief Clear
	/*! Method to clear the current image
	*/
	virtual void clear();

	//! \brief setBoundingBox
	/*! Method to set the object bounding box
		\param	box		box value
	*/
	virtual void setBoundingBox(const TeBox &box);
};


#endif

