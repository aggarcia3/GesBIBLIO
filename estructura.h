#ifndef ESTRUCTURA_H_INCLUDED
#define ESTRUCTURA_H_INCLUDED

    #include "headers.h"

    #define MAXLIBROS UINT8_MAX - 1
    #define MAXTITULO 100
    #define MAXISBN 20
    #define MAXAUTORIA 50
    #define MAXEDITORIAL 50
    #define MAXFORMATO 12

    typedef struct {
        uint8_t dia;
        uint8_t mes;
        uint16_t anho;
    } data;

    typedef struct {
        char ISBN[MAXISBN];
        char titulo[MAXTITULO];
        char autoria[MAXAUTORIA];
        char editorial[MAXEDITORIAL];
        char formato[MAXFORMATO];
        float precio;
        data fecha;
    } Libro;

    typedef struct {
        Libro Libros[MAXLIBROS];  // Array donde almacenamos todos los libros
        uint8_t numLibros;  // Número total de libros existentes en el vector Libros
    } setLibros ;

    typedef struct {
        char firma[10];   // GESBIBLIO1
        size_t tamanoSet; // sizeof(setLibros)
        setLibros libros;
    } archivoLibros;

#endif // ESTRUCTURA_H_INCLUDED
