#ifndef TDK_ABSTRACT_CANVAS_DRAW_H
#define TDK_ABSTRACT_CANVAS_DRAW_H

//tdk include files
#include <TdkCoordTransformer.h>
#include <TdkException.h>

#include <TeVisual.h>

//foward declarations
class TeLine2D;
class TeRaster;
class TeRasterParams;
class TeDecoder;
class TeProjection;

class TdkMathMatrix;
class TeVisual;
class TdkTextBounds;

class TdkAbstractImage;

#define inch		2.54
#define inch10		25.4

class TDK_API TdkAbstractCanvasDraw
{
public:
	enum TdkCanvasBuffer
	{
		cbrBack = 0,
		cbrFront = 1,
		cbrCache = 2, //!< Armazena o pixmap com o desenho vindo do banco de dados, sem conter edicao, selecao, etc.
		cbrPrinter = 3
	};

	/** @name This enum specifies the possible drawing states on canvas.
		*/
	enum TdkPaintMode
	{
		pmdREPLACE = 1,      /**< Allows to overwrite any previous drawing. */
		pmdXOR = 2,          /**< Do a XOR with the pixels in the buffer. */
		pmdNotXOR = 3,        /**< XXXXXXXXX. */ 
		pmdNot = 4
	};

	enum TdkClipAreaType
	{ 
		catUnion = 1,
		catIntersect = 2,
		catDifference = 3,
		catNotIntercsect = 4
	};

    TdkAbstractCanvasDraw(const int& canvasId);

    virtual ~TdkAbstractCanvasDraw();

	/** @name Canvas configuration
		* Methods related to canvas configuration.
		*/
	//@{		

	/** \brief Adjusts world (or window) coordinates area (supposing a cartesian reference system).
		\param llx Lower left abscissa. (Input)
		\param lly Lower left ordinate. (Input)
		\param urx Upper left abscissa. (Input)
		\param ury Upper left ordinate. (Input)
		*/
	virtual void setWindow(const double& llx, const double& lly, const double& urx, const double& ury);
	
	/** \brief Adjusts world (window) coordinates area (supposing a cartesian reference system).
		\param box Bounding box of world. (Input)
		*/
	virtual void setWindow(const TeBox& box);
	
	/** \brief Returns the world (window) coordinates area (supposing a cartesian reference system).
		\param llx Lower left abscissa. (Output)
		\param lly Lower left ordinate. (Output)
		\param urx Upper left abscissa. (Output)
		\param ury Upper left ordinate. (Output)
		*/
	virtual void getWindow(double& llx, double& lly, double& urx, double& ury);

	virtual void getWindow(TeBox& window);
	
	/** \brief Adjusts device coordinates area (supposing a cartesian reference system).
		\param llx Lower left abscissa. (Input)
		\param lly Lower left ordinate. (Input)
		\param urx Upper left abscissa. (Input)
		\param ury Upper left ordinate. (Input)
		*/
	virtual void setViewport(const double& llx, const double& lly, const double& urx, const double& ury);

	/** \brief Adjusts device coordinates area (supposing a cartesian reference system).
		\param box Device bounding box. (Input)
		*/
	virtual void setViewport(const TeBox& box);
	
	/** \brief Returns the device coordinates area.
		\param llx Lower left abscissa. (Output)
		\param lly Lower left ordinate. (Output)
		\param urx Upper left abscissa. (Output)
		\param ury Upper left ordinate. (Output)
		*/
	virtual void getViewport(double& llx, double& lly, double& urx, double& ury);

	virtual void getViewport(TeBox& viewport);

	/** \brief Transform world (or window) coordinates to device (or viewport) coordinates.
		\param wx World (or window) abscissa. (Input)
		\param wy World (or window) ordinate. (Input)
		\param vx Viewport (or device) abscissa. (Output)
		\param vy Viewport (or device) ordinate. (Output)
		*/
	virtual void window2Viewport(const double& wx, const double& wy, double& vx, double& vy);

	/** \brief Transform world (or window) value to device (or viewport) value according to one axis.
		\param w World (or window) value. (Input)
		\param v Viewport (or device) value. (Output)
		\param xdirection If world and device don't keep aspect ratio you should specify what axis to consider. (Input)
		*/
	virtual void window2Viewport(const double& w, double& v, const bool& xdirection = true);

    /** \brief Transform world (or window) value to device (or viewport) value according to one axis.
    \param pIn  Polygon in World coordinates. (Input)
    \param pOut Polygon in device coordinates. (Output)
    \param xdirection If world and device don't keep aspect ratio you should specify what axis to consider. (Input)
    */
    virtual void window2Viewport(const TePolygon& pIn, TePolygon& pOut);

	virtual void window2Viewport(const TeLine2D& lIn, TeLine2D& lOut);

	/** \brief Transform viewport (or device) coordinates to world (or window) coordinates.
		\param pIn Viewport (or device) coordinates. (Input)
		\param pOut window (or world) coordinates. (Output)
		*/
	virtual void viewport2Window(const TePolygon& pIn, TePolygon& pOut);

	/** \brief Transform viewport (or device) coordinates to world (or window) coordinates.
		\param vx Viewport (or device) abscissa. (Input)
		\param vy Viewport (or device) ordinate. (Input)
		\param wx World (or window) abscissa. (Output)
		\param wy World (or window) ordinate. (Output)
		*/
	virtual void viewport2Window(const double& vx, const double& vy, double& wx, double& wy);		

	/** \brief Transform device (or viewport) value to world (or window) value according to one axis.
		\param v Viewport (or device) value. (Input)
		\param w World (or window) value. (Output)			
		\param xdirection If world and device don't keep aspect ratio you should specify what axis to consider.
		*/
	virtual void viewport2Window(const double& v, double& w, const bool& xdirection = true);

    virtual void getDimension(double& width, double& height);

    virtual void getDimensionMM(double& width, double& height) = 0;

    virtual double getWidth() = 0;

    virtual double getHeight() = 0;

