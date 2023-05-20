void gestionCursos(){
    system("cls");
    char * menu_gestion_cursos[30]={"1. COMENZAR CURSO.","2. FINALIZAR CURSO.","3. BOLETIN ALUMNO.","4. VOLVER."};
    void (*function[])()={comenzarCurso,finalizarCurso,boletinAlumno};
    int opc=menu(menu_gestion_cursos,4);
    while(opc!=4){
        (* function[opc-1])();
        opc=menu(menu_gestion_cursos,4);
    }
    printf(ANSI_COLOR_MAGENTA "\n\nPresionar una tecla para volver..." ANSI_COLOR_RESET);
}

void comenzarCurso(){
    system("cls");
    FILE *pf_alumn,*pf_curso,*pf_matricula;
    CURSO curso;
    int last_nCurso,last_nAlumn, nCurso;

    pf_alumn=fopen(RUTA_A,"rb");
    pf_curso=fopen(RUTA_C,"rb+");
    pf_matricula=fopen(RUTA_M,"rb");

    if(pf_alumn==NULL){
        printf(ANSI_COLOR_RED "\n\nError: No se encontro el fichero de alumnos.\n\n" ANSI_COLOR_RESET);
        fclose(pf_alumn);
        system("pause");
        return;
    }else if(pf_curso==NULL){
        printf(ANSI_COLOR_RED "\n\nError: No se encontro el fichero de cursos.\n\n" ANSI_COLOR_RESET);
        fclose(pf_curso);
        system("pause");
        return;
    }else if(pf_matricula==NULL){
        printf(ANSI_COLOR_RED "\n\nError: No se encontro el fichero de matricula.\n\n" ANSI_COLOR_RESET);
        fclose(pf_matricula);
        system("pause");
        return;
    }
    last_nCurso=totalRegistro(pf_curso,sizeof(CURSO));
    //last_nAlumn=totalRegistro(pf_alumn,sizeof(ALUMNO));

    pedirCurso(&nCurso,"");

    if(comprobar(nCurso,last_nCurso)){
        fseek(pf_curso,sizeof(CURSO)*(nCurso -1),SEEK_SET);
        fread(&curso,sizeof(CURSO),1,pf_curso);
        if(curso.iniciado==0){
            curso.iniciado=1;
            fwrite(&curso,sizeof(CURSO),1,pf_curso);
        }
        
        if(informeAlumnosPorCurso(nCurso,pf_matricula,pf_alumn)) 
            printf(ANSI_COLOR_GREEN "\n\nInforme generado en: informes/matriculados.txt\n\n" ANSI_COLOR_RESET);
    }else{
        printf(ANSI_COLOR_RED "\n\nNª de cursos no valido.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf_matricula);
    fclose(pf_curso);
    fclose(pf_alumn);
    system("pause");
}

int informeAlumnosPorCurso(int nCurso,FILE*pf_matriculas,FILE*pf_alumnos){
    system("cls");
    MATRICULA matricula;ALUMNO alumno;
    fseek(pf_matriculas,0,SEEK_SET);
    FILE*pf=fopen(RUTA_LISTA_AL,"w");

    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nNo se cuentra la carpeta informes.\n\n");
        printf("\n\nInforme de resumenes no generado.\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return 0;
    }

    fprintf(pf,"\n+----------------------------------------+\n");
    fprintf(pf,"|%-20s %-20s|\n","CURSO","ALUMNO");
    fprintf(pf,"\n+----------------------------------------+\n");
    while (fread(&matricula,sizeof(MATRICULA),1,pf_matriculas)==1)
    {
        if(matricula.nCurso==nCurso){
            fseek(pf_alumnos,sizeof(ALUMNO)*(matricula.nExp-1),SEEK_SET);
            fread(&alumno,sizeof(ALUMNO),1,pf_alumnos);
            fprintf(pf,"| %-20d %-20s|\n",nCurso,alumno.nombre);
            fprintf(pf,"\n+----------------------------------------+\n");
        }
    }
    fclose(pf);
    return 1;
}

void finalizarCurso(){
    system("cls");
    CURSO curso;
    FILE *pf_alumn,*pf_curso,*pf_matricula;
    int last_nCurso,nCurso;

    pf_alumn=fopen(RUTA_A,"rb");
    pf_curso=fopen(RUTA_C,"rb+");
    pf_matricula=fopen(RUTA_M,"rb+");

    if(pf_alumn==NULL){
        printf(ANSI_COLOR_RED "\n\nError: No se encontro el fichero de alumnos.\n\n" ANSI_COLOR_RESET);
        fclose(pf_alumn);
        system("pause");
        return;
    }else if(pf_curso==NULL){
        printf(ANSI_COLOR_RED "\n\nError: No se encontro el fichero de cursos.\n\n" ANSI_COLOR_RESET);
        fclose(pf_curso);
        system("pause");
        return;
    }else if(pf_matricula==NULL){
        printf(ANSI_COLOR_RED "\n\nError: No se encontro el fichero de matricula.\n\n" ANSI_COLOR_RESET);
        fclose(pf_matricula);
        system("pause");
        return;
    }
    
    last_nCurso=totalRegistro(pf_curso,sizeof(CURSO));

    pedirCurso(&nCurso,"");
    if(comprobar(nCurso,last_nCurso)){
        fseek(pf_curso,sizeof(CURSO)*(nCurso-1),SEEK_SET);
        fread(&curso,sizeof(CURSO),1,pf_curso);
        mostrarCurso(curso);
        system("pause");
        curso.finalizado=1;
        fwrite(&curso,sizeof(CURSO),1,pf_curso);
        gestionarNotas(nCurso,pf_matricula,pf_alumn);

        if(informeResumen(pf_matricula,pf_curso)) 
            printf(ANSI_COLOR_GREEN "\n\nInforme generado en: informes/resumenes.txt\n\n" ANSI_COLOR_RESET);
        
    }else{
        printf(ANSI_COLOR_RED "\n\n Nº de curso no valido.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf_alumn);
    fclose(pf_curso);
    fclose(pf_matricula);
    system("pause");
}

void gestionarNotas(int nCurso,FILE*pf_matriculas,FILE*pf_alumnos){
    MATRICULA matricula;ALUMNO alumno;
    float nota;int i=1;
    fseek(pf_matriculas,0,SEEK_SET);
    while (fread(&matricula,sizeof(MATRICULA),1,pf_matriculas)==1)
    {
            i++;
        if(matricula.nCurso==nCurso){
            fseek(pf_alumnos,sizeof(ALUMNO)*(matricula.nExp-1),SEEK_SET);
            fread(&alumno,sizeof(ALUMNO),1,pf_alumnos);
            mostrarAlumno(alumno);
            pedirNota(&nota);
            matricula.nota=nota;
            fseek(pf_matriculas,sizeof(MATRICULA)*(matricula.nMatricula-1),SEEK_SET);
            fwrite(&matricula,sizeof(MATRICULA),1,pf_matriculas);
            printf(ANSI_COLOR_GREEN "\n\nLa nota se guardo con exito!\n\n" ANSI_COLOR_RESET);
            system("pause");
            fseek(pf_matriculas,sizeof(MATRICULA)*(i-1),SEEK_SET);
        }
    }
}

void pedirNota(float* nota){
    printf("\n\nNota: ");
    scanf("%f",nota);
    fflush(stdin);
    if(*nota < 0.0f || *nota > 10.0f){
        printf(ANSI_COLOR_RED "\n\nLa nota debe estar entre 0 y 10.\n\n" ANSI_COLOR_RESET);
        system("pause");
        pedirNota(nota);
    }
    return;
}

int informeResumen(FILE*pf_matriculas,FILE*pf_cursos){
    system("cls");
    MATRICULA matricula;CURSO curso;
    FILE*pf=fopen(RUTA_LISTA_RE,"w");

    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nNo se cuentra la carpeta informes.\n\n");
        printf("\n\nInforme de resumenes no generado.\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return 0;
    }

    int nAlumnos=0;
    float avg_nota;

    fprintf(pf,"\n+--------------------------------------------------------------------+\n");
    fprintf(pf,"| %-40s |\n","LISTADO RESUMEN DE CURSOS FINALIZADOS");
    fprintf(pf,"+--------------------------------------------------------------------+\n");
    fprintf(pf,"| %12s | %13s | %14s | %12s | %12s | %12s |\n","CURSO","DESCRIPCION","FECHA INICIO","FECHA FIN","Nº ALUMNOS","NOTA MEDIA");
    fprintf(pf,"+--------------------------------------------------------------------+\n");
    fseek(pf_cursos,0,SEEK_SET);
    while (fread(&curso,sizeof(CURSO),1,pf_cursos)==1)
    {
        if(curso.finalizado){
            avg_nota=0;
            fseek(pf_matriculas,0,SEEK_SET);
            while(fread(&matricula,sizeof(MATRICULA),1,pf_matriculas)==1){
                if(matricula.nCurso==curso.nCurso){
                    nAlumnos++;
                    avg_nota+=matricula.nota;
                }
            }
            avg_nota/=nAlumnos;
            fprintf(pf,"| %12d | %13s | %2d/%2d/%4d | %2d/%2d/%4d | %12d |%12.2f |\n",curso.nCurso,curso.description,curso.fInicio.dia,curso.fInicio.mes,curso.fInicio.anio,curso.fFin.dia,curso.fFin.mes,curso.fFin.anio,nAlumnos,avg_nota);
            fprintf(pf,"+--------------------------------------------------------------------+\n");
        }
    }
    fclose(pf);
    return 1;
}

void boletinAlumno(){

}