#include <TdkDecoderGdiImage.h>

///////////////////////////////////////////////////////////////////////////////
//Constructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkDecoderGdiImage::TdkDecoderGdiImage( const TeRasterParams& par )
{
	image_ = 0;
	transp_ = 255;
	params_ = par;
}

///////////////////////////////////////////////////////////////////////////////
//Destructor
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
TdkDecoderGdiImage::~TdkDecoderGdiImage()
{
	clear ();
	transp_ = 255;
}


///////////////////////////////////////////////////////////////////////////////
//Start the decoder
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
void TdkDecoderGdiImage::init()
{
	params_.status_= TeRasterParams::TeNotReady;
	if (params_.mode_ == 'c')	// creating a new file
	{
		clear ();
		image_ = new Gdiplus::Bitmap(params_.ncols_,params_.nlines_,PixelFormat24bppRGB);
		params_.status_ = TeRasterParams::TeReadyToWrite;
	}
	else if (params_.mode_ == 'w')
	{
		if (image_)		params_.status_ = TeRasterParams::TeReadyToWrite;
	}
	else if (params_.mode_ == 'r')
	{
		if (image_)		params_.status_ = TeRasterParams::TeReadyToRead;	
	}
}

///////////////////////////////////////////////////////////////////////////////
//Clear decoder
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkDecoderGdiImage::clear()
{
	if(image_)		delete  image_;
	image_=0;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
//Set RGB Elements
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkDecoderGdiImage::setElementRGB(int col, int lin, double Rval, double Gval, double Bval, unsigned int transp)
{
	if(image_)	
	{
		image_->SetPixel(col,lin,Gdiplus::Color(transp,(BYTE)Rval,(BYTE)Gval,(BYTE)Bval));
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Set the element (set the pixel color to specific band)
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkDecoderGdiImage::setElement (int col, int lin, double val, int band)
{
	if(image_)	
	{
		BYTE	red, green, blue, alpha;

		Gdiplus::Color color;
		image_->GetPixel(col,lin,&color);

		red=color.GetRed();
		green=color.GetGreen();
		blue=color.GetBlue();
		alpha=color.GetAlpha();
		switch(band)
		{
			case 0: red=(BYTE)val;
					break;
			case 1: green=(BYTE)val;
					break;
			case 2: blue=(BYTE)val;
					break;
			case 3: alpha=(BYTE)val;
					break;
		}
		image_->SetPixel(col,lin,Gdiplus::Color(red,green,blue));
		return true;
	}
	return false;
}
	
///////////////////////////////////////////////////////////////////////////////
//Returns the element (get the pixel for specific band)
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkDecoderGdiImage::getElement (int col, int lin, double &val, int band)
{
	if(image_)	
	{
		Gdiplus::Color color;
		image_->GetPixel(col,lin,&color);
		switch(band)
		{
			case 0: val=(double) color.GetRed();
					break;
			case 1: val=(double) color.GetGreen();
					break;
			case 2: val=(double) color.GetBlue();
					break;
			case 3: val=(double) color.GetAlpha();
					break;
		}
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
//Set Alpha Buffer to Transparent
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
bool TdkDecoderGdiImage::setAlphaBufferToTransparent()
{
	return false;
}


///////////////////////////////////////////////////////////////////////////////
//Returns the bitmap image
//Author : Rui Mauricio Gregório 
//Date : 08/2009
///////////////////////////////////////////////////////////////////////////////
Gdiplus::Bitmap*	TdkDecoderGdiImage::getImage () 
{ 
	return image_; 
}