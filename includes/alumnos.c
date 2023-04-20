//Introducimos los datos del alumno
void introducirDatosAlumnos(ALUMNO *alumno){
        gotoXY(18,4);
        fgets(alumno->nombre,21,stdin);
        gotoXY(18,5);
        fgets(alumno->domicilio,21,stdin);
        gotoXY(18,6);
        fgets(alumno->codPost,5,stdin);
        rewind(stdin);
        gotoXY(18,7);
        fgets(alumno->municipio,16,stdin);
        gotoXY(18,8);
        fgets(alumno->nif,11,stdin);
}

//Modificamos los datos del alumno
void editarAlumno(ALUMNO *alumno){
    int resp,success=1;
    printf("\n¿Qué dato deseas editar?: ");
    scanf("%d",&resp);
    rewind(stdin);
    switch(resp){
        case 1:
            printf("\n Nombre: ");
            fgets(alumno->nombre,21,stdin);
            break;
        case 2:
            printf("\n Domicilio: ");
            fgets(alumno->domicilio,21,stdin);
            break;
        case 3:
            printf("\n Código postal: ");
            fgets(alumno->codPost,5,stdin);
            break;
        case 4:
            printf("\n Municipio: ");
            fgets(alumno->municipio,16,stdin);
            break;
        case 5:
            printf("\n N.I.F: ");
            fgets(alumno->nif,11,stdin);
            break;
        default:
            printf("\n Opción incorrecta...");
            success=0;
            break;
    }
    rewind(stdin);
    if(success) printf("\n\n Modificación exitosa!\n");
}

void menuAlumnos(){
    system("cls");
    char * menu_alummnos[30]={"1. ALTA.","2. MODIFICACIÓN.","3. CONSULTA.","4. VOLVER."};
    void (*function[])()={altaAlumnos,modificarAlumno};
    int opc=menu(menu_alummnos,4);
    while(opc!=4){
        (* function[opc-1])();
        opc=menu(menu_alummnos,4);
    }
    printf("\nVolviendo...");
}

void altaAlumnos(){
    system("cls");
    ALUMNO alumno;FILE *pf;char resp;
    //Abrimos o creamos el fichero de bits de en alumnos.dat
    pf=fopen(RUTA_A,"ab+");
    if(pf==NULL){
        printf("\nError al crear o abrir el fichero.");
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
    introducirDatosAlumnos(&alumno);
    //Pedimos conformidad para guardar el registro
    printf("\nDesea guardar el registro? (s/?): ");
    resp=tolower(_getche());
    if(resp=='s'){
        //Guardamos la estructura de ALUMNO con los datos introducidos en el fichero
        fseek(pf, 0, SEEK_SET);
        fwrite(&alumno,sizeof(alumno),1,pf);
        printf("\nRegistro guardado con exito!!");
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
//Modificar los datos del alumno
void modificarAlumno(){
    system("cls");
    ALUMNO alumno;FILE *pf;int last_nexp, nExp;
    char resp;
    pf=fopen(RUTA_A,"rb+");
    //Comprobamos si el fichero existe
    if(pf==NULL){
        printf("\nError: El fichero no existe.");
        fclose(pf);
        printf("\nVolviendo...");
        _getch();
        return;
    }
    last_nexp=getLastExpe(pf);
    //Pedir nº de expediente.
    printf("\nNúmero de exp. : ");
    scanf("%d",&nExp);
    rewind(stdin);
    if(comprobarExp(nExp,last_nexp)){
        fseek(pf, (nExp-1) * sizeof(alumno), SEEK_SET);
	    fread(&alumno, sizeof(alumno), 1, pf);
        do{
            system("cls");
            // Mostrar el menú
            printf("+----------------------------------+\n");
            printf("|         FICHERO DE ALUMNOS       |\n");
            printf("|----------------------------------|\n");
            printf("| Nº Expediente    : %-17d|\n", alumno.nExped);
            printf("| Nombre        (1): %-17s|\n", alumno.nombre);
            printf("| Domicilio     (2): %-17s|\n", alumno.domicilio);
            printf("| Cod. Postal   (3): %-17s|\n", alumno.codPost);
            printf("| Municipio     (4): %-17s|\n", alumno.municipio);
            printf("| N.I.F.        (5): %-17s|\n", alumno.nif);
            printf("+----------------------------------+\n");
            editarAlumno(&alumno);
            printf("\nDeseas seguir? (s/?): ");
            resp=tolower(_getche());
        }while (resp=='s');
        fseek(pf,(alumno.nExped-1)*sizeof(alumno),SEEK_SET);
        fwrite(&alumno,sizeof(alumno),1,pf);
    }else{
        printf("\nError: Nº de expediente no valido.");
    }
    fclose(pf);
    printf("\nVolviendo...");
    _getch();
}

//Comprobar si el nº expediente está dentro de los límites.
int comprobarExp(int nExp,int lastNExp){
   return !(nExp < 0 || nExp > lastNExp);
}