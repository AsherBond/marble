//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009      Bastian Holst <bastianholst@gmx.de>
//

#ifndef WEATHERMODEL_H
#define WEATHERMODEL_H

#include "AbstractDataPluginModel.h"

#include "WeatherData.h"
#include "GeoDataLatLonBox.h"
#include "MarbleWidget.h"

#include <QStringList>

class QByteArray;
class QTimer;

namespace Marble
{

class AbstractWeatherService;
class GeoDataLatLonBox;
class MarbleModel;
    
class WeatherModel : public AbstractDataPluginModel
{
    Q_OBJECT
    
 public:
    explicit WeatherModel( const MarbleModel *marbleModel, QObject *parent );
    ~WeatherModel();

    void setUpdateInterval( quint32 hours );

    void setFavoriteItems( const QStringList& list );
    
 public Q_SLOTS:
    /**
     * Downloads the file from @p url. @p item -> addDownloadedFile() will be called when the
     * download is finished. Additionally initialized() items will be added to the item list
     * after the download.
     * @param: The type of the download
     **/
    void downloadItemData( const QUrl& url, const QString& type, AbstractDataPluginItem *item );
    
    void downloadDescriptionFileRequested( const QUrl& url, const TileId& tileId );

    void setMarbleWidget(MarbleWidget *widget);

 Q_SIGNALS:
    void additionalItemsRequested( const GeoDataLatLonBox &,
                                   qint32 number,
                                   const TileId& tileId );
    void favoriteItemChanged( const QString& id, bool isFavorite );
    void parseFileRequested( const QByteArray& file, int zoomLevel );

 protected:
    void getAdditionalItems( const GeoDataLatLonBox& box,
                             qint32 number,
                             const TileId& tileId );
    void getItem( const QString &id, int zoomLevel );
    void parseFile( const QByteArray& file, int zoomLevel );

 private:
    void addService( AbstractWeatherService *service );

    QList<AbstractWeatherService*> m_services;
    QTimer *m_timer;
};

} // namespace Marble

#endif // WEATHERMODEL_H
