# Relatório EP 2 - MAC0422

## Parte 1

A lista _hooks_ do arquivo `dmp.c`[^1] associa teclas de função com a execução de
rotinas do kernel. Nesta, a tecla F4 já é mapeada para executar a função
`privileges_dmp`[^2], o que significa que nós só tivemos que alterar o corpo
desta função para mostrar as informações que nos interessavam.

Em nossa implementação, tomamos como base a função `sched_dmp`[^3], que já
recuperava e iterava em ordem de privilégio sobre as filas de processos
gerenciadas pelo escalonador, e a modificamos para imprimir as informações de
interesse.

[^1]: caminho do arquivo `/usr/src/servers/is/dmp.c` 
[^2]: encontrada na linha 351 do arquivo `/usr/src/servers/is/dmp_kernel.c` 
[^3]: encontrada na linha 227 do arquivo `/usr/src/servers/is/dmp_kernel.c` 

## Parte 2

Para criar uma _syscall_ no Minix, tivemos que seguir os seguintes passos:

1. Adicionar um **protótipo de função** em alguma biblioteca de sistema para
   fazer com que programas de usuário possam chamar nossa nova _syscall_. Isso
   pode ser feito tanto em uma biblioteca já existente (como a `unistd.h`)
   quanto em uma nova biblioteca. Todas as bibliotecas de sistema podem ser
   encontradas em `/usr/src/include`.

1. Adicionar um identificador numérico para a _syscall_ em
   `/usr/src/include/minix/callnr.h`, assim como aumentar o número de chamadas
   de systema existentes (`NCALLS`). Esse identificador será importante para os
   próximos passos.

1. Adicionar o **corpo da chamada**, ou seja, uma função com a mesma assinatura
   que o protótipo do primeiro item que implementa efetivamente a chamada da
   _syscall_. Como ambas nossas chamadas de sistemas são relacionadas ao
   _process manager_, essa função vai enviar uma mensagem ao _process manager_
   (aqui identificado como `MM`) pedindo que ele execute a chamada indicada por
   um identificador numérico e com uma dada mensagem:

   ```c
_syscall(MM, IDENTIFICADOR_NUMERICO, &mensagem)
   ```

   Nesse contexto, a mensagem é um _payload_ de dados que pode ser usada para
   passar informações à _syscall_ como, por exemplo, o `pid` do processo filho
   que queremos modificar.

Com os três passos acima, o Minix já consegue relacionar uma requisição de
chamda de sistema feita por um programa de usuário com uma requisição de
execução de chamada de sistema no _process manager_. No entanto, o _process
manager_ ainda não sabe como executar essa chamada de sistema. Para registrar o
que o _PM_ deve fazer, temos que seguir os seguintes passos:

1. Criar um **protótipo de função** para a função que vai executar a
   requisição. Como quem vai tratar da nossa requisição é o _process manager_,
   esse protótipo deve ser adicionado no arquivo `/usr/src/servers/pm/proto.h`.
   Por padrão, os nomes dos protótipos seguem a forma `do_chamadaDeSistema`.

1. Associar o protótipo ao identificador numérico da _syscall_ na tabela do
   _process manager_ (`usr/src/servers/pm/table.c`). Aqui é **muito
   importante** que a posição do protótipo no vetor `call_vec` seja
   **exatamente igual** ao identificador numérico da chamada de sistema, para
   que a associação seja feita corretamente.

1. Implementar o **corpo da função** em algum arquivo C dentro do diretório
   `/usr/src/servers/pm/`.

Com isso feito, basta recompilar o _kernel_ e testar a _syscall_ usando a
biblioteca em que adicionamos a chamada de sistema.

### TODOs

- Explicar onde devemos adicionar o corpo da chamada da syscall na parte 2
- Apontar os arquivos que foram modificados para facilitar a correção
- Explicar como funcionam nossas syscalls

### OBS

- Podemos encontrar a prioridade mínima e máxima de tarefas de usuário no
  arquivo `kernel/proc.h` próximo à linha 85.
