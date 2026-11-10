#include "formatacao.hpp"

#include <iomanip>
#include <sstream>

namespace calc {

std::string formatarNumero(double valor) {
    if (valor == 0.0) valor = 0.0;  // evita imprimir "-0"
    std::ostringstream ss;
    ss << std::setprecision(12) << valor;
    return ss.str();
}

}  // namespace calc
