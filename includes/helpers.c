#include "header.h"

//Establece la posición del cursor x, y en la consola.
void gotoXY(int x, int y) {
    COORD pos;  // Estructura COORD para almacenar las coordenadas
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);  // Obtener el identificador de la consola
    pos.X = x;  // Establecer la coordenada X
    pos.Y = y;  // Establecer la coordenada Y
    SetConsoleCursorPosition(h, pos);  // Establecer la posición del cursor en la consola
}

// Retorna un entero del 1 al 5 de la opción introducida por el usuario.
int menu(char* menu[30],int limit,char * titulo){
    int opc;
    do{
        system("cls");
        mostrarMenu(menu,limit,titulo); 
        printf("\nIntroduzca una opción: ",limit);
        scanf("%d",&opc); // Obtenemos la opción introducida por el usuario.
        rewind(stdin); //  Limpiar lo almacenado en el buffer.
    }while(opc < 1 || opc > limit); // Validar que la opción sea entre 1 y 5
    return opc;
}

// Obtenemos el número total de registros en un archivo
int totalRegistro(FILE* pf, long sizeReg) {
    int tam;
    fseek(pf, 0, SEEK_END);    // Nos posicionamos al final del archivo
    tam = ftell(pf);           // Obtenemos la posición actual, que es el tamaño total del archivo
    fseek(pf, 0, SEEK_SET);    // Volvemos al inicio del archivo
    tam -= ftell(pf);          // Restamos la posición actual al tamaño total para obtener el tamaño de los registros
    return (tam / sizeReg);    // Dividimos el tamaño entre el tamaño de cada registro para obtener el número total de registros
}

// Insertar fecha en una estructura FECHA a partir de una cadena en formato "dd/mm/yyyy"
void insertarFecha(char date[], FECHA* fecha) {
    char *token;
    token = strtok(date, "/");         // Dividimos la cadena en tokens usando "/" como delimitador
    sscanf(token, "%d", &fecha->dia);  // Convertimos el primer token en un entero y lo asignamos al campo "dia" de la estructura FECHA
    token = strtok(NULL, "/");         // Continuamos con el siguiente token
    sscanf(token, "%d", &fecha->mes);  // Convertimos el token en un entero y lo asignamos al campo "mes" de la estructura FECHA
    token = strtok(NULL, "/");         // Continuamos con el siguiente token
    sscanf(token, "%d", &fecha->anio); // Convertimos el token en un entero y lo asignamos al campo "anio" de la estructura FECHA
}

// Comprobar si un número está dentro de los límites
int comprobar(int n, int lastN) {
    return !(n < 1 || n > lastN); // Retorna 1 si el número está dentro de los límites, 0 si no lo está
}

// Imprimir un entero para depuración
void debugearInt(int n) {
    printf("\n|%d|\n", n); // Imprime el valor del entero entre barras verticales para facilitar la visualización en la depuración
    _getch();              // Espera a que se presione una tecla antes de continuar (función específica de ciertos compiladores)
}

// Obtener la fecha actual del sistema
FECHA obtenerFechaActual() {
    FECHA fecha;
    time_t t;
    t = time(NULL);                    // Obtenemos la hora actual en formato de tiempo Unix
    struct tm* t_fecha;
    t_fecha = localtime(&t);           // Convertimos el tiempo Unix a una estructura tm para acceder a los componentes de la fecha
    fecha.dia = t_fecha->tm_mday;       // Obtenemos el día actual
    fecha.mes = t_fecha->tm_mon + 1;    // Obtenemos el mes actual (se suma 1 ya que los meses van de 0 a 11)
    fecha.anio = t_fecha->tm_year + 1900;  // Obtenemos el año actual (se suma 1900 ya que tm_year cuenta los años desde 1900)
    return fecha;                       // Devolvemos la fecha obtenida
}

//Función para validar la fecha apartir del año 1990
int validarFecha(FECHA fecha) {
    if (fecha.mes >= 1 && fecha.mes <= 12 && fecha.anio >= 1990) {
        // Verificar el rango de meses y el año mínimo

        switch (fecha.mes) {
            // Casos para los meses que tienen 31 días
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                return (fecha.dia >= 1 && fecha.dia <= 31);

            // Casos para los meses que tienen 30 días
            case 4:
            case 6:
            case 9:
            case 11:
                return (fecha.dia >= 1 && fecha.dia <= 30);

            // Caso para el mes de febrero
            case 2:
                if (fecha.anio % 4 == 0 && fecha.anio % 100 != 0 || fecha.anio % 400 == 0)
                    // Si es un año bisiesto, febrero tiene 29 días
                    return (fecha.dia >= 1 && fecha.dia <= 29);
                else
                    // Si no es un año bisiesto, febrero tiene 28 días
                    return (fecha.dia >= 1 && fecha.dia <= 28);
        }
    } else {
        // Si el mes está fuera del rango (1-12) o el año es menor a 1990, la fecha es inválida
        return 0;
    }
}


