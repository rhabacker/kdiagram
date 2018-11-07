/*
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KD Chart library.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KCHARTABSTRACTAXIS_H
#define KCHARTABSTRACTAXIS_H

// #include <QObject>
// #include <QRectF>
// #include <QWidget>

#include "kchart_export.h"
#include "KChartGlobal.h"
#include "KChartAbstractArea.h"
#include "KChartTextAttributes.h"
#include "KChartRulerAttributes.h"

QT_BEGIN_NAMESPACE
class QPainter;
class QSizeF;
QT_END_NAMESPACE


namespace KChart {

    class Area;
    class AbstractCoordinatePlane;
    class PaintContext;
    class AbstractDiagram;

    /**
      * The base class for axes.
      *
      * For being useful, axes need to be assigned to a diagram, see
      * AbstractCartesianDiagram::addAxis and AbstractCartesianDiagram::takeAxis.
      *
      * \sa PolarAxis, AbstractCartesianDiagram
      */
    class KCHART_EXPORT AbstractAxis : public AbstractArea
    {
        Q_OBJECT

        Q_DISABLE_COPY( AbstractAxis )
        KCHART_DECLARE_PRIVATE_DERIVED_PARENT( AbstractAxis, AbstractDiagram* )

    public:
        explicit AbstractAxis( AbstractDiagram* diagram = nullptr );
        virtual ~AbstractAxis();

        // FIXME implement when code os ready for it:
        // virtual Area* clone() const = 0;

        // FIXME (Mirko) readd when needed
        // void copyRelevantDetailsFrom( const KChartAxis* axis );

        /*    virtual void paint( PaintContext* ) const = 0;
              virtual QSize sizeHint() const = 0;*/
	//virtual void paintEvent( QPaintEvent* event) = 0;

        /**
         * \brief Reimplement this method if you want to adjust axis labels
         * before they are printed.
         *
         * KChart is calling this method immediately before drawing the
         * text, this  means: What you return here will be drawn without
         * further modifications.
         *
         * \param label The text of the label as KChart has calculated it
         * automatically (or as it was taken from a QStringList provided
         * by you, resp.)
         *
         * \note If you reimplement this method in a subclass of KChart::CartesianAxis,
         * and your reimplementation's return value depends on data other than @p label
         * (so KChart will not know when it changes), you must manually ensure that
         * layouts are adapted to any changed sizes of the axis labels. To do that,
         * call KChart::CartesianAxis::layoutPlanes() from your reimplementation when
         * you know that the external data changed and it will change label sizes -
         * or when you cannot exclude that.
         *
         * \return The text to be drawn. By default this is the same as \c label.
         */
        virtual const QString customizedLabel( const QString& label ) const;

        /**
         * Returns true if both axes have the same settings.
         */
        bool compare( const AbstractAxis* other ) const;

        /**
          * \internal
          *
          * Method invoked by AbstractCartesianDiagram::addAxis().
          *
          * You should not call this function, unless you know exactly,
          * what you are doing.
          *
          * \sa connectSignals(), AbstractCartesianDiagram::addAxis()
          */
        void createObserver( AbstractDiagram* diagram );

        /**
          * \internal
          *
          * Method invoked by AbstractCartesianDiagram::takeAxis().
          *
          * You should not call this function, unless you know exactly,
          * what you are doing.
          *
          * \sa AbstractCartesianDiagram::takeAxis()
          */
        void deleteObserver( AbstractDiagram* diagram );
        const AbstractDiagram* diagram() const;
        bool observedBy( AbstractDiagram* diagram ) const;

        /**
          * Wireing the signal/slot connections.
          *
          * This method gets called automatically, each time, when you assign
          * the axis to a diagram, either by passing a diagram* to the c'tor,
          * or by calling the diagram's setAxis method, resp.
          *
          * If overwriting this method in derived classes, make sure to call
          * this base method AbstractAxis::connectSignals(), so your axis
          * gets connected to the diagram's built-in signals.
          *
          * \sa AbstractCartesianDiagram::addAxis()
          */
        virtual void connectSignals();

        /**
          \brief Use this to specify the text attributes to be used for axis labels.

          By default, the reference area will be set at painting time.
          It will be the then-valid coordinate plane's parent widget,
          so normally, it will be the KChart::Chart.
          Thus the labels of all of your axes in all of your diagrams
          within that Chart will be drawn in same font size, by default.

          \sa textAttributes, setLabels
        */
        void setTextAttributes( const TextAttributes &a );

        /**
          \brief Returns the text attributes to be used for axis labels.

          \sa setTextAttributes
        */
        TextAttributes textAttributes() const;

        /**
          \brief Use this to specify the attributes used to paint the axis ruler

          Every axis has a default set of ruler attributes that is exactly the
          same among them. Use this method to specify your own attributes.

          \sa rulerAttributes
        */
        void setRulerAttributes( const RulerAttributes &a );

        /**
          \brief Returns the attributes to be used for painting the rulers

          \sa setRulerAttributes
        */
        RulerAttributes rulerAttributes() const;

        /**
          \brief Use this to specify your own set of strings, to be used as axis labels.

          Labels specified via setLabels take precedence:
          If a non-empty list is passed, KChart will use these strings as axis labels,
          instead of calculating them.

          If you pass a smaller number of strings than the number of labels drawn at this
          axis, KChart will repeat the strings until all labels are drawn.
          As an example you could specify the seven days of the week as abscissa labels,
          which would be repeatedly used then.

          By passing an empty QStringList you can reset the default behaviour.

          \sa labels, setShortLabels
        */
        void setLabels( const QStringList& list );

        /**
          Returns a list of strings, that are used as axis labels, as set via setLabels.

          \sa setLabels
        */
        QStringList labels() const;

        /**
          \brief Use this to specify your own set of strings, to be used as axis labels,
          in case the normal labels are too long.

          \note Setting done via setShortLabels will be ignored, if you did not pass
          a non-empty string list via setLabels too!

          By passing an empty QStringList you can reset the default behaviour.

          \sa shortLabels, setLabels
        */
        void setShortLabels( const QStringList& list );

        /**
          Returns a list of strings, that are used as axis labels, as set via setShortLabels.

          \note Setting done via setShortLabels will be ignored, if you did not pass
          a non-empty string list via setLabels too!

          \sa setShortLabels
        */
        QStringList shortLabels() const;

        void setGeometry( const QRect& rect ) Q_DECL_OVERRIDE = 0;
        QRect geometry() const Q_DECL_OVERRIDE = 0;

        /**
            \brief Convenience function, returns the coordinate plane, in which this axis is used.

            If the axis is not used in a coordinate plane, the return value is Zero.
         */
        const AbstractCoordinatePlane* coordinatePlane() const;

    protected Q_SLOTS:
        /** called for initializing after the c'tor has completed */
        virtual void delayedInit();

    public Q_SLOTS:
        void update();

    Q_SIGNALS:
        void coordinateSystemChanged();
    };
}

#endif // KCHARTABSTRACTAXIS_H
