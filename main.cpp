#include "mainwindow.h"

#include <QApplication>

#include<QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //Con ayuda de la libreria QSplashScreen se puede mostrar una pantalla de carga con un logo png diseñado para el juego
    QSplashScreen splash;
    splash.setPixmap(QPixmap(":/recursos/imagenes/presentacion").scaled(308,274));
    splash.show();
    //se muestra por 3 segundos el logo del juego y luego se ejecuta el juego
    QTimer::singleShot(3000,&splash,SLOT(close()));
    QTimer::singleShot(3500,&w,SLOT(show()));
    return a.exec();
}
