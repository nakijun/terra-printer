#include <TdkGdiPoint.h>
#include <TdkGdiLine.h>
#include <TdkGdiPolygon.h>
#include <TdkGdiText.h>
#include "TdkAbstractCanvasDraw.h"
#include "TdkGdiCanvasDraw.h"
#include <TdkAbstractImage.h>
#include <TdkGdiImage.h>
#include <TdkDecoderGdiImage.h>
#include <TeRaster.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiCanvasDraw::TdkGdiCanvasDraw(HWND hWnd) : TdkAbstractCanvasDraw(1)
{
	_hWnd=hWnd;
	_dc=NULL;
	GdiplusStartup(&_gdiplusToken, &_gdiplusStartupInput, NULL);
	_defaultGraphics=new Graphics(_hWnd);
	_currentGraphics=_defaultGraphics;
	_currentBufferId=TdkAbstractCanvasDraw::cbrFront;
	_fontString=new Font(L"Verdana",10);
	_fontForeColor=new SolidBrush(Color(0,0,0));
	_drawPoint=new TdkGdiPoint();
	_drawLine=new TdkGdiLine();
	_drawPolygon=new TdkGdiPolygon();
	_drawText=new TdkGdiText();
	_dpiRatio=1;
	
}

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiCanvasDraw::TdkGdiCanvasDraw(HDC dc, const double &dpiRatio): TdkAbstractCanvasDraw(1)
{
	_hWnd=NULL;
	_dc=dc;
	GdiplusStartup(&_gdiplusToken, &_gdiplusStartupInput, NULL);
	_defaultGraphics=new Graphics(_dc);
	_currentGraphics=_defaultGraphics;
	_currentBufferId=TdkAbstractCanvasDraw::cbrFront;
	_fontString=new Font(L"Verdana",10);
	_fontForeColor=new SolidBrush(Color(0,0,0));
	_drawPoint=new TdkGdiPoint();
	_drawLine=new TdkGdiLine();
	_drawPolygon=new TdkGdiPolygon();
	_drawText=new TdkGdiText();
	_dpiRatio=dpiRatio;

	SetMapMode(_dc,MM_TEXT);
	_defaultGraphics->SetPageUnit(Gdiplus::UnitPixel); 

}



///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiCanvasDraw::~TdkGdiCanvasDraw()
{
	removeAllBuffers();
	if(_defaultGraphics) delete _defaultGraphics;
	if(_fontString)		 delete _fontString;
	if(_fontForeColor)	 delete _fontForeColor;
	if(_drawPoint)		 delete _drawPoint;
	if(_drawPolygon)	 delete _drawPolygon;
	if(_drawText)		 delete _drawText;
	GdiplusShutdown(_gdiplusToken);
}


