#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene> //incluir la libreria QgraphicsScene.
#include "tanque.h" //incluir la clase tanque.
#include <QMainWindow> //incluir libreria mainWindow
#include "fuerzaaerea.h" //incluir la clase fuerza Aerea enemiga.
#include "balas.h" //incluir la libreria balas.
#include "salud.h" //incluir la libreria de salud.
#include "puntaje.h" //incluir la libreria de puntaje.
#include <QKeyEvent> //libreria para las teclas.
#include <QTimer> //lireria del timer.
#include <QDebug> //libreria de debug.
#include <QList> //libreria de Qlist.
#include <fstream> //libreria de lectura de archivos.
#include <QFile> //libreria lectura de archivos.
#include <QTextStream> //libreria flujo de texto
#include <QMessageBox> //libreria de mensajes de caja
#include <QMediaPlayer> //libreria para musica.
#include <QMovie> //libreria para gif.
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
