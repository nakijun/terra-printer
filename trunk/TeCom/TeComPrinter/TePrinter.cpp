// TePrinter.cpp : Implementation of CTePrinter
#include "stdafx.h"
#include "TePrinter.h"
#include <TdkLayoutController.h>
#include <TdkAbstractCanvasDraw.h>
#include <TdkGdiCanvasDraw.h>
#include <TdkMouseEvent.h>
#include <comutil.h>
#include <TeAdoDB.h>
#include <TeAdoFireBird.h>
#include <TeAdoOracle.h>
#include <TeAdoSqlServer.h>
#include <TePostgreSQL.h>
#include <TeDatabase.h>
#include <TdkAbstractProperty.h>
#include <TdkWin32Decoder.h>
#include <TdkWin32Error.h>
#include <TdkAbstractClipboard.h>
#include <TdkWin32LayoutClipboard.h>
#include <TdkGdiImage.h>
#include <locale>

#include <strsafe.h>
// CTePrinter


std::string getApplicationPath(WCHAR path[])
{
	int				len;
	int				i;
	char			*justPath;
	std::string		result;


	len=(int)wcslen(path);
	justPath=new char[len + 1];
	for(i=0;i<len;i++)		
		justPath[i]=(char)path[i];
	justPath[i]=NULL;

	for(i=len - 1; i>=0; i--)
	{
		if(justPath[i] == '\\') break;
		justPath[i]=NULL;
	}

	result=std::string(justPath);
	return result;
}



///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
CTePrinter::CTePrinter()
	{
		WCHAR			path[2048];
		std::string		fullPath;

		setlocale(LC_ALL,"English");
		m_bWindowOnly = TRUE;
		_controller=NULL;
		m_clrBackColor=RGB(128,128,128);
		_controller=new TdkLayoutController(this,this);
		_cursor=CursorNormal;
		_provider=Access;
		setlocale(LC_NUMERIC,"English_USA.1252");
		if(_controller)
		{
			::GetModuleFileName(NULL,path,2048);
			fullPath=getApplicationPath(path);

			_controller->setPath(fullPath);
			fullPath+="databaseImage.png";
			TdkAbstractImage *logo=new TdkGdiImage(fullPath); 
			_controller->setDatabaseLogo(logo);

			//TdkWin32LayoutClipboard *clipBoard=new TdkWin32LayoutClipboard(m_hWnd);
			//_controller->setClipboard(clipBoard);

		}
	}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
CTePrinter::~CTePrinter()
{
	if(_controller) delete _controller;
}

///////////////////////////////////////////////////////////////////////////////
//Draw Method
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

