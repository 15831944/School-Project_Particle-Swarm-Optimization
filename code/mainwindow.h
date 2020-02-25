#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt3d_surfaceplot.h>
#include <qwt3d_plot.h>
#include <qwt3d_enrichment_std.h>
#include <qwt3d_enrichment.h>
#include <function.h>
#include "psomodel.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Qwt3D::SurfacePlot* plot1;
    Qwt3D::SurfacePlot* plot;
    Qwt3D::Function* ackley;
    Qwt3D::Enrichment* dot;
    PsoModel *pso;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
