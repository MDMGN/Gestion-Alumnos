#include "./includes/header.h"
#include "./includes/helpers.c"
#include "./includes/alumno.c"
#include "./includes/curso.c"
#include "./includes/matriculaciones.c"
#include "./includes/gestion_cursos.c"

int main(){
    system("chcp 65001");  // Establece la página de códigos para admitir caracteres Unicode en la consola de Windows
    system("mode con: cols=80 lines=25"); // Establece el tamaño de la consola a 80 columnas por 25 líneas
    //system("color 7"); // Configura el color de fondo y de texto en la consola (comentado)
    system("cls"); 
    void (* function[])()={menuAlumno,menuCurso,matriculaciones,gestionCursos};
    char *menuPrincipal[30]={"1. ALUMNOS.","2. CURSOS.","3. MATRICULACIONES.","4. GESTIÓN DE CURSOS.","5. SALIR."};
    int opc=menu(menuPrincipal,5,"MENU PRINCIPAL");
    
    //Mostramos el menú hasta que el usuario elija la opción salir (5)
    while(opc!=5){
        (* function[opc-1])();
        opc=menu(menuPrincipal,5,"MENU PRINCIPAL");
    }
    system("pause");
    return 0;
}