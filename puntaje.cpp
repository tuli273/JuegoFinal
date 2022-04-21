#include "puntaje.h"

puntaje::puntaje(QGraphicsItem *parent)
{
    //dibujar el texto
    setPlainText(QString("Score: ")+QString::number(Puntaje)); //escribir el texto
    setDefaultTextColor(Qt::white); //pintar el texto
    setFont(QFont("Trajan Pro",18)); //fuente y tamaño
}

void puntaje::aumentar_puntaje(int p_)
{
    Puntaje=p_;
    setPlainText(QString("Score: ")+QString::number(Puntaje)); //escribir el texto
}

void puntaje::setPuntaje(int p_)
{
    Puntaje=p_;
    setPlainText(QString("Score: ")+QString::number(Puntaje)); //escribir el texto
}

int puntaje::getPuntaje()
{
    return Puntaje;
}

void puntaje::mostrar_Puntaje()
{
    setPlainText(QString("Score: ")+QString::number(Puntaje)); //escribir el texto
}

void puntaje::tiempo(int p_)
{
    Puntaje=p_;
    setPlainText(QString("TIME: ")+QString::number(Puntaje)); //escribir el texto
}

void puntaje::texto(QString texto)
{
    setPlainText(texto);
    setDefaultTextColor(Qt::white); //pintar el texto
    setFont(QFont("Trajan Pro",16)); //fuente y tamaño
}




