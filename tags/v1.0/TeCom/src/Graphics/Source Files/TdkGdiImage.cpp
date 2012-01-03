#include <TdkGdiImage.h>
#include <comutil.h>


///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

TdkGdiImage::TdkGdiImage(const std::string &fileName) : TdkAbstractImage()
{
	TdkAbstractImage::setFileName(fileName);
	if(_fileName.empty())	_bitMap=NULL;
	else					_bitMap=new Gdiplus::Bitmap(bstr_t(_fileName.c_str()));
}


TdkGdiImage::TdkGdiImage(LPCTSTR pName, LPCTSTR pType, HMODULE hInst)
{
	HGLOBAL	buffer;

	_bitMap=NULL;
	HRSRC hResource = ::FindResource(hInst, pName, pType);
    if (!hResource)	return;
    
    DWORD imageSize = ::SizeofResource(hInst, hResource);
    if (!imageSize) return;

    const void* pResourceData = ::LockResource(::LoadResource(hInst,hResource));
    if (!pResourceData)	return;

    buffer  = ::GlobalAlloc(GMEM_MOVEABLE, imageSize);
    if (buffer)
    {
        void* pBuffer = ::GlobalLock(buffer);
        if (pBuffer)
        {
            CopyMemory(pBuffer, pResourceData, imageSize);

            IStream* pStream = NULL;
            if (::CreateStreamOnHGlobal(buffer, FALSE, &pStream) == S_OK)
            {
                _bitMap = Gdiplus::Bitmap::FromStream(pStream);
                pStream->Release();
				if (_bitMap)
					{ 
						Gdiplus::Status status;
						status=_bitMap->GetLastStatus();
						if (status != Gdiplus::Ok)
						{
							delete _bitMap;
							_bitMap = NULL;
						}
					}
            }
            ::GlobalUnlock(buffer);
        }
        ::GlobalFree(buffer);
        buffer = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiImage::~TdkGdiImage()
{
	if(_bitMap)		delete _bitMap;
	_bitMap=NULL;
}

///////////////////////////////////////////////////////////////////////////////
// Set image's height
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiImage::setHeight(const double &value)
{

}

///////////////////////////////////////////////////////////////////////////////
//Sets image's file name
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiImage::setFileName(const std::string &fileName)
{
	TdkAbstractImage::setFileName(fileName);
	if(_bitMap)		delete _bitMap;
	_bitMap=NULL;
	if(!_fileName.empty()) 
		_bitMap=new Gdiplus::Bitmap(bstr_t(_fileName.c_str()));
}

///////////////////////////////////////////////////////////////////////////////
//Sets abstract file name
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
void TdkGdiImage::setAbstractFileName(const std::string &fileName)
{
	TdkAbstractImage::setFileName(fileName);
}
///////////////////////////////////////////////////////////////////////////////
//Clear Image
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
 void TdkGdiImage::clear()
 {
	if(_bitMap)	delete _bitMap;
	_bitMap=NULL;
 }

///////////////////////////////////////////////////////////////////////////////
//Sets image's width
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////

void TdkGdiImage::setWidth(const double &value)
{

}

///////////////////////////////////////////////////////////////////////////////
//Return the image encoder
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
CLSID*  TdkGdiImage::getEncoder(const Encoders encoder)
{
	CLSID   *encoderClsid=new CLSID();
	int		status;
	switch(encoder)
	{
		case JPEG :		status=GetEncoderClsid(L"image/jpeg", encoderClsid);
							break;
		case PNG :		status=GetEncoderClsid(L"image/png", encoderClsid);
							break;
		case GIF :		status=GetEncoderClsid(L"image/gif", encoderClsid);
							break;
		case TIF :		status=GetEncoderClsid(L"image/tiff", encoderClsid);
							break;
		default :		status=GetEncoderClsid(L"image/jpeg", encoderClsid);
	}
	if(status==-1)
	{
		delete encoderClsid;
		encoderClsid=NULL;
	}
	return encoderClsid;
}

///////////////////////////////////////////////////////////////////////////////
//Return clsid image encoder
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
int TdkGdiImage::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
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
//Saves Image to file
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGdiImage::save(const std::string &fileName)
{
	if(_bitMap)	return (_bitMap->Save((WCHAR*)fileName.c_str(),this->getEncoder(PNG)) == Gdiplus::Ok ? true : false);
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the image height
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
double TdkGdiImage::getHeight()
{
	if(_bitMap)	return ((double)_bitMap->GetHeight());
	return 0.0;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the image width
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
double TdkGdiImage::getWidth()
{
	if(_bitMap)	return ((double)_bitMap->GetWidth());
	return 0.0;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the gdi image pointer
//Author : Rui Mauricio Gregório 
//Date : 06/2009
///////////////////////////////////////////////////////////////////////////////
Gdiplus::Bitmap* TdkGdiImage::getBitmap()
{
	return _bitMap;
}

///////////////////////////////////////////////////////////////////////////////
//Returns the image like unsigned char array
//Author : Rui Mauricio Gregório 
//Date : 09/2010
///////////////////////////////////////////////////////////////////////////////

unsigned char * TdkGdiImage::getIstream(unsigned long &size)
{
	IStream					*pIStream    = NULL;
	CLSID					pngClsid;
	EncoderParameters		encoderParameters;
	ULONG					quality = 75;
	Status					SaveStatus;
	ULARGE_INTEGER			ulnSize;
	LARGE_INTEGER			lnOffset;
	unsigned char			*pBuff=0;


	if(_bitMap == 0) return 0;

	if(CreateStreamOnHGlobal(NULL, TRUE, (LPSTREAM*)&pIStream) != S_OK)
	  return 0;

	GetEncoderClsid(L"image/jpeg", &pngClsid);

	encoderParameters.Count = 1;
	encoderParameters.Parameter[0].Guid = EncoderQuality;
	encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
	encoderParameters.Parameter[0].NumberOfValues = 1;
	encoderParameters.Parameter[0].Value = &quality;
	SaveStatus = _bitMap->Save(pIStream, &pngClsid, &encoderParameters);
	if(SaveStatus != Ok)
	{
		pIStream->Release();
		return 0;
	}
	lnOffset.QuadPart = 0;
	if(pIStream->Seek(lnOffset, STREAM_SEEK_END, &ulnSize) != S_OK)
	{    
		pIStream->Release();
		return 0;
	}
	if(pIStream->Seek(lnOffset, STREAM_SEEK_SET, NULL) != S_OK)
	{
		pIStream->Release();
		return 0;
	}
	pBuff =(unsigned char*) new unsigned char[(ULONG)ulnSize.QuadPart];
	ULONG ulBytesRead;
    if(pIStream->Read(pBuff,(ULONG) ulnSize.QuadPart, &ulBytesRead) != S_OK)
    {
        pIStream->Release();
        delete pBuff;
        return 0;
    }
	pIStream->Release();
	size=ulBytesRead;
	return pBuff;
}

///////////////////////////////////////////////////////////////////////////////
//Creates image from IStream
//Author : Rui Mauricio Gregório 
//Date : 09/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkGdiImage::setIStream(unsigned char *value, const unsigned long &size)
{
	IStream* pIStream    = NULL;
	ULONG				writtenSize;

	if(CreateStreamOnHGlobal(NULL, TRUE, (LPSTREAM*)&pIStream) != S_OK)	return false;
	pIStream->Write(value,size,&writtenSize);
	_bitMap=Gdiplus::Bitmap::FromStream(pIStream);
	pIStream->Release();
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Clone Image
//Author : Rui Mauricio Gregório 
//Date : 09/2009
///////////////////////////////////////////////////////////////////////////////
TdkGdiImage* TdkGdiImage::clone()
{
	if(_bitMap == 0) return 0;
	TdkGdiImage *obj;

	obj=new TdkGdiImage("");
	obj->_bitMap=_bitMap->Clone(0,0,_bitMap->GetWidth(),_bitMap->GetHeight(),_bitMap->GetPixelFormat());
	return obj;
}