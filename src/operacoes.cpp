#include "operacoes.hpp"

#include <cmath>
#include <stdexcept>

namespace calc {

double somar(double a, double b) { return a + b; }

double subtrair(double a, double b) { return a - b; }

double multiplicar(double a, double b) { return a * b; }

double dividir(double a, double b) {
    if (b == 0.0) throw std::domain_error("divisão por zero");
    return a / b;
}

double modulo(double a, double b) {
    if (b == 0.0) throw std::domain_error("módulo por zero");
    return std::fmod(a, b);
}

double potencia(double base, double expoente) {
    double r = std::pow(base, expoente);
    if (std::isnan(r)) throw std::domain_error("potência inválida");
    return r;
}

double raizQuadrada(double x) {
    if (x < 0.0) throw std::domain_error("raiz quadrada de número negativo");
    return std::sqrt(x);
}

}  // namespace calc
