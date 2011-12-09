/******************************************************************************
* FUNCATE - GIS development team
* 
* TerraLib Components - TeCOM
* 
* @(#) TdkGdiCanvasDraw.h
*
*******************************************************************************
*
* $Rev$:
*
* $Author: rui.gregorio $:
*
* $Date: 2010/08/26 17:42:13 $:
*
******************************************************************************/
// Elaborated by Rui Mauricio Gregório


#ifndef __TDK_GDI_CANVAS_DRAW_H
#define __TDK_GDI_CANVAS_DRAW_H

#include <windows.h>
#include <gdiplus.h>
#include <TdkAbstractCanvasDraw.h>

#include <TeDataTypes.h>


using namespace Gdiplus;





typedef map<int,Bitmap*>	bitmapList;

class TdkGdiPoint;
class TdkGdiLine;
class TdkGdiPolygon;
class TdkGdiText;
class TdkAbstractImage;


class TdkGdiCanvasDraw : public TdkAbstractCanvasDraw
{
protected :

	GdiplusStartupInput			_gdiplusStartupInput;
	ULONG_PTR					_gdiplusToken;
	HWND						_hWnd;
	HDC							_dc;
	double						_dpiRatio;
	Graphics*					_defaultGraphics;
	Graphics*					_currentGraphics;
	bitmapList					_bufferList;
	Font*						_fontString;
	Brush*						_fontForeColor;
	
	

	TdkGdiPoint*				_drawPoint;
	TdkGdiLine*					_drawLine;
	TdkGdiPolygon*				_drawPolygon;
	TdkGdiText*					_drawText;

protected:

		//! \brief getClientArea
		/*! Method to return the client area from 
			component
			\param		rectangle		rectangle object with client area
			\param		returns true wheter sucess
		*/
		virtual bool getClientArea(RECT &rectangle);

		//! \brief drawPoints
		/*! Method to draw a list points in GDI format
			\param		points	list points in gdi format
			\param		size	points quantity
		*/
		virtual void drawPoints(PointF* points,const unsigned int &size);

		virtual PointF* transform2GdiPoint(const TeLine2D &line);

		virtual GraphicsPath* transform2GdiPoint(const TePolygon &pol);

		//! \brief createFontSize
		/*! Calculate the font size, used to print
			process
			\param	size	fontSize
		*/
		virtual int createFontSize(int size);

		//! \brief getEncoderClsid
		/*! Method to return the encoder to specific format
			to save a image for file
			\param		format		format name
			\param		pClsid		handle
			\param		returns different of -1 whether sucess
		*/
		virtual int getEncoderClsid(const WCHAR* format, CLSID* pClsid);

public :
	
		//! \brief Constructor
		/*! Class constructor
			\param	hWnd		Handle Device
		*/
		TdkGdiCanvasDraw(HWND hWnd);

		TdkGdiCanvasDraw(HDC dc, const double &dpiRatio=300);

		//! \brief Destructor
		virtual ~TdkGdiCanvasDraw();

		//! \brief getDimensionMM
		/*! Method to return the client area in millimeter unit
			\param	width		width value
			\param	height		height value
		*/
		virtual void getDimensionMM(double& width, double& height);

		//! \brief getWidth
		/*! Method to return the width value from component
		*/
		virtual double getWidth() ;

		//! \brief getHeight
		/*! Method to return the height value from component
		*/
		virtual double getHeight();

		//! \brief addBuffer
		/*! Method to create buffer to use such as (double buffer)
			withou flick
			\param	bufferId			buffer identify
		*/
		virtual int addBuffer(const int& bufferId = -1);

		//! \brief clear
		/*! Clear all buffers from memory
		*/
		virtual void clear();

		/** \brief Sets the current buffer used to draw.
		This method changes the current buffer used to draw,
		you should specify a valid identifier, otherwise it will be raised an exception.
		\param  bufferId Buffer identification: it is a key for identify a given buffer. (Input)
		\return Return the previous buffer id that was active or -1 if the buffer could not be found.
		*/
		virtual int setActiveBuffer(const int& bufferId);

		//! \brief addBuffer
		/*! This method add a new bitmap object to list with with and height defined by
			user
			\param	width		width value
			\param	height		height value
			\param	bufferId	buffer identify
			\return Returns the buffer id value whether sucess
		*/
		virtual int addBuffer(const double& width, const double& height, const int& bufferId = -1);

		//! \brief Resizes the buffer identified by \a bufferId parameter.
		/*!
			\param bufferId Identifier of buffer to be resized.
			\param width New buffer width.
			\param height New buffer height.
		*/
		virtual void resizeBuffer(const int& bufferId, const double& width, const double& height);

		 //! \brief Removes the buffer identified by bufferId.
		/*!
			If you specify an invalid id, it will be raised an exception.
			\param bufferId  The identification of the buffer to be removed. (Input)
			\note If the buffer is the current one, you should specify a new active (current) buffer, otherwise, you can get an undefined result.
		*/
		virtual void removeBuffer(const int& bufferId);

