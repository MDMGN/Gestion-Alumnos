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
    pf_curso=fopen(RUTA_C,"rb");
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
    last_nAlumn=totalRegistro(pf_alumn,sizeof(ALUMNO));

    pedirCurso(&nCurso,"");

    if(comprobar(nCurso,last_nCurso)){
        fseek(pf_curso,sizeof(CURSO)*(nCurso -1),SEEK_SET);
        fread(&curso,sizeof(CURSO),1,pf_curso);
        if(curso.iniciado==0){
            curso.iniciado=1;
        }
        listarAlumnosPorCurso(nCurso,pf_matricula,pf_alumn);
        printf(ANSI_COLOR_GREEN "\n\nInforme generado en: informes/matriculados.txt\n\n" ANSI_COLOR_RESET);
    }else{
        printf(ANSI_COLOR_RED "\n\nNª de cursos no valido.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf_matricula);
    fclose(pf_curso);
    fclose(pf_alumn);
    system("pause");
}

void listarAlumnosPorCurso(int nCurso,FILE*pf_matriculas,FILE*pf_alumnos){
    MATRICULA matricula;ALUMNO alumno;
    fseek(pf_matriculas,0,SEEK_SET);
    FILE*pf=fopen(RUTA_LISTA_AL,"w");
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
}

void finalizarCurso(){

}

void boletinAlumno(){

}