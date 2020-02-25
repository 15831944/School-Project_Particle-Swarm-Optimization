#include <scattergraph.h>
#include <qscatterdataproxy.h>
#include <qvalue3daxis.h>
#include <q3dscene.h>
#include <qscatter3dseries.h>
#include <q3dtheme.h>
#include <qmath.h>
#include <cstdlib>
#include <iostream>
#include <QTime>
#include <time.h>
#include <QCoreApplication>
#include <cstdlib>
#include <QFile>

#define RND() ((double)rand()/RAND_MAX)

using namespace std;
using namespace QtDataVisualization;

ScatterGraph::ScatterGraph(Q3DScatter *scatter)
    : m_graph(scatter)
{
    pso = new PsoModel();
    ParticalNUM =30;
    inertiaweiNUM = 0.5;
    personinfluNUM = 0.5;
    socialinfluNUM = 0.5;
    GroupSize = 10;
    NowShow = 0;
    error = 0.000001;
    MaxStandardDeviation = 100;
    MaxGenerate = 5000;
    isTrainOver = false;
    playflag = true;
    MAX_Vx = 64;MAX_Vy = 64;MAX_Vz = 64;
    MAX_Px = 32;MIN_Px = -32;
    MAX_Py = 32;MIN_Py = -32;
    MAX_Pz = 32;MIN_Pz = -32;
    m_graph->activeTheme()->setType(Q3DTheme::ThemeEbony);
    QFont font = m_graph->activeTheme()->font();
    font.setPointSize(80.0f);
    m_graph->activeTheme()->setFont(font);
    m_graph->axisX()->setLabelFormat("%.2f");
    m_graph->axisZ()->setLabelFormat("%.2f");
    m_graph->axisX()->setRange(-32.0f, 32.0f);
    m_graph->axisY()->setRange(-32.0f, 32.0f);
    m_graph->axisZ()->setRange(-32.0f, 32.0f);
    m_graph->axisX()->setLabelAutoRotation(30);
    m_graph->axisY()->setLabelAutoRotation(90);
    m_graph->axisZ()->setLabelAutoRotation(30);
    proxy     = new QScatterDataProxy();
    series    = new QScatter3DSeries(proxy);
    dataArray = new QScatterDataArray();
    m_graph->addSeries(series);

}

ScatterGraph::~ScatterGraph()
{
    delete m_graph;
}

void ScatterGraph::changeParticalNUM(int _ParticalNUM)
{ParticalNUM = _ParticalNUM;}
void ScatterGraph::changeInertiaweiNUM(double _inertiaweiNUM)
{inertiaweiNUM = _inertiaweiNUM;}
void ScatterGraph::changePersoninfluNUM(double _personinfluNUM)
{personinfluNUM = _personinfluNUM;}
void ScatterGraph::changeSocialinfluNUM(double _socialinfluNUM)
{socialinfluNUM = _socialinfluNUM;}
void ScatterGraph::changeGroupSize(int _GroupSize)
{GroupSize = _GroupSize;}
void ScatterGraph::changeTerminationNUM(double _Termination)
{error = _Termination;}