		//! \brief Remve all buffer from memory
		virtual void removeAllBuffers();


		/** \brief Copies the content of source buffer to a destination buffer (its a pixel a pixel copy).
		When transparent is set to true, the pixels specified by (r, g, b, a) color will not be copied to the destination buffer.
		\param sourceBuff       Source buffer, from wich the pixels will be copied to a destination buffer. (Input)
		\param destinationBuff  Destination buffer, to wich the pixels will be copied. (Input)
		\param transparent      Indicates if we will have a transparent color during copy, i. e., the pixels with the specified color that will not be copied from the source buffer to the destination. (Input)
		\param r                Red component color. (Input)
		\param g                Green component color. (Input)
		\param b                Blue component color. (Input)
		\param a                Alpha component. (Input)
		*/
		virtual void writeBuffer(const int& sourceBuff, const int& destinationBuff,
			                    const bool& transparent = false,
			                    const int& r = 0, const int& g = 0,
								const int& b = 0, const int& a = 0);


		/** \brief Copies partial contents of source buffer to a destination buffer with angle rotation.
		\param sourceBuff       Source buffer, from wich the pixels will be copied to a destination buffer. (Input)
		\param destinationBuff  Destination buffer, to wich the pixels will be copied. (Input)
        \param srcX             Initial x coordinate in sourceBuffer. This is a lower left corner coordinate. (Input)
        \param srcY             Initial y coordinate in sourceBuffer. This is a lower left corner coordinate. (Input)
        \param srcW             Width of the piece we want from the buffer. (Input)
        \param srcH             Height of the piece we want from the buffer. (Input)
        \param dstX             Initial x coordinate in destinationBuff. This is a lower left corner coordinate. (Input)
        \param dstY             Initial y coordinate in destinationBuff. This is a lower left corner coordinate. (Input)
		\param angle			angle rotation
        */
		virtual void writeBuffer(const int& sourceBuff, const int& destinationBuff, const double& srcX, 
                            const double& srcY, const double& srcW, const double& srcH, 
                            const double& dstX, const double& dstY, const double& angle);

		/** \brief Copies partial contents of source buffer to a destination buffer.
		\param sourceBuff       Source buffer, from wich the pixels will be copied to a destination buffer. (Input)
		\param destinationBuff  Destination buffer, to wich the pixels will be copied. (Input)
        \param srcX             Initial x coordinate in sourceBuffer. This is a lower left corner coordinate. (Input)
        \param srcY             Initial y coordinate in sourceBuffer. This is a lower left corner coordinate. (Input)
        \param srcW             Width of the piece we want from the buffer. (Input)
        \param srcH             Height of the piece we want from the buffer. (Input)
        \param dstX             Initial x coordinate in destinationBuff. This is a lower left corner coordinate. (Input)
        \param dstY             Initial y coordinate in destinationBuff. This is a lower left corner coordinate. (Input)
        */
		virtual void writeBuffer(const int& sourceBuff, const int& destinationBuff, const double& srcX, 
                            const double& srcY, const double& srcW, const double& srcH, 
                            const double& dstX, const double& dstY);


		
	/** \brief Copies partial contents of source buffer to a destination buffer with angle rotation.
		\param sourceBuff       Source buffer, from wich the pixels will be copied to a destination buffer. (Input)
		\param destinationBuff  Destination buffer, to wich the pixels will be copied. (Input)
        \param srcX             Initial x coordinate in sourceBuffer. This is a lower left corner coordinate. (Input)
        \param srcY             Initial y coordinate in sourceBuffer. This is a lower left corner coordinate. (Input)
        \param srcW             Width of the piece we want from the buffer. (Input)
        \param srcH             Height of the piece we want from the buffer. (Input)
        \param dstX             Initial x coordinate in destinationBuff. This is a lower left corner coordinate. (Input)
        \param dstY             Initial y coordinate in destinationBuff. This is a lower left corner coordinate. (Input)
		\param dstW				Width to final image
		\param dstH				Height to final image
		\param angle			angle rotation
        */
		virtual void writeBuffer(const int& sourceBuff, const int& destinationBuff, const double& srcX, 
                            const double& srcY, const double& srcW, const double& srcH, 
                            const double& dstX, const double& dstY, const double& dstW, const double& dstH, double angle);


