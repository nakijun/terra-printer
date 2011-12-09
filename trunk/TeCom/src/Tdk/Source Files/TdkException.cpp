/**
 * Tecgraf - GIS development team
 * 
 * Tdk Framework
 * 
 * @(#) TdkExeption.cpp
 */  

/*
** ---------------------------------------------------------------
** Includes:
*/
#include "TdkException.h"
#ifdef LOGGER_ON
#include "TdkLogger.h"
#endif
#include "TeUtils.h"
#include <string>

/*
** ---------------------------------------------------------------
** Methods:
*/

TdkException::TdkException(std::string src_file_name,
						   int src_file_line,
						   int error_code, 
						   std::string more_info) throw ()
{
	codeError_= error_code;
	moreInfo_ = more_info;
	setDebugInfo(src_file_name, src_file_line);
}

TdkException::TdkException(std::string src_file_name,
						   int src_file_line,
						   std::string error_msg) throw ()
{
	codeError_= -1;
	setDebugInfo(src_file_name, src_file_line);
	message_ = error_msg;
}

const char* TdkException::trace() throw ()
{
	
	if (codeError_ != -1)
	{
		setMessagesMap();
		message_ = getMessageFromMap(codeError_);
	}
	
	if (moreInfo_.length())
		message_ += "\n" + moreInfo_;

#ifdef _DEBUG
	if (debugInfo_.length())
		message_ += "\n\n" + debugInfo_;
	message_ += "\n\n";	
#endif

	std::string printInfo = message_;

#ifdef _DEBUG				
	if (debugInfo_.length())
		printInfo += "\n\n" + debugInfo_;
#endif

#ifdef LOGGER_ON
			TdkLogger::writeToFile(printInfo);
#endif
	
	return message_.c_str();
}

const char* TdkException::msg() throw ()
{
	setMessagesMap();

	message_ = getMessageFromMap(codeError_);
	
	if (moreInfo_.length())
		message_ += "\n" + moreInfo_;

#ifdef LOGGER_ON
			TdkLogger::writeToFile(message_);
#endif


	return message_.c_str();
}

const int TdkException::getCodeError() throw()
{
	return codeError_;
}

void TdkException::setDebugInfo(std::string src_file_name,
						   int src_file_line) throw()
{
//#ifdef _DEBUG
	//debug settings
	debugInfo_ += "\n\nDebug details...";
	if (src_file_name.length())
		debugInfo_ += "\nSource file: " + src_file_name;
	if (src_file_line != -1)
	{
		debugInfo_ += "\nLine: ";
		debugInfo_ += Te2String (src_file_line);
	}
	debugInfo_ += "\n\n";
//#endif
}

std::string TdkException::getMessageFromMap(int code_error) throw()
{
	_MSG_MAP::iterator it = msgMap_.find(code_error);
    if (it != msgMap_.end())
		return (*it).second;
	return "";
}

/*
** ---------------------------------------------------------------
** End:
*/

