
//Establece la posición del cursor x, y en la consola.
void gotoXY(int x,int y){
    COORD pos;
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(h,pos);
}

//Imprime la pantalla del menú principal del programa

void mostrarMenu(){
int i, menuWidth = 20;
    char menu[5][30] = {"1. Alumnos.", "2. CURSOS.", "3. MATRICULACIONES.", "4. GESTIÓN DE CURSOS.", "5. Salir."};
    
    // Obtener la longitud máxima de cadena para ajustar el ancho del menú
    for (i = 0; i < 5; i++) {
        int len = strlen(menu[i]);
        if (len > menuWidth) {
            menuWidth = len;
        }
    }
    
    // Imprimir el menú con bordes
    printf("+");
    for(i = 0; i < menuWidth + 3; i++) {
        printf("-");
    }
    printf("+\n");
    
    printf("|%*sMENU PRINCIPAL%*s|\n", (menuWidth - 2) / 3, "", (menuWidth - 2) / 4, "");
    
    printf("+");
    for(i = 0; i < menuWidth + 3; i++) {
        printf("-");
    }
    printf("+\n");
    
    for (i = 0; i < 5; i++) {
        printf("| %-*s  |\n", menuWidth, menu[i]);
    }
    
    printf("+");
    for(i = 0; i < menuWidth + 3; i++) {
        printf("-");
    }
    printf("+\n");
}

// Retorna un entero del 1 al 5 de la opción introducida por el usuario.
int menu(){
    int opc;
    do{
        system("cls");
        mostrarMenu(); 
        printf("\nIntroduzca una opción: ");
        scanf("%d",&opc); // Obtenemos la opción introducida por el usuario.
        rewind(stdin); //  Limpiar lo almacenado en el buffer.
    }while(opc < 1 || opc > 5); // Validar que la opción sea entre 1 y 5
    return opc;
}

void introducirDatosAlumnos(){
    ALUMNO alumno;
        gotoXY(18,3);
        scanf("%d",&alumno.nExped);
        rewind(stdin);
        gotoXY(18,4);
        fgets(alumno.nombre,20,stdin);
        gotoXY(18,5);
        gets(alumno.domicilio);
        gotoXY(18,6);
        gets(alumno.codPost);
        gotoXY(18,7);
        gets(alumno.municipio);
        gotoXY(18,8);
        gets(alumno.nif);
        // limpiar la posición de la etiqueta del número de expediente
}

void pedirAlumnos(){
    system("cls");
    // Mostrar el menú
    printf("+----------------------------------+\n");
    printf("|         FICHERO DE ALUMNOS       |\n");
    printf("|----------------------------------|\n");
    printf("| Nº Expediente : %-17s|\n", "");
    printf("| Nombre        : %-17s|\n", "");
    printf("| Domicilio     : %-17s|\n", "");
    printf("| Cod. Postal   : %-17s|\n", "");
    printf("| Municipio     : %-17s|\n", "");
    printf("| N.I.F.        : %-17s|\n", "");
    printf("+----------------------------------+\n");
    introducirDatosAlumnos();
    _getch();
    // Mostrar la línea de mensajes
    system("cls");
    printf("Línea de mensajes\n");
    _getch();
}