#include "mainwindow.h"
#include "playersdirector.h"
#include <QApplication>

#include <QTimer>
#include <QDir>
#include <QUrl>
#include <QFileInfo>
#include <QMediaPlaylist>

#include <QScopedPointer>

int main ( int argc, char* argv[] )
{

  qDebug () << "start program" << endl;


  QApplication a ( argc, argv );
  MainWindow w;
  w.show();

  QScopedPointer<PlayersDirector> pd ( new PlayersDirector () );

  pd->createPlayers();
  pd->play();
  //pd->stop();

  return a.exec();

}


