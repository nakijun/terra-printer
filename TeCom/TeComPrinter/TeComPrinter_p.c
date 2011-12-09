

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */
#pragma warning( disable: 4211 )  /* redefine extent to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "TeComPrinter.h"

#define TYPE_FORMAT_STRING_SIZE   1067                              
#define PROC_FORMAT_STRING_SIZE   1957                              
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   2            

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ITePrinter_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ITePrinter_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, float, double or hyper in -Oif or -Oicf, more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure put_BackColor */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x8 ),	/* 8 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter clr */

/* 16 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 18 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 20 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 22 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 24 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 26 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_BackColor */

/* 28 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 30 */	NdrFcLong( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x8 ),	/* 8 */
/* 36 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0x24 ),	/* 36 */
/* 42 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pclr */

/* 44 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 46 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 48 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 50 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 52 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 54 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure execute */

/* 56 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 58 */	NdrFcLong( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x9 ),	/* 9 */
/* 64 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x8 ),	/* 8 */
/* 70 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 72 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 74 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 76 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_orientation */

/* 78 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 80 */	NdrFcLong( 0x0 ),	/* 0 */
/* 84 */	NdrFcShort( 0xa ),	/* 10 */
/* 86 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 88 */	NdrFcShort( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x22 ),	/* 34 */
/* 92 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 94 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 96 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 98 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 100 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 102 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 104 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_orientation */

/* 106 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 108 */	NdrFcLong( 0x0 ),	/* 0 */
/* 112 */	NdrFcShort( 0xb ),	/* 11 */
/* 114 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 116 */	NdrFcShort( 0x6 ),	/* 6 */
/* 118 */	NdrFcShort( 0x8 ),	/* 8 */
/* 120 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 122 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 124 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 126 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 128 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 130 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 132 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_paperSize */

/* 134 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 136 */	NdrFcLong( 0x0 ),	/* 0 */
/* 140 */	NdrFcShort( 0xc ),	/* 12 */
/* 142 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 144 */	NdrFcShort( 0x0 ),	/* 0 */
/* 146 */	NdrFcShort( 0x22 ),	/* 34 */
/* 148 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 150 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 152 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 154 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 156 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 158 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 160 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_paperSize */

/* 162 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 164 */	NdrFcLong( 0x0 ),	/* 0 */
/* 168 */	NdrFcShort( 0xd ),	/* 13 */
/* 170 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 172 */	NdrFcShort( 0x6 ),	/* 6 */
/* 174 */	NdrFcShort( 0x8 ),	/* 8 */
/* 176 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 178 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 180 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 182 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 184 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 186 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 188 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addText */

/* 190 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 192 */	NdrFcLong( 0x0 ),	/* 0 */
/* 196 */	NdrFcShort( 0xe ),	/* 14 */
/* 198 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 202 */	NdrFcShort( 0x8 ),	/* 8 */
/* 204 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter textValue */

/* 206 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 208 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 210 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 212 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 214 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 216 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setAlign */

/* 218 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 220 */	NdrFcLong( 0x0 ),	/* 0 */
/* 224 */	NdrFcShort( 0xf ),	/* 15 */
/* 226 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 228 */	NdrFcShort( 0x6 ),	/* 6 */
/* 230 */	NdrFcShort( 0x8 ),	/* 8 */
/* 232 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter value */

/* 234 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 236 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 238 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 240 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 242 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 244 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure printExecute */

/* 246 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 248 */	NdrFcLong( 0x0 ),	/* 0 */
/* 252 */	NdrFcShort( 0x10 ),	/* 16 */
/* 254 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 256 */	NdrFcShort( 0x0 ),	/* 0 */
/* 258 */	NdrFcShort( 0x22 ),	/* 34 */
/* 260 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter printTitle */

/* 262 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 264 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 266 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter result */

/* 268 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 270 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 272 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 274 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 276 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 278 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addImage */

/* 280 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 282 */	NdrFcLong( 0x0 ),	/* 0 */
/* 286 */	NdrFcShort( 0x11 ),	/* 17 */
/* 288 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 290 */	NdrFcShort( 0x0 ),	/* 0 */
/* 292 */	NdrFcShort( 0x8 ),	/* 8 */
/* 294 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter fileName */

/* 296 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 298 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 300 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 302 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 304 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 306 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_connection */

/* 308 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 310 */	NdrFcLong( 0x0 ),	/* 0 */
/* 314 */	NdrFcShort( 0x12 ),	/* 18 */
/* 316 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 318 */	NdrFcShort( 0x0 ),	/* 0 */
/* 320 */	NdrFcShort( 0x8 ),	/* 8 */
/* 322 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 324 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 326 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 328 */	NdrFcShort( 0x400 ),	/* Type Offset=1024 */

	/* Return value */

/* 330 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 332 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 334 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_connection */

/* 336 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 338 */	NdrFcLong( 0x0 ),	/* 0 */
/* 342 */	NdrFcShort( 0x13 ),	/* 19 */
/* 344 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 348 */	NdrFcShort( 0x8 ),	/* 8 */
/* 350 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 352 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 354 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 356 */	NdrFcShort( 0x40e ),	/* Type Offset=1038 */

	/* Return value */

/* 358 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 360 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 362 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_provider */

/* 364 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 366 */	NdrFcLong( 0x0 ),	/* 0 */
/* 370 */	NdrFcShort( 0x14 ),	/* 20 */
/* 372 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 374 */	NdrFcShort( 0x0 ),	/* 0 */
/* 376 */	NdrFcShort( 0x22 ),	/* 34 */
/* 378 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 380 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 382 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 384 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 386 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 388 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 390 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_provider */

/* 392 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 394 */	NdrFcLong( 0x0 ),	/* 0 */
/* 398 */	NdrFcShort( 0x15 ),	/* 21 */
/* 400 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 402 */	NdrFcShort( 0x6 ),	/* 6 */
/* 404 */	NdrFcShort( 0x8 ),	/* 8 */
/* 406 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 408 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 410 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 412 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 414 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 416 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addMap */

