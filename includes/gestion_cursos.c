void gestionCursos(){
    system("cls");
    char * menu_gestion_cursos[30]={"1. COMENZAR CURSO.","2. FINALIZAR CURSO.","3. BOLETIN ALUMNO.","4. VOLVER."};
    void (*function[])()={comenzarCurso,finalizarCurso,boletinAlumno};
    int opc=menu(menu_gestion_cursos,4,"MENU GESTIÓN DE CURSOS");
    while(opc!=4){
        (* function[opc-1])();
        opc=menu(menu_gestion_cursos,4,"MENU GESTIÓN DE CURSOS");
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
    fseek(pf_curso,sizeof(CURSO)*(nCurso -1),SEEK_SET);
    fread(&curso,sizeof(CURSO),1,pf_curso);
    if(comprobar(nCurso,last_nCurso) && curso.nCurso!=0){
        if(!curso.iniciado){
            curso.iniciado=1;
            curso.finalizado=0;
            fseek(pf_curso,sizeof(CURSO)*(nCurso -1),SEEK_SET);
            fwrite(&curso,sizeof(CURSO),1,pf_curso);
            if(informeAlumnosPorCurso(nCurso,pf_matricula,pf_alumn)) 
                printf(ANSI_COLOR_GREEN "\n\nInforme generado en: informes/matriculados.txt\n\n" ANSI_COLOR_RESET);
        }else{
            printf(ANSI_COLOR_RED "\n\nEl curso ya ha sido iniciado.\n\n" ANSI_COLOR_RESET);
        }
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
    FILE*pf=fopen(RUTA_INFO_AL,"w");

    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nNo se cuentra la carpeta informes.\n\n");
        printf("\n\nInforme de resumenes no generado.\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return 0;
    }

    fprintf(pf,"\n+----------------------------------------+\n");
    fprintf(pf,"| %-17s | %-18s |\n","CURSO","ALUMNO");
    fprintf(pf,"+----------------------------------------+\n");
    while (fread(&matricula,sizeof(MATRICULA),1,pf_matriculas)==1)
    {
        if(matricula.nCurso==nCurso && matricula.nMatricula!=0){
            fseek(pf_alumnos,sizeof(ALUMNO)*(matricula.nExp-1),SEEK_SET);
            fread(&alumno,sizeof(ALUMNO),1,pf_alumnos);
            fprintf(pf,"| %-17d | %-18s |\n",nCurso,alumno.nombre);
            fprintf(pf,"+----------------------------------------+\n");
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
    fseek(pf_curso,sizeof(CURSO)*(nCurso-1),SEEK_SET);
    fread(&curso,sizeof(CURSO),1,pf_curso);
    if(comprobar(nCurso,last_nCurso) && curso.nCurso!=0){
        if(curso.finalizado){
            printf(ANSI_COLOR_RED "\n\n El curso ya ha sido finalizado.\n\n" ANSI_COLOR_RESET);
        }else{
            mostrarCurso(curso);
            system("pause");
            curso.finalizado=1;
            fseek(pf_curso,sizeof(CURSO)*(nCurso-1),SEEK_SET);
            fwrite(&curso,sizeof(CURSO),1,pf_curso);
            gestionarNotas(nCurso,pf_matricula,pf_alumn);

            if(informeResumen(pf_matricula,pf_curso)) 
                printf(ANSI_COLOR_GREEN "\n\nInforme generado en: informes/resumenes.txt\n\n" ANSI_COLOR_RESET);
        }
    }else{
        printf(ANSI_COLOR_RED "\n\n Nº de curso incorrecto.\n\n" ANSI_COLOR_RESET);
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
        if(matricula.nCurso==nCurso && matricula.nMatricula!=0){
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
    MATRICULA matricula;CURSO curso;RESUMEN resumen;
    FILE*pf=fopen(RUTA_INFO_RE,"w");
    FILE*pf_resumenes=fopen(RUTA_RE,"ab+");
    if(pf_resumenes==NULL || pf==NULL){
        printf(ANSI_COLOR_RED "\n\nNo se cuentra la carpeta data o informes.\n\n");
        printf("\n\nInforme de resúmenes no generado.\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        fclose(pf_resumenes);
        system("pause");
        return 0;
    }

    int nAlumnos,encontrados,total=0;
    float avg_nota;
    
    fprintf(pf,"\n+----------------------------------------------------------------------------------------+\n");
    fprintf(pf,"| %23s %38s %23s |\n","","LISTADO RESUMEN DE CURSOS FINALIZADOS","");
    fprintf(pf,"+----------------------------------------------------------------------------------------+\n");
    fprintf(pf,"| %5s | %-20s | %10s | %12s | %-13s | %-10s |\n","CURSO","DESCRIPCION","FECHA INICIO","FECHA FIN","Nº ALUMNOS","NOTA MEDIA");
    fprintf(pf,"+----------------------------------------------------------------------------------------+\n");
    fseek(pf_cursos,0,SEEK_SET);
    while (fread(&curso,sizeof(CURSO),1,pf_cursos)==1)
    {
        if(curso.finalizado && curso.nCurso!=0){
            avg_nota=nAlumnos=encontrados=0;
            fseek(pf_matriculas,0,SEEK_SET);
            while(fread(&matricula,sizeof(MATRICULA),1,pf_matriculas)==1 && !encontrados){
                if(matricula.nCurso==curso.nCurso && matricula.nMatricula!=0){
                    nAlumnos++;
                    avg_nota+=matricula.nota;
                    if(curso.plazasMax==nAlumnos) encontrados=1;
                }
            }
            avg_nota/=nAlumnos;
            fprintf(pf,"| %5d | %-20s | %3d/%3d/%4d | %3d/%3d/%4d | %12d | %10.2f |\n",curso.nCurso,curso.description,curso.fInicio.dia,curso.fInicio.mes,curso.fInicio.anio,curso.fFin.dia,curso.fFin.mes,curso.fFin.anio,nAlumnos,avg_nota);
            fprintf(pf,"+----------------------------------------------------------------------------------------+\n");
            //Asignamos el valor a la estructura resumen.
            resumen.nCurso=curso.nCurso;
            strcpy(resumen.description,curso.description);
            resumen.fInicio=curso.fInicio;
            resumen.ffin=curso.fFin;
            resumen.n_alumnos=nAlumnos;
            resumen.media_curso=avg_nota;
            //Guardamos la estructura resumen con los datos al fichero resumenes.
            fwrite(&resumen,sizeof(RESUMEN),1,pf_resumenes);
            total+=nAlumnos;
        }
    }
    fprintf(pf,"| %42s  | %12s | %12d | %10s |\n","","Totales",total,"");
    fprintf(pf,"+----------------------------------------------------------------------------------------+\n");
    fclose(pf);
    fclose(pf_resumenes);
    return 1;
}

void boletinAlumno(){
    system("cls");
    FILE *pf_alumnos,*pf_cursos,*pf_matriculas;
    ALUMNO alumno;
    int last_nAlumn, nExp;

    pf_alumnos=fopen(RUTA_A,"rb");
    pf_cursos=fopen(RUTA_C,"rb");
    pf_matriculas=fopen(RUTA_M,"rb");

    if(pf_alumnos==NULL){
        printf(ANSI_COLOR_RED "\n\nError: No se encontro el fichero de data/alumnos.data\n\n" ANSI_COLOR_RESET);
        fclose(pf_alumnos);
        system("pause");
        return;
    }else if(pf_cursos==NULL){
        printf(ANSI_COLOR_RED "\n\nError: No se encontro el fichero de data/cursos.data\n\n" ANSI_COLOR_RESET);
        fclose(pf_cursos);
        system("pause");
        return;
    }else if(pf_matriculas==NULL){
        printf(ANSI_COLOR_RED "\n\nError: No se encontro el fichero de data/matricula.data\n\n" ANSI_COLOR_RESET);
        fclose(pf_matriculas);
        system("pause");
        return;
    }

    last_nAlumn=totalRegistro(pf_alumnos,sizeof(ALUMNO));
    pedirAlumno(&nExp,"");
    fseek(pf_alumnos,sizeof(ALUMNO)*(nExp-1),SEEK_SET);
    fread(&alumno,sizeof(ALUMNO),1,pf_alumnos);
    if(comprobar(nExp,last_nAlumn) && alumno.nExped!=0){
        mostrarAlumno(alumno);
        system("pause");
        if(informeBoletinAlumno(nExp,pf_matriculas,pf_cursos,alumno))
            printf(ANSI_COLOR_GREEN "\n\nInforme generado en informes/boletin.txt\n\n" ANSI_COLOR_RESET);
    }else{
        printf(ANSI_COLOR_RED "\n\nNº de alumno incorrecto.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf_alumnos);
    fclose(pf_cursos);
    fclose(pf_matriculas);
    system("pause");
}

int informeBoletinAlumno(int nExp,FILE* pf_matriculas,FILE* pf_cursos,ALUMNO alumno){
    MATRICULA matricula;CURSO curso;FECHA fecha;
    FILE *pf=fopen(RUTA_INFO_BO,"w");
    float nota_media;int count;
    nota_media=count=0;
    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nNo se cuentra la carpeta de informes.\n\n");
        printf("\n\nInforme de boletin no generado.\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return 0;
    }
    
    fecha=obtenerFechaActual();
    fprintf(pf,"\n+--------------------------------------------+\n");
    fprintf(pf,"| Nª Expediente: %2d  Nombre: %11s %3s |\n",alumno.nExped,alumno.nombre,"");
    fprintf(pf,"| Fecha: %2d/%2d/%2d %-24s |\n",fecha.dia,fecha.mes,fecha.anio,"");
    fprintf(pf,"+--------------------------------------------+\n");
    fprintf(pf,"| Nº CURSO |     Denominación     |   Nota   |\n");
    fprintf(pf,"+--------------------------------------------+\n");

    fseek(pf_matriculas,0,SEEK_SET);
    while(fread(&matricula,sizeof(MATRICULA),1,pf_matriculas)==1){
        if(matricula.nExp==nExp && matricula.nMatricula!=0){
            fseek(pf_cursos,sizeof(CURSO)*(matricula.nCurso-1),SEEK_SET);
            fread(&curso,sizeof(CURSO),1,pf_cursos);
            fprintf(pf,"| %8d | %20s | %8.2f |\n",curso.nCurso,curso.description,matricula.nota);
            fprintf(pf,"+--------------------------------------------+\n");
            nota_media+=matricula.nota;
            count++;
        }
    }
    nota_media/=count;
    fprintf(pf,"| Nota media: %4.2f %-26s|\n",nota_media,"");
    fprintf(pf,"+--------------------------------------------+\n");
    fclose(pf);
    return 1; 
}