#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_ipv4 {
    char class;
    char *strBinaryAddress[4];
    int iDecimalAddress[4];
    int iSubNetMask[4];
} t_ipv4;

int CheckArguments(int pa_argc);
void ProcessAddress(char *pa_argv[], t_ipv4 *pa_sIpv4);

int main(int argc, char *argv[]) {
    
    t_ipv4 ipv4;
    
    if(CheckArguments(argc)) {
        ProcessAddress(argv, &ipv4);
    }
    
    return EXIT_SUCCESS;
}

int CheckArguments(int pa_argc) {
    
    if(pa_argc != 3) {
        printf("\r\n\tERROR : Wrong syntax.\r\n\r\n");
        exit(EXIT_FAILURE);
    }
    else {
        return 1;
    }
}
void ProcessAddress(char *pa_argv[], t_ipv4 *pa_ipv4) {
    
    void *ptr_Address;
    char *ptr_Token;
    char cOption;
    const char separators[] = ".";
    int iByteCounter = 0;
    
    //Détermine l'emplacement de stockage de la valeur en fonction du format de l'iP
    sscanf(pa_argv[1], "-%c", &cOption);    
    switch(cOption) {
        case 'b':
            ptr_Address = &pa_ipv4->strBinaryAddress;
            break;
        case 'd':
            ptr_Address = &pa_ipv4->iDecimalAddress;
            break;
        default :
            printf("\r\n\tERROR : Invalid argument '%c'.\r\n", cOption);
            exit(EXIT_FAILURE);
    }
    
    //Récupère la chaîne passée en argument de main
    ptr_Token = strtok(pa_argv[1], separators);
}