///////////////////////////////////////////////////////////////////////////////
//Returns the Client Area
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGdiCanvasDraw::getClientArea(RECT &rectangle)
{
	if(_hWnd)
	{
		bool status=(GetClientRect(_hWnd,&rectangle) ? true : false);
		return status;
	}else if(_dc)
	{
		rectangle.left=0;
		rectangle.top=0;
		rectangle.right=GetDeviceCaps(_dc, HORZRES);
		rectangle.bottom=GetDeviceCaps(_dc, VERTRES);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the dimensions in millimeter
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::getDimensionMM(double& width, double& height)
{
	RECT	rectangle;

	if((!getClientArea(rectangle)) || (_currentGraphics==NULL))
	{
		width=0;
		height=0;
		return;
	}
	width=((rectangle.right-rectangle.left)/_currentGraphics->GetDpiX()) * inch10;
	height=((rectangle.bottom-rectangle.top)/_currentGraphics->GetDpiY()) * inch10;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the width of client area
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
double TdkGdiCanvasDraw::getWidth()
{
	RECT	rectangle;
	if(getClientArea(rectangle))
	{
		return rectangle.right-rectangle.left;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the height of client area
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
double TdkGdiCanvasDraw::getHeight()
{
	RECT	rectangle;
	if(getClientArea(rectangle))
	{
		return rectangle.bottom-rectangle.top;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Sets Active buffer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
int TdkGdiCanvasDraw::setActiveBuffer(const int& bufferId)
{
	bitmapList::iterator	it;
	
	if(_currentGraphics!=_defaultGraphics)
	{
		delete _currentGraphics;
		_currentGraphics=NULL;
	}
	if(bufferId==TdkAbstractCanvasDraw::cbrFront)
	{
		_currentGraphics=_defaultGraphics;
	}else
	{
		if((it=_bufferList.find(bufferId))!=_bufferList.end())
		{
			_currentGraphics=new Graphics(it->second);
		}else
		{
			throw "Buffer Id not found";
		}
	}
	_currentGraphics->SetCompositingQuality(Gdiplus::CompositingQualityDefault);
	_currentGraphics->SetTextRenderingHint(TextRenderingHintAntiAlias);
	_currentBufferId=bufferId;
	return bufferId;
}

///////////////////////////////////////////////////////////////////////////////
//Add a new buffer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
int TdkGdiCanvasDraw::addBuffer(const int& bufferId)
{
	return addBuffer(0,0,bufferId);
}

///////////////////////////////////////////////////////////////////////////////
//Add a new buffer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
int TdkGdiCanvasDraw::addBuffer(const double& width, const double& height, const int& bufferId)
{
	Gdiplus::Bitmap			*newBuffer;
	RECT					rectangle;
	INT						iWidth;
	INT						iHeight;
	bitmapList::iterator	it;

	
	it=_bufferList.find(bufferId);

	if(it!=_bufferList.end())				return bufferId;
	else if((!getClientArea(rectangle)))	return -1;
	

	if((!width) && (!height))
	{
		iWidth=(INT)(rectangle.right-rectangle.left);
		iHeight=(INT)(rectangle.bottom-rectangle.top);
	}else
	{
		iWidth=(INT) width;
		iHeight=(INT) height;
	}
	newBuffer = new Gdiplus::Bitmap(iWidth,iHeight);
	_bufferList[bufferId]=newBuffer;
	return bufferId;
}

///////////////////////////////////////////////////////////////////////////////
//Clear current buffer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::clear()
{
	if(_currentGraphics)
	{
		_currentGraphics->Clear(Color(_backgroundColor.red_,_backgroundColor.green_,_backgroundColor.blue_));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Remove all buffer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::removeAllBuffers()
{
	bitmapList::iterator	it;

	for(it=_bufferList.begin();it!=_bufferList.end();it++)
	{
		if(it->second!=NULL)
		{
			delete it->second;
			it->second=NULL;
		}
	}
	_bufferList.clear();
}

///////////////////////////////////////////////////////////////////////////////
//Remove buffer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::removeBuffer(const int& bufferId)
{
	bitmapList::iterator	it;

	if((it=_bufferList.find(bufferId))==_bufferList.end())
	{
		throw "Buffer Id not found!";
	}

	if(_currentBufferId==bufferId)
	{
		delete _currentGraphics;
		_currentGraphics=_defaultGraphics;
	}

	if(it->second)
	{
		delete it->second;
		it->second=NULL;
	}
	_bufferList.erase(it);
}

///////////////////////////////////////////////////////////////////////////////
//Resize buffer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::resizeBuffer(const int& bufferId, const double& width, const double& height)
{
	bitmapList::iterator	it;
	Gdiplus::Bitmap			*resizeBitmap=NULL;
	double					w,h;

	w=width;
	h=height;
	if((w==-1) || (h==-1))
	{
		w=this->getWidth();
		h=this->getHeight();
	}

	if((it=_bufferList.find(bufferId))==_bufferList.end())
	{
		throw "Buffer Id not found!";
	}

	if(it->second)
	{
		resizeBitmap=new Gdiplus::Bitmap((INT)w,(INT)h);
		delete it->second;
		it->second=NULL;
	}else
	{
		resizeBitmap=new Gdiplus::Bitmap((INT)w,(INT)h);
	}
	_bufferList[bufferId]=resizeBitmap;

	if(_currentBufferId==bufferId)
	{
		delete _currentGraphics;
		_currentGraphics=new Graphics(resizeBitmap);
		_currentGraphics->Clear(Color(_backgroundColor.red_,_backgroundColor.green_,_backgroundColor.blue_));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Write buffer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::writeBuffer(const int& sourceBuff, const int& destinationBuff,const bool& transparent ,
			                    const int& r, const int& g,const int& b, const int& a )
{
	bitmapList::iterator	itSource;
	bitmapList::iterator	itDest;
	Graphics				*destGraph;
	bool					newGraph=false;

	if((itSource=_bufferList.find(sourceBuff))==_bufferList.end())
	{
		throw "Source buffer Id not found!";
	}
	
	if(destinationBuff==TdkAbstractCanvasDraw::cbrFront)
	{
		destGraph=_defaultGraphics;
	}else
	{
		if((itDest=_bufferList.find(destinationBuff))==_bufferList.end())
		{
			throw "Source buffer Id not found!";
		}
		destGraph=new Graphics(itDest->second);
		newGraph=true;
	}
	
	if(transparent)
	{
		ImageAttributes remapAttributes;
		remapAttributes.SetColorKey(Color(a,r,g,b),Color(a,r,g,b));
		destGraph->DrawImage(itSource->second,0,0,0,0,itSource->second->GetWidth(),itSource->second->GetHeight(), \
		UnitPixel,&remapAttributes,NULL,NULL);
	}else
	{
		destGraph->DrawImage(itSource->second,0,0);
	}
	if(newGraph)
	{
		delete destGraph;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Write buffer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::writeBuffer(const int& sourceBuff, const int& destinationBuff, const double& srcX, 
                            const double& srcY, const double& srcW, const double& srcH, 
                            const double& dstX, const double& dstY, const double& angle)
{
	bitmapList::iterator	itSource;
	bitmapList::iterator	itDest;
	Graphics				*destGraph;
	bool					newGraph=false;

	if((itSource=_bufferList.find(sourceBuff))==_bufferList.end())
	{
		throw "Source buffer Id not found!";
	}
	
	if(destinationBuff==TdkAbstractCanvasDraw::cbrFront)
	{
		destGraph=_defaultGraphics;
	}else
	{
		if((itDest=_bufferList.find(destinationBuff))==_bufferList.end())
		{
			throw "Source buffer Id not found!";
		}
		destGraph=new Graphics(itDest->second);
		newGraph=true;
	}

	Gdiplus::Region region;
	if(!_currentGraphics->IsClipEmpty())
	{
		_currentGraphics->GetClip(&region);
		destGraph->SetClip(&region);
	}
	if(angle)
	{	
		
		
		destGraph->TranslateTransform((REAL)(dstX + (srcW/2.)),(REAL)(dstY + (srcH/2)));
		destGraph->RotateTransform((REAL)angle);
		destGraph->DrawImage(itSource->second,(REAL)(-(srcW/2.)),(REAL)(-(srcH/2)),(REAL)srcX,(REAL)srcY,(REAL)srcW,(REAL)srcH,UnitPixel);
		destGraph->ResetTransform();
	
	}
	else
	{
		destGraph->DrawImage(itSource->second,(INT)dstX,(INT)dstY,(INT)srcX,(INT)srcY,(INT)srcW,(INT)srcH,UnitPixel);
	}
	destGraph->ResetClip();
	if(newGraph)
	{
		delete destGraph;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Write buffer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::writeBuffer(const int& sourceBuff, const int& destinationBuff, const double& srcX, 
                            const double& srcY, const double& srcW, const double& srcH, 
                            const double& dstX, const double& dstY)
{
	writeBuffer(sourceBuff,destinationBuff,srcX,srcY,srcW,srcH,dstX,dstY,0);
}


///////////////////////////////////////////////////////////////////////////////
//Write buffer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::writeBuffer(const int& sourceBuff, const int& destinationBuff, const double& srcX, 
                            const double& srcY, const double& srcW, const double& srcH, 
                            const double& dstX, const double& dstY, const double& dstW, const double& dstH, double angle)
{
	RectF	recSource((REAL)srcX,(REAL)srcY,(REAL)srcW,(REAL)srcH);
	RectF	recDest((REAL)dstX,(REAL)dstY,(REAL)dstW,(REAL)dstH);

	bitmapList::iterator	itSource;
	bitmapList::iterator	itDest;
	Graphics				*destGraph;
	bool					newGraph=false;
	double					x,y;

	if((itSource=_bufferList.find(sourceBuff))==_bufferList.end())
	{
		throw "Source buffer Id not found!";
	}
	
	if(destinationBuff==TdkAbstractCanvasDraw::cbrFront)
	{
		destGraph=_defaultGraphics;
	}else
	{
		if((itDest=_bufferList.find(destinationBuff))==_bufferList.end())
		{
			throw "Source buffer Id not found!";
		}
		destGraph=new Graphics(itDest->second);
		newGraph=true;
	}

	if(angle)
	{
		x=dstW/2.0;
		y=dstH/2;
		RectF rec((REAL)-x,(REAL)-y,(REAL)dstW,(REAL)dstH);
		destGraph->TranslateTransform((REAL)(dstX + (dstW/2.)),(REAL)(dstY + (dstH/2)));
		destGraph->RotateTransform((REAL)angle);
		destGraph->DrawImage(itSource->second,rec,(REAL)srcX,(REAL)srcY,(REAL)srcW,(REAL)srcH,UnitPixel,NULL, NULL,NULL);
		destGraph->ResetTransform();
	}
	else
	{
		destGraph->DrawImage((Gdiplus::Image*)itSource->second,recDest,(REAL)srcX,(REAL)srcY,(REAL)srcW,(REAL)srcH,UnitPixel);
	}
	
	if(newGraph)
	{
		delete destGraph;
	}

}

///////////////////////////////////////////////////////////////////////////////
//Write buffer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::writeBuffer(const int& sourceBuff, const int& destinationBuff, const double& srcX, 
                            const double& srcY, const double& srcW, const double& srcH, 
                            const double& dstX, const double& dstY, const double& dstW, const double& dstH)
{
	writeBuffer(sourceBuff,destinationBuff,srcX,srcY,srcW,srcH,dstX,dstY,dstW,dstH,0);
}

///////////////////////////////////////////////////////////////////////////////
//Write buffer
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::writeBuffer(const int& sourceBuff, const int& destinationBuff, const double& srcX, 
                            const double& srcY, const double& srcW, const double& srcH, 
                            const double& dstX, const double& dstY, const double& dstW, const double& dstH, const int& transp)
{
	//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Draw Line
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawLine(const TeLine2D& line, const bool& showPoint)
{
	PointF				*gdiPoints=NULL;

	if((line.size()>=2) && (_currentGraphics) && (_drawLine))
	{
		if((gdiPoints=transform2GdiPoint(line)))
		{
			_drawLine->showPointLine(showPoint);
			_drawLine->draw(gdiPoints,line.size(),_currentGraphics,(_paintMode==TdkAbstractCanvasDraw::pmdXOR ? true : false));
			delete gdiPoints;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw Segment Line
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawLineSegment(const double& x0, const double& y0, const double& x1, const double& y1)
{
	if((_currentGraphics) && (_drawLine))
	{
		_drawLine->draw(x0,y0,x1,y1,_currentGraphics);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw Segment Line
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawLineSegment(const TeCoord2D& c1, const TeCoord2D& c2)
{
	drawLineSegment(c1.x(),c1.y(),c2.x(),c2.y());
}

///////////////////////////////////////////////////////////////////////////////
//Draw Line
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawLine(TdkPrimitiveCoord* line, const int& lineSize)
{
	PointF			*point;
	unsigned int	i;

	if((_currentGraphics) && (_drawLine) && (lineSize>=2) && (line))
	{
		point=new PointF[lineSize];
		for(i=0;i<(unsigned int)lineSize;i++)
		{
			point[i].X=(REAL)line[i].x_;
			point[i].Y=(REAL)line[i].y_;
		}
		_drawLine->draw(point,lineSize,_currentGraphics);
		delete point;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a hollow rect
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawRect(const double& llx, const double& lly,const double& urx, const double& ury)
{
	if((_currentGraphics) && (_drawPolygon))
	{
		RectF rectangle((REAL)llx,(REAL)lly,(REAL)(urx-llx),(REAL)(ury-lly));
		_drawPolygon->drawRectangle(_currentGraphics,rectangle, (_paintMode==TdkAbstractCanvasDraw::pmdXOR ? true : false));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Fill Rect
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::fillRect(const double& llx, const double& lly,const double& urx, const double& ury)
{
	if((_currentGraphics) && (_drawPolygon))
	{
		RectF rectangle((REAL)llx,(REAL)lly,(REAL)(urx-llx),(REAL)(ury-lly));
		_currentGraphics->FillRectangle(_drawPolygon->getBrush(),rectangle);
		_currentGraphics->DrawRectangle(_drawPolygon->getPen(),rectangle);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw Points
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawPoints(PointF* points,const unsigned int &size)
{
	unsigned int i;

	for(i=0;i<size;i++)
	{
		_drawPoint->draw(points[i].X,points[i].Y,_currentGraphics);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets polygon type
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPolygonType(const int& type)
{
	if(_drawPolygon)
	{
		_drawPolygon->setType((PolygonSettings::backgroundStyle)type);
		return;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Transform Terralib Line to Gdi point
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
PointF* TdkGdiCanvasDraw::transform2GdiPoint(const TeLine2D &line)
{
	unsigned int	i;
	PointF*			points=NULL;
	
	if(line.size()>=2) 
	{
		if((points=new PointF[line.size()]))
		{
			for(i=0;i<line.size();i++)
			{
				points[i].X=(REAL)line[i].x();
				points[i].Y=(REAL)line[i].y();
			}
		}
	}
	return points;
}

///////////////////////////////////////////////////////////////////////////////
//transform2GdiPoint
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
GraphicsPath* TdkGdiCanvasDraw::transform2GdiPoint(const TePolygon &pol)
{
	GraphicsPath*	graph=NULL;
	PointF*			points=NULL;
	unsigned int	i;

	if(!pol.empty())
	{
		graph=new GraphicsPath();
		for(i=0;i<pol.size();i++)
		{
			points=transform2GdiPoint(pol[i]);
			graph->AddPolygon(points,pol[i].size());
			delete points;
		}
	}
	return graph;
}

///////////////////////////////////////////////////////////////////////////////
//Draw Polygon
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawPolygon(const TePolygon& poly, const bool& showPoint)
{
	if(_drawPolygon)
	{
		GraphicsPath*	polygonPath=NULL;
		polygonPath=transform2GdiPoint(poly);
		_drawPolygon->draw(polygonPath,_currentGraphics);
		delete polygonPath;
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw Polygon
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawPolygon(TdkPrimitiveCoord* poly, int* ringSize, const int& nRings)
{
	int						i,j;
	TdkPrimitiveCoord		*polRead=NULL;
	PointF					*points=NULL;
	GraphicsPath			pathPolygon;
	

	if((_currentGraphics) && (_drawPolygon) && (poly))
	{
		polRead=poly;
		for(i=0;i<nRings;i++)
		{
			points=new PointF[ringSize[i]];
			for(j=0;j<ringSize[i];j++,polRead++)
			{
				points[j].X=(REAL)polRead->x_;
				points[j].Y=(REAL)polRead->y_;
			}
			pathPolygon.AddPolygon(points,ringSize[i]);
			delete points;
		}
		_drawPolygon->draw(&pathPolygon,_currentGraphics);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw Cell
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawCell(const TeCell& cell, const bool& showPoint)
{
  TeBox box=cell.box();
  drawPolygon(polygonFromBox(box),showPoint);
}


///////////////////////////////////////////////////////////////////////////////
//getEncoderClsid
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
int TdkGdiCanvasDraw::getEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

///////////////////////////////////////////////////////////////////////////////
//Draw a Terralib Raster
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawRaster(TeRaster* raster)
{
	TeBox		clientArea;

	if(raster == NULL) return;

	clientArea=raster->params().boundingBox();
	if(clientArea.isValid())
	{
		TdkDecoderGdiImage *dec = reinterpret_cast<TdkDecoderGdiImage*>(raster->decoder());
        if (dec != NULL)
        {
			getViewport(clientArea);
			RectF rec((REAL)clientArea.x1(),(REAL)clientArea.y2(),(REAL)fabs(clientArea.width()),(REAL)fabs(clientArea.height()));
			_currentGraphics->DrawImage(dec->getImage(),rec);
        }
	}
}


///////////////////////////////////////////////////////////////////////////////
//Draw Point
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawPoint(const double& x, const double& y)
{
	_drawPoint->draw(x,y,_currentGraphics);
}

///////////////////////////////////////////////////////////////////////////////
//Draw Ellipse
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawEllipse(const double& xc, const double& yc,const double& rx, const double& ry, const double& angle)
{
	 if((_currentGraphics) && (_drawPolygon))
	 {
		 if(angle)
		 {
			_currentGraphics->TranslateTransform((REAL)xc,(REAL)yc);
			_currentGraphics->RotateTransform((REAL)angle);
			_currentGraphics->DrawEllipse(_drawPolygon->getPen(),(REAL)-rx,(REAL)-ry,(REAL)(rx*2),(REAL)(ry*2));
			_currentGraphics->ResetTransform();
		}
		 else
		 {
			_currentGraphics->DrawEllipse(_drawPolygon->getPen(),(REAL)(xc-rx),(REAL)(yc-ry),(REAL)(rx*2),(REAL)(ry*2));
		}
	 }
}

///////////////////////////////////////////////////////////////////////////////
//Draw Ellipse
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawEllipse(const double& xc, const double& yc,const double& rx1, const double& ry1,const double& rx2, const double& ry2)
{
	drawEllipse(xc,yc,(rx2-rx1),(ry2-ry1),0);
}

///////////////////////////////////////////////////////////////////////////////
//Fill Elipse
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::fillEllipse(const double& xc, const double& yc,const double& rx, const double& ry, const double& angle)
{
	 if((_currentGraphics) && (_drawPolygon))
	 {
		 if(angle)
		 {
			_currentGraphics->TranslateTransform((REAL)xc,(REAL)yc);
			_currentGraphics->RotateTransform((REAL)angle);
			_currentGraphics->FillEllipse(_drawPolygon->getBrush(),(REAL)-rx,(REAL)-ry,(REAL)(rx*2),(REAL)(ry*2));
			_currentGraphics->ResetTransform();
		}
		 else
		 {
			_currentGraphics->FillEllipse(_drawPolygon->getBrush(),(REAL)(xc-rx),(REAL)(yc-ry),(REAL)(rx*2),(REAL)(ry*2));
		}
	 }
}

///////////////////////////////////////////////////////////////////////////////
//Fill Ellipse
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::fillEllipse(const double& xc, const double& yc,const double& rx1, const double& ry1,const double& rx2, const double& ry2)
{	
	fillEllipse(xc,yc,(rx2-rx1),(ry2-ry1),0);
}

///////////////////////////////////////////////////////////////////////////////
//Draw Arc
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawArc(const double& xc, const double& yc,const double& w, const double& h,const double& startAngle, const double& finalAngle)
{
	 if((_currentGraphics) && (_drawLine))
	 {
		REAL x,y;
		x=(REAL)(xc - w/2);
		y=(REAL)(yc - h/2);
		_currentGraphics->DrawArc(_drawLine->getPen(),x,y,(REAL)w,(REAL)h,(REAL)startAngle,REAL(finalAngle-startAngle));
	 }
}

///////////////////////////////////////////////////////////////////////////////
//Draw a sector
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawSector(const double& xc, const double& yc,const double& w, const double& h, const double& startAngle, const double& finalAngle)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Fill Sector
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::fillSector(const double& xc, const double& yc,const double& w, const double& h,const double& startAngle, const double& finalAngle)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Draw a Image
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawImage(const unsigned char* image, const std::string& imageType, const int& imgSize, const double& dstX , const double& dstY)
{
	bitmapList::iterator	it;
	BitmapData				bitmapData;
	Rect					rect;
	UINT*					pixels;
	int						i;
	int						init;


	if(_currentBufferId == TdkAbstractCanvasDraw::cbrFront)
	{
		return;
	}

   if((it=_bufferList.find(_currentBufferId))!=_bufferList.end())
   {
	   rect=Rect(0,0,it->second->GetWidth(),it->second->GetHeight());
	   it->second->LockBits(&rect,ImageLockModeWrite,PixelFormat32bppARGB,&bitmapData);

	    pixels = (UINT*)bitmapData.Scan0;
		init=(int)(dstY * bitmapData.Stride /4 + dstX);
		pixels=&pixels[init];
		for(i=0;i<imgSize;i++,pixels++,image++)
		{
			*pixels=*image;
		}
		it->second->UnlockBits(&bitmapData);
   }
}

///////////////////////////////////////////////////////////////////////////////
//Draw a rgb image according world coordinate
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawImageRGBW(const unsigned int& imgW, const unsigned int& imgH,
			                    unsigned char* red, unsigned char* green, unsigned char* blue,
								const double& dstX, const double& dstY,
								const unsigned int& dstW, const unsigned int& dstH, const double& angle)
{
// not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Draw a rgb image
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawImageRGB(const unsigned int& imgW, const unsigned int& imgH,
			                    unsigned char* red, unsigned char* green, unsigned char* blue,
								const double& dstX, const double& dstY,
								const unsigned int& dstW, const unsigned int& dstH, const double& angle)
{
// not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Draw a image rgb
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawImageRGB(const unsigned int& imgW, const unsigned int& imgH,
			                    unsigned char* red, unsigned char* green, unsigned char* blue,
								const double& dstX, const double& dstY,
								const unsigned int& dstW, const unsigned int& dstH,
								const double& srcX, const double& srcY,
								const unsigned int& srcW, const unsigned int& srcH, const double& angle)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Draw a text
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawText(const double& x, const double& y, const string& text)
{
	if(_drawText)
	{
		_drawText->draw(x,y,text,_currentGraphics);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Draw a text
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawText(const TeBox &box, const std::string &text)
{
	if(_drawText)
	{
		RectF	rect=RectF((REAL)box.x1(),(REAL)box.y1(),(REAL)box.width(),(REAL)box.height());
		_drawText->draw(rect,text,_currentGraphics);
	}
}
///////////////////////////////////////////////////////////////////////////////
//Sets terralib visual
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setVisual(TeVisual* v, const TeGeomRep& rep)
{
	switch(rep)
	{
		case TePOLYGONS:
				break;
		case TeLINES:
				break;
		case TePOINTS:
				break;
		case TeTEXT:
				break;
	}

}

///////////////////////////////////////////////////////////////////////////////
//Sets point color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

void TdkGdiCanvasDraw::setPointColor(const int& r, const int& g, const int& b, const int& alpha)
{
	if(_drawPoint!=NULL)
	{
		_drawPoint->setColor(Color(alpha,r,g,b));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets point color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPointColor(const int& r, const int& g, const int& b)
{
	setPointColor(r,g,b,255);
}

///////////////////////////////////////////////////////////////////////////////
//Sets point color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPointColor(const TeColor& color, const int& alpha)
{
	setPointColor(color.red_,color.green_,color.blue_,alpha);
}

///////////////////////////////////////////////////////////////////////////////
//Sets point alpha
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPointAlpha(const int& alpha)
{
	if(_drawPoint!=NULL)
	{
		_drawPoint->setAlpha(alpha);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets point type
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPointType(const int& type)
{
	if(_drawPoint!=NULL)
	{
		_drawPoint->setType((PointSettings::pointType)type);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets point size
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPointSize(const int& s)
{
	if(_drawPoint!=NULL)
	{
		_drawPoint->setSize(createFontSize(s));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets point char
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPointChar(const char& c)
{
	if(_drawPoint!=NULL)
	{
		_drawPoint->setChar(c);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets Line Color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setLineColor(const int& r, const int& g, const int& b, const int& alpha)
{
	if(_drawLine!=NULL)
	{
		_drawLine->setColor(Color(alpha,r,g,b));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set Line color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setLineColor(const int& r, const int& g, const int& b)
{
	setLineColor(r,g,b,255);
}

///////////////////////////////////////////////////////////////////////////////
//Set Line Color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setLineColor(const TeColor& color, const int& alpha)
{
	setLineColor(color.red_,color.green_,color.blue_,alpha);
}

///////////////////////////////////////////////////////////////////////////////
//Set Line Alpha
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setLineAlpha(const int& alpha)
{
	if(_drawLine!=NULL)
	{
		_drawLine->setAlpha(alpha);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets Line type
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setLineType(const int& type)
{
	if(_drawLine!=NULL)
	{
		_drawLine->setType((LineSettings::DashStyle)type);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set Line Style dashes
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setLineStyleDashes(double *dashArray, const int &size)
{
	if(_drawLine!=NULL)
	{
		_drawLine->dash(dashArray,size);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set Line width
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setLineWidth(const int& width)
{
	if(_drawLine!=NULL)
	{
		REAL w=(REAL) width;
		if(_currentGraphics)	w=(REAL)((_currentGraphics->GetDpiX() * width)/72.0);
		_drawLine->setWidth((REAL)w);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets polygon color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPolygonColor(const int& r, const int& g, const int& b, const int& alpha)
{
	if(_drawPolygon!=NULL)
	{
		_drawPolygon->setColor(Color(alpha,r,g,b));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets polygon color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPolygonColor(const int& r, const int& g, const int& b)
{
	setPolygonColor(r,g,b,255);
}

///////////////////////////////////////////////////////////////////////////////
//Sets polygon color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPolygonColor(const TeColor& color, const int& alpha)
{
	setPolygonColor(color.red_,color.green_,color.blue_,alpha);
}

///////////////////////////////////////////////////////////////////////////////
//Sets polygon alpha color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPolygonAlpha(const int& alpha)
{
	if(_drawPolygon)
	{
		_drawPolygon->setAlpha(alpha);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets polygon border color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPolygonBorderColor(const int& r, const int& g, const int& b, const int& alpha)
{
	if(_drawPolygon)
	{
		_drawPolygon->setBorderColor(Color(alpha,r,g,b));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets polygon border color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPolygonBorderColor(const int& r, const int& g, const int& b)
{
	setPolygonBorderColor(r,g,b,255);
}

///////////////////////////////////////////////////////////////////////////////
//Sets polygon border color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPolygonBorderColor(const TeColor& color, const int& alpha)
{
	setPolygonBorderColor(color.red_,color.green_,color.blue_,alpha);
}

///////////////////////////////////////////////////////////////////////////////
//Sets poly
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPolygonBorderAlpha(const int& alpha)
{
	if(_drawPolygon)
	{
		_drawPolygon->setBorderAlpha(alpha);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets polygon type stipple
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPolygonTypeStipple(const int& width, const int& height, unsigned char* fgbg, const int& br, const int& bg, const int& bb)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Sets polygon type pattern
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void  TdkGdiCanvasDraw::setPolygonTypePattern(const int& width, const int& height, unsigned char* r, unsigned char* g, unsigned char* b)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Sets polygon border type
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPolygonBorderType(const int& type)
{	
	if(_drawPolygon)
	{
		_drawPolygon->setBorderType((LineSettings::DashStyle)type);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets polygon border width
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPolygonBorderWidth(const int& width)
{
	if(_drawPolygon)
	{
		REAL w=(REAL) width;
		if(_currentGraphics)	w=(REAL)((_currentGraphics->GetDpiX() * width)/72.0);
		_drawPolygon->setBorderWidth((int)w);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets text color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextColor(const int& r, const int& g, const int& b)
{
	setTextColor(r,g,b,255);
}

///////////////////////////////////////////////////////////////////////////////
//Sets text color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextColor(const int& r, const int& g, const int& b, const int& alpha)
{
	if(_drawText)
	{
		_drawText->setColor(Color(alpha,r,g,b));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets text alpha color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void  TdkGdiCanvasDraw::setTextAlpha(const int& alpha) 
{
	if(_drawText)
	{
		_drawText->setAlpha(alpha);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets text color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextColor(const TeColor& color, const int& alpha)
{
	setTextColor(color.red_,color.green_,color.blue_,alpha);
}

///////////////////////////////////////////////////////////////////////////////
//Sets text background color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextBackgroundColor(const int& r, const int& g, const int& b, const int& alpha)
{
	if(_drawText)
	{
		_drawText->setBackColor(Color(alpha,r,g,b));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextBackgroundColor(const int& r, const int& g, const int& b)
{
	setTextBackgroundColor(r,g,b,255);
}

///////////////////////////////////////////////////////////////////////////////
//Set Text Background color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextBackgroundColor(const TeColor& color, const int& alpha)
{
	setTextBackgroundColor(color.red_,color.green_,color.blue_,alpha);
}

///////////////////////////////////////////////////////////////////////////////
//Create a new font according the font name
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextBackgroundAlpha(const int& alpha)
{
	if(_drawText)
	{
		_drawText->setBackAlpha(alpha);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set Text background type
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextBackgroundType(const int& type)
{

}

///////////////////////////////////////////////////////////////////////////////
//Sets text border color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextBorderColor(const int& r, const int& g, const int& b)
{

}

///////////////////////////////////////////////////////////////////////////////
//Set Text Border color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextBorderColor(const int& r, const int& g, const int& b, const int& alpha)
{

}

///////////////////////////////////////////////////////////////////////////////
//Set Text Border color
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextBorderColor(const TeColor& color, const int& alpha)
{

}

///////////////////////////////////////////////////////////////////////////////
//Sets text border alpha
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextBorderAlpha(const int& alpha)
{

}

///////////////////////////////////////////////////////////////////////////////
//Set Texto Border Type
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextBorderType(const int& type)
{

}

	
///////////////////////////////////////////////////////////////////////////////
//Sets text border width
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextBorderWidth(const int& width)
{

}

///////////////////////////////////////////////////////////////////////////////
//Create a new font according the font name
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextFont(const string& fontName)
{
	if(_drawText)
	{
		_drawText->setFontName(fontName);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Create a new font according the size value
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

int TdkGdiCanvasDraw::createFontSize(int size)
{
	int			mult;
	int			logPixelsY;

	if(_dc==0) 
	{
		HDC dc=_defaultGraphics->GetHDC();
		logPixelsY=::GetDeviceCaps(dc, LOGPIXELSY);
		_defaultGraphics->ReleaseHDC(dc);
	}
	else			logPixelsY=::GetDeviceCaps(_dc, LOGPIXELSY);
		
	mult = MulDiv(size, logPixelsY, 72);
	//mult=(int) floor(mult * _dpiRatio);
	if(mult<=0) mult=3;
	return mult;
}

///////////////////////////////////////////////////////////////////////////////
//transform2GdiPoint
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextSize(const int& size)
{
	if(_drawText) 
	{
		if(size == 0)	_drawText->setFontSize(1);
		else			_drawText->setFontSize((REAL)createFontSize(size));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set the font size in pixels
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextPixelSize(const int &size)
{
	if(_drawText) 
	{
		if(size==0)	_drawText->setFontSize(1);
		else		_drawText->setFontSize((REAL)size);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set text angle
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextAngle(const double& angle)
{
	if(_drawText)
	{
		_drawText->setAngle(angle);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets the text bold
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextBold(const bool& bold)
{
	if(_drawText)
	{
		_drawText->setTextBold(bold);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets the text italic
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextItalic(const bool& italic)
{
	if(_drawText)
	{
		_drawText->setTextItalic(italic);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Sets the text alignment
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setTextAlign(const double& alignmentHoriz, const double& alignmentVert)
{
	if(_drawText)
	{
		TdkGdiText::horzAlignment	horiz;
		TdkGdiText::vertAlignment	vert;

		horiz=(TdkGdiText::horzAlignment)((int)alignmentHoriz);
		vert=(TdkGdiText::vertAlignment)((int)alignmentVert);
		_drawText->setHorizontalAligment(horiz);
		_drawText->setVerticalAlignment(vert);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Returns the text alignment
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::getTextAlign(double& alignmentHoriz, double& alignmentVert)
{
}

///////////////////////////////////////////////////////////////////////////////
//Set the clip area
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setClipArea(const TeBox& box)
{
	if(_currentGraphics)
	{
		RectF	rect((REAL)box.x1(),(REAL)box.y1(),(REAL)box.width(),(REAL)box.height());
		_currentGraphics->SetClip(rect);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set the clip area
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setClipArea(const double& llx, const double& lly, const double& urx, const double& ury)
{
	setClipArea(TeBox(llx,lly,urx,ury));
}

///////////////////////////////////////////////////////////////////////////////
//Subtract the clip area
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::subtractClipArea(const double& llx, const double& lly, const double& urx, const double& ury)
{
	if(_currentGraphics)
	{
		RectF	rect((REAL)llx,(REAL)lly,(REAL)fabs(urx-llx),(REAL)fabs(ury-lly));
		_currentGraphics->SetClip(rect,CombineModeExclude);
	}
}

///////////////////////////////////////////////////////////////////////////////
//Return the clip area
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::getClipArea(double& llx, double& lly, double& urx, double& ury)
{
	Rect	rect;

	llx=0;
	lly=0;
	urx=0;
	ury=0;
	if(_currentGraphics)
	{
		if(!_currentGraphics->IsClipEmpty())
		{
			_currentGraphics->GetClipBounds(&rect);
			llx=rect.X;
			lly=rect.Y;
			urx=rect.X + rect.Width;
			ury=rect.Y + rect.Height;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set the Clip area with polygon
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setClipArea(const TePolygon& poly)
{
	GraphicsPath*	path;

	path=transform2GdiPoint(poly);
	if(_currentGraphics)
	{
		_currentGraphics->SetClip(path);
	}
	if(path)	delete path;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the clip area
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::getClipArea(TePolygon& poly)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Active Clip Area
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::activateClip()
{
// not necessary
}

///////////////////////////////////////////////////////////////////////////////
//Deactive clip area
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::deactivateClip()
{
	if(_currentGraphics)
	{
		_currentGraphics->ResetClip();
	}
}

///////////////////////////////////////////////////////////////////////////////
//Set the Printer page size
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPrinterPageSize(const short& pageSize)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Set the Printer Orientation
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setPrinterPageOrientation(const short& orientation)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Return the Canvas Id
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
int TdkGdiCanvasDraw::getCanvasId()
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Update Canvas with current window handle
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::Update()
{
	if(_hWnd)
	{
		if(_defaultGraphics) delete _defaultGraphics;
		_defaultGraphics=new Graphics(_hWnd);
		_defaultGraphics->Clear(Color(_backgroundColor.red_,_backgroundColor.green_,_backgroundColor.blue_));
	}
}

///////////////////////////////////////////////////////////////////////////////
//Export the pixmap to file
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGdiCanvasDraw::exportBuffer(const int &bufferId, const std::string &fileName, const std::string &fileFormat, const int &quality)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Set the Raster Decoder
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setRasterDecoder(TeRaster* raster, TeRasterParams& params)
{
	TdkDecoderGdiImage *dec = new TdkDecoderGdiImage(params);
	raster->setDecoder(dec);
}

///////////////////////////////////////////////////////////////////////////////
//Sets the raster transparency
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setRasterTransparency(TeDecoder* dec, unsigned int transparency)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Return the text bounding box in world coordinate
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::getTextBoundsW(const string& text, const double& x, const double& y,
			const double& angle, TdkTextBounds& bounds)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Returns the text bounding box 
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::getTextBounds(const string& text, const double& x, const double& y,
			const double& angle, TdkTextBounds& bounds)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Returns the text bounding box in world coordinates
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::getTextBoundsW(const TeText& text, TdkTextBounds& bounds)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Returns the text bounding box
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::getTextBounds(const TeText& text, TdkTextBounds& bounds)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Set the ClipArea
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::setClipArea(const TePolygonSet& polys, const TdkClipAreaType& clipType)
{
//not implemented
}

///////////////////////////////////////////////////////////////////////////////
//Returns the text dimensions
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

bool TdkGdiCanvasDraw::getTextDimension(const std::string &text, double &w, double &h)
{
	if((_drawText!=NULL) && (_currentGraphics!=NULL))
	{
		SizeF	size;
		size=_drawText->MeasureString(text,_currentGraphics);
		w=size.Width;
		h=size.Height;
		return true;
	}
	return false;
}


///////////////////////////////////////////////////////////////////////////////
//Draw the abstract image
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

void TdkGdiCanvasDraw::drawRaster(TdkAbstractImage* raster, const TeBox &box,const double &angle)
{
	Gdiplus::RectF rect((Gdiplus::REAL)box.x1(),(Gdiplus::REAL)box.y1(),(Gdiplus::REAL)box.width(),(Gdiplus::REAL)box.height());
	Gdiplus::Bitmap *bitmap=((TdkGdiImage*)raster)->getBitmap();
	if(angle)
	{
		_currentGraphics->TranslateTransform((Gdiplus::REAL)box.center().x(),(Gdiplus::REAL)box.center().y());
		_currentGraphics->RotateTransform((Gdiplus::REAL)angle);
		rect=Gdiplus::RectF((Gdiplus::REAL) (-box.width()/2.0),(Gdiplus::REAL) (-box.height()/2.0),(Gdiplus::REAL) box.width(),(Gdiplus::REAL) box.height());
	}	
	_currentGraphics->DrawImage(bitmap,rect);
}

///////////////////////////////////////////////////////////////////////////////
//Draw a terralib raster
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////

void TdkGdiCanvasDraw::drawRaster(TeRaster* raster, const double &scaleX, const double &scaleY)
{
	//not implemented
	
}


///////////////////////////////////////////////////////////////////////////////
//Draw a terralib raster
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiCanvasDraw::drawRaster(TeRaster* raster, const double &scaleX, const double &scaleY,const double &y)
{

	//not implemented

}

///////////////////////////////////////////////////////////////////////////////
//Returns the dpi in x axes
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
double TdkGdiCanvasDraw::getDpiX()
{
	if(_currentGraphics)	return (double)_currentGraphics->GetDpiX();
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the dpi in y axes
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
double TdkGdiCanvasDraw::getDpiY()
{
	if(_currentGraphics)	return (double)_currentGraphics->GetDpiY();
	return 0;
}
