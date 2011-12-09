/**
* Tecgraf - GIS development team
* 
* Tdk Framework
* 
* @(#) TdkCoordTransformer.cpp
**/

/*
** ---------------------------------------------------------------
** Includes:
*/

#include "TdkCoordTransformer.h"

/*
** ---------------------------------------------------------------
** Definitions:
*/

/*
** ---------------------------------------------------------------
** Methods Implementation:
*/

TdkCoordTransformer::TdkCoordTransformer(const TdkTransformationType& transformationType) :
sX_(1.0),
sY_(1.0),
s_(0.),
tX_(0.),
tY_(0.),
llxW_(0.),
llyW_(0.),
urxW_(0.),
uryW_(0.),
widthW_(0.),
heightW_(0.),
llxV_(0.),
llyV_(0.),
urxV_(0.),
uryV_(0.),
widthV_(0.),
heightV_(0.),
transformationType_(transformationType)
{}

void TdkCoordTransformer::setWindow(const double& llx, const double& lly,
                                    const double& urx, const double& ury)
{
    llxW_ = llx;
    llyW_ = lly;
    urxW_ = urx;
    uryW_ = ury;

    updateTransformation();
}

void TdkCoordTransformer::setWindow(const TeBox& box)
{
    setWindow(box.x1_, box.y1_, box.x2_, box.y2_);
}

void TdkCoordTransformer::getWindow(double& llx, double& lly,
                                    double& urx, double& ury)
{
    llx = llxW_;
    lly = llyW_;
    urx = urxW_;
    ury = uryW_;
}

void TdkCoordTransformer::setViewport(const double& llx, const double& lly,
                                      const double& urx, const double& ury)
{
    llxV_ = llx;
    llyV_ = lly;
    urxV_ = urx;
    uryV_ = ury;

    updateTransformation();
}

void TdkCoordTransformer::setViewport(const TeBox& box)
{
    setViewport(box.x1_, box.y1_, box.x2_, box.y2_);
}

void TdkCoordTransformer::getViewport(double& llx, double& lly,
                                      double& urx, double& ury)
{
    llx = llxV_;
    lly = llyV_;
    urx = urxV_;
    ury = uryV_;
}

void TdkCoordTransformer::window2Viewport(const double& wx, const double& wy,
                                          double& vx, double& vy)
{
    vx = sX_ * wx + tX_;
    vy = sY_ * wy + tY_;
}

void TdkCoordTransformer::window2Viewport(const TeCoord2D& wc, TeCoord2D& vc)
{
    vc.x_ = sX_ * wc.x_ + tX_;
    vc.y_ = sY_ * wc.y_ + tY_;
}

void TdkCoordTransformer::window2Viewport(const TdkPrimitiveCoord& wc,
                                          TdkPrimitiveCoord& vc)
{
    vc.x_ = sX_ * wc.x_ + tX_;
    vc.y_ = sY_ * wc.y_ + tY_;
}

void TdkCoordTransformer::window2Viewport(const TeBox& wbox, TeBox& vbox)
{
    window2Viewport(wbox.x1_, wbox.y1_, vbox.x1_, vbox.y1_);
    window2Viewport(wbox.x2_, wbox.y2_, vbox.x2_, vbox.y2_);
}

void TdkCoordTransformer::window2Viewport(const double& w, double& v,
                                          const bool& xdirection)
{
    if (xdirection)
        v = sX_ * w;
    else
        v = sY_ * w;
}

void TdkCoordTransformer::window2Viewport(const TeLine2D& lineIn,
                                          TeLine2D& lineOut)
{
    lineOut.clear();

    unsigned int lineInSize = lineIn.size();

    lineOut.reserve(lineInSize);

    TeCoord2D c(0.0, 0.0);

    for (unsigned int i = 0; i < lineInSize; ++i)
    {
        window2Viewport(lineIn[i].x_, lineIn[i].y_, c.x_, c.y_);
        lineOut.add(c);
    }
}

void TdkCoordTransformer::window2Viewport(const TePolygon& polyIn,
                                          TePolygon& polyOut)
{
    polyOut.clear();

    unsigned int polyInSize = polyIn.size();

    polyOut.reserve(polyInSize);

    for (unsigned int i = 0; i < polyInSize; ++i)
    {
        TeLine2D lout;
        window2Viewport(polyIn[i], lout);
        TeLinearRing r(lout);
        polyOut.add(r);
    }
}

void TdkCoordTransformer::window2Viewport(TdkPrimitiveCoord* inputCoords,
                                          TdkPrimitiveCoord* outputCoords, const int& numCoords)
{
    for (int i = 0; i < numCoords; ++i)
        window2Viewport(inputCoords[i], outputCoords[i]);
}

void TdkCoordTransformer::viewport2Window(const double& vx, const double& vy,
                                          double& wx, double& wy)
{
    wx = ((vx - tX_) / sX_);
    wy = ((vy - tY_) / sY_);
}

void TdkCoordTransformer::viewport2Window(const TdkPrimitiveCoord& vc,
                                          TdkPrimitiveCoord& wc)
{
    wc.x_ = ((vc.x_ - tX_) / sX_);
    wc.y_ = ((vc.y_ - tY_) / sY_);
}

