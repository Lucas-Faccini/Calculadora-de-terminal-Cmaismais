#pragma once

namespace calc {

// Operações aritméticas básicas.
// Funções com entradas inválidas lançam std::domain_error.
double somar(double a, double b);
double subtrair(double a, double b);
double multiplicar(double a, double b);
double dividir(double a, double b);
double modulo(double a, double b);
double potencia(double base, double expoente);
double raizQuadrada(double x);

}  // namespace calc
