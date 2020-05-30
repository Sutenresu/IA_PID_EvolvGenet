#ifndef PID_HPP_INCLUDED
#define PID_HPP_INCLUDED

#include <iostream>

/**
 * Esta classe foi criada para facilitar a utilização do PID. Como você já deve
 * saber a esta altura, utilizamos muito o PID. Muito mesmo. PID é vida.Seguir
 * uma linha, seguir uma referência da bússola ou se mover utilizando a parede
 * como referência são algumas das (infinitas) aplicações do PID. Se você não
 * faz ideia do que seja PID, dê uma olhada na NET. É uma das coisas mais lindas
 * que você vai ver hoje. Resumidamente, o PID é uma técnica de controle
 * utilizada para que seu sistema (no caso, seu robô) esteja onde você quer que
 * ele esteja. Você determina uma referência, o robô vê quão longe está dessa
 * referência, por meio de um sensor, e reage de acordo, ligando os motores mais
 * ou menos intensamente. Imagine que você queira andar em linha reta mantendo
 * uma distância fixa de 15 centímetros de uma parede qualquer. Imagine que para
 * isso você utilize o ultrassom. Se o ultrassom detectar 15, tudo bem, mas se
 * detectar 20, você deve ligar os motores de forma a se aproximar da parede
 * novamente. Não sei se ajudei muito, mas quando você vir o código, e der uma
 * olhadinha na net (Wikipedia pode sim), você vai entender melhor.
 *
 * @author SEK - EDROM
 *
 */

class PID
{
public:
    PID();
    PID(double sP);
    PID(double sP, double kp, double ki, double kd);

    /*
     * Aqui é setada a referência em que o robô deve se basear para saber se
     * está ou não onde deveria estar. Se você quiser seguir uma parede com um
     * ultrassom por exemplo, a uma distância de 15 cm, sua referência é 15.
     */
    void setSetpoint(double sP);

    /*
     * Caso você já tenha criado o objeto PID com determinadas constantes mas
     * deseja mudá-las, você pode utilizar estas funções de set.
     */
    void setPID(double kp, double ki, double kd);
    void setPID(double kp, double ki);
    void setPID(double kp);

    /**
     * Este método apenas calcula o erro, baseando-se na entrada (in) e no valor
     * de referência. Foi criado pela necessidade de calcular o erro de forma
     * diferente quando estamos lidando com a bússola. Para isto existe outra
     * classe de PID, esclusiva para a bússola, que sobrescreve este método.
     *
     * @param in
     */
    void calculateError(double in);

    /**
     * É onde a mágica realmente acontece. Um valor de entrada é passado para a
     * função e ela retorna a saída do PID realizando os cálculos necessário.
     * Esta saída é usada para o controle de um motor por exemplo.
     *
     * @param in
     * @return
     */
    double getPID(double in);

    /**
     * Esta função reseta as variáveis responsáveis por armazenar o erro, a
     * somatória do erro, e a variação do erro, pro caso de você querer começar
     * o PID do zero mesmo. Se você não faz ideia do que é somatória do erro,
     * variação do erro e erro, digite no google, "PID Wikipedia", abra o
     * primeiro link e seja feliz.
     */
    void resetPID();

    double getError();
    //~ /**
     //~ * Apenas uma função de get que retorna um vetor com todas as informações do
     //~ * PID nesta ordem: 1)erro; 2)somatória do erro; 3)variaçaõ do erro; 4)erro
     //~ * anterior.
     //~ *
     //~ * @return
     //~ */
    //~ double[] pidInfo();
private:
    double setPoint;
    double Kp, Ki, Kd;
    double error;
    double previousError;
    double ierror;
    double derror;
    bool firstLoop;
};

#endif
