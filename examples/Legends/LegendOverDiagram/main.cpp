/**
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

#include <QApplication>
#include <KChartWidget>
#include <KChartBarDiagram>
#include <KChartPosition>
#include <KChartLegend>


using namespace KChart;

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    Widget widget;
    widget.resize( 600, 600 );

    QVector< qreal > vec0,  vec1,  vec2;

    vec0 << -5 << -4 << -3 << -2 << -1 << 0
         << 1 << 2 << 3 << 4 << 5;
    vec1 << 25 << 16 << 9 << 4 << 1 << 0
         << 1 << 4 << 9 << 16 << 25;
    vec2 << -125 << -64 << -27 << -8 << -1 << 0
         << 1 << 8 << 27 << 64 << 125;

    widget.setDataset( 0, vec0, "v0" );
    widget.setDataset( 1, vec1, "v1" );
    widget.setDataset( 2, vec2, "v2" );
    widget.setType( Widget::Bar );
 
    Legend* legend = new Legend( widget.diagram(), &widget );
    legend->setOrientation( Qt::Horizontal );
    legend->setTitleText( "Bars Legend" );
    legend->setText( 0,  "Vector 1" );
    legend->setText( 1,  "Vector 2" );
    legend->setText( 2,  "Vector 3" );
    legend->setShowLines(  true );

    // The following aligns the legend exactly to the
    // chart's coordinate plane's top-right corner.
    //
    // Note: We do NOT use Legend::setAlignment here, because when
    //       setRelativePosition is used the alignment is set at the
    //       KChart::RelativePosition rather than at the KChart::Legend.
    KChart::RelativePosition relativePosition;
    relativePosition.setReferenceArea( widget.coordinatePlane() );
    relativePosition.setReferencePosition( Position::NorthEast );
    relativePosition.setAlignment( Qt::AlignTop | Qt::AlignRight );
    relativePosition.setHorizontalPadding( KChart::Measure( -1.0, KChartEnums::MeasureCalculationModeAbsolute ) );
    relativePosition.setVerticalPadding(   KChart::Measure(  1.0, KChartEnums::MeasureCalculationModeAbsolute ) );
    legend->setFloatingPosition( relativePosition );

    widget.addLegend( legend );

    widget.show();

    return app.exec();
}
