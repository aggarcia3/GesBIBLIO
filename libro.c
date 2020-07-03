#include "libro.h"

// Definiciones de las funciones necesarias específicas para gestionar la biblioteca

unsigned short calcularDiasMes(uint8_t mes, uint16_t anho);

void mostrarLibro(Libro elLibro, FILE* archivoSalida);
void modificarTitulo(Libro *libro);
void modificarISBN(Libro *libro);
void modificarAutor(Libro *libro);
void modificarEditorial(Libro *libro);
void modificarFormato(Libro *libro);
void modificarPrecio(Libro *libro);
void modificarFecha(Libro *libro);

uint8_t buscarLibroISBN(setLibros *variosLibros);
uint8_t buscarLibroTitulo(setLibros *variosLibros);
uint8_t buscarLibroAutor(setLibros *variosLibros, bool soloMostrar);
uint8_t buscarLibro(setLibros *variosLibros); // Función para buscar de las tres maneras un solo libro

/* ---------------------
   Funciones específicas
   --------------------- */
unsigned short calcularDiasMes(uint8_t mes, uint16_t anho) {
    // Calcular los días que tendría el mes sin tener en cuenta un año bisiesto
    unsigned short diasMes = 28 + (mes + mes / 8) % 2 + 2 % mes + 2 * (1 / mes);

    // Si es febrero y el año es bisiesto, añadir un día
    if (mes == 2 && ((anho % 4 == 0 && anho % 100 != 0) || anho % 400 == 0)) {
        diasMes++;
    }

    return diasMes;
}

void mostrarLibro(Libro elLibro, FILE *archivoSalida) {
    FILE *salida;
    salida = archivoSalida != NULL ? archivoSalida : stdout;
    char meses[][12] = { "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre" }; // Para visualizar los meses

    fprintf(salida, "\n------------------------------------------------------\n");
    fprintf(salida, "\tTítulo: %s", elLibro.titulo);
    fprintf(salida, "\n\tISBN: %s", elLibro.ISBN);
    fprintf(salida, "\n\tAutor/a: %s", elLibro.autoria);
    fprintf(salida, "\n\tEditorial: %s", elLibro.editorial);
    fprintf(salida, "\n\tFormato: %s", elLibro.formato);
    fprintf(salida, "\n\tPrecio: %.2f %s", elLibro.precio, region->int_curr_symbol);
    fprintf(salida, "\n\tFecha: %d de %s de %d", elLibro.fecha.dia, meses[elLibro.fecha.mes - 1], elLibro.fecha.anho);
    fprintf(salida, "\n------------------------------------------------------\n");
}

void modificarTitulo(Libro *libro) {
    leerCadena("\nIntroduzca el título: ", libro->titulo, MAXTITULO, false);
}

void modificarISBN(Libro *libro) {
    leerCadena("\nIntroduzca el ISBN: ", libro->ISBN, MAXISBN, false);
}

void modificarAutor(Libro *libro) {
    leerCadena("\nIntroduzca el autor/a: ", libro->autoria, MAXAUTORIA, false);
}

void modificarEditorial(Libro *libro) {
    leerCadena("\nIntroduzca el editorial: ", libro->editorial, MAXEDITORIAL, false);
}

void modificarFormato(Libro *libro) {
    leerCadena("\nIntroduzca el formato: ", libro->formato, MAXFORMATO, false);
}

void modificarPrecio(Libro *libro) {
    char cadenaPrecio[33];
    float precio;

    sprintf(cadenaPrecio, "\nIntroduzca el precio (en %s): ", region->int_curr_symbol);
    precio = leerFlotante(cadenaPrecio, false);
    while (precio < 0) {
        precio = leerFlotante("\n El precio introducido no es válido. Introduzca otro: ", false);
    }

    libro->precio = precio;
}

