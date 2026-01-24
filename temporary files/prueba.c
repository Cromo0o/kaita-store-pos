#include <stdio.h>


int main(){

    char cliente[100];

    printf("Digite el nombre del cliente:\n>>");
    fgets(cliente, sizeof(cliente), stdin);

    printf("Cliente: %s", cliente);

    return 0;
}