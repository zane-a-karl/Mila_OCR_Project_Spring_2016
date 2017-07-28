#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "screenshot.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "SizeGripItem.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFrame>
#include <QGridLayout>
#include <iostream>
#include <QPoint>
#include <QPointF>
/**
 *
 */
namespace
{
    class RectResizer : public SizeGripItem::Resizer
    {
        public:
            virtual void operator()(QGraphicsItem* item, const QRectF& rect)
            {
                QGraphicsRectItem* rectItem = dynamic_cast<QGraphicsRectItem*>(item);
                if (rectItem)
                {
                    rectItem->setRect(rect);
                }
            }
    };
}
/**
 * @brief MainWindow::MainWindow
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QWidget* main_window=new QWidget;//create a central widget
    QHBoxLayout *button_layout=new QHBoxLayout;//create a layout

    QPushButton* openFileButton=new QPushButton;//create a button
    openFileButton->setText("Choose File");//choose file
    QObject::connect(openFileButton,SIGNAL(clicked()),this,SLOT(chooseFile()));

    button_layout->addWidget(openFileButton);//add button to layout
    main_window->setLayout(button_layout);//add layout to widget
    this->setCentralWidget(main_window);//set central widget
}
/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*turn a image to greyscale image
 * @param QImage* origin[original image]
 * return pointer pointing to the image
*/
 QImage* MainWindow::greyScale(QImage* origin)
 {
     QImage * newImage = new QImage(origin->width()
                                    , origin->height()
                                    , QImage::Format_ARGB32);
      QRgb * line;

      for(int y = 0; y<newImage->height(); y++)
      {
         line = (QRgb *)origin->scanLine(y);

        for(int x = 0; x<newImage->width(); x++)
        {
          int average = (qRed(line[x]) + qGreen(line[x]) + qRed(line[x]))/3;
          newImage->setPixel(x,y, qRgb(average, average, average));
        }

      }

      return newImage;
 }

 /*choose a image file
*/
void MainWindow::chooseFile()
{
    fileName = QFileDialog::getOpenFileName(this
                                            ,tr("open file"),"C:/"
                                            ,tr("Allfile(*.*)"));//open a dialog
    if(!fileName.isNull())//if a file is selected, do something
    {
        originalImage->load(fileName);
        greyScaleImage=greyScale(originalImage);
        gifImage->setPixmap(QPixmap::fromImage(*greyScaleImage));

        QPoint* c1 = new QPoint(gifImage->x()+25,gifImage->y()+25);
        QPoint* c2 = new QPoint(c1->rx()+300,c1->ry()+300);



        //SizeGrip stuff
        QGraphicsScene* scene = new QGraphicsScene;
        scene->addPixmap(*(gifImage->pixmap()));



        QGraphicsView* graphicsView = new QGraphicsView(this);
        graphicsView->setScene(scene);
        gview = graphicsView;
        gscene = scene;

        this->setCentralWidget(graphicsView);
        this->setFixedSize(500,500);
        this->move(0,0);

        QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF(10, 10, 300, 150));
        rectItem->setBrush(Qt::gray);
        rectItem->setOpacity( 0.15 );
        rectItem->setPen(Qt::NoPen);
        rectItem->setFlag(QGraphicsItem::ItemIsMovable);
        scene->addItem(rectItem);

        SizeGripItem* rectSizeGripItem = new SizeGripItem(new RectResizer, rectItem);


        //Screenshot stuff
        Screenshot* screen = new Screenshot();
        screen->set_label(gifImage);

        c1 = new QPoint(rectItem->x(),rectItem->y());
        c2 = new QPoint(rectItem->x() + rectItem->rect().width()
                        , rectItem->y() + rectItem->rect().height());

        QPoint c1_viewpoint = graphicsView->mapFromGlobal(*c1);
        QPointF c1_scenepoint = graphicsView->mapToScene(c1_viewpoint);
        QPoint c2_viewpoint = graphicsView->mapFromGlobal(*c2);
        QPointF c2_scenepoint = graphicsView->mapToScene(c2_viewpoint);
        c1->setX(c1_scenepoint.toPoint().rx());
        c1->setY(c1_scenepoint.toPoint().ry());
        c2->setX(c2_scenepoint.toPoint().rx());
        c2->setY(c2_scenepoint.toPoint().ry());

        screen->set_click1(c1);
        screen->set_click2(c2);
        screen->set_gripper(rectItem);
        screen->move(QPoint(600,0));
        screen->show();
    }
    else
    {
        std::cout<<"fail to open file"<<std::endl;
    }
}
