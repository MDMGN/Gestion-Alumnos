
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

void introducirDatosAlumnos(FILE *pf,ALUMNO alumno){
    //Introducimos los datos del alumno
        gotoXY(18,4);
        gets(alumno.nombre);
        gotoXY(18,5);
        gets(alumno.domicilio);
        gotoXY(18,6);
        gets(alumno.codPost);
        gotoXY(18,7);
        gets(alumno.municipio);
        gotoXY(18,8);
        gets(alumno.nif);
}


void menuAlumnos(){
    system("cls");
    char * menu_alummnos[30]={"1. ALTA.","2. MODIFICACIÓN.","3. CONSULTA.","4. VOLVER."};
    void (*function[])()={alta};
    int opc=menu(menu_alummnos,4);

    while(opc!=4){
        (* function[opc-1])();
        opc=menu(menu_alummnos,4);
    }
    printf("\nVolviendo...");
}

void alta(){
    system("cls");
    ALUMNO alumno;FILE *pf;char resp;
    //Creamos el fichero de bits de en alumnos.dat
    pf=fopen(RUTA_A,"ab+");
    if(pf==NULL){
        printf("\nError al abrir el fichero.");
        fclose(pf);
        _getch();
        return;
    }
    alumno.nExped=getLastExpe(pf)+1;
    // Mostrar el menú
    printf("+----------------------------------+\n");
    printf("|         FICHERO DE ALUMNOS       |\n");
    printf("|----------------------------------|\n");
    printf("| Nº Expediente : %-17d|\n", alumno.nExped);
    printf("| Nombre        : %-17s|\n", "");
    printf("| Domicilio     : %-17s|\n", "");
    printf("| Cod. Postal   : %-17s|\n", "");
    printf("| Municipio     : %-17s|\n", "");
    printf("| N.I.F.        : %-17s|\n", "");
    printf("+----------------------------------+\n");
    introducirDatosAlumnos(pf,alumno);
    //Pedimos conformidad para guardar el registro
    printf("\nDesea guardar el registro? (s/?): ");
    resp=tolower(_getche());
    if(resp=='s'){
        //Guardamos la estructura de ALUMNO con los datos introducidos en el fichero
        fseek(pf, 0, SEEK_SET);
        fwrite(&alumno,sizeof(alumno),1,pf);
        printf("\nFichero creado con exito!!");
    }else{
        printf("\nVolviendo...");
    }
    fclose(pf);
    _getch();
}
//Obtenemos el último número de expediente
int getLastExpe(FILE *file){
    int last_nExped = 0;
    ALUMNO a;

    fseek(file, 0, SEEK_SET);

    while (fread(&a, sizeof(ALUMNO), 1, file) == 1) {
        if (a.nExped > last_nExped) {
            last_nExped = a.nExped;
        }
    }
    return last_nExped;
}