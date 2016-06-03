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

        QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF(0, 0, 320, 240));
        rectItem->setBrush(Qt::gray);
        rectItem->setOpacity( 0.15 );
        rectItem->setPen(Qt::NoPen);
        rectItem->setFlag(QGraphicsItem::ItemIsMovable);
        scene->addItem(rectItem);

        SizeGripItem* rectSizeGripItem = new SizeGripItem(new RectResizer, rectItem);

        QGraphicsView* graphicsView = new QGraphicsView(this);
        graphicsView->setScene(scene);

        this->setCentralWidget(graphicsView);

        //Screenshot stuff
        Screenshot* screen = new Screenshot();
        screen->set_label(gifImage);
        screen->set_gripper(rectItem);
        c1 = new QPoint(rectItem->x(),rectItem->y());
        c2 = new QPoint(rectItem->x() + rectItem->rect().width()
                        , rectItem->y() + rectItem->rect().height());


        screen->set_click1(c1);
        screen->set_click2(c2);

        screen->show();
    }
    else
    {
        std::cout<<"fail to open file"<<std::endl;
    }
}
