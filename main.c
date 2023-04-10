#include "./includes/header.h"
#include "./includes/functions.c"

int main(){
    void (* function[])()={pedirAlumnos};
    int opc=menu();
    //Mostramos el menú hasta que el usuario elija la opción salir (5)
    while(opc!=5){
        (* function[opc-1])();
        opc=menu();
    }
    printf("\nSaliendo...");
    _getch();
    return 0;
}