/* DT079G Project - Forrest Jump game
 *  Amarildo Rajta 2023-01-07 */
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Game.h"
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent),
    ui(new Ui::MainWindow){
    setFixedSize(800,600);
    auto label = new QLabel(this);
    QPixmap pixmap(":/images/resources/forrestjump.png");
    label->setPixmap(pixmap);
    label->setFixedSize(pixmap.size());
    label->setAlignment(Qt::AlignCenter);
    label->setScaledContents(true);
    label->move(200,50);

    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_pushButton_clicked(){
    auto game = new Game();
    game->show();
    this->close();
}

