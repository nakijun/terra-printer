#include <TdkAbstractCanvasDraw.h>

#include <TeProjection.h>
#include <TeRaster.h>
#include <TeDecoderMemory.h>

TdkAbstractCanvasDraw::TdkAbstractCanvasDraw(const int& canvasId) :
_paintMode(pmdREPLACE),
_canvasId(canvasId),
_currentBufferId(-1),
_backgroundColor(TeColor(255, 255, 255))
{
}

TdkAbstractCanvasDraw::~TdkAbstractCanvasDraw()
{
}
void TdkAbstractCanvasDraw::setWindow(const double& llx, const double& lly, const double& urx, 
                                      const double& ury)
{
    _transformer.setWindow(llx, lly, urx, ury);
}

void TdkAbstractCanvasDraw::setWindow(const TeBox& box)
{
    setWindow(box.x1(), box.y1(), box.x2(), box.y2());
}

void TdkAbstractCanvasDraw::getWindow(double& llx, double& lly, double& urx, double& ury)
{
    _transformer.getWindow(llx, lly, urx, ury);
}

void TdkAbstractCanvasDraw::getWindow(TeBox& window)
{
    getWindow(window.x1_, window.y1_, window.x2_, window.y2_);
}

void TdkAbstractCanvasDraw::setViewport(const double& llx, const double& lly, const double& urx, 
                                        const double& ury)
{
    _transformer.setViewport(llx, lly, urx, ury);
}

void TdkAbstractCanvasDraw::setViewport(const TeBox& box)
{
    setViewport(box.x1(), box.y1(), box.x2(), box.y2());
}

void TdkAbstractCanvasDraw::getViewport(double& llx, double& lly, double& urx, double& ury)
{
    _transformer.getViewport(llx, lly, urx, ury);
}

void TdkAbstractCanvasDraw::getViewport(TeBox& viewport)
{
    getViewport(viewport.x1_, viewport.y1_, viewport.x2_, viewport.y2_);
}

void TdkAbstractCanvasDraw::window2Viewport(const double& wx, const double& wy, double& vx, double& vy)
{
    _transformer.window2Viewport(wx, wy, vx, vy);
}

void TdkAbstractCanvasDraw::window2Viewport(const double& w, double& v, const bool& xdirection)
{
    _transformer.window2Viewport(w, v, xdirection);
}

void TdkAbstractCanvasDraw::window2Viewport(const TePolygon& pIn, TePolygon& pOut)
{
    _transformer.window2Viewport(pIn, pOut);
}

void TdkAbstractCanvasDraw::window2Viewport(const TeLine2D& lIn, TeLine2D& lOut)
{
    _transformer.window2Viewport(lIn, lOut);
}

void TdkAbstractCanvasDraw::viewport2Window(const TePolygon& pIn, TePolygon& pOut)
{
    _transformer.viewport2Window(pIn, pOut);
}

void TdkAbstractCanvasDraw::viewport2Window(const double& vx, const double& vy, double& wx, double& wy)
{
    _transformer.viewport2Window(vx, vy, wx, wy);
}

void TdkAbstractCanvasDraw::viewport2Window(const double& v, double& w, const bool& xdirection)
{
    _transformer.viewport2Window(v, w, xdirection);
}

void TdkAbstractCanvasDraw::getDimension(double& width, double& height)
{
    width = getWidth();
    height = getHeight();
}

void TdkAbstractCanvasDraw::setBackgroundColor(const TeColor& color)
{
    _backgroundColor = color;
}

void TdkAbstractCanvasDraw::clear(const int& bufferId)
{
    int oldBuffer = setActiveBuffer(bufferId);
    clear();

    setActiveBuffer(oldBuffer);
}

double TdkAbstractCanvasDraw::getPixelSize()
{
	// Gets the drawing area in world coordinates.
	TeBox windowsBBox;
	getWindow(windowsBBox.x1_, windowsBBox.y1_, windowsBBox.x2_, windowsBBox.y2_);

	// Gets the canvas dimensions in pixels.
	double canvasWidthPx;
	double canvasHeightPx;
	getDimension(canvasWidthPx, canvasHeightPx);

	// Computes the pixel size.
	return (windowsBBox.width() / canvasWidthPx);
}