/* 420 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 422 */	NdrFcLong( 0x0 ),	/* 0 */
/* 426 */	NdrFcShort( 0x16 ),	/* 22 */
/* 428 */	NdrFcShort( 0x30 ),	/* x86 Stack size/offset = 48 */
/* 430 */	NdrFcShort( 0x40 ),	/* 64 */
/* 432 */	NdrFcShort( 0x8 ),	/* 8 */
/* 434 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x7,		/* 7 */

	/* Parameter viewName */

/* 436 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 438 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 440 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter userName */

/* 442 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 444 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 446 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter x1 */

/* 448 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 450 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 452 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter y1 */

/* 454 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 456 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 458 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter x2 */

/* 460 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 462 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 464 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Parameter y2 */

/* 466 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 468 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 470 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 472 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 474 */	NdrFcShort( 0x2c ),	/* x86 Stack size/offset = 44 */
/* 476 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLayoutObjectCount */

/* 478 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 480 */	NdrFcLong( 0x0 ),	/* 0 */
/* 484 */	NdrFcShort( 0x17 ),	/* 23 */
/* 486 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 488 */	NdrFcShort( 0x0 ),	/* 0 */
/* 490 */	NdrFcShort( 0x24 ),	/* 36 */
/* 492 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter result */

/* 494 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 496 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 498 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 500 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 502 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 504 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLayoutObjectName */

/* 506 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 508 */	NdrFcLong( 0x0 ),	/* 0 */
/* 512 */	NdrFcShort( 0x18 ),	/* 24 */
/* 514 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 516 */	NdrFcShort( 0x8 ),	/* 8 */
/* 518 */	NdrFcShort( 0x8 ),	/* 8 */
/* 520 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 522 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 524 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 526 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter result */

/* 528 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 530 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 532 */	NdrFcShort( 0x41c ),	/* Type Offset=1052 */

	/* Return value */

/* 534 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 536 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 538 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLayoutObjectPropertiesCount */

/* 540 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 542 */	NdrFcLong( 0x0 ),	/* 0 */
/* 546 */	NdrFcShort( 0x19 ),	/* 25 */
/* 548 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 550 */	NdrFcShort( 0x0 ),	/* 0 */
/* 552 */	NdrFcShort( 0x24 ),	/* 36 */
/* 554 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter objectName */

/* 556 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 558 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 560 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter result */

/* 562 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 564 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 566 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 568 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 570 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 572 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLayoutObjectPropertyName */

/* 574 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 576 */	NdrFcLong( 0x0 ),	/* 0 */
/* 580 */	NdrFcShort( 0x1a ),	/* 26 */
/* 582 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 584 */	NdrFcShort( 0x8 ),	/* 8 */
/* 586 */	NdrFcShort( 0x8 ),	/* 8 */
/* 588 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter objectName */

/* 590 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 592 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 594 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter index */

/* 596 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 598 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 600 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter result */

/* 602 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 604 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 606 */	NdrFcShort( 0x41c ),	/* Type Offset=1052 */

	/* Return value */

/* 608 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 610 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 612 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLayoutObjectPropertyValue */

/* 614 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 616 */	NdrFcLong( 0x0 ),	/* 0 */
/* 620 */	NdrFcShort( 0x1b ),	/* 27 */
/* 622 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 624 */	NdrFcShort( 0x8 ),	/* 8 */
/* 626 */	NdrFcShort( 0x8 ),	/* 8 */
/* 628 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter objectName */

/* 630 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 632 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 634 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter index */

/* 636 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 638 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 640 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter result */

