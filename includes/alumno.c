#include "header.h"

// Introducimos los datos del alumno
void introducirDatosAlumno(ALUMNO *alumno){
        // Posicionamos el cursor en la coordenada (18, 4) de la pantalla
        gotoXY(18,4);
        // Obtenemos el dato del nombre del alumno desde la entrada del usuario
        obtenerDato(alumno->nombre,20);

        // Posicionamos el cursor en la coordenada (18, 5) de la pantalla
        gotoXY(18,5);
        // Obtenemos el dato del domicilio del alumno desde la entrada del usuario
        obtenerDato(alumno->domicilio,20);

        // Posicionamos el cursor en la coordenada (18, 6) de la pantalla
        gotoXY(18,6);
        // Obtenemos el dato del código postal del alumno desde la entrada del usuario
        obtenerDato(alumno->codPost,6);

        // Posicionamos el cursor en la coordenada (18, 7) de la pantalla
        gotoXY(18,7);
        // Obtenemos el dato del municipio del alumno desde la entrada del usuario
        obtenerDato(alumno->municipio,15);

        // Posicionamos el cursor en la coordenada (18, 8) de la pantalla
        gotoXY(18,8);
        // Obtenemos el dato del NIF del alumno desde la entrada del usuario
        obtenerDato(alumno->nif,11);
}


// Consultamos la información del alumno
void consultaAlumno(){
    // Limpiamos la pantalla
    system("cls");
    ALUMNO alumno;
    FILE *pf;
    int last_nexp, nExp;

    // Abrimos el archivo de datos en modo lectura y escritura binaria
    pf=fopen(RUTA_A,"rb+");

    // Verificamos si se pudo abrir el archivo correctamente
    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nError al intentar abrir el fichero data/alumnos.dat\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return;
    }

    // Obtenemos el último número de expediente registrado en el archivo
    last_nexp=totalRegistro(pf,sizeof(ALUMNO));

    // Solicitamos al usuario el número de expediente a consultar
    pedirAlumno(&nExp,"");

    // Posicionamos el puntero en el registro correspondiente al número de expediente ingresado
    fseek(pf, (nExp-1) * sizeof(alumno), SEEK_SET);

    // Leemos los datos del alumno desde el archivo
	fread(&alumno, sizeof(alumno), 1, pf);

    // Comprobamos si el número de expediente ingresado es válido y si el alumno existe en el archivo
    if(comprobar(nExp,last_nexp) && alumno.nExped!=0){
        // Mostramos los datos del alumno en pantalla
        mostrarAlumno(alumno);
        printf(ANSI_COLOR_GREEN "\n\nFichero cargado correctamente.\n\n" ANSI_COLOR_RESET);
    }else{
        printf(ANSI_COLOR_RED "\n\nNº de expediente incorrecto.\n\n" ANSI_COLOR_RESET);
    }

    // Cerramos el archivo
    fclose(pf);
    system("pause");
}


    // Modificamos los datos del alumno
void editarAlumno(ALUMNO *alumno){
    int resp, success=1;

    // Solicitamos al usuario el número correspondiente al dato que desea editar
    printf(ANSI_COLOR_BLUE "\n¿Qué dato deseas editar?: " ANSI_COLOR_RESET);
    scanf("%d",&resp);
    rewind(stdin);

    switch(resp){
        case 1:
            // Modificamos el nombre del alumno
            printf("\n Nombre: ");
            obtenerDato(alumno->nombre,20);
            break;
        case 2:
            // Modificamos el domicilio del alumno
            printf("\n Domicilio: ");
            obtenerDato(alumno->domicilio,20);
            break;
        case 3:
            // Modificamos el código postal del alumno
            printf("\n Código postal: ");
            obtenerDato(alumno->codPost,6);
            break;
        case 4:
            // Modificamos el municipio del alumno
            printf("\n Municipio: ");
            obtenerDato(alumno->municipio,15);
            break;
        case 5:
            // Modificamos el NIF del alumno
            printf("\n N.I.F: ");
            obtenerDato(alumno->nif,11);
            break;
        default:
            // Opción incorrecta seleccionada
            printf(ANSI_COLOR_CYAN "\n\n Opción incorrecta..." ANSI_COLOR_RESET);
            success=0;
            break;
    }

    if(success) printf(ANSI_COLOR_GREEN "\n\n Modificación exitosa!\n\n" ANSI_COLOR_RESET);
}