HRESULT CTePrinter::OnDrawAdvanced(ATL_DRAWINFO& di)
{
	if(!_controller->getCanvas())
	{
		RECT& rc = *(RECT*)di.prcBounds;
		HBRUSH hBrush=CreateSolidBrush(m_clrBackColor);
		FillRect(di.hdcDraw,&rc,hBrush);
		DeleteObject(hBrush);
	}else
	{
		_controller->refresh();
	}

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Execute Method
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::execute(void)
{
	DWORD	size;
	double	x,y;
	
	// Get the size of the default printer name.
	GetDefaultPrinter(NULL, &size);

	// Allocate a buffer large enough to hold the printer name.
	if(size<2048)
	{
		TCHAR* buffer = new TCHAR[size];
		 if(GetDefaultPrinter(buffer, &size))
		 {
				HDC hdcPrint;
				hdcPrint = CreateDC(NULL, buffer, NULL, NULL);
				
				x=::GetDeviceCaps(hdcPrint,PHYSICALOFFSETX);
				y=::GetDeviceCaps(hdcPrint,PHYSICALOFFSETY);
				
				x=(x * 25.4) /(double)::GetDeviceCaps(hdcPrint,LOGPIXELSX);
				y=(y * 25.4) /(double)::GetDeviceCaps(hdcPrint,LOGPIXELSY);

				DeleteDC(hdcPrint);
		 }
		 delete buffer;
	}

	if(!_controller)
	{
		TdkAbstractCanvasDraw*  canvas=new TdkGdiCanvasDraw(m_hWnd);
		_controller=new TdkLayoutController(canvas);

		TdkWin32LayoutClipboard *clipBoard=new TdkWin32LayoutClipboard(m_hWnd);
		_controller->setClipboard(clipBoard);

	}else if(!_controller->getCanvas())
	{
		TdkAbstractCanvasDraw*  canvas=new TdkGdiCanvasDraw(m_hWnd);
		_controller->setCanvas(canvas);

		TdkWin32LayoutClipboard *clipBoard=new TdkWin32LayoutClipboard(m_hWnd);
		_controller->setClipboard(clipBoard);
	}
	_controller->setMarginMinimum(x,y);
	_controller->update();
	_controller->refresh();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Resize Event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
LRESULT CTePrinter::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if(_controller)
	{
		m_clrBackColor=RGB(128,128,128);
		_controller->resize();
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Create Event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
LRESULT CTePrinter::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_clrBackColor=RGB(128,128,128);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Page Orientation (Get Property)
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::get_orientation(Orientation* pVal)
{
	if(_controller) *pVal=(Orientation)_controller->getPaperOrientation();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Page Orientation (Put Property)
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::put_orientation(Orientation newVal)
{
	if(_controller) _controller->setPaperOrientation((short)newVal);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Page Size ( Get Property )
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::get_paperSize(PaperSize* pVal)
{
	if(_controller)	*pVal=(PaperSize)_controller->getPaperSize();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Page Size ( Put Property )
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::put_paperSize(PaperSize newVal)
{
	if(_controller) _controller->setPaperSize((short)newVal);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Erase Background Event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
LRESULT CTePrinter::OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Add Text to Layout
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::addText(BSTR textValue)
{
	if(_controller) _controller->createText(TeBox(0,0,0,0),std::string(bstr_t(textValue)));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Left Mouse Button Down Event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
LRESULT CTePrinter::OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	TdkMouseEvent e;
	short num;

	e.X=(double)LOWORD(lParam); 
	e.Y=(double)HIWORD(lParam);
	e.Button=TdkMouseEvent::Left;
	num=GetKeyState(VK_CONTROL);
	if(_controller)	_controller->mouseDown(&e,((num & 0x80) ==0 ? false : true));
	setCursor(_cursor);
	this->Fire_atlMouseDown(0,(int)LOWORD(lParam),(int)HIWORD(lParam));
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Left Mouse Button Up Event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
LRESULT CTePrinter::OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	TdkMouseEvent e;
	short num;

	e.X=(double)LOWORD(lParam); 
	e.Y=(double)HIWORD(lParam);
	e.Button=TdkMouseEvent::Left;
	num=GetKeyState(VK_CONTROL);

	try
	{
		if(_controller)	_controller->mouseUp(&e,((num & 0x80) ==0 ? false : true));
	}catch(char *error)
	{
		setCursor(_cursor);
		return TdkWin32Error::DispatchError(E_FAIL,CLSID_TePrinter,_T("TePrinter"),LPCTSTR(error),0,0); 
	}
	catch(...)
	{

	}
	setCursor(_cursor);
	this->Fire_atlMouseUp(0,(LONG)LOWORD(lParam),(LONG)HIWORD(lParam));
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Right Mouse Button Donw Event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
LRESULT CTePrinter::OnRButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	TdkMouseEvent e;
	e.X=(double)LOWORD(lParam); 
	e.Y=(double)HIWORD(lParam);
	e.Button=TdkMouseEvent::Right;
	if(_controller)	_controller->mouseDown(&e);
	this->Fire_atlMouseDown(1,(int)LOWORD(lParam),(int)HIWORD(lParam));
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Right Mouse Button Up Event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
LRESULT CTePrinter::OnRButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	TdkMouseEvent e;
	e.X=(double)LOWORD(lParam); 
	e.Y=(double)HIWORD(lParam);
	e.Button=TdkMouseEvent::Right;
	if(_controller)	_controller->mouseUp(&e,false);
	this->Fire_atlMouseUp(1,(LONG)LOWORD(lParam),(LONG)HIWORD(lParam));
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Mouse Wheel Event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
LRESULT CTePrinter::OnMouseWheel(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	int		delta;
		
	delta = (int) wParam; 
	if(_controller)		
	{
		_controller->zoom(delta);
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Key Press Event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
LRESULT CTePrinter::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
		short num;

	num=GetKeyState(VK_CONTROL);
	if(_controller) _controller->keyDown((long)wParam,((num & 0x80) ==0 ? false : true));
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Accelerator Key Event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
BOOL CTePrinter::PreTranslateAccelerator(LPMSG pMsg, HRESULT& /*hRet*/)
{
	short num;
	if(pMsg->message == WM_KEYDOWN && 
		(pMsg->wParam == VK_LEFT || pMsg->wParam == VK_RIGHT ||  
		pMsg->wParam == VK_UP ||    pMsg->wParam == VK_DOWN))
      {
		num=GetKeyState(VK_CONTROL);
		if(_controller)	_controller->moveKey((moveKeys)pMsg->wParam,((num & 0x80) ==0 ? false : true));
         return TRUE;
      }
      return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//Key Up Event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
LRESULT CTePrinter::OnKeyUp(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	short num;

	num=GetKeyState(VK_CONTROL);
	if(_controller) _controller->keyUp((long)wParam,((num & 0x80) ==0 ? false : true));
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Mouse Move Event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
LRESULT CTePrinter::OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	TdkMouseEvent e;
	e.X=(double)LOWORD(lParam);  
	e.Y=(double)HIWORD(lParam);
	if(_controller)	_controller->mouseMove(&e);
	setCursor(_cursor);
	this->Fire_atlMouseMove((LONG)LOWORD(lParam),(LONG)HIWORD(lParam));
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Set Layout Objects Alignment
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::setAlign(TdkAlignment value)
{
	if(_controller)	_controller->setAlignment(value);
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////
//Sets mouse cursor mode
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

void CTePrinter::setCursor(const cursorMode &cursor)
{
	HINSTANCE	hInst = (HINSTANCE) _AtlBaseModule.m_hInst;
	HCURSOR		hcursor;

	switch(cursor)
	{
		case CursorNormal:	SetCursor(LoadCursor(NULL, IDC_ARROW));
							break;
		case CursorWait:	SetCursor(LoadCursor(NULL, IDC_WAIT));
							break;
		case CursorCross:	SetCursor(LoadCursor(NULL, IDC_CROSS));
							break;
		case CursorNWSE:	SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
							break;
		case CursorNESW:	SetCursor(LoadCursor(NULL, IDC_SIZENESW));
							break;
		case CursorWE:		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
							break;
		case CursorNS:		SetCursor(LoadCursor(NULL, IDC_SIZENS));
							break;
		case CursorAll:		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
							break;
		case CursorFinger:	SetCursor(LoadCursor(NULL, IDC_HAND));
							break;
		case CursorHand:	hcursor=LoadCursor(hInst,MAKEINTRESOURCE(IDC_MOUSEHAND));
							if(hcursor)		SetCursor(hcursor);
							else			SetCursor(LoadCursor(NULL, IDC_HAND));
							break;
		case CursorZoom:	hcursor=LoadCursor(hInst,MAKEINTRESOURCE(IDC_ZOOM));
							if(hcursor)		SetCursor(hcursor);
							else			SetCursor(LoadCursor(NULL, IDC_ARROW));
							break;
		case CursorZoomOut:	hcursor=LoadCursor(hInst,MAKEINTRESOURCE(IDC_ZOOMOUT));
							if(hcursor)		SetCursor(hcursor);
							else			SetCursor(LoadCursor(NULL, IDC_ARROW));
							break;
					
							
	}
	_cursor=cursor;
}		
///////////////////////////////////////////////////////////////////////////////
//Set Cursor Event
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

LRESULT CTePrinter::OnSetCursor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Print all layout objects
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::printExecute(BSTR printTitle,VARIANT_BOOL* result)
{
	double			x,y;
	std::string		title;
	PRINTDLG		printDlg;
	wchar_t			*pwc=0;

	ZeroMemory(&printDlg, sizeof(printDlg));
	printDlg.lStructSize = sizeof(printDlg);
	printDlg.Flags = PD_RETURNDC;

	if(printTitle != 0 ) title=std::string(bstr_t(printTitle));

	DOCINFO docInfo;
	ZeroMemory(&docInfo, sizeof(docInfo));
	docInfo.cbSize = sizeof(docInfo);
	if(title.empty())			docInfo.lpszDocName =L"TerraLib Layout";
	else						
	{
		pwc=(wchar_t *)malloc( sizeof( wchar_t ) * title.size() + 1 );
		for(unsigned int i=0;i<title.size();i++) pwc[i]=title[i];
		pwc[title.size()]=0;
		docInfo.lpszDocName=pwc;
	}
	
	// Display a print dialog box.
	if(!PrintDlg(&printDlg))
	{
		*result=false;
	}
	else
	{
		LPDEVMODE dev = (LPDEVMODE)::GlobalLock(printDlg.hDevMode);
		
		/*if(_controller)
		{
			double w,h;
			dev->dmFields|=DM_PAPERSIZE | DM_PAPERLENGTH | DM_PAPERWIDTH;
			dev->dmPaperSize=256;
			_controller->getPaperSize(w,h);
			dev->dmPaperLength=(short)(h * 10);
			dev->dmPaperWidth=(short)(w * 10);
			dev->dmFields|=DM_ORIENTATION;
			dev->dmOrientation=1;
		}*/
		
		double dpiRatio=300.0/dev->dmPrintQuality;
		GlobalUnlock(dev);
		//::ResetDC(printDlg.hDC,dev);


		x=::GetDeviceCaps(printDlg.hDC,PHYSICALOFFSETX);
		y=::GetDeviceCaps(printDlg.hDC,PHYSICALOFFSETY);
		x=(x * 25.4) /(double)::GetDeviceCaps(printDlg.hDC,LOGPIXELSX);
		y=(y * 25.4) /(double)::GetDeviceCaps(printDlg.hDC,LOGPIXELSY);
		
		StartDoc(printDlg.hDC, &docInfo);
		StartPage(printDlg.hDC);
		
		TdkAbstractCanvasDraw*  canvas=new TdkGdiCanvasDraw(printDlg.hDC,dpiRatio);
		if(_controller)	_controller->print(canvas,x,y);
		delete canvas;
		EndPage(printDlg.hDC);
		EndDoc(printDlg.hDC); 
		*result=true;
	}
   
	if(printDlg.hDevMode)		GlobalFree(printDlg.hDevMode);
	if(printDlg.hDevNames)		GlobalFree(printDlg.hDevNames);
	if(printDlg.hDC)			DeleteDC(printDlg.hDC);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Adds a new image object to layout
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTePrinter::addImage(BSTR fileName)
{
	std::string fName;
	if(fileName)	fName=std::string(bstr_t(fileName));
	if(_controller) _controller->createImage(fName);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Adds a new map object to layout
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTePrinter::addMap(BSTR viewName, BSTR userName, DOUBLE x1, DOUBLE y1, DOUBLE x2, DOUBLE y2)
{
	std::string	name;
	std::string view;

	if(userName)	name=std::string(bstr_t(userName));
	if(viewName)	view=std::string(bstr_t(viewName));
	if(_controller) _controller->createMap(view,name,TeBox(x1,y1,x2,y2),TeBox());
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////
//Returns the connection pointer
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTePrinter::get_connection(VARIANT* pVal)
{
	*pVal=_connection;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Sets the connection pointer
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTePrinter::put_connection(VARIANT newVal)
{
	TeDatabase *database=NULL;
	_connection=newVal;
	switch(_provider)
	{
		case SqlServer:
				{
					database=new TeSqlServer();
					((TeSqlServer*)database)->connection(newVal.pdispVal);
				} break;
			case Oracle:
				{
					database=new TeOracle();
					((TeOracle*)database)->connection(newVal.pdispVal);
				}break;
			case FireBird:
				{
					database=new TeFireBird();
					((TeFireBird*)database)->connection(newVal.pdispVal);
				}break;
			case PostgreSQL:
				{
					database = new TePostgreSQL(true);
					((TePostgreSQL*)database)->connect((PGconn*)newVal.ullVal);
				}break;
			default://conexao acces eh a default
				{
					database=new TeAdo();
					((TeAdo*)database)->connection(newVal.pdispVal);
				}
	}
	if(_controller && database) _controller->setDatabase(database);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the provider type
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::get_provider(connectionType* pVal)
{
	*pVal=_provider;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Sets the provider type
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::put_provider(connectionType newVal)
{
	_provider=newVal;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the quantity of layout object
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::getLayoutObjectCount(LONG* result)
{
	if(_controller) *result=_controller->getObjectCount();
	else			*result=0;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the object name according index value
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::getLayoutObjectName(LONG index, BSTR* result)
{
	CComBSTR	objName="";

	if(_controller)  objName=_controller->getObjectName((unsigned int)index).c_str();
	*result=objName.Copy();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the quantity of properties 
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::getLayoutObjectPropertiesCount(BSTR objectName, LONG* result)
{
	std::string object;
	*result=0;
	if(objectName)	object=std::string(bstr_t(objectName));
	if(_controller)	*result=_controller->getPropertiesCount(object);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the property name according index value
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::getLayoutObjectPropertyName(BSTR objectName, LONG index, BSTR* result)
{
	CComBSTR	propName="";
	std::string	object;
	if(objectName)	object=std::string(bstr_t(objectName));
	if(_controller) propName=_controller->getPropertyName(object,(unsigned int)index).c_str();
	*result=propName.Copy();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the property value according the index 
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::getLayoutObjectPropertyValue(BSTR objectName, LONG index, VARIANT* result)
{
	TdkAbstractProperty	*prop=NULL;
	if(_controller) prop=_controller->getPropertyValue(std::string(bstr_t(objectName)),index);
	TdkWin32Decoder::decoder(prop,result);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the property value according index value
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::setObjectPropertyValue(BSTR objName, LONG index, VARIANT value)
{
	TdkAbstractProperty	*prop=NULL;
	if(_controller) 
	{
		prop=_controller->getPropertyValue(std::string(bstr_t(objName)),index);
		TdkWin32Decoder::encoder(prop,value);
		_controller->associatePropertyObject(prop,std::string(bstr_t(objName)));
	}
	
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the quantity of select layout objects
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::getLayoutSelectObjectCount(LONG* result)
{
	if(_controller) *result=_controller->getSelectObjectCount();
	else			*result=0;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the select layout object name
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::getLayoutSelectObjectName(LONG index, BSTR* result)
{
	CComBSTR	objName="";

	if(_controller)  objName=_controller->getSelectObjectName((unsigned int)index).c_str();
	*result=objName.Copy();
	return S_OK;return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Sets the property value according object and property name
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::setObjectPropertyValueByName(BSTR objName, BSTR propertyName, VARIANT value)
{
	TdkAbstractProperty	*prop=NULL;
	if(_controller) 
	{
		prop=_controller->getPropertyValue(std::string(bstr_t(objName)),std::string(bstr_t(propertyName)));
		TdkWin32Decoder::encoder(prop,value);
		if(value.vt == VT_BSTR)
		{
			_controller->associatePropertyObject(prop,string(_bstr_t(value.bstrVal)));
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Sets the Map mode (Pan, Zoom In, Zoom Out)
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::setMapMode(MapMode mode)
{
	if(_controller)	_controller->setMapMode(mode);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Send the select objecto to back
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::sendObjectToBack(void)
{
	if(_controller)  _controller->sendToBack();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Bring the select objects to front
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::bringObjectToFront(void)
{
	if(_controller)  _controller->bringToFront();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Add a new rectangle object to layout
//Author : Rui Mauricio Gregório 
//Date : 07/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::addRectangle(void)
{
	if(_controller)	_controller->createRectangle();
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////
//Add a new ellipse object to layout
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::addEllipse(void)
{
	if(_controller)	_controller->createEllipse();
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////
//Add a new line object to layout
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::addLine(void)
{
	if(_controller)	_controller->createLine();
	
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Stop the all draw process
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::stopProcess(void)
{
	if(_controller) _controller->Stop();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Add Scale Object
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::addScale(void)
{
	if(_controller) _controller->createScale();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Property to return the left margin
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::get_leftMargin(DOUBLE* pVal)
{
	double left=0, top, right, bottom;
	if(_controller) _controller->getMargin(left,top,right,bottom);
	*pVal=left;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Property to set the left margin
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::put_leftMargin(DOUBLE newVal)
{
	double left, top, right, bottom;
	if(_controller) 
	{
		_controller->getMargin(left,top,right,bottom);
		_controller->setMargin(newVal,top,right,bottom);
	}
	

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Property to return the top margin
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::get_topMargin(DOUBLE* pVal)
{
	double left, top=0, right, bottom;
	if(_controller) _controller->getMargin(left,top,right,bottom);
	*pVal=top;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Property to set the top margin
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::put_topMargin(DOUBLE newVal)
{
	double left, top, right, bottom;
	if(_controller) 
	{
		_controller->getMargin(left,top,right,bottom);
		_controller->setMargin(left,newVal,right,bottom);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Property to return the bottom margin
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::get_bottomMargin(DOUBLE* pVal)
{
	double left, top, right, bottom=0;
	if(_controller) _controller->getMargin(left,top,right,bottom);
	*pVal=bottom;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Property to set the bottom margin
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::put_bottomMargin(DOUBLE newVal)
{
	double left, top, right, bottom;
	if(_controller) 
	{
		_controller->getMargin(left,top,right,bottom);
		_controller->setMargin(left,top,right,newVal);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Property to return the right margin
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::get_rightMargin(DOUBLE* pVal)
{
	double left, top, right, bottom=0;
	if(_controller) _controller->getMargin(left,top,right,bottom);
	*pVal=right;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Property to set the right margin
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::put_rightMargin(DOUBLE newVal)
{
	double left, top, right, bottom;
	if(_controller) 
	{
		_controller->getMargin(left,top,right,bottom);
		_controller->setMargin(left,top,newVal,bottom);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Select the object by your name
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::selectObject(BSTR objectName, VARIANT_BOOL* result)
{
	std::string	object;
	*result=false;
	if(objectName)	object=std::string(bstr_t(objectName));
	if(_controller)	*result=_controller->select(object);
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////
//Add Nort Object to Map
//Author : Rui Mauricio Gregório 
//Date : 03/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::addNorth(void)
{
	WCHAR			path[2048];
	std::string		fullPath;

	::GetModuleFileName(NULL,path,2048);
	fullPath=getApplicationPath(path);

	if(_controller) _controller->createNorth(fullPath);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Set Displacement to x axle
//Author : Rui Mauricio Gregório 
//Date : 03/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::hrzDisplacement(DOUBLE value)
{
	if(_controller) _controller->hDisplacement(value);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Sets displacement to y axle
//Author : Rui Mauricio Gregório 
//Date : 03/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::vrtDisplacement(DOUBLE value)
{
	if(_controller) _controller->vDisplacement(value);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Fit paper 
//Author : Rui Mauricio Gregório 
//Date : 03/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::recompose(void)
{
	if(_controller) _controller->recompose();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Return the width client area
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTePrinter::get_wClientArea(LONG* pVal)
{
	if(_controller)
	{
		*pVal=(LONG)(_controller->getBoundingBox().width());
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Return the height client area
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTePrinter::get_hClientArea(LONG* pVal)
{
	if(_controller)
	{
		*pVal=(LONG)(_controller->getBoundingBox().height());
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the layout zoom factor
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTePrinter::get_zoomFactor(DOUBLE* pVal)
{
	if(_controller) *pVal=_controller->getZoomFactor();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Sets the zoom factor value
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTePrinter::put_zoomFactor(DOUBLE newVal)
{
	if(_controller) _controller->setZoomFactor((double)newVal);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Gets the center of visible area on axle x
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::get_centerVisibleAreaX(LONG* pVal)
{
	if(_controller) *pVal=(LONG)_controller->getCenterViewPortWindow().x();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Gets the center of visible area on axle y
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::get_centerVisibleAreaY(LONG* pVal)
{
	if(_controller) *pVal=(LONG)_controller->getCenterViewPortWindow().y();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Remove the selected itens from layout
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::removeSelectedItems(void)
{	
	if(_controller) _controller->removeSelectedItems();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the object type
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::getLayoutObjectType(BSTR objectName, objectType* result)
{
	std::string	objName;
	if(objectName)	objName=std::string(bstr_t(objectName));
	if(_controller) *result=_controller->getObjectType(objName);
	else			*result=LT_UNDEFINED;
	return S_OK;
}


///////////////////////////////////////////////////////////////////////////////
//Sets the layout mode
//Author : Rui Mauricio Gregório 
//Date : 05/2010
///////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTePrinter::setLayoutMode(layoutMode mode)
{
	if(_controller)	_controller->setLayoutMode((TdkLayoutController::pageProcess)mode);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the property type
//Author : Rui Mauricio Gregório 
//Date : 07/2010
///////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTePrinter::getLayoutPropertyType(BSTR objectName, BSTR propertyName, propertyType* result)
{
	std::string		objName;
	std::string		propName;
	*result=PNumber;
	if(objectName)	objName=std::string(bstr_t(objectName));
	if(propertyName) propName=std::string(bstr_t(propertyName));
	if(_controller)	*result=_controller->getPropertyType(objName,propName);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Force the full update 
//Author : Rui Mauricio Gregório 
//Date : 07/2010
///////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTePrinter::forceFullUpdate(void)
{
	if(_controller) _controller->fullRedraw();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//add a Database layout object
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::addDatabase(void)
{
	//std::string		fullFileName;
	//WCHAR			path[2048];

	/*::GetModuleFileName(NULL,path,2048);
	fullFileName=getApplicationPath(path);
	fullFileName+="databaseImage.png";
	TdkAbstractImage *logo=new TdkGdiImage(fullFileName); */
	if(_controller) _controller->createDatabase();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Save layout to xml file
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::save(BSTR fileName, VARIANT_BOOL* result)
{
	if(_controller)	*result=_controller->save(std::string(bstr_t(fileName)));
	else			*result=false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Open a Xml File
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::open(BSTR fileName, VARIANT_BOOL* result)
{
	if(_controller)	*result=_controller->open(std::string(bstr_t(fileName)));
	else			*result=false;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Create a new empty page layout
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

STDMETHODIMP CTePrinter::newEmptyPage(void)
{
	if(_controller)
	{
		_controller->newPage();
		_controller->recompose();
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Add Multi Line Text to Layout
//Author : Rui Mauricio Gregório 
//Date : 06/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::addMText(BSTR textValue)
{
	if(_controller) _controller->createMText(TeBox(0,0,0,0),std::string(bstr_t(textValue)));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Add Political Division to Layout
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::addPoliticalDivision(void)
{
	if(_controller) _controller->createPoliticalDivision(TeBox(0,0,0,0));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Copy Layout Objects to Clipboard
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::copyToClipboard(void)
{
	if(_controller) _controller->copyToClipboard();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//Paste Layout Objects from Cipboard
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::pasteFromClipboard(void)
{
	if(_controller) _controller->pasteFromClipboard();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//clipboardIsEmpty
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::clipboardIsEmpty(VARIANT_BOOL* result)
{
	*result=false;
	if(_controller)		*result=(VARIANT_BOOL) _controller->clipboardIsEmpty();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//createBarcode
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::addBarcode(BSTR textValue)
{
	if(_controller) _controller->createBarcode(TeBox(0,0,0,0),std::string(bstr_t(textValue)));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//addVLineControl
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::addVLineControl(void)
{
	if(_controller) _controller->createVLineControl(TeBox(0,0,0));
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//addHLineControl
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
STDMETHODIMP CTePrinter::addHLineControl(void)
{
	if(_controller) _controller->createHLineControl(TeBox(0,0,0));
	return S_OK;
}
