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