void menuAlumno() {
    system("cls");  // Limpia la pantalla de la consola

    // Definición de las opciones del menú de alumnos
    char *menu_alumnos[30] = {"1. ALTA.", "2. MODIFICACIÓN.", "3. CONSULTA.", "4. ELIMINAR", "5. VOLVER."};

    // Definición de un arreglo de punteros a funciones para las opciones del menú
    void (*function[])() = {altaAlumno, modificarAlumno, consultaAlumno, eliminarAlumno};

    // Mostrar el menú de alumnos y obtener la opción seleccionada por el usuario
    int opc = menu(menu_alumnos, 5, "MENU ALUMNOS");

    // Ejecutar la opción seleccionada hasta que el usuario elija "VOLVER" (opción 5)
    while (opc != 5) {
        (*function[opc - 1])();  // Llamar a la función correspondiente según la opción seleccionada
        opc = menu(menu_alumnos, 5, "MENU ALUMNOS");  // Mostrar nuevamente el menú y obtener una nueva opción
    }

    printf(ANSI_COLOR_MAGENTA "\n\nPresionar una tecla para continuar..." ANSI_COLOR_RESET);
    // Mostrar un mensaje en magenta y esperar a que el usuario presione una tecla para continuar
}
void altaAlumno(){
    // Limpiamos la pantalla
    system("cls");
    ALUMNO alumno;
    FILE *pf;
    char resp;

    // Abrimos o creamos el archivo de datos en modo anexar y lectura binaria
    pf=fopen(RUTA_A,"ab+");

    // Verificamos si se pudo abrir o crear el archivo correctamente
    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nError no se encuentra la carpeta data.\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return;
    }

    // Asignamos al número de expediente del alumno el valor correspondiente al total de registros existentes más 1
    alumno.nExped=totalRegistro(pf,sizeof(ALUMNO))+1;

    // Mostramos el menú y los campos para ingresar los datos del alumno
    printf("+----------------------------------+\n");
    printf("|         FICHERO DE ALUMNOS       |\n");
    printf("|----------------------------------|\n");
    printf("| Nº Expediente : %-17d|\n", alumno.nExped);
    printf("| Nombre        : %-17s|\n", "");
    printf("| Domicilio     : %-17s|\n", "");
    printf("| Cod. Postal   : %-17s|\n", "");
    printf("| Municipio     : %-17s|\n", "");
    printf("| N.I.F.        : %-17s|\n", "");
    printf("+----------------------------------+\n");

    // Solicitamos y obtenemos los datos del alumno
    introducirDatosAlumno(&alumno);

    // Pedimos confirmación para guardar el registro
    printf(ANSI_COLOR_BLUE "\n\n¿Desea guardar el registro? (s/?): " ANSI_COLOR_RESET);
    resp=tolower(_getche());

    if(resp=='s'){
        // Guardamos la estructura ALUMNO con los datos introducidos en el archivo
        fseek(pf, 0, SEEK_SET);
        fwrite(&alumno,sizeof(alumno),1,pf);
        printf(ANSI_COLOR_GREEN "\n\nRegistro guardado con exito!!\n\n" ANSI_COLOR_RESET);
    }else{
        printf(ANSI_COLOR_CYAN "\n\nRegistro no guardado.\n\n" ANSI_COLOR_RESET);
    }

    // Cerramos el archivo
    fclose(pf);
    system("pause");
}


//Modificar los datos del alumno
void modificarAlumno(){
    // Limpiamos la pantalla
    system("cls");
    ALUMNO alumno;
    FILE *pf;
    int last_nexp, nExp;
    char resp;

    // Abrimos el archivo de datos en modo lectura y escritura binaria
    pf=fopen(RUTA_A,"rb+");

    // Verificamos si se pudo abrir el archivo correctamente
    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nError al intentar abrir el fichero data/alumnos.dat\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return;
    }

    // Obtenemos el último número de expediente registrado en el archivo
    last_nexp=totalRegistro(pf,sizeof(ALUMNO));

    // Solicitamos al usuario el número de expediente a modificar
    pedirAlumno(&nExp,"");

    // Posicionamos el puntero en el registro correspondiente al número de expediente ingresado
    fseek(pf, (nExp-1) * sizeof(alumno), SEEK_SET);

    // Leemos los datos del alumno desde el archivo
	fread(&alumno, sizeof(alumno), 1, pf);

    // Comprobamos si el número de expediente ingresado es válido y si el alumno existe en el archivo
    if(comprobar(nExp,last_nexp) && alumno.nExped!=0){
        do{
            // Mostramos los datos del alumno en pantalla
            mostrarAlumno(alumno);

            // Editamos los datos del alumno
            editarAlumno(&alumno);

            // Preguntamos si desea seguir editando
            printf(ANSI_COLOR_BLUE "\n\n¿Deseas seguir? (s/?): " ANSI_COLOR_RESET);
            resp=tolower(_getche());
        }while (resp=='s');

        // Posicionamos el puntero en el registro correspondiente al número de expediente del alumno
        fseek(pf,(alumno.nExped-1)*sizeof(alumno),SEEK_SET);

        // Sobrescribimos los datos del alumno en el archivo
        fwrite(&alumno,sizeof(alumno),1,pf);
    }else{
        printf(ANSI_COLOR_RED "\n\n Nº de expediente incorrecto.\n\n" ANSI_COLOR_RESET);
    }

    // Cerramos el archivo
    fclose(pf);
    printf("\n\n");
    system("pause");
}

