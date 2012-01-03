/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef QWT_PLOT_CURVE_H
#define QWT_PLOT_CURVE_H

#include <qpen.h>
#include <qstring.h>
#include "qwt_global.h"
#include "qwt_plot_item.h"
#include "qwt_text.h"
#include "qwt_data.h"

class QPainter;
class QwtScaleMap;
class QwtSymbol;

#if QT_VERSION < 0x040000
class QPointArray;
#else
class QPolygon;
#endif

/*!
  \brief A class which draws curves

  This class can be used to display data as a curve in the  x-y plane.
  It supports different display styles, spline interpolation and symbols.

  \par Usage
  <dl><dt>A. Assign curve properties</dt>
  <dd>When a curve is created, it is configured to draw black solid lines
  with QwtPlotCurve::Lines and no symbols. You can change this by calling 
  QwtPlotCurve::setPen(), QwtPlotCurve::setStyle() and QwtPlotCurve::setSymbol().</dd>
  <dt>B. Assign or change data.</dt>
  <dd>Data can be set in two ways:<ul>
  <li>QwtPlotCurve::setData() is overloaded to initialize the x and y data by
  copying from different data structures with different kind of copy semantics.
  <li>QwtPlotCurve::setRawData() only stores the pointers and size information
  and is provided for backwards compatibility.  This function is less safe (you
  must not delete the data while they are attached), but has been more
  efficient, and has been more convenient for dynamically changing data.
  Use of QwtPlotCurve::setData() in combination with a problem-specific subclass
  of QwtData is always preferrable.</ul></dd>
  <dt>C. Draw</dt>
  <dd>QwtPlotCurve::draw() maps the data into pixel coordinates and paints them.
  </dd></dl>

  \par Example:
  see examples/curvdemo

  \sa QwtData, QwtSymbol, QwtScaleMap
*/
class QWT_EXPORT QwtPlotCurve: public QwtPlotItem
{
public:
    /*! 
        Curve styles. 
        \sa QwtPlotCurve::setStyle
    */
    enum CurveStyle
    {
        NoCurve,
        Lines,
        Sticks,
        Steps,
        Dots,
        Spline,
        UserCurve = 100
    };

    /*! 
        Curve attributes. 
        \sa QwtPlotCurve::setCurveAttribute, QwtPlotCurve::testCurveAttribute
    */
    enum CurveAttribute
    {
        Auto = 0,
        Yfx = 1,
        Xfy = 2,
        Parametric = 4,
        Periodic = 8,
        Inverted = 16
    };

    /*! 
        Paint attributes 
        \sa QwtPlotCurve::setPaintAttribute, testPaintAttribute
    */
    enum PaintAttribute
    {
        PaintFiltered = 1,
        ClipPolygons = 2
    };

    explicit QwtPlotCurve();
    explicit QwtPlotCurve(const QwtText &title);
    explicit QwtPlotCurve(const QString &title);
    explicit QwtPlotCurve(const QwtPlotCurve &c);

    virtual ~QwtPlotCurve();

    const QwtPlotCurve& operator= (const QwtPlotCurve &c);

    virtual int rtti() const;

    void setPaintAttribute(PaintAttribute, bool on = true);
    bool testPaintAttribute(PaintAttribute) const;

    void setRawData(const double *x, const double *y, int size);
    void setData(const double *xData, const double *yData, int size);
    void setData(const QwtArray<double> &xData, const QwtArray<double> &yData);
    void setData(const QwtArray<QwtDoublePoint> &data);
    void setData(const QwtData &data);
    
    int closestPoint(const QPoint &pos, double *dist = NULL) const;

    QwtData &data();
    const QwtData &data() const;

    int dataSize() const;
    inline double x(int i) const;
    inline double y(int i) const;

    virtual QwtDoubleRect boundingRect() const;

    //! boundingRect().left()
    inline double minXValue() const { return boundingRect().left(); }
    //! boundingRect().right()
    inline double maxXValue() const { return boundingRect().right(); }
    //! boundingRect().top()
    inline double minYValue() const { return boundingRect().top(); }
    //! boundingRect().bottom()
    inline double maxYValue() const { return boundingRect().bottom(); }

    void setCurveAttribute(CurveAttribute, bool on = true);
    bool testCurveAttribute(CurveAttribute) const;

    void setTitle(const QString &title);
    void setTitle(const QwtText &title);
    const QwtText &title() const;

    void setPen(const QPen &);
    const QPen &pen() const;

    void setBrush(const QBrush &);
    const QBrush &brush() const;

    void setBaseline(double ref);
    double baseline() const;

    void setStyle(CurveStyle style);
    CurveStyle style() const;

    void setSymbol(const QwtSymbol &s);
    const QwtSymbol& symbol() const;

    void setSplineSize(int s);
    int splineSize() const;

    virtual void draw(QPainter *p, 
        const QwtScaleMap &xMap, const QwtScaleMap &yMap,
        const QRect &) const;

    virtual void draw(QPainter *p, 
        const QwtScaleMap &xMap, const QwtScaleMap &yMap,
        int from, int to) const;

    void draw(int from, int to) const;

    virtual void updateLegend(QwtLegend *) const;

protected:

    void init(const QwtText &title);
    void copy(const QwtPlotCurve &c);

    virtual void drawCurve(QPainter *p, int style,
        const QwtScaleMap &xMap, const QwtScaleMap &yMap,
        int from, int to) const;

    virtual void drawSymbols(QPainter *p, const QwtSymbol &,
        const QwtScaleMap &xMap, const QwtScaleMap &yMap,
        int from, int to) const;

    void drawLines(QPainter *p,
        const QwtScaleMap &xMap, const QwtScaleMap &yMap,
        int from, int to) const;
    void drawSticks(QPainter *p,
        const QwtScaleMap &xMap, const QwtScaleMap &yMap,
        int from, int to) const;
    void drawDots(QPainter *p,
        const QwtScaleMap &xMap, const QwtScaleMap &yMap,
        int from, int to) const;
    void drawSteps(QPainter *p,
        const QwtScaleMap &xMap, const QwtScaleMap &yMap,
        int from, int to) const;
    void drawSpline(QPainter *p,
        const QwtScaleMap &xMap, const QwtScaleMap &yMap) const;

#if QT_VERSION < 0x040000
    void fillCurve(QPainter *,
        const QwtScaleMap &, const QwtScaleMap &,
        QPointArray &) const;
    void closePolyline(const QwtScaleMap &, const QwtScaleMap &,
        QPointArray &) const;
#else
    void fillCurve(QPainter *,
        const QwtScaleMap &, const QwtScaleMap &,
        QPolygon &) const;
    void closePolyline(const QwtScaleMap &, const QwtScaleMap &,
        QPolygon &) const;
#endif

    int verifyRange(int &i1, int &i2) const;

private:
    QwtData *d_xy;

    class PrivateData;
    PrivateData *d_data;
};

//! \return the the curve data
inline QwtData &QwtPlotCurve::data()
{
    return *d_xy;
}

//! \return the the curve data
inline const QwtData &QwtPlotCurve::data() const
{
    return *d_xy;
}

/*!
    \param i index
    \return x-value at position i
*/
inline double QwtPlotCurve::x(int i) const 
{ 
    return d_xy->x(i); 
}

/*!
    \param i index
    \return y-value at position i
*/
inline double QwtPlotCurve::y(int i) const 
{ 
    return d_xy->y(i); 
}

#endif
