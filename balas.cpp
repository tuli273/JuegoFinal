#include "balas.h" //incluir la libreria balas
#include <QTimer> //incluir la libreria Qtimer
#include <QGraphicsScene> //incluir la libreria QgraphicsScene
#include <QGraphicsItem> //incluir la libreria QgraphicsItem
#include <QList> //incluir la libreria Qlist
#include <QDebug> //incluir la libreria Qdebug
#include "mainwindow.h" //incluir la libreria

balas::balas(QGraphicsItem* parent): QObject(), QGraphicsPixmapItem()
{
    //dibujar la bala
    setPixmap(QPixmap(":/recursos/Imagenes/bala.png")); //tamaño de las ballas
    this->setScale(0.5);
    //conectar el tiempo a la bala
    QTimer * timer= new QTimer(); //crear el QTimer
    connect(timer,SIGNAL(timeout()),this,SLOT(move())); //conectar el timer con la funcion mover de las balas
    //lo que hace es que cada 50 milisegundos la bala se mueve
    timer->start(50); //empieza cada 50 milisegundos
}

void balas::move()
{
    //mover la bala
    setPos(x(),y()-20); //le da la posicicion de la bala
    if(pos().y()<80) //condicion que pregunta si la bala salio de la pantalla
    {
        delete this; //elimina la bala
    }

    QList<QGraphicsItem *> colliding_items = collidingItems(); //lista de colisiones
    for(int i = 0, n = colliding_items.size(); i < n; i++)//condicion que me pregunta si hubo alguna collision
    {
        if(typeid(*(colliding_items[i])) == typeid (fuerzaaerea)) //pregunta si la colision fue con un fuerzaaerea
        {
            //remover la bala y el fuerzaaerea
            scene()->removeItem(colliding_items[i]); //remueve el fuerzaaerea
            scene()->removeItem(this); //remueve la bala
            delete this; //elimina la bala
            colliding_items[i]->hide(); //esconde el fuerzaaerea
        }
    }
}