/* 642 */	NdrFcShort( 0x4113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=16 */
/* 644 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 646 */	NdrFcShort( 0x400 ),	/* Type Offset=1024 */

	/* Return value */

/* 648 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 650 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 652 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setObjectPropertyValue */

/* 654 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 656 */	NdrFcLong( 0x0 ),	/* 0 */
/* 660 */	NdrFcShort( 0x1c ),	/* 28 */
/* 662 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 664 */	NdrFcShort( 0x8 ),	/* 8 */
/* 666 */	NdrFcShort( 0x8 ),	/* 8 */
/* 668 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter objName */

/* 670 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 672 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 674 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter index */

/* 676 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 678 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 680 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter value */

/* 682 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 684 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 686 */	NdrFcShort( 0x40e ),	/* Type Offset=1038 */

	/* Return value */

/* 688 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 690 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 692 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLayoutSelectObjectCount */

/* 694 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 696 */	NdrFcLong( 0x0 ),	/* 0 */
/* 700 */	NdrFcShort( 0x1d ),	/* 29 */
/* 702 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0x24 ),	/* 36 */
/* 708 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter result */

/* 710 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 712 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 714 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 716 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 718 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 720 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLayoutSelectObjectName */

/* 722 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 724 */	NdrFcLong( 0x0 ),	/* 0 */
/* 728 */	NdrFcShort( 0x1e ),	/* 30 */
/* 730 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 732 */	NdrFcShort( 0x8 ),	/* 8 */
/* 734 */	NdrFcShort( 0x8 ),	/* 8 */
/* 736 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter index */

/* 738 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 740 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 742 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter result */

/* 744 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 746 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 748 */	NdrFcShort( 0x41c ),	/* Type Offset=1052 */

	/* Return value */

/* 750 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 752 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 754 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setObjectPropertyValueByName */

/* 756 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 758 */	NdrFcLong( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0x1f ),	/* 31 */
/* 764 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 768 */	NdrFcShort( 0x8 ),	/* 8 */
/* 770 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter objName */

/* 772 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 774 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 776 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter propertyName */

/* 778 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 780 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 782 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter value */

/* 784 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 786 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 788 */	NdrFcShort( 0x40e ),	/* Type Offset=1038 */

	/* Return value */

/* 790 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 792 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 794 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setMapMode */

/* 796 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 798 */	NdrFcLong( 0x0 ),	/* 0 */
/* 802 */	NdrFcShort( 0x20 ),	/* 32 */
/* 804 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 806 */	NdrFcShort( 0x6 ),	/* 6 */
/* 808 */	NdrFcShort( 0x8 ),	/* 8 */
/* 810 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter mode */

/* 812 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 814 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 816 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 818 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 820 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 822 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure sendObjectToBack */

/* 824 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 826 */	NdrFcLong( 0x0 ),	/* 0 */
/* 830 */	NdrFcShort( 0x21 ),	/* 33 */
/* 832 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 834 */	NdrFcShort( 0x0 ),	/* 0 */
/* 836 */	NdrFcShort( 0x8 ),	/* 8 */
/* 838 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 840 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 842 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 844 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure bringObjectToFront */

/* 846 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 848 */	NdrFcLong( 0x0 ),	/* 0 */
/* 852 */	NdrFcShort( 0x22 ),	/* 34 */
/* 854 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 856 */	NdrFcShort( 0x0 ),	/* 0 */
/* 858 */	NdrFcShort( 0x8 ),	/* 8 */
/* 860 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 862 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 864 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 866 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addRectangle */

/* 868 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 870 */	NdrFcLong( 0x0 ),	/* 0 */
/* 874 */	NdrFcShort( 0x23 ),	/* 35 */
/* 876 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 878 */	NdrFcShort( 0x0 ),	/* 0 */
/* 880 */	NdrFcShort( 0x8 ),	/* 8 */
/* 882 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 884 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 886 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 888 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addEllipse */

/* 890 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 892 */	NdrFcLong( 0x0 ),	/* 0 */
/* 896 */	NdrFcShort( 0x24 ),	/* 36 */
/* 898 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 900 */	NdrFcShort( 0x0 ),	/* 0 */
/* 902 */	NdrFcShort( 0x8 ),	/* 8 */
/* 904 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 906 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 908 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 910 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addLine */

/* 912 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 914 */	NdrFcLong( 0x0 ),	/* 0 */
/* 918 */	NdrFcShort( 0x25 ),	/* 37 */
/* 920 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 922 */	NdrFcShort( 0x0 ),	/* 0 */
/* 924 */	NdrFcShort( 0x8 ),	/* 8 */
/* 926 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 928 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 930 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 932 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure stopProcess */

/* 934 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 936 */	NdrFcLong( 0x0 ),	/* 0 */
/* 940 */	NdrFcShort( 0x26 ),	/* 38 */
/* 942 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 944 */	NdrFcShort( 0x0 ),	/* 0 */
/* 946 */	NdrFcShort( 0x8 ),	/* 8 */
/* 948 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 950 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 952 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 954 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addScale */

/* 956 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 958 */	NdrFcLong( 0x0 ),	/* 0 */
/* 962 */	NdrFcShort( 0x27 ),	/* 39 */
/* 964 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 966 */	NdrFcShort( 0x0 ),	/* 0 */
/* 968 */	NdrFcShort( 0x8 ),	/* 8 */
/* 970 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 972 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 974 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 976 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_leftMargin */

/* 978 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 980 */	NdrFcLong( 0x0 ),	/* 0 */
/* 984 */	NdrFcShort( 0x28 ),	/* 40 */
/* 986 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 988 */	NdrFcShort( 0x0 ),	/* 0 */
/* 990 */	NdrFcShort( 0x2c ),	/* 44 */
/* 992 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 994 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 996 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 998 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1000 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1002 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1004 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_leftMargin */

/* 1006 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1008 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1012 */	NdrFcShort( 0x29 ),	/* 41 */
/* 1014 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1016 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1018 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1020 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1022 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1024 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1026 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1028 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1030 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1032 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_topMargin */

/* 1034 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1036 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1040 */	NdrFcShort( 0x2a ),	/* 42 */
/* 1042 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1046 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1048 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1050 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1052 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1054 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1056 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1058 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1060 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_topMargin */

/* 1062 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1064 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1068 */	NdrFcShort( 0x2b ),	/* 43 */
/* 1070 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1072 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1074 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1076 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1078 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1080 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1082 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1084 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1086 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1088 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_bottomMargin */

/* 1090 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1092 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1096 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1098 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1102 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1104 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1106 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1108 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1110 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1112 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1114 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1116 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_bottomMargin */

/* 1118 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1120 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1124 */	NdrFcShort( 0x2d ),	/* 45 */
/* 1126 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1128 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1130 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1132 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1134 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1136 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1138 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1140 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1142 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1144 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_rightMargin */

/* 1146 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1148 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1152 */	NdrFcShort( 0x2e ),	/* 46 */
/* 1154 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1156 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1158 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1160 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1162 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1164 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1166 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1168 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1170 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_rightMargin */

/* 1174 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1176 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1180 */	NdrFcShort( 0x2f ),	/* 47 */
/* 1182 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1184 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1186 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1188 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1190 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1192 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1194 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1196 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1198 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1200 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure selectObject */

/* 1202 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1204 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1208 */	NdrFcShort( 0x30 ),	/* 48 */
/* 1210 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1212 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1214 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1216 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter objectName */

/* 1218 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1220 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1222 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter result */

/* 1224 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1226 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1228 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1230 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1232 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1234 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addNorth */

/* 1236 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1238 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1242 */	NdrFcShort( 0x31 ),	/* 49 */
/* 1244 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1246 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1248 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1250 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1252 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1254 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1256 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure hrzDisplacement */

/* 1258 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1260 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1264 */	NdrFcShort( 0x32 ),	/* 50 */
/* 1266 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1268 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1270 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1272 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter value */

/* 1274 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1276 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1278 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1280 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1282 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1284 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure vrtDisplacement */

/* 1286 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1288 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1292 */	NdrFcShort( 0x33 ),	/* 51 */
/* 1294 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1296 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1298 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1300 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter value */

/* 1302 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1304 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1306 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1308 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1310 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1312 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure recompose */

/* 1314 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1316 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1320 */	NdrFcShort( 0x34 ),	/* 52 */
/* 1322 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1326 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1328 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1330 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1332 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1334 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_wClientArea */

/* 1336 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1338 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1342 */	NdrFcShort( 0x35 ),	/* 53 */
/* 1344 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1348 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1350 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1352 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1354 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1356 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1358 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1360 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1362 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_hClientArea */

/* 1364 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1366 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1370 */	NdrFcShort( 0x36 ),	/* 54 */
/* 1372 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1374 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1376 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1378 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1380 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1382 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1384 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1386 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1388 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1390 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_zoomFactor */

/* 1392 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1394 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1398 */	NdrFcShort( 0x37 ),	/* 55 */
/* 1400 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1404 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1406 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1408 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1410 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1412 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1414 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1416 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_zoomFactor */

/* 1420 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1422 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1426 */	NdrFcShort( 0x38 ),	/* 56 */
/* 1428 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1430 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1432 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1434 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1436 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1438 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1440 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1442 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1444 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1446 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_centerVisibleAreaX */

/* 1448 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1450 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1454 */	NdrFcShort( 0x39 ),	/* 57 */
/* 1456 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1458 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1460 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1462 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1464 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1466 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1468 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1470 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1472 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1474 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_centerVisibleAreaY */

/* 1476 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1478 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1482 */	NdrFcShort( 0x3a ),	/* 58 */
/* 1484 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1488 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1490 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1492 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1494 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1496 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1498 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1500 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1502 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure removeSelectedItems */

/* 1504 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1506 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1510 */	NdrFcShort( 0x3b ),	/* 59 */
/* 1512 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1516 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1518 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1520 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1522 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1524 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLayoutObjectType */

/* 1526 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1528 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1532 */	NdrFcShort( 0x3c ),	/* 60 */
/* 1534 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1538 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1540 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter objectName */

/* 1542 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1544 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1546 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter result */

/* 1548 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 1550 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1552 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 1554 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1556 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1558 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure setLayoutMode */

/* 1560 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1562 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1566 */	NdrFcShort( 0x3d ),	/* 61 */
/* 1568 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1570 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1572 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1574 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter mode */

/* 1576 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1578 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1580 */	0xd,		/* FC_ENUM16 */
			0x0,		/* 0 */

	/* Return value */

/* 1582 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1584 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1586 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure getLayoutPropertyType */

/* 1588 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1590 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1594 */	NdrFcShort( 0x3e ),	/* 62 */
/* 1596 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 1598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1600 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1602 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x4,		/* 4 */

	/* Parameter objectName */

/* 1604 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1606 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1608 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter propertyName */

/* 1610 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1612 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1614 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter result */

/* 1616 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 1618 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1620 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Return value */

/* 1622 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1624 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1626 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure forceFullUpdate */

/* 1628 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1630 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1634 */	NdrFcShort( 0x3f ),	/* 63 */
/* 1636 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1640 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1642 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1644 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1646 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1648 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addDatabase */

/* 1650 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1652 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1656 */	NdrFcShort( 0x40 ),	/* 64 */
/* 1658 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1662 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1664 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1666 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1668 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1670 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure save */

/* 1672 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1674 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1678 */	NdrFcShort( 0x41 ),	/* 65 */
/* 1680 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1682 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1684 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1686 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter fileName */

/* 1688 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1690 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1692 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter result */

/* 1694 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1696 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1698 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1700 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1702 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1704 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure open */

/* 1706 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1708 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1712 */	NdrFcShort( 0x42 ),	/* 66 */
/* 1714 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1716 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1718 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1720 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter fileName */

/* 1722 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1724 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1726 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Parameter result */

/* 1728 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1730 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1732 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1734 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1736 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1738 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure newEmptyPage */

/* 1740 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1742 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1746 */	NdrFcShort( 0x43 ),	/* 67 */
/* 1748 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1750 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1752 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1754 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1756 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1758 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1760 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addMText */

/* 1762 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1764 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1768 */	NdrFcShort( 0x44 ),	/* 68 */
/* 1770 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1772 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1774 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1776 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter textValue */

/* 1778 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1780 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1782 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 1784 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1786 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1788 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addPoliticalDivision */

/* 1790 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1792 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1796 */	NdrFcShort( 0x45 ),	/* 69 */
/* 1798 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1802 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1804 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1806 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1808 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1810 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure copyToClipboard */

/* 1812 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1814 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1818 */	NdrFcShort( 0x46 ),	/* 70 */
/* 1820 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1822 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1824 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1826 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1828 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1830 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1832 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure pasteFromClipboard */

/* 1834 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1836 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1840 */	NdrFcShort( 0x47 ),	/* 71 */
/* 1842 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1844 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1846 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1848 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1850 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1852 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1854 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure clipboardIsEmpty */

/* 1856 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1858 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1862 */	NdrFcShort( 0x48 ),	/* 72 */
/* 1864 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1868 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1870 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter result */

/* 1872 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1874 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1876 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1878 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1880 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1882 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addBarcode */

/* 1884 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1886 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1890 */	NdrFcShort( 0x49 ),	/* 73 */
/* 1892 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1894 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1896 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1898 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter textValue */

/* 1900 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1902 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1904 */	NdrFcShort( 0x22 ),	/* Type Offset=34 */

	/* Return value */

/* 1906 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1908 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1910 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addVLineControl */

/* 1912 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1914 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1918 */	NdrFcShort( 0x4a ),	/* 74 */
/* 1920 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1922 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1924 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1926 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1928 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1930 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1932 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure addHLineControl */

/* 1934 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1936 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1940 */	NdrFcShort( 0x4b ),	/* 75 */
/* 1942 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1944 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1946 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1948 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1950 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1952 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1954 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  8 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */
/* 10 */	
			0x12, 0x0,	/* FC_UP */
/* 12 */	NdrFcShort( 0xc ),	/* Offset= 12 (24) */
/* 14 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 16 */	NdrFcShort( 0x2 ),	/* 2 */
/* 18 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 20 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 22 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 24 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 26 */	NdrFcShort( 0x8 ),	/* 8 */
/* 28 */	NdrFcShort( 0xfff2 ),	/* Offset= -14 (14) */
/* 30 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 32 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 34 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 36 */	NdrFcShort( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0x4 ),	/* 4 */
/* 40 */	NdrFcShort( 0x0 ),	/* 0 */
/* 42 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (10) */
/* 44 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 46 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 48 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 50 */	NdrFcShort( 0x3ce ),	/* Offset= 974 (1024) */
/* 52 */	
			0x13, 0x0,	/* FC_OP */
/* 54 */	NdrFcShort( 0x3b6 ),	/* Offset= 950 (1004) */
/* 56 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 58 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 60 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 62 */	NdrFcShort( 0x2 ),	/* Offset= 2 (64) */
/* 64 */	NdrFcShort( 0x10 ),	/* 16 */
/* 66 */	NdrFcShort( 0x2f ),	/* 47 */
/* 68 */	NdrFcLong( 0x14 ),	/* 20 */
/* 72 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 74 */	NdrFcLong( 0x3 ),	/* 3 */
/* 78 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 80 */	NdrFcLong( 0x11 ),	/* 17 */
/* 84 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 86 */	NdrFcLong( 0x2 ),	/* 2 */
/* 90 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 92 */	NdrFcLong( 0x4 ),	/* 4 */
/* 96 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 98 */	NdrFcLong( 0x5 ),	/* 5 */
/* 102 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 104 */	NdrFcLong( 0xb ),	/* 11 */
/* 108 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 110 */	NdrFcLong( 0xa ),	/* 10 */
/* 114 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 116 */	NdrFcLong( 0x6 ),	/* 6 */
/* 120 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (352) */
/* 122 */	NdrFcLong( 0x7 ),	/* 7 */
/* 126 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 128 */	NdrFcLong( 0x8 ),	/* 8 */
/* 132 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (358) */
/* 134 */	NdrFcLong( 0xd ),	/* 13 */
/* 138 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (362) */
/* 140 */	NdrFcLong( 0x9 ),	/* 9 */
/* 144 */	NdrFcShort( 0xec ),	/* Offset= 236 (380) */
/* 146 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 150 */	NdrFcShort( 0xf8 ),	/* Offset= 248 (398) */
/* 152 */	NdrFcLong( 0x24 ),	/* 36 */
/* 156 */	NdrFcShort( 0x306 ),	/* Offset= 774 (930) */
/* 158 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 162 */	NdrFcShort( 0x300 ),	/* Offset= 768 (930) */
/* 164 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 168 */	NdrFcShort( 0x2fe ),	/* Offset= 766 (934) */
/* 170 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 174 */	NdrFcShort( 0x2fc ),	/* Offset= 764 (938) */
/* 176 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 180 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (942) */
/* 182 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 186 */	NdrFcShort( 0x2f8 ),	/* Offset= 760 (946) */
/* 188 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 192 */	NdrFcShort( 0x2f6 ),	/* Offset= 758 (950) */
/* 194 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 198 */	NdrFcShort( 0x2f4 ),	/* Offset= 756 (954) */
/* 200 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 204 */	NdrFcShort( 0x2de ),	/* Offset= 734 (938) */
/* 206 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 210 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (942) */
/* 212 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 216 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (958) */
/* 218 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 222 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (954) */
/* 224 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 228 */	NdrFcShort( 0x2de ),	/* Offset= 734 (962) */
/* 230 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 234 */	NdrFcShort( 0x2dc ),	/* Offset= 732 (966) */
/* 236 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 240 */	NdrFcShort( 0x2da ),	/* Offset= 730 (970) */
/* 242 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 246 */	NdrFcShort( 0x2d8 ),	/* Offset= 728 (974) */
/* 248 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 252 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (978) */
/* 254 */	NdrFcLong( 0x10 ),	/* 16 */
/* 258 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 260 */	NdrFcLong( 0x12 ),	/* 18 */
/* 264 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 266 */	NdrFcLong( 0x13 ),	/* 19 */
/* 270 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 272 */	NdrFcLong( 0x15 ),	/* 21 */
/* 276 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 278 */	NdrFcLong( 0x16 ),	/* 22 */
/* 282 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 284 */	NdrFcLong( 0x17 ),	/* 23 */
/* 288 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 290 */	NdrFcLong( 0xe ),	/* 14 */
/* 294 */	NdrFcShort( 0x2b4 ),	/* Offset= 692 (986) */
/* 296 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 300 */	NdrFcShort( 0x2b8 ),	/* Offset= 696 (996) */
/* 302 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 306 */	NdrFcShort( 0x2b6 ),	/* Offset= 694 (1000) */
/* 308 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 312 */	NdrFcShort( 0x272 ),	/* Offset= 626 (938) */
/* 314 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 318 */	NdrFcShort( 0x270 ),	/* Offset= 624 (942) */
/* 320 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 324 */	NdrFcShort( 0x26e ),	/* Offset= 622 (946) */
/* 326 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 330 */	NdrFcShort( 0x264 ),	/* Offset= 612 (942) */
/* 332 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 336 */	NdrFcShort( 0x25e ),	/* Offset= 606 (942) */
/* 338 */	NdrFcLong( 0x0 ),	/* 0 */
/* 342 */	NdrFcShort( 0x0 ),	/* Offset= 0 (342) */
/* 344 */	NdrFcLong( 0x1 ),	/* 1 */
/* 348 */	NdrFcShort( 0x0 ),	/* Offset= 0 (348) */
/* 350 */	NdrFcShort( 0xffff ),	/* Offset= -1 (349) */
/* 352 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 354 */	NdrFcShort( 0x8 ),	/* 8 */
/* 356 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 358 */	
			0x13, 0x0,	/* FC_OP */
/* 360 */	NdrFcShort( 0xfeb0 ),	/* Offset= -336 (24) */
/* 362 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 364 */	NdrFcLong( 0x0 ),	/* 0 */
/* 368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 370 */	NdrFcShort( 0x0 ),	/* 0 */
/* 372 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 374 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 376 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 378 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 380 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 382 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 386 */	NdrFcShort( 0x0 ),	/* 0 */
/* 388 */	NdrFcShort( 0x0 ),	/* 0 */
/* 390 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 392 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 394 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 396 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 398 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 400 */	NdrFcShort( 0x2 ),	/* Offset= 2 (402) */
/* 402 */	
			0x13, 0x0,	/* FC_OP */
/* 404 */	NdrFcShort( 0x1fc ),	/* Offset= 508 (912) */
/* 406 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 408 */	NdrFcShort( 0x18 ),	/* 24 */
/* 410 */	NdrFcShort( 0xa ),	/* 10 */
/* 412 */	NdrFcLong( 0x8 ),	/* 8 */
/* 416 */	NdrFcShort( 0x58 ),	/* Offset= 88 (504) */
/* 418 */	NdrFcLong( 0xd ),	/* 13 */
/* 422 */	NdrFcShort( 0x78 ),	/* Offset= 120 (542) */
/* 424 */	NdrFcLong( 0x9 ),	/* 9 */
/* 428 */	NdrFcShort( 0x94 ),	/* Offset= 148 (576) */
/* 430 */	NdrFcLong( 0xc ),	/* 12 */
/* 434 */	NdrFcShort( 0xbc ),	/* Offset= 188 (622) */
/* 436 */	NdrFcLong( 0x24 ),	/* 36 */
/* 440 */	NdrFcShort( 0x114 ),	/* Offset= 276 (716) */
/* 442 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 446 */	NdrFcShort( 0x130 ),	/* Offset= 304 (750) */
/* 448 */	NdrFcLong( 0x10 ),	/* 16 */
/* 452 */	NdrFcShort( 0x148 ),	/* Offset= 328 (780) */
/* 454 */	NdrFcLong( 0x2 ),	/* 2 */
/* 458 */	NdrFcShort( 0x160 ),	/* Offset= 352 (810) */
/* 460 */	NdrFcLong( 0x3 ),	/* 3 */
/* 464 */	NdrFcShort( 0x178 ),	/* Offset= 376 (840) */
/* 466 */	NdrFcLong( 0x14 ),	/* 20 */
/* 470 */	NdrFcShort( 0x190 ),	/* Offset= 400 (870) */
/* 472 */	NdrFcShort( 0xffff ),	/* Offset= -1 (471) */
/* 474 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 476 */	NdrFcShort( 0x4 ),	/* 4 */
/* 478 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 480 */	NdrFcShort( 0x0 ),	/* 0 */
/* 482 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 484 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 486 */	NdrFcShort( 0x4 ),	/* 4 */
/* 488 */	NdrFcShort( 0x0 ),	/* 0 */
/* 490 */	NdrFcShort( 0x1 ),	/* 1 */
/* 492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 494 */	NdrFcShort( 0x0 ),	/* 0 */
/* 496 */	0x13, 0x0,	/* FC_OP */
/* 498 */	NdrFcShort( 0xfe26 ),	/* Offset= -474 (24) */
/* 500 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 502 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 504 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 506 */	NdrFcShort( 0x8 ),	/* 8 */
/* 508 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 510 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 512 */	NdrFcShort( 0x4 ),	/* 4 */
/* 514 */	NdrFcShort( 0x4 ),	/* 4 */
/* 516 */	0x11, 0x0,	/* FC_RP */
/* 518 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (474) */
/* 520 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 522 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 524 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 526 */	NdrFcShort( 0x0 ),	/* 0 */
/* 528 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 530 */	NdrFcShort( 0x0 ),	/* 0 */
/* 532 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 536 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 538 */	NdrFcShort( 0xff50 ),	/* Offset= -176 (362) */
/* 540 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 542 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 544 */	NdrFcShort( 0x8 ),	/* 8 */
/* 546 */	NdrFcShort( 0x0 ),	/* 0 */
/* 548 */	NdrFcShort( 0x6 ),	/* Offset= 6 (554) */
/* 550 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 552 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 554 */	
			0x11, 0x0,	/* FC_RP */
/* 556 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (524) */
/* 558 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 560 */	NdrFcShort( 0x0 ),	/* 0 */
/* 562 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 564 */	NdrFcShort( 0x0 ),	/* 0 */
/* 566 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 570 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 572 */	NdrFcShort( 0xff40 ),	/* Offset= -192 (380) */
/* 574 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 576 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 578 */	NdrFcShort( 0x8 ),	/* 8 */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x6 ),	/* Offset= 6 (588) */
/* 584 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 586 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 588 */	
			0x11, 0x0,	/* FC_RP */
