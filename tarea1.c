#include "types.h"
#include "stat.h"
#include "user.h"

int main(void){
  printf(1, "Procesos corriendo %d\n",getprocs());
  exit();
}
