#ifndef C_PLOTTER_H
#define C_PLOTTER_H
#include <QtDataVisualization/Q3DScatter>


namespace plotter
  {
  class C_plotter
      {
    public:
      C_plotter();
      ~C_plotter();

      QtDataVisualization::Q3DScatter *scatter;

      QtDataVisualization::QScatter3DSeries *series;

      QtDataVisualization::QScatterDataArray* data;


      void init();
      void addSingleData(QVector3D point3D);
      void addTrackingeData(QVector3D actualPoint, QVector3D predPoint);
      void pushData();
      void show();
      void close();

      };
  }

#endif // C_PLOTTER_H