/* 590 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (558) */
/* 592 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 594 */	NdrFcShort( 0x4 ),	/* 4 */
/* 596 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 598 */	NdrFcShort( 0x0 ),	/* 0 */
/* 600 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 602 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 604 */	NdrFcShort( 0x4 ),	/* 4 */
/* 606 */	NdrFcShort( 0x0 ),	/* 0 */
/* 608 */	NdrFcShort( 0x1 ),	/* 1 */
/* 610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 612 */	NdrFcShort( 0x0 ),	/* 0 */
/* 614 */	0x13, 0x0,	/* FC_OP */
/* 616 */	NdrFcShort( 0x184 ),	/* Offset= 388 (1004) */
/* 618 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 620 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 622 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 624 */	NdrFcShort( 0x8 ),	/* 8 */
/* 626 */	NdrFcShort( 0x0 ),	/* 0 */
/* 628 */	NdrFcShort( 0x6 ),	/* Offset= 6 (634) */
/* 630 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 632 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 634 */	
			0x11, 0x0,	/* FC_RP */
/* 636 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (592) */
/* 638 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 640 */	NdrFcLong( 0x2f ),	/* 47 */
/* 644 */	NdrFcShort( 0x0 ),	/* 0 */
/* 646 */	NdrFcShort( 0x0 ),	/* 0 */
/* 648 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 650 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 652 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 654 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 656 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 658 */	NdrFcShort( 0x1 ),	/* 1 */
/* 660 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 662 */	NdrFcShort( 0x4 ),	/* 4 */
/* 664 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 666 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 668 */	NdrFcShort( 0x10 ),	/* 16 */
/* 670 */	NdrFcShort( 0x0 ),	/* 0 */
/* 672 */	NdrFcShort( 0xa ),	/* Offset= 10 (682) */
/* 674 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 676 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 678 */	NdrFcShort( 0xffd8 ),	/* Offset= -40 (638) */
/* 680 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 682 */	
			0x13, 0x0,	/* FC_OP */
