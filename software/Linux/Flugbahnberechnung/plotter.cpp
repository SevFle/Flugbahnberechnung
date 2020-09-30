#include "plotter.h"

using namespace plotter;

C_plotter::C_plotter()
  {
  this->graph = new QtDataVisualization::Q3DScatter;
  this->seriesReal  = new QtDataVisualization::QScatter3DSeries;
  this->dataReal    = new QtDataVisualization::QScatterDataArray;
  this->seriesPredicted  = new QtDataVisualization::QScatter3DSeries;
  this->dataPredicted    = new QtDataVisualization::QScatterDataArray;

  seriesType    = new plotter::series;
  init();
  }
C_plotter::~C_plotter()
  {
  delete (seriesType);
  delete (dataPredicted);
  delete (seriesPredicted);
  delete (dataReal);
  delete (seriesReal);

  delete (graph);
  }

void C_plotter::init()
  {
  //this->scatter->setFlags(scatter->flags() ^ Qt::FramelessWindowHint);
  graph->setShadowQuality(QtDataVisualization::QAbstract3DGraph::ShadowQualityNone);
  seriesPredicted->setBaseColor(QColor(255, 0, 0, 127));
  graph->axisX()->setTitle("X-Achse");
  graph->axisY()->setTitle("Y-Achse");
  graph->axisZ()->setTitle("Z-Achse");
  QFont font = graph->activeTheme()->font();
  font.setPointSize(2);
  auto *axisX = new QtDataVisualization::QValue3DAxis;
  auto *axisY = new QtDataVisualization::QValue3DAxis;
  auto *axisZ = new QtDataVisualization::QValue3DAxis;

  graph->setAspectRatio(10.0);
  graph->setHorizontalAspectRatio(10.0);

  axisX->setRange(0, 10);
  //axisY->setSegmentCount(10);
  //axisX->setLabelFormat("%.2f");
 graph->setAxisX(axisX);
  graph->setAxisY(axisY);
 graph->setAxisZ(axisZ);
  }
void C_plotter::addSingleData(QVector3D point3D, enum series Type)
  {
  *seriesType = Type;
  //QVector3D(0.5f, 0.5f, 0.5f)
  switch (*seriesType)
    {
    case prediction:
      *dataPredicted << point3D;
      pushData(dataPredicted);
      break;
    case realValue:
      *dataReal << point3D;
      pushData(dataReal);
      break;
    }
  }
void C_plotter::addTrackingeData(QVector3D actualPoint, QVector3D predPoint)
  {
  *dataPredicted << predPoint;
  *dataReal      << actualPoint;
  seriesPredicted->dataProxy()->addItems  (*dataPredicted);
  seriesReal->dataProxy()->addItems       (*dataReal);
  graph->addSeries                        (seriesPredicted);
  graph->addSeries                        (seriesReal);
  }
void C_plotter::pushData(QtDataVisualization::QScatterDataArray *data)
  {
  switch (*seriesType)
    {
    case prediction:
      seriesPredicted->dataProxy()->addItems(*data);
      graph->addSeries(seriesPredicted);

      break;
    case realValue:
      seriesReal->dataProxy()->addItems(*data);
      graph->addSeries(seriesReal);
      break;
    }
  }
