#pragma once

#include <iostream>

namespace calc {

// Exibe os comandos e exemplos disponíveis.
void mostrarAjuda(std::ostream& out);

// Laço interativo (REPL): lê expressões ou comandos até "sair" ou fim da entrada.
void executarRepl(std::istream& in, std::ostream& out);

}  // namespace calc