/* 684 */	NdrFcShort( 0xffe4 ),	/* Offset= -28 (656) */
/* 686 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 688 */	NdrFcShort( 0x4 ),	/* 4 */
/* 690 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 692 */	NdrFcShort( 0x0 ),	/* 0 */
/* 694 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 696 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 698 */	NdrFcShort( 0x4 ),	/* 4 */
/* 700 */	NdrFcShort( 0x0 ),	/* 0 */
/* 702 */	NdrFcShort( 0x1 ),	/* 1 */
/* 704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0x0 ),	/* 0 */
/* 708 */	0x13, 0x0,	/* FC_OP */
/* 710 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (666) */
/* 712 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 714 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 716 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 718 */	NdrFcShort( 0x8 ),	/* 8 */
/* 720 */	NdrFcShort( 0x0 ),	/* 0 */
/* 722 */	NdrFcShort( 0x6 ),	/* Offset= 6 (728) */
/* 724 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 726 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 728 */	
			0x11, 0x0,	/* FC_RP */
/* 730 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (686) */
/* 732 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 734 */	NdrFcShort( 0x8 ),	/* 8 */
/* 736 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 738 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 740 */	NdrFcShort( 0x10 ),	/* 16 */
/* 742 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 744 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 746 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (732) */
			0x5b,		/* FC_END */
