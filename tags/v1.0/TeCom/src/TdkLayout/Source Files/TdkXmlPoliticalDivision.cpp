
#include <TdkXmlPoliticalDivision.h>
#include <TdkXmlItem.h>

///////////////////////////////////////////////////////////////////////////////
//Contructor
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TdkXmlPoliticalDivision::TdkXmlPoliticalDivision()
{

}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TdkXmlPoliticalDivision::~TdkXmlPoliticalDivision()
{

}

///////////////////////////////////////////////////////////////////////////////
//Returns the polygons list
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TePolygonSet TdkXmlPoliticalDivision::getPolygons()
{
	return _plsStates;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the lines list
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TeLineSet	TdkXmlPoliticalDivision::getLines()
{
	return _lnsStates;
}


///////////////////////////////////////////////////////////////////////////////
//Returns the points list
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TePointSet	TdkXmlPoliticalDivision::getPoints()
{
	return _ptsStates;
}


///////////////////////////////////////////////////////////////////////////////
//Open
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlPoliticalDivision::open(const std::string &fileName)
{
	xmlTextReaderPtr	xml;
	TdkXmlItem*			xmlMemory=0;
	
	if((xml=openXmlFile(fileName)) != 0)
	{
		xmlMemory=new TdkXmlItem();
		loadToMemory(xml,xmlMemory);
		xmlTextReaderClose(xml);
		_plsStates=getPolygons(xmlMemory);
		delete xmlMemory;
		if(_plsStates.empty() == false) return true;
	}
	return false;
}


///////////////////////////////////////////////////////////////////////////////
//Open gml file
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
xmlTextReaderPtr TdkXmlPoliticalDivision::openXmlFile(const std::string &fileName)
{
	xmlTextReaderPtr xml;
    xml = xmlReaderForFile(fileName.c_str(), NULL, 0);
	return xml;
}

///////////////////////////////////////////////////////////////////////////////
//Load gml to memory
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlPoliticalDivision::loadToMemory(xmlTextReaderPtr xml, TdkXmlItem* item)
{
	int				fstatus;
	int				type;
	int				isEmpty;
	const			xmlChar *name, *value;
	TdkXmlItem		*subItem=0;
	bool			status=true;
	
	if(item == 0) item=new TdkXmlItem();
	do
	{
		if((fstatus=xmlTextReaderRead(xml)) != 1)	
		{
			break;
		}
		name = xmlTextReaderConstName(xml);
		if (name == NULL)	name = BAD_CAST "0";
		value = xmlTextReaderConstValue(xml);
		type=xmlTextReaderNodeType(xml);
		isEmpty=xmlTextReaderIsEmptyElement(xml);

		if(type == Element)
		{
			subItem=new TdkXmlItem();
			subItem->setName(std::string((char*)name));
			item->addItem(subItem);
		}else if(type == Text)
		{
			item->getItem()->setValue(std::string((char*)value));
			continue;
		}
		else if(type == Comment)	continue;
		else if(type == Undefined)	continue;
		else if(type == EndElement)	return true;
		if((status=loadToMemory(xml,item->getItem())) == true)
		{
			item->close();
		}

	}while(status);
	return true;
}


///////////////////////////////////////////////////////////////////////////////
//Returns the polygons list
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TePolygonSet TdkXmlPoliticalDivision::getPolygons(TdkXmlItem* xmlItem)
{
	TdkXmlItem								*item;
	std::vector<TdkXmlItem*>				subItem;
	TdkXmlItem								*polItem;
	std::vector<TdkXmlItem*>::iterator		it;
	TePolygonSet							plsRead;
	TePolygon								polRead;


	if((item=xmlItem->searchItem("gml:FeatureCollection")) == 0)	return plsRead;
	subItem=item->getSubItem();
	for(it=subItem.begin();it!=subItem.end();it++)
	{
			if( (polItem=(*it)->searchItem("gml:posList"))!=0)
			{
				polRead=decoderPolygon(polItem->getValue());
				if(polRead.size()) plsRead.add(polRead);
			}
	}
	return plsRead;
}


///////////////////////////////////////////////////////////////////////////////
//decoder polygon from gml
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
TePolygon TdkXmlPoliticalDivision::decoderPolygon(const std::string &value)
{
	TePolygon		polRead;
	TeLine2D		lneRead;
	double			x,y;
	std::string		number;
	unsigned int	i;
	bool			bNext = false;


	for(i=0;i<value.size();i++)
	{
		if( ((value[i] == ',') || (value[i] == ' ')) && ( bNext == false) )
		{
			x=(double)atof(number.c_str());
			number.clear();
			bNext=true;
		}else if( (value[i] == ' ') && (bNext == true))
		{
			y=(double) atof(number.c_str());
			number.clear();
			lneRead.add(TeCoord2D(x,y));
			bNext=false;
		}else number+=value[i];
	}
	if(lneRead.size() > 3)	polRead.add(lneRead);
	return polRead;
}

///////////////////////////////////////////////////////////////////////////////
//Return is valid ( whether there are geometries on memory )
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
bool TdkXmlPoliticalDivision::isValid()
{
	return  ((!_plsStates.empty()) | (!_lnsStates.empty()) | (!_ptsStates.empty()));
}

TeBox TdkXmlPoliticalDivision::getBox()
{
	TeBox		box;

	if(_plsStates.box().isValid()) updateBox(box,_plsStates.box());
	if(_lnsStates.box().isValid()) updateBox(box,_lnsStates.box());
	if(_ptsStates.box().isValid()) updateBox(box,_ptsStates.box());

	return box;
}