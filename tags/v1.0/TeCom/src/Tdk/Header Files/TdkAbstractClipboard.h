/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkAbstractClipboard.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/09/14 18:19:47 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_CLIPBOARD_H
#define __TDK_CLIPBOARD_H

//! \class TdkAbstractClipboard
/*! Abstract class to manipulate
	the clipboard
*/
class TdkAbstractClipboard
{
protected:

	//! \brief registerFormat
	/*! Method to register the proprietary
		format
	*/
	virtual bool registerFormat() = 0;

public :

	//! \brief Constructor
	TdkAbstractClipboard();

	//! \brief Destructor
	virtual ~TdkAbstractClipboard();

	//! \brief copy
	/*! Copy the unsigned char array to clipboard
		area
		\param	buff		unsigned char array
		\param	size		size array
		\return		returns true whether sucess
	*/
	virtual bool copy(unsigned char *buff, const unsigned int &size) = 0;

	//! \brief paste
	/*! Paste the unsigned char arrray from
		clipboard area
		\param	size		size arrya
		\return	returns the unsigned char array
	*/
	virtual unsigned char *paste(unsigned int &size) = 0;

	//! \brief isEmpty
	/*! Returns if clipboard has a layout object
	*/
	virtual bool isEmpty() = 0;
};


#endif // end __TDK_CLIPBOARD_H