void modificarFecha(Libro *libro) {
    uint16_t anho;
    uint8_t mes, dia;

    anho = leerEntero("\nIntroduzca el año (1-2017): ", true);
    while (anho < 1 || anho > 2017) {
        anho = leerEntero("\n El año introducido no es válido. Introduzca otro: ", true);
    }
    libro->fecha.anho = anho;

    mes = leerEntero("\nIntroduzca el número de mes (1-12): ", true);
    while (mes < 1 || mes > 12) {
        mes = leerEntero("\n El mes introducido no es válido. Introduzca otro: ", true);
    }
    libro->fecha.mes = mes;

    dia = leerEntero("\nIntroduzca el día del mes: ", true);
    while (dia < 1 || dia > calcularDiasMes(mes, anho)) {
        dia = leerEntero("\n El día del mes introducido no es válido. Introduzca otro: ", true);
    }
    libro->fecha.dia = dia;
}

uint8_t buscarLibroISBN(setLibros *variosLibros) {
    char ISBN[MAXISBN];
    const uint8_t numLibros = variosLibros->numLibros;
    uint8_t i;
    uint8_t libroEncontrado = LIBRO_INVALIDO;

    // Leer el ISBN del teclado
    leerCadena("\nIntroduzca el ISBN del libro a buscar: ", ISBN, MAXISBN, false);

    for (i = 0; i < numLibros; i++) {
        // Si hay un libro en el array cuyo ISBN coincide, devolver su número
        if (!strcmp(variosLibros->Libros[i].ISBN, ISBN)) {
            libroEncontrado = i;
            break;
        }
    }

    if (libroEncontrado == LIBRO_INVALIDO) {
        puts("\n No se pudo encontrar el libro especificado.");
    }

    return libroEncontrado;
}

uint8_t buscarLibroTitulo(setLibros *variosLibros) {
    char titulo[MAXTITULO];
    const uint8_t numLibros = variosLibros->numLibros;
    uint8_t i;
    uint8_t libroEncontrado = LIBRO_INVALIDO;

    // Leer el ISBN del teclado
    leerCadena("\nIntroduzca el título del libro a buscar: ", titulo, MAXTITULO, false);

    for (i = 0; i < numLibros; i++) {
        // Si hay un libro en el array cuyo ISBN coincide, devolver su número
        if (!strcmp(variosLibros->Libros[i].titulo, titulo)) {
            libroEncontrado = i;
            break;
        }
    }

    if (libroEncontrado == LIBRO_INVALIDO) {
        puts("\n No se pudo encontrar el libro especificado.");
    }

    return libroEncontrado;
}

uint8_t buscarLibroAutor(setLibros *variosLibros, bool soloMostrar) {
    char autoria[MAXAUTORIA];
    const uint8_t numLibros = variosLibros->numLibros;
    uint8_t i;
    uint8_t librosEncontrados = 0;
    uint8_t libroNum[MAXLIBROS]; // MAXLIBROS es el máximo número de libros que puede haber de un autor
    uint8_t libroIntroducido;
    bool libroCorrecto = false;

    // Inicializar el array a LIBRO_INVALIDO
    for (i = 0; i < MAXLIBROS; i++) {
        libroNum[i] = LIBRO_INVALIDO;
    }

    // Leer el autor del teclado
    leerCadena("\nIntroduzca el autor/a de los libros a buscar: ", autoria, MAXAUTORIA, false);

    for (i = 0; i < numLibros; i++) {
        // Si hay libros en el array cuyo autor coincide, guardarlos en el array
        if (!strcmp(variosLibros->Libros[i].autoria, autoria)) {
            libroNum[librosEncontrados] = i;
            librosEncontrados++;
        }
    }

    if (librosEncontrados == 0) {
        // No tenemos libros de ese autor
        printf("\n No se pudieron encontrar libros de %s.\n", autoria);
    } else if (librosEncontrados > 1) {
        // Tenemos más de un libro de ese autor, mostrarlos
        for (i = 0; i < librosEncontrados; i++) {
            if (i == 0) {
                puts("\n------------------------------------------------------");
            }
            printf("Libro %d:", libroNum[i] + 1);
            mostrarLibro(variosLibros->Libros[libroNum[i]], NULL);
        }

        // Si queremos que escoja uno, hacerlo
        if (!soloMostrar) {
            libroIntroducido = leerEntero("\nIntroduzca el número del libro que interese: ", false);
            for (i = 0; i < librosEncontrados; i++) {
                if (libroNum[i] + 1 == libroIntroducido) {
                    libroNum[0] = libroNum[i]; // Para devolver el libro deseado
                    libroCorrecto = true;
                    break;
                }
            }
            while (!libroCorrecto) {
                libroIntroducido = leerEntero("\n El libro introducido no es válido. Introduzca otro: ", false);
                for (i = 0; i < librosEncontrados; i++) {
                    if (libroNum[i] + 1 == libroIntroducido) {
                        libroNum[0] = libroNum[i]; // Para devolver el libro deseado
                        libroCorrecto = true;
                        break;
                    }
                }
            }
        }
    } else if (soloMostrar) {
        puts("\n------------------------------------------------------");
        printf("Libro %d:", libroNum[0] + 1);
        mostrarLibro(variosLibros->Libros[libroNum[0]], NULL);
    }

    // Devolver el libro buscado
    return libroNum[0];
}

