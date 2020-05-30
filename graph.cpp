#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
    ui->chartWidget = new QWidget(this);
    ui->chartWidget->resize(720,530);
    ui->popSizeSpin->setRange(0,1000);
    ui->popSizeSpin->setValue(100);
    ui->crossSpin->setRange(0.0,1.0);
    ui->crossSpin->setValue(0.2);
    ui->mutationSpin->setRange(0.0,2.0);
    ui->mutationSpin->setValue(1.5);

    chart  = new QChart;
    chartView = new QChartView(chart);
    gridLayout = new QGridLayout(ui->chartWidget);
    gridLayout->addWidget(chartView,0,0);
    gridLayout->addWidget(ui->horizontalSlider,7,0);

    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;

    screenWidth = desktop->width(); // get width of screen
    screenHeight = desktop->height(); // get height of screen

    windowSize = size(); // size of our application window
    width = windowSize.width();
    height = windowSize.height();

    // little computations
    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;
    y -= 50;

    // move window to desired coordinates
    move ( x, y );

    played = 0;
    lastSave = -1;

    connect(ui->playButton,SIGNAL(released()),this,SLOT(startEvolution()));
    connect(ui->subjectSelection, SIGNAL(currentIndexChanged(int)),this, SLOT(showGraph(int)));
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(slider(int)));
    connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(printNoControl(bool)));
    connect(ui->saveButton,SIGNAL(released()),this,SLOT(saveCost()));
    connect(ui->clearButton,SIGNAL(released()),this,SLOT(clearCost()));
    connect(ui->displayButton,SIGNAL(released()),this,SLOT(displayCost()));
}

Graph::~Graph()
{
    delete ui;
}

void Graph::startEvolution()
{
    played++;
    Evolution evolution;
    Evolution::populationSize = ui->popSizeSpin->value();
    Evolution::MUTATION_CONST = ui->mutationSpin->value();
    Evolution::CROSSOVER_CONST = ui->crossSpin->value();

    best = evolution.startEvolution();

    std::vector<double> evolutionCost;
    costSeries = new QLineSeries();
    for(unsigned int i = 0; i < best.size(); i++)
    {
        evolutionCost.push_back(Simulation::getCost(best[i]));
        costSeries->append(i,evolutionCost[i]);
    }

    std::cout<<"\nNúmero de gerações: "<< best.size()<<std::endl;
    std::cout<<"Critério de parada: ";
    if(Evolution::stopCriterion == 0)
        std::cout<<" tempo\n";
    else if(Evolution::stopCriterion == 1)
        std::cout<<" custo mínimo\n";
    else if(Evolution::stopCriterion == 2)
        std::cout<<" convergência\n";
    else
        std::cout<<" capeta\n";

    ui->subjectSelection->clear();
    for(unsigned int i = 0; i < best.size(); i++)
        ui->subjectSelection->addItem("subject " + QString::number(i + 1));

    ui->horizontalSlider->setRange(0,best.size() -1);
}

void Graph::showGraph(int index)
{
    if(index < best.size() && index != -1)
    {

        std::vector<double> timeAxis;
        for(int i = 0; i < Simulation::amountOfPoints; i++)
        {
            timeAxis.push_back(i);
        }

        std::vector<double> yAxis = Simulation::getPoints(best[index]);
        double cost = Simulation::getCost(best[index]);
        ui->textEdit->setText("Cost: " + QString::number(cost));

        QLineSeries *series = new QLineSeries();

        for(unsigned int i = 0; i < timeAxis.size() - 1; i++)
            series->append(timeAxis[i],yAxis[i + 1]);

        chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();

        /////////////////////////////////////////////////////////////////////////////
        if(ui->checkBox->isChecked())
        {
            yAxis.clear();
            yAxis = Simulation::noControl();
            series = new QLineSeries();
            for(unsigned int i = 0; i < timeAxis.size() - 1; i++)
                series->append(timeAxis[i],yAxis[i + 1]);

            chart->addSeries(series);
        }
        /////////////////////////////////////////////////////////////////////////////

        std::string name = "Melhor indivíduo da geração: ";
        name += std::to_string(index + 1);
        chart->setTitle(name.c_str());

        chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        gridLayout->addWidget(chartView,0,0);

        this->show();
        QCoreApplication::processEvents();
    }
}

void Graph::printNoControl(bool c)
{
    showGraph(ui->subjectSelection->currentIndex());
}

void Graph::slider(int index)
{
    ui->subjectSelection->setCurrentIndex(index);
}

void Graph::saveCost()
{
    if(lastSave != played)
    {
        costFunction.push_back(costSeries);
    }
}
void Graph::clearCost()
{
    costFunction.clear();
}
void Graph::displayCost()
{
    if(!costFunction.empty())
    {
        chart = new QChart();
        chart->legend()->hide();
        for(unsigned int i = 0; i < costFunction.size();i++)
            chart->addSeries(costFunction[i]);
        chart->createDefaultAxes();
        chart->setTitle("Comparação entre evoluções");

        chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        ui->textEdit->clear();
        gridLayout->addWidget(chartView,0,0);

        this->show();
        QCoreApplication::processEvents();
    }
}
