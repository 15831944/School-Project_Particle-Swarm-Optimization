#ifndef FUNCTION_H
#define FUNCTION_H

#include <qwt3d_function.h>
#include <math.h>

using namespace Qwt3D;

class Ackley : public Function
{
public:

    Ackley(SurfacePlot& pw)
    :Function(pw)
    {
    }

    double operator()(double x, double y)
    {
        return -20*exp(-0.2*sqrt((x*x+y*y)/3))-exp((cos(2*PI*x)+cos(2*PI*y))/3)+exp(1)+20 ;
    }
};

#endif // FUNCTION_H