		/** \brief Copies partial contents of source buffer to a destination buffer with resize .
		\param sourceBuff       Source buffer, from wich the pixels will be copied to a destination buffer. (Input)
		\param destinationBuff  Destination buffer, to wich the pixels will be copied. (Input)
        \param srcX             Initial x coordinate in sourceBuffer. This is a lower left corner coordinate. (Input)
        \param srcY             Initial y coordinate in sourceBuffer. This is a lower left corner coordinate. (Input)
        \param srcW             Width of the piece we want from the buffer. (Input)
        \param srcH             Height of the piece we want from the buffer. (Input)
        \param dstX             Initial x coordinate in destinationBuff. This is a lower left corner coordinate. (Input)
        \param dstY             Initial y coordinate in destinationBuff. This is a lower left corner coordinate. (Input)
		\param dstW             Width to resize image
        \param dstH             Height to resize image
        */
		virtual void writeBuffer(const int& sourceBuff, const int& destinationBuff, const double& srcX, 
                            const double& srcY, const double& srcW, const double& srcH, 
                            const double& dstX, const double& dstY, const double& dstW, const double& dstH);

		/** \brief Copies partial contents of source buffer to a destination buffer.
		\param sourceBuff       Source buffer, from wich the pixels will be copied to a destination buffer. (Input)
		\param destinationBuff  Destination buffer, to wich the pixels will be copied. (Input)
        \param srcX             Initial x coordinate in sourceBuffer. This is a lower left corner coordinate. (Input)
        \param srcY             Initial y coordinate in sourceBuffer. This is a lower left corner coordinate. (Input)
        \param srcW             Width of the piece we want from the buffer. (Input)
        \param srcH             Height of the piece we want from the buffer. (Input)
        \param dstX             Initial x coordinate in destinationBuff. This is a lower left corner coordinate. (Input)
        \param dstY             Initial y coordinate in destinationBuff. This is a lower left corner coordinate. (Input)
		\param dstW				Width to final image
		\param dstH				Height to final image
		\param transp           Alpha component. (Input)
        */
		virtual void writeBuffer(const int& sourceBuff, const int& destinationBuff, const double& srcX, 
                            const double& srcY, const double& srcW, const double& srcH, 
                            const double& dstX, const double& dstY, const double& dstW, const double& dstH, const int& transp); 

		/** \brief Draws a line with vertexes specified in device coordinates.
		\param line       TerraLib line instance. (Input)
		\param showPoint  If true the line vertexes will be drawn. (Input)
		*/
		virtual void drawLine(const TeLine2D& line, const bool& showPoint = false);


		/** \brief Draws a polygon with vertexes specified in device coordinates.
		\param poly       TerraLib polygon instance. (Input)
		\param showPoint  If true the polygon vertexes will be drawn. (Input)
		*/
		virtual void drawPolygon(const TePolygon& poly, const bool& showPoint = false);

		/** \brief Sets the style for draw line geometries.
		\param style Line style that will be used to draw lines. (Input)
        */
		virtual void setPolygonType(const int& type);

		/** \brief Draws a cell with vetexes specified in device coordinates.
		\param cell       TerraLib cell instance. (Input)
		\param showPoint  If true the cell vertexes will be drawn. (Input)
		*/
		virtual void drawCell(const TeCell& cell, const bool& showPoint = false);


		/** \brief Draws a line segment from (x0, y0) to (x1, y1), specified in device coordinates.
		\param x0 Abscissa value indicating the segment begin. (Input)
		\param y0 Ordinate value indicating the segment begin. (Input)
		\param x1 Abscissa value indicating the segment end. (Input)
		\param y1 Ordinate value indicating the segment end. (Input)
		*/		         
		virtual void drawLineSegment(const double& x0, const double& y0, const double& x1, const double& y1);

		virtual void drawLineSegment(const TeCoord2D& c1, const TeCoord2D& c2);

		/** \brief Draws a rectangle with lower left corner at (llx, lly) and uper right corner at (urx, ury), specified in device coordinates.
		\param llx Lower left abscissa. (Input)
		\param lly Lower left ordinate. (Input)
		\param urx Upper right abscissa. (Input)
		\param ury Upper right ordinate. (Input)
		*/
		virtual void drawRect(const double& llx, const double& lly,const double& urx, const double& ury);

		/** \brief Fills the rectangle with lower left corner at (llx, lly) and uper right corner at (urx, ury), specified in device coordinates.
		\param llx Lower left abscissa. (Input)
		\param lly Lower left ordinate. (Input)
		\param urx Upper right abscissa. (Input)
		\param ury Upper right ordinate. (Input)
		*/
		virtual void fillRect(const double& llx, const double& lly,const double& urx, const double& ury);

		/** \brief Draws the raster.
		\param raster  A pointer to a TerraLib raster instance. (Input)
		\param transf  A pointer to the raster transform function. (Input)
		*/
		virtual void drawRaster(TeRaster* raster);

		//! \brief Draw the abstract Image
		virtual void drawRaster(TdkAbstractImage* raster, const TeBox &box, const double &angle=0.0);

		//! \brief Draw the abstract Image
		virtual void drawRaster(TeRaster* raster, const double &scaleX, const double &scaleY);

		//! \brief Draw the abstract Image
		virtual void drawRaster(TeRaster* raster, const double &scaleX, const double &scaleY,const double &y);

