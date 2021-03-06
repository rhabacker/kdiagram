/*
 * Copyright (C) 2001-2015 Klaralvdalens Datakonsult AB.  All rights reserved.
 *
 * This file is part of the KGantt library.
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

#ifndef KGANTTDATETIMEGRID_H
#define KGANTTDATETIMEGRID_H

#include "kganttabstractgrid.h"

#include <QDateTime>
#include <QSet>
#include <QPair>

namespace KGantt {

    class DateTimeScaleFormatter;
    class DateTimeTimeLine;

    class KGANTT_EXPORT DateTimeGrid : public AbstractGrid
    {
        Q_OBJECT
        KGANTT_DECLARE_PRIVATE_DERIVED( DateTimeGrid )
    public:
        enum Scale {
            ScaleAuto, 
            ScaleHour,
            ScaleDay,
            ScaleWeek,
            ScaleMonth,
            ScaleUserDefined
        };
	
        DateTimeGrid();
        virtual ~DateTimeGrid();

        QDateTime startDateTime() const;
        void setStartDateTime( const QDateTime& dt );

        qreal dayWidth() const;
        void setDayWidth( qreal );

        qreal mapFromDateTime( const QDateTime& dt) const;
        QDateTime mapToDateTime( qreal x ) const;

        void setWeekStart( Qt::DayOfWeek );
        Qt::DayOfWeek weekStart() const;

        void setFreeDays( const QSet<Qt::DayOfWeek>& fd );
        QSet<Qt::DayOfWeek> freeDays() const;

        void setFreeDaysBrush(const QBrush brush);
        QBrush freeDaysBrush() const;

        void setScale( Scale s );
        Scale scale() const;

        void setUserDefinedLowerScale( DateTimeScaleFormatter* lower );
        void setUserDefinedUpperScale( DateTimeScaleFormatter* upper );
        DateTimeScaleFormatter* userDefinedLowerScale() const;
        DateTimeScaleFormatter* userDefinedUpperScale() const;

        bool rowSeparators() const;
        void setRowSeparators( bool enable );

        void setNoInformationBrush( const QBrush& brush );
        QBrush noInformationBrush() const;

        /*reimp*/ Span mapToChart( const QModelIndex& idx ) const Q_DECL_OVERRIDE;
        /*reimp*/ bool mapFromChart( const Span& span, const QModelIndex& idx,
                                     const QList<Constraint>& constraints=QList<Constraint>() ) const Q_DECL_OVERRIDE;
        /*reimp*/ qreal mapToChart( const QVariant& value ) const Q_DECL_OVERRIDE;
        /*reimp*/ QVariant mapFromChart( qreal x ) const Q_DECL_OVERRIDE;
        /*reimp*/ void paintGrid( QPainter* painter, 
                                  const QRectF& sceneRect, const QRectF& exposedRect,
                                  AbstractRowController* rowController = nullptr,
                                  QWidget* widget = nullptr ) Q_DECL_OVERRIDE;
        /*reimp*/ void paintHeader( QPainter* painter, 
                                    const QRectF& headerRect, const QRectF& exposedRect,
                                    qreal offset, QWidget* widget = nullptr ) Q_DECL_OVERRIDE;

        DateTimeTimeLine *timeLine() const;

    protected:
        virtual void paintHourScaleHeader( QPainter* painter, 
                           const QRectF& headerRect, const QRectF& exposedRect,
                           qreal offset, QWidget* widget = nullptr );
        virtual void paintDayScaleHeader( QPainter* painter, 
                          const QRectF& headerRect, const QRectF& exposedRect,
                          qreal offset, QWidget* widget = nullptr );
        virtual void paintWeekScaleHeader( QPainter* painter,
                                           const QRectF& headerRect, const QRectF& exposedRect,
                                           qreal offset, QWidget* widget = nullptr );
        virtual void paintMonthScaleHeader( QPainter* painter,
                                            const QRectF& headerRect, const QRectF& exposedRect,
                                            qreal offset, QWidget* widget = nullptr );

        virtual void paintUserDefinedHeader( QPainter* painter, 
                                     const QRectF& headerRect, const QRectF& exposedRect, 
                                     qreal offset, const DateTimeScaleFormatter* formatter, 
                                     QWidget* widget = nullptr );

        virtual void drawDayBackground(QPainter* painter, const QRectF& rect, const QDate& date);
        virtual void drawDayForeground(QPainter* painter, const QRectF& rect, const QDate& date);
        
        QRectF computeRect(const QDateTime& from, const QDateTime& to, const QRectF& rect) const;
        QPair<QDateTime, QDateTime> dateTimeRange(const QRectF& rect) const;

        /* reimp */ void drawBackground(QPainter* paint, const QRectF& rect) Q_DECL_OVERRIDE;
        /* reimp */ void drawForeground(QPainter* paint, const QRectF& rect) Q_DECL_OVERRIDE;
    };

    class KGANTT_EXPORT DateTimeScaleFormatter
    {
        KGANTT_DECLARE_PRIVATE_BASE_POLYMORPHIC( DateTimeScaleFormatter )
    public:
        enum Range {
            Second,
            Minute,
            Hour,
            Day,
            Week,
            Month,
            Year
        };

        DateTimeScaleFormatter( Range range, const QString& formatString,
                                Qt::Alignment alignment = Qt::AlignCenter );
        DateTimeScaleFormatter( Range range, const QString& formatString,
                                const QString& templ, Qt::Alignment alignment = Qt::AlignCenter );
        DateTimeScaleFormatter( const DateTimeScaleFormatter& other );
        virtual ~DateTimeScaleFormatter();

        DateTimeScaleFormatter& operator=( const DateTimeScaleFormatter& other );

        QString format() const;
        Range range() const;
        Qt::Alignment alignment() const;

        virtual QDateTime nextRangeBegin( const QDateTime& datetime ) const;
        virtual QDateTime currentRangeBegin( const QDateTime& datetime ) const;

        QString format( const QDateTime& datetime ) const;
        virtual QString text( const QDateTime& datetime ) const;
    };
}



#ifndef QT_NO_DEBUG_STREAM
QDebug KGANTT_EXPORT operator<<( QDebug dbg, KGantt::DateTimeScaleFormatter::Range );
#endif

#endif /* KGANTTDATETIMEGRID_H */

