#include <stdio.h>

#include "sgx_eid.h"     /* sgx_enclave_id_t */
#include "sgx_trts.h"
#include "sgx_urts.h"

#include "enclave_u.h"

# define TOKEN_FILENAME   "enclave.token"
# define ENCLAVE_FILENAME "trusted_enclave_signed.so"

sgx_enclave_id_t global_eid = 0;

int initialize_enclave(void)
{
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    
    ret = sgx_create_enclave(ENCLAVE_FILENAME, SGX_DEBUG_FLAG, NULL, NULL, &global_eid, NULL);
    if (ret != SGX_SUCCESS) {
        printf("%d",ret);
        return -1;
    }

    return 0;
}
int SGX_CDECL main(int argc, char *argv[]) {

    initialize_enclave();
    sgx_status_t t = init(global_eid);
    printf("\n\n stat%x",t);
    return 0;
}

//Ocalls 

void ocall_print_bytes(char* name,unsigned char* b,size_t len) {
  printf("%s \n",name);
  for(int i =0;i<len;i++) {
    printf("%02x",b[i]);
  }
  printf("\n");
}

void ocall_print( char* str ) {
  printf("Print :: %s\n",str);
}

void ocall_print_key_value(char* key, int value) {
  printf("%s :: %d\n",key,value);
}