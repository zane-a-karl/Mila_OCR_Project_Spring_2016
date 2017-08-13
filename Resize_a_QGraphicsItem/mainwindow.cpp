#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "SizeGripItem.h"
#include <QLabel>

namespace
{
    class RectResizer : public SizeGripItem::Resizer
    {
        public:
            virtual void operator()(QGraphicsItem* item, const QRectF& rect)
            {
                QGraphicsRectItem* rectItem =
                    dynamic_cast<QGraphicsRectItem*>(item);

                if (rectItem)
                {
                    rectItem->setRect(rect);
                }
            }
    };

    class EllipseResizer : public SizeGripItem::Resizer
    {
        public:
            virtual void operator()(QGraphicsItem* item, const QRectF& rect)
            {
                QGraphicsEllipseItem* ellipseItem =
                    dynamic_cast<QGraphicsEllipseItem*>(item);

                if (ellipseItem)
                {
                    ellipseItem->setRect(rect);
                }
            }
    };
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QGraphicsScene* scene = new QGraphicsScene;

    QLabel* lab = new QLabel("Hey");
    scene->addWidget(lab);
    //QMouseEvent* c1;
    //QMouseEvent* c2;
    //int width = c2->x() - c1->x();
    //int height = c2->y() - c1->y();;

    //QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF(c1->x(), c1->y(), width, height));
    QGraphicsRectItem* rectItem = new QGraphicsRectItem(QRectF(0, 0, 320, 240));
    rectItem->setBrush(Qt::gray);
    rectItem->setOpacity( 0.15 );
    rectItem->setPen(Qt::NoPen);
    rectItem->setFlag(QGraphicsItem::ItemIsMovable);
    scene->addItem(rectItem);


    SizeGripItem* rectSizeGripItem = new SizeGripItem(new RectResizer, rectItem);

    QGraphicsView* graphicsView = new QGraphicsView(this);
    graphicsView->setScene(scene);

    setCentralWidget(graphicsView);

    //connect(mouse_position, SIGNAL(sendMousePosition(QPoint&)), this, SLOT(showMousePosition(QPoint&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::showMousePosition(QPoint &pos)
//{

    //this->mouse_position->setText("x: " + QString::number(pos.x()) + ", y: " + QString::number(pos.y()));
    //this->setCentralWidget(mouse_position);
    //mouse_position->show();
//}
