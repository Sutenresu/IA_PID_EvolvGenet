#ifndef EVOLUTION_H
#define EVOLUTION_H

#include "gene.h"
#include "simulation.h"
#include <vector>
#include <time.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <limits>

/*
 * Essa classe implementa a evolução diferencial em si. A organização do código ficou bem parecida com a original
 * do Matlab.
 */

class Evolution
{
public:
    Evolution();
    /*
     *Função que inicia o processo de evolução
     * O tempo da função está em minutos, o limitCost é o custo mínimo desejado se algum individuo chegar nesse valor a
     * evolução para.
     */
    std::vector<Gene> startEvolution(int time = 1,double limitCost = 0);
    static int generationNumber;
    static int stopCriterion;
    static int populationSize;
    static double MUTATION_CONST;
    static double CROSSOVER_CONST;
private:
    int generation;
    double lowerGenerationCost;
    Gene bestSubject;
    std::vector<Gene> subject;
    std::vector<Gene> mutation;
    std::vector<Gene> crossover;
    std::vector<Gene> newGeneration;
};

#endif // EVOLUTION_H