// Eliminar los espacios en blanco a la izquierda de una cadena
char* ltrim(char* s) {
    while (isspace(*s)) {  // Mientras el primer caracter de la cadena sea un espacio en blanco
        s++;              // Avanzamos el puntero al siguiente caracter
    }
    return s;             // Devolvemos el puntero a la cadena sin los espacios en blanco iniciales
}

// Eliminar los espacios en blanco a la derecha de una cadena
char* rtrim(char* s) {
    char* back = s + strlen(s);      // Apuntamos al último caracter de la cadena
    while (isspace(*--back));        // Retrocedemos desde el último caracter hasta encontrar el primer caracter que no sea un espacio en blanco
    *(back + 1) = '\0';              // Terminamos la cadena después del último caracter válido
    return s;                        // Devolvemos el puntero a la cadena sin los espacios en blanco finales
}

// Eliminar los espacios en blanco a ambos lados de una cadena
char* trim(char* s) {
    return rtrim(ltrim(s));          // Aplicamos rtrim() seguido de ltrim() para eliminar los espacios en blanco en ambos lados de la cadena
}

// Obtener un dato del usuario y eliminar los espacios en blanco
void obtenerDato(char* dato, int tam) {
    fgets(dato, tam, stdin);         // Leer la cadena de entrada del usuario
    strtok(dato, "\n");              // Eliminar el salto de línea al final de la cadena
    strcpy(dato, trim(dato));        // Eliminar los espacios en blanco al inicio y al final de la cadena
    fflush(stdin);                   // Limpiar el búfer de entrada
}

// Función para dibujar un recuadro con bordes en la consola
void recuadro(int xs, int ys, int xi, int yi) {
    for (int i = xs; i <= xi; i++) {
        gotoXY(i,ys);printf("\u2500"); // Borde horizontal
        gotoXY(i,yi);printf("\u2500"); // Borde horizontal
    }

    for (int i = ys; i <= yi; i++) {
        gotoXY(xs,i);printf("\u2502\n"); // Borde vertical
        gotoXY(xi,i);printf("\u2502\n"); // Borde vertical
    }
    gotoXY(xs,ys);printf("\u2554"); // Esquina superior izquierda
    gotoXY(xi,yi);printf("\u255D\n"); // Esquina inferior derecha
    gotoXY(xi,ys);printf("\u2557"); // Esquina superior derecha
    gotoXY(xs,yi);printf("\u255A\n"); // Esquina inferior izquierda
}
// Función para mostrar un menú con título y opciones
void mostrarMenu(char* menu[], int limit, char* titulo) {
    int i, menuWidth = 20;

    // Obtener la longitud máxima de cadena para ajustar el ancho del menú
    for (i = 0; i < limit; i++) {
        int len = strlen(menu[i]);
        if (len > menuWidth) {
            menuWidth = len;
        }
    }

    // Calcular el ancho del título
    int tituloWidth = strlen(titulo);

    // Calcular el ancho total del menú
    int totalWidth = menuWidth + 4; // Ancho del contenido del menú + 2 caracteres de espacio en cada lado

    // Calcular las coordenadas del recuadro del menú
    int xs = 0;
    int ys = 1; // Incrementamos en 1 para dejar espacio para el título
    int xi = totalWidth + 1; // Aumentamos en 1 para alinear correctamente la esquina inferior derecha
    int yi = limit + limit; // Aumentamos en limit para el espacio adicional entre el contenido y el borde inferior

    // Imprimir el menú con bordes
    recuadro(xs, ys, xi, yi);
    gotoXY(xs,ys);
    // Imprimir el título del menú centrado
    int espacioTitulo = (totalWidth - tituloWidth) / 2; // Espacio en blanco necesario para centrar el título
    printf("\n\u2502%*s%s%*s\n\n", espacioTitulo, "", titulo, espacioTitulo, "");

    for (i = 0; i < limit; i++) {
        printf("\u2502 %-*s \n", menuWidth, menu[i]);
    }

    printf("\n");
}
