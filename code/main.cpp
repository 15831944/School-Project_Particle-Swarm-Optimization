#include <QApplication>
#include <Q3DScatter>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPainter>
#include <QScreen>
#include <QTime>
#include "psomodel.h"
#include "surfacegraph.h"
#include "scattergraph.h"
#include "qcustomplot.h"
#include <iostream>


using namespace std;
using namespace QtDataVisualization;
QApplication *a;
Q3DSurface *graph;
Q3DScatter *graph1;
QWidget *container;
QWidget *container1;
ScatterGraph *ParticalPoint;
QCustomPlot *generatPlot;
QCustomPlot *meanPlot;
QCustomPlot *StandardDeviationPlot;
QPushButton *PsoStartBtn;
QPushButton *ReTrainBtn;

QSpinBox *particalNUM;
QDoubleSpinBox *inertiaweiNUM;
QDoubleSpinBox *personinfluNUM;
QDoubleSpinBox *socialinfluNUM;
QSpinBox *groupsizeNUM;
QDoubleSpinBox *terminationNUM;

QPushButton *nextBtn;
QPushButton *stopBtn;
QPushButton *playBtn;
QPushButton *preBtn;
QPushButton *plotBtn;

void EnableNextBtn(){nextBtn->setEnabled(TRUE);}
void EnableStopBtn(){stopBtn->setEnabled(TRUE);}
void EnablePlayBtn(){playBtn->setEnabled(TRUE);}
void EnablePreBtn(){preBtn->setEnabled(TRUE);}
void EnablePlotBtn(){plotBtn->setEnabled(TRUE);}
void EnableReTrainBtn(){ReTrainBtn->setEnabled(TRUE);}
void DisablePsoStartBtn(){PsoStartBtn->setEnabled(FALSE);}
void DisableParticalNUM(){particalNUM->setEnabled(FALSE);}
void DisableInertiaweiNUM(){inertiaweiNUM->setEnabled(FALSE);}
void DisablePersoninfluNUM(){personinfluNUM->setEnabled(FALSE);}
void DisableSocialinfluNUM(){socialinfluNUM->setEnabled(FALSE);}
void DisableGroupsizeNUM(){groupsizeNUM->setEnabled(FALSE);}
void DisableTerminationNUM(){terminationNUM->setEnabled(FALSE);}

void AddGeneratPlotData()
{
    if(ParticalPoint->isTrainOver)
    {
    //! [generatPlot]
    generatPlot->xAxis->setLabel("Number of iterations");
    generatPlot->xAxis->setLabelFont(QFont("sans", 15, QFont::Bold));
    generatPlot->xAxis->setRange(0, ParticalPoint->pso->generateNUM);
    generatPlot->yAxis->setLabel("Minimum fitness value");
    generatPlot->yAxis->setLabelFont(QFont("sans", 15, QFont::Bold));
    generatPlot->yAxis->setRange(0, 22);

    //! [generatPlot]

    //! [meanPlot]
    meanPlot->xAxis->setLabel("Number of iterations");
    meanPlot->xAxis->setLabelFont(QFont("sans", 15, QFont::Bold));
    meanPlot->xAxis->setRange(0, ParticalPoint->pso->generateNUM);
    meanPlot->yAxis->setLabel("Mean value");
    meanPlot->yAxis->setLabelFont(QFont("sans", 15, QFont::Bold));
    meanPlot->yAxis->setRange(0, 22);

    //! [meanPlot]

    //! [StandardDeviationPlot]
    StandardDeviationPlot->xAxis->setLabel("Number of iterations");
    StandardDeviationPlot->xAxis->setLabelFont(QFont("sans", 15, QFont::Bold));
    StandardDeviationPlot->xAxis->setRange(0, ParticalPoint->pso->generateNUM);
    StandardDeviationPlot->yAxis->setLabel("Standard deviation value");
    StandardDeviationPlot->yAxis->setLabelFont(QFont("sans", 15, QFont::Bold));
    StandardDeviationPlot->yAxis->setRange(0,ParticalPoint->MaxStandardDeviation);
    //! [StandardDeviationPlot]

    int pointNUM= ParticalPoint->pso->generateNUM;
    QVector<double> x(pointNUM), y(pointNUM);
    for (int i=0; i<pointNUM; ++i)
    {
      x[i] = i;
      y[i] = ParticalPoint->pso->generation.at(i).Gbest;
    }
    generatPlot->addGraph();
    generatPlot->graph(0)->setData(x, y);
    generatPlot->replot();

    QVector<double> x1(pointNUM), y1(pointNUM);
    for (int i=0; i<pointNUM; ++i)
    {
      x1[i] = i;
      y1[i] = ParticalPoint->pso->generation.at(i).mean;
    }
    meanPlot->addGraph();
    meanPlot->graph(0)->setData(x1, y1);
    meanPlot->replot();

    QVector<double> x2(pointNUM), y2(pointNUM);
    for (int i=0; i<pointNUM; ++i)
    {
      x2[i] = i;
      y2[i] = ParticalPoint->pso->generation.at(i).standarddeviation;
    }
    StandardDeviationPlot->addGraph();
    StandardDeviationPlot->graph(0)->setData(x2, y2);
    StandardDeviationPlot->replot();

    }
}

