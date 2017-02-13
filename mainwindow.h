#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QLineEdit>
#include <QColorDialog>
#include <QFontDialog>
#include <QGraphicsLineItem>
#include <QGraphicsWidget>
#include <QGridLayout>
#include <QSlider>
#include <QRect>
#include <QSpinBox>

#include "plansview.h"
#include "plansscene.h"
#include "camera.h"
#include "wicket.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    PlansView *view;
    PlansScene *scene;

    QLineEdit *leX0;
    QLineEdit *leY0;
    QLineEdit *leX1;
    QLineEdit *leY1;
    QLineEdit *leWidth;
    QLineEdit *leText;

    QPushButton *pbPen;
    QPushButton *pbBorderPen;
    QPushButton *pbFont;

    QButtonGroup *bgType;

    QRadioButton *rbType1;
    QRadioButton *rbType2;
    QRadioButton *rbType3;
    QRadioButton *rbType4;

    QSlider *sOpacity;

    QPushButton *pbAddWall;
    QPushButton *pbAddWicket;
    QPushButton *pbAddCamera;
    QPushButton *pbAddText;
    QPushButton *pbAddWidget;
    QPushButton *pbAddZone;

    QWidget *wWall;
    QWidget *wWicket;
    QWidget *wCamera;
    QWidget *wText;
    QWidget *wWidget;
    QWidget *wZone;

    QGridLayout *glWall;
    QGridLayout *glWicket;
    QGridLayout *glCamera;
    QGridLayout *glZone;
    QGridLayout *glText;
    QGridLayout *glWidget;

    QTabWidget *TabWidget;

    QColorDialog  *cdPen;
    QColorDialog  *cdPenBorder;

    QFontDialog *fdFont;

    QWidget *myWidget;

    QSpinBox *sbRotateView;
    QDoubleSpinBox *dsbScaleView;

    qreal Opacity = 1;
    /*QRect r1 =
            QRect((leX0->text()).toInt() * scene->StepLine,
             (leY0->text()).toInt() * scene->StepLine,
             (leX1->text()).toInt() * scene->StepLine,
             (leY1->text()).toInt() * scene->StepLine);*/

private slots:

    void AddWall();
    void AddWicket();
    void AddCamera();
    void AddZone();
    void AddText();
    void AddWidget();
    void SetOpacity();
    void CreateTool();
    void SetRotateView();
    void SetScaleView();
};

#endif // MAINWINDOW_H
