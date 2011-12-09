#include <TdkLayoutTypes.h>
#include <TdkLayoutDatabaseObject.h>
#include <TdkAbstractCanvasDraw.h>
#include <TdkAbstractImage.h>
#include <TdkAngleProperty.h>
#include <TdkUserNameProperty.h>
#include <TdkPasswordProperty.h>
#include <TdkHostProperty.h>
#include <TdkPortProperty.h>
#include <TdkDatabaseTypeProperty.h>
#include <TdkMakeConnectionFactory.h>
#include <TdkDatabaseNameProperty.h>
#include <TdkDatabaseConnectedProperty.h>
#include <TeDatabase.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutDatabaseObject::TdkLayoutDatabaseObject(const unsigned int &id, TdkAbstractCanvasDraw *canvas, const TeBox &box, TdkAbstractImage *logo) : TdkLayoutObject(id,canvas)
{
	_type=LT_DATABASE;
	_visibleContourBox=false;
	_objectName="Database_" + Te2String(id,0);
	_logo=logo;
	_editable=false;
	_database=NULL;
	registerExtendProperties();
}


///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutDatabaseObject::~TdkLayoutDatabaseObject()
{
	if(_logo)			_logo=0;
	if(_database)		delete _database;
}


///////////////////////////////////////////////////////////////////////////////
//Draw the database logo
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutDatabaseObject::draw()
{
	double llx,lly;
	double x1,y1,x2,y2;

	if( (_canvas == NULL) || (_logo == NULL) ) return;
	_canvas->window2Viewport(_boundingBox.x1(), _boundingBox.y1(), llx,lly);
	
	_canvas->viewport2Window(0,0,x1,y1);
	_canvas->viewport2Window(25,25,x2,y2);
	x1=fabs(x1-x2);
	y1=fabs(y1-y2);
	_boundingBox=TeBox(_boundingBox.x1(), _boundingBox.y1(),_boundingBox.x1() + x1, _boundingBox.y1() + y1);
	this->subtractRulerArea();
	_canvas->drawRaster(_logo,TeBox(llx,lly,llx + 25 , lly + 25),0);
	TdkLayoutObject::draw();
	_canvas->deactivateClip();
	if(_angle)	_angle->setValue(0);
}

///////////////////////////////////////////////////////////////////////////////
//Register the Extend Properties
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutDatabaseObject::registerExtendProperties()
{
	_userName=new TdkUserNameProperty(this);
	_properties.push_back((TdkAbstractProperty*)_userName);

	_password=new TdkPasswordProperty(this);
	_properties.push_back((TdkAbstractProperty*)_password);

	_host = new TdkHostProperty(this);
	_properties.push_back((TdkAbstractProperty*)_host);

	_port = new TdkPortProperty();
	_properties.push_back((TdkAbstractProperty*)_port);

	_DbType=new TdkDatabaseTypeProperty(Access);
	_properties.push_back((TdkAbstractProperty*)_DbType);

	_databaseName= new TdkDatabaseNameProperty(this);
	_properties.push_back((TdkAbstractProperty*)_databaseName);

	_connected = new TdkDatabaseConnectedProperty(this);
	_properties.push_back((TdkAbstractProperty*)_connected);

	//teste de conexão
	_userName->setValue("postgres");
	_password->setValue("postgres");
	_DbType->setValue(PostgreSQL);
	_databaseName->setValue("rui_teste");
	_host->setValue("192.168.3.221");


}

///////////////////////////////////////////////////////////////////////////////
//Connect to database
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutDatabaseObject::connect()
{
	std::vector<TdkAbstractProperty*>::iterator it;
	_database=TdkMakeConnectionFactory::build((TDK_Connection::connType)_DbType->getValue(),_databaseName->getValue(),_userName->getValue(),_password->getValue(),_host->getValue(),_port->getValue());
	for(it=_decoratedPropertyList.begin();it!=_decoratedPropertyList.end();it++)
	{
		(*it)->update();
	}
	return (_database!=0 ? true : false);
}

///////////////////////////////////////////////////////////////////////////////
//Close connection with database
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkLayoutDatabaseObject::closeConnection()
{
	std::vector<TdkAbstractProperty*>::iterator it;
	if(_database)	delete _database;
	_database=NULL;
	for(it=_decoratedPropertyList.begin();it!=_decoratedPropertyList.end();it++)
	{
		(*it)->update();
	}
	_connected->closedConnection();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the terralib database
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////

TeDatabase* TdkLayoutDatabaseObject::getTerralibDatabase()
{
	return _database;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the database's user
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
std::string TdkLayoutDatabaseObject::getUser()
{
	if(_userName)	return _userName->getValue();
	return "";
}