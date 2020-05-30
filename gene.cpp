#include "gene.h"

int Gene::geneSize = 0;

Gene::Gene()
{
	genes.resize(geneSize);
    for(int i = 0; i < geneSize; i ++)
    {
        genes[i] = (rand()%5000)/5000.0;
    }
}

Gene::Gene(std::vector<double> gene)
{
    setGenes(gene);
}

void Gene::setGenes(std::vector<double> gene)
{
    for(int i = 0; i < geneSize; i ++)
        genes[i] = gene[i];
}

