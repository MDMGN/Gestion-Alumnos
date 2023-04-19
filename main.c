#include "./includes/header.h"
#include "./includes/helpers.c"
#include "./includes/alumnos.c"

int main(){
    void (* function[])()={menuAlumnos};
    char *menuPrincipal[30]={"1. ALUMNOS.","2. CURSOS.","3. MATRICULACIONES.","4. GESTIÓN DE CURSOS.","5. SALIR."};
    int opc=menu(menuPrincipal,5);
    //Mostramos el menú hasta que el usuario elija la opción salir (5)
    while(opc!=5){
        (* function[opc-1])();
        opc=menu(menuPrincipal,5);
    }
    printf("\nSaliendo...");
    _getch();
    return 0;
}