void ScatterGraph::initialPSO(int ParticalNUM,double inertiaweiNUM,double personinfluNUM,double socialinfluNUM,int GroupSize)
{
    cout << pso->PsoModel::Ackley(19.7921,12.4331) <<endl;
    pso->generateNUM = 0;
    Generation generation;
    pso->generation.push_back(generation);

    pso->particalNUM = ParticalNUM;
    pso->GroupSize = GroupSize;

    cout << "ParticalNUM: "   << ParticalNUM   << endl
         << "inertiaweiNUM: " << inertiaweiNUM << endl
         << "personinfluNUM: "<< personinfluNUM<< endl
         << "socialinfluNUM: "<< socialinfluNUM<< endl
         << "GroupSize: "     << GroupSize     << endl
         << "We will have " << ceil((double)ParticalNUM/(double)GroupSize)<< " groups" <<endl;

    int nowGroup = 0;
    int count = GroupSize;
    int TotalgroupNUM = ceil((double)ParticalNUM/(double)GroupSize);
    double temp_groupbest,temp_groupbestX,temp_groupbestY,temp_groupbestZ;
    Group group;
    pso->generation.at(0).group.push_back(group);

    for(int i=0;i<ParticalNUM;i++)
    {
        Partical partical;
        partical.Px = (32.0 - (-32.0)) * rand() / RAND_MAX + (-32.0);
        partical.Py = (32.0 - (-32.0)) * rand() / RAND_MAX + (-32.0);
        partical.Pz = (32.0 - (-32.0)) * rand() / RAND_MAX + (-32.0);
        partical.Value = pso->PsoModel::Ackley(partical.Px, partical.Py);
        if(count - 1 >=0)
          {
           count--;
            if(i==0 || partical.Value < temp_groupbest)
              {
               temp_groupbest = partical.Value;
               temp_groupbestX= partical.Px;
               temp_groupbestY= partical.Py;
               temp_groupbestZ= partical.Pz;
               pso->generation.at(0).group.at(nowGroup).Groupbest = temp_groupbest;
               pso->generation.at(0).group.at(nowGroup).GroupbestX= temp_groupbestX;
               pso->generation.at(0).group.at(nowGroup).GroupbestY= temp_groupbestY;
               pso->generation.at(0).group.at(nowGroup).GroupbestZ= temp_groupbestZ;
              }
          }

        else
          {
            pso->generation.at(0).group.at(nowGroup).Groupbest = temp_groupbest;
            pso->generation.at(0).group.at(nowGroup).GroupbestX= temp_groupbestX;
            pso->generation.at(0).group.at(nowGroup).GroupbestY= temp_groupbestY;
            pso->generation.at(0).group.at(nowGroup).GroupbestZ= temp_groupbestZ;
            count = GroupSize;
            Group newGroup;
            pso->generation.at(0).group.push_back(newGroup);
            nowGroup++;
            temp_groupbest = partical.Value;
            temp_groupbestX= partical.Px;
            temp_groupbestY= partical.Py;
            temp_groupbestZ= partical.Pz;
            pso->generation.at(0).group.at(nowGroup).Groupbest = temp_groupbest;
            pso->generation.at(0).group.at(nowGroup).GroupbestX= temp_groupbestX;
            pso->generation.at(0).group.at(nowGroup).GroupbestY= temp_groupbestY;
            pso->generation.at(0).group.at(nowGroup).GroupbestZ= temp_groupbestZ;
          }
        partical.pbest  = partical.Value;
        partical.pbestX = partical.Px;
        partical.pbestY = partical.Py;
        partical.pbestZ = partical.Pz;
        partical.Vx = RND()*MAX_Vx;
        partical.Vy = RND()*MAX_Vy;
        partical.Vz = RND()*MAX_Vz;
        pso->generation.at(pso->generateNUM).group.at(nowGroup).partical.push_back(partical);
    }


    for(int i=0;i<TotalgroupNUM;i++)
    {
        for(int j=0;j<pso->generation.at(0).group.at(i).partical.size();j++)
           {
            if(pso->generation.at(0).group.at(i).partical.at(j).pbest == pso->generation.at(0).group.at(i).Groupbest)
              {pso->generation.at(0).group.at(i).partical.at(j).leader = TRUE;
               pso->generation.at(0).group.at(i).in = j;}
            else
              {pso->generation.at(0).group.at(i).partical.at(j).leader = FALSE;}
           }
    }
    float Gbest,GbestX,GbestY,GbestZ;

    for(int i=0;i<TotalgroupNUM;i++)
    {
        if(i==0 || pso->generation.at(0).group.at(i).Groupbest<Gbest)
        {
            Gbest = pso->generation.at(0).group.at(i).Groupbest;
            GbestX= pso->generation.at(0).group.at(i).GroupbestX;
            GbestY= pso->generation.at(0).group.at(i).GroupbestY;
            GbestZ= pso->generation.at(0).group.at(i).GroupbestZ;
        }
    }
    pso->generation.at(0).Gbest = Gbest;
    pso->generation.at(0).GbestX= GbestX;
    pso->generation.at(0).GbestY= GbestY;
    pso->generation.at(0).GbestZ= GbestZ;
    CalError(0);
    CalMean(0);
    CalStandardDeviation(0);
    addData(0);
}

