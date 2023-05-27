//Establece la posición del cursor x, y en la consola.
void gotoXY(int x,int y){
    COORD pos;
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(h,pos);
}

// Retorna un entero del 1 al 5 de la opción introducida por el usuario.
int menu(char* menu[30],int limit,char * titulo){
    int opc;
    do{
        system("cls");
        mostrarMenu(menu,limit,titulo); 
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
    if ( fecha.mes >= 1 && fecha.mes <= 12 && fecha.anio >= 1900){
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

void recuadro(int xs, int ys, int xi, int yi) {
    for (int i = xs; i <= xi; i++) {
        gotoXY(i,ys);printf("\u2500"); // Borde horizontal
        gotoXY(i,yi);printf("\u2500"); // Borde horizontal
    }

    for (int i = ys; i <= yi; i++) {
        gotoXY(xs,i);printf("\u2502\n"); // Borde vertical
        gotoXY(xi,i);printf("\u2502\n"); // Borde vertical
    }
    gotoXY(xs,ys);printf("\u2554"); // Esquina superior izquierda
    gotoXY(xi,yi);printf("\u255D\n"); // Esquina inferior derecha
    gotoXY(xi,ys);printf("\u2557"); // Esquina superior derecha
    gotoXY(xs,yi);printf("\u255A\n"); // Esquina inferior izquierda
}

void mostrarMenu(char* menu[], int limit, char* titulo) {
    int i, menuWidth = 20;

    // Obtener la longitud máxima de cadena para ajustar el ancho del menú
    for (i = 0; i < limit; i++) {
        int len = strlen(menu[i]);
        if (len > menuWidth) {
            menuWidth = len;
        }
    }

    // Calcular el ancho del título
    int tituloWidth = strlen(titulo);

    // Calcular el ancho total del menú
    int totalWidth = menuWidth + 4; // Ancho del contenido del menú + 2 caracteres de espacio en cada lado

    // Calcular las coordenadas del recuadro del menú
    int xs = 0;
    int ys = 1; // Incrementamos en 1 para dejar espacio para el título
    int xi = totalWidth + 1; // Aumentamos en 1 para alinear correctamente la esquina inferior derecha
    int yi = limit + limit; // Aumentamos en limit para el espacio adicional entre el contenido y el borde inferior

    // Imprimir el menú con bordes
    recuadro(xs, ys, xi, yi);
    gotoXY(xs,ys);
    // Imprimir el título del menú centrado
    int espacioTitulo = (totalWidth - tituloWidth) / 2; // Espacio en blanco necesario para centrar el título
    printf("\n\u2502%*s%s%*s\n\n", espacioTitulo, "", titulo, espacioTitulo, "");

    for (i = 0; i < limit; i++) {
        printf("\u2502 %-*s \n", menuWidth, menu[i]);
    }

    printf("\n");
}
   


