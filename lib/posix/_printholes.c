#include "/usr/src/servers/is/inc.h"
#include "/usr/src/servers/pm/mproc.h"
#include <lib.h>
#include <math.h>
#include <unistd.h>

int calculate_median(int a[], int size) {
  int i, j, t, median;

  for (i = 1; i <= size - 1; i++) {
    for (j = 1; j <= size - i; j++) {
      if (a[j] <= a[j + 1]) {
        t = a[j];
        a[j] = a[j + 1];
        a[j + 1] = t;
      } else
        continue;
    }
  }

  if (size % 2 == 0)
    median = (a[size / 2] + a[size / 2 + 1]) / 2;
  else
    median = a[size / 2 + 1];

  return median;
}

PUBLIC void print_holes(void) {
  struct pm_mem_info pmi;
  int h, median, holes_avg, holes_sd, holes_median, sizes[_NR_HOLES];
  int num_holes = 0, total_holes_size = 0;
  float aux_sd = 0.0;
  int sd;

  if (getsysinfo(PM_PROC_NR, SI_MEM_ALLOC, &pmi) != 0) {
    printf("Obtaining memory hole list failed.\n");
    return;
  }

  for (h = 0; h < _NR_HOLES; h++) {
    if (pmi.pmi_holes[h].h_base && pmi.pmi_holes[h].h_len) {
      int bytes;
      num_holes++;
      bytes = (pmi.pmi_holes[h].h_len << CLICK_SHIFT);
      total_holes_size += bytes / 1024;
      sizes[h] = bytes / 1024;
    }
  }

  holes_avg = total_holes_size / num_holes;
  median = calculate_median(sizes, num_holes);

  for (h = 0; h < _NR_HOLES; h++) {
    if (pmi.pmi_holes[h].h_base && pmi.pmi_holes[h].h_len) {
      int bytes;
      bytes = (pmi.pmi_holes[h].h_len << CLICK_SHIFT);
      aux_sd += pow((bytes / 1024) - holes_avg, 2);
    }
  }
  sd = sqrt(aux_sd / num_holes);

  printf("\nTamanho medio:%dkB\tMediana:%dkB\tDesvio padrao:%dkB", holes_avg,
         median, sd);
}
