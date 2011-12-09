// TePrinter.h : Declaration of the CTePrinter
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "TeComPrinter.h"
#include "_ITePrinterEvents_CP.h"
#include <TdkAbstractCursor.h>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

class TdkLayoutController;

// CTePrinter
class ATL_NO_VTABLE CTePrinter :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CTePrinter, ITePrinter>,
	public IPersistStreamInitImpl<CTePrinter>,
	public IOleControlImpl<CTePrinter>,
	public IOleObjectImpl<CTePrinter>,
	public IOleInPlaceActiveObjectImpl<CTePrinter>,
	public IViewObjectExImpl<CTePrinter>,
	public IOleInPlaceObjectWindowlessImpl<CTePrinter>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CTePrinter>,
	public CProxy_ITePrinterEvents<CTePrinter>,
	public IPersistStorageImpl<CTePrinter>,
	public ISpecifyPropertyPagesImpl<CTePrinter>,
	public IQuickActivateImpl<CTePrinter>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CTePrinter>,
#endif
	public IProvideClassInfo2Impl<&CLSID_TePrinter, &__uuidof(_ITePrinterEvents), &LIBID_TeComPrinterLib>,
#ifdef _WIN32_WCE // IObjectSafety is required on Windows CE for the control to be loaded correctly
	public IObjectSafetyImpl<CTePrinter, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
#endif
	public CComCoClass<CTePrinter, &CLSID_TePrinter>,
	public CComControl<CTePrinter>,
	public TdkAbstractCursor
{
public:


	CTePrinter();

	~CTePrinter();

	virtual void setCursor(const cursorMode &cursor);

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_TEPRINTER)


BEGIN_COM_MAP(CTePrinter)
	COM_INTERFACE_ENTRY(ITePrinter)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
#ifdef _WIN32_WCE // IObjectSafety is required on Windows CE for the control to be loaded correctly
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
#endif
END_COM_MAP()

