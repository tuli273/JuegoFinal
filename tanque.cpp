#include "tanque.h"

tanque::tanque()
{

}

tanque::tanque(double x, double y, double ancho_, double largo_)
{
    posx=x; //asignar la posicion en x ingresada.
    posy=y; //asignar la posicion en y ingresada.
    ancho=ancho_; //asignar el ancho del tanque.
    largo=largo_; //asignar el largo del tanque.
    columnas =0;
    filas=45;
    setPos(posx,posy);
    pixmap = new QPixmap(":/recursos/Imagenes/personaje_principal.png");
}

double tanque::getPosx()
{
    return posx; //retornar posicion en x.
}

double tanque::getPosy()
{
    return posy; //retornar posicion en y.
}

void tanque::setPosx(double x)
{
    posx=x;
    setX(posx); //darle el valor x a la posicion en x
}

void tanque::setPosy(double y)
{
    posy=y;
    setY(posy); //darle el valor y a la posicion en y
}

void tanque::setVelocidad(int v_)
{
    velocidad=v_; //dar velocidad
}

void tanque::setcolumna_fila(int c_, int f_)
{
    columnas=c_; //actualizar columna
    filas=f_; //actualizar fila
    this->update(-ancho/2,-largo/2,ancho,largo); //actualiza el tanque
}

void tanque::setImagen(int i)
{
    // actualizar la imagen
    if(i==0)
    {
        pixmap = new QPixmap(":/recursos/Imagenes/personaje_principal.png");
    }
    if(i==1)
    {
        pixmap = new QPixmap(":/recursos/Imagenes/sprite_vidas.png");
    }
    if(i==2)
    {
        pixmap = new QPixmap(":/recursos/Imagenes/VACIO.png");
    }
    if(i==3)
    {
        pixmap = new QPixmap(":/recursos/Imagenes/personaje_secundario.png");
    }
}

QRectF tanque::boundingRect() const
{
    return QRectF(-ancho/2,-largo/2,ancho,largo); //retornar un rectangulo
}

void tanque::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-largo/2,*pixmap,columnas,filas,ancho,largo);
}

void tanque::mover_derecha()
{
    columnas=0; //dejar columna 0
    filas=0; //ir sumando 40 a la fila
    this->update(-ancho/2,-largo/2,ancho,largo); //actualizar tanque
    posx=posx+velocidad; //sumarle el valor de la velocidad a la posicion en x
    setX(posx); //actualiza la posicion en x
}

void tanque::mover_izquierda()
{
    columnas=0;
    filas=60;
    this->update(-ancho/2,-largo/2,ancho,largo);
    posx=posx-velocidad; //restarle el valor de la velocidad a la posicion en x
    setX(posx); //actualizar la posicion en x
}

void tanque::Disparo()
{
    columnas=0;
    filas=120;
    this->update(-ancho/2,-largo/2,ancho,largo);
}