uint8_t buscarLibro(setLibros *variosLibros) {
    char metodoBusqueda[2];
    uint8_t numLibro = LIBRO_INVALIDO;

    if (leerRespuesta("\n¿Quiere buscarlo? (S/N) ")) {
        // Respuesta afirmativa
        do {
            puts("\nElija método de búsqueda:");
            puts("I = por ISBN");
            puts("T = por título");
            puts("A = por autor/a");
            leerCadena("\nOpción: ", metodoBusqueda, 2, true);
            *metodoBusqueda = tolower(*metodoBusqueda);

            switch (*metodoBusqueda) {
                case 'i':
                    do {
                        numLibro = buscarLibroISBN(variosLibros);
                    } while (numLibro == LIBRO_INVALIDO);
                    break;
                case 't':
                    do {
                        numLibro = buscarLibroTitulo(variosLibros);
                    } while (numLibro == LIBRO_INVALIDO);
                    break;
                case 'a':
                    do {
                        numLibro = buscarLibroAutor(variosLibros, false);
                    } while (numLibro == LIBRO_INVALIDO);
                    break;
                default:
                    puts("\n El método de búsqueda especificado no es válido.");
            }
        } while (*metodoBusqueda != 'i' && *metodoBusqueda != 't' && *metodoBusqueda != 'a');
    } else {
        // Respuesta negativa
        numLibro = leerEntero("\nIntroduzca el número del libro: ", false);
        numLibro--;

        while (numLibro > variosLibros->numLibros - 1) {
            numLibro = leerEntero("\n El número del libro especificado no es válido. Introduzca otro: ", false);
            numLibro--;
        }
    }

    // Devolver el libro encontrado
    return numLibro;
}

/* -------------
   Listar libros
   ------------- */
void listarLibros(setLibros *variosLibros) {
    FILE *archivoSalida = stdout;
    uint8_t i;

    puts("Está listando libros.");

    if (variosLibros->numLibros == 0) {
        puts("\nNo hay libros que listar.");
    } else {
        if (leerRespuesta("\n¿Quiere exportar la lista de libros a un archivo de texto? (S/N) ")) {
            // Respuesta afirmativa
            archivoSalida = fopen("Lista de libros.txt", "w");
            if (archivoSalida == NULL) {
                printf("\n Error al crear el archivo: %s. La lista se mostrará por pantalla.", strerror(errno));
                archivoSalida = stdout;
            }
        }
        fputs("\n------------------------------------------------------\n", archivoSalida);
        for (i = 0; i < variosLibros->numLibros; i++) {
            fprintf(archivoSalida, "Libro %d:", i + 1);
            mostrarLibro(variosLibros->Libros[i], archivoSalida);
        }
    }

    if (archivoSalida != stdout) {
        fclose(archivoSalida);
        puts("\nLista de libros exportada al archivo 'Lista de libros.txt'.");
    }
}

/* ---------------
   Insertar libros
   --------------- */
