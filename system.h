#ifndef SYSTEM_H
#define SYSTEM_H

/*
 * Essa classe simula um sistema físico. Como muitos sistemas físicos possuem memória, ela armazena valores
 * da execução anterior, sendo necessário resetar ou criar um outro objeto para uma nova execução.
 * A função principal é a getOutput(double input) que retorna a saída do sistema para determinada entrada.
 */

class System
{
public:
    System();
    void reset();
    double getOutput(double input);
private:
    double x_1;
    double y_1;
    double x_2;
    double y_2;
    double x_3;
    double y_3;
};

#endif // SYSTEM_H
