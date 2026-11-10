#pragma once

#include <string>

namespace calc {

// Avalia uma expressão matemática, por exemplo "2 + 3 * (4 - 1)^2".
//
// Suporta: + - * / % ^, parênteses, sinais unários, sqrt()/raiz(),
// a variável "ans" (último resultado) e vírgula como separador decimal.
//
// Lança std::invalid_argument para erros de sintaxe e
// std::domain_error para erros matemáticos.
double avaliar(const std::string& expressao, double ans = 0.0);

}  // namespace calc
