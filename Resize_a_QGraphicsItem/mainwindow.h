#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //QLabel* mouse_position = new QLabel;

private:
    Ui::MainWindow *ui;

public slots:
    //void showMousePosition(QPoint& pos);
};

#endif // MAINWINDOW_H
