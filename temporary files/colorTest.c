#include <stdio.h>
#include <windows.h>

int main(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("Texto normal ");
    SetConsoleTextAttribute(hConsole, 10); // Verde
    printf("Texto en verde");
    SetConsoleTextAttribute(hConsole, 7);  // Color por defecto
    printf(" texto normal otra vez\n");
    return 0;
}