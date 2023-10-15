#include "../myip.h"

#include <errno.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

void MYIP_init() { MYIP_LOG("initialize unix adapter."); }

void MYIP_print_address() {
  struct ifaddrs *addresses;

  if (getifaddrs(&addresses)) {
    MYIP_ERROR("getifaddrs: %s", strerror(errno));
    return;
  }

  struct ifaddrs *address;
  for (address = addresses; address != NULL; address = address->ifa_next) {

    int family = address->ifa_addr->sa_family;

    if (family == AF_INET || family == AF_INET6) {
      char address_name_buffer[BUFSIZ];
      getnameinfo(address->ifa_addr,
                  family == AF_INET ? sizeof(struct sockaddr_in)
                                    : sizeof(struct sockaddr_in6),
                  address_name_buffer, sizeof(address_name_buffer), 0, 0,
                  NI_NUMERICHOST);
      fprintf(stdout, "%s\n\t%s\n", address->ifa_name, address_name_buffer);
    }
  }
}

void MYIP_close() { MYIP_LOG("closed unix adapter."); }
