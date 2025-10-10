#include "Circulo.h"
#include "bits/stdc++.h"

using namespace std;

// Implementações das funções

Circulo::Circulo(double raio) {
    raio_ = raio;
    // this->raio_ = raio;
}

double Circulo::calcula_area(){
    double area;
    area = 3.14 * raio_ * raio_;
    return area;
}

void Circulo::imprime_area(){
    cout << calcula_area() << "\n";
}