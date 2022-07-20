---
title: EP 3 --- MAC0422
author:
    - Caio Dantas Simão Ugêda, Nº USP:11796868
    - Daniel Pessoa Cardeal, Nº USP:10693170
---
# Parte 1

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

# Parte 2

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

# Parte 3

Como a nossa chamada de sistema foi adicionada à biblioteca `unistd.h`, a
implementação desse item consistiu apenas em traduzir o argumento de entrada
para um dos identificadores das estratégias de alocação e realizar a própria
chamada de sistema.

# Parte 4

Para implementar o programa de usuário `memstat.c` foi necessário incluir um
novo arquivo (`_printholes.c`) a biblioteca posix presente no minix para que
pudéssemos obter e exibir as informações necessárias referente ao buracos
presentes na memória do sistema. Mais adentro da implementação de `printholes`,
foi necessário utilizar a chamada de sistema `getsysinfo` com o argumento
`SI_MEM_ALLOC` para que obtivéssemos as informações necessárias referente aos
buracos na memória, com essa informação podemos contar a quantidade de buracos,
calcular a média dos tamanhos, a mediana e o desvio padrão, todas informações
são exibidas com um `printf` ao ser executado `print_holes`. No nosso arquivo de
usuário `memstat.c` chamamos `print_holes` a cada 1 segundo de intervalo e
evitando o bloqueio da saída padrão. Todas informações sao exibidas na unidade
kyloByte (kB).
