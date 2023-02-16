#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QColor>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lcdNumberMin->display(min);
    ui->lcdNumberSec->display(sec);

    ui->lcdNumberMin->setAutoFillBackground(true);
    ui->lcdNumberSec->setAutoFillBackground(true);
    ui->lcdNumberMin->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumberSec->setSegmentStyle(QLCDNumber::Flat);

    QPalette paletteMin = ui->lcdNumberMin->palette();
    paletteMin.setColor(QPalette::Normal, QPalette::Window, QColor(247, 215, 215));
    ui->lcdNumberMin->setPalette(paletteMin);
    ui->lcdNumberSec->setPalette(paletteMin);

    connect(timer, &QTimer::timeout, this, &MainWindow::update);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    ++sec;
    if(sec == 60)
    {
        ++min;
        sec = 0;
    }
    ui->lcdNumberMin->display(min);
    ui->lcdNumberSec->display(sec);
}

void MainWindow::on_startButton_clicked()
{
    if(not timer->isActive())
    {
        timer->start(1000);
    }
}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}

void MainWindow::on_resetButton_clicked()
{
    sec = 0;
    min = 0;
    ui->lcdNumberMin->display(min);
    ui->lcdNumberSec->display(sec);
}