double TdkAbstractCanvasDraw::getScale(TeProjection* viewProj)
{
	//FROM TERRAVIEW
	TeBox windowsBBox;
	getWindow(windowsBBox.x1_, windowsBBox.y1_, windowsBBox.x2_, windowsBBox.y2_);

	// Gets the canvas dimension in pixels.
	double canvasWidthPx;
	double canvasHeightPx;
	getDimension(canvasWidthPx, canvasHeightPx);

	// Gets the canvas dimension in mm.
	double canvasWidthMM;
	double canvasHeightMM;
	getDimensionMM(canvasWidthMM, canvasHeightMM);

	double	dxw = windowsBBox.width(),
		dyw = windowsBBox.height(),
		dxv = canvasWidthPx,
		dyv = canvasHeightPx;

	double	fx = dxv/dxw,
		fy = dyv/dyw,
		factor;

	if (fx > fy)
	{
		factor = fy;
		canvasWidthPx = (int)(factor * dxw + .5);
	}
	else
	{
		factor = fx;
		canvasHeightPx = (int)(factor * dyw + .5);
	}

	double wpixels = canvasWidthPx;
	double wMM = canvasWidthMM;
	double wT = wMM;

	// Gets canvas dimension in view coordinates.
	if (viewProj)
	{
		const string unit = viewProj->units();
		if (TeConvertToUpperCase(unit) == "METERS")
			wT = wMM / 1000.;
		else if (TeConvertToUpperCase(unit) == "KILOMETERS")
			wT = wMM / 1000000.;
		else if (TeConvertToUpperCase(unit) == "CENTIMETERS")
			wT = wMM / 100.;
		else if (TeConvertToUpperCase(unit) == "MILLIMETERS")
			wT = wMM;
		else if (TeConvertToUpperCase(unit) == "FEET")
			wT = wMM / (12. * 25.4);
		else if (TeConvertToUpperCase(unit) == "INCHES")
			wT = wMM / 25.4;
		else if (TeConvertToUpperCase(unit) == "DECIMALDEGREES")
			wT = wMM / 110000000.;
	}
	double wp = wT / wpixels;
	return (1. / factor ) / wp;
}

int TdkAbstractCanvasDraw::setActiveBuffer(const int& bufferId)
{
	int oldBufferId = _currentBufferId;
    _currentBufferId = bufferId;
	return oldBufferId;
}

int TdkAbstractCanvasDraw::getActiveBuffer()
{
	return _currentBufferId;
}

inline int TdkAbstractCanvasDraw::setPaintMode(const int& mode)
{
	int oldMode = _paintMode;
	_paintMode = mode;
	return oldMode;
}

inline int TdkAbstractCanvasDraw::getPaintMode() const
{
	return _paintMode;
}

void TdkAbstractCanvasDraw::drawPointW(const TePoint& pt)
{
    drawPointW(pt.location());
}

void TdkAbstractCanvasDraw::drawPointsW(TePointSet& points)
{
    TePointSet::iterator it;

    for(it = points.begin(); it != points.end(); ++it)
    {
        drawPointW((*it));
    }
}

void TdkAbstractCanvasDraw::drawLineW(const TeLine2D& line, const bool& showPoint)
{
	TeLine2D vline;
	_transformer.window2Viewport(line, vline);
	drawLine(vline, showPoint);
}

void TdkAbstractCanvasDraw::drawLinesW(TeLineSet& lines, const bool& showPoint)
{
    TeLineSet::iterator it;

    for(it = lines.begin(); it != lines.end(); ++it)
    {
        drawLineW((*it));
    }
}

void TdkAbstractCanvasDraw::drawPolygonW(const TePolygon& poly, const bool& showPoint)
{
    TePolygon p;
    _transformer.window2Viewport(poly, p);
    drawPolygon(p, showPoint);
}

void TdkAbstractCanvasDraw::drawPolygonsW(TePolygonSet& polys, const bool& showPoint)
{
    TePolygonSet::iterator it;

    for(it = polys.begin(); it != polys.end(); ++it)
    {
        drawPolygonW((*it));
    }
}

void TdkAbstractCanvasDraw::drawCellW(const TeCell& cell, const bool& showPoint)
{
    TeCell c = cell;
    TeBox vBox;
    _transformer.window2Viewport(c.box(), vBox);
    c.setBox(vBox);
    drawCell(c);
}

void TdkAbstractCanvasDraw::drawCellsW(TeCellSet& cells, const bool& showPoint)
{
}

void TdkAbstractCanvasDraw::drawTextW(const TeText& text)
{
	TeCoord2D	vcoord;
	TeText		vText;
	_transformer.window2Viewport(text.location(), vcoord);
	drawText(vcoord.x(),vcoord.y(),text.textValue());
}

