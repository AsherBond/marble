//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 200-2007 Torsten Rahn <tackat@kde.org>"
// Copyright 2007      Inge Wallin  <ingwa@kde.org>"
//


#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QStringList>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtGui/QApplication>


int main(int argc, char *argv[])
{
    QCoreApplication  app(argc, argv);
    QFile             data( "../../src/lib/texturepalette.cpp" );

    if ( !data.open( QFile::WriteOnly | QFile::Truncate ) ) {
        app.exit();
        return EXIT_FAILURE;
    }

    QTextStream  out(&data);
    out << "//" << endl;
    out << "// DO NOT EDIT" << endl;
    out << "// This file is autogenerated from the tools/pallettegen program" << endl;
    out << "//" << endl;

    out << "// This file is part of the Marble Desktop Globe." << endl;
    out << "//" << endl;
    out << "// This program is free software licensed under the GNU LGPL. You can" << endl;
    out << "// find a copy of this license in LICENSE.txt in the top directory of" << endl;
    out << "// the source code." << endl;
    out << "//" << endl;
    out << "// Copyright 2007 Torsten Rahn <tackat@kde.org>" << endl;
    out << "// Copyright 2007 Inge Wallin  <ingwa@kde.org>" << endl;
    out << "//" << endl;
    out << "" << endl;
    out << "" << endl;

    out << "const uint TextureColorizer::texturepalette[][512]=" << endl
        << "{" << endl;
    out.setIntegerBase(16);

    QImage  gradimg( 256, 10, QImage::Format_RGB32 );

    QStringList  filelist;
    filelist << "../../data/seacolors.leg" << "../../data/landcolors.leg";

    QPainter  painter(&gradimg);
    painter.setPen(Qt::NoPen);

    for ( int j = 0; j < 16; ++j ) {
        foreach ( const QString& filename, filelist ) {
		
            QLinearGradient  gradient( 0, 0, 256, 0 );

            QFile  file( filename );
            file.open( QIODevice::ReadOnly );
            QTextStream  stream( &file );  // read the data serialized from the file
            QString  evalstrg;

            while ( !stream.atEnd() ) {
                stream >> evalstrg;
                if ( !evalstrg.isEmpty() && evalstrg.contains( "=" ) ) {
                    QString  colval = evalstrg.section( "=", 0, 0 );
                    QString  colpos = evalstrg.section( "=", 1, 1 );
                    gradient.setColorAt(colpos.toDouble(), QColor(colval));
                }
            }
            painter.setBrush( gradient );
            painter.drawRect( 0, 0, 256, 10 );	


            int  alpha = j;

            for ( int i = 0; i < 256; ++i) {

                    QRgb  shadeColor = gradimg.pixel( i, 1 );
                    QImage  shadeImage ( 256, 10, QImage::Format_RGB32 );
                    QLinearGradient  shadeGradient( 0, 0, 256, 0 );
                    shadeGradient.setColorAt(0.15, QColor(Qt::white));
                    shadeGradient.setColorAt(0.496, shadeColor);
                    shadeGradient.setColorAt(0.504, shadeColor);
                    shadeGradient.setColorAt(0.75, QColor(Qt::black));
                    QPainter  shadePainter(&shadeImage);
                    shadePainter.setPen(Qt::NoPen);
                    shadePainter.setBrush( shadeGradient );
                    shadePainter.drawRect( 0, 0, 256, 10 );
                    shadePainter.end();
                    int shadeIndex = 120 + alpha;
//                    qDebug() << QString("Shade: %1").arg(shadeIndex);
                    QRgb  palcol = shadeImage.pixel( shadeIndex, 1 );

                if ( filename == filelist[0] ) {
                    if ( i == 0 )
                        out << "		{ 0x" << (uint)palcol << "," << endl;
                    else
                        out << "		0x" << (uint)palcol << "," << endl;
                }
                else {
                    if ( i == 255 ) 
                        out << "		0x" << (uint)palcol << " }," << endl;
                    else
                        out << "		0x" << (uint)palcol << "," << endl;
                    // out << "		" << (uint)gradimg->pixel(i,1) << "," << endl;
                }
            }
        }
    }
    painter.end();

    out << "};" << endl;

    //<< qSetFieldWidth(10) << left << 3.14 << 2.7 << endl;
    // writes "Result: 3.14      2.7       \n"

    app.exit();
}
