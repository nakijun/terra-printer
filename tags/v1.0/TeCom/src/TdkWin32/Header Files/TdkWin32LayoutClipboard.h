/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkWin32LayoutClipboard.h
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
#ifndef __TDK_WIN32_LAYOUT_CLIPBOARD_H
#define __TDK_WIN32_LAYOUT_CLIPBOARD_H

class TdkWin32LayoutClipboard : public TdkAbstractClipboard
{
protected:

	HWND		_hwnd;
	UINT		_format;

protected :

	//! \brief registerFormat
	/*! Method to register the proprietary
		format
	*/
	virtual bool registerFormat();

public :

	//! \brief Constructor
	TdkWin32LayoutClipboard(HWND hwnd);

	//! \brief Destructor
	~TdkWin32LayoutClipboard();

	//! \brief copy
	/*! Copy the unsigned char array to clipboard
		area
		\param	buff		unsigned char array
		\param	size		size array
		\return		returns true whether sucess
	*/
	virtual bool copy(unsigned char *buff, const unsigned int &size);

	//! \brief paste
	/*! Paste the unsigned char arrray from
		clipboard area
		\param	size		size arrya
		\return	returns the unsigned char array
	*/
	virtual unsigned char *paste(unsigned int &size);

	
	//! \brief isEmpty
	/*! Returns if clipboard has a layout object
	*/
	virtual bool isEmpty();
};


#endif // __TDK_WIN32_LAYOUT_CLIPBOARD_H