void TdkAbstractCanvasDraw::drawTextW(const TeBox &box, const std::string &text)
{
	double	llx,lly;
	double	urx,ury;

	_transformer.window2Viewport(box.x1(),box.y1(),llx,lly);
	_transformer.window2Viewport(box.x2(),box.y2(),urx,ury);

	drawText(TeBox(llx,lly,urx,ury),text);
}



void TdkAbstractCanvasDraw::drawTextsW(TeTextSet& texts)
{
}

void TdkAbstractCanvasDraw::drawPointW(const TeCoord2D& coord)
{
	TeCoord2D vcoord;
	_transformer.window2Viewport(coord, vcoord);
	drawPoint(vcoord);
}

void TdkAbstractCanvasDraw::drawBoxW(TeBox& box, const bool& showPoint)
{
	double llx,lly;
	double urx,ury;
	
	_transformer.window2Viewport(box.x1(),box.y1(),llx,lly);
	_transformer.window2Viewport(box.x2(),box.y2(),urx,ury);
	this->drawRect(llx,lly,urx,ury);
}

void TdkAbstractCanvasDraw::drawPointW(const double& x, const double& y)
{
	TeCoord2D coord(x, y);
	TeCoord2D vcoord;
	_transformer.window2Viewport(coord, vcoord);
	drawPoint(vcoord.x_, vcoord.y_);
}

void TdkAbstractCanvasDraw::drawLineSegmentW(const double& x0, const double& y0,
			                    const double& x1, const double& y1)
{
	double	vX0, vY0;
	double	vX1, vY1;

	_transformer.window2Viewport(x0,y0,vX0,vY0);
	_transformer.window2Viewport(x1,y1,vX1,vY1);
	drawLineSegment(vX0,vY0,vX1,vY1);
}

void TdkAbstractCanvasDraw::drawLineSegmentW(const TeCoord2D& c1, const TeCoord2D& c2)
{
	drawLineSegmentW(c1.x_, c1.y_, c2.x_, c2.y_);
}

void TdkAbstractCanvasDraw::drawRectW(const double& llx, const double& lly,
			            const double& urx, const double& ury)
{
    double vx1,
           vx2,
           vy1,
           vy2;

    window2Viewport(llx, lly, vx1, vy1);
    window2Viewport(urx, ury, vx2, vy2);

    drawRect(vx1, vy1, vx2, vy2);
}

void TdkAbstractCanvasDraw::drawRectW(const TeBox& rect)
{
    drawRectW(rect.x1(), rect.y1(), rect.x2(), rect.y2());
}

void TdkAbstractCanvasDraw::fillRectW(const double& llx, const double& lly,
			            const double& urx, const double& ury)
{
    double vx1,
           vx2,
           vy1,
           vy2;

    window2Viewport(llx, lly, vx1, vy1);
    window2Viewport(urx, ury, vx2, vy2);

    fillRect(vx1, vy1, vx2, vy2);
}

void TdkAbstractCanvasDraw::fillRectW(const TeBox& rect)
{
    fillRectW(rect.x1(), rect.y1(), rect.x2(), rect.y2());
}

void TdkAbstractCanvasDraw::drawLineW(TdkPrimitiveCoord* line, const int& lineSize)
{
}

void TdkAbstractCanvasDraw::drawPolygonW(TdkPrimitiveCoord* poly, int* ringSize, const int& nRings)
{
}

void TdkAbstractCanvasDraw::drawEllipseW(const double& xc, const double& yc,
			                const double& rx, const double& ry, const double& angle)
{
    double vxc,
           vrx,
           vyc,
           vry;

    window2Viewport(xc, yc, vxc, vyc);
	window2Viewport(rx, vrx);
	window2Viewport(ry, vry);

	drawEllipse(vxc, vyc, vrx, vry, angle);
}

void TdkAbstractCanvasDraw::drawEllipseW(const double& xc, const double& yc,
			                const double& rx1, const double& ry1,
							const double& rx2, const double& ry2)
{
    double vxc, vrx1, vrx2,
           vyc, vry1, vry2;

    window2Viewport(xc, yc, vxc, vyc);
	window2Viewport(rx1, vrx1);
	window2Viewport(ry1, vry1);
	window2Viewport(rx2, vrx2);
	window2Viewport(ry2, vry2);

	drawEllipse(vxc, vyc, vrx1, vry1, vrx2, vry2);
}

void TdkAbstractCanvasDraw::fillEllipseW(const double& xc, const double& yc,
			                const double& rx, const double& ry, const double& angle)
{
	 double vxc,
           vrx,
           vyc,
           vry;

    window2Viewport(xc, yc, vxc, vyc);
	window2Viewport(rx, vrx);
	window2Viewport(ry, vry);

	fillEllipse(vxc, vyc, vrx, vry, angle);
}

