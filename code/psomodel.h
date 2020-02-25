#ifndef PSOMODEL_H
#define PSOMODEL_H

#include<string>
#include<cmath>
#include<vector>
#include"partical.h"

using namespace std;

class PsoModel
{
public:
    PsoModel();
    vector<Generation>generation;
    int particalNUM;
    int generateNUM;
    int GroupSize;
    double Ackley(double x,double y);
    double Ackley(double x,double y,double z);
    double** data;
};

#endif // PSOMODEL_H
