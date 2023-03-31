void printMenu(){
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

int menu(){
    int opc;
    do{
        system("cls");
        printMenu();
        scanf("%d",&opc);
    }while(opc > 1 || opc > 5);

    return opc;
}