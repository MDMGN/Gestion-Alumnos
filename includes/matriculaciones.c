void matriculaciones(){
    system("cls");
    FILE *pf_alumn,*pf_curso,*pf_matricula;

    pf_alumn=fopen(RUTA_A,"rb");
    pf_curso=fopen(RUTA_C,"rb");

    if(pf_alumn==NULL){
        printf("\n\nError: No se encontro el fichero de alumnos.");
        fclose(pf_alumn);
        return;
    }else if(pf_curso==NULL){
        printf("\n\nError: No se encontro el fichero de cursos.");
        fclose(pf_curso);
        return;
    }
    
    fclose(pf_alumn);
    fclose(pf_curso);

    pf_alumn=fopen(RUTA_A,"rb");
    pf_curso=fopen(RUTA_C,"rb");
    pf_matricula=fopen(RUTA_M,"rb+");

    if(pf_matricula==NULL){
        printf("\n\nError: No se encontro el fichero de matricula.");
        fclose(pf_matricula);
        return;
    }
    pedirDatosMatricula(pf_alumn,pf_curso,pf_matricula);

}

void pedirDatosMatricula(FILE *pf_alumn,FILE *pf_curso,FILE *pf_matricula){
    CURSO curso;ALUMNO alumno;MATRICULA matricula;
    int last_nCurso,last_nAlumn, nCurso,nAlumno;

    last_nAlumn=totalRegistro(pf_alumn,sizeof(ALUMNO));
    last_nCurso=totalRegistro(pf_curso,sizeof(CURSO));

    printf("\nNº de curso: ");
    scanf("%d",&nCurso);
    fflsuh(stdin);
    while(nCurso!=0){
        while(!comprobar(nCurso,last_nCurso)){
           printf("\nNº curso incorrecto.");
           _getch();
           system("cls");
           printf("\nNº de curso: ");
            scanf("%d",&nCurso);
            fflsuh(stdin);
        }
        fseek(pf_curso,(nCurso-1)*sizeof(CURSO),SEEK_SET);
        fread(&curso,sizeof(CURSO),1,pf_curso);
        /* while(comprobarPlazas(CURSO curso,int totalC) && comprobar(nAlumno,last_nAlumn)){

        } */
    }
}

/* 
int comprobarPlazas(int ncursos,int maxPlazas){
    return maxPlazas-ncursos > 0;
} */