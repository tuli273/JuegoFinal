#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //escena
    escena = new QGraphicsScene; //crear la escena del juego
    ui->graphicsView->setScene(escena); //agregar el graphicsView
    escena->setSceneRect(0,0,1000,698); //darle un tamaño a la escena

    //vidas
    vidas = new salud(); //crear variable de las vidas
    vidas->setPos(70,20); //dar posicion a las vidas

    //puntos
    puntos = new puntaje; //crear variable puntaje
    puntos->setPos(140,20); //dar posicion al puntaje

    //texto en pantalla
    escogerpartida = new puntaje;
    escogerpartida->setPos(353,20);


    //tanque principal
    tanque1 = new tanque(10,595,71,55); //creo chillin

    //entorno
    piso = new tanque(500,650,1000,50); //creo el piso
    muroderecho = new tanque(1025,350,50,800); //creo el muro derecho
    muroizquierdo = new tanque(-25,350,50,800); //creo el muro izquierdo

    //timers
    timerfuerzaaerea = new QTimer; //creo el Qtimer
    timerfuerzaaerea2 = new QTimer; //creo el Qtimer
    timerfuerzaaerea3 = new QTimer; //creo el Qtimer
    timergenerarfuerzaaereas = new QTimer;
    timerfuerzaaereasmultijugador = new QTimer;

    //sprite vidas
    Sprite_vidas = new tanque(50,40,50,50); //crear Spritevidas
    Sprite_vidas->setImagen(1); //actualizar el spirte

    //lodo
    musgo = new tanque(500,600,350,40); //crear lodo
    musgo->setImagen(2); //seleccionar imagen

    //audio
    musica = new QMediaPlayer; //creo musica del menu
    musica->setMedia(QUrl("qrc:/recursos/musica/musica_menu.mp3")); // le doy la cancion correspondiente

    //lineedit
    ui->lineEdit_clave->setEchoMode(QLineEdit::Password); //esconder texto en el lineEdit

    multijugador=false; //multijugador

    menu(); //mostrar el menu
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mover_enemys_level_1()
{
    for(int i=0; i<fuerzaaereas.size();i++) //ciclo que lee toda la lista de fuerzaaereas
    {
         /* fuerzaaerea 1 2 3 y 4 las bolas con movimiento MCU
         * fuerzaaerea 5 con el movimiento MAS*/
        if(i==0) //condicion que pregunta si es el tercer fuerzaaerea
        {
            fuerzaaereas.at(i)->MCU(150,400,150,-1,0); //darle movimiento circular uniforme
        }

        if(i==1) //condicion que pregunta si es el tercer fuerzaaerea
        {
            fuerzaaereas.at(i)->MCU(850,400,150,1,-3.1416); //darle movimiento circular uniforme
        }

        if(i==2) //condicion que pregunta si es el tercer fuerzaaerea
        {
            fuerzaaereas.at(i)->MCU(250,400,150,1,0); //darle movimiento circular uniforme
        }

        if(i==3) //condicion que pregunta si es el cuarto fuerzaaerea
        {
            fuerzaaereas.at(i)->MCU(750,400,150,-1,-3.1416); //darle el omvimiento circular uniforme
        }

        if(i==4) //condicion que pregunta si es el quinto fuerzaaerea
        {
            fuerzaaereas.at(i)->MAS(500,170,280,2,1); //darle movmiento armonico simple
        }

        choque(fuerzaaereas.at(i)); //funcion que detecta el choque y actualiza las vidas
        actualizar_puntaje(0); //funcion que detecta que el diparo haya acertado a un fuerzaaerea y actualiza el puntaje
    }
    if(puntos->getPuntaje()==50)
    {
        nivel2();
    }
    //qDebug()<<"fuerzaaereas: "<<c;
    //qDebug()<<"corriendo timer1";
}

void MainWindow::mover_enemys_level_2()
{
    for(int i=0; i<fuerzaaereas.size();i++) //ciclo que lee toda la lista de fuerzaaereas
    {
        //qDebug() <<"velocidad: "<<fuerzaaereas.at(i)->getVel();
        //qDebug() <<"velocidadx: "<<fuerzaaereas.at(i)->getVely();

        if(i==0)
        {
            if(fuerzaaereas.at(i)->getVel()>70){fuerzaaereas.at(i)->setVel(70);} //condicion para que no supere cierta velocidad
            if(fuerzaaereas.at(i)->getVelx()<45){fuerzaaereas.at(i)->setVelx(45);} //condicion para que no rebote con una velocidad menor
        }

        if(i==1)
        {
            if(fuerzaaereas.at(i)->getVel()>70){fuerzaaereas.at(i)->setVel(70);} //condicion para que no supere cierta velocidad
            if(fuerzaaereas.at(i)->getVelx()<45){fuerzaaereas.at(i)->setVelx(45);} //condicion para que no rebote con una velocidad menor
        }

        if(i==2)
        {
            if(fuerzaaereas.at(i)->getVel()>50){fuerzaaereas.at(i)->setVel(50);} //condicion para que no supere cierta velocidad
            if(fuerzaaereas.at(i)->getVelx()<15){fuerzaaereas.at(i)->setVelx(15);} //condicion para que no rebote con una velocidad menor
        }

        if(i==3)
        {
            if(fuerzaaereas.at(i)->getVel()>50){fuerzaaereas.at(i)->setVel(50);} //condicion para que no supere cierta velocidad
            if(fuerzaaereas.at(i)->getVelx()<15){fuerzaaereas.at(i)->setVelx(15);} //condicion para que no rebote con una velocidad menor
        }

        if(i==4)
        {
            if(fuerzaaereas.at(i)->getVel()>80){fuerzaaereas.at(i)->setVel(80);} //condicion para que no supere cierta velocidad
            if(fuerzaaereas.at(i)->getVelx()<0){fuerzaaereas.at(i)->setVelx(0);} //condicion para que no rebote con una velocidad menor
        }

        //mover a la derecha
        if(fuerzaaereas.at(i)->getDir()==1) //condicion para preguntar por la direcion
        {

            if(fuerzaaereas.at(i)->getVely()>0) //condicion que pregunta si la velocidad e el eje y es positiva
            {
                fuerzaaereas.at(i)->setColumnas_fila(0,0);//actulizar el sprite
            }
            if(fuerzaaereas.at(i)->getVely()<0) //condicion que pregunta si la velocidad en el eje y es negativo
            {
                fuerzaaereas.at(i)->setColumnas_fila(0,84);// actualiza el sprite
            }
            fuerzaaereas.at(i)->actualizarposicion_derecha(); //actualiza la posicion
            fuerzaaereas.at(i)->actualizarvelocidad(); //actualiza la velocidad
            fuerzaaereas.at(i)->setX(fuerzaaereas.at(i)->getPosx()); //setea la posicion en x
            fuerzaaereas.at(i)->setY(-fuerzaaereas.at(i)->getPosy());//setea la posicion en y
        }

        //mover a la izquierda
        if(fuerzaaereas.at(i)->getDir()==2) //condicion para preguntar la direccion
        {
            if(fuerzaaereas.at(i)->getVely()>0) //condicion que pregunta si la velocidad e el eje y es positiva
            {
                fuerzaaereas.at(i)->setColumnas_fila(58,0); //actualiza el sprite
            }
            if(fuerzaaereas.at(i)->getVely()<0) //condicion que pregunta si la velocidad en el eje y es negativa
            {
                fuerzaaereas.at(i)->setColumnas_fila(58,84); //actualizar el sprite
            }
            fuerzaaereas.at(i)->actualizarposicion_izquierda(); //actualiza la posicion
            fuerzaaereas.at(i)->actualizarvelocidad(); //actualiza la velocidad
            fuerzaaereas.at(i)->setX(fuerzaaereas.at(i)->getPosx()); //setea la posicion en x
            fuerzaaereas.at(i)->setY(-fuerzaaereas.at(i)->getPosy());//setea la posicion en y
        }

        //rebote con el piso
        if(fuerzaaereas.at(i)->collidesWithItem(piso)) //condicion para preguntar si colisiono con el piso
        {
            fuerzaaereas.at(i)->rebotepiso(); //aplicar rebote
        }
        //rebote con el muro derecho
        if (fuerzaaereas.at(i)->collidesWithItem(muroderecho)) //condicion que pregunta si colisiono con el muro derecho
        {
            fuerzaaereas.at(i)->setDir(2); //actualizar la direccion de movimiento
        }
        //rebote con el muro izquierdo
        if (fuerzaaereas.at(i)->collidesWithItem(muroizquierdo)) //condicion que pregunta si colisiono con el muro izquierdo
        {
            fuerzaaereas.at(i)->setDir(1);//actualizar la direccion de movimiento
        }

        choque(fuerzaaereas.at(i)); //funcion que detecta el choque y actualiza las vidas
        actualizar_puntaje(50); //funcion que detecta que el diparo haya acertado a un fuerzaaerea y actualiza el puntaje
    }

    if(puntos->getPuntaje()==100)
    {
        nivel3();
    }
    //qDebug()<<"corriendo timer1";

}