void ScatterGraph::GeneratePSO()
{
    double TempVx,TempVy,TempVz;//速度
    double TempPx,TempPy,TempPz;//位置
    double TempPbestX,TempPbestY,TempPbestZ;//pbest位置
    double TempGrbestX,TempGrbestY,TempGrbestZ;//Group best位置
    double TempGbestX,TempGbestY,TempGbestZ;//Gbest位置
    int Nowgenerate = pso->generateNUM;
    int _groupsize = GroupSize;
    int _particalsize = pso->particalNUM;
    int Totalgroup = ceil((double)_particalsize/(double)_groupsize);
    TempGbestX = pso->generation.at(Nowgenerate).GbestX;
    TempGbestY = pso->generation.at(Nowgenerate).GbestY;
    TempGbestZ = pso->generation.at(Nowgenerate).GbestZ;

    Generation generation;
    generation.Gbest  = pso->generation.at(Nowgenerate).Gbest;
    generation.GbestX = pso->generation.at(Nowgenerate).GbestX;
    generation.GbestY = pso->generation.at(Nowgenerate).GbestY;
    generation.GbestZ = pso->generation.at(Nowgenerate).GbestZ;
    pso->generation.push_back(generation);

    //cout << "Now generation " << Nowgenerate <<endl;
    for(int i=0;i<Totalgroup;i++) // 組別
    {
        Group group;
        pso->generation.at(Nowgenerate+1).group.push_back(group);
        TempGrbestX = pso->generation.at(Nowgenerate).group.at(i).GroupbestX;
        TempGrbestY = pso->generation.at(Nowgenerate).group.at(i).GroupbestY;
        TempGrbestZ = pso->generation.at(Nowgenerate).group.at(i).GroupbestZ;
        for(int j=0;j<pso->generation.at(Nowgenerate).group.at(i).partical.size();j++) // 組內成員
        {
        Partical partical;

        TempVx = pso->generation.at(Nowgenerate).group.at(i).partical.at(j).Vx;
        TempVy = pso->generation.at(Nowgenerate).group.at(i).partical.at(j).Vy;
        TempVz = pso->generation.at(Nowgenerate).group.at(i).partical.at(j).Vz;

        TempPx = pso->generation.at(Nowgenerate).group.at(i).partical.at(j).Px;
        TempPy = pso->generation.at(Nowgenerate).group.at(i).partical.at(j).Py;
        TempPz = pso->generation.at(Nowgenerate).group.at(i).partical.at(j).Pz;

        TempPbestX = pso->generation.at(Nowgenerate).group.at(i).partical.at(j).pbestX;
        TempPbestY = pso->generation.at(Nowgenerate).group.at(i).partical.at(j).pbestY;
        TempPbestZ = pso->generation.at(Nowgenerate).group.at(i).partical.at(j).pbestZ;

        if(pso->generation.at(Nowgenerate).group.at(i).partical.at(j).leader)//Leader 的回合
          {
           TempVx = inertiaweiNUM*TempVx + personinfluNUM*RND()*(TempPbestX-TempPx) + socialinfluNUM*RND()*(TempGbestX-TempPx);
           TempVy = inertiaweiNUM*TempVy + personinfluNUM*RND()*(TempPbestY-TempPy) + socialinfluNUM*RND()*(TempGbestY-TempPy);
           TempVz = inertiaweiNUM*TempVz + personinfluNUM*RND()*(TempPbestZ-TempPz) + socialinfluNUM*RND()*(TempGbestZ-TempPz);

           if(TempVx> MAX_Vx){TempVx =  MAX_Vx;}    if(TempVy> MAX_Vy){TempVy =  MAX_Vy;}   if(TempVz> MAX_Vz){TempVz =  MAX_Vz;}
           if(TempVx<-MAX_Vx){TempVx = -MAX_Vx;}    if(TempVy<-MAX_Vy){TempVy = -MAX_Vy;}   if(TempVz<-MAX_Vz){TempVz = -MAX_Vz;}

           TempPx = TempPx + TempVx ;
           TempPy = TempPy + TempVy ;
           TempPz = TempPz + TempVz ;

           if(TempPx>MAX_Px){TempPx = MAX_Px;}    if(TempPy>MAX_Py){TempPy = MAX_Py;}   if(TempPz>MAX_Pz){TempPz = MAX_Pz;}
           if(TempPx<MIN_Px){TempPx = MIN_Px;}    if(TempPy<MIN_Py){TempPy = MIN_Py;}   if(TempPz<MIN_Pz){TempPz = MIN_Pz;}

           partical.Vx = TempVx;
           partical.Vy = TempVy;
           partical.Vz = TempVz;

           partical.Px = TempPx;
           partical.Py = TempPy;
           partical.Pz = TempPz;

           partical.Value = pso->PsoModel::Ackley(TempPx,TempPy,TempPz);
           //cout <<i <<"-" << j << " Temp " << TempPx <<"/"<< TempPy<<"/"<< pso->PsoModel::Ackley(TempVx,TempVy)<< endl;
           //cout <<i <<"-" << j << " Partical " << partical.Px <<"/"<< partical.Py<<"/"<< partical.Pz<< endl;
           if(j==0) // 更新 Group Best
             {
              pso->generation.at(Nowgenerate+1).group.at(i).Groupbest = partical.Value;
              pso->generation.at(Nowgenerate+1).group.at(i).GroupbestX= partical.Px;
              pso->generation.at(Nowgenerate+1).group.at(i).GroupbestY= partical.Py;
              pso->generation.at(Nowgenerate+1).group.at(i).GroupbestZ= partical.Pz;
              partical.leader = TRUE;
              pso->generation.at(Nowgenerate+1).group.at(i).in = j ;
              //cout << "i==0 leader in " << pso->generation.at(Nowgenerate+1).group.at(i).in <<endl;
             }
           else if(partical.Value < pso->generation.at(Nowgenerate+1).group.at(i).Groupbest)
             {
              pso->generation.at(Nowgenerate+1).group.at(i).Groupbest = partical.Value;
              pso->generation.at(Nowgenerate+1).group.at(i).GroupbestX= partical.Px;
              pso->generation.at(Nowgenerate+1).group.at(i).GroupbestY= partical.Py;
              pso->generation.at(Nowgenerate+1).group.at(i).GroupbestZ= partical.Pz;
              partical.leader = TRUE;
              int lastLeaderIn = pso->generation.at(Nowgenerate+1).group.at(i).in;
              //cout <<"Nowgenerate : " << Nowgenerate <<"Group : "<< i << " member : " << j << " lastLeaderIn : " << lastLeaderIn <<endl;
              pso->generation.at(Nowgenerate+1).group.at(i).partical.at(lastLeaderIn).leader = FALSE;
              pso->generation.at(Nowgenerate+1).group.at(i).in = j ;
             }
           else
             {
              partical.leader = FALSE;
             }
           if(partical.Value < pso->generation.at(Nowgenerate).group.at(i).partical.at(j).pbest) // 更新 Pbest
             {
              partical.pbest = partical.Value;
              partical.pbestX= partical.Px;
              partical.pbestY= partical.Py;
              partical.pbestZ= partical.Pz;
             }
           else
             {
              partical.pbest = pso->generation.at(Nowgenerate).group.at(i).partical.at(j).pbest;
              partical.pbestX= pso->generation.at(Nowgenerate).group.at(i).partical.at(j).pbestX;
              partical.pbestY= pso->generation.at(Nowgenerate).group.at(i).partical.at(j).pbestY;
              partical.pbestZ= pso->generation.at(Nowgenerate).group.at(i).partical.at(j).pbestZ;
             }
           if(partical.Value < pso->generation.at(Nowgenerate+1).Gbest) //更新 Gbest
             {
              pso->generation.at(Nowgenerate+1).Gbest = partical.Value;
              pso->generation.at(Nowgenerate+1).GbestX= partical.Px;
              pso->generation.at(Nowgenerate+1).GbestY= partical.Py;
              pso->generation.at(Nowgenerate+1).GbestZ= partical.Pz;
             }

          }

        else //普通Partical的回合
          {
           TempVx = inertiaweiNUM*TempVx + personinfluNUM*RND()*(TempPbestX-TempPx) + socialinfluNUM*RND()*(TempGrbestX-TempPx);
           TempVy = inertiaweiNUM*TempVy + personinfluNUM*RND()*(TempPbestY-TempPy) + socialinfluNUM*RND()*(TempGrbestY-TempPy);
           TempVz = inertiaweiNUM*TempVz + personinfluNUM*RND()*(TempPbestZ-TempPz) + socialinfluNUM*RND()*(TempGrbestZ-TempPz);

           if(TempVx> MAX_Vx){TempVx =  MAX_Vx;}    if(TempVy> MAX_Vy){TempVy =  MAX_Vy;}   if(TempVz> MAX_Vz){TempVz =  MAX_Vz;}
           if(TempVx<-MAX_Vx){TempVx = -MAX_Vx;}    if(TempVy<-MAX_Vy){TempVy = -MAX_Vy;}   if(TempVz<-MAX_Vz){TempVz = -MAX_Vz;}
           TempPx = TempPx + TempVx ;
           TempPy = TempPy + TempVy ;
           TempPz = TempPz + TempVz ;

           if(TempPx>MAX_Px){TempPx = MAX_Px;}    if(TempPy>MAX_Py){TempPy = MAX_Py;}   if(TempPz>MAX_Pz){TempPz = MAX_Pz;}
           if(TempPx<MIN_Px){TempPx = MIN_Px;}    if(TempPy<MIN_Py){TempPy = MIN_Py;}   if(TempPz<MIN_Pz){TempPz = MIN_Pz;}
           partical.Vx = TempVx;
           partical.Vy = TempVy;
           partical.Vz = TempVz;

           partical.Px = TempPx;
           partical.Py = TempPy;
           partical.Pz = TempPz;
           partical.Value = pso->PsoModel::Ackley(TempPx,TempPy,TempPz);
           //cout <<i <<"-" << j << " Temp " << TempPx <<"/"<< TempPy<<"/"<< pso->PsoModel::Ackley(TempVx,TempVy)<< endl;
           //cout <<i <<"-" << j << " Partical " << partical.Px <<"/"<< partical.Py<<"/"<< partical.Pz<< endl;
           if(j==0) // 更新 Group Best
             {
              pso->generation.at(Nowgenerate+1).group.at(i).Groupbest = partical.Value;
              pso->generation.at(Nowgenerate+1).group.at(i).GroupbestX= partical.Px;
              pso->generation.at(Nowgenerate+1).group.at(i).GroupbestY= partical.Py;
              pso->generation.at(Nowgenerate+1).group.at(i).GroupbestZ= partical.Pz;
              partical.leader = TRUE;
              pso->generation.at(Nowgenerate+1).group.at(i).in = j ;
             }
           else if(partical.Value < pso->generation.at(Nowgenerate+1).group.at(i).Groupbest)
             {
              pso->generation.at(Nowgenerate+1).group.at(i).Groupbest = partical.Value;
              pso->generation.at(Nowgenerate+1).group.at(i).GroupbestX= partical.Px;
              pso->generation.at(Nowgenerate+1).group.at(i).GroupbestY= partical.Py;
              pso->generation.at(Nowgenerate+1).group.at(i).GroupbestZ= partical.Pz;
              partical.leader = TRUE;
              pso->generation.at(Nowgenerate+1).group.at(i).partical.at(pso->generation.at(Nowgenerate+1).group.at(i).in).leader = FALSE;
              pso->generation.at(Nowgenerate+1).group.at(i).in = j ;
             }
           else
             {
              partical.leader = FALSE;
             }

           if(partical.Value < pso->generation.at(Nowgenerate).group.at(i).partical.at(j).pbest) // 更新 Pbest
             {
              partical.pbest = partical.Value;
              partical.pbestX= partical.Px;
              partical.pbestY= partical.Py;
              partical.pbestZ= partical.Pz;
             }
           else
             {
              partical.pbest = pso->generation.at(Nowgenerate).group.at(i).partical.at(j).pbest;
              partical.pbestX= pso->generation.at(Nowgenerate).group.at(i).partical.at(j).pbestX;
              partical.pbestY= pso->generation.at(Nowgenerate).group.at(i).partical.at(j).pbestY;
              partical.pbestZ= pso->generation.at(Nowgenerate).group.at(i).partical.at(j).pbestZ;
             }
           if(partical.Value < pso->generation.at(Nowgenerate+1).Gbest) //更新 Gbest
             {
              pso->generation.at(Nowgenerate+1).Gbest = partical.Value;
              pso->generation.at(Nowgenerate+1).GbestX= partical.Px;
              pso->generation.at(Nowgenerate+1).GbestY= partical.Py;
              pso->generation.at(Nowgenerate+1).GbestZ= partical.Pz;
             }
          }

        //cout <<i <<"-" << j << " PUSH " << partical.Px <<"/"<< partical.Py<<"/"<< partical.Pz<< endl;
        pso->generation.at(Nowgenerate+1).group.at(i).partical.push_back(partical);
        }
    }
    pso->generateNUM++;
}

