void menuCurso(){
    system("cls");
    char * menu_alummnos[30]={"1. ALTA.","2. MODIFICACIÓN.","3. CONSULTA.","4. ELIMINAR","5. VOLVER."};
    void (*function[])()={altaCurso,modificarCurso,consultaCurso,eliminarCurso};
    int opc=menu(menu_alummnos,5,"MENU CURSOS");
    while(opc!=5){
        (* function[opc-1])();
        opc=menu(menu_alummnos,5,"MENU CURSOS");
    }
    printf(ANSI_COLOR_MAGENTA "\n\nPresionar una tecla para volver..." ANSI_COLOR_RESET);
}

void altaCurso(){
    system("cls");
    CURSO curso;FILE *pf;char resp;
    //Abrimos o creamos el fichero de bits de en alumnos.dat
    pf=fopen(RUTA_C,"ab+");
    if(pf==NULL){
        printf(ANSI_COLOR_RED "\nError: No se encuentra la carpeta data.\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("cls");
        return;
    }
    curso.nCurso=totalRegistro(pf,sizeof(CURSO))+1;
    // Mostrar el menú
    printf("+--------------------------------------------------------+\n");
    printf("|                FICHERO DE CURSO                        |\n");
    printf("|--------------------------------------------------------|\n");
    printf("| Nº Curso      : %-39d|\n", curso.nCurso);
    printf("| Descripción   : %-15s Plazas max: %-11s|\n", "","");
    printf("| Desde         : %-15s Hasta     : %-11s|\n", "","");
    printf("+--------------------------------------------------------+\n");
    introducirDatosCurso(&curso);
    curso.iniciado=0;
    curso.finalizado=0;
    //Pedimos conformidad para guardar el registro
    printf(ANSI_COLOR_BLUE "\n¿Desea guardar el registro? (s/?): " ANSI_COLOR_RESET);
    resp=tolower(_getche());
    if(resp=='s'){
        //Guardamos la estructura de CURSO con los datos introducidos
        fseek(pf, 0, SEEK_SET);
        fwrite(&curso,sizeof(curso),1,pf);
        printf(ANSI_COLOR_GREEN "\n\nRegistro guardado con exito!!\n\n" ANSI_COLOR_RESET);
    }else{
        printf(ANSI_COLOR_GREEN "\n\nRegistro no guardado.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf);
    _getch();
}

//Introducimos los datos del curso
void introducirDatosCurso(CURSO *curso){
    char date[11];
        gotoXY(18,4);
        obtenerDato(curso->description,20);

        gotoXY(46,4);
        scanf("%d",&curso->plazasMax);
        fflush(stdin);
        
        gotoXY(18,5);
        obtenerDato(date,11);
        insertarFecha(date,&curso->fInicio);

        while(!validarFecha(curso->fInicio)){
            gotoXY(18,9);
            printf(ANSI_COLOR_RED "\n\nIntroduzca una fecha correcta (dd/mm/aaaa).\n\n" ANSI_COLOR_RESET);
            gotoXY(18,5);
            obtenerDato(date,11);
            insertarFecha(date,&curso->fInicio);
        }
        gotoXY(0,11);
        printf("                                                                                     ");

        gotoXY(46,5);
        obtenerDato(date,11);
        insertarFecha(date,&curso->fFin);

        while(!validarFecha(curso->fFin)){
            gotoXY(18,9);
            printf(ANSI_COLOR_RED "\n\nIntroduzca una fecha correcta (dd/mm/aaaa).\n\n" ANSI_COLOR_RESET);
            gotoXY(46,5);
            obtenerDato(date,11);
            insertarFecha(date,&curso->fFin);
        }
        gotoXY(0,11);
        printf("                                                                                     ");
}

void consultaCurso(){
    system("cls");
    CURSO curso;FILE *pf;int last_ncurs, nCurs;
    pf=fopen(RUTA_C,"rb");
    //Comprobamos si el fichero existe
    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nError al intentar abrir el fichero data/curso.dat\n\n." ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return;
    }
    last_ncurs=totalRegistro(pf,sizeof(CURSO));
    //Pedir nº de curso.
    pedirCurso(&nCurs,"");
    fseek(pf,(nCurs-1)*sizeof(CURSO),SEEK_SET);
    fread(&curso, sizeof(curso), 1, pf);
    if(comprobar(nCurs,last_ncurs) && curso.nCurso!=0){
        mostrarCurso(curso);
        printf(ANSI_COLOR_GREEN "\n\nFichero cargado correctamente.\n\n" ANSI_COLOR_RESET);
    }else{
        printf(ANSI_COLOR_RED "\n\nNº de curso incorrecto.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf);
    system("pause");
}

void modificarCurso(){
   system("cls");
    CURSO curso;FILE *pf;int last_ncurs, nCurs;
    char resp;
    pf=fopen(RUTA_C,"rb+");
    //Comprobamos si el fichero existe
    if(pf==NULL){
        printf(ANSI_COLOR_RESET "\n\nError al intentar abrir el fichero data/curso.dat\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return;
    }
    last_ncurs=totalRegistro(pf,sizeof(CURSO));
    //Pedir nº de curso.
    pedirCurso(&nCurs,"");
    fseek(pf, (nCurs-1) * sizeof(CURSO), SEEK_SET);
	fread(&curso, sizeof(curso), 1, pf);
    if(comprobar(nCurs,last_ncurs) && curso.nCurso!=0){
        do{
            mostrarCurso(curso);
            editarCurso(&curso);
            printf(ANSI_COLOR_BLUE "\nDeseas seguir? (s/?): " ANSI_COLOR_RESET);
            resp=tolower(_getche());
        }while (resp=='s');
        fseek(pf,(curso.nCurso-1)*sizeof(CURSO),SEEK_SET);
        fwrite(&curso,sizeof(CURSO),1,pf);
    }else{
        printf(ANSI_COLOR_RED "\n\nNº de curso incorrecto." ANSI_COLOR_RESET);
    }
    printf("\n\n");
    fclose(pf);
    system("pause");
}

//Modificamos los datos del curso
void editarCurso(CURSO *curso){
    int resp,success=1;
    char date[11];
    printf(ANSI_COLOR_BLUE "\n¿Qué dato deseas editar?: " ANSI_COLOR_RESET);
    scanf("%d",&resp);
    fflush(stdin);
    switch(resp){
        case 1:
            printf("\n Descripción: ");
            fgets(curso->description,sizeof(curso->description),stdin);
            strtok(curso->description,"\n");
            break;
        case 2:
            printf("\n Plazas max: ");
            scanf("%d",&curso->plazasMax);
            break;
        case 3:
            printf("\n Desde: ");
            fgets(date,11,stdin);
            insertarFecha(date,&curso->fInicio);
            break;
        case 4:
            printf("\n Hasta: ");
            fgets(date,11,stdin);
            insertarFecha(date,&curso->fFin);
            break;
        case 5:
            printf("\n Iniciado: ");
            scanf("%d",&curso->iniciado);
            break;
        case 6:
            printf("\n Finalizado: ");
            scanf("%d",&curso->finalizado);
            break;
        default:
            printf(ANSI_COLOR_CYAN "\n Opción incorrecta..." ANSI_COLOR_RESET);
            success=0;
            break;
    }
    fflush(stdin);
    if(success) printf(ANSI_COLOR_GREEN "\n\n Modificación exitosa!\n\n" ANSI_COLOR_RESET);
}

void pedirCurso(int* curso,char* extra){
    system("cls");
    printf("\nNº de curso %s: ",extra);
    scanf("%d",curso);
    fflush(stdin);
 }

void mostrarCurso(CURSO curso){
    system("cls");
    const char *iniciado= (curso.iniciado) ? "Sí" :  "No";
    const char *finalizado= (curso.finalizado) ? "Sí" :  "No";
    // Mostrar los datos del curso
    printf("+------------------------------------------------------------------+\n");
    printf("|                           FICHERO DE CURSO                       |\n");
    printf("|------------------------------------------------------------------|\n");
    printf("| Nº Curso       : %d                                              |\n", curso.nCurso);
    printf("| Descripción (1): %s                   Plazas max (2): %d         |\n", curso.description,curso.plazasMax);
    printf("| Desde       (3): %d/%d/%d             Hasta      (4): %d/%d/%d   |\n", curso.fInicio.dia,curso.fInicio.mes,curso.fInicio.anio,curso.fFin.dia,curso.fFin.mes,curso.fFin.anio);
    printf("| Iniciado    (5): %s                   Finalizado (6): %s         |\n", iniciado,finalizado);
    printf("+------------------------------------------------------------------+\n");
}

 void eliminarCurso(){
    system("cls");
    FILE *pf;
    CURSO curso;
    int nCurso,lastNCurso;
    char resp;

    pf=fopen(RUTA_C,"rb+");

    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nError al intentar abrir el fichero data/curso.dat\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return;
    }

    lastNCurso=totalRegistro(pf,sizeof(CURSO));

    pedirCurso(&nCurso,"");
    fseek(pf,sizeof(CURSO)*(nCurso-1),SEEK_SET);
    fread(&curso,sizeof(CURSO),1,pf);
    if(comprobar(nCurso,lastNCurso) && curso.nCurso!=0){
        mostrarCurso(curso);
        printf(ANSI_COLOR_BLUE "\n\n¿Deseas seguir? (s/?): " ANSI_COLOR_RESET);
        resp=_getche();
        if(resp=='s'){
            curso.nCurso=0;
            fseek(pf,sizeof(CURSO)*(nCurso-1),SEEK_SET);
            fwrite(&curso,sizeof(CURSO),1,pf);
            if(eliminarMatriculaCurso(nCurso))
                printf(ANSI_COLOR_GREEN "\n\n Curso eliminado correctamente.\n\n" ANSI_COLOR_RESET);
        }
    }else{
        printf(ANSI_COLOR_RED "\n\n Nº de curso incorrecto.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf);
    printf("\n\n");
    system("pause");
 }

 int eliminarMatriculaCurso(int nCurso){
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
        if(matricula.nMatricula==nCurso){
            matricula.nMatricula=0;
            fseek(pf_matricula,sizeof(MATRICULA)*(matricula.nMatricula-1),SEEK_SET);
            fwrite(&matricula,sizeof(MATRICULA),1,pf_matricula);
        }
    }
    fclose(pf_matricula);
    return 1;
}