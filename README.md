# Calculadora de Terminal (C++)

Calculadora de linha de comando em C++17 que resolve expressões completas, respeitando a precedência dos operadores.

## Funcionalidades

- Operadores `+ - * / % ^` e parênteses
- Função `raiz(x)` (ou `sqrt(x)`)
- `ans` guarda o último resultado
- Aceita vírgula ou ponto como separador decimal
- Histórico da sessão
- Tratamento de erros (divisão por zero, parênteses, sintaxe)

## Estrutura

```
include/   cabeçalhos (.hpp)
src/       código-fonte (.cpp)
build/     executável gerado (ignorado pelo Git)
```

## Como compilar

Requer `g++` com suporte a C++17. Na raiz do projeto:

```bash
g++ -std=c++17 -Iinclude src/main.cpp src/menu.cpp src/parser.cpp src/operacoes.cpp src/historico.cpp src/formatacao.cpp -o build/calculadora
```

## Como usar

Modo interativo:

```bash
./build/calculadora        # Windows: .\build\calculadora.exe
```

```
> 2 + 3 * 4
= 14
> raiz(144) + ans
= 26
> 10 / 0
Erro: divisão por zero
```

Modo direto:

```bash
./build/calculadora "2 + 3 * (4 - 1)^2"
# 29
```

Comandos no modo interativo: `ajuda`, `hist`, `limpar`, `sair`.