void MainWindow::mover_enemys_level_3()
{
    if(puntos->getPuntaje()==170)
    {
        gano();
    }
    //qDebug()<<"tamaño lista;"<<fuerzaaereas.size();
    for(int i=0; i<fuerzaaereas.size();i++) //ciclo que lee toda la lista de fuerzaaereas
    {
        /* enemmigo 1 y 2 son las bolas que rebotan
         * fuerzaaerea 3 y 4 las bolas con movimiento MCU
         * fuerzaaerea 5 con el movimiento MAS*/

        //qDebug() <<"velocidad: "<<fuerzaaereas.at(i)->getVel();
        //qDebug() <<"velocidadx: "<<fuerzaaereas.at(i)->getVelx();
        if(fuerzaaereas.at(i)->getVel()>90){fuerzaaereas.at(i)->setVel(90);} //condicion para que no supere cierta velocidad
        if(fuerzaaereas.at(i)->getVelx()<30){fuerzaaereas.at(i)->setVelx(30);} //condicion para que no rebote con una velocidad menor

        //mover a la derecha
        if(fuerzaaereas.at(i)->getDir()==1) //condicion para preguntar por la direcion
        {

            if(fuerzaaereas.at(i)->getVely()>0) //condicion que pregunta si la velocidad e el eje y es positiva
            {
                fuerzaaereas.at(i)->setColumnas_fila(0,0);//actulizar el sprite
            }
            if(fuerzaaereas.at(i)->getVely()<0) //condicion que pregunta si la velocidad en el eje y es negativo
            {
                fuerzaaereas.at(i)->setColumnas_fila(0,84);// actualiza el sprite
            }
            fuerzaaereas.at(i)->actualizarposicion_derecha(); //actualiza la posicion
            fuerzaaereas.at(i)->actualizarvelocidad(); //actualiza la velocidad
            fuerzaaereas.at(i)->setX(fuerzaaereas.at(i)->getPosx()); //setea la posicion en x
            fuerzaaereas.at(i)->setY(-fuerzaaereas.at(i)->getPosy());//setea la posicion en y
        }

        //mover a la izquierda
        if(fuerzaaereas.at(i)->getDir()==2) //condicion para preguntar la direccion
        {
            if(fuerzaaereas.at(i)->getVely()>0) //condicion que pregunta si la velocidad e el eje y es positiva
            {
                fuerzaaereas.at(i)->setColumnas_fila(80,0); //actualiza el sprite
            }
            if(fuerzaaereas.at(i)->getVely()<0) //condicion que pregunta si la velocidad en el eje y es negativa
            {
                fuerzaaereas.at(i)->setColumnas_fila(80,84); //actualizar el sprite
            }
            fuerzaaereas.at(i)->actualizarposicion_izquierda(); //actualiza la posicion
            fuerzaaereas.at(i)->actualizarvelocidad(); //actualiza la velocidad
            fuerzaaereas.at(i)->setX(fuerzaaereas.at(i)->getPosx()); //setea la posicion en x
            fuerzaaereas.at(i)->setY(-fuerzaaereas.at(i)->getPosy());//setea la posicion en y
        }

        //rebote con el piso
        if(fuerzaaereas.at(i)->collidesWithItem(piso)) //condicion para preguntar si colisiono con el piso
        {
            if(i!=5)
            {
                fuerzaaereas.at(i)->rebotepiso(); //aplicar rebote
            }
        }
        //rebote con el muro derecho
        if (fuerzaaereas.at(i)->collidesWithItem(muroderecho)) //condicion que pregunta si colisiono con el muro derecho
        {
            fuerzaaereas.at(i)->setDir(2); //actualizar la direccion de movimiento
        }
        //rebote con el muro izquierdo
        if (fuerzaaereas.at(i)->collidesWithItem(muroizquierdo)) //condicion que pregunta si colisiono con el muro izquierdo
        {
            fuerzaaereas.at(i)->setDir(1);//actualizar la direccion de movimiento
        }

        if(i==2) //condicion que pregunta si es el tercer fuerzaaerea
        {
            fuerzaaereas.at(i)->MCU(300,400,200,-1,0); //darle movimiento circular uniforme
        }

        if(i==3) //condicion que pregunta si es el cuarto fuerzaaerea
        {
            fuerzaaereas.at(i)->MCU(700,400,200,-1,-3.1416); //darle el omvimiento circular uniforme
        }

        if(i==4) //condicion que pregunta si es el quinto fuerzaaerea
        {
            fuerzaaereas.at(i)->MAS(500,350,240,1,2); //darle movmiento armonico simple
        }

        if(i==5) //condicion que pregunta si es el sexto fuerzaaerea
        {
            fuerzaaereas.at(i)->MAS(250,350,200,1.8,1);
        }

        if(i==6) //condicion que pregunta si es el sexto fuerzaaerea
        {
            fuerzaaereas.at(i)->MAS(750,350,200,-1.8,1);
        }

        choque(fuerzaaereas.at(i)); //funcion que detecta el choque y actualiza las vidas
        actualizar_puntaje(100); //funcion que detecta que el diparo haya acertado a un fuerzaaerea y actualiza el puntaje
    }
}

void MainWindow::mover_enemys_multiplayer()
{
    if(vidas->getVidas()==2)
    {
        for(int i=0; i<fuerzaaereas.size();i++) //ciclo que lee toda la lista de fuerzaaereas
        {
            if(fuerzaaereas.at(i)->isVisible())
            {
                fuerzaaereas.at(i)->actualizarposicion_derecha(); //actualiza la posicion
                fuerzaaereas.at(i)->actualizarvelocidad(); //actualiza la velocidad
                fuerzaaereas.at(i)->setX(fuerzaaereas.at(i)->getPosx()); //setea la posicion en x
                fuerzaaereas.at(i)->setY(-fuerzaaereas.at(i)->getPosy());//setea la posicion en y
            }

            if(fuerzaaereas.at(i)->getPosy()<-750 && fuerzaaereas.at(i)->isActive())
            {
                fuerzaaereas.at(i)->hide();
            }
            choque_multijugador(fuerzaaereas.at(i));
        }
    }

    if(vidas->getVidas()==1)
    {
        for(int i=0; i<fuerzaaereas2.size();i++) //ciclo que lee toda la lista de fuerzaaereas
        {
            if(fuerzaaereas2.at(i)->isVisible())
            {
                fuerzaaereas2.at(i)->actualizarposicion_derecha(); //actualiza la posicion
                fuerzaaereas2.at(i)->actualizarvelocidad(); //actualiza la velocidad
                fuerzaaereas2.at(i)->setX(fuerzaaereas2.at(i)->getPosx()); //setea la posicion en x
                fuerzaaereas2.at(i)->setY(-fuerzaaereas2.at(i)->getPosy());//setea la posicion en y
            }

            if(fuerzaaereas2.at(i)->getPosy()<-750 && fuerzaaereas2.at(i)->isActive())
            {
                fuerzaaereas2.at(i)->hide();
            }
            choque_multijugador(fuerzaaereas2.at(i));
        }
    }
}

void MainWindow::menu()
{
    juego=false; //no se puede jugar
    musica->play(); //reproducir cancion menu
    musica->setVolume(50);
    ui->graphicsView->setBackgroundBrush(QPixmap(":/recursos/Imagenes/fondo_menu.jpg")); //selecionar fondo
    ui->boton_partida1->hide(); //esconder boton
    ui->boton_partida2->hide();//esconder boton
    ui->boton_partida3->hide();//esconder boton
    ui->boton_regresar->hide();//esconder boton
    ui->lineEdit1->hide();//esconder boton
    ui->lineEdit2->hide();//esconder boton
    ui->lineEdit3->hide();//esconder boton
    ui->boton_guardarpartida1->hide();//esconder boton
    ui->boton_guardarpartida2->hide();//esconder boton
    ui->boton_guardarpartida3->hide();//esconder boton
    ui->guardar->hide(); //esconder boton
    ui->pausar->hide();//esconder boton
    ui->label_clave->hide(); //esconder boton
    ui->label_usuario->hide(); //esconder boton
    ui->lineEdit_clave->hide(); //esconder boton
    ui->lineEdit_usuario->hide(); //esconder boton
    ui->label_inicio_de_sesion->hide(); //esconder boton
    ui->boton_ingresar->hide(); //esconder boton
    ui->boton_cancelar->hide(); //esconder boton
    ui->boton_eliminar->hide(); //esconder boton
    ui->boton_volveralmenu->hide();
    ui->label_ganador_multijugador->hide();
}

void MainWindow::nivel1()
{
    juego = true; //se puede jugar
    musica->stop();
    musica->setMedia(QUrl("qrc:/recursos/musica/musica_nivel1.mp3")); //le doy la cancion correspondiente
    ui->graphicsView->setBackgroundBrush(QPixmap(":/recursos/Imagenes/fondo_nivel1.png"));
    ui->pausar->show(); //mostrar boton
    puntos->setPuntaje(0);
    tanque1->setVelocidad(10);
    if(partida==0)
    {
        ui->guardar->hide(); //esonder boton
    }
    if(partida!=0)
    {
        ui->guardar->show(); //mostrar boton
    }
    timerfuerzaaerea->stop(); //parar el timer del nivel 2
    timerfuerzaaerea2->stop();
    timerfuerzaaerea3->stop();
    tanque1->setPosx(500); //actualizar posicion

    srand(time(NULL)); // iniciar el time para la variable aleatoria

    musgo->hide(); //esconder lodo

    //agregar personaje principal
    escena->addItem(tanque1); //agregar la chillin

    Sprite_vidas->setcolumna_fila(0,0); //actualizar columnas y filas
    escena->addItem(Sprite_vidas); //añadir spritevidas a escena
    actualizar_sprite_vidas();

    //fuerzaaerea 1
    enemy1 = new fuerzaaerea(150,-500,260,260); //creo fuerzaaerea 1
    enemy1->setImagen(2); //selecionar imagen
    enemy1->setScale(0.3);//cambiar tamaño
    fuerzaaereas.push_back(enemy1); //agrego fuerzaaerea 1 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(0)); //añado fuerzaaerea 1 a la escena

    //fuerzaaerea 2
    enemy2 = new fuerzaaerea(850,-500,260,260); //creo fuerzaaerea 2
    enemy2->setImagen(2); //seleccionar la imagen
    enemy2->setScale(0.3); //cambiar tamaño
    fuerzaaereas.push_back(enemy2); //agrego fuerzaaerea 2 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(1)); //añado fuerzaaerea 2 a la escena

    //fuerzaaerea 3
    enemy3 = new fuerzaaerea(500,-350,260,260); //creo fuerzaaerea 3
    enemy3->setImagen(2); //selecionar imagen
    enemy3->setScale(0.4); //cambiar tamaño
    fuerzaaereas.push_back(enemy3); //agrego fuerzaaerea 3 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(2)); //añado fuerzaaerea 3 a la escena

    //fuerzaaerea 4
    enemy4 = new fuerzaaerea(750,-350,260,260); //creo fuerzaaerea 4
    enemy4->setImagen(2); //sleecionar imagen
    enemy4->setScale(0.4); //cambiar tamaño
    fuerzaaereas.push_back(enemy4); //agrego fuerzaaerea 4 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(3)); //añado fuerzaaerea 4 a la escena

    //fuerzaaerea 5
    enemy5 = new fuerzaaerea(500,-170,260,260); //creo fuerzaaerea 5
    enemy5->setImagen(2); //seleccionar imagen
    enemy5->setScale(0.4); //cambiar tamaño
    fuerzaaereas.push_back(enemy5); //agrego fuerzaaerea 4 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(4)); //añado fuerzaaerea 4 a la escena

    //piso
    //escena->addItem(piso); //agregar piso

    //muro derecho
    //escena->addItem(muroderecho); //agregar muro derecho

    //muro izquierdo
    //escena->addItem(muroizquierdo); //agregar muro izquierdo

    //salud
    escena->addItem(vidas); //añadir las vidas a la escena

    //puntaje
    escena->addItem(puntos); //añadir el puntaje a la escena

    //timer para los fuerzaaereas
    connect(timerfuerzaaerea,SIGNAL(timeout()),this,SLOT(mover_enemys_level_1())); //conecto el timer al movimiento del fuerzaaerea
    //timerfuerzaaerea->start(10); //iniciar timer
}

