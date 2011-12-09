#include <windows.h>
#include <gdiplus.h>

#include <TdkAbstractCanvasDraw.h>
#include <TdkLayoutTypes.h>
#include <TdkLayoutImageObject.h>
#include <TdkAbstractImage.h>
#include <TdkGdiImage.h>
#include <TdkAngleProperty.h>
#include <TdkImageFileNameProperty.h>
#include <TdkLayoutNorthObject.h>
#include <TdkNorthTypeProperty.h>
#include <TdkImageProperty.h>

///////////////////////////////////////////////////////////////////////////////
//North Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutNorthObject::TdkLayoutNorthObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box \
										   , const std::string &pathName) : TdkLayoutImageObject(id,canvas,box,pathName + "\\windRoses\\north01.wmf")
{
	_type=LT_NORTH;
	_objectName="North_" + Te2String(id,0);
	_path=pathName;
	registerExtendProperties();
}

///////////////////////////////////////////////////////////////////////////////
//North Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
TdkLayoutNorthObject::~TdkLayoutNorthObject()
{
	if(_fileName) delete _fileName;
	if(_bitMap)	  delete _bitMap;	
}

///////////////////////////////////////////////////////////////////////////////
//Draw Method
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutNorthObject::draw()
{
	this->_fileName->setValue(_nortProperty->getFullValue());
	TdkLayoutImageObject::draw(); 
}

///////////////////////////////////////////////////////////////////////////////
//Register extend properties
//Author : Rui Mauricio Gregório 
//Date : 08/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutNorthObject::registerExtendProperties()
{
	_properties.erase(_properties.end() -1 ); //remove from properties the binary 
	_nortProperty=new TdkNorthTypeProperty(_path + "\\windRoses\\");
	_properties.erase(_properties.end()-1);	//remove the file name propery from list
	_properties.push_back(_nortProperty);
}

void TdkLayoutNorthObject::setNorthType(const std::string &type)
{
	
}