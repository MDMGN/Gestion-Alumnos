void menuCurso(){
    system("cls");
    char * menu_alummnos[30]={"1. ALTA.","2. MODIFICACIÓN.","3. CONSULTA.","4. VOLVER."};
    void (*function[])()={altaCurso};
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
    printf("+----------------------------------------------------+\n");
    printf("|                FICHERO DE CURSO                    |\n");
    printf("|----------------------------------------------------|\n");
    printf("| Nº Curso      : %-35d|\n", curso.nCurso);
    printf("| Descripción   : %-15s Plazas max: %-7s|\n", "","");
    printf("| Desde         : %-15s Hasta     : %-7s|\n", "","");
    printf("| Iniciado      : %-15s Finalizado: %-7s|\n", "","");
    printf("+----------------------------------------------------+\n");
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
        gotoXY(18,4);
        fgets(curso->description,20,stdin);
        fflush(stdin);
        strtok(curso->description,"\n");
        gotoXY(46,4);
        scanf("%d",&curso->plazasMax);
        fflush(stdin);
        gotoXY(18,5);
        scanf("%s/%s/%s",curso->fInicio.dia,curso->fInicio.mes,curso->fInicio.anio);
        fflush(stdin);
        gotoXY(46,5);
        scanf("%s/%s/%s",curso->fFin.dia,curso->fFin.mes,curso->fFin.anio);
        fflush(stdin);
        gotoXY(18,6);
        scanf("%d",curso->iniciado);
        fflush(stdin);
        gotoXY(46,6);
        scanf("%d",curso->finalizado);
        fflush(stdin);
}