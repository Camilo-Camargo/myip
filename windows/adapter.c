#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
 
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#include "../myip.h"

void MYIP_init(){
  MYIP_LOG("Initializing windows adapter.");

  WSADATA d;

  if(WSAStartup(MAKEWORD(2,2), &d)){
    MYIP_ERROR("Failed to initialize winsock2.");
    return;
  }
  MYIP_LOG("Initialize successfully.");
}


void MYIP_print_address(){
  DWORD rv, size;
  PIP_ADAPTER_ADDRESSES adapter_addresses;

  rv = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, NULL, &size);

  if(rv != ERROR_BUFFER_OVERFLOW) goto error;

  adapter_addresses = (PIP_ADAPTER_ADDRESSES) malloc(size);
  rv = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, NULL, adapter_addresses, &size);

  if(rv != ERROR_SUCCESS) goto error;

  PIP_ADAPTER_ADDRESSES adapter = adapter_addresses;
  for(adapter = adapter_addresses; adapter != NULL; adapter = adapter->Next){
    PIP_ADAPTER_UNICAST_ADDRESS address;
    for(address = adapter->FirstUnicastAddress; address != NULL; address = address->Next){
      char address_name_buffer [BUFSIZ];
      getnameinfo(
        address->Address.lpSockaddr,
        address->Address.iSockaddrLength,
        address_name_buffer,
        sizeof(address_name_buffer),
        0,
        0,
        NI_NUMERICHOST
      );

      fprintf(stdout,"%S: \n\t%s\n", adapter->FriendlyName,address_name_buffer);
    }
  }

  goto cleanup;

error:
  MYIP_ERROR("GetAdaptersAddresses failed with error code %d", rv);

cleanup:
  free(adapter_addresses);
}

void MYIP_close(){
  MYIP_LOG("closed windows adapter.");
}

