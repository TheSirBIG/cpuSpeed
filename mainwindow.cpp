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
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    num_of_cpu = si.dwNumberOfProcessors;
    this->ui->plainTextEdit->appendPlainText(QString::number(num_of_cpu));
//    ppi = new std::vector<PROCESSOR_POWER_INFORMATION>(num_of_cpu);
    ppi = new PROCESSOR_POWER_INFORMATION[num_of_cpu];
    ppi_size = sizeof(PROCESSOR_POWER_INFORMATION) * num_of_cpu;
}

MainWindow::~MainWindow()
{
    mainTimer->stop();
    delete mainTimer;
    delete ppi;

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

void MainWindow::on_pushButton_released()
{
//    CallNtPowerInformation(POWER_INFORMATION_LEVEL::ProcessorInformation, NULL, 0, ppi, ppi_size);
    CallNtPowerInformation(POWER_INFORMATION_LEVEL::ProcessorInformation, NULL, 0, &ppi[0], ppi_size);
    for(int i=0; i>num_of_cpu; i++)
    {
//        this->ui->plainTextEdit->appendPlainText(QString::number(ppi->at(i).CurrentMhz));
        this->ui->plainTextEdit->appendPlainText(QString::number(ppi[i].CurrentMhz));
    }
}
