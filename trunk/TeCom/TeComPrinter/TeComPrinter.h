

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Mon Dec 05 15:39:26 2011
 */
/* Compiler settings for .\TeComPrinter.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __TeComPrinter_h__
#define __TeComPrinter_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ITePrinter_FWD_DEFINED__
#define __ITePrinter_FWD_DEFINED__
typedef interface ITePrinter ITePrinter;
#endif 	/* __ITePrinter_FWD_DEFINED__ */


#ifndef ___ITePrinterEvents_FWD_DEFINED__
#define ___ITePrinterEvents_FWD_DEFINED__
typedef interface _ITePrinterEvents _ITePrinterEvents;
#endif 	/* ___ITePrinterEvents_FWD_DEFINED__ */


#ifndef __TePrinter_FWD_DEFINED__
#define __TePrinter_FWD_DEFINED__

#ifdef __cplusplus
typedef class TePrinter TePrinter;
#else
typedef struct TePrinter TePrinter;
#endif /* __cplusplus */

#endif 	/* __TePrinter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_TeComPrinter_0000 */
/* [local] */ 

typedef 
enum pageOrientation
    {	portrait	= 0,
	landscape	= 1
    } 	Orientation;

typedef 
enum pageSize
    {	A0	= 0,
	A1	= 1,
	A2	= 2,
	A3	= 3,
	A4	= 4,
	A5	= 5,
	A6	= 6,
	Custom	= 7
    } 	PaperSize;

typedef 
enum Alignment
    {	Left_Align	= 0,
	Right_Align	= 1,
	Top_Align	= 2,
	Bottom_Align	= 3,
	Horizontal_Center_Align	= 4,
	Vertical_Center_Align	= 5
    } 	TdkAlignment;

typedef 
enum horizontalTextAlignment
    {	hLeft	= 0,
	hCenter	= 1,
	hRight	= 2
    } 	hrzTextAlign;

typedef 
enum verticalTextAlignment
    {	vTop	= 0,
	vCenter	= 1,
	vBottom	= 2
    } 	vertTextAlign;

typedef 
enum MOVE_KEYS
    {	TDK_LEFT	= 0x25,
	TDK_UP	= 0x26,
	TDK_RIGHT	= 0x27,
	TDK_DOWN	= 0x28
    } 	moveKeys;

typedef 
enum HOT_POINTS
    {	LeftTop	= 0,
	MiddleTop	= 1,
	RightTop	= 2,
	MiddleRight	= 3,
	RightBottom	= 4,
	MiddleBottom	= 5,
	LeftBottom	= 6,
	MiddleLeft	= 7,
	NonePoint	= 8,
	RotatePoint	= 9
    } 	hotPoint;

typedef 
enum CURSOR_MODE
    {	CursorNormal	= 0,
	CursorWait	= 1,
	CursorCross	= 2,
	CursorNWSE	= 3,
	CursorNESW	= 4,
	CursorWE	= 5,
	CursorNS	= 6,
	CursorAll	= 7,
	CursorHand	= 8,
	CursorZoom	= 9,
	CursorZoomOut	= 10,
	CursorFinger	= 11
    } 	cursorMode;

typedef 
enum CONNECTION_TYPE
    {	Access	= 0,
	SqlServer	= 1,
	Oracle	= 2,
	FireBird	= 3,
	PostgreSQL	= 4
    } 	connectionType;

typedef 
enum MAP_MODE
    {	None	= 0,
	Pan	= 1,
	ZoomIn	= 2,
	ZoomOut	= 3,
	ZoomArea	= 4,
	FullExtend	= 5
    } 	MapMode;

typedef 
enum LAYOUT_MODE
    {	LNone	= 0,
	LZoomOut	= 1,
	LZoomArea	= 2,
	LPan	= 3
    } 	layoutMode;

typedef 
enum PROPERTY_TYPE
    {	PNumber	= 0,
	PBoolean	= 1,
	PText	= 2,
	PColor	= 3,
	PBinary	= 4
    } 	propertyType;