	/** \brief Sets the background color of the canvas to c.
		This will affect all buffers in use, painting all them with the specified color.
		\param c Background color that must be applied to canvas. (Input)
	    */
    virtual void setBackgroundColor(const TeColor& color);

    virtual void clear() = 0;

    virtual void clear(const int& bufferId);

    virtual double getPixelSize();

	virtual double getScale(TeProjection* viewProj);
	//@}

	/** @name Behavior Canvas methods
		* This methods can be used to set canvas behavior during drawing. For example,
		* one can create four buffers (see addBuffer):
		* <ul>
		* <li> one to write the vector content;
		* <li> one to write the raster content;
		* <li> one that can be used to draw temporary data, like new geometries in an editor;
		* <li> and a fourth that will be used as a copy (merger) of the three above (raster data below vector data, and new data above the other two).
		* </ul>
		* Then the application can manage these buffers:
		* <ul>
		* <li> when the user undo the drawing of geometries, only the vector and raster content need to be copy to the fourth buffer, so it will not be necessary to repaint all vector anda raster geometries again.
		* <li> when it is need to do a refresh, one can decide the order to copy to a single one.
		* </ul>
		*
		*/
	//@{

	/** \brief Adjusts canvas drawing mode: ....
		\param mode The mode can be one of the following: ..... (Input)
		*/
	virtual int setPaintMode(const int& mode);
	
	/** \brief Gets current Canvas paint mode.
		*/
	virtual int getPaintMode() const;

    /** \brief Sets the current buffer used to draw.
		This method changes the current buffer used to draw,
		you should specify a valid identifier, otherwise it will be raised an exception.
		\param  bufferId Buffer identification: it is a key for identify a given buffer. (Input)
		\return Return the previous buffer id that was active or -1 if the buffer could not be found.
		*/
	virtual int setActiveBuffer(const int& bufferId);
	
	/** \brief Gets the current buffer identifier or -1 if there is not a current one.
		*/
	virtual int getActiveBuffer();
	
	/** \brief Adds a new buffer identified by bufferId.
		If you try to create another one identified by the same id, it will raise an exception.
		\param bufferId The buffer identification associated to the new buffer. By default this value 
        is -1. This value indicates that the the user do not knows a valid buffer Id. In this case, 
        we must return a valid buffer id. (Input)
		\return Return the buffer Id.
		*/
	virtual int addBuffer(const int& bufferId = -1) = 0;

	/** \brief Adds a new buffer identified by bufferId, with pre-defined dimensions.
		If you try to create another one identified by the same id, it will raise an exception.
        \param width New buffer width.
        \param height New buffer height.
		\param bufferId The buffer identification associated to the new buffer. By default this value 
        is -1. This value indicates that the the user do not knows a valid buffer Id. In this case, 
        we must return a valid buffer id. (Input)
		\return Return the buffer Id.
		*/
	virtual int addBuffer(const double& width, const double& height, const int& bufferId = -1) = 0;

    /** \brief Removes the buffer identified by bufferId.
		If you specify an invalid id, it will be raised an exception.
		\param bufferId  The identification of the buffer to be removed. (Input)
		\note If the buffer is the current one, you should specify a new active (current) buffer, otherwise, you can get an undefined result.
		*/
	virtual void removeBuffer(const int& bufferId) = 0;
	
    /** \brief Resizes the buffer identified by \a bufferId parameter.
      * \param bufferId Identifier of buffer to be resized.
      * \param width New buffer width.
      * \param height New buffer height.
      */
    virtual void resizeBuffer(const int& bufferId, const double& width, const double& height) = 0;

	virtual void removeAllBuffers() = 0;

