#include "simulation.h"

Simulation::Simulation()
{
}

double Simulation::getCost(Gene gene)
{
    double cost;
    std::vector<double> points;
    calculate(gene, cost, points);
    return cost;
}

std::vector<double> Simulation::getPoints(Gene gene)
{
    double cost = 0;
    std::vector<double> points;
    calculate(gene, cost, points);
    return points;
}

void Simulation::calculate(Gene gene, double &cost,std::vector<double> &points)
{
    double absMeanError = 0;
    double overshoot = -1;
    double settlingTime = amountOfPoints;
    bool reachedRegime = false;
    bool instable = false;

    PID pid;
    System system;
    std::vector<double> y;
    std::vector<double> error;
    double input = 0;
    y.resize(amountOfPoints);
    error.resize(amountOfPoints);
    input = pid.getPID(0);
    y[0] = system.getOutput(input);
    error[0] = pid.getError();

    double kp = gene.genes[0];
    double ki = gene.genes[1];
    double kd = gene.genes[2];
    pid.setPID(kp,ki,kd);

    //Degrau unitário
    pid.setSetpoint(1);

    for(int i = 0; i < amountOfPoints - 1; i++)
    {
        input = pid.getPID(y[i]);
        y[i + 1] = system.getOutput(input);
        error[i + 1] = pid.getError();

        if(error[i+1] > 100)
            instable = true;

        if(y[i] > overshoot)
            overshoot = y[i];
        if((y[i] > 0.98 && y[i] < 1.02) && reachedRegime == false)
        {
            settlingTime = i;
            reachedRegime = true;
        }

        if((y[i] > 1.02 || y[i] < 0.98) && reachedRegime == true)
        {
            settlingTime = amountOfPoints;
            reachedRegime = false;
        }
    }
    if(instable)
        cost = std::numeric_limits<double>::infinity();
    else
    {
        if(overshoot > 1)
            overshoot = overshoot - 1;
        else
            overshoot = 0;

        for(int i = 0; i < amountOfPoints; i++)
            absMeanError += std::abs(error[i]);

    //    std::cout<<"Abs:"<< absMeanError<<std::endl;
        absMeanError /= amountOfPoints;

//        cost = absMeanError + overshoot + settlingTime/(amountOfPoints*1.0);
       cost = absMeanError;
        //Segurança para evitar crescimento excessivo de constante:
        if(kp > 15 || ki > 15 || kd > 15)
            cost +=1;

        //Segurança para evitar constante negativa:
        if(kp < 0 || ki < 0 || kd < 0)
            cost +=1;

    }

    for(int j = 0; j < amountOfPoints; j++)
        points.push_back(y[j]);
}

std::vector<double> Simulation::noControl()
{
    std::vector<double> y;
    System system;
    for(int i = 0; i < amountOfPoints; i++)
    {
        y.push_back(system.getOutput(1));
    }
    return y;
}