		/** \brief Draws a point specified in device coordinates.
		\param pt TerraLib point instance. (Input)
		*/
  		virtual void drawPoint(const double& x, const double& y);

		/** \brief Draws a line with vertexes specified in device coordinates.
		\param line     A pointer to line vertexes. (Input)
		\param lineSize Number of line vertexes. (Input)
		*/
		virtual void drawLine(TdkPrimitiveCoord* line, const int& lineSize);

		/** \brief Draws a polygon with vertexes specified in device coordinates.
		\param poly     A pointer to polygon vertexes. (Input)
		\param ringSize A pointer to an array with each polygon ring size. (Input)
		\param nRings   The number of rings in the specified polygon. (Input)
		*/
		virtual void drawPolygon(TdkPrimitiveCoord* poly, int* ringSize, const int& nRings);		

		/** \brief Draws an ellipse with center at (xc, yc), specified in device coordinates, x axis width r1 and y axis width r2, especified in the same device unit.
		\param xc Center abscissa. (Input)
		\param yc Center ordinate. (Input)
		\param rx X axis width (in the same device unit). (Input)
		\param ry Y axis width (in the same device unit). (Input)
		\param angle Angle to rotate the ellipse round "x" axis. (Input)
		*/
		virtual void drawEllipse(const double& xc, const double& yc,const double& rx, const double& ry, const double& angle);


		/** \brief Draws an ellipse with center at (xc, yc), specified in device coordinates, x axis width r1 and y axis width r2, especified in the same device unit.
		\param xc Center abscissa. (Input)
		\param yc Center ordinate. (Input)
		\param rx1 First conjugate radius (in the same device unit). (Input)
		\param ry1 First conjugate radius (in the same device unit). (Input)
		\param rx2 Second conjugate radius (in the same device unit). (Input)
		\param ry2 Second conjugate radius (in the same device unit). (Input)
		*/
		virtual void drawEllipse(const double& xc, const double& yc,const double& rx1, const double& ry1,const double& rx2, const double& ry2);

		 /** \brief Fills the ellipse with center at (xc, yc), specified in device coordinates, x axis width r1 and y axis width r2, especified in the same device unit.
		\param xc Center abscissa. (Input)
		\param yc Center ordinate. (Input)
		\param rx X axis width (in the same device unit). (Input)
		\param ry Y axis width (in the same device unit). (Input)
		\param angle Angle to rotate the ellipse round "x" axis. (Input)
		*/
		virtual void fillEllipse(const double& xc, const double& yc,const double& rx, const double& ry, const double& angle);

		/** \brief Fills the ellipse with center at (xc, yc), specified in device coordinates, x axis width r1 and y axis width r2, especified in the same device unit.
		\param xc Center abscissa. (Input)
		\param yc Center ordinate. (Input)
		\param rx1 First conjugate radius (in the same device unit). (Input)
		\param ry1 First conjugate radius (in the same device unit). (Input)
		\param rx2 Second conjugate radius (in the same device unit). (Input)
		\param ry2 Second conjugate radius (in the same device unit). (Input)
		*/
		virtual void fillEllipse(const double& xc, const double& yc,const double& rx1, const double& ry1,const double& rx2, const double& ry2);

		/** \brief Draws an arc defined by a center at (xc, yc), specified in device coordinates, width (w), height (h), the start angle (startAngle) and the final angle (finalAngle).
		\param xc		   Center abscissa. (Input)
		\param yc          Center ordinate. (Input)
		\param w           Width (in the same device unit). (Input)
		\param h           Height (in the same device unit). (Input)
		\param startAngle  Start angle in decimal degrees. (Input)
		\param finalAngle  Final angle in decimal degrees. (Input)
		*/
		virtual void drawArc(const double& xc, const double& yc,const double& w, const double& h,const double& startAngle, const double& finalAngle);

		/** \brief Draws a sector defined by a center coordinate (xc, yc), specified in device coordinates, width (w), height (h), the start angle (startANgle) and the final angle (finalAngle).
		\param xc		   Center abscissa. (Input)
		\param yc          Center ordinate. (Input)
		\param w           Width (in the same device unit). (Input)
		\param h           Height (in the same device unit). (Input)
		\param startAngle  Start angle in decimal degrees. (Input)
		\param finalAngle  Final angle in decimal degrees. (Input)
		*/
		virtual void drawSector(const double& xc, const double& yc,const double& w, const double& h, const double& startAngle, const double& finalAngle);
		
		/** \brief Fills the sector defined by a center coordinate (xc, yc), specified in device coordinates, width (w), height (h), the start angle (startANgle) and the final angle (finalAngle).
		\param xc		   Center abscissa. (Input)
		\param yc          Center ordinate. (Input)
		\param w           Width (in the same device unit). (Input)
		\param h           Height (in the same device unit). (Input)
		\param startAngle  Start angle in decimal degrees. (Input)
		\param finalAngle  Final angle in decimal degrees. (Input)
		*/
		virtual void fillSector(const double& xc, const double& yc,const double& w, const double& h,const double& startAngle, const double& finalAngle);