void TdkAbstractCanvasDraw::fillEllipseW(const double& xc, const double& yc,
			                const double& rx1, const double& ry1,
							const double& rx2, const double& ry2)
{
}

void TdkAbstractCanvasDraw::drawArcW(const double& xc, const double& yc,
			            const double& w, const double& h,
						const double& startAngle, const double& finalAngle)
{
}

void TdkAbstractCanvasDraw::drawSectorW(const double& xc, const double& yc,
			                const double& w, const double& h,
							const double& startAngle, const double& finalAngle)
{
}

void TdkAbstractCanvasDraw::fillSectorW(const double& xc, const double& yc,
			                const double& w, const double& h,
							const double& startAngle, const double& finalAngle)
{
}

void TdkAbstractCanvasDraw::drawImageRGBW(const unsigned int& imgW, const unsigned int& imgH,
			                    unsigned char* red, unsigned char* green, unsigned char* blue,
								const double& dstX, const double& dstY,
								const unsigned int& dstW, const unsigned int& dstH, const double& angle)
{
	double dstXv, dstYv;
	double dstWv, dstHv;
	window2Viewport(dstX, dstY, dstXv, dstYv);
	window2Viewport(dstW, dstWv);
	window2Viewport(dstH, dstHv);
	drawImageRGB(imgW, imgH, red, green, blue, dstXv, dstYv, (int)dstWv, (int)dstHv, angle);
}


void TdkAbstractCanvasDraw::drawImageRGBW(const unsigned int& imgW, const unsigned int& imgH,
			                    unsigned char* red, unsigned char* green, unsigned char* blue,
								const double& dstX, const double& dstY,
								const unsigned int& dstW, const unsigned int& dstH,
								const double& srcX, const double& srcY,
								const unsigned int& srcW, const unsigned int& srcH, const double& angle)
{
	double dstXv, dstYv;
	double srcXv, srcYv;
	double dstWv, dstHv;
	double srcWv, srcHv;

	window2Viewport(dstX, dstY, dstXv, dstYv);
	window2Viewport(srcX, srcY, srcXv, srcYv);
	window2Viewport(dstW, dstWv);
	window2Viewport(dstH, dstHv);
	window2Viewport(srcW, srcWv);
	window2Viewport(srcH, srcHv);

	drawImageRGB(imgW, imgH, red, green, blue, dstXv, dstYv, (int)dstWv, (int)dstHv, srcXv, srcYv, (int)srcWv, (int)srcHv, angle);
}


void TdkAbstractCanvasDraw::drawTextW(const double& x, const double& y, const string& text)
{
	double vX;
	double vY;

	_transformer.window2Viewport(x,y,vX,vY);
	drawText(vX,vY,text);
}

void TdkAbstractCanvasDraw::drawPoint(const TePoint& pt)
{
	drawPoint(pt.location().x_, pt.location().y_);
}

void TdkAbstractCanvasDraw::drawPoints(TePointSet& points)
{
	TePointSet::iterator it;
	for(it = points.begin(); it != points.end(); ++it)
	{
		drawPoint((*it));
	}
}

void TdkAbstractCanvasDraw::drawLines(TeLineSet& lines, const bool& showPoint)
{
}

void TdkAbstractCanvasDraw::drawPolygons(TePolygonSet& polys, const bool& showPoint)
{
}

void TdkAbstractCanvasDraw::drawCells(TeCellSet& cells, const bool& showPoint)
{
}

void TdkAbstractCanvasDraw::drawText(const TeText& text)
{
}

void TdkAbstractCanvasDraw::drawTexts(TeTextSet& texts)
{
}

void TdkAbstractCanvasDraw::drawPoint(const TeCoord2D& coord)
{
	drawPoint(coord.x_, coord.y_);
}

void TdkAbstractCanvasDraw::drawBox(const TeBox& box, const bool& showPoint)
{
}

void TdkAbstractCanvasDraw::drawRect(const TeBox& rect)
{
    drawRect(rect.x1(), rect.y1(), rect.x2(), rect.y2());
}

void TdkAbstractCanvasDraw::fillRect(const TeBox& rect)
{
    fillRect(rect.x1(), rect.y1(), rect.x2(), rect.y2());
}

int TdkAbstractCanvasDraw::getCanvasId()
{
    return _canvasId;
}

void TdkAbstractCanvasDraw::setRasterDecoder(TeRaster* raster, TeRasterParams& params)
{
	TeDecoderMemory *dec = new TeDecoderMemory(params);
	raster->setDecoder(dec);
}