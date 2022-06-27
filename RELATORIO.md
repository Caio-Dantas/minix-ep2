# Relatório EP 2 - MAC0422

## Parte 1

Para implementar uma nova chamada de sistema seguimos os mesmos passos do EP
anterior, registrando um identificador numérico para a chamada em `callnr.h`,
adicionando um protótipo de função em `servers/pm/proto.h`, implementando a
chamada em `alloc.c` e associando um identificador numérico à chamada de sistema
usando a tabela do arquivo `servers/pm/table.c`.

Para expor essa nova chamada de sistema para o usuário, criamos uma função na
biblioteca de usuário `unistd` seguindo os seguintes passos:

1. Criamos um protótipo de função no arquivo `include/unistd.h`, assim como as
   macros facilitadoras **WORST_FIT**, **BEST_FIT** e **RANDOM_FIT**.

1. Adicionamos um novo arquivo `lib/posix/_changealoc.c` com a implementação da
   função de biblioteca.

1. Adicionamos o arquivo ao processo de compilação do Minix adicionando seu nome
   no Makefile da biblioteca (`lib/posix/Makefile.in`)

## Parte 2

Para possibilitar a convivência das diversas estratégias de alocação no nosso
sistema, primeiro criamos uma variável global chamada `aloc_strat` no arquivo
`servers/pm/alloc.c` que mantém a informação sobre qual é a estratégia
atualmente em vigor. Note que esse é o mesmo arquivo onde foi implementada a
chamada de sistema `do_changealoc` do item anterior, o que permite que a mudança
de estratégia seja tão simples como a modificação de uma variável. Com essa
variável, a função `alloc_mem` pode delegar (em tempo de execução) a escolha do
buraco a ser alocado para alguma das diferentes estratégias usando um simples
*switch case*.

Também criamos uma função (`use_hole`) para reduzir a repetição de código no
processo de reduzir ou deletar o buraco que foi escolhido pelo algoritmo de
alocação.

A implementação em si das estratégias de alocação foi feita usando os conceitos
delineados pelo livro da disciplina, sem nenhuma modificação muito
significativa.

## Parte 3

Como a nossa chamada de sistema foi adicionada à biblioteca `unistd.h`, a
implementação desse item consistiu apenas em traduzir o argumento de entrada
para um dos identificadores das estratégias de alocação e realizar a própria
chamada de sistema.

## Parte 4