/* 750 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 752 */	NdrFcShort( 0x18 ),	/* 24 */
/* 754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 756 */	NdrFcShort( 0xa ),	/* Offset= 10 (766) */
/* 758 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 760 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 762 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (738) */
/* 764 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 766 */	
			0x11, 0x0,	/* FC_RP */
/* 768 */	NdrFcShort( 0xff0c ),	/* Offset= -244 (524) */
/* 770 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 772 */	NdrFcShort( 0x1 ),	/* 1 */
/* 774 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 776 */	NdrFcShort( 0x0 ),	/* 0 */
/* 778 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 780 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 782 */	NdrFcShort( 0x8 ),	/* 8 */
/* 784 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 786 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 788 */	NdrFcShort( 0x4 ),	/* 4 */
/* 790 */	NdrFcShort( 0x4 ),	/* 4 */
/* 792 */	0x13, 0x0,	/* FC_OP */
/* 794 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (770) */
/* 796 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 798 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 800 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 802 */	NdrFcShort( 0x2 ),	/* 2 */
/* 804 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 806 */	NdrFcShort( 0x0 ),	/* 0 */
/* 808 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 810 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 812 */	NdrFcShort( 0x8 ),	/* 8 */
/* 814 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 816 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 818 */	NdrFcShort( 0x4 ),	/* 4 */
/* 820 */	NdrFcShort( 0x4 ),	/* 4 */
/* 822 */	0x13, 0x0,	/* FC_OP */
/* 824 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (800) */
/* 826 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 828 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 830 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 832 */	NdrFcShort( 0x4 ),	/* 4 */
/* 834 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 836 */	NdrFcShort( 0x0 ),	/* 0 */
/* 838 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 840 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 842 */	NdrFcShort( 0x8 ),	/* 8 */
/* 844 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 846 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 848 */	NdrFcShort( 0x4 ),	/* 4 */
/* 850 */	NdrFcShort( 0x4 ),	/* 4 */
/* 852 */	0x13, 0x0,	/* FC_OP */
/* 854 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (830) */
/* 856 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 858 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 860 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 862 */	NdrFcShort( 0x8 ),	/* 8 */
/* 864 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 866 */	NdrFcShort( 0x0 ),	/* 0 */
/* 868 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 870 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 872 */	NdrFcShort( 0x8 ),	/* 8 */
/* 874 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 876 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 878 */	NdrFcShort( 0x4 ),	/* 4 */
/* 880 */	NdrFcShort( 0x4 ),	/* 4 */
/* 882 */	0x13, 0x0,	/* FC_OP */
/* 884 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (860) */
/* 886 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 888 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 890 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 892 */	NdrFcShort( 0x8 ),	/* 8 */
/* 894 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 896 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 898 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 900 */	NdrFcShort( 0x8 ),	/* 8 */
/* 902 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 904 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 906 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 908 */	NdrFcShort( 0xffee ),	/* Offset= -18 (890) */
/* 910 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 912 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 914 */	NdrFcShort( 0x28 ),	/* 40 */
/* 916 */	NdrFcShort( 0xffee ),	/* Offset= -18 (898) */
/* 918 */	NdrFcShort( 0x0 ),	/* Offset= 0 (918) */
/* 920 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 922 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 924 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 926 */	NdrFcShort( 0xfdf8 ),	/* Offset= -520 (406) */
/* 928 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 930 */	
			0x13, 0x0,	/* FC_OP */
