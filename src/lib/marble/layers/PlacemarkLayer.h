//
// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2006-2007 Torsten Rahn <tackat@kde.org>
// Copyright 2007-2008 Inge Wallin  <ingwa@kde.org>
// Copyright 2012      Bernhard Beschow <bbeschow@cs.tu-berlin.de>
//

//
// PlacemarkLayer is responsible for drawing the Placemarks on the map
//

#ifndef MARBLE_PLACEMARKLAYER_H
#define MARBLE_PLACEMARKLAYER_H


#include <QObject>
#include "LayerInterface.h"
#include "GlLayerInterface.h"

#include <QHash>
#include <QVector>
#include <QColor>
#include <qgl.h>

#include "PlacemarkLayout.h"

class QAbstractItemModel;
class QGLContext;
class QItemSelectionModel;
class QString;

namespace Marble
{

class GeoPainter;
class GeoSceneLayer;
class MarbleClock;
class ViewportParams;
class VisiblePlacemark;

class PlacemarkLayer : public QObject, public LayerInterface, public GlLayerInterface
{
    Q_OBJECT

 public:
    PlacemarkLayer( QAbstractItemModel *placemarkModel,
                    QItemSelectionModel *selectionModel,
                    MarbleClock *clock,
                    QObject *parent = 0 );
    ~PlacemarkLayer();

    /**
     * @reimp
     */
    QStringList renderPosition() const;

    /**
     * @reimp
     */
    qreal zValue() const;

    /**
     * @reimp
     */
    bool render( GeoPainter *painter, ViewportParams *viewport,
                 const QString &renderPos = "NONE", GeoSceneLayer *layer = 0 );

    void paintGL( QGLContext *glContext, const ViewportParams *viewport );

    virtual QString runtimeTrace() const;

    /**
     * Returns a list of model indexes that are at position @p pos.
     */
    QVector<const GeoDataPlacemark*> whichPlacemarkAt( const QPoint &pos );

    static bool m_useXWorkaround;  // Indicates need for an X windows workaround.
 public Q_SLOTS:
   // earth
   void setShowPlaces( bool show );
   void setShowCities( bool show );
   void setShowTerrain( bool show );
   void setShowOtherPlaces( bool show );

   // other planets
   void setShowLandingSites( bool show );
   void setShowCraters( bool show );
   void setShowMaria( bool show );

   void requestStyleReset();

 Q_SIGNALS:
   void repaintNeeded();

 private:
    bool testXBug();

 private:
    PlacemarkLayout m_layout;

    struct GlData {
        GlData( GLuint symbolId = 0, GLuint labelId = 0 ) :
            symbolId( symbolId ),
            labelId( labelId )
        {}

        GLuint symbolId;
        GLuint labelId;
    };

    QHash<const GeoDataPlacemark *, GlData> m_glMap;
};

}

#endif
