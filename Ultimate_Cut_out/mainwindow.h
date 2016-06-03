#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDir>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QObject>
#include <QFileDialog>
#include <iostream>
#include <QImage>
#include <QLabel>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QImage* greyScale(QImage* origin);

public slots:
    void chooseFile();

private:
    Ui::MainWindow *ui;
    QString fileName;
    QLabel * gifImage = new QLabel;
    QImage* originalImage=new QImage;//original image
    QImage* greyScaleImage=new QImage;//greyscaled image

};




#endif // MAINWINDOW_H
