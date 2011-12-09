/******************************************************************************
* FUNCATE - GIS development team
* 
* @(#) TdkMakeConnectionFactory.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/08/02 14:23:49 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório
#ifndef __TDK_MAKE_CONNECTION_FACTORY_H
#define __TDK_MAKE_CONNECTION_FACTORY_H

#include <iostream>
#include "TdkDataTypes.h"
#include "comutil.h"

class TeDatabase;

using namespace std;

//! \class TdkMakeConnectionFactory
/*! Class to make the connection with database
*/
class TdkMakeConnectionFactory
{
	private :
		//! \brief Constructor			
		TdkMakeConnectionFactory(){};

	public :

		//! \brief build
		/*! Method to make a connection with database
			\param	type		connection type
			\param	conn		variant connection from RAD environment
			\return returns the database pointer
		*/
		static TeDatabase* build(const TDK_Connection::connType &type,VARIANT conn);

		//! \brief build
		/*! Method to make a connection with database
			\param	type			connection type
			\param	user			user name
			\param	password		password
			\param	databaseName	database name
			\param	host			host name
			\param	port			port number
			\return returns the database pointer
		*/
		static TeDatabase* build(const TDK_Connection::connType &type,const std::string &databaseName, const std::string &user="",const std::string &password="", const std::string &host="", const std::string &port="");
};


#endif


