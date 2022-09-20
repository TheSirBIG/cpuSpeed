#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Windows.h"
extern "C" {
#include "powrprof.h"
}
#pragma comment(lib, "powrprof.lib")


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainTimer = new QTimer(this);
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(onMainTimer()));
}

MainWindow::~MainWindow()
{
    mainTimer->stop();
    delete mainTimer;

    delete ui;
}

void MainWindow::onMainTimer()
{
    static int qq = 0;
    //update timer
    this->ui->buttonStart->setText(QString::number(qq));
    qq++;
}


void MainWindow::on_buttonStart_released()
{
    mainTimer->setInterval(500);
    mainTimer->start();
}

void MainWindow::on_stopButton_released()
{
    mainTimer->stop();
}
