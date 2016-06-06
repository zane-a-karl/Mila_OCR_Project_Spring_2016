#include "screenshot.h"
#include "ui_screenshot.h"

#include <QLabel>
#include <QTimer>
#include <QDir>
#include <QDesktopWidget>
#include <QFileDialog>
#include <iostream>
#include <QRect>
#include <QSize>
#include <QPainter>

/**
 * @brief Screenshot::Screenshot
 */
Screenshot::Screenshot()
{
    screenshotLabel = new QLabel;
    screenshotLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    screenshotLabel->setAlignment(Qt::AlignCenter);
    screenshotLabel->setMinimumSize(240, 160);

    createOptionsGroupBox();
    createButtonsLayout();

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(screenshotLabel);
    mainLayout->addWidget(optionsGroupBox);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    delaySpinBox->setValue(5);

    setWindowTitle(tr("Screenshot"));
    resize(300, 200);
}

/**
 * @brief Screenshot::resizeEvent
 */
void Screenshot::resizeEvent(QResizeEvent * /* event */)
{
    QSize scaledSize = originalPixmap.size();
    scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);
    if (!screenshotLabel->pixmap() || scaledSize != screenshotLabel->pixmap()->size())
        updateScreenshotLabel();
}

/**
 * @brief Screenshot::newScreenshot
 */
void Screenshot::newScreenshot()
{
    if (hideThisWindowCheckBox->isChecked())
    {
        hide();
    }
    newScreenshotButton->setDisabled(true);

    QTimer::singleShot(delaySpinBox->value() * 1000
                       , this, SLOT(shootScreen()));
}

/**
 * @brief Screenshot::saveScreenshot
 */
void Screenshot::saveScreenshot()
{
    QString format = "png";
    QString initialPath = QDir::currentPath()
            + tr("/untitled.") + format;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(format.toUpper())
                               .arg(format));
    if (!fileName.isEmpty())
        originalPixmap.save(fileName, format.toAscii());
}

/**
 * @brief Screenshot::shootScreen
 */
void Screenshot::shootScreen()
{
    if (delaySpinBox->value() != 0)
    {
        qApp->beep();
    }

    click1->setX(gripper->x());
    click1->setY(gripper->y());
    click2->setX(gripper->x() + gripper->boundingRect().width());
    click2->setY(gripper->y() + gripper->boundingRect().height());
    double x_diff = click2->rx() - click1->rx();
    double y_diff = click2->ry() - click1->ry();

    std::cout << "these are top left and bottom right corrds for rect " << std::endl;
    std::cout << click1->rx() << "  " << click1->ry() << std::endl;
    std::cout << click2->rx() << "  " << click2->ry() << std::endl;
    originalPixmap = QPixmap::grabWidget(label
                                         , click1->rx()
                                         , click1->ry()
                                         , x_diff
                                         , y_diff);
    updateScreenshotLabel();

    newScreenshotButton->setDisabled(false);
    if (hideThisWindowCheckBox->isChecked())
    {
        show();
    }
}

/**
 * @brief Screenshot::updateCheckBox
 */
void Screenshot::updateCheckBox()
{
    if (delaySpinBox->value() == 0)
    {
        hideThisWindowCheckBox->setDisabled(true);
        hideThisWindowCheckBox->setChecked(false);
    }
    else
    {
        hideThisWindowCheckBox->setDisabled(false);
    }
}

/**
 * @brief Screenshot::createOptionsGroupBox
 */
void Screenshot::createOptionsGroupBox()
{
    optionsGroupBox = new QGroupBox(tr("Options"));

    delaySpinBox = new QSpinBox;
    delaySpinBox->setSuffix(tr(" s"));
    delaySpinBox->setMaximum(60);
    connect(delaySpinBox, SIGNAL(valueChanged(int)), this, SLOT(updateCheckBox()));

    delaySpinBoxLabel = new QLabel(tr("Screenshot Delay:"));

    hideThisWindowCheckBox = new QCheckBox(tr("Hide This Window"));

    optionsGroupBoxLayout = new QGridLayout;
    optionsGroupBoxLayout->addWidget(delaySpinBoxLabel, 0, 0);
    optionsGroupBoxLayout->addWidget(delaySpinBox, 0, 1);
    optionsGroupBoxLayout->addWidget(hideThisWindowCheckBox, 1, 0, 1, 2);
    optionsGroupBox->setLayout(optionsGroupBoxLayout);
}

/**
 * @brief Screenshot::createButtonsLayout
 */
void Screenshot::createButtonsLayout()
{
    newScreenshotButton = createButton(tr("New Screenshot"), this, SLOT(newScreenshot()));

    saveScreenshotButton = createButton(tr("Save Screenshot"), this, SLOT(saveScreenshot()));

    quitScreenshotButton = createButton(tr("Quit"), this, SLOT(close()));

    buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(newScreenshotButton);
    buttonsLayout->addWidget(saveScreenshotButton);
    buttonsLayout->addWidget(quitScreenshotButton);
}

/**
 * @brief Screenshot::createButton
 * @param text
 * @param receiver
 * @param member
 * @return
 */
QPushButton *Screenshot::createButton(const QString &text, QWidget *receiver,
                                      const char *member)
{
    QPushButton *button = new QPushButton(text);
    button->connect(button, SIGNAL(clicked()), receiver, member);
    return button;
}

/**
 * @brief Screenshot::updateScreenshotLabel
 */
void Screenshot::updateScreenshotLabel()
{
    screenshotLabel->setPixmap(originalPixmap/*.scaled(screenshotLabel->size(),
                                                     Qt::KeepAspectRatio,
                                                     Qt::SmoothTransformation)*/);
}