		virtual void drawImage(const unsigned char* image, const std::string& imageType, const int& imgSize, const double& dstX = TeMINFLOAT, const double& dstY = TeMINFLOAT);

		/** \brief Draws at (dstX, dstY) the pixels of a RGB image.
		\param imgW      Source image width. (Input) 
		\param imgH      Source image height. (Input)
		\param red       Pointer to red pixel component array. (Input)
		\param green     Pointer to green pixel component array. (Input)
		\param blue      Pointer to blue pixel component array. (Input)
		\param dstX      Baseline abscissa on canvas. (Input)
		\param dstY      Baseline ordinate on canvas. (Input)
		\param dstW      Bounding width for drawing on canvas from the abscissa (dstX). (Input)
		\param dstH      Bounding height for drawing on canvas from the ordinate (dstY). (Input)
		\param angle	 Angle of image rotation. (Input)
		*/
		virtual void drawImageRGBW(const unsigned int& imgW, const unsigned int& imgH,
			                    unsigned char* red, unsigned char* green, unsigned char* blue,
								const double& dstX, const double& dstY,
								const unsigned int& dstW, const unsigned int& dstH, const double& angle);

		/** \brief Draws at (dstX, dstY) the pixels of a RGB image.
		\param imgW      Source image width. (Input) 
		\param imgH      Source image height. (Input)
		\param red       Pointer to red pixel component array. (Input)
		\param green     Pointer to green pixel component array. (Input)
		\param blue      Pointer to blue pixel component array. (Input)
		\param dstX      Baseline abscissa on canvas. (Input)
		\param dstY      Baseline ordinate on canvas. (Input)
		\param dstW      Bounding width for drawing on canvas from the abscissa (dstX). (Input)
		\param dstH      Bounding height for drawing on canvas from the ordinate (dstY). (Input)
		\param angle	 Angle of image rotation. (Input)
		*/
		virtual void drawImageRGB(const unsigned int& imgW, const unsigned int& imgH,
			                    unsigned char* red, unsigned char* green, unsigned char* blue,
								const double& dstX, const double& dstY,
								const unsigned int& dstW, const unsigned int& dstH, const double& angle = 0);

	/** \brief Draws at (dstX, dstY) the pixels of a RGB image. 
		\param imgW      Source image width. (Input)
		\param imgH      Source image height. (Input)
		\param red       Pointer to red pixel component array. (Input)
		\param green     Pointer to green pixel component array. (Input)
		\param blue      Pointer to blue pixel component array. (Input)
		\param dstX      Baseline abscissa on canvas. (Input)
		\param dstY      Baseline ordinate on canvas. (Input)
		\param dstW      Bounding width for drawing on canvas from the abscissa (dstX). (Input)
		\param dstH      Bounding height for drawing on canvas from the ordinate (dstY). (Input)
		\param srcX      Initial abscissa position of the pixel on the image to copy to canvas. (Input)
		\param srcY      Initial ordinate position of the pixel on the image to copy to canvas. (Input)
		\param srcW      Number of columns (width) to copy from srcX position. (Input)
		\param srcH      Number of lines (height) to copy from srcY position. (Input)
		\param angle	 Angle of image rotation. (Input)
		*/
		virtual void drawImageRGB(const unsigned int& imgW, const unsigned int& imgH,
			                    unsigned char* red, unsigned char* green, unsigned char* blue,
								const double& dstX, const double& dstY,
								const unsigned int& dstW, const unsigned int& dstH,
								const double& srcX, const double& srcY,
								const unsigned int& srcW = 0, const unsigned int& srcH = 0, const double& angle = 0);

		/** \brief Draws the text with baseline at (x, y), specified in device coordinates.
		\param x     Baseline abscissa. (Input)
		\param y     Baseline ordinate. (Input)
		\param text  Text to write over canvas. (Input)
		*/
		virtual void drawText(const double& x, const double& y, const string& text);

		virtual void drawText(const TeBox &box, const std::string &text);

		 /** \brief Sets the visual for a given geometry type.
		\param v   Visual that must be applied to a given geometry type. (Input)
		\param rep Geometry type that the visual will be applied (may be: TePOLYGON for polygon geometry, TeLINES for line geometry, TePOINTS for point geometry, TeTEXT = 128 for text geometry, TeCELLS for cell geometry). (Input)
		\note The parameter transparency_ in visual must be an integer value between 0 and 100, it must be converted to 0-255 internally in each implementation.
		*/
		virtual void setVisual(TeVisual* v, const TeGeomRep& rep);

