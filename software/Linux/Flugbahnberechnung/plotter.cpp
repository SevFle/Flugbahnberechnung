#include "plotter.h"

using namespace plotter;

C_plotter::C_plotter()
  {
  this->scatter = new QtDataVisualization::Q3DScatter;
  this->series  = new QtDataVisualization::QScatter3DSeries;
  this->data    = new QtDataVisualization::QScatterDataArray;
  init();
  }
C_plotter::~C_plotter()
  {
  delete (data);
  delete (series);
  delete (scatter);
  }

void C_plotter::init()
  {
  this->scatter->setFlags(scatter->flags() ^ Qt::FramelessWindowHint);
  }
void C_plotter::addSingleData(QVector3D point3D)
  {
  //QVector3D(0.5f, 0.5f, 0.5f)
  *this->data << point3D;
  }
void C_plotter::addTrackingeData(QVector3D actualPoint, QVector3D predPoint)
  {
  *this->data << actualPoint << predPoint;
  }
void C_plotter::pushData()
  {
  series->dataProxy()->addItems(*this->data);
  scatter->addSeries(series);
  }
void C_plotter::show()
  {
  this->scatter->show();
  }
void C_plotter::close()
  {
  this->scatter->close();
  }
