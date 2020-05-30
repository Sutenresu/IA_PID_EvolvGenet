#include "evolution.h"
#define TESTING_EVOLUTION

int Evolution::generationNumber = 0;
int Evolution::stopCriterion = -1;
int Evolution::populationSize = 100;
double Evolution::MUTATION_CONST = 1.5;
double Evolution::CROSSOVER_CONST= 0.2;


Evolution::Evolution()
{

    generation = 0;
    Gene::geneSize = 3;
    populationSize = 100;

 
    subject.resize(populationSize);
    mutation.resize(populationSize);
    crossover.resize(populationSize);
    newGeneration.resize(populationSize);
    lowerGenerationCost = std::numeric_limits<double>::infinity();

    for(int i = 0; i < populationSize; i++)
        subject[i] = Gene();

}

std::vector<Gene> Evolution::startEvolution(int maximumTime, double limitCost)
{
    std::vector<Gene> evolutionResult;
    generationNumber = 0;
    stopCriterion = -1;
    generation = 0;
    int lowCostDifference = 0;
    double lastGenBestCost = 0;
    time_t startTime = time(0);

    while(true)
    {
        ///////////////////////////////////////////////////////////////////////////////////////////////////////
        //Critérios de parada

        //Tempo de execução
        double minutes = difftime(time(0),startTime)/60.0 ;
        if(minutes > maximumTime)
        {
            stopCriterion = 0;
            break;
        }
        //Custo - Aqui estamos avaliando o menor custo da ultima geração executada
        if(lowerGenerationCost <= limitCost)
        {
            stopCriterion = 1;
            break;
        }
        //Diferença de custo entre as gerações
        if(std::abs(lastGenBestCost - lowerGenerationCost) < 0.00005)
            lowCostDifference++;
        else
            lowCostDifference = 0;

        //Atualizando a informação
        lastGenBestCost = lowerGenerationCost;

        if(lowCostDifference == 50)
        {
            stopCriterion = 2;
            break;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Evolução diferencial:
        //Resetando a informação do menor custo da geração
         lowerGenerationCost = std::numeric_limits<double>::infinity();

        //Mutação
        for(int i = 0; i < populationSize; i++)
        {
            Gene newGene;
            std::vector<double> values;
            values.resize(Gene::geneSize);

            int jIndex = rand() % populationSize;
            int lIndex = rand() % populationSize;

            for(int j = 0; j < Gene::geneSize; j++)
                values[j] = subject[i].genes[j] +  MUTATION_CONST*(subject[jIndex].genes[j] - subject[lIndex].genes[j]);
            newGene.setGenes(values);
            mutation[i] = newGene;
        }

        //Cruzamento
        for(int i = 0; i < populationSize; i++)
        {
            for(int j = 0; j < Gene::geneSize; j++)
            {
                double compareCR = rand()/RAND_MAX;
                int crossPoint = rand()%Gene::geneSize;
                if(crossPoint == j || compareCR > CROSSOVER_CONST)
                    crossover[i].genes[j] = mutation[i].genes[j];
                else
                    crossover[i].genes[j] = subject[i].genes[j];

            }
        }

        //Seleção
        for(int i = 0; i < populationSize; i++)
        {

            double subjectCost = Simulation::getCost(subject[i]);
            double sonCost = Simulation::getCost(crossover[i]);

            //Como estamos trabalhando com o custo, se o indíviduo original tiver custo menor do que seu filho
            //ele é considerado melhor, e passará para próxima geração.
            if(subjectCost <= sonCost)
            {
                newGeneration[i] = subject[i];

                //Verificação do melhor individuo da geração
                if(subjectCost < lowerGenerationCost)
                {
                    lowerGenerationCost = subjectCost;
                    bestSubject = subject[i];
                }
            }
            else
            {
                newGeneration[i] = crossover[i];

                //Verificação do melhor individuo da geração
                if(sonCost < lowerGenerationCost)
                {
                    lowerGenerationCost = sonCost;
                    bestSubject = crossover[i];
                }
            }
        }
        evolutionResult.push_back(bestSubject);

        //Atualizando a nova geração
        for(int i = 0; i < populationSize; i++)
            subject[i] = newGeneration[i];

        generation++;

    #ifdef TESTING_EVOLUTION
        std::cout<<"Menor custo na geração "<< generation << " foi: "<< lowerGenerationCost<<std::endl;
        std::cout<<"Kp:"<<bestSubject.genes[0]<<std::endl;
        std::cout<<"Ki:"<<bestSubject.genes[1]<<std::endl;
        std::cout<<"Kd:"<<bestSubject.genes[2]<<std::endl;
    #endif
    }
    return evolutionResult;
}