	virtual bool exportBuffer(const int &bufferId, const std::string &fileName, const std::string &fileFormat, const int &quality) = 0;
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
								const int& b = 0, const int& a = 0) = 0;

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
                            const double& dstX, const double& dstY, const double& angle)=0;

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
                            const double& dstX, const double& dstY, const double& dstW, const double& dstH, double angle)=0;

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
                            const double& dstX, const double& dstY, const double& dstW, const double& dstH)=0;

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
                            const double& dstX, const double& dstY) = 0;

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
                            const double& dstX, const double& dstY, const double& dstW, const double& dstH, const int& transp) = 0; 

    //@}

	/** @name Drawing methods for TerraLib's geometries using Window (World) Coordinates
		* Window (World) Coordinates Drawing Methods.
		* These methods (wich have the "W" suffix) can be used to draw on canvas using Window (World) Coordinates.
		* The visual (style) used to draw vector geometries is affected by the visual (style) methods defined in this API.
		*/
	//@{

	/** \brief Draws a point specified in window (world) coordinates.
		*	\param pt TerraLib point instance. (Input)			
		*/
	virtual void drawPointW(const TePoint& pt);

	/** \brief Draws a set of points specified in window (world) coordinates.
		\param points TerraLib pointset instance. (Input)
		*/
	virtual void drawPointsW(TePointSet& points);

	/** \brief Draws a line with vertexes specified in window (world) coordinates.
		\param line       TerraLib line instance. (Input)
		\param showPoint  If true the line vertexes will be drawn. (Input)
		*/
	virtual void drawLineW(const TeLine2D& line, const bool& showPoint = false);

	/** \brief Draws a set of lines with vertexes specified in window (world) coordinates.
		\param lines      TerraLib lineset instance. (Input)
		\param showPoint  If true the line vertexes will be drawn. (Input)
		*/
	virtual void drawLinesW(TeLineSet& lines, const bool& showPoint = false);

	/** \brief Draws a polygon with vertexes specified in window (world) coordinates.
		\param poly       TerraLib polygon instance. (Input)
		\param showPoint  If true the polygon vertexes will be drawn. (Input)
		*/
	virtual void drawPolygonW(const TePolygon& poly, const bool& showPoint = false);

	/** \brief Draws a set of polygons with vetexes specified in window (world) coordinates.
		\param polys      TerraLib polygonset instance. (Input)
		\param showPoint  If true the polygon vertexes will be drawn. (Input)
		*/
	virtual void drawPolygonsW(TePolygonSet& polys, const bool& showPoint = false);

	/** \brief Draws a cell with vetexes specified in window (world) coordinates.
		\param cell       TerraLib cell instance. (Input)
		\param showPoint  If true the cell vertexes will be drawn. (Input)
		*/
	virtual void drawCellW(const TeCell& cell, const bool& showPoint = false);

	/** \brief Draws a set of cells with vetexes specified in window (world) coordinates..
		\param cells      TerraLib cellset instance. (Input)
		\param showPoint  If true the cell vertexes will be drawn. (Input)
		*/
	virtual void drawCellsW(TeCellSet& cells, const bool& showPoint = false);

	/** \brief Draws a text with baseline coordinates specified in window (world) coordinates.
		\param text       TerraLib text instance. (Input)
		*/
	virtual void drawTextW(const TeText& text);

	virtual void drawTextW(const TeBox &box, const std::string &text);

	/** \brief Draws a set of texts with baseline coordinates specified in window (world) coordinates.
		\param texts      TerraLib textset instance. (Input)
		*/
	virtual void drawTextsW(TeTextSet& texts);
	//@}
	
	/** @name Drawing methods for auxiliary TerraLib's geometries in Window (World) Coordinates
		* Window (World) Coordinates Drawing Methods.
		* These methods (wich have the "W" suffix) can be used to draw on canvas using Window (World) Coordinates.
		* The visual (style) used to draw vector geometries is affected by the visual (style) methods defined in this API.
		*/
	//@{        

	/** \brief Draws a point specified in window (world) coordinates.
		\param coord TerraLib coordinate instance. (Input)
		*/
   	virtual void drawPointW(const TeCoord2D& coord);

	/** \brief Draws a box specified in window (world) coordinates.
		\param box        TerraLib box instance. (Input)
		\param showPoint  True if the box vertex will be drawn. (Input)
		*/
	virtual void drawBoxW(TeBox& box, const bool& showPoint = false);

	//@}

	/** @name Primitive drawing methods in Window (World) Coordinates
		* Window (World) Coordinates Drawing Methods.
		* These methods (wich have the "W" suffix) can be used to draw on canvas using Window (World) Coordinates.
		* The visual (style) used to draw vector geometries is affected by the visual (style) methods defined in this API.
		*/
	//@{ 
	
    /** \brief Draws a point specified in window (world) coordinates.
		\param x Abscissa: horizontal coordinate (x). (Input)
		\param y Ordinate: vertical coordinate (y). (Input)
		*/
	virtual void drawPointW(const double& x, const double& y);

	/** \brief Draws a line segment from (x0, y0) to (x1, y1), specified in window (world) coordinates.
		\param x0 Abscissa value indicating the segment begin. (Input)
		\param y0 Ordinate value indicating the segment begin. (Input)
		\param x1 Abscissa value indicating the segment end. (Input)
		\param y1 Ordinate value indicating the segment end. (Input)
		*/		     
	virtual void drawLineSegmentW(const double& x0, const double& y0,
			                        const double& x1, const double& y1);

	virtual void drawLineSegmentW(const TeCoord2D& c1, const TeCoord2D& c2);

	/** \brief Draws a rectangle with lower left corner at (llx, lly) and upper right corner at (urx, ury), specified in window (world) coordinates.
		\param llx Lower left abscissa. (Input)
		\param lly Lower left ordinate. (Input)
		\param urx Upper right abscissa. (Input)
		\param ury Upper right ordinate. (Input)
		*/
	virtual void drawRectW(const double& llx, const double& lly,
			                const double& urx, const double& ury);

    virtual void drawRectW(const TeBox& rect);

    /** \brief Fills the rectangle with lower left corner at (llx, lly) and upper right corner at (urx, ury), specified in window (world) coordinates.
		\param llx Lower left abscissa. (Input)
		\param lly Lower left ordinate. (Input)
		\param urx Upper right abscissa. (Input)
		\param ury Upper right ordinate. (Input)
		*/
	virtual void fillRectW(const double& llx, const double& lly,
			                const double& urx, const double& ury) ;

    virtual void fillRectW(const TeBox& rect);

	/** \brief Draws a line with vertexes specified in window (world) coordinates.
		\param line     A pointer to line vertexes. (Input)
		\param lineSize Number of line vertexes. (Input)
		*/
	virtual void drawLineW(TdkPrimitiveCoord* line, const int& lineSize);

	/** \brief Draws a polygon with vertexes specified in window (world) coordinates.
		\param poly     A pointer to polygon vertexes. (Input)
		\param ringSize A pointer to an array with each polygon ring size. (Input)
		\param nRings   The number of rings in the specified polygon. (Input)
		*/
	virtual void drawPolygonW(TdkPrimitiveCoord* poly, int* ringSize, const int& nRings);

    /** \brief Draws an ellipse with center at (xc, yc), specified in window (world) coordinates, x axis width r1 and y axis width r2, especified in the same window (world) unit.
		\param xc Center abscissa. (Input)
		\param yc Center ordinate. (Input)
		\param rx X axis width (in the same window unit). (Input)
		\param ry Y axis width (in the same window unit). (Input)
		\param angle Angle to rotate the ellipse round "x" axis. (Input)
		*/
	virtual void drawEllipseW(const double& xc, const double& yc,
			                    const double& rx, const double& ry, const double& angle);

	/** \brief Draws an ellipse with center at (xc, yc), specified in window (world) coordinates, x axis width r1 and y axis width r2, especified in the same window (world) unit.
		\param xc Center abscissa. (Input)
		\param yc Center ordinate. (Input)
		\param rx1 First conjugate radius (in the same window unit). (Input)
		\param ry1 First conjugate radius (in the same window unit). (Input)
		\param rx2 Second conjugate radius (in the same window unit). (Input)
		\param ry2 Second conjugate radius (in the same window unit). (Input)
		*/
	virtual void drawEllipseW(const double& xc, const double& yc,
			                    const double& rx1, const double& ry1,
								const double& rx2, const double& ry2);

    /** \brief Fills the ellipse with center at (xc, yc), specified in window (world) coordinates, x axis width r1 and y axis width r2, especified in the same window (world) unit.
		\param xc Center abscissa. (Input)
		\param yc Center ordinate. (Input)
		\param rx X axis width (in the same window unit). (Input)
		\param ry Y axis width (in the same window unit). (Input)
		\param angle Angle to rotate the ellipse round "x" axis. (Input)
		*/
	virtual void fillEllipseW(const double& xc, const double& yc,
			                    const double& rx, const double& ry, const double& angle);

	/** \brief Fills the ellipse with center at (xc, yc), specified in window (world) coordinates, x axis width r1 and y axis width r2, especified in the same window (world) unit.
		\param xc Center abscissa. (Input)
		\param yc Center ordinate. (Input)
		\param rx1 First conjugate radius (in the same window unit). (Input)
		\param ry1 First conjugate radius (in the same window unit). (Input)
		\param rx2 Second conjugate radius (in the same window unit). (Input)
		\param ry2 Second conjugate radius (in the same window unit). (Input)
		*/
	virtual void fillEllipseW(const double& xc, const double& yc,
			                    const double& rx1, const double& ry1,
								const double& rx2, const double& ry2);

    /** \brief Draws an arc defined by a center at (xc, yc), specified in window (world) coordinates, width (w), height (h), the start angle (startAngle) and the final angle (finalAngle).
		\param xc		   Center abscissa. (Input)
		\param yc          Center ordinate. (Input)
		\param w           Width (in the same window unit). (Input)
		\param h           Height (in the same window unit). (Input)
		\param startAngle  Start angle in decimal degrees. (Input)
		\param finalAngle  Final angle in decimal degrees. (Input)
		*/
	virtual void drawArcW(const double& xc, const double& yc,
			                const double& w, const double& h,
							const double& startAngle, const double& finalAngle);

	/** \brief Draws a sector defined by a center coordinate (xc, yc), specified in window (world) coordinates, width (w), height (h), the start angle (startAngle) and the final angle (finalAngle).
		\param xc		   Center abscissa. (Input)
		\param yc          Center ordinate. (Input)
		\param w           Width (in the same window unit). (Input)
		\param h           Height (in the same window unit). (Input)
		\param startAngle  Start angle in decimal degrees. (Input)
		\param finalAngle  Final angle in decimal degrees. (Input)
		*/
	virtual void drawSectorW(const double& xc, const double& yc,
			                    const double& w, const double& h,
								const double& startAngle, const double& finalAngle);

    /** \brief Fills the sector defined by a center coordinate (xc, yc), specified in window (world) coordinates, width (w), height (h), the start angle (startANgle) and the final angle (finalAngle).
		\param xc		   Center abscissa. (Input)
		\param yc          Center ordinate. (Input)
		\param w           Width (in the same window unit). (Input)
		\param h           Height (in the same window unit). (Input)
		\param startAngle  Start angle in decimal degrees. (Input)
		\param finalAngle  Final angle in decimal degrees. (Input)
		*/
	virtual void fillSectorW(const double& xc, const double& yc,
			                    const double& w, const double& h,
								const double& startAngle, const double& finalAngle);

    /** \brief Draws the text with baseline at (x, y), specified in window (world) coordinates.
		\param x     Baseline abscissa. (Input)
		\param y     Baseline ordinate. (Input)
		\param text  Text to write over canvas. (Input)
		*/
	virtual void drawTextW(const double& x, const double& y, const string& text);

	

	//@}

	/** @name Drawing methods for TerraLib's geometries using device coordinates
		* Device Coordinates Drawing Methods.
		* These methods can be used to draw on canvas using Device Coordinates.
		* The visual (style) used to draw vector geometries is affected by the visual (style) methods defined in this API.
		*/
	//@{

	/** \brief Draws a point specified in device coordinates.
		\param pt TerraLib point instance. (Input)
		*/
   	virtual void drawPoint(const TePoint& pt);

	/** \brief Draws a set of points specified in device coordinates.
		\param points TerraLib pointset instance. (Input)
		*/
	virtual void drawPoints(TePointSet& points);

	/** \brief Draws a line with vertexes specified in device coordinates.
		\param line       TerraLib line instance. (Input)
		\param showPoint  If true the line vertexes will be drawn. (Input)
		*/
	virtual void drawLine(const TeLine2D& line, const bool& showPoint = false) = 0;

	/** \brief Draws a set of lines with vertexes specified in device coordinates.
		\param lines      TerraLib lineset instance. (Input)
		\param showPoint  If true the line vertexes will be drawn. (Input)
		*/
	virtual void drawLines(TeLineSet& lines, const bool& showPoint = false);

	/** \brief Draws a polygon with vertexes specified in device coordinates.
		\param poly       TerraLib polygon instance. (Input)
		\param showPoint  If true the polygon vertexes will be drawn. (Input)
		*/
	virtual void drawPolygon(const TePolygon& poly, const bool& showPoint = false) = 0;

	/** \brief Draws a set of polygons with vertexes specified in device coordinates.
		\param polys      TerraLib polygonset instance. (Input)
		\param showPoint  If true the polygon vertexes will be drawn. (Input)
		*/
	virtual void drawPolygons(TePolygonSet& polys, const bool& showPoint = false);

	/** \brief Draws a cell with vertexes specified in device coordinates.
		\param cell       TerraLib cell instance. (Input)
		\param showPoint  If true the cell vertexes will be drawn. (Input)
		*/
	virtual void drawCell(const TeCell& cell, const bool& showPoint = false) = 0;

	/** \brief Draws a set of cells with vertexes specified in device coordinates.
		\param cells      TerraLib cellset instance. (Input)
		\param showPoint  If true the cell vertexes will be drawn. (Input)
		*/
	virtual void drawCells(TeCellSet& cells, const bool& showPoint = false);

	/** \brief Draws a text with baseline coordinates specified in device coordinates.
		\param text TerraLib text instance. (Input)
		*/
	virtual void drawText(const TeText& text);

	/** \brief Draws a set of texts with baseline coordinates specified in device coordinates.
		\param texts TerraLib textset instance. (Input)
		*/
	virtual void drawTexts(TeTextSet& texts);

    /** \brief Draws the raster.
		\param raster  A pointer to a TerraLib raster instance. (Input)
		\param transf  A pointer to the raster transform function. (Input)
		\param angle   ????
		\param matrix  ????
		*/
	virtual void drawRaster(TeRaster* raster) = 0;

	//! \brief Draw the abstract Image
	virtual void drawRaster(TdkAbstractImage* raster, const TeBox &box, const double &angle=0.0) =0;

	virtual void drawRaster(TeRaster* raster, const double &scaleX, const double &scaleY)=0;

	virtual void drawRaster(TeRaster* raster, const double &scaleX, const double &scaleY,const double &y)=0;

	//@}

	/** @name Drawing methods for auxiliary TerraLib's geometries using device coordinates
		* Device Coordinates Drawing Methods.
		* These methods can be used to draw on canvas using Device Coordinates.
		* The visual (style) used to draw vector geometries is affected by the visual (style) methods defined in this API.
		*/
	//@{

	/** \brief Draws a point specified in device coordinates.
		\param coord TerraLib coordinate instance. (Input)
		*/
   	virtual void drawPoint(const TeCoord2D& coord);

	/** \brief Draws a box specified in device coordinates.
		\param box        TerraLib box instance. (Input)
		\param showPoint  True if the box vertex will be drawn. (Input)
		*/
	virtual void drawBox(const TeBox& box, const bool& showPoint = false);

	//@}

	/** @name Primitive drawing methods using device coordinates
		* Device Coordinates Drawing Methods.
		* These methods can be used to draw on canvas using Device Coordinates.
		* The visual (style) used to draw vector geometries is affected by the visual (style) methods defined in this API.
		*/
	//@{		
	
	/** \brief Draws a point specified in device coordinates.
		\param x Abscissa: horizontal coordinate (x). (Input)
		\param y Ordinate: vertical coordinate (y). (Input)
		*/
	virtual void drawPoint(const double& x, const double& y) = 0;

	/** \brief Draws a line segment from (x0, y0) to (x1, y1), specified in device coordinates.
		\param x0 Abscissa value indicating the segment begin. (Input)
		\param y0 Ordinate value indicating the segment begin. (Input)
		\param x1 Abscissa value indicating the segment end. (Input)
		\param y1 Ordinate value indicating the segment end. (Input)
		*/		     
	virtual void drawLineSegment(const double& x0, const double& y0,
			                        const double& x1, const double& y1) = 0;

	virtual void drawLineSegment(const TeCoord2D& c1, const TeCoord2D& c2) = 0;

	/** \brief Draws a rectangle with lower left corner at (llx, lly) and uper right corner at (urx, ury), specified in device coordinates.
		\param llx Lower left abscissa. (Input)
		\param lly Lower left ordinate. (Input)
		\param urx Upper right abscissa. (Input)
		\param ury Upper right ordinate. (Input)
		*/
	virtual void drawRect(const double& llx, const double& lly,
			                const double& urx, const double& ury) = 0;

    virtual void drawRect(const TeBox& rect);

    /** \brief Fills the rectangle with lower left corner at (llx, lly) and uper right corner at (urx, ury), specified in device coordinates.
		\param llx Lower left abscissa. (Input)
		\param lly Lower left ordinate. (Input)
		\param urx Upper right abscissa. (Input)
		\param ury Upper right ordinate. (Input)
		*/
	virtual void fillRect(const double& llx, const double& lly,
			                const double& urx, const double& ury) = 0;

    virtual void fillRect(const TeBox& rect);

	/** \brief Draws a line with vertexes specified in device coordinates.
		\param line     A pointer to line vertexes. (Input)
		\param lineSize Number of line vertexes. (Input)
		*/
	virtual void drawLine(TdkPrimitiveCoord* line, const int& lineSize) = 0;

	/** \brief Draws a polygon with vertexes specified in device coordinates.
		\param poly     A pointer to polygon vertexes. (Input)
		\param ringSize A pointer to an array with each polygon ring size. (Input)
		\param nRings   The number of rings in the specified polygon. (Input)
		*/
	virtual void drawPolygon(TdkPrimitiveCoord* poly, int* ringSize, const int& nRings) = 0;		

	/** \brief Draws an ellipse with center at (xc, yc), specified in device coordinates, x axis width r1 and y axis width r2, especified in the same device unit.
		\param xc Center abscissa. (Input)
		\param yc Center ordinate. (Input)
		\param rx X axis width (in the same device unit). (Input)
		\param ry Y axis width (in the same device unit). (Input)
		\param angle Angle to rotate the ellipse round "x" axis. (Input)
		*/
	virtual void drawEllipse(const double& xc, const double& yc,
			                    const double& rx, const double& ry, const double& angle) = 0;

	/** \brief Draws an ellipse with center at (xc, yc), specified in device coordinates, x axis width r1 and y axis width r2, especified in the same device unit.
		\param xc Center abscissa. (Input)
		\param yc Center ordinate. (Input)
		\param rx1 First conjugate radius (in the same device unit). (Input)
		\param ry1 First conjugate radius (in the same device unit). (Input)
		\param rx2 Second conjugate radius (in the same device unit). (Input)
		\param ry2 Second conjugate radius (in the same device unit). (Input)
		*/
	virtual void drawEllipse(const double& xc, const double& yc,
			                    const double& rx1, const double& ry1,
								const double& rx2, const double& ry2) = 0;

    /** \brief Fills the ellipse with center at (xc, yc), specified in device coordinates, x axis width r1 and y axis width r2, especified in the same device unit.
		\param xc Center abscissa. (Input)
		\param yc Center ordinate. (Input)
		\param rx X axis width (in the same device unit). (Input)
		\param ry Y axis width (in the same device unit). (Input)
		\param angle Angle to rotate the ellipse round "x" axis. (Input)
		*/
	virtual void fillEllipse(const double& xc, const double& yc,
			                    const double& rx, const double& ry, const double& angle) = 0;

	/** \brief Fills the ellipse with center at (xc, yc), specified in device coordinates, x axis width r1 and y axis width r2, especified in the same device unit.
		\param xc Center abscissa. (Input)
		\param yc Center ordinate. (Input)
		\param rx1 First conjugate radius (in the same device unit). (Input)
		\param ry1 First conjugate radius (in the same device unit). (Input)
		\param rx2 Second conjugate radius (in the same device unit). (Input)
		\param ry2 Second conjugate radius (in the same device unit). (Input)
		*/
	virtual void fillEllipse(const double& xc, const double& yc,
			                    const double& rx1, const double& ry1,
								const double& rx2, const double& ry2) = 0;

    /** \brief Draws an arc defined by a center at (xc, yc), specified in device coordinates, width (w), height (h), the start angle (startAngle) and the final angle (finalAngle).
		\param xc		   Center abscissa. (Input)
		\param yc          Center ordinate. (Input)
		\param w           Width (in the same device unit). (Input)
		\param h           Height (in the same device unit). (Input)
		\param startAngle  Start angle in decimal degrees. (Input)
		\param finalAngle  Final angle in decimal degrees. (Input)
		*/
	virtual void drawArc(const double& xc, const double& yc,
			                const double& w, const double& h,
							const double& startAngle, const double& finalAngle) = 0;

	/** \brief Draws a sector defined by a center coordinate (xc, yc), specified in device coordinates, width (w), height (h), the start angle (startANgle) and the final angle (finalAngle).
		\param xc		   Center abscissa. (Input)
		\param yc          Center ordinate. (Input)
		\param w           Width (in the same device unit). (Input)
		\param h           Height (in the same device unit). (Input)
		\param startAngle  Start angle in decimal degrees. (Input)
		\param finalAngle  Final angle in decimal degrees. (Input)
		*/
	virtual void drawSector(const double& xc, const double& yc,
			                const double& w, const double& h,
							const double& startAngle, const double& finalAngle) = 0;

    /** \brief Fills the sector defined by a center coordinate (xc, yc), specified in device coordinates, width (w), height (h), the start angle (startANgle) and the final angle (finalAngle).
		\param xc		   Center abscissa. (Input)
		\param yc          Center ordinate. (Input)
		\param w           Width (in the same device unit). (Input)
		\param h           Height (in the same device unit). (Input)
		\param startAngle  Start angle in decimal degrees. (Input)
		\param finalAngle  Final angle in decimal degrees. (Input)
		*/
	virtual void fillSector(const double& xc, const double& yc,
			                const double& w, const double& h,
							const double& startAngle, const double& finalAngle) = 0;


    virtual void drawImage(const unsigned char* image, const std::string& imageType, 
        const int& imgSize, const double& dstX = TeMINFLOAT, const double& dstY = TeMINFLOAT) = 0;

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
	virtual void drawImageRGBW(const unsigned int& imgW, const unsigned int& imgH,
			                    unsigned char* red, unsigned char* green, unsigned char* blue,
								const double& dstX, const double& dstY,
								const unsigned int& dstW, const unsigned int& dstH,
								const double& srcX, const double& srcY,
								const unsigned int& srcW = 0, const unsigned int& srcH = 0, const double& angle = 0);

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
								const unsigned int& dstW, const unsigned int& dstH, const double& angle = 0) = 0;

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
								const unsigned int& srcW = 0, const unsigned int& srcH = 0, const double& angle = 0) = 0;

    /** \brief Draws the text with baseline at (x, y), specified in device coordinates.
		\param x     Baseline abscissa. (Input)
		\param y     Baseline ordinate. (Input)
		\param text  Text to write over canvas. (Input)
		*/
	virtual void drawText(const double& x, const double& y, const string& text) = 0;

	virtual void drawText(const TeBox &box, const std::string &text) = 0;
	//@}		

	/** @name Styles configuration
		* Methods related to styles configuration.
		*/
	//@{

    /** \brief Sets the visual for a given geometry type.
		\param v   Visual that must be applied to a given geometry type. (Input)
		\param rep Geometry type that the visual will be applied (may be: TePOLYGON for polygon geometry, TeLINES for line geometry, TePOINTS for point geometry, TeTEXT = 128 for text geometry, TeCELLS for cell geometry). (Input)
		\note The parameter transparency_ in visual must be an integer value between 0 and 100, it must be converted to 0-255 internally in each implementation.
		*/
	virtual void setVisual(TeVisual* v, const TeGeomRep& rep) = 0;

	/** \brief Sets the pen color used to draw point geometries.
		\param r Red component color value. (Input)
		\param g Green component color value. (Input)
		\param b Blue component color value. (Input)
        */
	virtual void setPointColor(const int& r, const int& g, const int& b) = 0;

	/** \brief Sets the pen color used to draw point geometries.
		\param r      Red component color value. (Input)
		\param g      Green component color value. (Input)
		\param b      Blue component color value. (Input)
		\param alpha  Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
        */
	virtual void setPointColor(const int& r, const int& g, const int& b, const int& alpha) = 0;

    virtual void setPointColor(const TeColor& color, const int& alpha) = 0;

    /** \brief Sets the alpha channel used to draw point geometries.
		\param alpha  Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
        */
	virtual void setPointAlpha(const int& alpha) = 0;

	/** \brief Sets the style for draw point geometries.
		\param style Point style that will be used to draw points. (Input)
        */		
	virtual void setPointType(const int& type) = 0;

	/** \brief Sets pen size (in pixels) used to draw point geometries.
		\param s Pen size (in pixels). (Input)
		*/
	virtual void setPointSize(const int& s) = 0;

    virtual void setPointChar(const char& c) = 0;

	/** \brief Sets the pen color used to draw line geometries.
		\param r Red component color value. (Input)
		\param g Green component color value. (Input)
		\param b Blue component color value. (Input)
        */
	virtual void setLineColor(const int& r, const int& g, const int& b) = 0;

    /** \brief Sets the pen color used to draw line geometries.
		\param r     Red component color value. (Input)
		\param g     Green component color value. (Input)
		\param b     Blue component color value. (Input)
		\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
        */
	virtual void setLineColor(const int& r, const int& g, const int& b, const int& alpha) = 0;

    virtual void setLineColor(const TeColor& color, const int& alpha) = 0;

    /** \brief Sets the alpha channel used to draw line geometries.
		\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
        */
	virtual void setLineAlpha(const int& alpha) = 0;

    /** \brief Sets the style for draw line geometries.
		\param style Line style that will be used to draw lines. (Input)
        */
	virtual void setLineType(const int& type) = 0;

	/** \brief Sets an array of custom dashes and spaces for this Pen object
		\param	dashArray Pointer to an array of real numbers that specifies the length of the custom dashes and spaces. All elements in the array must be positive.
		\param	size Integer that specifies the number of elements in the dashArray array. The integer must be greater than 0 and not greater than the total number of elements in the array		
	*/
	virtual void setLineStyleDashes(double *dashArray, const int &size) = 0;

    /** \brief Sets pen width (in pixels) used to draw line geometries .
		\param width Pen size (in pixels). (Input)
		*/
	virtual void setLineWidth(const int& width) = 0;

    /** \brief Sets the color used to fill the draw of polygon geometries.
		\param r Red component color value. (Input)
		\param g Green component color value. (Input)
		\param b Blue component color value. (Input)
        */
	virtual void setPolygonColor(const int& r, const int& g, const int& b) = 0;

	/** \brief Sets the color used to fill the draw of polygon geometries.
		\param r     Red component color value. (Input)
		\param g     Green component color value. (Input)
		\param b     Blue component color value. (Input)
		\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
        */
	virtual void setPolygonColor(const int& r, const int& g, const int& b, const int& alpha) = 0;

    virtual void setPolygonColor(const TeColor& color, const int& alpha) = 0;

	/** \brief Sets the alpha channel used to fill the draw of polygon geometries.
		\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
        */
	virtual void setPolygonAlpha(const int& alpha) = 0;

	/** \brief Sets the pen color used to draw the boundary of polygon geometries.
		\param r Red component color value. (Input)
		\param g Green component color value. (Input)
		\param b Blue component color value. (Input)
        */
	virtual void setPolygonBorderColor(const int& r, const int& g, const int& b) = 0;

	/** \brief Sets the pen color used to draw the boundary of polygon geometries.
		\param r     Red component color value. (Input)
		\param g     Green component color value. (Input)
		\param b     Blue component color value. (Input)
		\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
        */
	virtual void setPolygonBorderColor(const int& r, const int& g, const int& b, const int& alpha) = 0;

    virtual void setPolygonBorderColor(const TeColor& color, const int& alpha) = 0;

	/** \brief Sets the alpha channel used to draw the boundary of polygon geometries.
		\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
        */
	virtual void setPolygonBorderAlpha(const int& alpha) = 0;

	/** \brief Sets the style for draw line geometries.
		\param style Line style that will be used to draw lines. (Input)
        */
	virtual void setPolygonType(const int& type) = 0;

    /** \brief Fills the polygon with foreground color or a background color (r, g, b) having a mask matrix fgbg (of '0's and '1's).
		\param width  Number o columns. (Input)
		\param height Number o lines. (Input)
		\param fgbg   Mask matrix, when '0' we must use the background color (r,g,b) and when the value is '1' we must use the foreground color set in setPolygonColor. (Input)
		\param br     Red background color. (Input)
		\param bg     Green background color. (Input)
		\param bb     Blue background color. (Input)
        */
	virtual void setPolygonTypeStipple(const int& width, const int& height, unsigned char* fgbg, const int& br, const int& bg, const int& bb) = 0;

	/** \brief Sets the pattern style used to fill the draw of polygon geometries.
		\param width  The width of the pattern (number of columns of RGB array). (Input)
		\param height The height of the pattern (number of lines of RGB array). (Input)
		\param r      Pointer to red pixel component array. (Input)
		\param g      Pointer to green pixel component array. (Input)
		\param b      Pointer to blue pixel component array. (Input)
        */
	virtual void setPolygonTypePattern(const int& width, const int& height, unsigned char* r, unsigned char* g, unsigned char* b) = 0;

    /** \brief Sets the style used to draw the boundary of polygon geometries.
		\param style Line style used to draw a polygon boundary. (Input)
        */
	virtual void setPolygonBorderType(const int& type) = 0;

    /** \brief Sets pen width (in pixels) used to draw the boundary of polygon geometries .
		\param width Pen size (in pixels). (Input)
		*/
	virtual void setPolygonBorderWidth(const int& width) = 0;

	/** \brief Sets the color of the text.
		\param r Red component color value. (Input)
		\param g Green component color value. (Input)
		\param b Blue component color value. (Input)
		*/
	virtual void setTextColor(const int& r, const int& g, const int& b) = 0;

	/** \brief Sets the color of the text.
		\param r Red component color value. (Input)
		\param g Green component color value. (Input)
		\param b Blue component color value. (Input)
		\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
		*/
	virtual void setTextColor(const int& r, const int& g, const int& b, const int& alpha) = 0;

    virtual void setTextColor(const TeColor& color, const int& alpha) = 0;

	/** \brief Sets the alpha channel used to draw texts.		    
		\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
		*/
	virtual void setTextAlpha(const int& alpha) = 0;

	/** \brief Sets the background color of the text.
		\param r Red component color value. (Input)
		\param g Green component color value. (Input)
		\param b Blue component color value. (Input)
		*/
	virtual void setTextBackgroundColor(const int& r, const int& g, const int& b) = 0;

	/** \brief Sets the background color of the text.
		\param r Red component color value. (Input)
		\param g Green component color value. (Input)
		\param b Blue component color value. (Input)
		\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
		*/
	virtual void setTextBackgroundColor(const int& r, const int& g, const int& b, const int& alpha) = 0;

    virtual void setTextBackgroundColor(const TeColor& color, const int& alpha) = 0;

	/** \brief Sets the alpha channel used to fill the background of texts.
		\param alpha Must be a value between 0 and 255, where 0 is opaque and 255 is completely transparent. (Input)
		*/
	virtual void setTextBackgroundAlpha(const int& alpha) = 0;

    virtual void setTextBackgroundType(const int& type) = 0;

    virtual void setTextBorderColor(const int& r, const int& g, const int& b) = 0;

    virtual void setTextBorderColor(const int& r, const int& g, const int& b, const int& alpha) = 0;

    virtual void setTextBorderColor(const TeColor& color, const int& alpha) = 0;

    virtual void setTextBorderAlpha(const int& alpha) = 0;

    virtual void setTextBorderType(const int& type) = 0;

    virtual void setTextBorderWidth(const int& width) = 0;

    /** \brief Sets the font family of the text.
		\param fontName Font name. (Input)
		*/
	virtual void setTextFont(const string& fontName) = 0;

    /** \brief Sets the size of the text.
		\param size Font size. (Input)
		*/
	virtual void setTextSize(const int& size) = 0;

	/** \brief Sets the size of the text in pixels
		\param size Font size. (Input)
		*/
	virtual void setTextPixelSize(const int &size) = 0;

	/** \brief Adjusts the angle used to draw texts.
		\param angle Angle in decimal degrees. (Input)
		*/
	virtual void setTextAngle(const double& angle) = 0;

    /** \brief Sets the bold style for text.
		\param bold If true, the text will be draw in bold face otherwise not. (Input)
		*/
	virtual void setTextBold(const bool& bold = true) = 0;

	/** \brief Sets the italic style for text.
		\param italic If true, the text will be draw in italic otherwise not. (Input)
		*/
	virtual void setTextItalic(const bool& italic = true) = 0;

	/** \brief Sets the alignment of the text.
		\param alignmentVert Vertical alignment. (Input)
		\param alignmentHoriz Horizontal alignment. (Input)
		*/
	virtual void setTextAlign(const double& alignmentHoriz, const double& alignmentVert) = 0;

	virtual void getTextAlign(double& alignmentHoriz, double& alignmentVert) = 0;


	virtual void setRasterDecoder(TeRaster* raster, TeRasterParams& params) = 0;

	virtual void setRasterTransparency(TeDecoder* dec, unsigned int transparency = 255) = 0;

	//@}

	/** @name Utilities methods.
		* Utilitarian methods.
		*/
	//@{

    /** \brief Returns the bounding box of a text in world coordinates.
		\param text The text to retrieve the bounding box.
		\param box  A polygon with all text box coordinates (the box may not be parallel to xy axis). (Output)
		*/
    virtual void getTextBoundsW(const string& text, const double& x, const double& y,
		const double& angle, TdkTextBounds& bounds) = 0;

	/** \brief Returns the bounding box of a text in device coordinates.
    	\param text The text to retrieve the bounding box.
		\param box  A polygon with all text box coordinates (the box may not be parallel to xy axis). (Output)
		*/
	virtual void getTextBounds(const string& text, const double& x, const double& y,
		const double& angle, TdkTextBounds& bounds) = 0;

	virtual void getTextBoundsW(const TeText& text, TdkTextBounds& bounds) = 0;

	virtual void getTextBounds(const TeText& text, TdkTextBounds& bounds) = 0;

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
	virtual void setClipArea(const TeBox& box) = 0;

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
	virtual void setClipArea(const double& llx, const double& lly, const double& urx, const double& ury) = 0;

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
	virtual void subtractClipArea(const double& llx, const double& lly, const double& urx, const double& ury) = 0;

	/** \brief Returns the clipping area.
		\param llx Lower left abscissa (in device coordinates). (Output)
		\param lly Lower left ordinate (in device coordinates). (Output)
		\param urx Upper left abscissa (in device coordinates). (Output)
		\param ury Upper left ordinate (in device coordinates). (Output)
		*/
    virtual void getClipArea(double& llx, double& lly, double& urx, double& ury) = 0;

	/** \brief Establishes a clipping polygon.
		Once setClipArea has been called, all future drawing operations will remain
		within the specified polygon clipping area, until a new setClipArea call takes place.
		\param poly The polygon that will delimit the drawing area (in device coordinates). (Input)
		*/
    virtual void setClipArea(const TePolygon& poly) = 0;

	virtual void setClipArea(const TePolygonSet& polys, const TdkClipAreaType& clipType) = 0;
	
	/** \brief Returns the clipping polygon.
		\param poly The current clipping polygon (in device coordinates). (Output)
		*/
	virtual void getClipArea(TePolygon& poly) = 0;        

	/** \brief Activate clipping mode.
		*/
    virtual void activateClip() = 0;

	/** \brief Deactivate clipping mode.
		*/
    virtual void deactivateClip() = 0; 

	/** \brief Set the printer page size.
		*/
	virtual void setPrinterPageSize(const short& pageSize) = 0;

	/** \brief Set the printer page orientation.
		*/
	virtual void setPrinterPageOrientation(const short& orientation) = 0;

    virtual int getCanvasId();

	/*! \brief Update Pen and Brush
	*/
	virtual void Update()=0;

	virtual bool getTextDimension(const std::string &text, double &w, double &h) = 0;

	virtual double getDpiX()=0;

	virtual double getDpiY()=0;

	//@}
protected:
	int _currentBufferId;				//!< Indicates what is the active current buffer. If this value is set to -1, so there is not a current buffer.
	TeColor _backgroundColor;			//!< Indicates the current canvas background color.
    int _paintMode;						//!< Current Canvas paint mode.
	TdkCoordTransformer _transformer;	//!< This instance can be used to transform coordinates from world to device and device to world.
    int _canvasId;                      //!< Canvas identifier.
};

#endif