		/** \brief Sets the pen color used to draw point geometries.
		\param r Red component color value. (Input)
		\param g Green component color value. (Input)
		\param b Blue component color value. (Input)
        */
		virtual void setPointColor(const int& r, const int& g, const int& b);

		/** \brief Sets the pen color used to draw point geometries.
		\param r      Red component color value. (Input)
		\param g      Green component color value. (Input)
		\param b      Blue component color value. (Input)
		\param alpha  Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
        */
		virtual void setPointColor(const int& r, const int& g, const int& b, const int& alpha);

		virtual void setPointColor(const TeColor& color, const int& alpha);
		/** \brief Sets the alpha channel used to draw point geometries.
		\param alpha  Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
        */
		virtual void setPointAlpha(const int& alpha);

		/** \brief Sets the style for draw point geometries.
			\param style Point style that will be used to draw points. (Input)
			*/		
		virtual void setPointType(const int& type);

		/** \brief Sets pen size (in pixels) used to draw point geometries.
			\param s Pen size (in pixels). (Input)
			*/
		virtual void setPointSize(const int& s);

		virtual void setPointChar(const char& c);

		/** \brief Sets the pen color used to draw line geometries.
		\param r Red component color value. (Input)
		\param g Green component color value. (Input)
		\param b Blue component color value. (Input)
        */
		virtual void setLineColor(const int& r, const int& g, const int& b);

		/** \brief Sets the pen color used to draw line geometries.
		\param r     Red component color value. (Input)
		\param g     Green component color value. (Input)
		\param b     Blue component color value. (Input)
		\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
        */
		virtual void setLineColor(const int& r, const int& g, const int& b, const int& alpha);

		virtual void setLineColor(const TeColor& color, const int& alpha);

		/** \brief Sets the alpha channel used to draw line geometries.
		\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
        */
		virtual void setLineAlpha(const int& alpha);

		/** \brief Sets the style for draw line geometries.
		\param style Line style that will be used to draw lines. (Input)
        */
		virtual void setLineType(const int& type);

		/** \brief Sets an array of custom dashes and spaces for this Pen object
		\param	dashArray Pointer to an array of real numbers that specifies the length of the custom dashes and spaces. All elements in the array must be positive.
		\param	size Integer that specifies the number of elements in the dashArray array. The integer must be greater than 0 and not greater than the total number of elements in the array		
		*/
		virtual void setLineStyleDashes(double *dashArray, const int &size);

		/** \brief Sets pen width (in pixels) used to draw line geometries .
		\param width Pen size (in pixels). (Input)
		*/
		virtual void setLineWidth(const int& width);

		/** \brief Sets the color used to fill the draw of polygon geometries.
		\param r Red component color value. (Input)
		\param g Green component color value. (Input)
		\param b Blue component color value. (Input)
        */
		virtual void setPolygonColor(const int& r, const int& g, const int& b);

		/** \brief Sets the color used to fill the draw of polygon geometries.
			\param r     Red component color value. (Input)
			\param g     Green component color value. (Input)
			\param b     Blue component color value. (Input)
			\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
			*/
		virtual void setPolygonColor(const int& r, const int& g, const int& b, const int& alpha);

		virtual void setPolygonColor(const TeColor& color, const int& alpha);

		/** \brief Sets the alpha channel used to fill the draw of polygon geometries.
			\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
			*/
		virtual void setPolygonAlpha(const int& alpha);

		/** \brief Sets the pen color used to draw the boundary of polygon geometries.
			\param r Red component color value. (Input)
			\param g Green component color value. (Input)
			\param b Blue component color value. (Input)
			*/
		virtual void setPolygonBorderColor(const int& r, const int& g, const int& b);

		/** \brief Sets the pen color used to draw the boundary of polygon geometries.
			\param r     Red component color value. (Input)
			\param g     Green component color value. (Input)
			\param b     Blue component color value. (Input)
			\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
			*/
		virtual void setPolygonBorderColor(const int& r, const int& g, const int& b, const int& alpha);

		virtual void setPolygonBorderColor(const TeColor& color, const int& alpha);

		/** \brief Sets the alpha channel used to draw the boundary of polygon geometries.
			\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
			*/
		virtual void setPolygonBorderAlpha(const int& alpha);

		/** \brief Fills the polygon with foreground color or a background color (r, g, b) having a mask matrix fgbg (of '0's and '1's).
			\param width  Number o columns. (Input)
			\param height Number o lines. (Input)
			\param fgbg   Mask matrix, when '0' we must use the background color (r,g,b) and when the value is '1' we must use the foreground color set in setPolygonColor. (Input)
			\param br     Red background color. (Input)
			\param bg     Green background color. (Input)
			\param bb     Blue background color. (Input)
			*/
		virtual void setPolygonTypeStipple(const int& width, const int& height, unsigned char* fgbg, const int& br, const int& bg, const int& bb);