void MainWindow::nivel2()
{
    ui->pausar->setStyleSheet("border-image:url(:/recursos/Imagenes/pausa.png);");
    musica->stop(); //parar musica
    musica->setMedia(QUrl("qrc:/recursos/musica/musica_nivel2.mp3"));
    juego = true; //activar la jugabilidad
    ui->graphicsView->setBackgroundBrush(QPixmap(":/recursos/Imagenes/fondo_nivel2.PNG"));
    ui->guardar->show(); //mostrar boton
    puntos->setPuntaje(50); //actualizar puntaje

    musgo->hide();

    if(partida==0) //condicion que pregunta si es una partida rapida o no
    {
        ui->guardar->hide(); //esonder boton
    }
    if(partida!=0) //condicion que pregunta si se cargo una partida
    {
        ui->guardar->show(); //mostrar boton
    }
    timerfuerzaaerea->stop(); //parar el timer del nivel 2
    timerfuerzaaerea2->stop();
    timerfuerzaaerea3->stop();

    srand(time(NULL)); // iniciar el time para la variable aleatoria

    fuerzaaereas.clear(); //vacias lista de fuerzaaereas

    if(!tanque1->isActive()) //condicion que pregunta si el tanque ya esta en escena
    {
        escena->addItem(tanque1); //agregar la chillin
    }
    tanque1->setPosx(10); //actualizar posicion

    if(!Sprite_vidas->isActive()) //condicion que pregunta si el sprite vidas ya esta en escena
    {
        escena->addItem(Sprite_vidas);
        Sprite_vidas->setcolumna_fila(0,0);
    }
    actualizar_sprite_vidas();

    if(!vidas->isActive()) //condicion que pregunta si vidas ya esta en escena
    {
        escena->addItem(vidas);
    }

    if(!puntos->isActive()) //condicion que pregunta si los puntos ya estan en escena
    {
        escena->addItem(puntos);
    }


    //fuerzaaerea 6
    enemy6 = new fuerzaaerea(25,-150,58,83,10,90); //creo fuerzaaerea 6
    enemy6->setImagen(1); //selecionar imagen
    enemy6->setScale(0.8);//cambiar tamaño
    fuerzaaereas.push_back(enemy6); //agrego fuerzaaerea 1 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(0)); //añado fuerzaaerea 1 a la escena

    //fuerzaaerea 7
    enemy7 = new fuerzaaerea(975,-150,58,83,10,90); //creo fuerzaaerea 7
    enemy7->setImagen(1); //seleccionar la imagen
    enemy7->setScale(0.8); //cambiar tamaño
    fuerzaaereas.push_back(enemy7); //agrego fuerzaaerea 6 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(1)); //añado fuerzaaerea 6 a la escena

    //fuerzaaerea 8
    enemy8 = new fuerzaaerea(250,-350,58,83,10,180); //creo fuerzaaerea 8
    enemy8->setImagen(1); //selecionar imagen
    enemy8->setScale(0.8); //cambiar tamaño
    fuerzaaereas.push_back(enemy8); //agrego fuerzaaerea 3 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(2)); //añado fuerzaaerea 3 a la escena

    //fuerzaaerea 9
    enemy9 = new fuerzaaerea(750,-350,58,83,10,180); //creo fuerzaaerea 9
    enemy9->setImagen(1); //sleecionar imagen
    enemy9->setScale(0.8); //cambiar tamaño
    fuerzaaereas.push_back(enemy9); //agrego fuerzaaerea 4 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(3)); //añado fuerzaaerea 4 a la escena

    //fuerzaaerea 10
    enemy10 = new fuerzaaerea(500,-350,58,83,0,0); //creo fuerzaaerea 10
    enemy10->setImagen(1); //seleccionar imagen
    enemy10->setScale(0.8); //cambiar tamaño
    fuerzaaereas.push_back(enemy10); //agrego fuerzaaerea 4 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(4)); //añado fuerzaaerea 4 a la escena

    connect(timerfuerzaaerea2,SIGNAL(timeout()),this,SLOT(mover_enemys_level_2())); //conecto el timer al movimiento del fuerzaaerea

    actualizar_puntaje(50); //funcion que detecta que el diparo haya acertado a un fuerzaaerea y actualiza el puntaje

}

void MainWindow::nivel3()
{
    ui->pausar->setStyleSheet("border-image:url(:/recursos/Imagenes/pausa.png);");
    timerfuerzaaerea2->stop();
    juego = true;

    tanque1->setVelocidad(10); //actualizar velocidad
    musica->stop();
    musica->setMedia(QUrl("qrc:/recursos/musica/musica_nivel3.mp3"));

    musgo->show(); //mostrar lodo

    ui->graphicsView->setBackgroundBrush(QPixmap(":/recursos/Imagenes/fondo_nivel3.PNG"));
    ui->guardar->show(); //mostrar boton

    puntos->setPuntaje(100);

    if(partida==0)
    {
        ui->guardar->hide(); //esonder boton
    }
    if(partida!=0)
    {
        ui->guardar->show(); //mostrar boton
    }
    timerfuerzaaerea->stop(); //parar el timer del nivel 2
    timerfuerzaaerea2->stop();
    timerfuerzaaerea3->stop();
    srand(time(NULL)); // iniciar el time para la variable aleatoria

    fuerzaaereas.clear(); //vaciar lista de fuerzaaereas

    if(!tanque1->isActive()) //condicion que pregunta si el tanque principal ya esta en escena
    {
        escena->addItem(tanque1); //agregar la chillin
    }
    tanque1->setPosx(10); //actualizar posicion

    if(!Sprite_vidas->isActive()) //condicion que pregunta si Sprite vidas ya esta en escena
    {
        escena->addItem(Sprite_vidas);
        Sprite_vidas->setcolumna_fila(0,0);
    }
    actualizar_sprite_vidas();

    if(!vidas->isActive()) //condicion que pregunta si vida ya esta en escena
    {
        escena->addItem(vidas);
    }

    if(!puntos->isActive()) //condicion que pregunta si puntos ya esta en escena
    {
        escena->addItem(puntos);
    }

    //fuerzaaerea 11
    enemy11 = new fuerzaaerea(25,-200,81,82,30,0); //creo fuerzaaerea 11
    enemy11->setImagen(4); //selecionar imagen
    enemy11->setScale(1);//cambiar tamaño
    fuerzaaereas.push_back(enemy11); //agrego fuerzaaerea 11 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(0)); //añado fuerzaaerea 11 a la escena

    //fuerzaaerea 12
    enemy12 = new fuerzaaerea(975,-200,81,82,30,180); //creo fuerzaaerea 12
    enemy12->setImagen(4); //seleccionar la imagen
    enemy12->setScale(1); //cambiar tamaño
    fuerzaaereas.push_back(enemy12); //agrego fuerzaaerea 12 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(1)); //añado fuerzaaerea 12 a la escena

    //fuerzaaerea 13
    enemy13 = new fuerzaaerea(500,-350,244,102); //creo fuerzaaerea 13
    enemy13->setImagen(3); //selecionar imagen
    enemy13->setScale(0.3); //cambiar tamaño
    fuerzaaereas.push_back(enemy13); //agrego fuerzaaerea 13 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(2)); //añado fuerzaaerea 13 a la escena

    //fuerzaaerea 14
    enemy14 = new fuerzaaerea(750,-350,244,102); //creo fuerzaaerea 14
    enemy14->setImagen(3); //sleecionar imagen
    enemy14->setScale(0.3); //cambiar tamaño
    fuerzaaereas.push_back(enemy14); //agrego fuerzaaerea 14 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(3)); //añado fuerzaaerea 14 a la escena

    //fuerzaaerea 15
    enemy15 = new fuerzaaerea(500,-170,160,260); //creo fuerzaaerea 15
    enemy15->setImagen(6); //seleccionar imagen
    enemy15->setScale(0.8); //cambiar tamaño
    fuerzaaereas.push_back(enemy15); //agrego fuerzaaerea 4 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(4)); //añado fuerzaaerea 4 a la escena

    //fuerzaaerea 16
    enemy16 = new fuerzaaerea(250,-170,260,260); //creo fuerzaaerea 16
    enemy16->setImagen(5); //seleccionar imagen
    enemy16->setScale(0.2); //cambiar tamaño
    fuerzaaereas.push_back(enemy16); //agrego fuerzaaerea 16 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(5)); //añado fuerzaaerea 16 a la escena

    //fuerzaaerea 17
    enemy17 = new fuerzaaerea(750,-170,260,260); //creo fuerzaaerea 17
    enemy17->setImagen(5); //seleccionar imagen
    enemy17->setScale(0.2); //cambiar tamaño
    fuerzaaereas.push_back(enemy17); //agrego fuerzaaerea 17 a la lista de fuerzaaereas
    escena->addItem(fuerzaaereas.at(6)); //añado fuerzaaerea 17 a la escena

    connect(timerfuerzaaerea3,SIGNAL(timeout()),this,SLOT(mover_enemys_level_3())); //conecto el timer al movimiento del fuerzaaerea

    actualizar_puntaje(100); //funcion que detecta que el diparo haya acertado a un fuerzaaerea y actualiza el puntaje

}

void MainWindow::nivel_multijugador()
{
    multijugador=true;
    juego = true; //se puede jugar
    musica->stop();
    musica->setMedia(QUrl("qrc:/recursos/musica/musica_nivel3.mp3")); //le doy la cancion correspondiente
    ui->graphicsView->setBackgroundBrush(QPixmap(":/recursos/Imagenes/fondo_multijugador.jpg"));
    puntos->setPuntaje(0);
    puntos->tiempo(0);
    tanque1->setVelocidad(10);
    Sprite_vidas->hide();
    if(partida==0)
    {
        ui->guardar->hide(); //esonder boton
    }
    if(partida!=0)
    {
        ui->guardar->show(); //mostrar boton
    }
    timerfuerzaaerea->stop(); //parar el timer del nivel 2
    timerfuerzaaerea2->stop();
    timerfuerzaaerea3->stop();
    tanque1->setPosx(475); //actualizar posicion
    musica->play();

    srand(time(NULL)); // iniciar el time para la variable aleatoria

    musgo->hide(); //esconder lodo

    //agregar personaje principal
    escena->addItem(tanque1); //agregar la chillin

    Sprite_vidas->setcolumna_fila(0,0); //actualizar columnas y filas
    escena->addItem(Sprite_vidas); //añadir spritevidas a escena

    //puntaje
    escena->addItem(puntos); //añadir el puntaje a la escena

    connect(timergenerarfuerzaaereas,SIGNAL(timeout()),this,SLOT(generar_fuerzaaereas()));
    connect(timerfuerzaaereasmultijugador,SIGNAL(timeout()),this,SLOT(mover_enemys_multiplayer()));

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(juego) //condicion que pregunta si se puede jugar o no
    {
        //tecla D
        bool D=((event->key()==Qt::Key_D && timerfuerzaaerea->isActive()) || (event->key()==Qt::Key_D && timerfuerzaaerea2->isActive()) || ((event->key()==Qt::Key_D && timerfuerzaaerea3->isActive()) || ((event->key()==Qt::Key_D && timerfuerzaaereasmultijugador ->isActive())) ));
        if(D) //condicion que pregunta si la tecla es la D y el timerfuerzaaereas esta activo
        {
            if(tanque1->getPosx()<970) //condicion que pregunta si el personaje principal esta dentro de la pantalla visible
            {
                if(musgo->isVisible()) //condicion que pregunta si el lodo es visible
                {
                    if(tanque1->collidesWithItem(musgo)) //condicion que pregunta si esta chocando con algun lodo
                    {
                        tanque1->setVelocidad(5); //actualizar velocidad
                    }
                    if(!tanque1->collidesWithItem(musgo))
                    {
                        tanque1->setVelocidad(10); //actualizar velocidad
                    }
                }
                tanque1->mover_derecha(); //mover hacia la derecha
            }
        }

        //tecla A
        bool A=((event->key()==Qt::Key_A && timerfuerzaaerea->isActive()) || (event->key()==Qt::Key_A && timerfuerzaaerea2->isActive()) || (event->key()==Qt::Key_A && timerfuerzaaerea3->isActive()) || (event->key()==Qt::Key_A && timerfuerzaaereasmultijugador->isActive()) );
        if(A) //condicion que pregunta si la tecla es la A y el timerfuerzaaereas esta activo
        {
            if(tanque1->getPosx()>25) //condicion que pregunta si el personaje principal esta dentro de la pantalla visible
            {
                if(musgo->isVisible())
                {
                    if(tanque1->collidesWithItem(musgo))
                    {
                        tanque1->setVelocidad(5);
                    }
                    if(!tanque1->collidesWithItem(musgo))
                    {
                        tanque1->setVelocidad(10);
                    }
                }

                tanque1->mover_izquierda();//mover hacia la izquierda
            }
        }

        //tecla W
        bool W=((event->key()==Qt::Key_W && timerfuerzaaerea->isActive()) || (event->key()==Qt::Key_W && timerfuerzaaerea2->isActive()) ||(event->key()==Qt::Key_W && timerfuerzaaerea3->isActive()) || (event->key()==Qt::Key_W && timerfuerzaaereasmultijugador->isActive()) );
        if(W) //condicion que pregunta si la tecla es la espacio y el timerfuerzaaereas esta activo
        {
            tanque1->Disparo(); //actualizar sprite
            balas * bala = new balas(); //crear variable bala
            bala->setPos(tanque1->getPosx()-5,tanque1->getPosy()-50); //darle la posicion del personaje principal
            bala->setScale(0.6); //cambiar tamaño
            escena->addItem(bala); //añadir bala a la escena
        }

        if(event->key()==Qt::Key_Space) //condicion que pregunta si la tecla que se oprimio fue shift
        {
            //qDebug()<<puntos->getPuntaje();
            if(!multijugador)
            {
                if(puntos->getPuntaje()<50)
                {
                    timerfuerzaaerea->start(10); //iniciar juego
                    musica->play(); //reproducir cancion nivel1
                    ui->pausar->setFocus(); //foco en el boton pausa
                }
                if(puntos->getPuntaje()>=50&&puntos->getPuntaje()<100)
                {
                    timerfuerzaaerea2->start(10); //iniciar nivel2
                    musica->play(); //reproducir cancion nivel2
                    ui->pausar->setFocus(); //foco boton pausa
                }
                if(puntos->getPuntaje()>=100)
                {
                    timerfuerzaaerea3->start(10); //iniciar nivel3
                    musica->play();
                    ui->pausar->setFocus();// foco boton pausa
                }
            }

            if(multijugador)
            {
                timergenerarfuerzaaereas->start(333);
                timerfuerzaaereasmultijugador->start(15);
            }
        }
    }
}

