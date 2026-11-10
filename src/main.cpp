#include <exception>
#include <iostream>
#include <string>

#include "formatacao.hpp"
#include "menu.hpp"
#include "parser.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

// Uso:
//   calculadora                -> modo interativo
//   calculadora "2 + 3 * 4"    -> calcula e imprime o resultado
int main(int argc, char* argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // acentos corretos no terminal do Windows
    SetConsoleCP(CP_UTF8);
#endif

    if (argc > 1) {
        std::string expressao;
        for (int i = 1; i < argc; ++i) {
            if (i > 1) expressao += ' ';
            expressao += argv[i];
        }
        try {
            std::cout << calc::formatarNumero(calc::avaliar(expressao)) << "\n";
            return 0;
        } catch (const std::exception& e) {
            std::cerr << "Erro: " << e.what() << "\n";
            return 1;
        }
    }

    calc::executarRepl(std::cin, std::cout);
    return 0;
}