		/** \brief Sets the pattern style used to fill the draw of polygon geometries.
			\param width  The width of the pattern (number of columns of RGB array). (Input)
			\param height The height of the pattern (number of lines of RGB array). (Input)
			\param r      Pointer to red pixel component array. (Input)
			\param g      Pointer to green pixel component array. (Input)
			\param b      Pointer to blue pixel component array. (Input)
			*/
		virtual void setPolygonTypePattern(const int& width, const int& height, unsigned char* r, unsigned char* g, unsigned char* b);

		/** \brief Sets the style used to draw the boundary of polygon geometries.
			\param style Line style used to draw a polygon boundary. (Input)
			*/
		virtual void setPolygonBorderType(const int& type);

		/** \brief Sets pen width (in pixels) used to draw the boundary of polygon geometries .
			\param width Pen size (in pixels). (Input)
			*/
		virtual void setPolygonBorderWidth(const int& width);

			/** \brief Sets the color of the text.
			\param r Red component color value. (Input)
			\param g Green component color value. (Input)
			\param b Blue component color value. (Input)
			*/
		virtual void setTextColor(const int& r, const int& g, const int& b);

		/** \brief Sets the color of the text.
			\param r Red component color value. (Input)
			\param g Green component color value. (Input)
			\param b Blue component color value. (Input)
			\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
			*/
		virtual void setTextColor(const int& r, const int& g, const int& b, const int& alpha);

		virtual void setTextColor(const TeColor& color, const int& alpha);

		/** \brief Sets the alpha channel used to draw texts.		    
			\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
			*/
		virtual void setTextAlpha(const int& alpha) ;

		/** \brief Sets the background color of the text.
			\param r Red component color value. (Input)
			\param g Green component color value. (Input)
			\param b Blue component color value. (Input)
			*/
		virtual void setTextBackgroundColor(const int& r, const int& g, const int& b);

		/** \brief Sets the background color of the text.
			\param r Red component color value. (Input)
			\param g Green component color value. (Input)
			\param b Blue component color value. (Input)
			\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
			*/
		virtual void setTextBackgroundColor(const int& r, const int& g, const int& b, const int& alpha);

		virtual void setTextBackgroundColor(const TeColor& color, const int& alpha);

		/** \brief Sets the alpha channel used to fill the background of texts.
			\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
			*/
		virtual void setTextBackgroundAlpha(const int& alpha);

		virtual void setTextBackgroundType(const int& type);

		virtual void setTextBorderColor(const int& r, const int& g, const int& b);

		virtual void setTextBorderColor(const int& r, const int& g, const int& b, const int& alpha);

		virtual void setTextBorderColor(const TeColor& color, const int& alpha);

		virtual void setTextBorderAlpha(const int& alpha);

		virtual void setTextBorderType(const int& type);

		virtual void setTextBorderWidth(const int& width);

		/** \brief Sets the font family of the text.
			\param fontName Font name. (Input)
			*/
		virtual void setTextFont(const string& fontName);

		/** \brief Sets the size of the text.
			\param size Font size. (Input)
			*/
		virtual void setTextSize(const int& size);

		/** \brief Sets the size of the text in pixel
			\param size Font size. (Input)
			*/
		virtual void setTextPixelSize(const int &size);

		/** \brief Adjusts the angle used to draw texts.
			\param angle Angle in decimal degrees. (Input)
			*/
		virtual void setTextAngle(const double& angle);

		/** \brief Sets the bold style for text.
			\param bold If true, the text will be draw in bold face otherwise not. (Input)
			*/
		virtual void setTextBold(const bool& bold = true);

		/** \brief Sets the italic style for text.
			\param italic If true, the text will be draw in italic otherwise not. (Input)
			*/
		virtual void setTextItalic(const bool& italic = true);

		/** \brief Sets the alignment of the text.
			\param alignmentVert Vertical alignment. (Input)
			\param alignmentHoriz Horizontal alignment. (Input)
			*/
		virtual void setTextAlign(const double& alignmentHoriz, const double& alignmentVert);

		virtual void getTextAlign(double& alignmentHoriz, double& alignmentVert);

		//@}

		/** @name Clipping methods.
			* These methods can be used to set a sub-region .
			*/
		//@{

		/** \brief Establishes a clipping rectangle.
			Once setClipArea has been called, all future drawing operations will remain
			within the specified clipping area, until a new setClipArea call takes place.
			For instance, if a clipping rectangle of 25, 25, 75, 75 has been set within
			a 100x100 device area, a diagonal line from 0,0 to 99,99 will appear only
			between 25,25 and 75,75.
			\param box The box that will delimit the drawing area (in device coordinates). (Input)
			*/
		virtual void setClipArea(const TeBox& box);

