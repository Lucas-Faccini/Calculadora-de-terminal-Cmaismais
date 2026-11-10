#pragma once

#include <string>

namespace calc {

// Converte um número em texto legível (até 12 dígitos significativos),
// evitando ruídos como 0.30000000000000004.
std::string formatarNumero(double valor);

}  // namespace calc