void MainWindow::choque(fuerzaaerea* bola)
{
    if(tanque1->collidesWithItem(bola)&&bola->isVisible()) //condicion que pregunta si hubo colision con una bola amistosa
    {

        vidas->disminuir_salud(); //disminuye las vidas
        if(vidas->getVidas()==2) //condicion que pregunta si las vidas son diferentes de 0
        {
            if(puntos->getPuntaje()<50)
            {
                tanque1->setPosx(500); //resetea la posicion de la chillin
            }
            if(puntos->getPuntaje()>=50)
            {
                tanque1->setPosx(10); //resetea la posicion de la chillin
            }
            Sprite_vidas->setcolumna_fila(50,0); //actualizar sprite
        }
        if(vidas->getVidas()==1) //condicion que pregunta si las vidas son diferentes de 0
        {
            if(puntos->getPuntaje()<50)
            {
                tanque1->setPosx(500); //resetea la posicion de la chillin
            }
            if(puntos->getPuntaje()>50)
            {
                tanque1->setPosx(10); //resetea la posicion de la chillin
            }
            Sprite_vidas->setcolumna_fila(0,50); //actualziar sprite
        }

        if(vidas->getVidas()==0) //condicion que pregunta si las vidas son iguales a 0
        {
            game_over(); //terminar juego
        }
    }
}

void MainWindow::choque_multijugador(fuerzaaerea *bola)
{
    if(tanque1->collidesWithItem(bola)&&bola->isVisible()) //condicion que pregunta si hubo colision con una bola amistosa
    {
        for(int i=0;i<fuerzaaereas.size();i++)
        {
            if(fuerzaaereas.at(i)->isVisible())
            {
                fuerzaaereas.at(i)->hide();
            }
        }
        timergenerarfuerzaaereas->stop();
        timerfuerzaaereasmultijugador->stop();
        vidas->disminuir_salud(); //disminuye las vidas
        if(vidas->getVidas()==1) //condicion que pregunta si las vidas son diferentes de 0
        {
            tanque1->setImagen(3);
            tanque1->setPosx(475); //resetea la posicion de la chillin
        }

        if(vidas->getVidas()==0) //condicion que pregunta si las vidas son iguales a 0
        {
            game_over_multijugador(); //terminar juego
        }
    }
}

void MainWindow::actualizar_puntaje(int p)
{
    for(int i=0;i<fuerzaaereas.size();i++) //ciclo que recorre la lista de los fuerzaaereas
    {
        if(!fuerzaaereas.at(i)->isVisible()) //condicion que pregunta si el fuerzaaerea no es visible
        {
            p=p+10; //suma 10 a la variable ps
        }
    }
    puntos->aumentar_puntaje(p); //da el valor de p a los puntos
}

void MainWindow::actualizar_puntaje_multijugador(int p)
{
    if(vidas->getVidas()==2)
    {
        p=0;
        for(int i=0;i<fuerzaaereas.size();i++) //ciclo que recorre la lista de los fuerzaaereas
        {
            if(!fuerzaaereas.at(i)->isVisible()) //condicion que pregunta si el fuerzaaerea no es visible
            {
                p=p+1; //suma 10 a la variable ps
            }
        }
        puntaje1=p+aux1;
        p=p+aux1;

    }
    puntos->tiempo(p); //da el valor de p a los puntos


    if(vidas->getVidas()==1)
    {
        p=0;
        for(int i=0;i<fuerzaaereas2.size();i++) //ciclo que recorre la lista de los fuerzaaereas
        {
            if(!fuerzaaereas2.at(i)->isVisible()) //condicion que pregunta si el fuerzaaerea no es visible
            {
                p=p+1; //suma 10 a la variable ps
            }
        }
        puntaje2=p+aux2;
        p=p+aux2;
    }
    puntos->tiempo(p); //da el valor de p a los puntos


}

void MainWindow::game_over()
{
    juego=false; //no hay jugabilidad
    musica->stop();
    escena->removeItem(tanque1); //elimina el personaje principal
    for(int i=0;i<fuerzaaereas.size();i++) //ciclo que recorre toda la lista de fuerzaaereas
    {
        if(fuerzaaereas.at(i)->isVisible()) //condicion que pregunta si un fuerzaaerea es visible
        {
            escena->removeItem(fuerzaaereas.at(i)); //remueve los fuerzaaereas visibles
        }
    }
    escena->removeItem(puntos); //remueve el puntaje
    escena->removeItem(vidas); //remueve las vidas
    escena->removeItem(Sprite_vidas);
    ui->pausar->hide(); //esconder boton
    timerfuerzaaerea->stop(); //parar timer de fuerzaaereas
    timerfuerzaaerea2->stop(); //parar timer de fuerzaaereas2
    timerfuerzaaerea3->stop(); //parar timer de fuerzaaereas3
    timergenerarfuerzaaereas->stop();
    timerfuerzaaereasmultijugador->stop();
    ui->guardar->hide(); //esconder boton
    ui->boton_volveralmenu->show();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/recursos/Imagenes/gameover.jpg"));
}

void MainWindow::game_over_multijugador()
{
    juego=false; //no hay jugabilidad
    musica->stop();
    escena->removeItem(tanque1); //elimina el personaje principal
    for(int i=0;i<fuerzaaereas2.size();i++) //ciclo que recorre toda la lista de fuerzaaereas
    {
        if(fuerzaaereas2.at(i)->isVisible()) //condicion que pregunta si un fuerzaaerea es visible
        {
            escena->removeItem(fuerzaaereas2.at(i)); //remueve los fuerzaaereas visibles
        }
    }
    escena->removeItem(puntos); //remueve el puntaje
    escena->removeItem(Sprite_vidas);
    ui->pausar->hide(); //esconder boton
    timerfuerzaaerea->stop(); //parar timer de fuerzaaereas
    timerfuerzaaerea2->stop(); //parar timer de fuerzaaereas2
    timerfuerzaaerea3->stop(); //parar timer de fuerzaaereas3
    timergenerarfuerzaaereas->stop();
    timerfuerzaaereasmultijugador->stop();
    ui->guardar->hide(); //esconder boton
    ui->boton_volveralmenu->show();
    ui->label_ganador_multijugador->show();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/recursos/Imagenes/fondo_multijugador_final.jpg"));
    qDebug()<<"puntaje chillin: "<<puntaje1;
    qDebug()<<"puntaje moncha:"<<puntaje2;
    if(puntaje1>puntaje2)
    {
        ui->label_ganador_multijugador->setText("JUGADOR 1: "+QString::number(puntaje1)+" - JUGADOR 2: "+QString::number(puntaje2)+'\n'+"GANADOR= "+"JUGADOR 1");
        ui->label_ganador_multijugador->adjustSize();
    }
    if(puntaje1<puntaje2)
    {
        ui->label_ganador_multijugador->setText("JUGADOR 1: "+QString::number(puntaje1)+" - JUGADOR 2: "+QString::number(puntaje2)+'\n'+"GANADOR: "+"JUGADOR 2");
        ui->label_ganador_multijugador->adjustSize();
    }
    if(puntaje1==puntaje2)
    {
        ui->label_ganador_multijugador->setText("JUGADOR 1: "+QString::number(puntaje1)+" - JUGADOR 2: "+QString::number(puntaje2)+'\n'+"EMPATE");
        ui->label_ganador_multijugador->adjustSize();
    }
    fuerzaaereas.clear();
    fuerzaaereas2.clear();
    puntaje1=0;
    puntaje2=0;
    tanque1->setImagen(0);
}

void MainWindow::borrar_todos_botones()
{
    ui->boton_partida1->hide(); //esconder boton
    ui->boton_partida2->hide();//esconder boton
    ui->boton_partida3->hide();//esconder boton
    ui->boton_regresar->hide();//esconder boton
    ui->boton_nuevapartida->hide();//esconder boton
    ui->boton_cargarpartida->hide();//esconder boton
    ui->pausar->hide();//esconder boton
    ui->lineEdit1->hide();//esconder boton
    ui->lineEdit2->hide();//esconder boton
    ui->lineEdit3->hide();//esconder boton
    ui->guardar->hide(); //esconder boton
    ui->lineEdit_clave->hide(); //esconder boton
    ui->lineEdit_usuario->hide(); //esconder boton
    ui->label_clave->hide(); //esconder boton
    ui->label_usuario->hide(); //esconder boton
    ui->label_inicio_de_sesion->hide(); //esconder boton
    ui->boton_ingresar->hide(); //esconder boton
    ui->boton_cancelar->hide(); //esconder boton
    ui->boton_eliminar->hide(); //esconder boton
    ui->boton_multijugador->hide();
    ui->label_ganador_multijugador->hide();
    ui->label_ganador_multijugador->hide();
    ui->boton_informacion->hide();
}