		/** \brief Establishes a clipping rectangle.
			Once setClipArea has been called, all future drawing operations will remain
			within the specified clipping area, until a new setClipArea call takes place.
			For instance, if a clipping rectangle of 25, 25, 75, 75 has been set within
			a 100x100 device area, a diagonal line from 0,0 to 99,99 will appear only
			between 25,25 and 75,75.
			\param llx Lower left abscissa (in device coordinates). (Input)
			\param lly Lower left ordinate (in device coordinates). (Input)
			\param urx Upper left abscissa (in device coordinates). (Input)
			\param ury Upper left ordinate (in device coordinates). (Input)
			*/
		virtual void setClipArea(const double& llx, const double& lly, const double& urx, const double& ury);

		/** \brief Subtract a clipping rectangle from current clip area.
			Once setClipArea has been called, all future drawing operations will remain
			within the specified clipping area, until a new setClipArea call takes place.
			For instance, if a clipping rectangle of 25, 25, 75, 75 has been set within
			a 100x100 device area, a diagonal line from 0,0 to 99,99 will appear only
			between 25,25 and 75,75.
			\param llx Lower left abscissa (in device coordinates). (Input)
			\param lly Lower left ordinate (in device coordinates). (Input)
			\param urx Upper left abscissa (in device coordinates). (Input)
			\param ury Upper left ordinate (in device coordinates). (Input)
			*/
		virtual void subtractClipArea(const double& llx, const double& lly, const double& urx, const double& ury);

		/** \brief Returns the clipping area.
			\param llx Lower left abscissa (in device coordinates). (Output)
			\param lly Lower left ordinate (in device coordinates). (Output)
			\param urx Upper left abscissa (in device coordinates). (Output)
			\param ury Upper left ordinate (in device coordinates). (Output)
			*/
		virtual void getClipArea(double& llx, double& lly, double& urx, double& ury);

		/** \brief Establishes a clipping polygon.
			Once setClipArea has been called, all future drawing operations will remain
			within the specified polygon clipping area, until a new setClipArea call takes place.
			\param poly The polygon that will delimit the drawing area (in device coordinates). (Input)
			*/
		virtual void setClipArea(const TePolygon& poly);

		virtual void setClipArea(const TePolygonSet& polys, const TdkClipAreaType& clipType);
		
		/** \brief Returns the clipping polygon.
			\param poly The current clipping polygon (in device coordinates). (Output)
			*/
		virtual void getClipArea(TePolygon& poly);        

		/** \brief Activate clipping mode.
			*/
		virtual void activateClip();

		/** \brief Deactivate clipping mode.
			*/
		virtual void deactivateClip(); 

		/** \brief Set the printer page size.
			*/
		virtual void setPrinterPageSize(const short& pageSize);

		/** \brief Set the printer page orientation.
			*/
		virtual void setPrinterPageOrientation(const short& orientation);

		virtual int getCanvasId();

		/*! \brief Update Pen and Brush
		*/
		virtual void Update();


		virtual bool exportBuffer(const int &bufferId, const std::string &fileName, const std::string &fileFormat, const int &quality);

		virtual void setRasterDecoder(TeRaster* raster, TeRasterParams& params);

		virtual void setRasterTransparency(TeDecoder* dec, unsigned int transparency = 255);

		/** @name Utilities methods.
		* Utilitarian methods.
		*/
		//@{

		/** \brief Returns the bounding box of a text in world coordinates.
			\param text The text to retrieve the bounding box.
			\param box  A polygon with all text box coordinates (the box may not be parallel to xy axis). (Output)
			*/
		virtual void getTextBoundsW(const string& text, const double& x, const double& y,
			const double& angle, TdkTextBounds& bounds);

		/** \brief Returns the bounding box of a text in device coordinates.
    		\param text The text to retrieve the bounding box.
			\param box  A polygon with all text box coordinates (the box may not be parallel to xy axis). (Output)
			*/
		virtual void getTextBounds(const string& text, const double& x, const double& y,
			const double& angle, TdkTextBounds& bounds);

		//! \brief getTextBoundsW
		/*! Method to return the bouding box of text in world coordinate
			\param	text		terralib text
			\param	bound		bounding box calculate
		*/
		virtual void getTextBoundsW(const TeText& text, TdkTextBounds& bounds);

		//! \brief getTextBoundsW
		/*! Method to return the bouding box of text 
			\param	text		terralib text
			\param	bound		bounding box calculate
		*/
		virtual void getTextBounds(const TeText& text, TdkTextBounds& bounds);

		//! \brief getTextDimension
		/*! Method to return the text dimension
			\param	text		string
			\param	w			text width
			\param  h			text height
			\return	returns true whether sucess to calculate the text dimension
		*/
		virtual bool getTextDimension(const std::string &text, double &w, double &h);

		//! \brief getDpiX
		/*!	Method to return the dots per pixel on x axle
			\return		returns the double value
		*/
		virtual double getDpiX();

		//! \brief getDpiX
		/*!	Method to getDpiY the dots per pixel on y axle
			\return		returns the double value
		*/
		virtual double getDpiY();

		//@}

		
};



#endif

