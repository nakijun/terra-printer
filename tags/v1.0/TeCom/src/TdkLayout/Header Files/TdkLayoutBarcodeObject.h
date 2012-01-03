/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutBarcodeObject.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/09/16 17:37:20 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_LAYOUT_BARCODE_OBJECT_H
#define __TDK_LAYOUT_BARCODE_OBJECT_H

//! \class TdkLayoutBarcodeObject
/*! Barcode Class
*/
class TdkLayoutBarcodeObject : public TdkLayoutTextObject
{
protected :
	
	//! \brief registerExtendProperties
	/*! Register the extend properties
	*/
	virtual void registerExtendProperties();

public :

	//! \brief Constructor
	TdkLayoutBarcodeObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas, const TeBox &box,const std::string textValue="");

	//! \brief Destructor
	~TdkLayoutBarcodeObject();
};

#endif

