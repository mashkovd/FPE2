#include "mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QToolBox>
#include <QLabel>
#include <QWidget>
#include <QRadioButton>
#include <QtDebug>
#include <QGraphicsLineItem>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Окна ввода параметров
    wWall = new QWidget(this);
    glWall = new QGridLayout(wWall);

    wWicket = new QWidget(this);
    glWicket = new QGridLayout(wWicket);

    wCamera = new QWidget(this);
    glCamera = new QGridLayout(wCamera);

    wText = new QWidget(this);
    glText = new QGridLayout(wText);

    wWidget = new QWidget(this);
    glWidget = new QGridLayout(wWidget);

    wZone = new QWidget(this);
    glZone = new QGridLayout(wZone);

    // Элементы ввода

    // Координаты примитива
    leX0 = new QLineEdit(this);
    leX0->setPlaceholderText("X0");
    leX0->setAlignment(Qt::AlignRight);

    leY0 = new QLineEdit(this);
    leY0->setPlaceholderText("Y0");
    leY0->setAlignment(Qt::AlignRight);

    leX1 = new QLineEdit(this);
    leX1->setPlaceholderText("X1");
    leX1->setAlignment(Qt::AlignRight);

    leY1 = new QLineEdit(this);
    leY1->setPlaceholderText("Y1");
    leY1->setAlignment(Qt::AlignRight);

    // Вводимый текст
    leText = new QLineEdit(this);
    leText->setPlaceholderText("Введите текст");
    leText->hide();

    // шрифт текста
    pbFont = new QPushButton("Шрифт текста",this);
    fdFont  = new QFontDialog(this);
    fdFont->setWindowTitle("Выбор шрифта");
    connect(pbFont, SIGNAL(pressed()), fdFont, SLOT(show()));
    fdFont->setWindowModality(Qt::WindowModal);
    fdFont->setOption(QFontDialog::NoButtons);

    pbFont->hide();
    fdFont->hide();



    // Ширина примитива
    leWidth = new QLineEdit(this);
    leWidth->setPlaceholderText("Ширина");
    leWidth->setAlignment(Qt::AlignRight);

    // Тип примитива
    rbType1 = new QRadioButton("Турникет", this);
    rbType2 = new QRadioButton("Калитка", this);
    rbType3 = new QRadioButton("Роторный", this);
    rbType4 = new QRadioButton();

    rbType4->hide();
    rbType1->hide();
    rbType2->hide();
    rbType3->hide();

    bgType = new QButtonGroup();
    bgType->addButton(rbType1);
    bgType->addButton(rbType2);
    bgType->addButton(rbType3);
    bgType->addButton(rbType4);

    //Цвет заливки и границы
    pbPen = new QPushButton("цвет заливки",this);
    cdPen = new QColorDialog(this);
    cdPen->setModal(Qt::WindowModal);
    cdPen->setWindowTitle("Выбор цвета заливки");
    cdPen->hide();
    connect(pbPen, SIGNAL(pressed()), cdPen, SLOT(show()));

    pbBorderPen = new QPushButton("цвет границы",this);
    cdPenBorder = new QColorDialog(this);
    cdPenBorder->setModal(Qt::WindowModal);
    cdPenBorder->setWindowTitle("Выбор цвета границы");
    cdPenBorder->hide();
    connect(pbBorderPen, SIGNAL(pressed()), cdPenBorder, SLOT(show()));

    // Прозрачность примитива
    sOpacity = new QSlider(this);
    sOpacity->setOrientation(Qt::Horizontal);
    sOpacity->hide();
    connect(sOpacity, SIGNAL(valueChanged(int)), this, SLOT(SetOpacity()));

    // Кнопки Добавить

    pbAddWall = new QPushButton("Добавить стену", this);
    connect(pbAddWall, SIGNAL(pressed()),this, SLOT(AddWall()));

    pbAddWicket = new QPushButton("Добавить турникет", this);
    connect(pbAddWicket, SIGNAL(pressed()),this, SLOT(AddWicket()));

    pbAddCamera = new QPushButton("Добавить камеру", this);
    connect(pbAddCamera, SIGNAL(pressed()),this, SLOT(AddCamera()));


    pbAddZone = new QPushButton("Добавить зону", this);
    connect(pbAddZone, SIGNAL(pressed()),this, SLOT(AddZone()));

    pbAddText = new QPushButton("Добавить текст", this);
    connect(pbAddText, SIGNAL(pressed()),this, SLOT(AddText()));

    pbAddWidget = new QPushButton("Добавить виджет", this);
    connect(pbAddWidget, SIGNAL(pressed()),this, SLOT(AddWidget()));


    pbAddWicket->hide();
    pbAddCamera->hide();
    pbAddText->hide();
    pbAddWidget->hide();
    pbAddZone->hide();


    /*connect(pbAddWall, SIGNAL(released()), leX1, SLOT(clear()));
    connect(pbAddWall, SIGNAL(released()), leY1, SLOT(clear()));
    connect(pbAddWall, SIGNAL(released()), leX0, SLOT(clear()));
    connect(pbAddWall, SIGNAL(released()), leY0, SLOT(clear()));
    connect(pbAddWall, SIGNAL(released()), leWidth, SLOT(clear()));*/


    //Сцена + вьюха
    scene = new PlansScene();
    scene->setBackgroundBrush(QBrush(QColor(1, 2, 3, 50), Qt::SolidPattern));


    view = new PlansView();
    view->setScene(scene);
    view->show();

    //Основное окно
    QWidget *wMain = new QWidget(this);
    QHBoxLayout *hblMain = new QHBoxLayout(wMain);

    TabWidget = new QTabWidget(this);
    TabWidget->setTabPosition(QTabWidget::East);
    connect(TabWidget, SIGNAL(currentChanged(int)), this, SLOT(CreateTool()));

    TabWidget->addTab(wWall, "Стена");
    TabWidget->addTab(wWicket, "Турникет");
    TabWidget->addTab(wCamera, "Камера");
    TabWidget->addTab(wText, "Текст");
    TabWidget->addTab(wWidget, "Виджет");
    TabWidget->addTab(wZone, "Зона");

    sbRotateView = new QSpinBox(this);
    sbRotateView->setMinimum(0);
    sbRotateView->setMaximum(360);

    connect(sbRotateView, SIGNAL(valueChanged(int)), this, SLOT(SetRotateView()));


    dsbScaleView = new QDoubleSpinBox(this);

    dsbScaleView->setMinimum(0.2);
    dsbScaleView->setMaximum(5.0);
    dsbScaleView->setValue(1.0);
    dsbScaleView->setSingleStep(0.1);

    connect(dsbScaleView, SIGNAL(valueChanged(double)), this, SLOT(SetScaleView()));




    QWidget *wTool = new QWidget(this);
    QVBoxLayout *hblTool = new QVBoxLayout(wTool);
    hblTool->addWidget(TabWidget);
    hblTool->addWidget(sbRotateView);
    hblTool->addWidget(dsbScaleView);

    hblMain->addWidget(view, 9);
    hblMain->addWidget(wTool, 1);

    this->setWindowState(Qt::WindowMaximized);
    this->setCentralWidget(wMain);
}

