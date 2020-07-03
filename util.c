#include "util.h"

unsigned short limpiarStdin() { // Nota: la función asume que hay caracteres en stdin
    char c;
    unsigned short i = 0; // Número de caracteres leídos

    do {
        c = getchar();
        i++;
    } while (c != '\n');

    return i;
}

void leerCadena(char mensaje[], char cad[], unsigned short num, bool aceptarNulo) {
    char *n;

    fputs(mensaje, stdout);

    // Leer una línea de texto desde el teclado limitada a num caracteres
    fgets(cad, num, stdin);

    // Ver si contiene \n
    n = strstr(cad, "\n");
    if (n != NULL) {
        /* Si contiene \n, la hicimos más corta o igual de larga de lo posible
           Sustituir \n por \0 para correcto almacenamiento en memoria
           Si se quiere, también comprobar si introduce una cadena nula, y pedirle otra en tal caso */
        strncpy(n, "\0", 1);
        if (!aceptarNulo && strlen(cad) == 0) {
            fputs("\n Tiene que introducir un dato.", stdout);
            leerCadena(mensaje, cad, num, aceptarNulo);
        }
    } else {
        /* Si es más larga de lo debido, descartar caracteres sobrantes
           Avisarle también al usuario y pedirle el dato otra vez si hemos truncado lo que escribió */
        if (limpiarStdin() > 1) {
            printf("\n El dato introducido es demasiado largo (%d caracter/es máximo)", num - 1);
            leerCadena(mensaje, cad, num, aceptarNulo);
        }
    }
}

int leerEntero(char mensaje[], bool aceptarNulo) {
    char entero[LONGITUD_ENTERO];

    leerCadena(mensaje, entero, LONGITUD_ENTERO, aceptarNulo);

    return atoi(entero);
}

float leerFlotante(char mensaje[], bool aceptarNulo) {
    char flotante[LONGITUD_FLOTANTE];

    leerCadena(mensaje, flotante, LONGITUD_FLOTANTE, aceptarNulo);

    return atof(flotante);
}

bool leerRespuesta(char mensaje[]) {
    char caracter[2];
    bool respuesta = false;

    // Pedirle al usuario una respuesta sí/no a un mensaje
    do {
        leerCadena(mensaje, caracter, 2, true);
        *caracter = tolower(*caracter); // Ignorar mayúsculas

        switch (*caracter) {
            case 's':
                respuesta = true;
                break;
            case 'n':
                respuesta = false;
                break;
            default:
                puts("\n La respuesta dada no es válida.");
        }
    } while (*caracter != 's' && *caracter != 'n');

    return respuesta;
}
