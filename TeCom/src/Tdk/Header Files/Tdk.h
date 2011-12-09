#ifndef  __TDK_INTERNAL_DEFINES_H
#define  __TDK_INTERNAL_DEFINES_H

#ifdef WIN32

	#pragma warning(disable : 4251)
	#pragma warning(disable : 4275)
	#pragma warning(disable : 4290)
	#pragma warning(disable : 4482)

	#ifdef TDK_EXPORTS
		#define TDK_API  __declspec(dllexport)   // export DLL information
	#else
		#define TDK_API  __declspec(dllimport)   // import DLL information
	#endif 
#else
	#define TDK_API
#endif


#endif


//isto é um teste