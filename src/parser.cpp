#include "parser.hpp"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <stdexcept>

#include "operacoes.hpp"

namespace calc {
namespace {

// Analisador descendente recursivo. Gramática (da menor para a maior precedência):
//   expressao := termo (('+' | '-') termo)*
//   termo     := unario (('*' | '/' | '%') unario)*
//   unario    := ('-' | '+') unario | fator
//   fator     := primario ('^' unario)?
//   primario  := numero | '(' expressao ')' | identificador
class Avaliador {
public:
    Avaliador(const std::string& texto, double ans) : t_(texto), ans_(ans) {}

    double executar() {
        double v = expressao();
        pular();
        if (pos_ < t_.size()) {
            throw std::invalid_argument(std::string("caractere inesperado '") + t_[pos_] + "'");
        }
        return v;
    }

private:
    std::string t_;
    double ans_;
    std::size_t pos_ = 0;

    void pular() {
        while (pos_ < t_.size() && std::isspace(static_cast<unsigned char>(t_[pos_]))) ++pos_;
    }

    bool consumir(char c) {
        pular();
        if (pos_ < t_.size() && t_[pos_] == c) {
            ++pos_;
            return true;
        }
        return false;
    }

    double expressao() {
        double v = termo();
        for (;;) {
            if (consumir('+')) v = somar(v, termo());
            else if (consumir('-')) v = subtrair(v, termo());
            else return v;
        }
    }

    double termo() {
        double v = unario();
        for (;;) {
            if (consumir('*')) v = multiplicar(v, unario());
            else if (consumir('/')) v = dividir(v, unario());
            else if (consumir('%')) v = modulo(v, unario());
            else return v;
        }
    }

    double unario() {
        if (consumir('-')) return -unario();
        if (consumir('+')) return unario();
        return fator();
    }

    double fator() {
        double base = primario();
        if (consumir('^')) return potencia(base, unario());  // associativa à direita
        return base;
    }

    double primario() {
        pular();
        if (pos_ >= t_.size()) throw std::invalid_argument("expressão incompleta");
        char c = t_[pos_];
        if (c == '(') {
            ++pos_;
            double v = expressao();
            if (!consumir(')')) throw std::invalid_argument("faltou fechar parênteses");
            return v;
        }
        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') return numero();
        if (std::isalpha(static_cast<unsigned char>(c))) return identificador();
        throw std::invalid_argument(std::string("caractere inesperado '") + c + "'");
    }

    double numero() {
        std::size_t ini = pos_;
        bool ponto = false;
        int digitos = 0;
        while (pos_ < t_.size()) {
            char c = t_[pos_];
            if (std::isdigit(static_cast<unsigned char>(c))) {
                ++digitos;
                ++pos_;
            } else if (c == '.' && !ponto) {
                ponto = true;
                ++pos_;
            } else {
                break;
            }
        }
        if (digitos == 0) throw std::invalid_argument("número inválido");
        return std::stod(t_.substr(ini, pos_ - ini));
    }

    double identificador() {
        std::size_t ini = pos_;
        while (pos_ < t_.size() && std::isalpha(static_cast<unsigned char>(t_[pos_]))) ++pos_;
        std::string nome = t_.substr(ini, pos_ - ini);
        std::transform(nome.begin(), nome.end(), nome.begin(),
                       [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

        if (nome == "ans") return ans_;
        if (nome == "sqrt" || nome == "raiz") {
            if (!consumir('(')) throw std::invalid_argument("esperado '(' após " + nome);
            double v = expressao();
            if (!consumir(')')) throw std::invalid_argument("faltou fechar parênteses");
            return raizQuadrada(v);
        }
        throw std::invalid_argument("função ou variável desconhecida: " + nome);
    }
};

}  // namespace

double avaliar(const std::string& expressao, double ans) {
    std::string texto = expressao;
    std::replace(texto.begin(), texto.end(), ',', '.');  // aceita 3,5 como 3.5
    return Avaliador(texto, ans).executar();
}

}  // namespace calc
