#include "./includes/header.h"
#include "./includes/helpers.c"
#include "./includes/alumno.c"
#include "./includes/curso.c"
#include "./includes/matriculaciones.c"
#include "./includes/gestion_cursos.c"

int main(){
    system("chcp 65001");
    /* 
        system("mode con: cols=80 lines=25");
        system("color ZZ");
     */
    void (* function[])()={menuAlumno,menuCurso,matriculaciones,gestionCursos};
    char *menuPrincipal[30]={"1. ALUMNOS.","2. CURSOS.","3. MATRICULACIONES.","4. GESTIÓN DE CURSOS.","5. SALIR."};
    int opc=menu(menuPrincipal,5);
    //Mostramos el menú hasta que el usuario elija la opción salir (5)
    while(opc!=5){
        (* function[opc-1])();
        opc=menu(menuPrincipal,5);
    }
    system("pause");
    return 0;
}