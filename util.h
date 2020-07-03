#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

    #include "headers.h"

    #define LONGITUD_ENTERO 5 // 4 dígitos + \0
    #define LONGITUD_FLOTANTE 7 // 6 dígitos + \0

    // Declaraciones de las funciones necesarias para leer enteros, reales y cadenas de caracteres

    unsigned short limpiarStdin();
    void leerCadena(char mensaje[], char cad[], unsigned short num, bool aceptarNulo);
    int leerEntero(char mensaje[], bool aceptarNulo);
    float leerFlotante(char mensaje[], bool aceptarNulo);
    bool leerRespuesta(char mensaje[]);

#endif // UTIL_H_INCLUDED
