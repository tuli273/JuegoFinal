QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    balas.cpp \
    fuerzaaerea.cpp \
    main.cpp \
    mainwindow.cpp \
    puntaje.cpp \
    salud.cpp \
    tanque.cpp

HEADERS += \
    balas.h \
    fuerzaaerea.h \
    mainwindow.h \
    puntaje.h \
    salud.h \
    tanque.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    recursos.qrc

DISTFILES += \
    recursos/Imagenes/1.png \
    recursos/Imagenes/2.png \
    recursos/Imagenes/3.png \
    recursos/Imagenes/Logo.png \
    recursos/Imagenes/VACIO.png \
    recursos/Imagenes/abejorro.png \
    recursos/Imagenes/back.png \
    recursos/Imagenes/bala.png \
    recursos/Imagenes/bruja.png \
    recursos/Imagenes/calavera.png \
    recursos/Imagenes/fondo_menu.jpg \
    recursos/Imagenes/fondo_multijugador.jpg \
    recursos/Imagenes/fondo_multijugador_final.jpg \
    recursos/Imagenes/fondo_nivel1.png \
    recursos/Imagenes/fondo_nivel2.PNG \
    recursos/Imagenes/fondo_nivel3.PNG \
    recursos/Imagenes/gameover.jpg \
    recursos/Imagenes/guardar.png \
    recursos/Imagenes/guardian.png \
    recursos/Imagenes/image (2).png \
    recursos/Imagenes/image (2).png \
    recursos/Imagenes/image (3).png \
    recursos/Imagenes/image (3).png \
    recursos/Imagenes/image (4).png \
    recursos/Imagenes/image (4).png \
    recursos/Imagenes/informacion.jpg \
    recursos/Imagenes/informacion.png \
    recursos/Imagenes/jefe_final.png \
    recursos/Imagenes/load_game.png \
    recursos/Imagenes/multiplayer.png \
    recursos/Imagenes/new_game.png \
    recursos/Imagenes/pausa.png \
    recursos/Imagenes/personaje_principal.png \
    recursos/Imagenes/personaje_secundario.png \
    recursos/Imagenes/play.png \
    recursos/Imagenes/sprite_vidas.png \
    recursos/Imagenes/super_guardian.png
