void matriculaciones(){
    system("cls");
    FILE *pf_alumn,*pf_curso,*pf_matricula;

    pf_alumn=fopen(RUTA_A,"rb");
    pf_curso=fopen(RUTA_C,"rb");

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
    }
    
    pf_matricula=fopen(RUTA_M,"ab+");

    if(pf_matricula==NULL){
        printf(ANSI_COLOR_RED "\n\nError: No se encontro el fichero de matricula.\n\n" ANSI_COLOR_RESET);
        fclose(pf_matricula);
        system("pause");
        return;
    }
    gestionarMatricula(pf_alumn,pf_curso,pf_matricula);
}

void gestionarMatricula(FILE *pf_alumn,FILE *pf_curso,FILE *pf_matricula){
    CURSO curso;
    int last_nCurso,last_nAlumn, nCurso,nAlumno;

    
    last_nCurso=totalRegistro(pf_curso,sizeof(CURSO));
    last_nAlumn=totalRegistro(pf_alumn,sizeof(ALUMNO));
    pedirCurso(&nCurso,"(0 para salir)");
    while(nCurso!=0){
        system("cls");
        fseek(pf_curso,(nCurso-1)*sizeof(CURSO),SEEK_SET);
        fread(&curso,sizeof(CURSO),1,pf_curso);
        if(!comprobar(nCurso,last_nCurso) && curso.nCurso==0){
           printf(ANSI_COLOR_RED "\n\nNº curso incorrecto.\n\n" ANSI_COLOR_RESET);
        }else{
            if(!comprobarPlazas(nCurso,curso.plazasMax,pf_matricula)){
                    printf(ANSI_COLOR_RED "\n\nNo quedan plazas para este curso.\n\n" ANSI_COLOR_RESET);
            }else{
                pedirAlumno(&nAlumno,"(0 para salir)");
                while(nAlumno!=0 && comprobarPlazas(nCurso,curso.plazasMax,pf_matricula)){
                    gestionarAlumno(pf_matricula,pf_alumn,nAlumno,nCurso,last_nAlumn);
                    pedirAlumno(&nAlumno, "(0 para salir)");
                }
            }
        }
        system("pause");
        pedirCurso(&nCurso,"(0 para salir)");
    }

    fclose(pf_alumn);
    fclose(pf_curso);
    fclose(pf_matricula);
}

int comprobarPlazas(int ncurso,int maxPlazas,FILE *pf_matricula){
    MATRICULA matricula;
    int matriculados=0;
    fseek(pf_matricula,0,SEEK_SET);
    
    while(fread(&matricula,sizeof(MATRICULA),1,pf_matricula)==1){
        if(matricula.nCurso==ncurso){
            matriculados++;
        }
    }
    return maxPlazas - matriculados > 0;
 }

 int alumnoMatriculadoCurso(int nCurso,int nAlumno,FILE *pf_matricula){
    MATRICULA matricula;
    fseek(pf_matricula,0,SEEK_SET);

    while(fread(&matricula,sizeof(MATRICULA),1,pf_matricula)==1){
        if(matricula.nCurso==nCurso && matricula.nExp==nAlumno ) return 1;
    }
    return  0;
 }

 void gestionarAlumno(FILE *pf_matricula,FILE *pf_alumn,int nAlumno,int nCurso,int last_nAlumn){
    ALUMNO alumno;MATRICULA matricula;
    char resp;int nMatricula;
    if(!comprobar(nAlumno,last_nAlumn)){
            printf(ANSI_COLOR_RED "\n\nNº alumno incorrecto.\n\n" ANSI_COLOR_RESET);
    }else if(alumnoMatriculadoCurso(nCurso,nAlumno,pf_matricula)){
            printf(ANSI_COLOR_RED "\n\nEl alumno ya está matriculado en el curso.\n\n" ANSI_COLOR_RESET);
    }else{
        fseek(pf_alumn,sizeof(ALUMNO)*(nAlumno-1),SEEK_SET);
        fread(&alumno,sizeof(ALUMNO),1,pf_alumn);
        mostrarAlumno(alumno);
        printf(ANSI_COLOR_BLUE "\n\n¿Deseas matricularlo al curso? (s/?): " ANSI_COLOR_RESET);
        resp=tolower(_getche());
        if(resp=='s'){
            nMatricula=totalRegistro(pf_matricula,sizeof(MATRICULA))+1;
            escribirMatricula(&matricula,nMatricula,nCurso,nAlumno);
            fwrite(&matricula,sizeof(MATRICULA),1,pf_matricula);
            printf(ANSI_COLOR_GREEN "\n\nAlumno matriculado correctamente.\n\n" ANSI_COLOR_RESET);
        }else{
            printf(ANSI_COLOR_CYAN "\n\nAlumno no matriculado.\n\n" ANSI_COLOR_RESET);
        }
    }
    system("pause");
 }

 void escribirMatricula(MATRICULA*matricula,int nMatricula,int nCurso,int nExp){
    matricula->nMatricula=nMatricula;
    matricula->nCurso=nCurso;
    matricula->nExp=nExp;
    printf("\nNota: ");
    scanf("%f",&matricula->nota);
 }

 void mostrarMatriculas(){
    MATRICULA matricula;
    FILE* pf=fopen(RUTA_M,"rb");
    fseek(pf,0,SEEK_SET);
    while (fread(&matricula,sizeof(MATRICULA),1,pf)==1)
    {
        system("cls");
        printf("+----------------------------------+\n");
        printf("|         FICHERO DE ALUMNOS       |\n");
        printf("|----------------------------------|\n");
        printf("| Nº Matricula  : %7d|\n", matricula.nMatricula);
        printf("| Nª Curso      : %7d|\n", matricula.nCurso);
        printf("| Nª Exped.     : %7d|\n", matricula.nExp);
        printf("| Nota          : %-7.2f|\n", matricula.nota);
        printf("+----------------------------------+\n");
        system("pause");
    }
    fclose(pf);
 }