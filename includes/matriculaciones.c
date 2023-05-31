#include "header.h"

void matriculaciones(){
    system("cls");
    FILE *pf_alumn,*pf_curso,*pf_matricula;

    pf_alumn=fopen(RUTA_A,"rb"); // Abrir el archivo de alumnos en modo lectura binaria
    pf_curso=fopen(RUTA_C,"rb"); // Abrir el archivo de cursos en modo lectura binaria

    if(pf_alumn==NULL){
        printf(ANSI_COLOR_RED "\n\nError: No se encontró el fichero de alumnos.\n\n" ANSI_COLOR_RESET);
        fclose(pf_alumn);
        system("pause");
        return;
    }else if(pf_curso==NULL){
        printf(ANSI_COLOR_RED "\n\nError: No se encontró el fichero de cursos.\n\n" ANSI_COLOR_RESET);
        fclose(pf_curso);
        system("pause");
        return;
    }
    pf_matricula=fopen(RUTA_M,"ab+"); // Abrir el archivo de matrículas en modo anexar y lectura/escritura binaria
    if(pf_matricula==NULL){
        printf(ANSI_COLOR_RED "\n\nError: No se encontró el fichero de matrícula.\n\n" ANSI_COLOR_RESET);
        fclose(pf_matricula);
        system("pause");
        return;
    }
    gestionarMatricula(pf_alumn,pf_curso,pf_matricula); // Llamar a la función de gestión de matrículas pasando los archivos abiertos

    fclose(pf_alumn); // Cerrar el archivo de alumnos
    fclose(pf_curso); // Cerrar el archivo de cursos
    fclose(pf_matricula); // Cerrar el archivo de matrículas
}


void gestionarMatricula(FILE *pf_alumn, FILE *pf_curso, FILE *pf_matricula){
    CURSO curso;
    int last_nCurso, last_nAlumn, nCurso, nAlumno;
    system("cls");
    
    last_nCurso = totalRegistro(pf_curso, sizeof(CURSO)); // Obtener el número total de cursos en el archivo
    last_nAlumn = totalRegistro(pf_alumn, sizeof(ALUMNO)); // Obtener el número total de alumnos en el archivo
    pedirCurso(&nCurso, "(0 para salir)"); // Solicitar el número de curso al usuario
    while(nCurso != 0){
        fseek(pf_curso, (nCurso-1) * sizeof(CURSO), SEEK_SET); // Mover el puntero de archivo al curso seleccionado
        fread(&curso, sizeof(CURSO), 1, pf_curso); // Leer los datos del curso seleccionado desde el archivo
        if(!comprobar(nCurso, last_nCurso) && curso.nCurso == 0){
           printf(ANSI_COLOR_RED "\n\nNº curso incorrecto.\n\n" ANSI_COLOR_RESET);
        }else{
            if(!comprobarPlazas(nCurso, curso.plazasMax, pf_matricula)){
                printf(ANSI_COLOR_RED "\n\nNo quedan plazas para este curso.\n\n" ANSI_COLOR_RESET);
            }else{
                pedirAlumno(&nAlumno, "(0 para salir)"); // Solicitar el número de alumno al usuario
                while(nAlumno != 0 && comprobarPlazas(nCurso, curso.plazasMax, pf_matricula)){
                    gestionarAlumno(pf_matricula, pf_alumn, nAlumno, nCurso, last_nAlumn); // Gestionar la matrícula del alumno en el curso
                    pedirAlumno(&nAlumno, "(0 para salir)"); // Solicitar el número de alumno al usuario nuevamente
                }
            }
        }
        system("pause");
        pedirCurso(&nCurso, "(0 para salir)"); // Solicitar el número de curso al usuario nuevamente
    }

    fclose(pf_alumn); // Cerrar el archivo de alumnos
    fclose(pf_curso); // Cerrar el archivo de cursos
    fclose(pf_matricula); // Cerrar el archivo de matrículas
}