void TdkCoordTransformer::viewport2Window(const double& v, double& w,
                                          const bool& xdirection)
{
    if (xdirection)
        w = v / sX_;
    else
        w = v / sY_;
}

void TdkCoordTransformer::viewport2Window(const TeLine2D& lineIn,
                                          TeLine2D& lineOut)
{
    lineOut.clear();

    unsigned int lineInSize = lineIn.size();

    lineOut.reserve(lineInSize);

    TeCoord2D c(0.0, 0.0);

    for (unsigned int i = 0; i < lineInSize; ++i)
    {
        viewport2Window(lineIn[i].x_, lineIn[i].y_, c.x_, c.y_);
        lineOut.add(c);
    }
}

void TdkCoordTransformer::viewport2Window(const TePolygon& polyIn,
                                          TePolygon& polyOut)
{
    polyOut.clear();

    unsigned int polyInSize = polyIn.size();

    polyOut.reserve(polyInSize);

    for (unsigned int i = 0; i < polyInSize; ++i)
    {
        TeLine2D lout;
        viewport2Window(polyIn[i], lout);
        TeLinearRing r(lout);
        polyOut.add(r);
    }
}

void TdkCoordTransformer::viewport2Window(TdkPrimitiveCoord* inputCoords,
                                          TdkPrimitiveCoord* outputCoords, const int& numCoords)
{
    for (int i = 0; i < numCoords; ++i)
        viewport2Window(inputCoords[i], outputCoords[i]);
}

const TdkCoordTransformer::TdkTransformationType& TdkCoordTransformer::getTransformationType() const
{
    return transformationType_;
}

void TdkCoordTransformer::setTransformationType(const TdkTransformationType& transformationType)
{
    transformationType_ = transformationType;
    updateTransformation();
}

TeBox TdkCoordTransformer::adjustWindowBox(const TeBox &boxW, const TeBox &boxV)
{

	TeBox	boxOut;
	boxOut=boxW;
    adjustWindowBox(boxOut.x1_, boxOut.y1_, boxOut.x2_, boxOut.y2_,
			boxV.x1(),boxV.y1(), boxV.x2(), boxV.y2(), TdkCoordTransformer::TdkDiscrete, true);
	return boxOut;

}

void TdkCoordTransformer::adjustWindowBox(double& llxW, double& llyW,
                                          double& urxW, double& uryW,
                                          const double& llxV, const double& llyV,
                                          const double& urxV, const double& uryV,
                                          const TdkTransformationType& transformationType,
                                          const bool& centralized)
{
    double worldDX = urxW - llxW;
    double worldDY = uryW - llyW;

    double vpDX = urxV - llxV;
    double vpDY = uryV - llyV;

    if (transformationType == TdkDiscrete)
    {
        vpDX += 1.0;
        vpDY += 1.0;
    }

    double fx = vpDX  / worldDX;
    double fy = vpDY / worldDY;

    // a funcao de transformacao escolhera para a proporcao do eixo que provoca a maior degradacao
    // da imagem: ou seja, a que a relacao (cumprimento_imagem / cumprimento_mundo) for menor
    if (fx > fy)
    {
        // o eixo x e redimensionado (aumentado o seu cumprimento)
        double dxw = vpDX / fy;

        if (centralized)
        {
            double dyw = vpDY / fy;

            double xc = (urxW + llxW) / 2.0;
            double yc = (uryW + llyW) / 2.0;

            llxW = xc - (dxw / 2.0);
            urxW = xc + (dxw / 2.0);

            llyW = yc - (dyw / 2.0);
            uryW = yc + (dyw / 2.0);
        }
        else
        {
            urxW = llxW + dxw;
        }
    }
    else
    {
        double dyw = vpDY / fx;

        if (centralized)
        {
            double dxw = vpDX / fx;

            double xc = (urxW + llxW) / 2.0;
            double yc = (uryW + llyW) / 2.0;

            llxW = xc - (dxw / 2.0);
            urxW = xc + (dxw / 2.0);

            llyW = yc - (dyw / 2.0);
            uryW = yc + (dyw / 2.0);
        }
        else
        {
            uryW = llyW + dyw;
        }
    }
}

void TdkCoordTransformer::updateTransformation()
{
    widthW_  = urxW_ - llxW_;
    heightW_ = uryW_ - llyW_;

    widthV_  = urxV_ - llxV_;
    heightV_ = uryV_ - llyV_;

    if (transformationType_ == TdkDiscrete)
    {
        widthV_ += 1.0;
        heightV_ += 1.0;
    }

    if (widthW_ != 0.0)
        sX_ = widthV_  / widthW_;

    if (heightW_ != 0.0)
        sY_ = heightV_ / heightW_;

    tX_ = llxV_ - llxW_ * sX_;
    tY_ = llyV_ - llyW_ * sY_;

    s_ = sqrt(sX_ * sX_ + sY_ * sY_);
}

/*
** ---------------------------------------------------------------
** End:
*/
