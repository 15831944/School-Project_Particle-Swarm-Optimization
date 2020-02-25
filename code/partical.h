#ifndef PARTICAL_H
#define PARTICAL_H
#include <vector>

using namespace std;

class Partical
{
public:
    double Px,Py,Pz;
    double Value;
    double Vx,Vy,Vz;
    double pbest,pbestX,pbestY,pbestZ;
    bool  leader;
};

class Group
{
  public:
  vector<Partical> partical;
  double Groupbest,GroupbestX,GroupbestY,GroupbestZ;
  int in;
};

class Generation
{
  public:
  vector<Group> group;
  double Gbest,GbestX,GbestY,GbestZ;
  double error;
  double mean;
  double standarddeviation;
};

#endif // PARTICAL_H
