#include "myip.h"

#include <stdio.h>

int main(){
  MYIP_init();
  MYIP_print_address();
  MYIP_close();
}
