/*! \author Amarildo Rajta \date 2023-01-07
 *  \details DT079G Project - Forrest Jump game */
//! \file
//! \code main.cpp

#include "mainwindow.h"
#include "Game.h"

#include <QApplication>

Game* game;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //game = new Game();
    //game->show();

    return a.exec();
}

//! \endcode
