#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char * argv[]) {
  while(1) {
  	print_holes();
	  fflush(stdout);
	sleep(1);
  }
  return 0;
}
