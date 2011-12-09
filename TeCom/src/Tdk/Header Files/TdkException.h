/**
 * Tecgraf - GIS development team
 * 
 * Tdk Framework
 * 
 * @(#) TdkExeption.h
 */  

/*
** ---------------------------------------------------------------
** Defines:
*/

#ifndef TdkException__h_h
#define TdkException__h_h

#ifdef WIN32
#pragma warning (disable: 4290)
#endif


/*
** ---------------------------------------------------------------
** Includes:
*/

//TDK include files
#include <tdk.h>

//STL include files
#include <string>
#include <map>

/*
** ---------------------------------------------------------------
** Macros:
*/

//! This macro is used to replace the debug parameters of the TdkException constructor. 
#define _TDK_DEBUG __FILE__,__LINE__ 

//! The message map type definition.
typedef std::map<int, std::string> _MSG_MAP;

/*
** ---------------------------------------------------------------
** Definition:
*/

//! Provides a class for handling exceptions on Tdk framework.
/*!
 \Todo:
 1) Document this class

   @ingroup core
*/
class TDK_API TdkException
{

// properties	
public:

    virtual ~TdkException(){};

    enum {
		UndefinedError,
			FatalError,
			InvalidValue,
			InvalidArgument,
			MemoryAllocation,
			OutOfMemory,
			TypeCasting,//Not used
			OutOfBoundary,
			FileNotFound,
			NoCurrentView,
			NoSelectedTheme,
			EmptyEventComposite,
			ExistentEventComposite,
			MrSIDError,
			ShapefileError,
			NoAvailableUndo,
			NoAvailableRedo,
			InvalidPointEditionInit,// This is beeing used in place of the two types below
			InvalidEditionPropertiesInit,// This is beeing used in place of the two types below
			NoSelectedObject,//not used in IUPVIPE
			MultipleSelectedObjects,//not used in IUPVIPE
			NoUserPermission,
			UserNotFound,
			RoleNotFound,
			NoTableSelected,
			ExistentTheme,
			ExistentLayer// not used in IUPVIPE
		};

protected:
	int codeError_; //!< The error code.
	std::string message_; //!< The error message.
	std::string debugInfo_; //!< Debug information about the moment when the exception happened: class, method, source file, line number. 
	std::string moreInfo_; //!< More information will show with the error message.
	_MSG_MAP msgMap_; //!< The message map indexed by the error code.

// methods

	//! Sets the message map.
	virtual void setMessagesMap();

	//! Sets the debug information.
	void setDebugInfo(std::string src_file_name, int src_file_line ) throw();

	//! Returns a message from the map corresponding to the given error code.
	std::string getMessageFromMap(int code_error) throw();

public:
	
	//! Construtor: The error message based on the error coded.
    TdkException(std::string src_file_name, //!< Name of the source file where the exception happened.
					int src_file_line, //!< Line number of the source file where the exception happened.
					int error_code,  //!< Error code associated with the exception.
					std::string more_info="" //!< This extra information must be showed with the error message.
					) throw();

	//! Construtor: Free error message.
    TdkException(std::string src_file_name="", //!< Name of the source file where the exception happened.
					int src_file_line=-1, //!< Line number of the source file where the exception happened.
					std::string error_msg="" //!< The error message.
					) throw();

	//! Returns a detailed error message: error message + more information + debug information (if DEBUG).
	const char* trace() throw();

	//! Returns a simples error message: error message + more information
	const char* msg() throw();
	
	//! Returns the error message code.
	const int getCodeError() throw();
};

/*
** ---------------------------------------------------------------
** Inline Methods:
*/

inline void TdkException::setMessagesMap(){
		//msgMap_[UndefinedError] = "Undefined error.";
		//msgMap_[FatalError]  = "Fatal error.";
		//msgMap_[InvalidValue]	  = "Invalid value.";
		//msgMap_[InvalidArgument]	  = "Invalid argument.";
		//msgMap_[MemoryAllocation]= "Memory allocation problem.";
		//msgMap_[OutOfMemory] = "Out of memory problem.";
		//msgMap_[TypeCasting] = "Type casting error.";
		//msgMap_[OutOfBoundary] = "The value is out of boundary.";
		//msgMap_[FileNotFound] = "File not found.";
		//msgMap_[NoCurrentView] = "No current view.";
		//msgMap_[NoSelectedTheme] = "No selected theme.";
		//msgMap_[EmptyEventComposite] = "The event composite is empty.";
		//msgMap_[ExistentEventComposite] = "Event composite already opened.";
		//msgMap_[MrSIDError] = "MrSID error.";
		//msgMap_[ShapefileError] = "Shapefile error.";
		//msgMap_[NoAvailableUndo] = "No available undo.";
		//msgMap_[NoAvailableRedo] = "No available redo.";
		//msgMap_[InvalidPointEditionInit] = "Invalid point edition initialization.";
		//msgMap_[InvalidEditionPropertiesInit] = "Invalid properties edition initialization.";
		//msgMap_[NoSelectedObject] = "No selected Object.";
		//msgMap_[MultipleSelectedObjects] = "Multiple selected Object.";
		//msgMap_[NoUserPermission] = "No user permission.";
		//msgMap_[UserNotFound] = "User not found.";
		//msgMap_[RoleNotFound] = "Authenticate role not found.";
		//msgMap_[NoTableSelected] = "Error when load table selected.";
		//msgMap_[ExistentTheme] = "Theme already created with the same name.";
		//msgMap_[ExistentLayer] = "Layer already created with the same name.";
}


#endif
/*
** ---------------------------------------------------------------
** End:
*/

