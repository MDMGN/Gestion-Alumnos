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
    sscanf(token,"%d",&fecha->dia);
    token=strtok(NULL,"/");
    sscanf(token,"%d",&fecha->mes);
    token=strtok(NULL,"/");
    sscanf(token,"%d",&fecha->anio);
}

//Comprobar si el nº expediente/curso/profesor está dentro de los límites.
int comprobar(int n,int lastN){
   return !(n < 1 || n > lastN);
}

void debugearInt(int n){
    printf("\n|%d|\n",n);
    _getch();
}

FECHA obtenerFechaActual(){
    FECHA fecha;
    time_t t;
    t= time(NULL);
    struct tm*t_fecha;
    t_fecha=localtime(&t);
    fecha.dia=t_fecha->tm_mday;
    fecha.mes=t_fecha->tm_mon+1;
    fecha.anio=t_fecha->tm_year+1900;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
    return fecha;
}

int validarFecha(FECHA fecha){
    if ( fecha.mes >= 1 && fecha.mes <= 12 ){
        switch ( fecha.mes ){
            case  1 :
            case  3 :
            case  5 :
            case  7 :
            case  8 :
            case 10 :
            case 12 : 
                        return ( fecha.dia >= 1 && fecha.dia <= 31 );
            case  4 :
            case  6 :
            case  9 :
            case 11 :
                        return ( fecha.dia >= 1 && fecha.dia <= 30 );
            case  2 : 
                        if( fecha.anio % 4 == 0 && fecha.anio % 100 != 0 || fecha.anio % 400 == 0 )
                                return ( fecha.dia >= 1 && fecha.dia <= 29 );
                        else
                                return ( fecha.dia >= 1 && fecha.dia <= 28 );
        }
    }
    else
        return 0;
}

char *ltrim(char *s){
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s){
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s){
    return rtrim(ltrim(s)); 
}

void obtenerDato(char* dato, int tam){
    fgets(dato,tam,stdin);
    strtok(dato,"\n");
    strcpy(dato,trim(dato));
    fflush(stdin);
}
/*
void recuadro(){
    int i;
    for(int i=xs; i <= xi; i++){
        gotoXY(i, ys):printf("%c",196);
        gotoXY(i, yi):printf("%c",196);
    }

    for(int i=ys; i <= yi; i++){
        gotoXY(xs, i):printf("%c",179);
        gotoXY(xi,i):printf("%c",179);
    }
}
*/
