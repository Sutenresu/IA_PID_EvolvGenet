#ifndef GENE_H
#define GENE_H

#include <vector>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>

/*
 * Essa classe está sendo usada para representar um indivíduo, existe uma variável estática que indica o
 * tamanho do vetor de genes. Foi decidido torná-la estática já que todos os indíviduos da população
 * possuem o mesmo tipo de gene. O vetor de genes em si, no caso sendo do tipo double. Os construtores
 * podem ou iniciar o vetor de forma aleatória (default) ou já inicializar com algum valor.
 * Devido a forma que o código foi feito ela se tornou um pouco desnecessária,
 * sendo usada apenas por organização. O acesso ao vetor de genes acabou sendo
 * colocado como público para facilitar a implementação, mas perdendo o encapsulamento do código.
 */

class Gene
{
public:
    //O construtor default deve ser chamado quando uma inicialização aleatória do gene for desejada
    Gene();
    //Construtor que já inicializa o vetor de genes
    Gene(std::vector<double> gene);
    //Quantidade de variáveis no vetor, é estático pois todos individuos da mesma popolação terão o mesmo tamanho
    static int geneSize;
    void setGenes(std::vector<double> gene);
    std::vector<double> genes;
};

#endif // GENE_H