void ScatterGraph::CalMean(int generationNUM)
{
    int groupNUM = pso->generation.at(generationNUM).group.size();
    int partical = ParticalNUM;
    double mean = 0;
    for(int i=0;i<groupNUM;i++)
       {
        for(int j=0;j<pso->generation.at(generationNUM).group.at(i).partical.size();j++)
           {
            mean+=pso->generation.at(generationNUM).group.at(i).partical.at(j).Value;
           }
       }
    mean = mean/partical;
    //cout << generationNUM << " " << mean <<endl;
    pso->generation.at(generationNUM).mean = mean;
}

void ScatterGraph::CalStandardDeviation(int generationNUM)
{
    int groupNUM = pso->generation.at(generationNUM).group.size();
    int partical = ParticalNUM;
    double Variance = 0;
    for(int i=0;i<groupNUM;i++)
       {
        for(int j=0;j<pso->generation.at(generationNUM).group.at(i).partical.size();j++)
           {
            double temp = (pso->generation.at(generationNUM).group.at(i).partical.at(j).Value - pso->generation.at(generationNUM).mean);
            Variance += temp*temp;
           }
       }
    Variance = Variance/partical;
    Variance = sqrt(Variance);
    if(generationNUM==0 || Variance>MaxStandardDeviation){MaxStandardDeviation = Variance;}
    pso->generation.at(generationNUM).standarddeviation = Variance;
}

