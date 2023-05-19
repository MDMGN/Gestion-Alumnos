void matriculaciones(){
    system("cls");
    FILE *pf_alumn,*pf_curso,*pf_matricula;

    pf_alumn=fopen(RUTA_A,"rb");
    pf_curso=fopen(RUTA_C,"rb");

    if(pf_alumn==NULL){
        printf("\n\nError: No se encontro el fichero de alumnos.");
        fclose(pf_alumn);
        _getch();
        return;
    }else if(pf_curso==NULL){
        printf("\n\nError: No se encontro el fichero de cursos.");
        fclose(pf_curso);
        _getch();
        return;
    }
    
    fclose(pf_alumn);
    fclose(pf_curso);

    pf_alumn=fopen(RUTA_A,"rb");
    pf_curso=fopen(RUTA_C,"rb");
    pf_matricula=fopen(RUTA_M,"ab+");

    if(pf_matricula==NULL){
        printf("\n\nError: No se encontro el fichero de matricula.");
        fclose(pf_matricula);
        _getch();
        return;
    }
    gestionarMatricula(pf_alumn,pf_curso,pf_matricula);

}

void gestionarMatricula(FILE *pf_alumn,FILE *pf_curso,FILE *pf_matricula){
    CURSO curso;
    int last_nCurso,last_nAlumn, nCurso,nAlumno;

    
    last_nCurso=totalRegistro(pf_curso,sizeof(CURSO));
    last_nAlumn=totalRegistro(pf_alumn,sizeof(ALUMNO));
    pedirCurso(&nCurso);
    while(nCurso!=0){
        system("cls");
        if(!comprobar(nCurso,last_nCurso)){
           printf("\nNº curso incorrecto.\nPresionar una tecla para continuar...");
           _getch();
        }else{
            fseek(pf_curso,(nCurso-1)*sizeof(CURSO),SEEK_SET);
            fread(&curso,sizeof(CURSO),1,pf_curso);

            if(!comprobarPlazas(nCurso,curso.plazasMax,pf_curso)){
                    printf("\nNo quedan plazas para este curso.\nPresionar una tecla para continuar...");
                    _getch();
            }else{
                pedirAlumno(&nAlumno);
                while(nAlumno!=0){
                    gestionarAlumno(pf_matricula,pf_alumn,nAlumno,nCurso,last_nAlumn);
                    pedirAlumno(&nAlumno);
                }
            }
        }
        pedirCurso(&nCurso);
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
    debugearInt(matricula.nExp);
    return maxPlazas - matriculados > 0;
 }

 void pedirCurso(int* curso){
    system("cls");
    printf("\nNº de curso: ");
    scanf("%d",curso);
    fflush(stdin);
 }

 void gestionarAlumno(FILE *pf_matricula,FILE *pf_alumn,int nAlumno,int nCurso,int last_nAlumn){
    ALUMNO alumno;MATRICULA matricula;
    char resp;int nMatricula;
    if(!comprobar(nAlumno,last_nAlumn)){
            printf("\nNº alumno incorrecto.\n\nPresionar una tecla para continuar...");
            _getch();
    }else{
        fseek(pf_alumn,sizeof(ALUMNO)*(nAlumno-1),SEEK_SET);
        fread(&alumno,sizeof(ALUMNO),1,pf_alumn);
        mostrarAlumno(alumno);
        printf("\n\n¿Deseas matricularlo al curso? (s/?): ");
        resp=tolower(_getche());
        if(resp=='s'){
            nMatricula=totalRegistro(pf_matricula,sizeof(MATRICULA))+1;
            escribirMatricula(&matricula,nMatricula,nCurso,nAlumno);
            fread(&matricula,sizeof(MATRICULA),1,pf_alumn);
            printf("\nAlumno matriculado correctamente.\n\nPresionar una tecla para continuar...");
        }else{
            printf("\nAlumno no matriculado.\n\nPresionar una tecla para continuar...");
        }
         _getch();
    }
 }

  void pedirAlumno(int* alumno){
    system("cls");
    printf("\nNº de alumno: ");
    scanf("%d",alumno);
    fflush(stdin);
 }
 void escribirMatricula(MATRICULA*matricula,int nMatricula,int nCurso,int nExp){
    matricula->nMatricula=nMatricula;
    matricula->nCurso=nCurso;
    matricula->nExp=nExp;
    printf("\nNota: ");
    scanf("%f",&matricula->nota);
 }