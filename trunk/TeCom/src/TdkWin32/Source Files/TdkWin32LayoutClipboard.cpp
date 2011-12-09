#include <stdafx.h>
#include <TdkAbstractClipboard.h>
#include <TdkWin32LayoutClipboard.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TdkWin32LayoutClipboard::TdkWin32LayoutClipboard(HWND hwnd) : TdkAbstractClipboard()
{
	_hwnd=hwnd;
	this->registerFormat();
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TdkWin32LayoutClipboard::~TdkWin32LayoutClipboard()
{
	EmptyClipboard();
}

///////////////////////////////////////////////////////////////////////////////
//Copy Layout Objects to Memory
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkWin32LayoutClipboard::copy(unsigned char *buff, const unsigned int &size)
{
	HGLOBAL hglbCopy;
	LPTSTR  lptstrCopy; 

	if (!OpenClipboard(_hwnd))		return false;
	EmptyClipboard(); 
	hglbCopy = GlobalAlloc(GMEM_MOVEABLE,(size + 1) * sizeof(TCHAR)); 
    if (hglbCopy == NULL) 
    { 
		CloseClipboard(); 
        return false;
    } 
    lptstrCopy =(LPTSTR) GlobalLock(hglbCopy); 
	for(unsigned int i=0;i<size;i++)	lptstrCopy[i]=buff[i];
	lptstrCopy[size]=0;
	GlobalUnlock(hglbCopy); 
	SetClipboardData(_format, hglbCopy); 
	CloseClipboard(); 
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Paste Layout Objects from Memory
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
unsigned char* TdkWin32LayoutClipboard::paste(unsigned int &size)
{
	HGLOBAL			hglb; 
	unsigned char	*buffer=0;
	LPTSTR			lptstr; 
	unsigned int	i;
	
	size=0;
	if (!IsClipboardFormatAvailable(_format))	return 0; 
	if (!OpenClipboard(_hwnd))					return 0; 
	hglb = GetClipboardData(_format); 
	if (hglb != NULL) 
	{ 
		lptstr =(LPTSTR) GlobalLock(hglb); 
		while(lptstr[size] != 0) size++;
		buffer=new unsigned char[size];
		for(i=0;i<size;i++)	buffer[i]=(unsigned char)lptstr[i];
		GlobalUnlock(hglb);
	}
	CloseClipboard(); 
	return buffer;
}

///////////////////////////////////////////////////////////////////////////////
//Register Layout Clipboard format
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkWin32LayoutClipboard::registerFormat()
{
	if((_format=RegisterClipboardFormat(L"LAYOUT_CLIPBOARD")) == 0) 
		return false;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//IsEmpty
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkWin32LayoutClipboard::isEmpty()
{
	return (IsClipboardFormatAvailable(_format) == FALSE ? true : false);
}