void MainWindow::escribir_partidasguardadas(QString texto,int p_)
{
    ui->lineEdit1->show(); //mostrar boton
    ui->lineEdit2->show();//mostrar boton
    ui->lineEdit3->show();//mostrar boton

    QFile archivo(texto); //leer el archivo
    if(!archivo.open(QFile::ReadOnly)) //condicion que pregunta si no lo pudo abrir
    {
        QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
    }
    QTextStream in(&archivo); //crear un flujo de lectura
    texto=in.readAll(); //leer todo el archivo
    QStringList lista_archivo=texto.split(QLatin1Char(',')); //crear una lista de String y agregarle los valores, cada valor viene dado separado de una coma
    archivo.close(); //cerrar archivo
    int nivel=0; //iniciar variable nivel
    name.clear();
    pass.clear();
    for(int i=0;i<lista_archivo.size();i++) //ciclo que recorre toda la lista
    {
        if(i==0){vidas->setVidas(lista_archivo.at(0).toInt());} //dar el valor de vidas
        if(i==1){nivel=lista_archivo.at(2).toInt();} //dar el valor del nivel
        if(i==2){name.append(lista_archivo.at(i));} //guardar el nombre
        if(i==3){pass.append(lista_archivo.at(i));} //guardar la contraseña
    }

    if(name=="vacio")
    {
        if(pass=="vacio")
        {
            if(p_==1)
            {
                ui->lineEdit1->setText("<VACIO>"); //escribir el texto completo de la partida 1 guardada
                ui->lineEdit1->setDisabled(true); //desabilitar escritura
                ui->lineEdit1->setFont(QFont("Trajan Pro",10)); //cambiar formto a la letra
            }

            if(p_==2)
            {
                ui->lineEdit2->setText("<VACIO>"); //escribir el texto completo de la partida 1 guardada
                ui->lineEdit2->setDisabled(true); //desabilitar escritura
                ui->lineEdit2->setFont(QFont("Trajan Pro",10)); //cambiar formto a la letra
            }
            if(p_==3)
            {
                ui->lineEdit3->setText("<VACIO>"); //escribir el texto completo de la partida 1 guardada
                ui->lineEdit3->setDisabled(true); //desabilitar escritura
                ui->lineEdit3->setFont(QFont("Trajan Pro",10)); //cambiar formto a la letra
            }
        }
    }

    if(name!="vacio")
    {
        if(pass!="vacio")
        {
            QString Texto1="Nivel: "; //crear variable string y añadir Nivel
            Texto1.append(lista_archivo.at(1)); //agregar el nivel
            Texto1.append(" Vidas: "); //agreagr Vidas:
            Texto1.append(lista_archivo.at(0)); //agregrar puntos

            if(p_==1) //condicion que pregunta si la partida abierta fue la 1
            {
                ui->lineEdit1->setText(Texto1); //escribir el texto completo de la partida 1 guardada
                ui->lineEdit1->setDisabled(true); //desabilitar escritura
                ui->lineEdit1->setFont(QFont("Trajan Pro",10)); //cambiar formto a la letra
            }
            if(p_==2) //condicion que pregunta si la partida abierta fue la 2
            {
                ui->lineEdit2->setText(Texto1); //escribir el texto completo de la partida 2 guardada
                ui->lineEdit2->setDisabled(true); //desabilitar escritura
                ui->lineEdit2->setFont(QFont("Trajan Pro",10)); //cambiar formto a la letra
            }
            if(p_==3) //condicion que pregunta si la partida abierta fue la 3
            {
                ui->lineEdit3->setText(Texto1); //escribir el texto completo de la partida 3 guardada
                ui->lineEdit3->setDisabled(true); //desabilitar escritura
                ui->lineEdit3->setFont(QFont("Trajan Pro",10)); //cambiar formto a la letra
            }
        }
    }

}

int MainWindow::leer_partidarguardadas(QString texto)
{
    QFile archivo(texto); //leer el archivo
    if(!archivo.open(QFile::ReadOnly)) //condicion que pregunta si no lo pudo abrir
    {
        QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
    }
    QTextStream in(&archivo); //crear un flujo de lectura
    texto=in.readAll(); //leer todo el archivo
    QStringList lista_archivo=texto.split(QLatin1Char(',')); //crear una lista de
    archivo.close(); //cerrar el archivo
    int nivel=0; //iniciari variable nivel
    for(int i=0;i<lista_archivo.size();i++) //ciclo que recorre toda la lista
    {
        if(i==0){vidas->setVidas(lista_archivo.at(0).toInt());} //dar el valor de vidas
        if(i==1){nivel=lista_archivo.at(1).toInt();} //dar el valor del nivel
    }
    qDebug()<<"aqui2"<<" "<<nivel;
    return nivel; //regresar el nivel
}

bool MainWindow::revisar_usuario_clave(QString texto)
{
    QFile archivo(texto); //leer el archivo
    if(!archivo.open(QFile::ReadOnly)) //condicion que pregunta si no lo pudo abrir
    {
        QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
    }
    QTextStream in(&archivo); //crear un flujo de lectura
    texto=in.readAll(); //leer todo el archivo
    QStringList lista_archivo=texto.split(QLatin1Char(',')); //crear una lista de
    archivo.close(); //cerrar el archivo

    name.clear();
    pass.clear();

    for(int i=0;i<lista_archivo.size();i++) //ciclo que recorre toda la lista
    {
        if(i==2) //condicion que pregunta si es el nombre de usuario
        {
            name.append(lista_archivo.at(i));//guardar usuario en variable
        }
        if(i==3) //condicion que pregunta si es la clave
        {
            pass.append(lista_archivo.at(i));//guardar clave en variable
        }
    }

    QString usuario=NULL; //variable que me guarda el nombre de usuario ingresado
    QString clave=NULL; //variable que me guarda la clave ingresada
    usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
    clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit

    if(clave==pass) //condicion que pregunta si la clave ingresada es igual a la guardada
    {
        if(usuario==name)//condicion que pregunta si el usuario ingresado es igual al guardado
        {
            return true; //regresa true
        }

        return false; //regresa false
    }
    else
    {
        return false; //regresa false
    }
}

void MainWindow::gano()
{
    timerfuerzaaerea3->stop(); //parar timer fuerzaaereas 3
    juego=false; //no hay jugabilidad
    musica->stop();
    escena->removeItem(tanque1); //elimina el personaje principal
    for(int i=0;i<fuerzaaereas.size();i++) //ciclo que recorre toda la lista de fuerzaaereas
    {
        if(fuerzaaereas.at(i)->isVisible()) //condicion que pregunta si un fuerzaaerea es visible
        {
            escena->removeItem(fuerzaaereas.at(i)); //remueve los fuerzaaereas visibles
        }
    }
    escena->removeItem(puntos); //remueve el puntaje
    escena->removeItem(vidas); //remueve las vidas
    escena->removeItem(Sprite_vidas); //remueve el sprite vidas
    ui->guardar->hide(); //esconder boton
    ui->pausar->hide(); //esconder boton
    ui->boton_volveralmenu->show();
    ui->graphicsView->setBackgroundBrush(QPixmap(":/recursos/Imagenes/you_did_it.jpg"));
}

void MainWindow::actualizar_sprite_vidas()
{
    if(vidas->getVidas()==3) //condicion que pregunta si las vidas son diferentes de 0
    {
        Sprite_vidas->setcolumna_fila(0,0); //actualizar sprite
    }

    if(vidas->getVidas()==2) //condicion que pregunta si las vidas son diferentes de 0
    {
        Sprite_vidas->setcolumna_fila(50,0); //actualizar sprite
    }

    if(vidas->getVidas()==1) //condicion que pregunta si las vidas son diferentes de 0
    {
        Sprite_vidas->setcolumna_fila(0,50); //actualizar sprite
    }
}

void MainWindow::on_boton_nuevapartida_clicked()
{
    multijugador=false;
    musica->stop(); //para cancion menu
    tanque1->setPosx(10);
    vidas->setVidas(3); //dar 3 vidas
    puntos->setPuntaje(0); //dar un puntaje de 0
    borrar_todos_botones(); // borrar todos los botones
    ui->pausar->show(); //mostrar boton pausa
    partida=0;
    nivel2(); // ir a funcion nivel1
}

void MainWindow::on_boton_cargarpartida_clicked()
{
    multijugador=false;
    ui->boton_cargarpartida->hide(); //esconde boton cargar partida
    ui->boton_nuevapartida->hide(); //esconde boton nueeva partida
    ui->boton_partida1->show(); //muestra boton partida1
    ui->boton_partida2->show(); //muestra boton partida2
    ui->boton_partida3->show(); //muestra boton partida3
    ui->boton_regresar->show(); //muestra boton regresar
    ui->boton_multijugador->hide();
    escribir_partidasguardadas("partida1.txt",1); //escribe en pantalla los datos guardados de la partida 1
    escribir_partidasguardadas("partida2.txt",2); //escribe en pantalla los datos guardados de la partida 2
    escribir_partidasguardadas("partida3.txt",3); //escribe en pantalla los datos guardados de la partida 3
}

void MainWindow::on_boton_regresar_clicked()
{
    ui->boton_nuevapartida->show(); //mostrar boton nueva partida
    ui->boton_cargarpartida->show(); //mostar boton cargar partida
    ui->boton_multijugador->show();
    ui->boton_informacion->show();
    ui->lineEdit_usuario->setText("");
    ui->lineEdit_clave->setText("");
    menu(); //ir a funcion menu
}

void MainWindow::on_boton_partida1_clicked()
{
    partida=1; //partida 1
    ui->boton_partida2->hide(); //esconder boton
    ui->boton_partida3->hide(); //esconder boton
    ui->lineEdit2->hide(); //esconder boton
    ui->lineEdit3->hide(); //esconder boton
    ui->lineEdit_clave->show(); //mostrar boton
    ui->lineEdit_usuario->show(); //mostrar boton
    ui->label_clave->show(); //mostrar boton
    ui->label_usuario->show(); //mostrar boton
    ui->label_inicio_de_sesion->show(); //mostrar boton
    ui->boton_ingresar->show(); //mostrar boton
    ui->boton_cancelar->show(); //mostrar boton
    ui->boton_eliminar->show(); //mostrar boton
}

void MainWindow::on_boton_partida2_clicked()
{
    partida = 2; //partida 2
    ui->boton_partida1->hide(); //esconder boton
    ui->boton_partida3->hide(); //esconder boton
    ui->lineEdit1->hide(); //esconder boton
    ui->lineEdit3->hide(); //esconder boton
    ui->lineEdit_clave->show(); //mostrar boton
    ui->lineEdit_usuario->show(); //mostrar boton
    ui->label_clave->show(); //mostrar boton
    ui->label_usuario->show(); //mostrar boton
    ui->label_inicio_de_sesion->show(); //mostrar boton
    ui->boton_ingresar->show(); //mostrar boton
    ui->boton_cancelar->show(); //mostrar boton
    ui->boton_eliminar->show(); //mostrar boton
}

