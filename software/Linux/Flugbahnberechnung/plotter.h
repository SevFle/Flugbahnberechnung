#ifndef C_PLOTTER_H
#define C_PLOTTER_H
#include <QtDataVisualization/Q3DScatter>
#include <QValue3DAxis>

namespace plotter
  {
  enum series
    {
    prediction,
    realValue
    };

  class C_plotter
      {
    public:
      C_plotter();
      ~C_plotter();

      QtDataVisualization::Q3DScatter *graph;
  private:

      QtDataVisualization::QScatter3DSeries *seriesReal;
      QtDataVisualization::QScatter3DSeries *seriesPredicted;

      QtDataVisualization::QScatterDataArray* dataReal;
      QtDataVisualization::QScatterDataArray* dataPredicted;
      plotter::series* seriesType;

  public:
      void addSingleData(QVector3D point3D, enum series Type);
      void addTrackingeData(QVector3D actualPoint, QVector3D predPoint);
  private:
      void init();

      void pushData(QtDataVisualization::QScatterDataArray* data);

      };
  }

#endif // C_PLOTTER_H
