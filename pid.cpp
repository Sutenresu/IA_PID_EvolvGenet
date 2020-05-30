#include "pid.h"

    /*
     * Os construtores servem apenas para definir as constantes do PID Kp, Ki e
     * Kd.
     */
    PID::PID()
    {
        firstLoop = true;
    }

    PID::PID(double sP)
    {
        setPoint = sP;
        firstLoop = true;
    }

    PID::PID(double sP, double kp, double ki, double kd)
    {
        setPoint = sP;
        Kp = kp;
        Ki = ki;
        Kd = kd;
        firstLoop = true;
    }

    void PID::setSetpoint(double sP)
    {
        setPoint = sP;
    }

    void PID::setPID(double kp, double ki, double kd)
    {
        Kp = kp;
        Ki = ki;
        Kd = kd;
    }

    void PID::setPID(double kp, double ki)
    {
        Kp = kp;
        Ki = ki;
        Kd = 0;
    }

    void PID::setPID(double kp)
    {
        Kp = kp;
        Ki = 0;
        Kd = 0;
    }

    void PID::calculateError(double in)
    {
        error = setPoint - in;
//        std::cout<<"Error:"<<error<<"\n";
    }

    double PID::getPID(double in)
    {
        double out;
        double p, i, d;

        calculateError(in);

        if (firstLoop) {
            previousError = error;
            firstLoop = false;
        }

        ierror += error;
        if (error * previousError < 0)
            ierror = 0;

        derror = previousError - error;

        p = Kp * error;
        i = Ki * ierror;
        d = Kd * derror;

        out = p + i + d;

        previousError = error;

        return out;
    }

    double PID::getError()
    {
        return error;
    }

    void PID::resetPID()
    {
        error = 0;
        ierror = 0;
        derror = 0;
        previousError = 0;
        firstLoop = true;
    }

    //~ double[] PID::pidInfo()
    //~ {
        //~ double[] info = { error, ierror, derror, previousError };
        //~ return info;
    //~ }

