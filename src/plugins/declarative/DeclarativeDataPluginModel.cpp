//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2012      Anton Chernov <chernov.anton.mail@gmail.com>
// Copyright 2012      "LOTES TM" LLC <lotes.sis@gmail.com>
// Copyright 2012      Dennis Nienhüser <earthwings@gentoo.org>
//

#include "DeclarativeDataPluginModel.h"

#include "GeoDataLatLonBox.h"

using namespace Marble;

DeclarativeDataPluginModel::DeclarativeDataPluginModel( const MarbleModel *marbleModel, QObject *parent )
    : AbstractDataPluginModel( "QMLDataPluginModel", marbleModel, parent )
{
    // nothing to do
}

DeclarativeDataPluginModel::~DeclarativeDataPluginModel()
{
    // nothing to do
}

void DeclarativeDataPluginModel::getAdditionalItems( const GeoDataLatLonBox& box, qint32, const TileId& tileId )
{
    Marble::GeoDataCoordinates::Unit const degree = Marble::GeoDataCoordinates::Degree;
    emit dataRequest( box.north( degree ), box.south( degree ), box.east( degree ), box.west( degree ), tileId );
}

#include "DeclarativeDataPluginModel.moc"
