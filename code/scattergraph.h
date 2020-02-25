#ifndef SCATTERGRAPH_H
#define SCATTERGRAPH_H

#include <Q3DScatter>
#include <qscatter3dseries.h>
#include <qscatterdataproxy.h>
#include <psomodel.h>
#include <QFont>
#include <QLabel>

using namespace QtDataVisualization;

class ScatterGraph : public QObject
{
    Q_OBJECT
public:
    explicit ScatterGraph(Q3DScatter *scatter);
    ~ScatterGraph();
    PsoModel *pso;
    QLabel *iterationsNUM;
    QLabel *totaliterationsNUM;
    int ParticalNUM;
    double inertiaweiNUM;
    double personinfluNUM;
    double socialinfluNUM;
    int GroupSize;
    int NowShow;
    double error;
    double MaxStandardDeviation;
    int MaxGenerate;
    bool isTrainOver;
    bool playflag;
    double MAX_Px,MIN_Px,MAX_Py,MIN_Py,MAX_Pz,MIN_Pz;
    double MAX_Vx,MAX_Vy,MAX_Vz;
    void changeParticalNUM(int _ParticalNUM);
    void changeInertiaweiNUM(double _inertiaweiNUM);
    void changePersoninfluNUM(double _personinfluNUM);
    void changeSocialinfluNUM(double _socialinfluNUM);
    void changeGroupSize(int _GroupSize);
    void changeTerminationNUM(double _Termination);

    void initialPSO(int ParticalNUM,double inertiaweiNUM,double personinfluNUM,double socialinfluNUM,int GroupSize);
    void GeneratePSO();
    void addData(int generationNUM);
    void CalError(int generationNUM);
    void CalMean(int generationNUM);
    void CalStandardDeviation(int generationNUM);
    void StartTraining();
    void ReTrain();
    void ClearALL();
    void next();
    void pre();
    void play();
    void stop();
public Q_SLOTS:


private:
    QScatterDataProxy *proxy;
    QScatter3DSeries  *series;
    QScatterDataArray *dataArray;
    Q3DScatter *m_graph;
    QAbstract3DSeries::Mesh m_style;

};

#endif // SCATTERGRAPH_H