void MainWindow::CreateTool()
{
    //qDebug() << TabWidget->indexOf(wWall);

    QString CurrentTabText = TabWidget->tabText(TabWidget->currentIndex());

    if (CurrentTabText == "Стена")
    {
        glWall->addWidget(leX0,                0, 0, 1, 1, Qt::AlignCenter);
        glWall->addWidget(leY0,                0, 1, 1, 1, Qt::AlignCenter);
        glWall->addWidget(leX1,                1, 0, 1, 1, Qt::AlignCenter);
        glWall->addWidget(leY1,                1, 1, 1, 1, Qt::AlignCenter);
        glWall->addWidget(leWidth,             2, 0, 1, 2, Qt::AlignCenter);

        glWall->addWidget(pbPen,             3, 0, 1, 2, Qt::AlignCenter);
        glWall->addWidget(pbBorderPen,       4, 0, 1, 2, Qt::AlignCenter);
        glWall->addWidget(pbAddWall,         5, 0, 1, 2, Qt::AlignRight);
    }
    else
        if (CurrentTabText == "Турникет")
        {
            glWicket->addWidget(leX0,                0, 0, 1, 1, Qt::AlignCenter);
            glWicket->addWidget(leY0,                0, 1, 1, 1, Qt::AlignCenter);
            glWicket->addWidget(pbAddWicket,         5, 0, 1, 2, Qt::AlignRight);
            glWicket->addWidget(rbType1,         2, 0, 1, 2, Qt::AlignCenter);
            glWicket->addWidget(rbType2,         3, 0, 1, 2, Qt::AlignCenter);
            glWicket->addWidget(rbType3,         4, 0, 1, 2, Qt::AlignCenter);

            rbType1->show();
            rbType2->show();
            rbType3->show();

            pbAddWicket->show();
        }
        else
            if (CurrentTabText == "Камера")
            {
                glCamera->addWidget(leX0,              0, 0, 1, 1, Qt::AlignCenter);
                glCamera->addWidget(leY0,              0, 1, 1, 1, Qt::AlignCenter);
                glCamera->addWidget(pbAddCamera,       5, 0, 1, 2, Qt::AlignRight);

                pbAddCamera->show();


            }
            else
                if (CurrentTabText == "Зона")
                {
                    glZone->addWidget(leX0,                0, 0, 1, 1, Qt::AlignCenter);
                    glZone->addWidget(leY0,                0, 1, 1, 1, Qt::AlignCenter);
                    glZone->addWidget(leX1,                1, 0, 1, 1, Qt::AlignCenter);
                    glZone->addWidget(leY1,                1, 1, 1, 1, Qt::AlignCenter);

                    glZone->addWidget(pbPen,               2, 0, 1, 2, Qt::AlignCenter);
                    glZone->addWidget(sOpacity,            3, 0, 1, 2, Qt::AlignCenter);
                    glZone->addWidget(pbAddZone,           5, 0, 1, 2, Qt::AlignRight);

                    pbPen->show();
                    sOpacity->show();
                    pbAddZone->show();
                }
                else
                    if (CurrentTabText == "Текст")
                    {
                        glText->addWidget(leX0,                0, 0, 1, 1, Qt::AlignCenter);
                        glText->addWidget(leY0,                0, 1, 1, 1, Qt::AlignCenter);
                        glText->addWidget(leText,              1, 0, 1, 2, Qt::AlignCenter);
                        glText->addWidget(pbFont,              2, 0, 1, 2, Qt::AlignCenter);
                        glText->addWidget(pbPen,               3, 0, 1, 2, Qt::AlignCenter);
                        glText->addWidget(pbAddText,           5, 0, 1, 2, Qt::AlignRight);

                        pbFont->show();
                        leText->show();
                        pbAddText->show();
                    }
                    else
                        if (CurrentTabText == "Виджет")
                        {
                            glWidget->addWidget(leX0,                0, 0, 1, 1, Qt::AlignCenter);
                            glWidget->addWidget(leY0,                0, 1, 1, 1, Qt::AlignCenter);
                            glWidget->addWidget(leX1,                1, 0, 1, 1, Qt::AlignCenter);
                            glWidget->addWidget(leY1,                1, 1, 1, 1, Qt::AlignCenter);

                            glWidget->addWidget(pbAddWidget,           5, 0, 1, 2, Qt::AlignRight);

                            pbAddWidget->show();

                        }

}