typedef 
enum LAYOUT_TYPES
    {	LT_UNDEFINED	= -1,
	LT_LINE	= 0,
	LT_RECTANGLE	= 1,
	LT_ELLIPSE	= 2,
	LT_IMAGE	= 3,
	LT_TEXT	= 4,
	LT_SCALE	= 5,
	LT_NORTH	= 6,
	LT_MAP	= 7,
	LT_DATABASE	= 8,
	LT_MTEXT	= 9,
	LT_POLITICALDIVISION	= 10,
	LT_BARCODE	= 11,
	LT_VLINE_CONTROL	= 12,
	LT_HLINE_CONTROL	= 13
    } 	objectType;



extern RPC_IF_HANDLE __MIDL_itf_TeComPrinter_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_TeComPrinter_0000_v0_0_s_ifspec;

#ifndef __ITePrinter_INTERFACE_DEFINED__
#define __ITePrinter_INTERFACE_DEFINED__

/* interface ITePrinter */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITePrinter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3D1C2BB1-6D87-42CA-A681-BBA7697031F8")
    ITePrinter : public IDispatch
    {
    public:
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE execute( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_orientation( 
            /* [retval][out] */ Orientation *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_orientation( 
            /* [in] */ Orientation newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_paperSize( 
            /* [retval][out] */ PaperSize *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_paperSize( 
            /* [in] */ PaperSize newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addText( 
            /* [defaultvalue][in] */ BSTR textValue = L"") = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setAlign( 
            /* [in] */ TdkAlignment value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE printExecute( 
            /* [in] */ BSTR printTitle,
            /* [retval][out] */ VARIANT_BOOL *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addImage( 
            /* [in] */ BSTR fileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_connection( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_connection( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_provider( 
            /* [retval][out] */ connectionType *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_provider( 
            /* [in] */ connectionType newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addMap( 
            /* [in] */ BSTR viewName,
            /* [defaultvalue][in] */ BSTR userName = L"",
            /* [defaultvalue][in] */ DOUBLE x1 = 3.4e+037,
            /* [defaultvalue][in] */ DOUBLE y1 = 3.4e+037,
            /* [defaultvalue][in] */ DOUBLE x2 = -3.4e+037,
            /* [defaultvalue][in] */ DOUBLE y2 = -3.4e+037) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLayoutObjectCount( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLayoutObjectName( 
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLayoutObjectPropertiesCount( 
            /* [in] */ BSTR objectName,
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLayoutObjectPropertyName( 
            /* [in] */ BSTR objectName,
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLayoutObjectPropertyValue( 
            /* [in] */ BSTR objectName,
            /* [in] */ LONG index,
            /* [retval][out] */ VARIANT *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setObjectPropertyValue( 
            /* [in] */ BSTR objName,
            /* [in] */ LONG index,
            /* [in] */ VARIANT value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLayoutSelectObjectCount( 
            /* [retval][out] */ LONG *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLayoutSelectObjectName( 
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setObjectPropertyValueByName( 
            /* [in] */ BSTR objName,
            /* [in] */ BSTR propertyName,
            /* [in] */ VARIANT value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setMapMode( 
            /* [in] */ MapMode mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE sendObjectToBack( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE bringObjectToFront( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addRectangle( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addEllipse( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addLine( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE stopProcess( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addScale( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_leftMargin( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_leftMargin( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_topMargin( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_topMargin( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_bottomMargin( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_bottomMargin( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_rightMargin( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_rightMargin( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE selectObject( 
            /* [in] */ BSTR objectName,
            /* [retval][out] */ VARIANT_BOOL *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addNorth( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE hrzDisplacement( 
            /* [in] */ DOUBLE value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE vrtDisplacement( 
            /* [in] */ DOUBLE value) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE recompose( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_wClientArea( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hClientArea( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_zoomFactor( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_zoomFactor( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_centerVisibleAreaX( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_centerVisibleAreaY( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE removeSelectedItems( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLayoutObjectType( 
            /* [in] */ BSTR objectName,
            /* [retval][out] */ objectType *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE setLayoutMode( 
            /* [in] */ layoutMode mode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE getLayoutPropertyType( 
            /* [in] */ BSTR objectName,
            /* [in] */ BSTR propertyName,
            /* [retval][out] */ propertyType *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE forceFullUpdate( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addDatabase( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE save( 
            /* [in] */ BSTR fileName,
            /* [retval][out] */ VARIANT_BOOL *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE open( 
            /* [in] */ BSTR fileName,
            /* [retval][out] */ VARIANT_BOOL *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE newEmptyPage( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addMText( 
            /* [in] */ BSTR textValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addPoliticalDivision( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE copyToClipboard( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE pasteFromClipboard( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE clipboardIsEmpty( 
            /* [retval][out] */ VARIANT_BOOL *result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addBarcode( 
            /* [in] */ BSTR textValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addVLineControl( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE addHLineControl( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITePrinterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ITePrinter * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ITePrinter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ITePrinter * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ITePrinter * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ITePrinter * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ITePrinter * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ITePrinter * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            ITePrinter * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            ITePrinter * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *execute )( 
            ITePrinter * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_orientation )( 
            ITePrinter * This,
            /* [retval][out] */ Orientation *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_orientation )( 
            ITePrinter * This,
            /* [in] */ Orientation newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_paperSize )( 
            ITePrinter * This,
            /* [retval][out] */ PaperSize *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_paperSize )( 
            ITePrinter * This,
            /* [in] */ PaperSize newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addText )( 
            ITePrinter * This,
            /* [defaultvalue][in] */ BSTR textValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setAlign )( 
            ITePrinter * This,
            /* [in] */ TdkAlignment value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *printExecute )( 
            ITePrinter * This,
            /* [in] */ BSTR printTitle,
            /* [retval][out] */ VARIANT_BOOL *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addImage )( 
            ITePrinter * This,
            /* [in] */ BSTR fileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_connection )( 
            ITePrinter * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_connection )( 
            ITePrinter * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_provider )( 
            ITePrinter * This,
            /* [retval][out] */ connectionType *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_provider )( 
            ITePrinter * This,
            /* [in] */ connectionType newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addMap )( 
            ITePrinter * This,
            /* [in] */ BSTR viewName,
            /* [defaultvalue][in] */ BSTR userName,
            /* [defaultvalue][in] */ DOUBLE x1,
            /* [defaultvalue][in] */ DOUBLE y1,
            /* [defaultvalue][in] */ DOUBLE x2,
            /* [defaultvalue][in] */ DOUBLE y2);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLayoutObjectCount )( 
            ITePrinter * This,
            /* [retval][out] */ LONG *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLayoutObjectName )( 
            ITePrinter * This,
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLayoutObjectPropertiesCount )( 
            ITePrinter * This,
            /* [in] */ BSTR objectName,
            /* [retval][out] */ LONG *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLayoutObjectPropertyName )( 
            ITePrinter * This,
            /* [in] */ BSTR objectName,
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLayoutObjectPropertyValue )( 
            ITePrinter * This,
            /* [in] */ BSTR objectName,
            /* [in] */ LONG index,
            /* [retval][out] */ VARIANT *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setObjectPropertyValue )( 
            ITePrinter * This,
            /* [in] */ BSTR objName,
            /* [in] */ LONG index,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLayoutSelectObjectCount )( 
            ITePrinter * This,
            /* [retval][out] */ LONG *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLayoutSelectObjectName )( 
            ITePrinter * This,
            /* [in] */ LONG index,
            /* [retval][out] */ BSTR *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setObjectPropertyValueByName )( 
            ITePrinter * This,
            /* [in] */ BSTR objName,
            /* [in] */ BSTR propertyName,
            /* [in] */ VARIANT value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setMapMode )( 
            ITePrinter * This,
            /* [in] */ MapMode mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *sendObjectToBack )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *bringObjectToFront )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addRectangle )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addEllipse )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addLine )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *stopProcess )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addScale )( 
            ITePrinter * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_leftMargin )( 
            ITePrinter * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_leftMargin )( 
            ITePrinter * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_topMargin )( 
            ITePrinter * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_topMargin )( 
            ITePrinter * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_bottomMargin )( 
            ITePrinter * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_bottomMargin )( 
            ITePrinter * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_rightMargin )( 
            ITePrinter * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_rightMargin )( 
            ITePrinter * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *selectObject )( 
            ITePrinter * This,
            /* [in] */ BSTR objectName,
            /* [retval][out] */ VARIANT_BOOL *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addNorth )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *hrzDisplacement )( 
            ITePrinter * This,
            /* [in] */ DOUBLE value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *vrtDisplacement )( 
            ITePrinter * This,
            /* [in] */ DOUBLE value);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *recompose )( 
            ITePrinter * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_wClientArea )( 
            ITePrinter * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_hClientArea )( 
            ITePrinter * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_zoomFactor )( 
            ITePrinter * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_zoomFactor )( 
            ITePrinter * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_centerVisibleAreaX )( 
            ITePrinter * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_centerVisibleAreaY )( 
            ITePrinter * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *removeSelectedItems )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLayoutObjectType )( 
            ITePrinter * This,
            /* [in] */ BSTR objectName,
            /* [retval][out] */ objectType *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *setLayoutMode )( 
            ITePrinter * This,
            /* [in] */ layoutMode mode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *getLayoutPropertyType )( 
            ITePrinter * This,
            /* [in] */ BSTR objectName,
            /* [in] */ BSTR propertyName,
            /* [retval][out] */ propertyType *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *forceFullUpdate )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addDatabase )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *save )( 
            ITePrinter * This,
            /* [in] */ BSTR fileName,
            /* [retval][out] */ VARIANT_BOOL *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *open )( 
            ITePrinter * This,
            /* [in] */ BSTR fileName,
            /* [retval][out] */ VARIANT_BOOL *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *newEmptyPage )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addMText )( 
            ITePrinter * This,
            /* [in] */ BSTR textValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addPoliticalDivision )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *copyToClipboard )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *pasteFromClipboard )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *clipboardIsEmpty )( 
            ITePrinter * This,
            /* [retval][out] */ VARIANT_BOOL *result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addBarcode )( 
            ITePrinter * This,
            /* [in] */ BSTR textValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addVLineControl )( 
            ITePrinter * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *addHLineControl )( 
            ITePrinter * This);
        
        END_INTERFACE
    } ITePrinterVtbl;

    interface ITePrinter
    {
        CONST_VTBL struct ITePrinterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITePrinter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITePrinter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITePrinter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITePrinter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITePrinter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITePrinter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITePrinter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITePrinter_put_BackColor(This,clr)	\
    (This)->lpVtbl -> put_BackColor(This,clr)

#define ITePrinter_get_BackColor(This,pclr)	\
    (This)->lpVtbl -> get_BackColor(This,pclr)

#define ITePrinter_execute(This)	\
    (This)->lpVtbl -> execute(This)

#define ITePrinter_get_orientation(This,pVal)	\
    (This)->lpVtbl -> get_orientation(This,pVal)

#define ITePrinter_put_orientation(This,newVal)	\
    (This)->lpVtbl -> put_orientation(This,newVal)

#define ITePrinter_get_paperSize(This,pVal)	\
    (This)->lpVtbl -> get_paperSize(This,pVal)

#define ITePrinter_put_paperSize(This,newVal)	\
    (This)->lpVtbl -> put_paperSize(This,newVal)

#define ITePrinter_addText(This,textValue)	\
    (This)->lpVtbl -> addText(This,textValue)

#define ITePrinter_setAlign(This,value)	\
    (This)->lpVtbl -> setAlign(This,value)

#define ITePrinter_printExecute(This,printTitle,result)	\
    (This)->lpVtbl -> printExecute(This,printTitle,result)

#define ITePrinter_addImage(This,fileName)	\
    (This)->lpVtbl -> addImage(This,fileName)

#define ITePrinter_get_connection(This,pVal)	\
    (This)->lpVtbl -> get_connection(This,pVal)

#define ITePrinter_put_connection(This,newVal)	\
    (This)->lpVtbl -> put_connection(This,newVal)

#define ITePrinter_get_provider(This,pVal)	\
    (This)->lpVtbl -> get_provider(This,pVal)

#define ITePrinter_put_provider(This,newVal)	\
    (This)->lpVtbl -> put_provider(This,newVal)

#define ITePrinter_addMap(This,viewName,userName,x1,y1,x2,y2)	\
    (This)->lpVtbl -> addMap(This,viewName,userName,x1,y1,x2,y2)

#define ITePrinter_getLayoutObjectCount(This,result)	\
    (This)->lpVtbl -> getLayoutObjectCount(This,result)

#define ITePrinter_getLayoutObjectName(This,index,result)	\
    (This)->lpVtbl -> getLayoutObjectName(This,index,result)

#define ITePrinter_getLayoutObjectPropertiesCount(This,objectName,result)	\
    (This)->lpVtbl -> getLayoutObjectPropertiesCount(This,objectName,result)

#define ITePrinter_getLayoutObjectPropertyName(This,objectName,index,result)	\
    (This)->lpVtbl -> getLayoutObjectPropertyName(This,objectName,index,result)

#define ITePrinter_getLayoutObjectPropertyValue(This,objectName,index,result)	\
    (This)->lpVtbl -> getLayoutObjectPropertyValue(This,objectName,index,result)

#define ITePrinter_setObjectPropertyValue(This,objName,index,value)	\
    (This)->lpVtbl -> setObjectPropertyValue(This,objName,index,value)

#define ITePrinter_getLayoutSelectObjectCount(This,result)	\
    (This)->lpVtbl -> getLayoutSelectObjectCount(This,result)

#define ITePrinter_getLayoutSelectObjectName(This,index,result)	\
    (This)->lpVtbl -> getLayoutSelectObjectName(This,index,result)

#define ITePrinter_setObjectPropertyValueByName(This,objName,propertyName,value)	\
    (This)->lpVtbl -> setObjectPropertyValueByName(This,objName,propertyName,value)

#define ITePrinter_setMapMode(This,mode)	\
    (This)->lpVtbl -> setMapMode(This,mode)

#define ITePrinter_sendObjectToBack(This)	\
    (This)->lpVtbl -> sendObjectToBack(This)

#define ITePrinter_bringObjectToFront(This)	\
    (This)->lpVtbl -> bringObjectToFront(This)

#define ITePrinter_addRectangle(This)	\
    (This)->lpVtbl -> addRectangle(This)

#define ITePrinter_addEllipse(This)	\
    (This)->lpVtbl -> addEllipse(This)

#define ITePrinter_addLine(This)	\
    (This)->lpVtbl -> addLine(This)

#define ITePrinter_stopProcess(This)	\
    (This)->lpVtbl -> stopProcess(This)

#define ITePrinter_addScale(This)	\
    (This)->lpVtbl -> addScale(This)

#define ITePrinter_get_leftMargin(This,pVal)	\
    (This)->lpVtbl -> get_leftMargin(This,pVal)

#define ITePrinter_put_leftMargin(This,newVal)	\
    (This)->lpVtbl -> put_leftMargin(This,newVal)

#define ITePrinter_get_topMargin(This,pVal)	\
    (This)->lpVtbl -> get_topMargin(This,pVal)

#define ITePrinter_put_topMargin(This,newVal)	\
    (This)->lpVtbl -> put_topMargin(This,newVal)

#define ITePrinter_get_bottomMargin(This,pVal)	\
    (This)->lpVtbl -> get_bottomMargin(This,pVal)

#define ITePrinter_put_bottomMargin(This,newVal)	\
    (This)->lpVtbl -> put_bottomMargin(This,newVal)

#define ITePrinter_get_rightMargin(This,pVal)	\
    (This)->lpVtbl -> get_rightMargin(This,pVal)

#define ITePrinter_put_rightMargin(This,newVal)	\
    (This)->lpVtbl -> put_rightMargin(This,newVal)

#define ITePrinter_selectObject(This,objectName,result)	\
    (This)->lpVtbl -> selectObject(This,objectName,result)

#define ITePrinter_addNorth(This)	\
    (This)->lpVtbl -> addNorth(This)

#define ITePrinter_hrzDisplacement(This,value)	\
    (This)->lpVtbl -> hrzDisplacement(This,value)

#define ITePrinter_vrtDisplacement(This,value)	\
    (This)->lpVtbl -> vrtDisplacement(This,value)

#define ITePrinter_recompose(This)	\
    (This)->lpVtbl -> recompose(This)

#define ITePrinter_get_wClientArea(This,pVal)	\
    (This)->lpVtbl -> get_wClientArea(This,pVal)

#define ITePrinter_get_hClientArea(This,pVal)	\
    (This)->lpVtbl -> get_hClientArea(This,pVal)

#define ITePrinter_get_zoomFactor(This,pVal)	\
    (This)->lpVtbl -> get_zoomFactor(This,pVal)

#define ITePrinter_put_zoomFactor(This,newVal)	\
    (This)->lpVtbl -> put_zoomFactor(This,newVal)

#define ITePrinter_get_centerVisibleAreaX(This,pVal)	\
    (This)->lpVtbl -> get_centerVisibleAreaX(This,pVal)

#define ITePrinter_get_centerVisibleAreaY(This,pVal)	\
    (This)->lpVtbl -> get_centerVisibleAreaY(This,pVal)

#define ITePrinter_removeSelectedItems(This)	\
    (This)->lpVtbl -> removeSelectedItems(This)

#define ITePrinter_getLayoutObjectType(This,objectName,result)	\
    (This)->lpVtbl -> getLayoutObjectType(This,objectName,result)

#define ITePrinter_setLayoutMode(This,mode)	\
    (This)->lpVtbl -> setLayoutMode(This,mode)

#define ITePrinter_getLayoutPropertyType(This,objectName,propertyName,result)	\
    (This)->lpVtbl -> getLayoutPropertyType(This,objectName,propertyName,result)

#define ITePrinter_forceFullUpdate(This)	\
    (This)->lpVtbl -> forceFullUpdate(This)

#define ITePrinter_addDatabase(This)	\
    (This)->lpVtbl -> addDatabase(This)

#define ITePrinter_save(This,fileName,result)	\
    (This)->lpVtbl -> save(This,fileName,result)

#define ITePrinter_open(This,fileName,result)	\
    (This)->lpVtbl -> open(This,fileName,result)

#define ITePrinter_newEmptyPage(This)	\
    (This)->lpVtbl -> newEmptyPage(This)

#define ITePrinter_addMText(This,textValue)	\
    (This)->lpVtbl -> addMText(This,textValue)

#define ITePrinter_addPoliticalDivision(This)	\
    (This)->lpVtbl -> addPoliticalDivision(This)

#define ITePrinter_copyToClipboard(This)	\
    (This)->lpVtbl -> copyToClipboard(This)

#define ITePrinter_pasteFromClipboard(This)	\
    (This)->lpVtbl -> pasteFromClipboard(This)

#define ITePrinter_clipboardIsEmpty(This,result)	\
    (This)->lpVtbl -> clipboardIsEmpty(This,result)

#define ITePrinter_addBarcode(This,textValue)	\
    (This)->lpVtbl -> addBarcode(This,textValue)

#define ITePrinter_addVLineControl(This)	\
    (This)->lpVtbl -> addVLineControl(This)

#define ITePrinter_addHLineControl(This)	\
    (This)->lpVtbl -> addHLineControl(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE ITePrinter_put_BackColor_Proxy( 
    ITePrinter * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB ITePrinter_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_BackColor_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB ITePrinter_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_execute_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_execute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_orientation_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ Orientation *pVal);


void __RPC_STUB ITePrinter_get_orientation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITePrinter_put_orientation_Proxy( 
    ITePrinter * This,
    /* [in] */ Orientation newVal);


void __RPC_STUB ITePrinter_put_orientation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_paperSize_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ PaperSize *pVal);


void __RPC_STUB ITePrinter_get_paperSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITePrinter_put_paperSize_Proxy( 
    ITePrinter * This,
    /* [in] */ PaperSize newVal);


void __RPC_STUB ITePrinter_put_paperSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addText_Proxy( 
    ITePrinter * This,
    /* [defaultvalue][in] */ BSTR textValue);


void __RPC_STUB ITePrinter_addText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_setAlign_Proxy( 
    ITePrinter * This,
    /* [in] */ TdkAlignment value);


void __RPC_STUB ITePrinter_setAlign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_printExecute_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR printTitle,
    /* [retval][out] */ VARIANT_BOOL *result);


void __RPC_STUB ITePrinter_printExecute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addImage_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR fileName);


void __RPC_STUB ITePrinter_addImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_connection_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB ITePrinter_get_connection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITePrinter_put_connection_Proxy( 
    ITePrinter * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB ITePrinter_put_connection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_provider_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ connectionType *pVal);


void __RPC_STUB ITePrinter_get_provider_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITePrinter_put_provider_Proxy( 
    ITePrinter * This,
    /* [in] */ connectionType newVal);


void __RPC_STUB ITePrinter_put_provider_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addMap_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR viewName,
    /* [defaultvalue][in] */ BSTR userName,
    /* [defaultvalue][in] */ DOUBLE x1,
    /* [defaultvalue][in] */ DOUBLE y1,
    /* [defaultvalue][in] */ DOUBLE x2,
    /* [defaultvalue][in] */ DOUBLE y2);


void __RPC_STUB ITePrinter_addMap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_getLayoutObjectCount_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ LONG *result);


void __RPC_STUB ITePrinter_getLayoutObjectCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_getLayoutObjectName_Proxy( 
    ITePrinter * This,
    /* [in] */ LONG index,
    /* [retval][out] */ BSTR *result);


void __RPC_STUB ITePrinter_getLayoutObjectName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_getLayoutObjectPropertiesCount_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR objectName,
    /* [retval][out] */ LONG *result);


void __RPC_STUB ITePrinter_getLayoutObjectPropertiesCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_getLayoutObjectPropertyName_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR objectName,
    /* [in] */ LONG index,
    /* [retval][out] */ BSTR *result);


void __RPC_STUB ITePrinter_getLayoutObjectPropertyName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_getLayoutObjectPropertyValue_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR objectName,
    /* [in] */ LONG index,
    /* [retval][out] */ VARIANT *result);


void __RPC_STUB ITePrinter_getLayoutObjectPropertyValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_setObjectPropertyValue_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR objName,
    /* [in] */ LONG index,
    /* [in] */ VARIANT value);


void __RPC_STUB ITePrinter_setObjectPropertyValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_getLayoutSelectObjectCount_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ LONG *result);


void __RPC_STUB ITePrinter_getLayoutSelectObjectCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_getLayoutSelectObjectName_Proxy( 
    ITePrinter * This,
    /* [in] */ LONG index,
    /* [retval][out] */ BSTR *result);


void __RPC_STUB ITePrinter_getLayoutSelectObjectName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_setObjectPropertyValueByName_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR objName,
    /* [in] */ BSTR propertyName,
    /* [in] */ VARIANT value);


void __RPC_STUB ITePrinter_setObjectPropertyValueByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_setMapMode_Proxy( 
    ITePrinter * This,
    /* [in] */ MapMode mode);


void __RPC_STUB ITePrinter_setMapMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_sendObjectToBack_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_sendObjectToBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_bringObjectToFront_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_bringObjectToFront_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addRectangle_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_addRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addEllipse_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_addEllipse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addLine_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_addLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_stopProcess_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_stopProcess_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addScale_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_addScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_leftMargin_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB ITePrinter_get_leftMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITePrinter_put_leftMargin_Proxy( 
    ITePrinter * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB ITePrinter_put_leftMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_topMargin_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB ITePrinter_get_topMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITePrinter_put_topMargin_Proxy( 
    ITePrinter * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB ITePrinter_put_topMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_bottomMargin_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB ITePrinter_get_bottomMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITePrinter_put_bottomMargin_Proxy( 
    ITePrinter * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB ITePrinter_put_bottomMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_rightMargin_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB ITePrinter_get_rightMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITePrinter_put_rightMargin_Proxy( 
    ITePrinter * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB ITePrinter_put_rightMargin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_selectObject_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR objectName,
    /* [retval][out] */ VARIANT_BOOL *result);


void __RPC_STUB ITePrinter_selectObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addNorth_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_addNorth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_hrzDisplacement_Proxy( 
    ITePrinter * This,
    /* [in] */ DOUBLE value);


void __RPC_STUB ITePrinter_hrzDisplacement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_vrtDisplacement_Proxy( 
    ITePrinter * This,
    /* [in] */ DOUBLE value);


void __RPC_STUB ITePrinter_vrtDisplacement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_recompose_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_recompose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_wClientArea_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITePrinter_get_wClientArea_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_hClientArea_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITePrinter_get_hClientArea_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_zoomFactor_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB ITePrinter_get_zoomFactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITePrinter_put_zoomFactor_Proxy( 
    ITePrinter * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB ITePrinter_put_zoomFactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_centerVisibleAreaX_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITePrinter_get_centerVisibleAreaX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITePrinter_get_centerVisibleAreaY_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB ITePrinter_get_centerVisibleAreaY_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_removeSelectedItems_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_removeSelectedItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_getLayoutObjectType_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR objectName,
    /* [retval][out] */ objectType *result);


void __RPC_STUB ITePrinter_getLayoutObjectType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_setLayoutMode_Proxy( 
    ITePrinter * This,
    /* [in] */ layoutMode mode);


void __RPC_STUB ITePrinter_setLayoutMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_getLayoutPropertyType_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR objectName,
    /* [in] */ BSTR propertyName,
    /* [retval][out] */ propertyType *result);


void __RPC_STUB ITePrinter_getLayoutPropertyType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_forceFullUpdate_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_forceFullUpdate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addDatabase_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_addDatabase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_save_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR fileName,
    /* [retval][out] */ VARIANT_BOOL *result);


void __RPC_STUB ITePrinter_save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_open_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR fileName,
    /* [retval][out] */ VARIANT_BOOL *result);


void __RPC_STUB ITePrinter_open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_newEmptyPage_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_newEmptyPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addMText_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR textValue);


void __RPC_STUB ITePrinter_addMText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addPoliticalDivision_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_addPoliticalDivision_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_copyToClipboard_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_copyToClipboard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_pasteFromClipboard_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_pasteFromClipboard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_clipboardIsEmpty_Proxy( 
    ITePrinter * This,
    /* [retval][out] */ VARIANT_BOOL *result);


void __RPC_STUB ITePrinter_clipboardIsEmpty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addBarcode_Proxy( 
    ITePrinter * This,
    /* [in] */ BSTR textValue);


void __RPC_STUB ITePrinter_addBarcode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addVLineControl_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_addVLineControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITePrinter_addHLineControl_Proxy( 
    ITePrinter * This);


void __RPC_STUB ITePrinter_addHLineControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITePrinter_INTERFACE_DEFINED__ */



#ifndef __TeComPrinterLib_LIBRARY_DEFINED__
#define __TeComPrinterLib_LIBRARY_DEFINED__

/* library TeComPrinterLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_TeComPrinterLib;

#ifndef ___ITePrinterEvents_DISPINTERFACE_DEFINED__
#define ___ITePrinterEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITePrinterEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ITePrinterEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("53CF6133-FC16-41A2-9F6B-EB9EA847BE14")
    _ITePrinterEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITePrinterEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _ITePrinterEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _ITePrinterEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _ITePrinterEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _ITePrinterEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _ITePrinterEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _ITePrinterEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _ITePrinterEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _ITePrinterEventsVtbl;

    interface _ITePrinterEvents
    {
        CONST_VTBL struct _ITePrinterEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITePrinterEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ITePrinterEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ITePrinterEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ITePrinterEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ITePrinterEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ITePrinterEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ITePrinterEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITePrinterEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TePrinter;

#ifdef __cplusplus

class DECLSPEC_UUID("02F2F0AF-E832-46CA-9D75-A312FB2D8837")
TePrinter;
#endif
#endif /* __TeComPrinterLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


