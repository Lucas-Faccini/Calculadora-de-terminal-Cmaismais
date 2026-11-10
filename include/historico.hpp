#pragma once

#include <cstddef>
#include <ostream>
#include <string>
#include <vector>

namespace calc {

// Guarda as expressões calculadas na sessão atual.
class Historico {
public:
    void adicionar(const std::string& expressao, double resultado);
    void listar(std::ostream& out) const;
    void limpar();
    std::size_t tamanho() const;

private:
    struct Entrada {
        std::string expressao;
        double resultado;
    };
    std::vector<Entrada> entradas_;
};

}  // namespace calc