void ScatterGraph::CalError(int generationNUM)
{
    //cout <<"Cal generate "  << pso->generateNUM <<endl;
    int groupNUM = pso->generation.at(generationNUM).group.size();
    double Gbest = pso->generation.at(generationNUM).Gbest;
    double thisError;
    for(int i=0;i<groupNUM;i++)
       {
        for(int j=0;j<pso->generation.at(generationNUM).group.at(i).partical.size();j++)
           {
            //cout << "Gbest : " << Gbest << "  "  << "Pbest : " << pso->generation.at(generationNUM).group.at(i).partical.at(j).pbest <<endl;
            if(j==0 || (pso->generation.at(generationNUM).group.at(i).partical.at(j).Value - Gbest)>thisError)
              {
               thisError = pso->generation.at(generationNUM).group.at(i).partical.at(j).Value - Gbest;
              }
           }
       }
    //cout << "Error : " << thisError <<endl;
    pso->generation.at(generationNUM).error = thisError;
}

void ScatterGraph::addData(int generationNUM)
{

    // Configure the axes according to the data
    //! [4]
    m_graph->axisX()->setTitle("X");
    m_graph->axisY()->setTitle("Y");
    m_graph->axisZ()->setTitle("Z");
    //! [4]
    int ParticalSize =pso->particalNUM;
    //cout << "In addData() ParticalSize : " << ParticalSize << endl;
    dataArray->resize(ParticalSize);
    QScatterDataItem *ptrToDataArray = &dataArray->first();


    /*cout << "Gbest & its position (X,Y): " << pso->generation.at(generationNUM).Gbest << "   (" << pso->generation.at(generationNUM).GbestX << ","
                                           << pso->generation.at(generationNUM).GbestY<< ")" << endl;*/

    //cout << "generationNUM : " << generationNUM << endl;
    for (int i = 0; i < pso->generation.at(generationNUM).group.size(); i++) {
        /*cout << "Group :" << i << endl
             << "Group Best & its position (X,Y) :" << pso->generation.at(generationNUM).group.at(i).Groupbest << "   ("
                                                    << pso->generation.at(generationNUM).group.at(i).GroupbestX<< ","
                                                    << pso->generation.at(generationNUM).group.at(i).GroupbestX<< ")" << endl
             << "at flag " << pso-> generation.at(generationNUM).group.at(i).in << "member" <<endl;*/
        for(int j = 0;j<pso->generation.at(generationNUM).group.at(i).partical.size();j++)
           {
            /*cout << "Member number : "  << j <<endl
                 << "Position (X,Y) : ("<< pso->generation.at(generationNUM).group.at(i).partical.at(j).Px << ","
                                        << pso->generation.at(generationNUM).group.at(i).partical.at(j).Py << ")" <<endl
                 << "Function Value : " << pso->generation.at(generationNUM).group.at(i).partical.at(j).Pz <<endl
                 << "Velocity (X,Y) : " << pso->generation.at(generationNUM).group.at(i).partical.at(j).Vx << ","
                                        << pso->generation.at(generationNUM).group.at(i).partical.at(j).Vy << ")" <<endl
                 << "Pbest & its position (X,Y) : " << pso->generation.at(generationNUM).group.at(i).partical.at(j).pbest  << "   ("
                                                    << pso->generation.at(generationNUM).group.at(i).partical.at(j).pbestX << ","
                                                    << pso->generation.at(generationNUM).group.at(i).partical.at(j).pbestY << ")" << endl;
            if(pso->generation.at(generationNUM).group.at(i).partical.at(j).leader){cout << "Leader" <<endl;}*/

            float x = (float)pso->generation.at(generationNUM).group.at(i).partical.at(j).Px;
            float y = (float)pso->generation.at(generationNUM).group.at(i).partical.at(j).Py;
            float z = (float)pso->generation.at(generationNUM).group.at(i).partical.at(j).Pz;

            //cout <<i <<"-" << j << "  " << x <<"/"<< y<<"/"<<z<< endl;

            ptrToDataArray->setPosition(QVector3D(x,z,y));
            ptrToDataArray++;
           }
    }

    m_graph->seriesList().at(0)->dataProxy()->resetArray(dataArray);
    if (m_graph->seriesList().size())
        m_graph->seriesList().at(0)->setMesh(QAbstract3DSeries::MeshPoint);
}

