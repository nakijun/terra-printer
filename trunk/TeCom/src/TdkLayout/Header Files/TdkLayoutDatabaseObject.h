/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkLayoutDatabaseObject.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/08/04 20:19:06 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório

#ifndef __TDK_LAYOUT_DATABASE_OBJECT_H
#define __TDK_LAYOUT_DATABASE_OBJECT_H


#include <TdkLayoutObject.h>

class TdkAbstractCanvasDraw;
class TdkAbstractImage;
class TdkUserNameProperty;
class TeDatabase;
class TdkPasswordProperty;
class TdkHostProperty;
class TdkPortProperty;
class TdkDatabaseTypeProperty;
class TdkDatabaseNameProperty;
class TdkDatabaseConnectedProperty;


#define __databaseType "__databaseType"

class TdkLayoutDatabaseObject : public TdkLayoutObject
{
protected:

		TdkAbstractImage	*_logo;

		TdkUserNameProperty	*_userName;

		TdkPasswordProperty *_password;

		TdkHostProperty		*_host;

		TdkPortProperty		*_port;

		TeDatabase			*_database;

		TdkDatabaseTypeProperty	*_DbType;

		TdkDatabaseNameProperty *_databaseName;

		TdkDatabaseConnectedProperty* _connected;
public:

		//! \brief Constructor
		TdkLayoutDatabaseObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box,TdkAbstractImage *logo);

		//! \brief Destructor
		~TdkLayoutDatabaseObject();

		//! \brief Draw
		/*! Method to draw the text object on 
			Back Buffer
		*/
		virtual void draw();


		//! \brief print
		/*! Method to print the object
			\param	canvas		canvas pointer
		*/
		virtual void print(TdkAbstractCanvasDraw *canvas){};

		//! \brief registerExtendProperties
		/*! Register extend properties
		*/
		virtual void registerExtendProperties();
	
		//! \brief connect
		/*! Connect to database
		*/
		virtual bool connect();

		//! \brief closeConnection
		/*! Close connection with database
		*/
		virtual bool closeConnection();

		//! \brief getTerralibDatabase
		/*! Returns the terralib database
		*/
		virtual TeDatabase* getTerralibDatabase();

		//! \brief Return the database's user
		virtual std::string getUser();

		
};

#endif

