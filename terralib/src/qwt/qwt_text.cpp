/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2003   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

// vim: expandtab

#include <qfont.h>
#include <qcolor.h>
#include <qpen.h>
#include <qbrush.h>
#include <qpainter.h>
#include "qwt_painter.h"
#include "qwt_text_engine.h"
#include "qwt_text.h"
#if QT_VERSION >= 0x040000
#include <qapplication.h>
#include <qdesktopwidget.h>
#endif
class QwtText::PrivateData
{
public:
    PrivateData():
        flags(Qt::AlignCenter),
        backgroundPen(Qt::NoPen),
        backgroundBrush(Qt::NoBrush),
        paintAttributes(QwtText::PaintUsingPainter),
        layoutAttributes(QwtText::DefaultLayout),
        textEngine(NULL)
    {
    }

    int flags;
    QString text;
    QFont font;
    QColor color;
    QPen backgroundPen;
    QBrush backgroundBrush;

    int paintAttributes;
    int layoutAttributes;

    QwtTextEngine *textEngine;
};

class QwtText::LayoutCache
{
public:
    void invalidate()
    {
        textSize = QSize();
    }

    QFont font;
    QSize textSize;
};

QwtText::QwtText(const QString &text, QwtText::TextFormat textFormat)
{
    d_data = new PrivateData;
    d_data->text = text;
    d_data->textEngine = textEngine(text, textFormat);

    d_layoutCache = new LayoutCache;
}

QwtText::QwtText(const QwtText &other)
{
    d_data = new PrivateData;
    *d_data = *other.d_data;

    d_layoutCache = new LayoutCache;
    *d_layoutCache = *other.d_layoutCache;
}

//! Destructor
QwtText::~QwtText() 
{
    delete d_data;
    delete d_layoutCache;
}

QwtText &QwtText::operator=(const QwtText &other)
{
    *d_data = *other.d_data;
    *d_layoutCache = *other.d_layoutCache;
    return *this;
}
    
int QwtText::operator==(const QwtText &other) const
{
    return d_data->flags == other.d_data->flags &&
        d_data->text == other.d_data->text &&
        d_data->font == other.d_data->font &&
        d_data->color == other.d_data->color &&
        d_data->backgroundPen == other.d_data->backgroundPen &&
        d_data->backgroundBrush == other.d_data->backgroundBrush &&
        d_data->paintAttributes == other.d_data->paintAttributes &&
        d_data->textEngine == other.d_data->textEngine;
}

int QwtText::operator!=(const QwtText &other) const // invalidate
{
   return !(other == *this);
}

void QwtText::setText(const QString &text, 
    QwtText::TextFormat textFormat) 
{ 
    d_data->text = text; 
    d_data->textEngine = textEngine(text, textFormat);
    d_layoutCache->invalidate();
}

//! Return the text.
QString QwtText::text() const 
{ 
    return d_data->text; 
}

void QwtText::setFlags(int flags) 
{ 
    if ( flags != d_data->flags )
    {
        d_data->flags = flags; 
#if 1
        d_layoutCache->invalidate();
#endif
    }
}

int QwtText::flags() const 
{ 
    return d_data->flags; 
}

//! Set the font.
void QwtText::setFont(const QFont &font) 
{
    d_data->font = font; 
    d_data->paintAttributes |= PaintUsingTextFont;
}

//! Return the font.
QFont QwtText::font() const 
{ 
    return d_data->font; 
}

QFont QwtText::usedFont(const QFont &font) const
{
    if ( d_data->paintAttributes & PaintUsingTextFont )
        return d_data->font;

    return font;
}

void QwtText::setColor(const QColor &color) 
{ 
    d_data->paintAttributes |= PaintUsingTextColor;
    d_data->color = color; 
}

QColor QwtText::color() const 
{ 
    return d_data->color; 
}

QColor QwtText::usedColor(const QColor &color) const
{
    if ( d_data->paintAttributes & PaintUsingTextColor )
        return d_data->color;

    return color;
}

void QwtText::setBackgroundPen(const QPen &pen) 
{ 
    d_data->paintAttributes |= PaintBackground;
    d_data->backgroundPen = pen; 
}

QPen QwtText::backgroundPen() const 
{ 
    return d_data->backgroundPen; 
}

void QwtText::setBackgroundBrush(const QBrush &brush) 
{ 
    d_data->paintAttributes |= PaintBackground;
    d_data->backgroundBrush = brush; 
}

QBrush QwtText::backgroundBrush() const 
{ 
    return d_data->backgroundBrush; 
}

void QwtText::setPaintAttributes(int attributes)
{
    d_data->paintAttributes = attributes;
}

int QwtText::paintAttributes() const
{
    return d_data->paintAttributes;
}

