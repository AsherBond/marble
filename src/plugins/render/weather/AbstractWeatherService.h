//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009      Bastian Holst <bastianholst@gmx.de>
//

#ifndef ABSTRACTWEATHERSERVICE_H
#define ABSTRACTWEATHERSERVICE_H

#include <QObject>
#include <QStringList>

class QUrl;

namespace Marble
{

class AbstractDataPluginItem;
class GeoDataLatLonBox;
class MarbleModel;
class MarbleWidget;

class AbstractWeatherService : public QObject
{
    Q_OBJECT
    
 public:
    explicit AbstractWeatherService( const MarbleModel *model, QObject *parent );
    virtual ~AbstractWeatherService();
    void setMarbleWidget( MarbleWidget* widget );
    
 public Q_SLOTS:
    virtual void setFavoriteItems( const QStringList& favorite );
    QStringList favoriteItems() const;

    virtual void getAdditionalItems( const GeoDataLatLonBox& box,
                                     qint32 number,
                                     int zoomLevel ) = 0;
    virtual void getItem( const QString &id, int zoomLevel ) = 0;
    virtual void parseFile( const QByteArray& file, int zoomLevel );
    
 Q_SIGNALS:
    void requestedDownload( const QUrl& url, const QString& type, AbstractDataPluginItem *item );
    void createdItems( QList<AbstractDataPluginItem*> items );
    void downloadDescriptionFileRequested( const QUrl&, int zoomLevel );

protected:
    const MarbleModel* marbleModel() const;
    MarbleWidget* marbleWidget();

private:
    const MarbleModel *const m_marbleModel;
    QStringList m_favoriteItems;
    MarbleWidget* m_marbleWidget;
};

} // namespace Marble

#endif // ABSTRACTWEATHERSERVICE_H