void insertarLibro(setLibros *variosLibros) {
    const uint8_t numLibros = variosLibros->numLibros;
    Libro *libro;

    if (numLibros == MAXLIBROS) {
        // La array está llena de libros
        puts("No se pueden insertar libros.");
    } else {
        puts("Está insertando un nuevo libro.");

        /* Este será el nuevo libro
           numLibros siempre será una posición disponible debido a las propiedades del array */
        libro = &variosLibros->Libros[numLibros];

        // Pedir los datos del libro y guardarlos
        modificarTitulo(libro);
        modificarISBN(libro);
        modificarAutor(libro);
        modificarEditorial(libro);
        modificarFormato(libro);
        modificarPrecio(libro);
        modificarFecha(libro);

        printf("\nEl libro número %d ha sido creado correctamente.\n", numLibros + 1);

        // Incrementar el número de libros guardados
        variosLibros->numLibros++;

        // Hemos hecho cambios a la lista de libros
        librosGuardados = false;
    }
}

/* -------------
   Borrar libros
   ------------- */
void borrarLibro(setLibros *variosLibros) {
    uint8_t i, numLibro;
    const uint8_t numLibros = variosLibros->numLibros;

    puts("Está borrando un libro.");

    if (numLibros == 0) {
        // No tenemos libros en el array
        puts("\nNo hay libros que borrar.");
    } else {
        // Pedir el libro a borrar
        numLibro = buscarLibro(variosLibros);

        // Desplazar los siguientes elementos una posición atrás si no borramos el último
        if (numLibro < numLibros - 1) {
            for (i = numLibro + 1; i < numLibros; i++) {
                variosLibros->Libros[i - 1] = variosLibros->Libros[i];
            }
        }

        printf("\nEl libro %d ha sido borrado.\n", numLibro + 1);

        // Decrementar el número de libros guardados
        variosLibros->numLibros--;

        // Hemos hecho cambios a la lista de libros
        librosGuardados = false;
    }
}

/* -----------------
   Búsqueda por ISBN
   ----------------- */
void busquedaLibroISBN(setLibros *variosLibros) {
    uint8_t numLibro;

    puts("Está buscando un libro por ISBN.");

    // Obtener el libro con un ISBN
    numLibro = buscarLibroISBN(variosLibros);

    // Mostrarlo si se puede
    if (numLibro != LIBRO_INVALIDO) {
        puts("\n------------------------------------------------------");
        printf("Libro %d:", numLibro + 1);
        mostrarLibro(variosLibros->Libros[numLibro], NULL);
    }
}

/* -------------------
   Búsqueda por título
   ------------------- */
void busquedaLibroTitulo(setLibros *variosLibros) {
    uint8_t numLibro;

    puts("Está buscando un libro por título.");

    // Obtener el libro con un título
    numLibro = buscarLibroTitulo(variosLibros);

    // Mostrarlo si se puede
    if (numLibro != LIBRO_INVALIDO) {
        puts("\n------------------------------------------------------");
        printf("Libro %d:", numLibro + 1);
        mostrarLibro(variosLibros->Libros[numLibro], NULL);
    }
}

/* ------------------
   Búsqueda por autor
   ------------------ */
void busquedaLibrosAutor(setLibros *variosLibros) {
    puts("Está buscando libros por autor/a.");

    // Mostrar libros del autor
    buscarLibroAutor(variosLibros, true);
}

/* ------------------------
   Modificación de un libro
   ------------------------ */
void modificarLibro(setLibros *variosLibros) {
    uint8_t numLibro;
    char campo[2];
    Libro *libro;

    puts("Está modificando un libro.");

    // Buscar y obtener el libro a modificar
    numLibro = buscarLibro(variosLibros);
    libro = &variosLibros->Libros[numLibro];

    do {
        // Pedir el campo a modificar
        puts("\n¿Qué campo quiere modificar?");
        puts("T = título");
        puts("I = ISBN");
        puts("A = autor/a");
        puts("E = editorial");
        puts("F = formato");
        puts("P = precio");
        puts("D = fecha");
        leerCadena("Opción: ", campo, 2, true);
        *campo = tolower(*campo);

        switch (*campo) {
            case 't':
                modificarTitulo(libro);
                break;
            case 'i':
                modificarISBN(libro);
                break;
            case 'a':
                modificarAutor(libro);
                break;
            case 'e':
                modificarEditorial(libro);
                break;
            case 'f':
                modificarFormato(libro);
                break;
            case 'p':
                modificarPrecio(libro);
                break;
            case 'd':
                modificarFecha(libro);
            default:
                break;
        }
    } while (*campo != 't' && *campo != 'i' && *campo != 'a' && *campo != 'e' && *campo != 'f' && *campo != 'p' && *campo != 'd');

    printf("\nEl libro %d ha sido modificado correctamente.\n", numLibro + 1);

    // Hemos hecho cambios a la lista de libros
    librosGuardados = false;
}