void ScatterGraph::pre()
{
    if((NowShow-1)>=0)
      { NowShow--;
        iterationsNUM->setText(QString::number(NowShow));
        addData(NowShow);}
}

void ScatterGraph::next()
{
    if((NowShow+1)<=pso->generateNUM)
      { NowShow++;
        iterationsNUM->setText(QString::number(NowShow));
        addData(NowShow);}
}

void ScatterGraph::play()
{
    playflag = TRUE;
    if((NowShow+1)<=pso->generateNUM){
    for(int i = NowShow;i<pso->generateNUM;i++)
    {
     NowShow++;
     iterationsNUM->setText(QString::number(NowShow));
     addData(i);
     if(!playflag){break;}
     QTime dieTime= QTime::currentTime().addMSecs(300);
     while( QTime::currentTime() < dieTime )
     QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    }
}

void ScatterGraph::stop()
{
    addData(NowShow);playflag = FALSE;
}

void ScatterGraph::StartTraining()
{
    initialPSO(ParticalNUM,inertiaweiNUM,personinfluNUM,socialinfluNUM,GroupSize);
    //cout << error << endl;
    while(pso->generation.at(pso->generateNUM).error>error)
    {GeneratePSO();
     CalError(pso->generateNUM);
     CalMean(pso->generateNUM);
     CalStandardDeviation(pso->generateNUM);
     MaxGenerate--;
     if(MaxGenerate<0)break;
    }
    isTrainOver = true;
    totaliterationsNUM->setText(QString::number(pso->generateNUM));

    QFile data("Gbest.txt");
    if (data.open(QFile::WriteOnly | QIODevice::Append)) {
        QTextStream out(&data);
        out << QString::number(pso->generation.at(pso->generateNUM).Gbest) <<","<<QString::number(pso->generateNUM)<<"\r\n";
    }
}

void ScatterGraph::ReTrain()
{
    ClearALL();
    initialPSO(ParticalNUM,inertiaweiNUM,personinfluNUM,socialinfluNUM,GroupSize);
    //cout << error << endl;
    while(pso->generation.at(pso->generateNUM).error>error)
    {GeneratePSO();
     CalError(pso->generateNUM);
     CalMean(pso->generateNUM);
     CalStandardDeviation(pso->generateNUM);
     MaxGenerate--;
     if(MaxGenerate<0)break;
    }
    isTrainOver = true;
    totaliterationsNUM->setText(QString::number(pso->generateNUM));

    QFile data("Gbest.txt");
    if (data.open(QFile::WriteOnly | QIODevice::Append)) {
        QTextStream out(&data);
        out << QString::number(pso->generation.at(pso->generateNUM).Gbest) <<","<<QString::number(pso->generateNUM)<<"\r\n";
    }
}

void ScatterGraph::ClearALL()
{

    pso = new PsoModel();
    NowShow = 0;
    isTrainOver = false;
    playflag = true;
    MaxGenerate = 5000;
    proxy     = new QScatterDataProxy();
    series    = new QScatter3DSeries(proxy);
    dataArray = new QScatterDataArray();
    m_graph->addSeries(series);

}
