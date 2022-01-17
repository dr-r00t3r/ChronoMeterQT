#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <list>
#include <QList>
#include <QStandardItemModel>
#include <QSerialPort>
#include <QIODevice>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTimer *timer;
    QTime *time;
    QSerialPort mSerialInput;
//    QSerialPort mSerialOutput;
public:
    MainWindow(QWidget *parent = nullptr);
    void initializeSerialPort();
    void startListenerGate();
    void updateUIByInputSignal();
    void closeSerialPort();
    ~MainWindow();
public slots:
    void timerHit();
private slots:
    void readDataInput();
//    void readDataOutput();
    void writeDataInput(const QByteArray &data);
    void clearAll();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
