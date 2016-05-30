#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
     QImage * newImage = new QImage(origin->width(), origin->height(), QImage::Format_ARGB32);

      QRgb * line;

      for(int y = 0; y<newImage->height(); y++){
         line = (QRgb *)origin->scanLine(y);

        for(int x = 0; x<newImage->width(); x++){
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
    fileName = QFileDialog::getOpenFileName(this,tr("open file"),"C:/",tr("Allfile(*.*)"));//open a dialog
    if(!fileName.isNull())//if a file is selected, do something
    {
           originalImage->load(fileName);
           greyScaleImage=greyScale(originalImage);
           gifImage->setPixmap(QPixmap::fromImage(*greyScaleImage));
           gifImage->show();
    }
    else{
        std::cout<<"fail to open file"<<std::endl;
    }

}
