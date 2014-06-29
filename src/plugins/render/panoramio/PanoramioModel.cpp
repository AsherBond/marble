//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2008      Shashan Singh <shashank.personal@gmail.com>
// Copyright 2009      Bastian Holst <bastianholst@gmx.de>
//

// Self
#include "PanoramioModel.h"
#include "PanoramioItem.h"
#include "PanoramioParser.h"

// Marble
#include "GeoDataLatLonAltBox.h"

// Qt
#include <QUrl>
#include <QString>

using namespace Marble;

PanoramioModel::PanoramioModel( const MarbleModel *marbleModel, QObject *parent )
    : AbstractDataPluginModel( "panoramio", marbleModel, parent )
{
}

void PanoramioModel::getAdditionalItems( const GeoDataLatLonAltBox &box, qint32 number )
{
    // FIXME: Download a list of constant number, because the parser doesn't support
    // loading a file of an unknown length.
    QUrl jsonUrl( "http://www.panoramio.com/map/get_panoramas.php?from="
                  + QString::number( 0 )
                  + "&order=upload_date"
                  + "&set=public"
                  + "&to="   + QString::number( number )
//                   + "&to=" + QString::number( number )
                  + "&minx=" + QString::number( box.west() * RAD2DEG )
                  + "&miny=" + QString::number( box.south() * RAD2DEG )
                  + "&maxx=" + QString::number( box.east() * RAD2DEG )
                  + "&maxy=" + QString::number( box.north() * RAD2DEG )
                  + "&size=small");

    downloadDescriptionFile( jsonUrl );
}

void PanoramioModel::parseFile( const QByteArray &file )
{
    PanoramioParser parser( file );
    QList<panoramioDataStructure> list = parser.parseAllObjects();

    QList<panoramioDataStructure>::iterator it;
    for ( it = list.begin(); it != list.end(); ++it ) {
        // Setting the meta information of the current image
        GeoDataCoordinates coordinates( (*it).longitude,
                                        (*it).latitude,
                                        0,
                                        GeoDataCoordinates::Degree );
                                        
        if( itemExists( QString::number( (*it).photo_id ) ) ) {
            continue;
        }
        
        PanoramioItem *item = new PanoramioItem( this );
        item->setTarget( "earth" );
        item->setCoordinate( coordinates );
        item->setId( QString::number( (*it).photo_id ) );
        item->setUploadDate( (*it).upload_date );
        
        // We need to download the file from Panoramio if it doesn't exist already
        if ( !fileExists( item->id(), standardImageSize ) ) {
            downloadItem( QUrl( (*it).photo_file_url ),
                                standardImageSize,
                                item );
        }
        else {
            // If the file does exist, we can simply load it to our widget.
            const QString filename = generateFilepath( item->id(), standardImageSize );
            item->addDownloadedFile( filename, standardImageSize );
            
            addItemToList( item );
        }
    }
}

#include "PanoramioModel.moc"