int comprobarPlazas(int ncurso, int maxPlazas, FILE *pf_matricula){
    MATRICULA matricula;
    int matriculados = 0;
    fseek(pf_matricula, 0, SEEK_SET); // Mover el puntero de archivo al principio del archivo de matrículas
    while(fread(&matricula, sizeof(MATRICULA), 1, pf_matricula) == 1){
        if(matricula.nCurso == ncurso && matricula.nMatricula != 0){
            //Si el laumno está matriculado al curso sumamos 1 a mtriculados
            matriculados++;
        }
    }
    return maxPlazas - matriculados > 0; // Devolver verdadero si hay plazas disponibles, falso si no
}


 int alumnoMatriculadoCurso(int nCurso, int nAlumno, FILE *pf_matricula){
    MATRICULA matricula;
    fseek(pf_matricula, 0, SEEK_SET); // Mover el puntero de archivo al principio del archivo de matrículas
    while(fread(&matricula, sizeof(MATRICULA), 1, pf_matricula) == 1){
        if(matricula.nCurso == nCurso && matricula.nExp == nAlumno){
            return 1; // Devolver 1 si el alumno está matriculado en el curso
        }
    }
    return 0; // Devolver 0 si el alumno no está matriculado en el curso
}
//Gestionar matricula
 void gestionarAlumno(FILE *pf_matricula, FILE *pf_alumn, int nAlumno, int nCurso, int last_nAlumn){
    ALUMNO alumno;
    MATRICULA matricula;
    fseek(pf_alumn, sizeof(ALUMNO)*(nAlumno-1), SEEK_SET); // Mover el puntero de archivo al registro del alumno seleccionado
    fread(&alumno, sizeof(ALUMNO), 1, pf_alumn); // Leer el registro del alumno desde el archivo

    char resp;
    int nMatricula;

    if(!comprobar(nAlumno, last_nAlumn) && alumno.nExped == 0){
        printf(ANSI_COLOR_RED "\n\nNº alumno incorrecto.\n\n" ANSI_COLOR_RESET);
    }else if(alumnoMatriculadoCurso(nCurso, nAlumno, pf_matricula)){
        printf(ANSI_COLOR_RED "\n\nEl alumno ya está matriculado en el curso.\n\n" ANSI_COLOR_RESET);
    }else{
        mostrarAlumno(alumno); // Mostrar los datos del alumno
        printf(ANSI_COLOR_BLUE "\n\n¿Deseas matricularlo al curso? (s/?): " ANSI_COLOR_RESET);
        resp = tolower(_getche());

        if(resp == 's'){
            nMatricula = totalRegistro(pf_matricula, sizeof(MATRICULA)) + 1;
            escribirMatricula(&matricula, nMatricula, nCurso, nAlumno); // Crear una nueva matrícula con los datos necesarios
            fwrite(&matricula, sizeof(MATRICULA), 1, pf_matricula); // Escribir la matrícula en el archivo de matrículas
            printf(ANSI_COLOR_GREEN "\n\nAlumno matriculado correctamente.\n\n" ANSI_COLOR_RESET);
        }else{
            printf(ANSI_COLOR_CYAN "\n\nAlumno no matriculado.\n\n" ANSI_COLOR_RESET);
        }
    }
    system("pause");
}

 void escribirMatricula(MATRICULA* matricula, int nMatricula, int nCurso, int nExp){
    matricula->nMatricula = nMatricula; // Asignar el número de matrícula al campo correspondiente en la estructura matrícula
    matricula->nCurso = nCurso; // Asignar el número de curso al campo correspondiente en la estructura matrícula
    matricula->nExp = nExp; // Asignar el número de expediente al campo correspondiente en la estructura matrícula
    printf("\nNota: ");
    scanf("%f", &matricula->nota); // Leer la nota y asignarla al campo correspondiente en la estructura matrícula
}


 void mostrarMatriculas(){
    MATRICULA matricula;
    FILE* pf=fopen(RUTA_M,"rb"); // Abrir el archivo de matrículas en modo lectura binaria
    fseek(pf,0,SEEK_SET); // Ir al inicio del archivo

    while (fread(&matricula,sizeof(MATRICULA),1,pf)==1) // Leer una estructura MATRICULA del archivo
    {
        system("cls"); // Limpiar la pantalla
        printf("+----------------------------------+\n");
        printf("|         FICHERO DE ALUMNOS       |\n");
        printf("|----------------------------------|\n");
        printf("| Nº Matricula  : %7d|\n", matricula.nMatricula); // Mostrar el número de matrícula
        printf("| Nª Curso      : %7d|\n", matricula.nCurso); // Mostrar el número de curso
        printf("| Nª Exped.     : %7d|\n", matricula.nExp); // Mostrar el número de expediente
        printf("| Nota          : %-7.2f|\n", matricula.nota); // Mostrar la nota
        printf("+----------------------------------+\n");
        system("pause"); // Pausar la ejecución para que el usuario pueda ver la información
    }
    fclose(pf); // Cerrar el archivo
}