void MainWindow::AddWall()
{

    //Рисуем границу стены с ZValue = 1

    QPen myPen(cdPenBorder->selectedColor(),
               leWidth->text().toInt(), Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin);

    QGraphicsLineItem  *LineBorder =
            scene->addLine((leX0->text()).toInt() * scene->StepLine,
                           (leY0->text()).toInt() * scene->StepLine,
                           (leX1->text()).toInt() * scene->StepLine,
                           (leY1->text()).toInt() * scene->StepLine,
                           myPen);

    LineBorder->setZValue(1);

    //Заливка стены с ZValue = 2

    myPen.setColor(cdPen->selectedColor());
    myPen.setWidth(myPen.width()-2);


    QGraphicsLineItem  *LineBrush = new
            QGraphicsLineItem();

    LineBrush->setPen(myPen);
    LineBrush->setLine((leX0->text()).toInt() * scene->StepLine,
                       (leY0->text()).toInt() * scene->StepLine,
                       (leX1->text()).toInt() * scene->StepLine,
                       (leY1->text()).toInt() * scene->StepLine);
    scene->addItem(LineBrush);
    LineBrush->setZValue(2);

    //qDebug() << LineBrush;

    //qDebug() << leX0->text().toFloat();
}

void MainWindow::AddWicket()
{

    // Добавляем турникет на сцену

    Wicket  *myWicket = new Wicket();

    if (rbType1->isChecked())
    {
        myWicket->setType(0);
    }
    else
        if (rbType2->isChecked())
        {
            myWicket->setType(1);
        }
        else
            if (rbType3->isChecked())
            {
                myWicket->setType(2);
            }
    scene->addItem(myWicket);

    myWicket->setPos((leX0->text()).toInt() * scene->StepLine,
                     (leY0->text()).toFloat() * scene->StepLine);
    myWicket->moveBy(- myWicket->boundingRect().width()/2, - myWicket->boundingRect().height()/2);
    myWicket->setZValue(3);

}