int main(int argc, char *argv[])
{
    srand((unsigned) time(NULL));
    a = new QApplication(argc, argv);
    //MainWindow *w = new MainWindow;
    //w.show();
    //! [0]
    graph = new Q3DSurface();
    container = QWidget::createWindowContainer(graph);

    graph1 = new Q3DScatter();
    container1 = QWidget::createWindowContainer(graph1);


    //! [0]

    if (!graph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        return -1;
    }

    QSize screenSize = graph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 4, screenSize.height() / 1.6));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    container1->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.6));
    container1->setMaximumSize(screenSize);
    container1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container1->setFocusPolicy(Qt::StrongFocus);

    //! [主畫面]
    QWidget *widget = new QWidget;

    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    //hLayout->addWidget(container,  1);
    hLayout->addWidget(container1, 1);
    hLayout->addLayout(vLayout);
    vLayout->setAlignment(Qt::AlignTop);
    //! [主畫面]    
    ParticalPoint = new ScatterGraph(graph1);

    widget->setWindowTitle(QStringLiteral("Swarm Intelligence test"));

    PsoStartBtn = new QPushButton(widget);
    PsoStartBtn->setText("Start Training");

    ReTrainBtn = new QPushButton(widget);
    ReTrainBtn->setText("ReTrain");
    ReTrainBtn->setEnabled(false);

    QGroupBox *settingGroupBox = new QGroupBox(QStringLiteral("Setting"));

    particalNUM = new QSpinBox(widget);
    particalNUM->setValue(30);
    particalNUM->setMaximum(999);
    particalNUM->setMinimum(1);

    inertiaweiNUM = new QDoubleSpinBox(widget);
    inertiaweiNUM->setValue(0.5);
    inertiaweiNUM->setSingleStep(0.1);
    inertiaweiNUM->setRange(0.0,1.0);

    personinfluNUM = new QDoubleSpinBox(widget);
    personinfluNUM->setValue(0.5);
    personinfluNUM->setSingleStep(0.1);
    personinfluNUM->setMinimum(0.0);

    socialinfluNUM = new QDoubleSpinBox(widget);
    socialinfluNUM->setValue(0.5);
    socialinfluNUM->setSingleStep(0.1);
    socialinfluNUM->setMinimum(0.0);

    groupsizeNUM = new QSpinBox(widget);
    groupsizeNUM->setValue(10);
    groupsizeNUM->setRange(5,particalNUM->value());

    terminationNUM = new QDoubleSpinBox(widget);
    terminationNUM->setMinimum(0.0);
    terminationNUM->setDecimals(8);
    terminationNUM->setValue(0.000001);
    terminationNUM->setSingleStep(0.000001);


    QVBoxLayout *settingVBox = new QVBoxLayout;
    settingVBox->addWidget(new QLabel(QStringLiteral("Particle Number")));
    settingVBox->addWidget(particalNUM);
    settingVBox->addWidget(new QLabel(QStringLiteral("Inertia Weight")));
    settingVBox->addWidget(inertiaweiNUM);
    settingVBox->addWidget(new QLabel(QStringLiteral("Personal influence")));
    settingVBox->addWidget(personinfluNUM);
    settingVBox->addWidget(new QLabel(QStringLiteral("Social influence")));
    settingVBox->addWidget(socialinfluNUM);
    settingVBox->addWidget(new QLabel(QStringLiteral("Group Size")));
    settingVBox->addWidget(groupsizeNUM);
    settingVBox->addWidget(new QLabel(QStringLiteral("Termination condition")));
    settingVBox->addWidget(terminationNUM);
    settingGroupBox->setLayout(settingVBox);

    QGroupBox *playGroupBox = new QGroupBox(QStringLiteral("Play control"));
    nextBtn = new QPushButton(widget);
    nextBtn->setText("Next");
    nextBtn->setEnabled(FALSE);
    stopBtn = new QPushButton(widget);
    stopBtn->setText("Stop");
    stopBtn->setEnabled(FALSE);
    playBtn = new QPushButton(widget);
    playBtn->setText("Start");
    playBtn->setEnabled(FALSE);
    preBtn = new QPushButton(widget);
    preBtn->setText("Pre");
    preBtn->setEnabled(FALSE);
    ParticalPoint->iterationsNUM = new QLabel(widget);
    ParticalPoint->iterationsNUM->setText("0");
    ParticalPoint->iterationsNUM->setAlignment(Qt::AlignCenter);
    ParticalPoint->totaliterationsNUM = new QLabel(widget);
    ParticalPoint->totaliterationsNUM->setText("0");
    ParticalPoint->totaliterationsNUM->setAlignment(Qt::AlignCenter);
    QHBoxLayout *playcontrol = new QHBoxLayout;
    playcontrol->addWidget(preBtn);
    playcontrol->addWidget(nextBtn);
    QHBoxLayout *playcontrol1 = new QHBoxLayout;
    playcontrol1->addWidget(stopBtn);
    playcontrol1->addWidget(playBtn);
    QVBoxLayout *playcontrol0= new QVBoxLayout;
    playcontrol0->addLayout(playcontrol);
    playcontrol0->addLayout(playcontrol1);
    playcontrol0->addWidget(new QLabel(QStringLiteral("Number of iterations now")));
    playcontrol0->addWidget(ParticalPoint->iterationsNUM);
    playcontrol0->addWidget(new QLabel(QStringLiteral("Total number of iterations")));
    playcontrol0->addWidget(ParticalPoint->totaliterationsNUM);
    playGroupBox->setLayout(playcontrol0);

    plotBtn = new QPushButton(widget);
    plotBtn->setText("Show plot");
    plotBtn->setEnabled(FALSE);
    //! [設定Layout]
    vLayout->addWidget(PsoStartBtn);
    vLayout->addWidget(ReTrainBtn);
    vLayout->addWidget(settingGroupBox);
    vLayout->addWidget(playGroupBox);
    vLayout->addWidget(plotBtn);

    //! [設定Layout]

    SurfaceGraph *AckleyFunc = new SurfaceGraph(graph);

    //! [Plot Widget]
    QWidget *plot   = new QWidget;
    plot->setWindowTitle("Line graph of fitness progress");
    plot->setMinimumSize(QSize(screenSize.width(), screenSize.height() / 1.6));
    plot->setMaximumSize(screenSize);
    plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    plot->setFocusPolicy(Qt::StrongFocus);
    generatPlot = new QCustomPlot(plot);
    meanPlot = new QCustomPlot(plot);
    StandardDeviationPlot = new QCustomPlot(plot);
    QHBoxLayout *plotHLayout = new QHBoxLayout(plot);
    QVBoxLayout *plotVLayout = new QVBoxLayout();
    plotHLayout->addWidget(meanPlot,1);
    plotHLayout->addWidget(StandardDeviationPlot,1);
    plotHLayout->addWidget(generatPlot,1);
    generatPlot->plotLayout()->insertRow(0);
    generatPlot->plotLayout()->addElement(0, 0, new QCPTextElement(generatPlot, "Line graph of fitness progress", QFont("sans", 24, QFont::Bold)));
    meanPlot->plotLayout()->insertRow(0);
    meanPlot->plotLayout()->addElement(0, 0, new QCPTextElement(meanPlot, "Mean", QFont("sans", 24, QFont::Bold)));
    StandardDeviationPlot->plotLayout()->insertRow(0);
    StandardDeviationPlot->plotLayout()->addElement(0, 0, new QCPTextElement(StandardDeviationPlot, "Standard Deviation", QFont("sans", 24, QFont::Bold)));

    meanPlot->replot();
    StandardDeviationPlot->replot();
    generatPlot->replot();
    //! [Plot Widget]


    QObject::connect(particalNUM, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                     ParticalPoint,&ScatterGraph::changeParticalNUM);
    QObject::connect(inertiaweiNUM,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                     ParticalPoint,&ScatterGraph::changeInertiaweiNUM);
    QObject::connect(personinfluNUM,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                     ParticalPoint,&ScatterGraph::changePersoninfluNUM);
    QObject::connect(socialinfluNUM,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                     ParticalPoint,&ScatterGraph::changeSocialinfluNUM);
    QObject::connect(groupsizeNUM, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                     ParticalPoint,&ScatterGraph::changeGroupSize);
    QObject::connect(terminationNUM,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                     ParticalPoint,&ScatterGraph::changeTerminationNUM);
    QObject::connect(particalNUM, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                     groupsizeNUM,&QSpinBox::setMaximum);

    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     ParticalPoint,&ScatterGraph::StartTraining); 
    QObject::connect(ReTrainBtn, &QPushButton::clicked,
                     ParticalPoint,&ScatterGraph::ReTrain);

    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     widget,&EnableNextBtn);
    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     widget,&EnableStopBtn);
    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     widget,&EnablePlayBtn);
    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     widget,&EnablePreBtn);
    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     widget,&EnablePlotBtn);
    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     widget,&EnableReTrainBtn);
    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     widget,&DisablePsoStartBtn);
    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     widget,&DisableParticalNUM);
    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     widget,&DisableInertiaweiNUM);
    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     widget,&DisablePersoninfluNUM);
    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     widget,&DisableSocialinfluNUM);
    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     widget,&DisableGroupsizeNUM);
    QObject::connect(PsoStartBtn, &QPushButton::clicked,
                     widget,&DisableTerminationNUM);

    QObject::connect(nextBtn, &QPushButton::clicked,
                     ParticalPoint,&ScatterGraph::next);
    QObject::connect(preBtn, &QPushButton::clicked,
                     ParticalPoint,&ScatterGraph::pre);
    QObject::connect(playBtn, &QPushButton::clicked,
                     ParticalPoint,&ScatterGraph::play);
    QObject::connect(stopBtn, &QPushButton::clicked,
                     ParticalPoint,&ScatterGraph::stop);

    QObject::connect(plotBtn, &QPushButton::clicked,
                     widget,&AddGeneratPlotData);
    QObject::connect(plotBtn, &QPushButton::clicked,
                     plot,&QWidget::show);





    widget->show();

    return a->exec();
}
