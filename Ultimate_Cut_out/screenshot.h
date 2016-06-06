#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QPushButton>
#include <QPixmap>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPoint>
#include <QMainWindow>
//#include "sizegripitem.h"
#include <QGraphicsRectItem>

/**
 * @brief The Screenshot class
 */
class Screenshot : public QWidget
{
    Q_OBJECT

public:
    Screenshot();

    void set_click1(QPoint* c1){
        click1 = c1;
    }

    void set_click2(QPoint* c2){
        click2 = c2;
    }

    void set_label(QLabel* lab){
        label = lab;
    }
    void set_gripper(QGraphicsRectItem* gri){
        gripper = gri;
    }

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void newScreenshot();
    void saveScreenshot();
    void shootScreen();
    void updateCheckBox();

private:

    void createOptionsGroupBox();
    void createButtonsLayout();
    QPushButton *createButton(const QString &text, QWidget *receiver, const char *member);
    void updateScreenshotLabel();

    QPixmap originalPixmap;

    QLabel *screenshotLabel;
    QGroupBox *optionsGroupBox;
    QSpinBox *delaySpinBox;
    QLabel *delaySpinBoxLabel;
    QCheckBox *hideThisWindowCheckBox;
    QPushButton *newScreenshotButton;
    QPushButton *saveScreenshotButton;
    QPushButton *quitScreenshotButton;

    QVBoxLayout *mainLayout;
    QGridLayout *optionsGroupBoxLayout;
    QHBoxLayout *buttonsLayout;

    QPoint* click1;
    QPoint* click2;
    QLabel* label;
    QGraphicsRectItem* gripper;
};

#endif
