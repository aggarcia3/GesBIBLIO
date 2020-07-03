#ifndef LIBRO_H_INCLUDED
#define LIBRO_H_INCLUDED

    #define LIBRO_INVALIDO UINT8_MAX
    #define ARCHIVO_LIBROS "librosguardados.dat" // Nombre del archivo donde se guardarán los libros

    #include "headers.h"
    #include "estructura.h"

    extern bool librosGuardados;

    /* Declaraciones de las funciones necesarias específicas para gestionar la biblioteca
       Todos los argumentos se pasan por referencia para mejorar el rendimiento */

    void listarLibros(setLibros *variosLibros);
    void insertarLibro(setLibros *variosLibros);
    void borrarLibro(setLibros *variosLibros);
    void busquedaLibroISBN(setLibros *variosLibros);
    void busquedaLibroTitulo(setLibros *variosLibros);
    void busquedaLibrosAutor(setLibros *variosLibros);
    void modificarLibro(setLibros *variosLibros);

    void cargadoLibros(setLibros *variosLibros);
    bool cargarLibros(const char *nombreArchivo, setLibros *variosLibros);
    bool guardarLibros(const char *nombreArchivo, setLibros *variosLibros);

#endif // LIBRO_H_INCLUDED
