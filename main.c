#include "./includes/header.h"
#include "./includes/functions.c"

int main(){
    void (* function[])()={mostrarFicheroAlumno};
    int opc=menu();
    //Mostramos el menú hasta que no le a la opción salir (5)
    while(opc!=5){
        (* function[opc-1])();
    }
    printf("\nSaliendo...");
    _getch();
    return 0;
}