#include <TdkConvertLayerToOdLayer.h>
#include <TeOdaExport.h>
#include <TeDatabase.h>
#include <TdkAbstractProcessEvent.h>
#include <TdkGeometrySettings.h>


TdkConvertLayerToOdLayer::TdkConvertLayerToOdLayer(TeOdaExport *odExport, TeDatabase *database, TdkAbstractProcessEvent *process)
{
	_database=database;
	_odExport=odExport;
	_layer=NULL;
	_process=process;
	_iProcess=0;
	_maxProcess=0;
	_cancel=NULL;
}

TdkConvertLayerToOdLayer::~TdkConvertLayerToOdLayer()
{
	_layer=NULL;
}

TeLayer* TdkConvertLayerToOdLayer::getLayer(const std::string &layerName)
{
	TeLayerMap				layerMap;
	TeLayerMap::iterator	it;

	if(_database == NULL)			throw "Invalid null database pointer";
	else if(layerName.empty())		throw "Invalid null layer name";

	layerMap=_database->layerMap();
	for(it=layerMap.begin();it!=layerMap.end();it++)
	{
		if(TeConvertToUpperCase((*it).second->name()) == TeConvertToUpperCase(layerName))
		{
			return (*it).second;
		}
	}
	TeLayer	*layer=new TeLayer();
	layer->name(layerName);
	if(!_database->loadLayer(layer))
	{
		delete layer;
		layer=NULL;
	}
	return layer;
}

bool TdkConvertLayerToOdLayer::convert(const std::string &layerName, const short &rep,const std::string &restriction, \
									   const TeColor &color, TdkGeometrySettings* settings)
{
	bool status=true;
	if(!(_layer=getLayer(layerName)))	throw "Impossible load layer";
	if( _odExport == NULL )				throw "Invalid null ODA pointer";
	_odExport->createLayer(layerName);
	_maxProcess=getTotalItemsfromLayer(_layer,rep,restriction);
	if(rep & TePOLYGONS & _layer->geomRep())  status=convertPolygons(_layer,color,restriction,settings);
	if(_cancel)	
		{
			if(*_cancel==true) return false;
		}
	if(rep & TeLINES & _layer->geomRep())	  status&=convertLines(_layer,color,restriction,settings);
	if(_cancel)	
		{
			if(*_cancel==true) return false;
		
		}
	if(rep & TeTEXT & _layer->geomRep())	 status&=convertTexts(_layer,color,restriction,settings);
	return status;
}

unsigned int TdkConvertLayerToOdLayer::getTotalItems(const std::string &tableName,const std::string &restriction)
{
	std::string			sql;
	TeDatabasePortal	*dbPortal=NULL;
	unsigned int		total;

	sql="select count(*) from " + tableName;
	if(!restriction.empty()) sql+= " " + restriction;
	dbPortal=_database->getPortal();
	if(dbPortal->query(sql) && dbPortal->fetchRow())
		total=(unsigned int)dbPortal->getInt(0);
	dbPortal->freeResult();
	delete dbPortal;
	return total;
}

unsigned TdkConvertLayerToOdLayer::getTotalItemsfromLayer(TeLayer *layer, const short &rep,const std::string &restriction)
{
	unsigned int total=0;
	if(_process)
	{
		if(layer->geomRep() & rep & TePOLYGONS)	total+=getTotalItems(layer->tableName(TePOLYGONS),restriction);
		if(layer->geomRep() & rep & TeLINES)	total+=getTotalItems(layer->tableName(TeLINES),restriction);
		if(layer->geomRep() & rep & TePOINTS)	total+=getTotalItems(layer->tableName(TePOINTS),restriction);
		if(layer->geomRep() & rep & TeTEXT)	total+=getTotalItems(layer->tableName(TeTEXT),restriction);
	}
	return total;
}