void MainWindow::on_boton_partida3_clicked()
{
    partida = 3; //partida 3
    ui->boton_partida1->hide(); //esconder boton
    ui->boton_partida2->hide(); //esconder boton
    ui->lineEdit1->hide(); //esconder boton
    ui->lineEdit2->hide(); //esconder boton
    ui->lineEdit_clave->show(); //mostrar boton
    ui->lineEdit_usuario->show(); //mostrar boton
    ui->label_clave->show(); //mostrar boton
    ui->label_usuario->show(); //mostrar boton
    ui->label_inicio_de_sesion->show(); //mostrar boton
    ui->boton_ingresar->show(); //mostrar boton
    ui->boton_cancelar->show(); //mostrar boton
    ui->boton_eliminar->show(); //mostrar boton
}

void MainWindow::on_pausar_clicked()
{
    if(puntos->getPuntaje()<50)
    {
        if(timerfuerzaaerea->isActive()) //condicion que pregunta si el timer esta activo
        {
            timerfuerzaaerea->stop(); //parar el timer
            musica->pause(); //pausar cancion
            juego = false; //para jugabilidad
            ui->pausar->setFocus(); //dejar el teclado en el boton pausa
            ui->pausar->setStyleSheet("border-image:url(:/recursos/Imagenes/play.png);");
            ui->boton_volveralmenu->show();
        }

        else if(!timerfuerzaaerea->isActive()) //condicion que pregunta si el timer esta activo
        {
            timerfuerzaaerea->start(10); //iniciar el timer
            musica->play(); //reproducir
            juego = true; //habilitar la jugabilidad
            ui->pausar->setFocus(); //dejar el teclado en el boton pausa
            ui->pausar->setStyleSheet("border-image:url(:/recursos/Imagenes/pausa.png);");
            ui->boton_volveralmenu->hide();
        }
    }

    if(puntos->getPuntaje()>=50&&puntos->getPuntaje()<100)
    {
        if(timerfuerzaaerea2->isActive()) //condicion que pregunta si el timer esta activo
        {
            timerfuerzaaerea2->stop(); //parar el timer
            musica->pause(); //pasuar cancion
            juego = false; //para jugabilidad
            ui->pausar->setFocus(); //dejar el teclado en el boton pausa
            ui->pausar->setStyleSheet("border-image:url(:/recursos/Imagenes/play.png);");
            ui->boton_volveralmenu->show();
        }

        else if(!timerfuerzaaerea2->isActive()) //condicion que pregunta si el timer esta activo
        {
            timerfuerzaaerea2->start(10); //iniciar el timer
            musica->play(); //reproducir cancion
            juego = true; //habilitar la jugabilidad
            ui->pausar->setFocus(); //dejar el teclado en el boton pausa
            ui->pausar->setStyleSheet("border-image:url(:/recursos/Imagenes/pausa.png);");
            ui->boton_volveralmenu->hide();
        }
    }

    if(puntos->getPuntaje()>=100)
    {
        if(timerfuerzaaerea3->isActive()) //condicion que pregunta si el timer esta activo
        {
            timerfuerzaaerea3->stop(); //parar el timer
            musica->pause();
            juego = false; //para jugabilidad
            ui->pausar->setFocus(); //dejar el teclado en el boton pausa
            ui->pausar->setStyleSheet("border-image:url(:/recursos/Imagenes/play.png);");
            ui->boton_volveralmenu->show();
        }

        else if(!timerfuerzaaerea3->isActive()) //condicion que pregunta si el timer esta activo
        {
            timerfuerzaaerea3->start(10); //iniciar el timer
            musica->play();
            juego = true; //habilitar la jugabilidad
            ui->pausar->setFocus(); //dejar el teclado en el boton pausa
            ui->pausar->setStyleSheet("border-image:url(:/recursos/Imagenes/pausa.png);");
            ui->boton_volveralmenu->hide();
        }
    }

}

void MainWindow::on_guardar_clicked()
{
    timerfuerzaaerea->stop(); //parar timer
    timerfuerzaaerea2->stop(); //parar timer
    timerfuerzaaerea3->stop(); //parar timer
//    escena->addItem(escogerpartida);
//    escogerpartida->texto("Donde desea guardar partida?");
//    ui->boton_guardarpartida1->show(); //mostrar boton
//    ui->boton_guardarpartida2->show(); //mostrar boton
//    ui->boton_guardarpartida3->show(); //mostrar boton

    if(partida==1) //condicion que pregunta si la partida es la 1
    {
        int nivel=0; //variable que me controla el nivel
        if(puntos->getPuntaje()<50) //condicion que pregunta si el puntaje es menor a 50
        {
            nivel=1; //nivel 1
        }
        if(puntos->getPuntaje()>=50 && puntos->getPuntaje()<100) //condicion que pregunta si el puntaje esta entre 50 y 90
        {
            nivel=2; //nivel 2
        }
        if(puntos->getPuntaje()>=100) //condicion que pregunta si el puntaje es mayor o igual a 100
        {
            nivel=3; //nivel 3
        }

        QString v=QString::number(vidas->getVidas()); //convertir las vidas a string
        QString n=QString::number(nivel); //convertir el nivel a string
        QString texto; //variable string
        texto.append(v); //agregar las vidas
        texto.append(","); //agregar coma
        texto.append(n); //agregar nivel
        texto.append(","); //agregar coma
        texto.append(name); //agregar usuario
        texto.append(","); //agregar coma
        texto.append(pass); //agregar contraseña

        QFile archivo("partida1.txt"); //leer el archivo
        if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }

        QTextStream out(&archivo); //flujo de escritura
        out<<texto; //escribir sobre el archivo
        archivo.flush(); //cerrar procesos sobre archivo
        archivo.close(); //cerrar archivo
        QMessageBox::information(this,"Guardar partida","partida guardada exitosamente");
        ui->pausar->setFocus(); //dar el focus a el boton pausa
    }

    if(partida==2) //condicion que pregunta si la partida es la 2
    {
        int nivel=0; //variable que me controla el nivel
        if(puntos->getPuntaje()<50) //condicion que pregunta si el puntaje es menor a 50
        {
            nivel=1; //nivel 1
        }
        if(puntos->getPuntaje()>=50 && puntos->getPuntaje()<100) //condicion que pregunta si el puntaje esta entre 50 y 90
        {
            nivel=2; //nivel 2
        }
        if(puntos->getPuntaje()>=100) //condicion que pregunta si el puntaje es mayor o igual a 100
        {
            nivel=3; //nivel 3
        }

        QString v=QString::number(vidas->getVidas()); //convertir las vidas a string
        QString n=QString::number(nivel); //convertir el nivel a string
        QString texto; //variable string
        texto.append(v); //agregar las vidas
        texto.append(","); //agregar coma
        texto.append(n); //agregar nivel
        texto.append(","); //agregar coma
        texto.append(name); //agregar usuario
        texto.append(","); //agregar coma
        texto.append(pass); //agregar contraseña

        QFile archivo("partida2.txt"); //leer el archivo
        if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }

        QTextStream out(&archivo); //flujo de escritura
        out<<texto; //escribir sobre el archivo
        archivo.flush(); //cerrar procesos sobre archivo
        archivo.close(); //cerrar archivo
        QMessageBox::information(this,"Guardar partida","partida guardada exitosamente");
        ui->pausar->setFocus(); //dar el focus a el boton pausa
    }

    if(partida==3) //condicion que pregunta si la partida es la 3
    {
        int nivel=0; //variable que me controla el nivel
        if(puntos->getPuntaje()<50) //condicion que pregunta si el puntaje es menor a 50
        {
            nivel=1; //nivel 1
        }
        if(puntos->getPuntaje()>=50 && puntos->getPuntaje()<100) //condicion que pregunta si el puntaje esta entre 50 y 90
        {
            nivel=2; //nivel 2
        }
        if(puntos->getPuntaje()>=100) //condicion que pregunta si el puntaje es mayor o igual a 100
        {
            nivel=3; //nivel 3
        }

        QString v=QString::number(vidas->getVidas()); //convertir las vidas a string
        QString n=QString::number(nivel); //convertir el nivel a string
        QString texto; //variable string
        texto.append(v); //agregar las vidas
        texto.append(","); //agregar coma
        texto.append(n); //agregar nivel
        texto.append(","); //agregar coma
        texto.append(name); //agregar usuario
        texto.append(","); //agregar coma
        texto.append(pass); //agregar contraseña

        QFile archivo("partida3.txt"); //leer el archivo
        if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }

        QTextStream out(&archivo); //flujo de escritura
        out<<texto; //escribir sobre el archivo
        archivo.flush(); //cerrar procesos sobre archivo
        archivo.close(); //cerrar archivo
        QMessageBox::information(this,"Guardar partida","partida guardada exitosamente");
        ui->pausar->setFocus(); //dar el focus a el boton pausa
    }
}

void MainWindow::on_boton_guardarpartida1_clicked()
{
    int nivel=0; //variable que me controla el nivel
    if(puntos->getPuntaje()<50) //condicion que pregunta si el puntaje es menor a 50
    {
        nivel=1; //nivel 1
    }
    if(puntos->getPuntaje()>=50 && puntos->getPuntaje()<100) //condicion que pregunta si el puntaje esta entre 50 y 90
    {
        nivel=2; //nivel 2
    }
    if(puntos->getPuntaje()>=100) //condicion que pregunta si el puntaje es mayor o igual a 100
    {
        nivel=3; //nivel 3
    }

    QString v=QString::number(vidas->getVidas()); //convertir las vidas a string
    QString n=QString::number(nivel); //convertir el nivel a string
    QString texto; //variable string
    texto.append(v); //agregar las vidas
    texto.append(","); //agregar coma
    texto.append(n); //agregar nivel

    QFile archivo("partida1.txt"); //leer el archivo
    if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
    {
        QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
    }

    QTextStream out(&archivo); //flujo de escritura
    out<<texto; //escribir sobre el archivo
    archivo.flush(); //cerrar procesos sobre archivo
    archivo.close(); //cerrar archivo

    ui->boton_guardarpartida1->hide(); //esconder boton
    ui->boton_guardarpartida2->hide(); //esconder boton
    ui->boton_guardarpartida3->hide(); //esconder boton
    escogerpartida->hide(); //esconder texto
    QMessageBox::information(this,"Guardar partida","partida guardada exitosamente");
    ui->pausar->setFocus(); //dar el focus a el boton pausa
}

void MainWindow::on_boton_guardarpartida2_clicked()
{
    int nivel=0; //variable que me controla el nivel
    if(puntos->getPuntaje()<50) //condicion que pregunta si el puntaje es menor a 50
    {
        nivel=1; //nivel 1
    }
    if(puntos->getPuntaje()>=50 && puntos->getPuntaje()<100) //condicion que pregunta si el puntaje esta entre 50 y 90
    {
        nivel=2; //nivel 2
    }
    if(puntos->getPuntaje()>=100) //condicion que pregunta si el puntaje es mayor o igual a 100
    {
        nivel=3; //nivel 3
    }

    QString v=QString::number(vidas->getVidas()); //convertir las vidas a string
    QString n=QString::number(nivel); //convertir el nivel a string
    QString texto; //variable string
    texto.append(v); //agregar las vidas
    texto.append(","); //agregar coma
    texto.append(","); //agregar coma
    texto.append(n); //agregar nivel

    QFile archivo("partida2.txt"); //leer el archivo
    if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
    {
        QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
    }

    QTextStream out(&archivo); //flujo de escritura
    out<<texto; //escribir sobre el archivo
    archivo.flush(); //cerrar procesos sobre archivo
    archivo.close(); //cerrar archivo

    ui->boton_guardarpartida1->hide(); //esconder boton
    ui->boton_guardarpartida2->hide(); //esconder boton
    ui->boton_guardarpartida3->hide(); //esconder boton
    escogerpartida->hide(); //esconder texto
    QMessageBox::information(this,"Guardar partida","partida guardada exitosamente");
    ui->pausar->setFocus(); //dar el focus a el boton pausa
}

