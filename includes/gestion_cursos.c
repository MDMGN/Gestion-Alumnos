#include "header.h"

void gestionCursos(){
    system("cls"); // Limpiar la pantalla
    // Opciones del menú de gestión de cursos
    char * menu_gestion_cursos[30]={"1. COMENZAR CURSO.","2. FINALIZAR CURSO.","3. BOLETIN ALUMNO.","4. VOLVER."};
    // Array de punteros a funciones correspondientes a cada opción del menú
    void (*function[])()={comenzarCurso,finalizarCurso,boletinAlumno};
    // Mostrar el menú y obtener la opción seleccionada
    int opc=menu(menu_gestion_cursos,4,"MENU GESTIÓN DE CURSOS");
    // Ciclo principal del menú
    while(opc!=4){
        (* function[opc-1])(); // Llamar a la función correspondiente a la opción seleccionada
        opc=menu(menu_gestion_cursos,4,"MENU GESTIÓN DE CURSOS"); // Mostrar el menú nuevamente y obtener la siguiente opción
    }
    printf(ANSI_COLOR_MAGENTA "\n\nPresionar una tecla para volver..." ANSI_COLOR_RESET); // Mostrar mensaje para volver
}


void comenzarCurso(){
    system("cls"); // Limpiar la pantalla

    FILE *pf_alumn,*pf_curso,*pf_matricula; // Declarar los punteros a los archivos
    CURSO curso;
    int last_nCurso,last_nAlumn, nCurso;

    pf_alumn=fopen(RUTA_A,"rb"); // Abrir el archivo de alumnos en modo lectura binaria
    pf_curso=fopen(RUTA_C,"rb+"); // Abrir el archivo de cursos en modo lectura y escritura binaria
    pf_matricula=fopen(RUTA_M,"rb"); // Abrir el archivo de matrícula en modo lectura binaria

    // Comprobar si se encontraron los archivos
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

    last_nCurso=totalRegistro(pf_curso,sizeof(CURSO)); // Obtener el último número de curso registrado

    pedirCurso(&nCurso,""); // Solicitar el número del curso a comenzar
    fseek(pf_curso,sizeof(CURSO)*(nCurso -1),SEEK_SET); // Ir a la posición del curso en el archivo
    fread(&curso,sizeof(CURSO),1,pf_curso); // Leer el curso desde el archivo
    // Comprobar si el número de curso es válido y el curso no ha sido iniciado
    if(comprobar(nCurso,last_nCurso) && curso.nCurso!=0){
        if(!curso.iniciado){ // Si el curso no ha sido iniciado
            curso.iniciado=1; // Marcar el curso como iniciado
            curso.finalizado=0; // Marcar el curso como no finalizado
            fseek(pf_curso,sizeof(CURSO)*(nCurso -1),SEEK_SET); // Ir a la posición del curso en el archivo
            fwrite(&curso,sizeof(CURSO),1,pf_curso); // Escribir el curso actualizado en el archivo

            // Generar informe de alumnos matriculados en el curso y comprobar si se generó correctamente
            if(informeAlumnosPorCurso(nCurso,pf_matricula,pf_alumn)) 
                printf(ANSI_COLOR_GREEN "\n\nInforme generado en: informes/matriculados.txt\n\n" ANSI_COLOR_RESET);
        }else{
            printf(ANSI_COLOR_RED "\n\nEl curso ya ha sido iniciado.\n\n" ANSI_COLOR_RESET);
        }
    }else{
        printf(ANSI_COLOR_RED "\n\nNª de cursos no valido.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf_matricula); // Cerrar el archivo de matrícula
    fclose(pf_curso); // Cerrar el archivo de cursos
    fclose(pf_alumn); // Cerrar el archivo de alumnos

    system("pause"); // Pausar la ejecución del programa
}


int informeAlumnosPorCurso(int nCurso, FILE* pf_matriculas, FILE* pf_alumnos) {
    system("cls");
    MATRICULA matricula;
    ALUMNO alumno;
    fseek(pf_matriculas, 0, SEEK_SET);
    FILE* pf = fopen(RUTA_INFO_AL, "w");

    if (pf == NULL) {
        // Carpeta "informes" no encontrada
        printf(ANSI_COLOR_RED "\n\nNo se encuentra la carpeta informes.\n\n");
        printf("\n\nInforme de resúmenes no generado.\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return 0;
    }

    // Encabezado del informe
    fprintf(pf, "\n+----------------------------------------+\n");
    fprintf(pf, "| %-17s | %-18s |\n", "CURSO", "ALUMNO");
    fprintf(pf, "+----------------------------------------+\n");

    while (fread(&matricula, sizeof(MATRICULA), 1, pf_matriculas) == 1) {
        if (matricula.nCurso == nCurso && matricula.nMatricula != 0) {
            fseek(pf_alumnos, sizeof(ALUMNO) * (matricula.nExp - 1), SEEK_SET);
            fread(&alumno, sizeof(ALUMNO), 1, pf_alumnos);
            // Agregar línea al informe con el número del curso y el nombre del alumno
            fprintf(pf, "| %-17d | %-18s |\n", nCurso, alumno.nombre);
            fprintf(pf, "+----------------------------------------+\n");
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
    //Abrimos los ficheros en modo lectura y lectura mas escritura
    pf_alumn=fopen(RUTA_A,"rb");
    pf_curso=fopen(RUTA_C,"rb+");
    pf_matricula=fopen(RUTA_M,"rb+");
    //Si algunos de los ficheros tienen problema al abrirse, mostrar error
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

    pedirCurso(&nCurso,"");//Pedir curso
    fseek(pf_curso,sizeof(CURSO)*(nCurso-1),SEEK_SET); // Mover la posicion del del fichero al curso
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

void gestionarNotas(int nCurso, FILE* pf_matriculas, FILE* pf_alumnos) {
    MATRICULA matricula;
    ALUMNO alumno;
    float nota;
    int i = 1;
    // Posiciona el puntero del archivo de matrículas al inicio
    fseek(pf_matriculas, 0, SEEK_SET);
    while (fread(&matricula, sizeof(MATRICULA), 1, pf_matriculas) == 1) {
        i++;
        // Verifica si la matrícula corresponde al curso y no está vacía
        if (matricula.nCurso == nCurso && matricula.nMatricula != 0) {
            // Posiciona el puntero del archivo de alumnos en la posición correcta
            fseek(pf_alumnos, sizeof(ALUMNO) * (matricula.nExp - 1), SEEK_SET);
            fread(&alumno, sizeof(ALUMNO), 1, pf_alumnos);
            mostrarAlumno(alumno);
            pedirNota(&nota);
            matricula.nota = nota;
            // Posiciona el puntero del archivo de matrículas en la posición correcta
            fseek(pf_matriculas, sizeof(MATRICULA) * (matricula.nMatricula - 1), SEEK_SET);
            fwrite(&matricula, sizeof(MATRICULA), 1, pf_matriculas);
            printf(ANSI_COLOR_GREEN "\n\nLa nota se guardó con éxito!\n\n" ANSI_COLOR_RESET);
            system("pause");
            // Posiciona el puntero del archivo de matrículas en la siguiente posición
            fseek(pf_matriculas, sizeof(MATRICULA) * (i - 1), SEEK_SET);
        }
    }
}


void pedirNota(float* nota) {
    printf("\n\nNota: ");
    scanf("%f", nota);
    fflush(stdin);
    // Verifica si la nota está fuera del rango válido (0-10)
    if (*nota < 0.0f || *nota > 10.0f) {
        printf(ANSI_COLOR_RED "\n\nLa nota debe estar entre 0 y 10.\n\n" ANSI_COLOR_RESET);
        system("pause");
        // Vuelve a pedir la nota
        pedirNota(nota);
    }
    return;
}


int informeResumen(FILE* pf_matriculas, FILE* pf_cursos) {
    system("cls");
    MATRICULA matricula;
    CURSO curso;
    RESUMEN resumen;
    FILE* pf = fopen(RUTA_INFO_RE, "w");
    FILE* pf_resumenes = fopen(RUTA_RE, "ab+");
    
    // Comprobar si los archivos se abrieron correctamente
    if (pf_resumenes == NULL || pf == NULL) {
        printf(ANSI_COLOR_RED "\n\nNo se encuentra la carpeta 'data' o 'informes'.\n\n");
        printf("\n\nInforme de resúmenes no generado.\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        fclose(pf_resumenes);
        system("pause");
        return 0;
    }
    
    int nAlumnos, encontrados, total = 0;
    float avg_nota;
    
    // Imprimir el encabezado del informe
    fprintf(pf, "\n+----------------------------------------------------------------------------------------+\n");
    fprintf(pf, "| %23s %38s %23s |\n", "", "LISTADO RESUMEN DE CURSOS FINALIZADOS", "");
    fprintf(pf, "+----------------------------------------------------------------------------------------+\n");
    fprintf(pf, "| %5s | %-20s | %10s | %12s | %-13s | %-10s |\n", "CURSO", "DESCRIPCION", "FECHA INICIO", "FECHA FIN", "Nº ALUMNOS", "NOTA MEDIA");
    fprintf(pf, "+----------------------------------------------------------------------------------------+\n");
    fseek(pf_cursos, 0, SEEK_SET);
    while (fread(&curso, sizeof(CURSO), 1, pf_cursos) == 1) {
        if (curso.finalizado && curso.nCurso != 0) {
            avg_nota = nAlumnos = encontrados = 0;
            
            fseek(pf_matriculas, 0, SEEK_SET);
            while (fread(&matricula, sizeof(MATRICULA), 1, pf_matriculas) == 1 && !encontrados) {
                if (matricula.nCurso == curso.nCurso && matricula.nMatricula != 0) {
                    nAlumnos++;
                    avg_nota += matricula.nota;
                    if (curso.plazasMax == nAlumnos)
                        encontrados = 1;
                }
            }
            avg_nota /= nAlumnos;
            // Imprimir la información del curso en el informe
            fprintf(pf, "| %5d | %-20s | %3d/%3d/%4d | %3d/%3d/%4d | %12d | %10.2f |\n", curso.nCurso, curso.description, curso.fInicio.dia, curso.fInicio.mes, curso.fInicio.anio, curso.fFin.dia, curso.fFin.mes, curso.fFin.anio, nAlumnos, avg_nota);
            fprintf(pf, "+----------------------------------------------------------------------------------------+\n");
            
            // Asignar los valores a la estructura resumen
            resumen.nCurso = curso.nCurso;
            strcpy(resumen.description, curso.description);
            resumen.fInicio = curso.fInicio;
            resumen.ffin = curso.fFin;
            resumen.n_alumnos = nAlumnos;
            resumen.media_curso = avg_nota;
            
            // Guardar la estructura resumen en el archivo de resúmenes
            fwrite(&resumen, sizeof(RESUMEN), 1, pf_resumenes);
            
            total += nAlumnos;
        }
    }
    
    // Imprimir los totales en el informe
    fprintf(pf, "| %42s  | %12s | %12d | %10s |\n", "", "Totales", total, "");
    fprintf(pf, "+----------------------------------------------------------------------------------------+\n");
    fclose(pf);
    fclose(pf_resumenes);
    return 1;
}


void boletinAlumno() {
    system("cls");
    FILE* pf_alumnos;
    FILE* pf_cursos;
    FILE* pf_matriculas;
    ALUMNO alumno;
    int last_nAlumn, nExp;

    // Abrir archivos necesarios
    pf_alumnos = fopen(RUTA_A, "rb");
    pf_cursos = fopen(RUTA_C, "rb");
    pf_matriculas = fopen(RUTA_M, "rb");

    // Comprobar si se abrieron correctamente los archivos
    if (pf_alumnos == NULL) {
        printf(ANSI_COLOR_RED "\n\nError: No se encontró el archivo 'data/alumnos.data'.\n\n" ANSI_COLOR_RESET);
        fclose(pf_alumnos);
        system("pause");
        return;
    } else if (pf_cursos == NULL) {
        printf(ANSI_COLOR_RED "\n\nError: No se encontró el archivo 'data/cursos.data'.\n\n" ANSI_COLOR_RESET);
        fclose(pf_cursos);
        system("pause");
        return;
    } else if (pf_matriculas == NULL) {
        printf(ANSI_COLOR_RED "\n\nError: No se encontró el archivo 'data/matricula.data'.\n\n" ANSI_COLOR_RESET);
        fclose(pf_matriculas);
        system("pause");
        return;
    }

    // Obtener el último número de expediente de alumnos
    last_nAlumn = totalRegistro(pf_alumnos, sizeof(ALUMNO));

    // Solicitar el número de expediente del alumno
    pedirAlumno(&nExp, "");

    // Leer el registro del alumno correspondiente al número de expediente ingresado
    fseek(pf_alumnos, sizeof(ALUMNO) * (nExp - 1), SEEK_SET);
    fread(&alumno, sizeof(ALUMNO), 1, pf_alumnos);

    // Verificar si el número de expediente es válido y el alumno existe
    if (comprobar(nExp, last_nAlumn) && alumno.nExped != 0) {
        mostrarAlumno(alumno);
        system("pause");

        // Generar informe de boletín para el alumno
        if (informeBoletinAlumno(nExp, pf_matriculas, pf_cursos, alumno))
            printf(ANSI_COLOR_GREEN "\n\nInforme generado en 'informes/boletin.txt'.\n\n" ANSI_COLOR_RESET);
    } else {
        printf(ANSI_COLOR_RED "\n\nNº de alumno incorrecto.\n\n" ANSI_COLOR_RESET);
    }

    // Cerrar archivos
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