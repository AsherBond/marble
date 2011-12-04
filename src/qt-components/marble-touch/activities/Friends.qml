// This file is part of the Marble Virtual Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2011 Dennis Nienhüser <earthwings@gentoo.org>
// Copyright 2011 Daniel Marth <danielmarth@gmx.at>

import QtQuick 1.0
import com.nokia.meego 1.0
import org.kde.edu.marble 0.11
import org.kde.edu.marble.qtcomponents 0.12

/*
 * Page for friends (social, opendesktop) activity.
 */
Page {
    id: friendsActivityPage
    anchors.fill: parent

    tools: ToolBarLayout {
        ToolIcon {
            iconId: "toolbar-back";
            onClicked: pageStack.pop()
        }
        ToolIcon {
            iconId: "toolbar-home"
            onClicked: {
                marbleWidget.centerOn( marbleWidget.getTracking().lastKnownPosition.longitude, marbleWidget.getTracking().lastKnownPosition.latitude )
                if (marbleWidget.zoom < 2000 ) {
                    marbleWidget.zoom = 2773
                }
            }
        }
        ToolIcon {
            iconId: "toolbar-view-menu"
            onClicked: pageMenu.open()
        }
    }

    Menu {
        id: pageMenu
        content: MenuLayout {
            MenuItem {
                text: "Map Theme"
                onClicked: {
                    pageStack.push( "qrc:/MapThemeSelectionPage.qml" )
                }
            }
            MenuItemSwitch {
                text: "Online"
                checked: !settings.workOffline
                onClicked: settings.workOffline = !settings.workOffline
            }
        }
    }

    Item {
        clip: true
        id: mapContainer
        anchors.fill: parent

        function embedMarbleWidget() {
            marbleWidget.parent = mapContainer
            settings.projection = "Mercator"
            var plugins = settings.defaultRenderPlugins
            settings.removeElementsFromArray(plugins, ["coordinate-grid", "sun", "stars", "compass"])
            plugins.push( "opendesktop" )

            settings.activeRenderPlugins =  plugins
            settings.mapTheme = "earth/openstreetmap/openstreetmap.dgml"
            settings.gpsTracking = true
            settings.showPosition = true
            settings.showTrack = false
            marbleWidget.visible = true
        }

        Component.onDestruction: {
            if ( marbleWidget.parent === mapContainer ) {
                marbleWidget.parent = null
                marbleWidget.visible = false
            }
        }
    }

    onStatusChanged: {
        if ( status === PageStatus.Activating ) {
            mapContainer.embedMarbleWidget()
        }
    }
}
