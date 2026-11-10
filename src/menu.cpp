#include "menu.hpp"

#include <algorithm>
#include <cctype>
#include <exception>
#include <string>

#include "formatacao.hpp"
#include "historico.hpp"
#include "parser.hpp"

namespace calc {
namespace {

std::string aparar(const std::string& s) {
    auto ini = std::find_if_not(s.begin(), s.end(), [](unsigned char c) { return std::isspace(c); });
    auto fim = std::find_if_not(s.rbegin(), s.rend(), [](unsigned char c) { return std::isspace(c); }).base();
    return (ini < fim) ? std::string(ini, fim) : std::string();
}

std::string minusculas(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}

}  // namespace

void mostrarAjuda(std::ostream& out) {
    out << "Digite uma expressão e pressione Enter. Exemplos:\n"
           "  2 + 3 * 4        (2 + 3) * 4       2 ^ 10\n"
           "  10 % 3           raiz(144)         ans * 2\n"
           "\n"
           "Operadores: + - * / % ^   |   Funções: raiz(x) ou sqrt(x)\n"
           "ans = último resultado    |   vírgula ou ponto como decimal\n"
           "\n"
           "Comandos:\n"
           "  ajuda       mostra esta ajuda\n"
           "  hist        mostra o histórico da sessão\n"
           "  limpar      apaga o histórico\n"
           "  sair        encerra o programa\n";
}

void executarRepl(std::istream& in, std::ostream& out) {
    Historico historico;
    double ans = 0.0;

    out << "=== Calculadora de Terminal ===\n";
    mostrarAjuda(out);
    out << "\n";

    std::string linha;
    while (true) {
        out << "> " << std::flush;
        if (!std::getline(in, linha)) break;

        linha = aparar(linha);
        if (linha.empty()) continue;

        const std::string cmd = minusculas(linha);
        if (cmd == "sair" || cmd == "exit" || cmd == "q") break;
        if (cmd == "ajuda" || cmd == "help") {
            mostrarAjuda(out);
            continue;
        }
        if (cmd == "hist" || cmd == "historico" || cmd == "histórico") {
            historico.listar(out);
            continue;
        }
        if (cmd == "limpar") {
            historico.limpar();
            out << "Histórico apagado.\n";
            continue;
        }

        try {
            double resultado = avaliar(linha, ans);
            ans = resultado;
            historico.adicionar(linha, resultado);
            out << "= " << formatarNumero(resultado) << "\n";
        } catch (const std::exception& e) {
            out << "Erro: " << e.what() << "\n";
        }
    }
    out << "Até logo!\n";
}

}  // namespace calc
