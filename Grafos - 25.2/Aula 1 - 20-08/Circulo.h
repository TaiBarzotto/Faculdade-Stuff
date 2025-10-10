#ifndef CIRCULO_H
#define CIRCULO_H

class Circulo
{
private:
    double raio_;
public:
    Circulo(double raio);

    double calcula_area();
    void imprime_area();
};

#endif