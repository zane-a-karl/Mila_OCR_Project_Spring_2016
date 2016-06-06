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
#include <QMouseEvent>
#include <QPoint>
#include <QGraphicsView>

/**
 *
 */
namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QImage* greyScale(QImage* origin);

protected:
    void mousePressEvent(QMouseEvent* e){
        QPoint mouse_pos = e->pos();
        QPoint mp_viewpoint = gview->mapFromGlobal(mouse_pos);
        QPointF mp_scenepoint = gview->mapToScene(mp_viewpoint);
        mouse_pos.setX(mp_scenepoint.toPoint().rx());
        mouse_pos.setY(mp_scenepoint.toPoint().ry());
        std::cout << mouse_pos.x() << " " << mouse_pos.y() << std::endl;
    }

public slots:
    void chooseFile();

private:
    Ui::MainWindow *ui;
    QString fileName;
    QLabel * gifImage = new QLabel;
    QImage* originalImage=new QImage;//original image
    QImage* greyScaleImage=new QImage;//greyscaled image
    QGraphicsView* gview = new QGraphicsView;
    QGraphicsScene* gscene = new QGraphicsScene;
};

#endif // MAINWINDOW_H
