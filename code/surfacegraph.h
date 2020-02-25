#ifndef SURFACEGRAPH_H
#define SURFACEGRAPH_H

#include <Q3DSurface>
#include <QSurfaceDataProxy>
#include <QSurface3DSeries>
#include <psomodel.h>

using namespace QtDataVisualization;

class SurfaceGraph : public QObject
{
    Q_OBJECT
  public:
    explicit SurfaceGraph(Q3DSurface *surface);
    ~SurfaceGraph();
    void FunctionProxy();
    PsoModel *pso;
  private:
    Q3DSurface *m_graph;
    QSurfaceDataProxy *m_sqrtSinProxy;
    QSurface3DSeries  *m_sqrtSinSeries;
    double m_rangeMinX;
    double m_rangeMinZ;
    double m_stepX;
    double m_stepZ;
};

#endif // SURFACEGRAPH_H