bool TdkConvertLayerToOdLayer::convertLines(TeLayer * layer, const TeColor &tcolor,const std::string &restriction, \
											TdkGeometrySettings *settings)
{
	std::string			tableName;
	std::string			sql;
	TeDatabasePortal	*dbPortal=NULL;
	bool				flag;
	OdCmColor			color;
  
	color.setRGB(tcolor.red_, tcolor.green_, tcolor.blue_);

	if(layer == NULL) throw "Invalid null layer pointer";
	tableName=layer->tableName(TeLINES);

	sql="select * from " + tableName;
	if(!restriction.empty())  sql+= " " + restriction;
	dbPortal=_database->getPortal();
	if(!dbPortal->query(sql) || !dbPortal->fetchRow())
	{
		dbPortal->freeResult();
		delete dbPortal;
		return false;
	}

	do
	{
		TeLine2D	lneRead;
		flag=dbPortal->fetchGeometry(lneRead);
		if(_process)	_process->buildingGeometryEvent(TeLINES,lneRead.geomId(),lneRead.objectId());
		if(settings) settings->setIsPolygon(false);
		_odExport->addLine2D(lneRead,color,settings);
		_iProcess++;
		if(_process) _process->processStatusEvent(_maxProcess,_iProcess);
		if(_cancel)	
		{
			if(*_cancel==true) break;
		}
	}while(flag);
	dbPortal->freeResult();
	delete dbPortal;
	return true;
}



bool TdkConvertLayerToOdLayer::convertPolygons(TeLayer * layer,const TeColor &tcolor,const std::string &restriction, \
											   TdkGeometrySettings* settings)
{
	std::string			tableName;
	std::string			sql;
	TeDatabasePortal	*dbPortal=NULL;
	bool				flag;
	unsigned int		i;
	OdCmColor			color;
  
	color.setRGB(tcolor.red_, tcolor.green_, tcolor.blue_);

	if(layer == NULL) throw "Invalid null layer pointer";
	tableName=layer->tableName(TePOLYGONS);

	sql="select * from " + tableName;
	if(!restriction.empty())  sql+= " " + restriction;
	dbPortal=_database->getPortal();
	if(!dbPortal->query(sql) || !dbPortal->fetchRow())
	{
		dbPortal->freeResult();
		delete dbPortal;
		return false;
	}

	do
	{
		TePolygon	polRead;
		flag=dbPortal->fetchGeometry(polRead);
		if(_process) 
			_process->buildingGeometryEvent(TePOLYGONS,polRead.geomId(),polRead.objectId());
		for(i=0;i<polRead.size();i++)
		{
			TeLine2D	lneRead;
			lneRead.copyElements(polRead[i]);
			if(settings) settings->setIsPolygon(true);
			_odExport->addLine2D(lneRead,color,settings);
			_iProcess++;
			if(_process) _process->processStatusEvent(_maxProcess,_iProcess);
			
		}
		if(_cancel)	
		{
			if(*_cancel==true) 
				break;
		}
	}while(flag);
	dbPortal->freeResult();
	delete dbPortal;
	return true;
}

bool TdkConvertLayerToOdLayer::convertTexts(TeLayer * layer, const TeColor &tcolor,const std::string &restriction, \
											TdkGeometrySettings *settings)
{
	std::string			tableName;
	std::string			sql;
	TeDatabasePortal	*dbPortal=NULL;
	bool				flag;
	OdCmColor			color;
  
	color.setRGB(tcolor.red_, tcolor.green_, tcolor.blue_);

	if(layer == NULL) throw "Invalid null layer pointer";
	tableName=layer->tableName(TeTEXT);

	sql="select * from " + tableName;
	if(!restriction.empty())  sql+= " " + restriction;
	dbPortal=_database->getPortal();
	if(!dbPortal->query(sql) || !dbPortal->fetchRow())
	{
		dbPortal->freeResult();
		delete dbPortal;
		return false;
	}
	do
	{
		TeText	txtRead;
		flag=dbPortal->fetchGeometry(txtRead);
		if(_process)	_process->buildingGeometryEvent(TeTEXT,txtRead.geomId(),txtRead.objectId());
		_odExport->addTeText(txtRead,color,settings);
		_iProcess++;
		if(_process) _process->processStatusEvent(_maxProcess,_iProcess);
		if(_cancel)	
		{
			if(*_cancel==true) 
				break;
		}
	}while(flag);
	dbPortal->freeResult();
	delete dbPortal;
	return true;


}