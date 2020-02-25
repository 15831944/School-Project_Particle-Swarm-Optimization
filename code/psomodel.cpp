#include "psomodel.h"
#define PI 3.14159265359

PsoModel::PsoModel()
{}

double PsoModel::Ackley(double x,double y)
{
    return -20*exp(-0.2*sqrt((x*x+y*y)/3))-exp((cos(2*PI*x)+cos(2*PI*y))/3)+exp(1)+20 ;

}

double PsoModel::Ackley(double x,double y,double z)
{
    return -20*exp(-0.2*sqrt((x*x+y*y+z*z)/3))-exp((cos(2*PI*x)+cos(2*PI*y)+cos(2*PI*z))/3)+exp(1)+20 ;
}
