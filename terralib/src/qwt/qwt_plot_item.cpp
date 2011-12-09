/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "qwt_plot.h"
#include "qwt_legend.h"
#include "qwt_legend_item.h"
#include "qwt_plot_item.h"

class QwtPlotItem::PrivateData
{
public:
    PrivateData():
        plot(NULL),
        isVisible(true),
        attributes(0),
#if QT_VERSION >= 0x040000
        renderHints(0),
#endif
        z(0.0),
        xAxis(QwtPlot::xBottom),
        yAxis(QwtPlot::yLeft)
    {
    }

    mutable QwtPlot *plot;

    bool isVisible;
    int attributes;
#if QT_VERSION >= 0x040000
    int renderHints;
#endif
    double z;

    int xAxis;
    int yAxis;
};

//! Constructor
QwtPlotItem::QwtPlotItem()
{
    d_data = new PrivateData;
}

//! Destroy the QwtPlotItem
QwtPlotItem::~QwtPlotItem()
{
    attach(NULL);
    delete d_data;
}

/*! 
  Attach the item to a plot
*/
void QwtPlotItem::attach(QwtPlot *plot)
{
    if ( plot == d_data->plot )
        return;

    // remove the item from the previous plot

    if ( d_data->plot )
    {
        if ( d_data->plot->legend() )
        {
            QWidget *legendItem = d_data->plot->legend()->find(this);
            if ( legendItem )
                delete legendItem; 
        }

        d_data->plot->attachItem(this, false);

        if ( d_data->plot->autoReplot() )
            d_data->plot->update();
    }

    d_data->plot = plot;

    if ( d_data->plot )
    {
        // insert the item into the current plot

        d_data->plot->attachItem(this, true);
        itemChanged();
    }
}

int QwtPlotItem::rtti() const
{
    return Rtti_PlotItem;
}

//! Return attached plot
QwtPlot *QwtPlotItem::plot() const 
{ 
    return d_data->plot; 
}

double QwtPlotItem::z() const 
{ 
    return d_data->z; 
}

void QwtPlotItem::setZ(double z) 
{ 
    if ( d_data->z != z )
    {
        d_data->z = z; 
        itemChanged();
    }
}

void QwtPlotItem::setItemAttribute(ItemAttribute attribute, bool on)
{
    if ( bool(d_data->attributes & attribute) != on )
    {
        if ( on )
            d_data->attributes |= attribute;
        else
            d_data->attributes &= ~attribute;

        itemChanged();
    }
}

bool QwtPlotItem::testItemAttribute(ItemAttribute attribute) const
{
    return d_data->attributes & attribute;
}

#if QT_VERSION >= 0x040000

void QwtPlotItem::setRenderHint(RenderHint hint, bool on)
{
    if ( (d_data->renderHints & hint) != on )
    {
        if ( on )
            d_data->renderHints |= hint;
        else
            d_data->renderHints &= ~hint;

        itemChanged();
    }
}

bool QwtPlotItem::testRenderHint(RenderHint hint) const
{
    return (d_data->renderHints & hint);
}

#endif

void QwtPlotItem::show()
{
    setVisible(true);
}

void QwtPlotItem::hide()
{
    setVisible(false);
}

/*! 
    \sa QwtPlotItem::setVisible
*/
void QwtPlotItem::setVisible(bool on) 
{ 
    if ( on != d_data->isVisible )
    {
        d_data->isVisible = on; 
        itemChanged(); 
    }
}

/*! 
    \return true if enabled
    \sa QwtPlotItem::setEnabled
*/
bool QwtPlotItem::isVisible() const
{ 
    return d_data->isVisible; 
}

//! Call QwtPlot::autoRefresh for the parent plot
void QwtPlotItem::itemChanged()
{
    if ( d_data->plot )
    {
        if ( d_data->plot->legend() )
            updateLegend(d_data->plot->legend());

        d_data->plot->autoRefresh();
    }
}

//!  Set x and y axis
void QwtPlotItem::setAxis(int xAxis, int yAxis)
{
    if (xAxis == QwtPlot::xBottom || xAxis == QwtPlot::xTop )
       d_data->xAxis = xAxis;

    if (yAxis == QwtPlot::yLeft || yAxis == QwtPlot::yRight )
       d_data->yAxis = yAxis;

    itemChanged();    
}

//!  Set y axis
void QwtPlotItem::setXAxis(int axis)
{
    if (axis == QwtPlot::xBottom || axis == QwtPlot::xTop )
    {
       d_data->xAxis = axis;
       itemChanged();    
    }
}

//!  Set y axis
void QwtPlotItem::setYAxis(int axis)
{
    if (axis == QwtPlot::yLeft || axis == QwtPlot::yRight )
    {
       d_data->yAxis = axis;
       itemChanged();   
    }
}

//! Return xAxis
int QwtPlotItem::xAxis() const 
{ 
    return d_data->xAxis; 
}

//! Return yAxis
int QwtPlotItem::yAxis() const 
{ 
    return d_data->yAxis; 
}

QwtDoubleRect QwtPlotItem::boundingRect() const
{
    return QwtDoubleRect(1.0, 1.0, -2.0, -2.0); // invalid
}

QWidget *QwtPlotItem::legendItem() const
{
    return new QwtLegendItem;
}

void QwtPlotItem::updateLegend(QwtLegend *legend) const
{
    if ( !legend )
        return;

    QWidget *lgdItem = legend->find(this);
    if ( testItemAttribute(QwtPlotItem::Legend) )
    {
        if ( lgdItem == NULL )
        {
            lgdItem = legendItem();
            if ( lgdItem )
            {
                if ( lgdItem->inherits("QwtLegendItem") )
                {
                    QwtLegendItem *label = (QwtLegendItem *)lgdItem;
                    label->setItemMode(legend->itemMode());

                    if ( d_data->plot )
                    {
                        QObject::connect(label, SIGNAL(clicked()), 
                            d_data->plot, SLOT(legendItemClicked()));
                        QObject::connect(label, SIGNAL(checked(bool)), 
                            d_data->plot, SLOT(legendItemChecked(bool)));
                    }
                }
                legend->insert(this, lgdItem);
            }
        }
    }
    else
    {
        delete lgdItem;
    }
}

void QwtPlotItem::updateScaleDiv(const QwtScaleDiv &,
    const QwtScaleDiv &) 
{ 
}

