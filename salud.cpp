#include "salud.h"

salud::salud()
{
    //dibujar el texto
    setPlainText(QString("x")+QString::number(Vidas)); //escribir el texto
    setDefaultTextColor(Qt::white); //pintar el texto
    setFont(QFont("Trajan Pro",18)); //fuente y tamaño
}

void salud::disminuir_salud()
{
    Vidas--; //restar 1 en las vidas
    setPlainText(QString("x")+QString::number(Vidas)); //actualizar texto
}

int salud::getVidas()
{
    return Vidas;
}

void salud::Game_over()
{
    setPlainText(QString("GAME OVER")); //actualizar texto
    setDefaultTextColor(Qt::white); //pintar el texto
    setFont(QFont("Trajan Pro",80)); //fuente y tamaño
}

void salud::setVidas(int v_)
{
    Vidas=v_;
    setPlainText(QString("x")+QString::number(Vidas)); //actualizar texto
}
