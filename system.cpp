#include "system.h"

/*
 * Classe que simula um sistema qualquer, no caso, apenas sistemas SISO(single input single output) podem ser usados
 * TODO:Transformar em uma interface para tornar mais genérico
 */


System::System()
{
   reset();
}

void System::reset()
{
    x_1 = 0;
    y_1 = 0;
    x_2 = 0;
    y_2 = 0;
    x_3 = 0;
    y_3 = 0;
}

double System::getOutput(double input)
{
    double y = 0.09516*x_1 + 0.9048*y_1;
    x_1 = input;
    y_1 = y;


//    double y = 3.301*y_1 - 3.279*y_2 + 0.982*y_3 + 0.02318*x_1 - 0.000142*x_2 - 0.02304*x_3;
//    x_1 = input;
//    y_1 = y;
//    x_2 = x_1;
//    y_2 = y_1;
//    x_3 = x_2;
//    y_3 = y_2;


     return y;
}