//Mostrar datos del alummno
void mostrarAlumno(ALUMNO alumno){
    system("cls");
    // Mostrar el menú
    printf("+----------------------------------+\n");
    printf("|         FICHERO DE ALUMNOS       |\n");
    printf("|----------------------------------|\n");
    printf("| Nº Expediente    : %-17d|\n", alumno.nExped);
    printf("| Nombre        (1): %-17s|\n", alumno.nombre);
    printf("| Domicilio     (2): %-17s|\n", alumno.domicilio);
    printf("| Cod. Postal   (3): %-17s|\n", alumno.codPost);
    printf("| Municipio     (4): %-17s|\n", alumno.municipio);
    printf("| N.I.F.        (5): %-17s|\n", alumno.nif);
    printf("+----------------------------------+\n");
}
// Pedir NºExp de un alumno
void pedirAlumno(int* alumno,char* extra){
    // Limpiamos la pantalla
    system("cls");

    // Solicitamos al usuario el número de expediente del alumno
    printf("\nNº de Exped. %s: ",extra);
    scanf("%d",alumno);
    fflush(stdin);
 }


 void eliminarAlumno(){
    // Limpiamos la pantalla
    system("cls");
    FILE *pf;
    ALUMNO alumno;
    int nExp,lastNexp;
    char resp;

    // Abrimos el archivo de datos en modo lectura y escritura binaria
    pf=fopen(RUTA_A,"rb+");

    // Verificamos si se pudo abrir el archivo correctamente
    if(pf==NULL){
        printf(ANSI_COLOR_RED "\n\nError al intentar abrir el fichero data/alumnos.dat\n\n" ANSI_COLOR_RESET);
        fclose(pf);
        system("pause");
        return;
    }

    // Obtenemos el último número de expediente registrado en el archivo
    lastNexp=totalRegistro(pf,sizeof(ALUMNO));

    // Solicitamos al usuario el número de expediente del alumno a eliminar
    pedirAlumno(&nExp,"");

    // Posicionamos el puntero en el registro correspondiente al número de expediente ingresado
    fseek(pf,sizeof(ALUMNO)*(nExp-1),SEEK_SET);

    // Leemos los datos del alumno desde el archivo
    fread(&alumno,sizeof(ALUMNO),1,pf);

    // Comprobamos si el número de expediente ingresado es válido y si el alumno existe en el archivo
    if(comprobar(nExp,lastNexp) && alumno.nExped!=0){
        // Mostramos los datos del alumno en pantalla
        mostrarAlumno(alumno);

        // Preguntamos si desea continuar con la eliminación
        printf(ANSI_COLOR_BLUE "\n\n¿Deseas seguir? (s/?): " ANSI_COLOR_RESET);
        resp=_getche();
        if(resp=='s'){
            // Marcamos el número de expediente del alumno como 0 para indicar que está eliminado
            alumno.nExped=0;

            // Posicionamos el puntero en el registro correspondiente al número de expediente del alumno
            fseek(pf,sizeof(ALUMNO)*(nExp-1),SEEK_SET);

            // Sobrescribimos los datos del alumno en el archivo con el número de expediente marcado como 0
            fwrite(&alumno,sizeof(ALUMNO),1,pf);

            // Eliminamos las matrículas del alumno
            if(eliminarMatriculaAlumno(nExp))
                printf(ANSI_COLOR_GREEN "\n\n Alumno eliminado correctamente.\n\n" ANSI_COLOR_RESET);
        }
    }else{
        printf(ANSI_COLOR_RED "\n\n Nº de expediente incorrecto.\n\n" ANSI_COLOR_RESET);
    }

    // Cerramos el archivo
    fclose(pf);
    printf("\n\n");
    system("pause");
 }


int eliminarMatriculaAlumno(int nExp){
    // Abrimos el archivo de matrículas en modo lectura y escritura binaria
    FILE*pf_matricula;
    MATRICULA matricula;
    pf_matricula=fopen(RUTA_M,"rb+");
    fseek(pf_matricula,0,SEEK_SET);
    // Verificamos si se pudo abrir el archivo correctamente
    if(pf_matricula==NULL){
        printf(ANSI_COLOR_RED "\n\nError al intentar abrir el fichero data/matricula.dat\n\n" ANSI_COLOR_RESET);
        fclose(pf_matricula);
        return 0;
    }
    // Recorremos el archivo de matrículas
    while(fread(&matricula,sizeof(MATRICULA),1,pf_matricula)==1){
        // Comprobamos si el número de expediente de la matrícula coincide con el número de expediente del alumno a eliminar
        if(matricula.nExp==nExp){
            // Marcamos el número de matrícula como 0 para indicar que está eliminada
            matricula.nMatricula=0;
            // Posicionamos el puntero en el registro correspondiente a la matrícula y sobrescribimos los datos en el archivo
            fseek(pf_matricula,sizeof(MATRICULA)*(matricula.nMatricula-1),SEEK_SET);
            fwrite(&matricula,sizeof(MATRICULA),1,pf_matricula);
            // Salimos del bucle ya que encontramos la matrícula a eliminar
            break;
        }
    }
    // Cerramos el archivo
    fclose(pf_matricula);
    return 1;
}
