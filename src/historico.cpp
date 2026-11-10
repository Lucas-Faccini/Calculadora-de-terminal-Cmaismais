#include "historico.hpp"

#include "formatacao.hpp"

namespace calc {

void Historico::adicionar(const std::string& expressao, double resultado) {
    entradas_.push_back({expressao, resultado});
}

void Historico::listar(std::ostream& out) const {
    if (entradas_.empty()) {
        out << "Histórico vazio.\n";
        return;
    }
    for (std::size_t i = 0; i < entradas_.size(); ++i) {
        out << "  " << (i + 1) << ") " << entradas_[i].expressao << " = "
            << formatarNumero(entradas_[i].resultado) << "\n";
    }
}

void Historico::limpar() { entradas_.clear(); }

std::size_t Historico::tamanho() const { return entradas_.size(); }

}  // namespace calc
