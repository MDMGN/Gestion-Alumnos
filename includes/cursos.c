void menuCurso(){
    system("cls");
    char * menu_alummnos[30]={"1. ALTA.","2. MODIFICACIÓN.","3. CONSULTA.","4. VOLVER."};
    void (*function[])()={altaCurso,modificarCurso,consultaCurso};
    int opc=menu(menu_alummnos,4);
    while(opc!=4){
        (* function[opc-1])();
        opc=menu(menu_alummnos,4);
    }
    printf("\nVolviendo...");
}

void altaCurso(){
    system("cls");
    CURSO curso;FILE *pf;char resp;
    //Abrimos o creamos el fichero de bits de en alumnos.dat
    pf=fopen(RUTA_C,"ab+");
    if(pf==NULL){
        printf("\nError al crear o abrir el fichero.");
        fclose(pf);
        _getch();
        return;
    }
    curso.nCurso=totalRegistro(pf,sizeof(CURSO))+1;
    // Mostrar el menú
    printf("+------------------------------------------------------+\n");
    printf("|                FICHERO DE CURSO                      |\n");
    printf("|------------------------------------------------------|\n");
    printf("| Nº Curso      : %-37d|\n", curso.nCurso);
    printf("| Descripción   : %-15s Plazas max: %-9s|\n", "","");
    printf("| Desde         : %-15s Hasta     : %-9s|\n", "","");
    printf("| Iniciado      : %-15s Finalizado: %-9s|\n", "","");
    printf("+------------------------------------------------------+\n");
    introducirDatosCurso(&curso);
    //Pedimos conformidad para guardar el registro
    printf("\nDesea guardar el registro? (s/?): ");
    resp=tolower(_getche());
    if(resp=='s'){
        //Guardamos la estructura de CURSO con los datos introducidos
        fseek(pf, 0, SEEK_SET);
        fwrite(&curso,sizeof(curso),1,pf);
        printf("\nRegistro guardado con exito!!");
    }else{
        printf("\nVolviendo...");
    }
    fclose(pf);
    _getch();
}

//Introducimos los datos del curso
void introducirDatosCurso(CURSO *curso){
    char date[11];
        gotoXY(18,4);
        fgets(curso->description,20,stdin);
        fflush(stdin);
        strtok(curso->description,"\n");
        gotoXY(46,4);
        scanf("%d",curso->plazasMax);
        fflush(stdin);
        gotoXY(18,5);
        fgets(date,11,stdin);
        fflush(stdin);
        insertarFecha(date,&curso->fInicio);
        gotoXY(46,5);
        fgets(date,11,stdin);
        fflush(stdin);
        insertarFecha(date,&curso->fFin);
        gotoXY(18,6);
        scanf("%d",curso->iniciado);
        fflush(stdin);
        gotoXY(46,6);
        scanf("%d",curso->finalizado);
        fflush(stdin);
}

void consultaCurso(){
    system("cls");
    CURSO curso;FILE *pf;int last_ncurs, nCurs;
    pf=fopen(RUTA_A,"rb");
    //Comprobamos si el fichero existe
    if(pf==NULL){
        printf("\nError: No se encuentra la carpeta data.");
        fclose(pf);
        printf("\nVolviendo...");
        _getch();
        return;
    }
    last_ncurs=totalRegistro(pf,sizeof(CURSO));
    //Pedir nº de expediente.
    printf("\nNúmero de curso: ");
    scanf("%d",&nCurs);
    rewind(stdin);
    if(comprobarExp(nCurs,last_ncurs)){
	    fread(&curso, sizeof(curso), nCurs, pf);
        mostrarCurso(curso);
        printf("\n\nFichero cargado correctamente.");
    }else{
        printf("\n\nNº de expediente incorrecto.");
    }
    fclose(pf);
    _getch();
}

void modificarCurso(){
    printf("modificarCurso");
    _getch();
}

void mostrarCurso(CURSO curso){
    system("cls");
    char *resp[]={"Sí","No"};
    // Mostrar los datos de curso
    printf("+---------------------------------------------------------+\n");
    printf("|                FICHERO DE CURSO                         |\n");
    printf("|---------------------------------------------------------|\n");
    printf("| Nº Curso      : %d                                      |\n", curso.nCurso);
    printf("| Descripción   : %s                   Plazas max: %d     |\n", curso.description,curso.plazasMax);
    printf("| Desde         : %d/%d/%d             Hasta     :%d/%d/%d|\n", curso.fInicio.dia,curso.fInicio.mes,curso.fInicio.anio,curso.fFin.dia,curso.fFin.mes,curso.fFin.anio);
    printf("| Iniciado      : %s                   Finalizado: %s     |\n", resp[0],resp[1]);
    printf("+---------------------------------------------------------+\n");
}