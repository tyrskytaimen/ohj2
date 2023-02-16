#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <fstream>

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


void MainWindow::on_findPushButton_clicked()
{
    filename = ui->fileLineEdit->text();
    word = ui->keyLineEdit->text();
    read_file();
}

void MainWindow::read_file()
{
    std::ifstream file(filename.toStdString());
    if(not file)
    {
        QString str = "File not found";
        ui->textBrowser->setText(str);
        return;
    }
    else if(word.size() == 0)
    {
        QString str = "File found";
        ui->textBrowser->setText(str);
        return;
    }

    bool word_found = false;
    std::string line = "";
    while(getline(file, line))
    {
        if(not ui->matchCheckBox->isChecked())
        {
            for(char& c : line)
            {
                c = tolower(c);
            }
            word = word.toLower();
        }
        if(line.find(word.toStdString()) != std::string::npos)
        {
            QString str = "Word found";
            ui->textBrowser->setText(str);
            word_found = true;
            return;
        }
    }
    file.close();
    if(not word_found)
    {
        QString str = "Word not found";
        ui->textBrowser->setText(str);
    }
}
