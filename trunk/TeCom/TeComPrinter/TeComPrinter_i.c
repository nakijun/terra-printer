

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_ITePrinter,0x3D1C2BB1,0x6D87,0x42CA,0xA6,0x81,0xBB,0xA7,0x69,0x70,0x31,0xF8);


MIDL_DEFINE_GUID(IID, LIBID_TeComPrinterLib,0xF141AAE7,0xBD4C,0x4793,0x88,0xDB,0x10,0xFE,0x8C,0xBA,0x51,0x8C);


MIDL_DEFINE_GUID(IID, DIID__ITePrinterEvents,0x53CF6133,0xFC16,0x41A2,0x9F,0x6B,0xEB,0x9E,0xA8,0x47,0xBE,0x14);


MIDL_DEFINE_GUID(CLSID, CLSID_TePrinter,0x02F2F0AF,0xE832,0x46CA,0x9D,0x75,0xA3,0x12,0xFB,0x2D,0x88,0x37);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



