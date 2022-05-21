#include <lockprioritylib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define PRIORIDADE 5
#define MAX_SEC 10

int main(void) {
  int pid, r, out;

  pid = getpid();
  printf("PID pai: %d\n", pid);

  pid = fork();
  if (pid != 0) { /* ======= Processo pai ======== */
    printf("PID filho: %d\n", pid);
    r = lockpriority(pid, PRIORIDADE);
    printf("Resultado de lockpriority: %d\n", r);
    waitpid(pid, &out, 0);
  } else { /* ======= Processo filho ======== */
    while (1) {
      int soma, i;
      soma = 0;
      for (i = 0; i < 1000; i++)
        soma += 1;
    }
  }
  return 0;
}
