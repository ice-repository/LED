#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow;

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(QObject *o){
        m_MainWindow = (MainWindow *)o;
    }

 private:
    void run();
    MainWindow *m_MainWindow;
    void snake(unsigned long, int, int);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *e);

private:
    Ui::MainWindow *ui;
    MyThread *m_thread;
};

#endif // MAINWINDOW_H
