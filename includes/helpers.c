//Establece la posición del cursor x, y en la consola.
void gotoXY(int x,int y){
    COORD pos;
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(h,pos);
}

//Imprime la pantalla del menú principal del programa

void mostrarMenu(char*menu[30],int limit){
int i, menuWidth = 20;    
    // Obtener la longitud máxima de cadena para ajustar el ancho del menú
    for (i = 0; i < limit; i++) {
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
    
    for (i = 0; i < limit; i++) {
        printf("| %-*s  |\n", menuWidth, menu[i]);
    }
    
    printf("+");
    for(i = 0; i < menuWidth + 3; i++) {
        printf("-");
    }
    printf("+\n");
}

// Retorna un entero del 1 al 5 de la opción introducida por el usuario.
int menu(char* menu[30],int limit){
    int opc;
    do{
        system("cls");
        mostrarMenu(menu,limit); 
        printf("\nIntroduzca una opción: ",limit);
        scanf("%d",&opc); // Obtenemos la opción introducida por el usuario.
        rewind(stdin); //  Limpiar lo almacenado en el buffer.
    }while(opc < 1 || opc > limit); // Validar que la opción sea entre 1 y 5
    return opc;
}

//Obtenemos el último número de expediente
int totalRegistro(FILE* pf,long sizeReg){
    int  tam;
    fseek(pf, 0, SEEK_END);    
    tam=ftell(pf);                      
    fseek(pf, 0, SEEK_SET);   
    tam -= ftell(pf);
    return (tam/sizeReg);
}

void insertarFecha(char date[],FECHA* fecha){
    char *token;
    token=strtok(date,"/");
    sscanf(token,"%i",fecha->dia);
    token=strtok(NULL,"/");
    sscanf(token,"%i",fecha->mes);
    token=strtok(NULL,"/");
    sscanf(token,"%i",fecha->anio);
}

