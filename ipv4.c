#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void StoreAddress(char *pa_argv[], int pa_ipAddress[]);
void SubNetMask(char pa_class, int pa_mask[]);
void NetworkAddress(int pa_ipAddress[], int pa_mask[], int pa_network[]);
void Display(int pa_address[]);
char Class(int pa_ipAddress[1]);

int main(int argc, char *argv[]) {
    
    char cNetworkClass;
    int iBytesBinaryAddress[4][8];
    int iBytesDecimalAddress[4];
    int iSubNetMask[4] = {0};
    int iNetworkAddress[4] = {0};
    
    char cOption;
        
    if(argc != 3) {
        printf("\r\n\tERROR : Wrong syntax.\r\n\r\n");
        exit(EXIT_FAILURE);
    }
    else {        
        StoreAddress(argv, iBytesDecimalAddress);
        

        printf("IPv4 : ");
        for(int i = 0; i < 4; i++) {
            printf("%d", iBytesDecimalAddress[i]);
            if(i < 3) {
                printf(".");
            }
        }
        printf("\r\n");
        
        //Détermine l'emplacement de stockage de la valeur en fonction du format de l'iP
        sscanf(argv[1], "-%c", &cOption);    
        switch(cOption) {
            case 'c' :
                cNetworkClass = Class(iBytesDecimalAddress);
                printf("Network class : %c\r\n", cNetworkClass);
                break;
                
            case 'm' :
                SubNetMask(Class(iBytesDecimalAddress), iSubNetMask);
                
                printf("SubNet mask : ");
                Display(iSubNetMask);                
                
                break;
                
            case 'n' :
                SubNetMask(Class(iBytesDecimalAddress), iSubNetMask);
                NetworkAddress(iBytesDecimalAddress, iSubNetMask, iNetworkAddress);
                
                printf("Network address : ");
                Display(iNetworkAddress);
                
                break;
            
            case 'a' :
                SubNetMask(Class(iBytesDecimalAddress), iSubNetMask);
                NetworkAddress(iBytesDecimalAddress, iSubNetMask, iNetworkAddress);
                cNetworkClass = Class(iBytesDecimalAddress);
                
                printf("SubNet mask : ");
                Display(iSubNetMask);
                printf("Network address : ");
                Display(iNetworkAddress);
                printf("Network class : %c\r\n", cNetworkClass);
                
                break;
                
            default :
                printf("\r\n\tERROR : Invalid argument '%c'.\r\n\r\n", cOption);
            
                exit(EXIT_FAILURE);
        }
    }
        
    return EXIT_SUCCESS;
}

void StoreAddress(char *pa_argv[], int pa_ipAddress[]) {
    
    char *ptr_Token;
    const char separators[] = ".";
    
    //Récupère la chaîne passée en argument de main et la range dans la variable...
    ptr_Token = strtok(pa_argv[2], separators);
    for(int i = 0; i < 4; i++) {
        if(ptr_Token) {
            pa_ipAddress[i] = atoi(ptr_Token);
            ptr_Token = strtok(NULL, separators);
        }
    }
    
    //Vérifie que les valeurs sont conformes...
    for(int i = 0; i < 4; i++) {
        if(pa_ipAddress[i] < 0 || pa_ipAddress[i] > 255) {
            printf("\r\n\tERROR : This IP address can't exist.\r\n\r\n");
            exit(EXIT_FAILURE);
        }
    }
}

void SubNetMask(char pa_class, int pa_mask[]) {
    
    int iNbFullBytes;
    
    switch(pa_class) {
        case 'A' :
            iNbFullBytes = 1;
            break;
        case 'B' :
            iNbFullBytes = 2;
            break;
        case 'C' :
            iNbFullBytes = 3;
            break;
        default :
            break;
    }
    
    for(int i = 0; i < iNbFullBytes; i++) {
        pa_mask[i] += 255;
    }
}

void NetworkAddress(int pa_ipAddress[], int pa_mask[], int pa_network[]) {
    
    for(int i = 0; i < 4; i++) {
        pa_network[i] = (pa_ipAddress[i] & pa_mask[i]);
    }
}

void Display(int pa_address[]) {
    
    for(int i = 0; i < 4; i++) {
        printf("%d", pa_address[i]);
        if(i < 3) {
            printf(".");
        }
    }
    printf("\r\n");
}

char Class(int pa_ipAddress[]) {

    if(pa_ipAddress[0] >= 192) {
        return 'C';
    }
    else if(pa_ipAddress[0] >= 128) {
        return 'B';
    }
    else if(pa_ipAddress[0] >= 1 && pa_ipAddress[0] <= 126) {
        return 'A';
    }
    else {
        printf("\r\n\tERROR : In GenerateClass().\r\n");
    }
}