void MainWindow::on_boton_guardarpartida3_clicked()
{
    int nivel=0; //variable que me controla el nivel
    if(puntos->getPuntaje()<50) //condicion que pregunta si el puntaje es menor a 50
    {
        nivel=1; //nivel 1
    }
    if(puntos->getPuntaje()>=50 && puntos->getPuntaje()<100) //condicion que pregunta si el puntaje esta entre 50 y 90
    {
        nivel=2; //nivel 2
    }
    if(puntos->getPuntaje()>=100) //condicion que pregunta si el puntaje es mayor o igual a 100
    {
        nivel=3; //nivel 3
    }

    QString v=QString::number(vidas->getVidas()); //convertir las vidas a string
    QString n=QString::number(nivel); //convertir el nivel a string
    QString texto; //variable string
    texto.append(v); //agregar las vidas
    texto.append(","); //agregar coma
    texto.append(","); //agregar coma
    texto.append(n); //agregar nivel

    QFile archivo("partida3.txt"); //leer el archivo
    if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
    {
        QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
    }

    QTextStream out(&archivo); //flujo de escritura
    out<<texto; //escribir sobre el archivo
    archivo.flush(); //cerrar procesos sobre archivo
    archivo.close(); //cerrar archivo

    ui->boton_guardarpartida1->hide(); //esconder boton
    ui->boton_guardarpartida2->hide(); //esconder boton
    ui->boton_guardarpartida3->hide(); //esconder boton
    escogerpartida->hide(); //esconder texto
    QMessageBox::information(this,"Guardar partida","partida guardada exitosamente");
    ui->pausar->setFocus(); //dar el focus a el boton pausa
}

