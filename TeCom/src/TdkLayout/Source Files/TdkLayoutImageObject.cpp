#include <windows.h>
#include <gdiplus.h>

#include <TdkAbstractCanvasDraw.h>
#include <TdkLayoutTypes.h>
#include <TdkLayoutImageObject.h>
#include <TdkAbstractImage.h>
#include <TdkGdiImage.h>
#include <TdkAngleProperty.h>
#include <TdkImageFileNameProperty.h>
#include <TdkImageProperty.h>


using namespace Gdiplus;
///////////////////////////////////////////////////////////////////////////////
//Constructor with Object Id, Canvas Pointer and Box to creation
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

TdkLayoutImageObject::TdkLayoutImageObject(const unsigned int &id, TdkAbstractCanvasDraw* canvas,const TeBox &box,const std::string &fileName) : TdkLayoutObject(id,canvas)
{
	_type=LT_IMAGE;
	this->registerExtendProperties();
	_fileName->setValue(fileName);
	_visibleContourBox=false;
	_objectName="Image_" + Te2String(id,0);
	if(!_fileName->getValue().empty())		_bitMap->Create(_fileName->getValue()); 
	else									_bitMap->Clear();
	if( (_bitMap->getImage() != NULL) && ( (box.height() == 0) || (box.width() == 0 )) )	_boundingBox=TeBox(0,0,_bitMap->getWidth(),_bitMap->getHeight());
	else																					_boundingBox=box;
	_objectName="Image_" + Te2String(id,0);
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

TdkLayoutImageObject::~TdkLayoutImageObject()
{

}

///////////////////////////////////////////////////////////////////////////////
//Set file image to layout object
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutImageObject::setImageFileName(const std::string &fileName)
{
	if(_bitMap->getImage()) _bitMap->Clear();
	_fileName->setValue(fileName);
	if(!fileName.empty())	_bitMap->Create(_fileName->getValue());
	else					_bitMap->Clear();
}

///////////////////////////////////////////////////////////////////////////////
//Draw Image Object
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutImageObject::draw()
{
	double llx,lly;
	double urx, ury;

	if( (_canvas == NULL) ) return;
	_canvas->window2Viewport(_boundingBox.x1(), _boundingBox.y1(), llx,lly);
	_canvas->window2Viewport(_boundingBox.x2(), _boundingBox.y2(), urx,ury);
	this->subtractRulerArea();

	if(_bitMap->getImage() == 0)
	{
		if(!_fileName->getValue().empty())	_bitMap->Create(_fileName->getValue());
		if(_bitMap->getImage() == 0) return;
	}

	if(_bitMap->getFileName() == "LMemory")							
	{
		std::string fileName;
		fileName=extractFileName(_fileName->getValue());
		_bitMap->setAbstractFileName(fileName);
		_fileName->setValue(fileName);
	}
	if( (_bitMap->getFileName() != _fileName->getValue()))			_bitMap->setFileName(_fileName->getValue());
	_canvas->drawRaster(_bitMap->getImage(),TeBox(llx,lly,urx,ury),_angle->getValue());
	TdkLayoutObject::draw();
	_canvas->deactivateClip();
}

///////////////////////////////////////////////////////////////////////////////
//Print the Image Object
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutImageObject::print(TdkAbstractCanvasDraw* canvas)
{
	double llx,lly;
	double urx, ury;
	double percentH=0,percentW=0;

	if( (canvas == NULL) ) return;
	canvas->window2Viewport(_boundingBox.x1(), _boundingBox.y1(), llx,lly);
	canvas->window2Viewport(_boundingBox.x2() + percentW, _boundingBox.y2() + percentH, urx,ury);
	canvas->drawRaster(_bitMap->getImage(),TeBox(llx,lly,urx,ury),_angle->getValue());
}

///////////////////////////////////////////////////////////////////////////////
//Set file image to layout object
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutImageObject::clear()
{
	if(_bitMap->getImage()) _bitMap->setFileName("");
}

///////////////////////////////////////////////////////////////////////////////
//Set Image Bounding Box
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

void TdkLayoutImageObject::setBoundingBox(const TeBox &box)
{
	double	width=100;
	double	 height=100;
	if(box.isValid()) _boundingBox=box;
	if(_bitMap->getImage())
	{
		width=(_bitMap->getWidth() * 25.4)/300.0;
		height=(_bitMap->getHeight() * 25.4)/300.0;
	}

	if(!_boundingBox.isValid())											_boundingBox=TeBox(0,0,width,height);
	if( (_boundingBox.width() <= 0) || (_boundingBox.height() <= 0))	_boundingBox=TeBox(_boundingBox.x1(),_boundingBox.y1(),_boundingBox.x1() + width, _boundingBox.y1() + height);
}

///////////////////////////////////////////////////////////////////////////////
//Register the Extend Properties
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
void TdkLayoutImageObject::registerExtendProperties()
{
	_fileName= new TdkImageFileNameProperty();
	_properties.push_back((TdkAbstractProperty*)_fileName);

	_bitMap=new TdkImageProperty();
	_properties.push_back((TdkAbstractProperty*)_bitMap);
}

///////////////////////////////////////////////////////////////////////////////
//Extract exact file name
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////
std::string TdkLayoutImageObject::extractFileName(const std::string &fileName)
{
	int		i;
	std::string			result;
	
	if(fileName.size() < 3) return fileName;
	for(i=(int)fileName.size() - 1; i > 0 ; i--)
	{
		if(fileName[i] == '\\') break;
	}
	for(i++;i<(int)fileName.size();i++)
	result+=fileName[i];
	return result;
}