/* 932 */	NdrFcShort( 0xfef6 ),	/* Offset= -266 (666) */
/* 934 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 936 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 938 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 940 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 942 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 944 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 946 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 948 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 950 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 952 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 954 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 956 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 958 */	
			0x13, 0x0,	/* FC_OP */
/* 960 */	NdrFcShort( 0xfda0 ),	/* Offset= -608 (352) */
/* 962 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 964 */	NdrFcShort( 0xfda2 ),	/* Offset= -606 (358) */
/* 966 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 968 */	NdrFcShort( 0xfda2 ),	/* Offset= -606 (362) */
/* 970 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 972 */	NdrFcShort( 0xfdb0 ),	/* Offset= -592 (380) */
/* 974 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 976 */	NdrFcShort( 0xfdbe ),	/* Offset= -578 (398) */
/* 978 */	
			0x13, 0x10,	/* FC_OP [pointer_deref] */
/* 980 */	NdrFcShort( 0x2 ),	/* Offset= 2 (982) */
/* 982 */	
			0x13, 0x0,	/* FC_OP */
/* 984 */	NdrFcShort( 0x14 ),	/* Offset= 20 (1004) */
/* 986 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 988 */	NdrFcShort( 0x10 ),	/* 16 */
/* 990 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 992 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 994 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 996 */	
			0x13, 0x0,	/* FC_OP */
