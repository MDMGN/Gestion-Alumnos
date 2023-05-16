//Introducimos los datos del alumno
void introducirDatosAlumno(ALUMNO *alumno){
        gotoXY(18,4);
        fgets(alumno->nombre,20,stdin);
        fflush(stdin);
        strtok(alumno->nombre,"\n");
        gotoXY(18,5);
        fgets(alumno->domicilio,20,stdin);
        fflush(stdin);
        strtok(alumno->domicilio,"\n");
        gotoXY(18,6);
        fgets(alumno->codPost,5,stdin);
        fflush(stdin);
        strtok(alumno->codPost,"\n");
        gotoXY(18,7);
        fgets(alumno->municipio,15,stdin);
        fflush(stdin);
        strtok(alumno->municipio,"\n");
        gotoXY(18,8);
        fgets(alumno->nif,10,stdin);
        fflush(stdin);
        strtok(alumno->nif,"\n");
}

//Consultamos la información del alumno
void consultaAlumno(){
    system("cls");
    ALUMNO alumno;FILE *pf;int last_nexp, nExp;
    pf=fopen(RUTA_A,"rb+");
    //Comprobamos si el fichero existe
    if(pf==NULL){
        printf("\nError: El fichero no existe.");
        fclose(pf);
        printf("\nVolviendo...");
        _getch();
        return;
    }
    last_nexp=totalRegistro(pf,sizeof(ALUMNO));
    //Pedir nº de expediente.
    printf("\nNúmero de exp. : ");
    scanf("%d",&nExp);
    rewind(stdin);
    if(comprobarExp(nExp,last_nexp)){
        fseek(pf, (nExp-1) * sizeof(alumno), SEEK_SET);
	    fread(&alumno, sizeof(alumno), 1, pf);
        mostrarAlumno(alumno);
        printf("\n\nFichero cargado correctamente.");
    }else{
        printf("\n\nNº de expediente incorrecto.");
    }
    fclose(pf);
    _getch();
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

void menuAlumno(){
    system("cls");
    char * menu_alummnos[30]={"1. ALTA.","2. MODIFICACIÓN.","3. CONSULTA.","4. VOLVER."};
    void (*function[])()={altaAlumno,modificarAlumno,consultaAlumno};
    int opc=menu(menu_alummnos,4);
    while(opc!=4){
        (* function[opc-1])();
        opc=menu(menu_alummnos,4);
    }
    printf("\nVolviendo...");
}

void altaAlumno(){
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
    alumno.nExped=totalRegistro(pf,sizeof(ALUMNO))+1;
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
    introducirDatosAlumno(&alumno);
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
    last_nexp=totalRegistro(pf,sizeof(ALUMNO));
    //Pedir nº de expediente.
    printf("\nNúmero de exp. : ");
    scanf("%d",&nExp);
    rewind(stdin);
    if(comprobarExp(nExp,last_nexp)){
        fseek(pf, (nExp-1) * sizeof(alumno), SEEK_SET);
	    fread(&alumno, sizeof(alumno), 1, pf);
        do{
            mostrarAlumno(alumno);
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

void editarCurso(CURSO *curso){
    int resp,success=1;
    printf("\n¿Qué dato deseas editar?: ");
    scanf("%d",&resp);
    rewind(stdin);
    switch(resp){
        case 1:
            printf("\n Descripción: ");
            fgets(curso->description,21,stdin);
            break;
        case 2:
            printf("\n Domicilio: ");
            scanf("%d",&curso->plazasMax);
            break;
        case 3:
            printf("\n Código postal: ");
            fgets(curso->codPost,5,stdin);
            break;
        case 4:
            printf("\n Municipio: ");
            fgets(curso->municipio,16,stdin);
            break;
        case 5:
            printf("\n N.I.F: ");
            fgets(curso->nif,11,stdin);
            break;
        default:
            printf("\n Opción incorrecta...");
            success=0;
            break;
    }
    rewind(stdin);
    if(success) printf("\n\n Modificación exitosa!\n");
}

void mostrarAlumno(ALUMNO alumno){
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
}