void QwtText::setLayoutAttributes(int attributes)
{
    d_data->layoutAttributes = attributes;
}

int QwtText::layoutAttributes() const
{
    return d_data->layoutAttributes;
}

int QwtText::heightForWidth(int width, const QFont &font) const
{
    const QwtMetricsMap map = QwtPainter::metricsMap();
    width = map.layoutToScreenX(width);

#if QT_VERSION < 0x040000
    const QFont fnt = usedFont(font);
#else
    // We want to calculate in screen metrics. So
    // we need a font that uses screen metrics

    const QFont fnt(usedFont(font), QApplication::desktop());
#endif

    int h = 0;

    if ( d_data->layoutAttributes & MinimumLayout )
    {
        int left, right, top, bottom;
        d_data->textEngine->textMargins(fnt, d_data->text,
            left, right, top, bottom);

        h = d_data->textEngine->heightForWidth(
            fnt, d_data->flags, d_data->text, 
            width + left + right);

        h -= top + bottom;
    }
    else
    {
        h = d_data->textEngine->heightForWidth(
            fnt, d_data->flags, d_data->text, width);
    }

    h = map.screenToLayoutY(h);
    return h;
}

QSize QwtText::textSize(const QFont &font) const
{
#if QT_VERSION < 0x040000
    const QFont fnt(usedFont(font));
#else
    // We want to calculate in screen metrics. So
    // we need a font that uses screen metrics

    const QFont fnt(usedFont(font), QApplication::desktop());
#endif

    if ( !d_layoutCache->textSize.isValid() 
        || d_layoutCache->font != fnt )
    {
        d_layoutCache->textSize = d_data->textEngine->textSize(
            fnt, d_data->flags, d_data->text);
        d_layoutCache->font = fnt;
    }

    QSize sz = d_layoutCache->textSize;

    if ( d_data->layoutAttributes & MinimumLayout )
    {
        int left, right, top, bottom;
        d_data->textEngine->textMargins(fnt, d_data->text,
            left, right, top, bottom);
        sz -= QSize(left + right, top + bottom);
    }

    const QwtMetricsMap map = QwtPainter::metricsMap();
    sz = map.screenToLayout(sz);
    return sz;
}

void QwtText::draw(QPainter *painter, const QRect &rect) const
{
    if ( d_data->paintAttributes & PaintBackground )
    {
        if ( d_data->backgroundPen != Qt::NoPen || 
            d_data->backgroundBrush != Qt::NoBrush )
        {
            painter->save();
            painter->setPen(d_data->backgroundPen);
            painter->setBrush(d_data->backgroundBrush);
            QwtPainter::drawRect(painter, rect);
            painter->restore();
        }
    }

    painter->save();

    if ( d_data->paintAttributes & PaintUsingTextFont )
    {
        painter->setFont(d_data->font);
    }

    if ( d_data->paintAttributes & PaintUsingTextColor )
    {
        if ( d_data->color.isValid() )
            painter->setPen(d_data->color);
    }

    QRect expandedRect = rect;
    if ( d_data->layoutAttributes & MinimumLayout )
    {
#if QT_VERSION < 0x040000
        const QFont fnt(painter->font());
#else
        // We want to calculate in screen metrics. So
        // we need a font that uses screen metrics

        const QFont fnt(painter->font(), QApplication::desktop());
#endif

        int left, right, top, bottom;
        d_data->textEngine->textMargins(
            fnt, d_data->text,
            left, right, top, bottom);

        const QwtMetricsMap map = QwtPainter::metricsMap();
        left = map.screenToLayoutX(left);
        right = map.screenToLayoutX(right);
        top = map.screenToLayoutY(top);
        bottom = map.screenToLayoutY(bottom);

        expandedRect.setTop(rect.top() - top);
        expandedRect.setBottom(rect.bottom() + bottom);
        expandedRect.setLeft(rect.left() - left);
        expandedRect.setRight(rect.right() + right);
    }

    d_data->textEngine->draw(painter, expandedRect, 
        d_data->flags, d_data->text);

    painter->restore();
}

QwtTextEngine *QwtText::textEngine(const QString &text,
    QwtText::TextFormat format) const
{
#ifndef QT_NO_RICHTEXT
    static QwtRichTextEngine richTextEngine;
#endif
    static QwtPlainTextEngine plainTextEngine;

    switch(format)
    {
        case QwtText::AutoText:
        {
#ifndef QT_NO_RICHTEXT
            if ( richTextEngine.mightRender(text) )
                return &richTextEngine;
#endif
            break;
        }
        case QwtText::RichText:
        {
#ifndef QT_NO_RICHTEXT
            return &richTextEngine;
#endif
            break;
        }
        case QwtText::PlainText:
        default:
            return &plainTextEngine;
    }

    return &plainTextEngine;
}
