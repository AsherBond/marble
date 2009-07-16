//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009      Andrew Manson <g.real.ate@gmail.com>
//

#include "OsmWayTagHandler.h"

#include "GeoParser.h"
#include "OsmElementDictionary.h"

namespace Marble
{

namespace osm
{

static GeoTagHandlerRegistrar s_handlerbounds( GeoTagHandler::QualifiedName(osmTag_way, ""),
                                               new OsmWayTagHandler() );

GeoNode* OsmWayTagHandler::parse( GeoParser& parser ) const
{
}

}

}
