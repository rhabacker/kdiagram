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

#include "KChartPrintingParameters.h"

using namespace KChart;

PrintingParameters::PrintingParameters()
    : scaleFactor( 1.0 )
{
}

PrintingParameters* PrintingParameters::instance()
{
    static PrintingParameters instance;
    return &instance;
}

void PrintingParameters::setScaleFactor( const qreal scaleFactor )
{
    instance()->scaleFactor = scaleFactor;
}

void PrintingParameters::resetScaleFactor()
{
    instance()->scaleFactor = 1.0;
}

QPen PrintingParameters::scalePen( const QPen& pen )
{
    if ( instance()->scaleFactor == 1.0 )
        return pen;

    QPen resultPen = pen;
    resultPen.setWidthF( resultPen.widthF() * instance()->scaleFactor );
    if ( resultPen.widthF() == 0.0 )
        resultPen.setWidthF( instance()->scaleFactor );

    return resultPen;
}