void MainWindow::AddCamera()
{

    // Добавляем камеру на сцену

    Camera *myCamera = new Camera();
    scene->addItem(myCamera);
    //w->setScale(0.5);
    myCamera->setPos((leX0->text()).toInt() * scene->StepLine,
                     (leY0->text()).toFloat() * scene->StepLine);
    myCamera->moveBy(- myCamera->boundingRect().width()/2, - myCamera->boundingRect().height()/2);
    myCamera->setZValue(4);
    //qDebug() << w->boundingRect().;
}

void MainWindow::AddZone()
{
    // Добавляем зону на сцену

    QGraphicsRectItem  *myZone =
            scene->addRect((leX0->text()).toInt() * scene->StepLine,
                           (leY0->text()).toInt() * scene->StepLine,
                           (leX1->text()).toInt() * scene->StepLine,
                           (leY1->text()).toInt() * scene->StepLine,
                           QPen(cdPen->selectedColor()), QBrush(cdPen->selectedColor(), Qt::SolidPattern));
    myZone->setZValue(0);
    myZone->setOpacity(Opacity);
}

void MainWindow::AddText()
{
    // Добавляем текст на сцену

    QGraphicsSimpleTextItem *myText = new QGraphicsSimpleTextItem(leText->text());

    myText->setFont(fdFont->currentFont());
    myText->setBrush(cdPen->currentColor());
    scene->addItem(myText);
    myText->setPos((leX0->text()).toInt() * scene->StepLine,
                   (leY0->text()).toFloat() * scene->StepLine);

    myText->moveBy(- myText->boundingRect().width()/2, - myText->boundingRect().height()/2);
    myText->setZValue(5);


}
void MainWindow::AddWidget()
{
    // Добавляем виджет на сцену
    myWidget = new QWidget();
    myWidget->setGeometry(0, 0,
                          (leX1->text()).toInt() * scene->StepLine,
                          (leY1->text()).toInt() * scene->StepLine);

    myWidget->move((leX0->text()).toInt() * scene->StepLine,
                   (leY0->text()).toInt() * scene->StepLine);




    QGraphicsProxyWidget  *myProxyWidget = scene->addWidget(myWidget);


    //myProxyWidget->setZValue(1000);


}

void MainWindow::SetOpacity()
{
    Opacity = (100 - sOpacity->value())/100.0;
    //qDebug() << (100 - sOpacity->value())/100.0;
}

void MainWindow::SetRotateView()
{
    //qDebug() <<sbRotateView->value();
    //qDebug() << radians;
    QMatrix myMatrix;
    myMatrix.rotate(sbRotateView->value());
    view->setMatrix(myMatrix);

}

void MainWindow::SetScaleView()
{
    QMatrix myMatrix;
    myMatrix.scale(dsbScaleView->value()*1.0, dsbScaleView->value()*1.0);
    view->setMatrix(myMatrix);
        qDebug() << dsbScaleView->value();
}

MainWindow::~MainWindow()
{

}