void MainWindow::on_boton_ingresar_clicked()
{
    if(partida==1) //condicion que pregunta si se selecciono la partida1
    {
        QString direccion="partida1.txt";
        QString texto;
        QFile archivo(direccion); //leer el archivo
        if(!archivo.open(QFile::ReadOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }
        QTextStream in(&archivo); //crear un flujo de lectura
        texto=in.readAll(); //leer todo el archivo
        QStringList lista_archivo=texto.split(QLatin1Char(',')); //crear una lista de
        archivo.flush();
        archivo.close(); //cerrar el archivo

        name.clear();
        pass.clear();

        for(int i=0;i<lista_archivo.size();i++) //ciclo que recorre toda la lista
        {
            if(i==2) //condicion que pregunta si es el nombre de usuario
            {
                name.append(lista_archivo.at(i));//guardar usuario en variable
            }
            if(i==3) //condicion que pregunta si es la clave
            {
                pass.append(lista_archivo.at(i));//guardar clave en variable
            }
        }

        if(name=="vacio")
        {
            QString usuario; //variable que me guarda el nombre de usuario ingresado
            QString clave; //variable que me guarda la clave ingresada
            usuario.clear();
            clave.clear();
            usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
            clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit
            QString Texto1; //variable string
            Texto1.append("3"); //agregar las vidas
            Texto1.append(","); //agregar coma
            Texto1.append("1"); //agregar nivel
            Texto1.append(","); //agregar coma
            Texto1.append(usuario); //agregar usuario
            Texto1.append(","); //agregar coma
            Texto1.append(clave); //agregar contraseña

            QFile archivo(direccion); //leer el archivo
            if(!archivo.open(QFile::WriteOnly | QFile::Text)) //condicion que pregunta si no lo pudo abrir
            {
                QMessageBox::warning(this,"UUYYYY :V","NO ABRE EL ARCHIVO PARA ESCRIBIR"); //mensaje que dice que no se pudo leer
            }
            QTextStream out(&archivo); //flujo de escritura
            out<<Texto1; //escribir sobre el archivo
            archivo.flush(); //cerrar procesos sobre archivo
            archivo.close(); //cerrar archivo
            QMessageBox::information(this,"Crear usuario","usuario creado exitosamente");
        }

        if(revisar_usuario_clave(direccion)) //condicion que pregunta si se ingreso correctamente la clave y el usuario
        {
            qDebug()<<"aqui1";
            if(leer_partidarguardadas(direccion)==1) //pregunta si el nivel es 1
            {
                borrar_todos_botones(); //borrar todos los botones
                ui->pausar->show(); //mostrar boton pausa
                nivel1(); //ir a funcion nivel1
            }
            if(leer_partidarguardadas(direccion)==2) //condicion que pregunta si el nivel es 2
            {
                borrar_todos_botones(); //borrar botones
                ui->pausar->show(); //mostrar boton pausa
                nivel2(); // ir a funcion nivel2
            }
            if(leer_partidarguardadas(direccion)==3) //condicion que pregunta si el nivel es 3
            {
                borrar_todos_botones(); //borrar todos los botones
                ui->pausar->show(); //mostrar boton pausa
                nivel3(); //ir a funcion nivel 3
            }
        }
        if(!revisar_usuario_clave(direccion))
        {
            QMessageBox::information(this,"incorrecto","clave o usuario equivocado");
        }
    }

    if(partida==2) //condicion que pregunta si se selecciono la partida1
    {
        QString direccion="partida2.txt";
        QString texto;
        QFile archivo(direccion); //leer el archivo
        if(!archivo.open(QFile::ReadOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }
        QTextStream in(&archivo); //crear un flujo de lectura
        texto=in.readAll(); //leer todo el archivo
        QStringList lista_archivo=texto.split(QLatin1Char(',')); //crear una lista de
        archivo.flush();
        archivo.close(); //cerrar el archivo

        name.clear();
        pass.clear();

        for(int i=0;i<lista_archivo.size();i++) //ciclo que recorre toda la lista
        {
            if(i==3) //condicion que pregunta si es el nombre de usuario
            {
                name.append(lista_archivo.at(i));//guardar usuario en variable
            }
            if(i==4) //condicion que pregunta si es la clave
            {
                pass.append(lista_archivo.at(i));//guardar clave en variable
            }
        }

        if(name=="vacio")
        {
            QString usuario; //variable que me guarda el nombre de usuario ingresado
            QString clave; //variable que me guarda la clave ingresada
            usuario.clear();
            clave.clear();
            usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
            clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit
            QString Texto1; //variable string
            Texto1.append("3"); //agregar las vidas
            Texto1.append(","); //agregar coma
            Texto1.append("1"); //agregar nivel
            Texto1.append(","); //agregar coma
            Texto1.append(usuario); //agregar usuario
            Texto1.append(","); //agregar coma
            Texto1.append(clave); //agregar contraseña

            QFile archivo(direccion); //leer el archivo
            if(!archivo.open(QFile::WriteOnly | QFile::Text)) //condicion que pregunta si no lo pudo abrir
            {
                QMessageBox::warning(this,"UUYYYY :V","NO ABRE EL ARCHIVO PARA ESCRIBIR"); //mensaje que dice que no se pudo leer
            }
            QTextStream out(&archivo); //flujo de escritura
            out<<Texto1; //escribir sobre el archivo
            archivo.flush(); //cerrar procesos sobre archivo
            archivo.close(); //cerrar archivo
            QMessageBox::information(this,"Crear usuario","usuario creado exitosamente");
        }

        if(revisar_usuario_clave(direccion)) //condicion que pregunta si se ingreso correctamente la clave y el usuario
        {
            if(leer_partidarguardadas(direccion)==1) //pregunta si el nivel es 1
            {
                borrar_todos_botones(); //borrar todos los botones
                ui->pausar->show(); //mostrar boton pausa
                nivel1(); //ir a funcion nivel1
            }
            if(leer_partidarguardadas(direccion)==2) //condicion que pregunta si el nivel es 2
            {
                borrar_todos_botones(); //borrar botones
                ui->pausar->show(); //mostrar boton pausa
                nivel2(); // ir a funcion nivel2
            }
            if(leer_partidarguardadas(direccion)==3) //condicion que pregunta si el nivel es 3
            {
                borrar_todos_botones(); //borrar todos los botones
                ui->pausar->show(); //mostrar boton pausa
                nivel3(); //ir a funcion nivel 3
            }
        }
        if(!revisar_usuario_clave(direccion))
        {
            QMessageBox::information(this,"incorrecto","clave o usuario equivocado");
        }
    }

    if(partida==3) //condicion que pregunta si se selecciono la partida1
    {
        QString direccion="partida3.txt";
        QString texto;
        QFile archivo(direccion); //leer el archivo
        if(!archivo.open(QFile::ReadOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }
        QTextStream in(&archivo); //crear un flujo de lectura
        texto=in.readAll(); //leer todo el archivo
        QStringList lista_archivo=texto.split(QLatin1Char(',')); //crear una lista de
        archivo.flush();
        archivo.close(); //cerrar el archivo

        name.clear();
        pass.clear();

        for(int i=0;i<lista_archivo.size();i++) //ciclo que recorre toda la lista
        {
            if(i==3) //condicion que pregunta si es el nombre de usuario
            {
                name.append(lista_archivo.at(i));//guardar usuario en variable
            }
            if(i==4) //condicion que pregunta si es la clave
            {
                pass.append(lista_archivo.at(i));//guardar clave en variable
            }
        }

        if(name=="vacio")
        {
            QString usuario; //variable que me guarda el nombre de usuario ingresado
            QString clave; //variable que me guarda la clave ingresada
            usuario.clear();
            clave.clear();
            usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
            clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit
            QString Texto1; //variable string
            Texto1.append("3"); //agregar las vidas
            Texto1.append(","); //agregar coma
            Texto1.append("1"); //agregar nivel
            Texto1.append(","); //agregar coma
            Texto1.append(usuario); //agregar usuario
            Texto1.append(","); //agregar coma
            Texto1.append(clave); //agregar contraseña

            QFile archivo(direccion); //leer el archivo
            if(!archivo.open(QFile::WriteOnly | QFile::Text)) //condicion que pregunta si no lo pudo abrir
            {
                QMessageBox::warning(this,"UUYYYY :V","NO ABRE EL ARCHIVO PARA ESCRIBIR"); //mensaje que dice que no se pudo leer
            }
            QTextStream out(&archivo); //flujo de escritura
            out<<Texto1; //escribir sobre el archivo
            archivo.flush(); //cerrar procesos sobre archivo
            archivo.close(); //cerrar archivo
            QMessageBox::information(this,"Crear usuario","usuario creado exitosamente");
        }

        if(revisar_usuario_clave(direccion)) //condicion que pregunta si se ingreso correctamente la clave y el usuario
        {
            if(leer_partidarguardadas(direccion)==1) //pregunta si el nivel es 1
            {
                borrar_todos_botones(); //borrar todos los botones
                ui->pausar->show(); //mostrar boton pausa
                nivel1(); //ir a funcion nivel1
            }
            if(leer_partidarguardadas(direccion)==2) //condicion que pregunta si el nivel es 2
            {
                borrar_todos_botones(); //borrar botones
                ui->pausar->show(); //mostrar boton pausa
                nivel2(); // ir a funcion nivel2
            }
            if(leer_partidarguardadas(direccion)==3) //condicion que pregunta si el nivel es 3
            {
                borrar_todos_botones(); //borrar todos los botones
                ui->pausar->show(); //mostrar boton pausa
                nivel3(); //ir a funcion nivel 3
            }
        }
        if(!revisar_usuario_clave(direccion))
        {
            QMessageBox::information(this,"incorrecto","clave o usuario equivocado");
        }
    }

    ui->lineEdit_usuario->setText("");
    ui->lineEdit_clave->setText("");
}

void MainWindow::on_boton_cancelar_clicked()
{
    ui->label_clave->hide(); //esconder boton
    ui->label_usuario->hide(); //esconder boton
    ui->lineEdit_clave->hide(); //esconder boton
    ui->lineEdit_usuario->hide(); //esconder boton
    ui->label_inicio_de_sesion->hide(); //esconder boton
    ui->boton_ingresar->hide(); //esconder boton
    ui->boton_cancelar->hide(); //esconder boton
    ui->boton_eliminar->hide(); //esoncer boton
    if(partida==1) //condicion que pregunta si se habia seleccionado la partida 1
    {
        ui->lineEdit2->show(); //mostrar boton
        ui->lineEdit3->show(); //mostrar boton
        ui->boton_partida2->show(); //mostrar boton
        ui->boton_partida3->show(); //mostrar boton
    }
    if(partida==2) //condicion que pregunta si se habia seleccionado la partida 2
    {
        ui->lineEdit1->show(); //mostrar boton
        ui->lineEdit3->show(); //mostrar boton
        ui->boton_partida1->show(); //mostrar boton
        ui->boton_partida3->show(); //mostrar boton
    }
    if(partida==3) //condicion que pregunta si se habia seleccionado la partida 3
    {
        ui->lineEdit2->show(); //mostrar boton
        ui->lineEdit1->show(); //mostrar boton
        ui->boton_partida2->show(); //mostrar boton
        ui->boton_partida1->show(); //mostrar boton
    }

    ui->lineEdit_usuario->setText("");
    ui->lineEdit_clave->setText("");
}

void MainWindow::on_boton_eliminar_clicked()
{
    if(partida==1)
    {
        QString usuario=NULL; //variable que me guarda el nombre de usuario ingresado
        QString clave=NULL; //variable que me guarda la clave ingresada
        usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
        clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit
        QString texto; //variable string
        texto.append("3"); //agregar las vidas
        texto.append(","); //agregar coma
        texto.append("1"); //agregar nivel
        texto.append(","); //agregar coma
        texto.append("vacio"); //agregar usuario
        texto.append(","); //agregar coma
        texto.append("vacio"); //agregar contraseña

        QFile archivo("partida1.txt"); //leer el archivo
        if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }

        QTextStream out(&archivo); //flujo de escritura
        out<<texto; //escribir sobre el archivo
        archivo.flush(); //cerrar procesos sobre archivo
        archivo.close(); //cerrar archivo
        QMessageBox::information(this,"Borrar usuario","usuario borrado exitosamente");
    }

    if(partida==2)
    {
        QString usuario=NULL; //variable que me guarda el nombre de usuario ingresado
        QString clave=NULL; //variable que me guarda la clave ingresada
        usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
        clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit
        QString texto; //variable string
        texto.append("3"); //agregar las vidas
        texto.append(","); //agregar coma
        texto.append("1"); //agregar nivel
        texto.append(","); //agregar coma
        texto.append("vacio"); //agregar usuario
        texto.append(","); //agregar coma
        texto.append("vacio"); //agregar contraseña

        QFile archivo("partida2.txt"); //leer el archivo
        if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }

        QTextStream out(&archivo); //flujo de escritura
        out<<texto; //escribir sobre el archivo
        archivo.flush(); //cerrar procesos sobre archivo
        archivo.close(); //cerrar archivo
        QMessageBox::information(this,"Borrar usuario","usuario borrado exitosamente");
    }

    if(partida==3)
    {
        QString usuario=NULL; //variable que me guarda el nombre de usuario ingresado
        QString clave=NULL; //variable que me guarda la clave ingresada
        usuario.append(ui->lineEdit_usuario->text()); //tomar texto del lineEdit
        clave.append(ui->lineEdit_clave->text()); //tomar texto del lineEdit
        QString texto; //variable string
        texto.append("3"); //agregar las vidas
        texto.append(","); //agregar coma
        texto.append("1"); //agregar nivel
        texto.append(","); //agregar coma
        texto.append("vacio"); //agregar usuario
        texto.append(","); //agregar coma
        texto.append("vacio"); //agregar contraseña

        QFile archivo("partida3.txt"); //leer el archivo
        if(!archivo.open(QFile::WriteOnly)) //condicion que pregunta si no lo pudo abrir
        {
            QMessageBox::warning(this,"UUYYYY :V","ERROR AL ABRIR EL ARCHIVO"); //mensaje que dice que no se pudo leer
        }

        QTextStream out(&archivo); //flujo de escritura
        out<<texto; //escribir sobre el archivo
        archivo.flush(); //cerrar procesos sobre archivo
        archivo.close(); //cerrar archivo
        QMessageBox::information(this,"Borrar usuario","usuario borrado exitosamente");
    }

    ui->boton_regresar->click();

}

void MainWindow::on_boton_volveralmenu_clicked()
{
    if(tanque1->isActive())
    {
        escena->removeItem(tanque1); //elimina el personaje principal
    }
    for(int i=0;i<fuerzaaereas.size();i++) //ciclo que recorre toda la lista de fuerzaaereas
    {
        if(fuerzaaereas.at(i)->isVisible()) //condicion que pregunta si un fuerzaaerea es visible
        {
            escena->removeItem(fuerzaaereas.at(i)); //remueve los fuerzaaereas visibles
        }
    }
    if(puntos->isActive())
    {
        escena->removeItem(puntos); //remueve el puntaje
    }
    if(vidas->isActive())
    {
        escena->removeItem(vidas); //remueve las vidas
    }
    if(Sprite_vidas->isActive())
    {
        escena->removeItem(Sprite_vidas); //remueve el sprite vidas
    }
    ui->boton_nuevapartida->show(); //mostrar boton nueva partida
    ui->boton_cargarpartida->show(); //mostar boton cargar partida
    ui->boton_multijugador->show();
    ui->label_ganador_multijugador->hide();
    ui->boton_informacion->show();

    timerfuerzaaerea->stop();
    timerfuerzaaerea2->stop();
    timerfuerzaaerea3->stop();
    timergenerarfuerzaaereas->stop();
    timerfuerzaaereasmultijugador->stop();
    delete timerfuerzaaerea;
    delete timerfuerzaaerea2;
    delete timerfuerzaaerea3;
    delete timergenerarfuerzaaereas;
    delete timerfuerzaaereasmultijugador;
    timerfuerzaaerea = new QTimer;
    timerfuerzaaerea2 = new QTimer;
    timerfuerzaaerea3 = new QTimer;
    timergenerarfuerzaaereas = new QTimer;
    timerfuerzaaereasmultijugador = new QTimer;
    partida=0;
    fuerzaaereas.clear();
    musica->setMedia(QUrl("qrc:/recursos/musica/musica_menu.mp3"));
    menu(); //ir a funcion menu
}

void MainWindow::on_boton_multijugador_clicked()
{
    musica->stop(); //para cancion menu
    tanque1->setPosx(10);
    vidas->setVidas(2); //dar 2 vidas
    puntos->setPuntaje(0); //dar un puntaje de 0
    borrar_todos_botones(); // borrar todos los botones
    ui->pausar->hide(); //mostrar boton pausa
    partida=0;
    ui->boton_multijugador->hide();
    fuerzaaereas.clear();
    fuerzaaereas2.clear();
    nivel_multijugador();
}

void MainWindow::generar_fuerzaaereas()
{

    if(vidas->getVidas()==2)
    {
        actualizar_puntaje_multijugador(puntaje1);
        //fuerzaaerea 1
        int largo=0;
        int ancho=0;
        double escala=0;
        int x = rand() % 1000;
        int imagen=1+rand()%(6-1);

        if(imagen==1)
        {
            largo=56;
            ancho=82;
            escala=0.6;
        }
        if(imagen==2)
        {
            largo=260;
            ancho=260;
            escala=0.2;
        }
        if(imagen==3)
        {
            largo=117;
            ancho=260;
            escala=0.4;
        }

        if(imagen==4)
        {
            largo=81;
            ancho=82;
            escala=0.6;
        }
        if(imagen==5)
        {
            largo=260;
            ancho=260;
            escala=0.2;
        }
        fuerzaaereas.push_back(new fuerzaaerea(x,10,largo,ancho,0,0)); //creo fuerzaaerea 1); //agrego fuerzaaerea 1 a la lista de fuerzaaereas
        fuerzaaereas.back()->setImagen(imagen);
        fuerzaaereas.back()->setScale(escala);
        if(imagen==4)
        {
            fuerzaaereas.back()->setColumnas_fila(0,82);
        }
        if(imagen==1)
        {
            fuerzaaereas.back()->setColumnas_fila(0,82);
        }
        escena->addItem(fuerzaaereas.back());
    }

    if(vidas->getVidas()==1)
    {
        actualizar_puntaje_multijugador(puntaje2);
        //fuerzaaerea 1
        int largo=0;
        int ancho=0;
        double escala=0;
        int x = rand() % 1000;
        int imagen=1+rand()%(6-1);

        if(imagen==1)
        {
            largo=81;
            ancho=82;
            escala=0.6;
        }
        if(imagen==2)
        {
            largo=260;
            ancho=260;
            escala=0.2;
        }
        if(imagen==3)
        {
            largo=260;
            ancho=260;
            escala=0.2;
        }

        if(imagen==4)
        {
            largo=81;
            ancho=82;
            escala=0.6;
        }
        if(imagen==5)
        {
            largo=260;
            ancho=260;
            escala=0.2;
        }
        fuerzaaereas2.push_back(new fuerzaaerea(x,10,largo,ancho,0,0)); //creo fuerzaaerea 1); //agrego fuerzaaerea 1 a la lista de fuerzaaereas
        fuerzaaereas2.back()->setImagen(imagen);
        fuerzaaereas2.back()->setScale(escala);
        if(imagen==4)
        {
            fuerzaaereas2.back()->setColumnas_fila(0,82);
        }
        if(imagen==1)
        {
            fuerzaaereas2.back()->setColumnas_fila(0,82);
        }
        escena->addItem(fuerzaaereas2.back());
    }

}

void MainWindow::on_boton_informacion_clicked()
{
    ui->graphicsView->setBackgroundBrush(QPixmap(":/recursos/Imagenes/informacion.jpg"));
    borrar_todos_botones();
    ui->boton_regresar->show();
}
