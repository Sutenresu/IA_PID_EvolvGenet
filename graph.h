#ifndef GRAPH_H
#define GRAPH_H

#include <QMainWindow>
#include <QDesktopWidget>
#include <vector>
#include <gene.h>
#include <simulation.h>
#include "evolution.h"
#include <QGridLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QCoreApplication>
#include <QDoubleSpinBox>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Graph;
}

class Graph : public QMainWindow
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = 0);
    ~Graph();
private slots:
    void startEvolution();
    void showGraph(int index);
    void slider(int index);
    void printNoControl(bool c);
    void saveCost();
    void clearCost();
    void displayCost();
private:
    Ui::Graph *ui;
    QGridLayout* gridLayout;
    QChart *chart;
    QChartView *chartView;
    std::vector<QLineSeries *> costFunction;
    QLineSeries *costSeries;
    std::vector<Gene> best;
    int played;
    int lastSave;
};

#endif // GRAPH_H
