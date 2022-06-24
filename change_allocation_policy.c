#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int get_aloc_strategy(const char *strategy_string);

int main(int argc, char *argv[]) {
  int strategy, result;
  if (argc < 2) {
    printf("Argumentos insuficientes\n");
    return EXIT_FAILURE;
  }
  strategy = get_aloc_strategy(argv[1]);
  if (strategy == -1) {
    printf("Argumento invalido\n");
    return EXIT_FAILURE;
  }
  result = changealoc(strategy);
  if (result < 0 || result > 4) {
    printf("Nao foi possivel alterar a estrategia\n");
    return EXIT_FAILURE;
  }
  printf("Estrategia alterada com sucesso. Nova estrategia: %d\n", strategy);
  return EXIT_SUCCESS;
}

int get_aloc_strategy(const char *strategy_string) {
  if (strcmp(strategy_string, "first_fit") == 0) {
    return FIRST_FIT;
  } else if (strcmp(strategy_string, "worst_fit") == 0) {
    return WORST_FIT;
  } else if (strcmp(strategy_string, "best_fit") == 0) {
    return BEST_FIT;
  } else if (strcmp(strategy_string, "random_fit") == 0) {
    return RANDOM_FIT;
  }
  return -1;
}
