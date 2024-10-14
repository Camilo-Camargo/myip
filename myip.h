#ifndef __MYIP__
#define __MYIP__
#define MYIP_VERSION "0.0.1"

#include <stdio.h>

#define MYIP_DEBUG 0
#define MYIP_LOG(format, ...) if(MYIP_DEBUG) fprintf(stdout, "[LOG] " format "\n", ##__VA_ARGS__)
#define MYIP_WARN(format, ...) fprintf(stdout, "[WARN] " format "\n", ##__VA_ARGS__)
#define MYIP_ERROR(format, ...) fprintf(stderr, "[ERROR] " format "\n", ##__VA_ARGS__)

struct _MYIP_Generic_Item;
typedef struct _MYIP_Generic_Item MYIP_Item;

void MYIP_init();
void MYIP_print_address();
void MYIP_close();

#endif
