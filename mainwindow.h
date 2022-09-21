#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Windows.h"

typedef struct _PROCESSOR_POWER_INFORMATION {
    ULONG  Number;
    ULONG  MaxMhz;
    ULONG  CurrentMhz;
    ULONG  MhzLimit;
    ULONG  MaxIdleState;
    ULONG  CurrentIdleState;
} PROCESSOR_POWER_INFORMATION, * PPROCESSOR_POWER_INFORMATION;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTimer *mainTimer;
//    std::vector<PROCESSOR_POWER_INFORMATION> *ppi;
    PROCESSOR_POWER_INFORMATION *ppi;
    int ppi_size;
    int num_of_cpu;

private slots:
    void onMainTimer();
    void on_buttonStart_released();
    void on_stopButton_released();
    void on_pushButton_released();
};
#endif // MAINWINDOW_H
