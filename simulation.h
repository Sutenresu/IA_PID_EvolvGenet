#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "gene.h"
#include "pid.h"
#include "system.h"
#include <cmath>
#include <limits>

/*
 * Essa classe simula o comportamento de um individuo e possui uma função que retorna o custo - inversamente proporcional ao
 * fitness - do mesmo.
 * TODO: Transformar essa classe em uma interface para poder resolver problemas genéricos
 */

class Simulation
{
public:
    Simulation();
    static double getCost(Gene gene);
    static std::vector<double> getPoints(Gene gene);
    static std::vector<double> noControl();
    static const int amountOfPoints = 100;
private:
    static void calculate(Gene gene, double &cost, std::vector<double> &points);
};

#endif // SIMULATION_H
