//Introducimos los datos del alumno
void introducirDatosAlumno(ALUMNO *alumno){
        gotoXY(18,4);
        obtenerDato(alumno->nombre);

        gotoXY(18,5);
        obtenerDato(alumno->domicilio);

        gotoXY(18,6);
        obtenerDato(alumno->codPost);

        gotoXY(18,7);
        obtenerDato(alumno->municipio);

        gotoXY(18,8);
        obtenerDato(alumno->codPost);

        gotoXY(18,9);
        obtenerDato(alumno->nif);
}

//Consultamos la información del alumno
void consultaAlumno(){
    system("cls");
    ALUMNO alumno;FILE *pf;int last_nexp, nExp;

    pf=fopen(RUTA_A,"rb+");

    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nError al intentar abrir  el fichero data/alumnos.dat\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return;
    }

    last_nexp=totalRegistro(pf,sizeof(ALUMNO));
    //Pedir nº de expediente.
    pedirAlumno(&nExp,"");
    fseek(pf, (nExp-1) * sizeof(alumno), SEEK_SET);
	fread(&alumno, sizeof(alumno), 1, pf);
    if(comprobar(nExp,last_nexp) && alumno.nExped!=0){
        mostrarAlumno(alumno);
        printf(ANSI_COLOR_GREEN "\n\nFichero cargado correctamente.\n\n" ANSI_COLOR_RESET);
    }else{
        printf(ANSI_COLOR_RED "\n\nNº de expediente incorrecto.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf);
    system("pause");
}

//Modificamos los datos del alumno
void editarAlumno(ALUMNO *alumno){
    int resp,success=1;
    printf(ANSI_COLOR_BLUE "\n¿Qué dato deseas editar?: " ANSI_COLOR_RESET);
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
            printf(ANSI_COLOR_CYAN "\n\n Opción incorrecta..." ANSI_COLOR_RESET);
            success=0;
            break;
    }
    fflush(stdin);
    if(success) printf(ANSI_COLOR_GREEN "\n\n Modificación exitosa!\n\n" ANSI_COLOR_RESET);
}

void menuAlumno(){
    system("cls");
    char * menu_alummnos[30]={"1. ALTA.","2. MODIFICACIÓN.","3. CONSULTA.","4. ELIMINAR","5. VOLVER."};
    void (*function[])()={altaAlumno,modificarAlumno,consultaAlumno,eliminarAlumno};
    int opc=menu(menu_alummnos,5);
    while(opc!=5){
        (* function[opc-1])();
        opc=menu(menu_alummnos,5);
    }
    printf(ANSI_COLOR_MAGENTA "\n\nPresionar una tecla para continuar..." ANSI_COLOR_RESET);
}

void altaAlumno(){
    system("cls");
    ALUMNO alumno;FILE *pf;char resp;
    //Abrimos o creamos el fichero de bits de en alumnos.dat
    pf=fopen(RUTA_A,"ab+");

    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nError no se encuentra la carpeta data.\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
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
    printf(ANSI_COLOR_BLUE "\n\n¿Desea guardar el registro? (s/?): " ANSI_COLOR_RESET);
    resp=tolower(_getche());
    if(resp=='s'){
        //Guardamos la estructura de ALUMNO con los datos introducidos en el fichero
        fseek(pf, 0, SEEK_SET);
        fwrite(&alumno,sizeof(alumno),1,pf);
        printf(ANSI_COLOR_GREEN "\n\nRegistro guardado con exito!!\n\n" ANSI_COLOR_RESET);
    }else{
        printf(ANSI_COLOR_CYAN "\n\nRegistro no guardado.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf);
    system("pause");
}

//Modificar los datos del alumno
void modificarAlumno(){
    system("cls");
    ALUMNO alumno;FILE *pf;int last_nexp, nExp;
    char resp;

    pf=fopen(RUTA_A,"rb+");

    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nError al intentar abrir el fichero data/alumnos.dat\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return;
    }

    last_nexp=totalRegistro(pf,sizeof(ALUMNO));
    //Pedir nº de expediente.
    pedirAlumno(&nExp,"");
    fseek(pf, (nExp-1) * sizeof(alumno), SEEK_SET);
	fread(&alumno, sizeof(alumno), 1, pf);
    if(comprobar(nExp,last_nexp) && alumno.nExped!=0){
        do{
            mostrarAlumno(alumno);
            editarAlumno(&alumno);
            printf(ANSI_COLOR_BLUE "\n\n¿Deseas seguir? (s/?): " ANSI_COLOR_RESET);
                resp=tolower(_getche());
        }while (resp=='s');
        fseek(pf,(alumno.nExped-1)*sizeof(alumno),SEEK_SET);
        fwrite(&alumno,sizeof(alumno),1,pf);
    }else{
        printf(ANSI_COLOR_RED "\n\n Nº de expediente incorrecto.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf);
    printf("\n\n");
    system("pause");
}

//Mostrar datos del alummno
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

void pedirAlumno(int* alumno,char* extra){
    system("cls");
    printf("\nNº de Exped. %s: ",extra);
    scanf("%d",alumno);
    fflush(stdin);
 }

 void eliminarAlumno(){
    system("cls");
    FILE *pf;
    ALUMNO alumno;
    int nExp,lastNexp;
    char resp;

    pf=fopen(RUTA_A,"rb+");

    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nError al intentar abrir el fichero data/alumnos.dat\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return;
    }

    lastNexp=totalRegistro(pf,sizeof(ALUMNO));

    pedirAlumno(&nExp,"");
    fseek(pf,sizeof(ALUMNO)*(nExp-1),SEEK_SET);
    fread(&alumno,sizeof(ALUMNO),1,pf);
    if(comprobar(nExp,lastNexp) && alumno.nExped!=0){
        mostrarAlumno(alumno);
        printf(ANSI_COLOR_BLUE "\n\n¿Deseas seguir? (s/?): " ANSI_COLOR_RESET);
        resp=_getche();
        if(resp=='s'){
            alumno.nExped=0;
            fseek(pf,sizeof(ALUMNO)*(nExp-1),SEEK_SET);
            fwrite(&alumno,sizeof(ALUMNO),1,pf);
            if(eliminarMatriculaAlumno(nExp))
                printf(ANSI_COLOR_GREEN "\n\n Alumno eliminado correctamente.\n\n" ANSI_COLOR_RESET);
        }
    }else{
        printf(ANSI_COLOR_RED "\n\n Nº de expediente incorrecto.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf);
    printf("\n\n");
    system("pause");
 }

int eliminarMatriculaAlumno(int nExp){
    FILE*pf_matricula;
    MATRICULA matricula;
    pf_matricula=fopen(RUTA_M,"rb+");
    fseek(pf_matricula,0,SEEK_SET);
    if(pf_matricula==NULL){
        printf(ANSI_COLOR_RED "\n\nError al intentar abrir el fichero data/matricula.dat\n\n" ANSI_COLOR_RESET);
        fclose(pf_matricula);
        return 0;
    }
    while(fread(&matricula,sizeof(MATRICULA),1,pf_matricula)==1){
        if(matricula.nExp==nExp){
            matricula.nMatricula=0;
            fseek(pf_matricula,sizeof(MATRICULA)*(matricula.nMatricula-1),SEEK_SET);
            fwrite(&matricula,sizeof(MATRICULA),1,pf_matricula);
            break;
        }
    }
    fclose(pf_matricula);
    return 1;
}