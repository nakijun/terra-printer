#include <TdkPageSize.h>

///////////////////////////////////////////////////////////////////////////////
//Empty Constructor
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
TdkPageSize::TdkPageSize()
{
	_sizeValue[A0].width=841;
	_sizeValue[A0].height=1189;
	_sizeValue[A1].width=594;
	_sizeValue[A1].height=841;
	_sizeValue[A2].width=420;
	_sizeValue[A2].height=594;
	_sizeValue[A3].width=297;
	_sizeValue[A3].height=420;
	_sizeValue[A4].width=210;
	_sizeValue[A4].height=297;
	_sizeValue[A5].width=148;
	_sizeValue[A5].height=210;
	_sizeValue[A6].width=105;
	_sizeValue[A6].height=148;
	_sizeValue[Custom].width=210;
	_sizeValue[Custom].height=297;

	_pageSize=A4;
	_pageOrientation=portrait;
	
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
TdkPageSize::~TdkPageSize()
{

}

///////////////////////////////////////////////////////////////////////////////
//Set Page Orientation ( Portrait or Landscape )
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
 void TdkPageSize::setOrientation(const pageOrientation &orientation)
 {
	_pageOrientation=orientation;
 }

///////////////////////////////////////////////////////////////////////////////
//Returns the page Orientation
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
 pageOrientation TdkPageSize::getOrientation()
 {
	return _pageOrientation;
 }

///////////////////////////////////////////////////////////////////////////////
//Set Page Size
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
 void TdkPageSize::setSize(const pageSize &size)
 {
	_pageSize=size;
 }

///////////////////////////////////////////////////////////////////////////////
//Returns the page size
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
pageSize TdkPageSize::getSize()
{
	return _pageSize;
}

///////////////////////////////////////////////////////////////////////////////
//Set Custom Page Size
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
void TdkPageSize::setCustomSize(const double &width, const double &height)
{
	_sizeValue[Custom].width=width;
	_sizeValue[Custom].height=height;
	_pageSize=Custom;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the page width
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
double TdkPageSize::getWidth()
{
	mapDimension::iterator	it;

	if((it=_sizeValue.find(_pageSize))!=_sizeValue.end())
	{
		if(_pageOrientation == portrait)	return it->second.width;
		else								return it->second.height;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the page height
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
double TdkPageSize::getHeight()
{
	mapDimension::iterator	it;

	if((it=_sizeValue.find(_pageSize))!=_sizeValue.end())
	{
		if(_pageOrientation == portrait)	return it->second.height;
		else								return it->second.width;
	}
	return 0;

}

///////////////////////////////////////////////////////////////////////////////
//Returns the horizontal page center
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
double TdkPageSize::getCenterWidth()
{
	return this->getWidth()/2.0;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the vertical page center
//Author : Rui Mauricio Gregório 
//Date : 12/2008
///////////////////////////////////////////////////////////////////////////////
double TdkPageSize::getCenterHeight()
{
	return this->getHeight()/2.0;
}