#include "header.h"

void menuCurso(){
    system("cls");
    // Array de opciones del menú de cursos
    char * menu_alummnos[30]={"1. ALTA.","2. MODIFICACIÓN.","3. CONSULTA.","4. ELIMINAR","5. VOLVER."};
    // Array de punteros a funciones correspondientes a cada opción del menú
    void (*function[])()={altaCurso,modificarCurso,consultaCurso,eliminarCurso};
    // Mostrar el menú y obtener la opción seleccionada por el usuario
    int opc=menu(menu_alummnos,5,"MENU CURSOS");
    // Bucle para ejecutar la opción seleccionada hasta que se elija la opción de volver
    while(opc!=5){
        // Llamar a la función correspondiente a la opción seleccionada
        (* function[opc-1])();
        // Mostrar el menú nuevamente y obtener la nueva opción seleccionada
        opc=menu(menu_alummnos,5,"MENU CURSOS");
    }
    printf(ANSI_COLOR_MAGENTA "\n\nPresionar una tecla para volver..." ANSI_COLOR_RESET);
}

//Dar de alta un curso
void altaCurso(){
    system("cls");
    CURSO curso;FILE *pf;char resp;

    // Abrir o crear el archivo de cursos
    pf=fopen(RUTA_C,"ab+");
    if(pf==NULL){
        printf(ANSI_COLOR_RED "\nError: No se encuentra la carpeta data.\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("cls");
        return;
    }

    // Obtener el número de curso sumando 1 al total de registros en el archivo
    curso.nCurso=totalRegistro(pf,sizeof(CURSO))+1;

    // Mostrar el menú de ingreso de datos del curso
    printf("+--------------------------------------------------------+\n");
    printf("|                FICHERO DE CURSO                        |\n");
    printf("|--------------------------------------------------------|\n");
    printf("| Nº Curso      : %-39d|\n", curso.nCurso);
    printf("| Descripción   : %-15s Plazas max: %-11s|\n", "","");
    printf("| Desde         : %-15s Hasta     : %-11s|\n", "","");
    printf("+--------------------------------------------------------+\n");

    // Obtener los datos del curso ingresados por el usuario
    introducirDatosCurso(&curso);

    // Inicializar los campos "iniciado" y "finalizado" del curso
    curso.iniciado=0;
    curso.finalizado=0;

    // Pedir confirmación para guardar el registro del curso
    printf(ANSI_COLOR_BLUE "\n¿Desea guardar el registro? (s/?): " ANSI_COLOR_RESET);
    resp=tolower(_getche());
    if(resp=='s'){
        // Guardar la estructura de CURSO con los datos ingresados en el archivo
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
    // Obtener la descripción del curso
    gotoXY(18,4);
    obtenerDato(curso->description,20);
    // Obtener el número máximo de plazas del curso
    gotoXY(46,4);
    scanf("%d",&curso->plazasMax);
    fflush(stdin);
    // Obtener la fecha de inicio del curso
    gotoXY(18,5);
    obtenerDato(date,11);
    insertarFecha(date,&curso->fInicio);
    // Validar la fecha de inicio ingresada
    while(!validarFecha(curso->fInicio)){
        gotoXY(18,9);
        printf(ANSI_COLOR_RED "\n\nIntroduzca una fecha correcta (dd/mm/aaaa).\n\n" ANSI_COLOR_RESET);
        gotoXY(18,5);
        obtenerDato(date,11);
        insertarFecha(date,&curso->fInicio);
    }
    gotoXY(0,11);
    printf("                                                                                     ");
    // Obtener la fecha de finalización del curso
    gotoXY(46,5);
    obtenerDato(date,11);
    insertarFecha(date,&curso->fFin);
    // Validar la fecha de finalización ingresada
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
//Consultar curso
void consultaCurso(){
    system("cls");
    CURSO curso;FILE *pf;int last_ncurs, nCurs;
    // Abrir el archivo de cursos en modo lectura
    pf=fopen(RUTA_C,"rb");
    // Comprobar si el archivo existe
    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nError al intentar abrir el fichero data/curso.dat\n\n." ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return;
    }
    // Obtener el número total de cursos en el archivo
    last_ncurs=totalRegistro(pf,sizeof(CURSO));
    // Pedir el número de curso al usuario
    pedirCurso(&nCurs,"");
    // Mover el puntero de lectura al registro correspondiente al número de curso ingresado
    fseek(pf,(nCurs-1)*sizeof(CURSO),SEEK_SET);
    // Leer el curso del archivo
    fread(&curso, sizeof(curso), 1, pf);
    // Comprobar si el número de curso ingresado es válido y el curso existe
    if(comprobar(nCurs,last_ncurs) && curso.nCurso!=0){
        mostrarCurso(curso);
        printf(ANSI_COLOR_GREEN "\n\nFichero cargado correctamente.\n\n" ANSI_COLOR_RESET);
    }else{
        printf(ANSI_COLOR_RED "\n\nNº de curso incorrecto.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf);
    system("pause");
}

//modificar curso
void modificarCurso(){
    system("cls");
    CURSO curso;FILE *pf;int last_ncurs, nCurs;
    char resp;

    // Abrir el archivo de cursos en modo lectura y escritura
    pf=fopen(RUTA_C,"rb+");

    // Comprobar si el archivo existe
    if(pf==NULL){
        printf(ANSI_COLOR_RESET "\n\nError al intentar abrir el fichero data/curso.dat\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return;
    }

    // Obtener el número total de cursos en el archivo
    last_ncurs=totalRegistro(pf,sizeof(CURSO));

    // Pedir el número de curso al usuario
    pedirCurso(&nCurs,"");

    // Mover el puntero de lectura al registro correspondiente al número de curso ingresado
    fseek(pf, (nCurs-1) * sizeof(CURSO), SEEK_SET);

    // Leer el curso del archivo
    fread(&curso, sizeof(curso), 1, pf);

    // Comprobar si el número de curso ingresado es válido y el curso existe
    if(comprobar(nCurs,last_ncurs) && curso.nCurso!=0){
        do{
            mostrarCurso(curso);
            editarCurso(&curso);
            printf(ANSI_COLOR_BLUE "\nDeseas seguir? (s/?): " ANSI_COLOR_RESET);
            resp=tolower(_getche());
        }while (resp=='s');

        // Mover el puntero de escritura al registro correspondiente al número de curso ingresado
        fseek(pf,(curso.nCurso-1)*sizeof(CURSO),SEEK_SET);

        // Escribir el curso modificado en el archivo
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
    // Pedir al usuario el dato que desea editar
    printf(ANSI_COLOR_BLUE "\n¿Qué dato deseas editar?: " ANSI_COLOR_RESET);
    scanf("%d",&resp);
    fflush(stdin);
    switch(resp){
        case 1:
            printf("\n Descripción: ");
            obtenerDato(curso->description,sizeof(curso->description));
            break;
        case 2:
            printf("\n Plazas max: ");
            scanf("%d",&curso->plazasMax);
            break;
        case 3:
            printf("\n Desde: ");
            obtenerDato(date,11);
            insertarFecha(date,&curso->fInicio);
            break;
        case 4:
            printf("\n Hasta: ");
            obtenerDato(date,11);
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
    // Si se ha modificado algún dato mistramos el mensaje.
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
    // Si el curso ha sido iniciado guardamos "Si" o en caso contrario "No"
    const char *iniciado= (curso.iniciado) ? "Sí" :  "No";
    // Si el curso ha sido finalizado guardamos "Si" o en caso contrario "No"
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
    int nCurso, lastNCurso;
    char resp;

    pf=fopen(RUTA_C,"rb+"); // Abrir el archivo en modo lectura y escritura binaria

    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nError al intentar abrir el fichero data/curso.dat\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return;
    }

    lastNCurso=totalRegistro(pf,sizeof(CURSO)); // Obtener el total de registros en el archivo

    pedirCurso(&nCurso,""); // Solicitar el número de curso al usuario

    fseek(pf,sizeof(CURSO)*(nCurso-1),SEEK_SET); // Desplazar el puntero de lectura/escritura al registro correspondiente
    fread(&curso,sizeof(CURSO),1,pf); // Leer el registro del curso desde el archivo

    if(comprobar(nCurso,lastNCurso) && curso.nCurso!=0){ // Comprobar si el número de curso es válido y si el curso existe
        mostrarCurso(curso); // Mostrar los datos del curso

        printf(ANSI_COLOR_BLUE "\n\n¿Deseas seguir? (s/?): " ANSI_COLOR_RESET);
        resp=_getche();

        if(resp=='s'){
            curso.nCurso=0; // Marcar el curso como eliminado asignando 0 al número de curso
            fseek(pf,sizeof(CURSO)*(nCurso-1),SEEK_SET); // Desplazar el puntero de escritura al registro correspondiente
            fwrite(&curso,sizeof(CURSO),1,pf); // Escribir el registro modificado en el archivo

            if(eliminarMatriculaCurso(nCurso)) // Eliminar las matrículas asociadas al curso
                printf(ANSI_COLOR_GREEN "\n\n Curso eliminado correctamente.\n\n" ANSI_COLOR_RESET);
        }
    }else{
        printf(ANSI_COLOR_RED "\n\n Nº de curso incorrecto.\n\n" ANSI_COLOR_RESET);
    }
    fclose(pf); // Cerrar el archivo
    printf("\n\n");
    system("pause");
}
//eliminar matricula del curso
int eliminarMatriculaCurso(int nCurso){
    FILE *pf_matricula;
    MATRICULA matricula;

    pf_matricula=fopen(RUTA_M,"rb+"); // Abrir el archivo de matrículas en modo lectura y escritura binaria
    if(pf_matricula==NULL){
        printf(ANSI_COLOR_RED "\n\nError al intentar abrir el fichero data/matricula.dat\n\n" ANSI_COLOR_RESET);
        fclose(pf_matricula);
        return 0;
    }
    fseek(pf_matricula,0,SEEK_SET); // Desplazar el puntero al inicio del archivo de matrículas
    while(fread(&matricula,sizeof(MATRICULA),1,pf_matricula)==1){ // Leer cada registro de matrícula en el archivo
        if(matricula.nMatricula==nCurso){ // Verificar si el número de curso de la matrícula coincide con el curso a eliminar
            matricula.nMatricula=0; // Marcar la matrícula como eliminada asignando 0 al número de curso
            fseek(pf_matricula,sizeof(MATRICULA)*(matricula.nMatricula-1),SEEK_SET); // Desplazar el puntero de escritura al registro correspondiente
            fwrite(&matricula,sizeof(MATRICULA),1,pf_matricula); // Escribir el registro modificado en el archivo
        }
    }
    fclose(pf_matricula); // Cerrar el archivo de matrículas
    return 1;
}
