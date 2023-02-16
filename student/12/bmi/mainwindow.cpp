#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <string.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_countButton_clicked()
{
    qDebug() << weight_ << " " << height_/100;
    double index = weight_ / ((height_/100) * (height_/100));

    QString text = "";
    if(index < 18.5)
    {
        text = "You are underweight.";
    }
    else if(index > 25)
    {
        text = "You are overweight.";
    }
    else
    {
        text = "Your weight is normal.";
    }

    ui->resultLabel->setText(QString::number(index));
    ui->infoTextBrowser->setText(text);
}

void MainWindow::on_weightLineEdit_editingFinished()
{
    weight_ = ui->weightLineEdit->text().toDouble();
}

void MainWindow::on_heightLineEdit_editingFinished()
{
    height_ = ui->heightLineEdit->text().toDouble();
}

void MainWindow::on_weightLineEdit_textChanged(const QString &arg1)
{
    weight_ = arg1.toDouble();
}

void MainWindow::on_heightLineEdit_textChanged(const QString &arg1)
{
    height_ = arg1.toDouble();
}