/* 998 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (986) */
/* 1000 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1002 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 1004 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1006 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1008 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1010 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1010) */
/* 1012 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1014 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1016 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1018 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1020 */	NdrFcShort( 0xfc3c ),	/* Offset= -964 (56) */
/* 1022 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1024 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1026 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1028 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1030 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1032 */	NdrFcShort( 0xfc2c ),	/* Offset= -980 (52) */
/* 1034 */	
			0x12, 0x0,	/* FC_UP */
/* 1036 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (1004) */
/* 1038 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1040 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1042 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1044 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1046 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (1034) */
/* 1048 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 1050 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1052) */
/* 1052 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1054 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1056 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1058 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1060 */	NdrFcShort( 0xfd42 ),	/* Offset= -702 (358) */
/* 1062 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 1064 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };



/* Standard interface: __MIDL_itf_TeComPrinter_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ITePrinter, ver. 0.0,
   GUID={0x3D1C2BB1,0x6D87,0x42CA,{0xA6,0x81,0xBB,0xA7,0x69,0x70,0x31,0xF8}} */

#pragma code_seg(".orpc")
static const unsigned short ITePrinter_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    28,
    56,
    78,
    106,
    134,
    162,
    190,
    218,
    246,
    280,
    308,
    336,
    364,
    392,
    420,
    478,
    506,
    540,
    574,
    614,
    654,
    694,
    722,
    756,
    796,
    824,
    846,
    868,
    890,
    912,
    934,
    956,
    978,
    1006,
    1034,
    1062,
    1090,
    1118,
    1146,
    1174,
    1202,
    1236,
    1258,
    1286,
    1314,
    1336,
    1364,
    1392,
    1420,
    1448,
    1476,
    1504,
    1526,
    1560,
    1588,
    1628,
    1650,
    1672,
    1706,
    1740,
    1762,
    1790,
    1812,
    1834,
    1856,
    1884,
    1912,
    1934
    };

static const MIDL_STUBLESS_PROXY_INFO ITePrinter_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ITePrinter_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ITePrinter_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ITePrinter_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(76) _ITePrinterProxyVtbl = 
{
    &ITePrinter_ProxyInfo,
    &IID_ITePrinter,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::put_BackColor */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_BackColor */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::execute */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_orientation */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::put_orientation */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_paperSize */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::put_paperSize */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addText */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::setAlign */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::printExecute */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addImage */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_connection */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::put_connection */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_provider */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::put_provider */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addMap */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::getLayoutObjectCount */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::getLayoutObjectName */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::getLayoutObjectPropertiesCount */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::getLayoutObjectPropertyName */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::getLayoutObjectPropertyValue */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::setObjectPropertyValue */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::getLayoutSelectObjectCount */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::getLayoutSelectObjectName */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::setObjectPropertyValueByName */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::setMapMode */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::sendObjectToBack */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::bringObjectToFront */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addRectangle */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addEllipse */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addLine */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::stopProcess */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addScale */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_leftMargin */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::put_leftMargin */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_topMargin */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::put_topMargin */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_bottomMargin */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::put_bottomMargin */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_rightMargin */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::put_rightMargin */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::selectObject */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addNorth */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::hrzDisplacement */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::vrtDisplacement */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::recompose */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_wClientArea */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_hClientArea */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_zoomFactor */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::put_zoomFactor */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_centerVisibleAreaX */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::get_centerVisibleAreaY */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::removeSelectedItems */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::getLayoutObjectType */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::setLayoutMode */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::getLayoutPropertyType */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::forceFullUpdate */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addDatabase */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::save */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::open */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::newEmptyPage */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addMText */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addPoliticalDivision */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::copyToClipboard */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::pasteFromClipboard */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::clipboardIsEmpty */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addBarcode */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addVLineControl */ ,
    (void *) (INT_PTR) -1 /* ITePrinter::addHLineControl */
};


static const PRPC_STUB_FUNCTION ITePrinter_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _ITePrinterStubVtbl =
{
    &IID_ITePrinter,
    &ITePrinter_ServerInfo,
    76,
    &ITePrinter_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x600016e, /* MIDL Version 6.0.366 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _TeComPrinter_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ITePrinterProxyVtbl,
    0
};

const CInterfaceStubVtbl * _TeComPrinter_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ITePrinterStubVtbl,
    0
};

PCInterfaceName const _TeComPrinter_InterfaceNamesList[] = 
{
    "ITePrinter",
    0
};

const IID *  _TeComPrinter_BaseIIDList[] = 
{
    &IID_IDispatch,
    0
};


#define _TeComPrinter_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _TeComPrinter, pIID, n)

int __stdcall _TeComPrinter_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_TeComPrinter_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo TeComPrinter_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _TeComPrinter_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _TeComPrinter_StubVtblList,
    (const PCInterfaceName * ) & _TeComPrinter_InterfaceNamesList,
    (const IID ** ) & _TeComPrinter_BaseIIDList,
    & _TeComPrinter_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

