#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qlayout.h>
#include <Q3DSurface>

using namespace Qwt3D;
using namespace std;
using namespace QtDataVisualization;

double** allocateData(int columns, int rows)
{
    double** data  = new double* [columns] ;
    for ( int i = 0; i < columns; ++i)
    {        data[i]  = new double [rows];    }
    return data;
}

void deleteData(double**data, int columns)
{
    for ( int i = 0; i < columns; i++)
    {         delete [] data[i];     }
    delete [] data;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand((unsigned) time(NULL));
    ui->setupUi(this);

    pso = new PsoModel();
    TripleField data;
    CellField cellF;
    Triple temp;
    for(int i=0;i<100;i++){
        temp.x = (32.0 - (-32.0)) * rand() / RAND_MAX + (-32.0);
        temp.y = (32.0 - (-32.0)) * rand() / RAND_MAX + (-32.0);
        temp.z = pso->PsoModel::Ackley(temp.x,temp.y);
        data.push_back(temp);
    }

    plot = new SurfacePlot(ui->frame);
    ui->verticalLayout->addWidget(plot,0,0);
    plot->setZoom(0.8);
    plot->setScale(1,1,5);
    plot->setRotation(30,0,15);
    plot->coordinates()->setGridLines(true,true);
    //plot->loadFromData(data,cellF);
    //plot->setPlotStyle(Qwt3D::POINTS);
    plot->setCoordinateStyle(BOX);
    ackley = new Ackley(*plot);
    ackley->setMesh(500,500);
    ackley->setDomain(-32,32,-32,32);
    ackley->setMinZ(-200);
    ackley->create();


    QGridLayout *grid1 = new QGridLayout(ui->frame_2);
    plot1 = new SurfacePlot(ui->frame_2);
    grid1->addWidget( plot1, 0, 0 );
    plot1->setZoom(0.8);
    plot1->setScale(1,1,5);
    plot1->setRotation(30,0,15);
    plot1->coordinates()->setGridLines(true,true);
    plot1->setCoordinateStyle(BOX);
    plot1->setPlotStyle(Qwt3D::POINTS);
    dot = plot1->setPlotStyle(Dot(1.0,true));
    plot1->loadFromData(data,cellF);
    plot1->updateData();
    plot1->updateGL();







}

MainWindow::~MainWindow()
{
    delete ui;
}