/* ------------------------
   Cargar libros de archivo
   ------------------------ */
bool cargarLibros(const char *nombreArchivo, setLibros *variosLibros) {
    FILE *archivo = fopen(nombreArchivo, "rb");
    archivoLibros estructuraArchivo;
    bool cargadoExitoso = true;

    if (archivo == NULL) {
        puts("\nNo hay un archivo de libros que cargar.");
        cargadoExitoso = false;
    }

    // Intentamos leer el archivo como una estructura de variables
    if (cargadoExitoso && fread(&estructuraArchivo, sizeof(estructuraArchivo), 1, archivo) != 1) {
        if (feof(archivo)) {
            puts("\n El archivo desde donde se intentaron cargar libros es incompatible.");
        } else {
            printf("\n Ha ocurrido un error al intentar cargar los libros desde archivo: %s.\n", strerror(errno));
        }
        cargadoExitoso = false;
    }

    // Comprobamos que la firma y el tamaño del conjunto de libros sean apropiados
    if (cargadoExitoso && (memcmp("GESBIBLIO1", estructuraArchivo.firma, 10) != 0 || estructuraArchivo.tamanoSet != sizeof(setLibros))) {
        puts("\n El archivo desde donde se intentaron cargar libros no es compatible con esta edición de GesBIBLIO.");
        cargadoExitoso = false;
    }

    // Si hemos cargado con éxito los datos, actualizar el conjunto de libros para que coincida con el del archivo
    if (cargadoExitoso) {
        *variosLibros = estructuraArchivo.libros;
        puts("\nLibros cargados correctamente.");
    }

    // Cerrar el archivo abierto
    fclose(archivo);

    return cargadoExitoso;
}

void cargadoLibros(setLibros *variosLibros) {
    char nombreArchivo[FILENAME_MAX];

    puts("Está cargando libros desde un archivo.");

    leerCadena("\n Introduzca el nombre y la extensión del archivo desde donde cargar libros.\n Deje en blanco para recargar la lista de libros desde la guardada.\n ", nombreArchivo, FILENAME_MAX, true);

    if (strlen(nombreArchivo) == 0) {
        strcpy(nombreArchivo, ARCHIVO_LIBROS);
    }

    // Hemos podido hacer cambios a la lista de libros
    librosGuardados = !cargarLibros(nombreArchivo, variosLibros);
}

/* ------------------------
   Guardar libros a archivo
   ------------------------ */
bool guardarLibros(const char *nombreArchivo, setLibros *variosLibros) {
    FILE *archivo = !librosGuardados ? fopen(nombreArchivo, "wb") : NULL;
    archivoLibros estructuraArchivo;
    bool guardadoExitoso = true;

    // Si no hemos hecho cambios, no molestarse más
    if (librosGuardados) {
        puts("\nLos libros ya están guardados.");
        return true;
    }

    if (archivo == NULL) {
        printf("\n No se pudieron guardar los libros a un archivo: %s.\n", strerror(errno));
        guardadoExitoso = false;
    }

    // Cambiar los campos de la estructura del archivo a guardar
    memcpy(estructuraArchivo.firma, "GESBIBLIO1", 10);
    estructuraArchivo.libros = *variosLibros;
    estructuraArchivo.tamanoSet = sizeof(setLibros);

    // Escribir la estructura al archivo
    if (guardadoExitoso && fwrite(&estructuraArchivo, sizeof(estructuraArchivo), 1, archivo) != 1) {
        printf("\n Ha ocurrido un error al guardar los libros a un archivo: %s.\n", strerror(errno));
    }

    if (guardadoExitoso) {
        puts("\nLos libros han sido guardados correctamente.");
    }

    // Cerrar el archivo abierto
    fclose(archivo);

    // Si hemos tenido éxito guardando libros, reflejarlo
    librosGuardados = guardadoExitoso;

    return guardadoExitoso;
}
