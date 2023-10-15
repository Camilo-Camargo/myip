#include "myip.h"

#include <stdio.h>

int main(){
  MYIP_init();
  MYIP_LOG("current version: %s", MYIP_VERSION);
  MYIP_close();
}