BEGIN_PROP_MAP(CTePrinter)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
#ifndef _WIN32_WCE
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
#endif
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CTePrinter)
	CONNECTION_POINT_ENTRY(__uuidof(_ITePrinterEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CTePrinter)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
	MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
	MESSAGE_HANDLER(WM_RBUTTONUP, OnRButtonUp)
	MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
	MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	CHAIN_MSG_MAP(CComControl<CTePrinter>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] =
		{
			&IID_ITePrinter,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// ITePrinter
public :
	OLE_COLOR				m_clrBackColor;
	
	TdkLayoutController*	_controller;

	VARIANT					_connection;

	connectionType			_provider;

	cursorMode				_cursor;
public:
	HRESULT OnDrawAdvanced(ATL_DRAWINFO& di);
		
	
	void OnBackColorChanged()
	{
		ATLTRACE(_T("OnBackColorChanged\n"));
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
	STDMETHOD(execute)(void);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	STDMETHOD(get_orientation)(Orientation* pVal);
	STDMETHOD(put_orientation)(Orientation newVal);
	STDMETHOD(get_paperSize)(PaperSize* pVal);
	STDMETHOD(put_paperSize)(PaperSize newVal);
	
	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	STDMETHOD(addText)(/*[in]*/ BSTR textValue);
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnRButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnRButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseWheel(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnKeyUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	BOOL PreTranslateAccelerator(LPMSG /*pMsg*/, HRESULT& /*hRet*/);

	STDMETHOD(setAlign)(TdkAlignment value);
	LRESULT OnSetCursor(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	STDMETHOD(printExecute)(BSTR printTitle, VARIANT_BOOL* result);
	STDMETHOD(addImage)(/*[in]*/ BSTR fileName);
	STDMETHOD(get_connection)(VARIANT* pVal);
	STDMETHOD(put_connection)(VARIANT newVal);
	STDMETHOD(get_provider)(connectionType* pVal);
	STDMETHOD(put_provider)(connectionType newVal);
	STDMETHOD(addMap)(BSTR viewName, BSTR userName, DOUBLE x1, DOUBLE y1, DOUBLE x2, DOUBLE y2);
	STDMETHOD(getLayoutObjectCount)(LONG* result);
	STDMETHOD(getLayoutObjectName)(LONG index, BSTR* result);
	STDMETHOD(getLayoutObjectPropertiesCount)(BSTR objectName, LONG* result);
	STDMETHOD(getLayoutObjectPropertyName)(BSTR objectName, LONG index, BSTR* result);
	STDMETHOD(getLayoutObjectPropertyValue)(BSTR objectName, LONG index, VARIANT* result);
	STDMETHOD(setObjectPropertyValue)(BSTR objName, LONG index, VARIANT value);
	STDMETHOD(getLayoutSelectObjectCount)(LONG* result);
	STDMETHOD(getLayoutSelectObjectName)(LONG index, BSTR* result);
	STDMETHOD(setObjectPropertyValueByName)(BSTR objName, BSTR propertyName, VARIANT value);
	STDMETHOD(setMapMode)(MapMode mode);
	STDMETHOD(sendObjectToBack)(void);
	STDMETHOD(bringObjectToFront)(void);
	STDMETHOD(addRectangle)(void);
	STDMETHOD(addEllipse)(void);
	STDMETHOD(addLine)(void);
	STDMETHOD(stopProcess)(void);
	STDMETHOD(addScale)(void);
	STDMETHOD(get_leftMargin)(DOUBLE* pVal);
	STDMETHOD(put_leftMargin)(DOUBLE newVal);
	STDMETHOD(get_topMargin)(DOUBLE* pVal);
	STDMETHOD(put_topMargin)(DOUBLE newVal);
	STDMETHOD(get_bottomMargin)(DOUBLE* pVal);
	STDMETHOD(put_bottomMargin)(DOUBLE newVal);
	STDMETHOD(get_rightMargin)(DOUBLE* pVal);
	STDMETHOD(put_rightMargin)(DOUBLE newVal);
	STDMETHOD(selectObject)(BSTR objectName, VARIANT_BOOL* result);
	STDMETHOD(addNorth)(void);
	STDMETHOD(hrzDisplacement)(DOUBLE value);
	STDMETHOD(vrtDisplacement)(DOUBLE value);
	STDMETHOD(recompose)(void);
	STDMETHOD(get_wClientArea)(LONG* pVal);
	STDMETHOD(get_hClientArea)(LONG* pVal);
	STDMETHOD(get_zoomFactor)(DOUBLE* pVal);
	STDMETHOD(put_zoomFactor)(DOUBLE newVal);
	STDMETHOD(get_centerVisibleAreaX)(LONG* pVal);
	STDMETHOD(get_centerVisibleAreaY)(LONG* pVal);
	STDMETHOD(removeSelectedItems)(void);
	STDMETHOD(getLayoutObjectType)(BSTR objectName, objectType* result);
	STDMETHOD(setLayoutMode)(layoutMode mode);
	STDMETHOD(getLayoutPropertyType)(BSTR objectName, BSTR propertyName, propertyType* result);
	STDMETHOD(forceFullUpdate)(void);
	STDMETHOD(addDatabase)(void);
	STDMETHOD(save)(BSTR fileName, VARIANT_BOOL* result);
	STDMETHOD(open)(BSTR fileName, VARIANT_BOOL* result);
	STDMETHOD(newEmptyPage)(void);
	STDMETHOD(addMText)(BSTR textValue);
	STDMETHOD(addPoliticalDivision)(void);
	STDMETHOD(copyToClipboard)(void);
	STDMETHOD(pasteFromClipboard)(void);
	STDMETHOD(clipboardIsEmpty)(VARIANT_BOOL* result);
	STDMETHOD(addBarcode)(BSTR textValue);
	STDMETHOD(addVLineControl)(void);
	STDMETHOD(addHLineControl)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(TePrinter), CTePrinter)
