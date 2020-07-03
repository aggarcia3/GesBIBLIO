/* ----------------------------------------------------------
   GesBIBLIO - Programa para gesti�n de biblioteca particular
   ---------------------------------------------------------- */
/*                  Hern�ndez Crespo, Pedro
                    G�mez Rodr�guez, Daniel
                   Gonz�lez Garc�a, Alejandro                 */

#include "headers.h"
#include "libro.h"

/* ---------------
   Configuraciones
   --------------- */
//#define LIBROS_PREDETERMINADOS             // No definir para empezar sin libros
#define REGION "spanish"                     // Juego de caracteres a usar

bool librosGuardados = true;

unsigned short menu();

int main() {
    unsigned short opcion;
    setLibros variosLibros = {0};

    #ifdef _WIN32
        // Cambiar el t�tulo de la ventana
        system("TITLE GesBIBLIO");
    #endif // _WIN32

    // Utilizar juego de caracteres especificado
    setlocale(LC_ALL, REGION);

    // Obtener datos de la regi�n
    region = localeconv();

    // Si hay libros predeterminados, a�adirlos
    #ifdef LIBROS_PREDETERMINADOS
        strcpy(variosLibros.Libros[0].ISBN, "9788425349751");
        strcpy(variosLibros.Libros[0].titulo, "Irene");
        strcpy(variosLibros.Libros[0].autoria, "Pierre Lemaitre");
        strcpy(variosLibros.Libros[0].editorial, "Grijalbo");
        strcpy(variosLibros.Libros[0].formato, "papel");
        variosLibros.Libros[0].precio = 23.6;
        variosLibros.Libros[0].fecha.dia = 15;
        variosLibros.Libros[0].fecha.mes = 4;
        variosLibros.Libros[0].fecha.anho = 2013;


        strcpy(variosLibros.Libros[1].ISBN, "9788401016950");
        strcpy(variosLibros.Libros[1].titulo, "Historia de un canalla");
        strcpy(variosLibros.Libros[1].autoria, "Julia Navarro");
        strcpy(variosLibros.Libros[1].editorial, "Plaza & Janes");
        strcpy(variosLibros.Libros[1].formato, "electr�nico");
        variosLibros.Libros[1].precio = 12.34;
        variosLibros.Libros[1].fecha.dia = 10;
        variosLibros.Libros[1].fecha.mes = 2;
        variosLibros.Libros[1].fecha.anho = 2016;

        strcpy(variosLibros.Libros[2].ISBN, " 9788490265475");
        strcpy(variosLibros.Libros[2].titulo, "Alex");
        strcpy(variosLibros.Libros[2].autoria, "Pierre Lemaitre");
        strcpy(variosLibros.Libros[2].editorial, "Bromera");
        strcpy(variosLibros.Libros[2].formato, "papel");
        variosLibros.Libros[2].precio = 39.85;
        variosLibros.Libros[2].fecha.dia = 16;
        variosLibros.Libros[2].fecha.mes = 8;
        variosLibros.Libros[2].fecha.anho = 2015;

        strcpy(variosLibros.Libros[3].ISBN, "9788433998200");
        strcpy(variosLibros.Libros[3].titulo, "Chicos y chicas");
        strcpy(variosLibros.Libros[3].autoria, "Soledad Puertolas");
        strcpy(variosLibros.Libros[3].editorial, "Anagrama");
        strcpy(variosLibros.Libros[3].formato, "electr�nico");
        variosLibros.Libros[3].precio = 9.49;
        variosLibros.Libros[3].fecha.dia = 5;
        variosLibros.Libros[3].fecha.mes = 10;
        variosLibros.Libros[3].fecha.anho = 2016;

        strcpy(variosLibros.Libros[4].ISBN, "9788483103937");
        strcpy(variosLibros.Libros[4].titulo, "Profundidades");
        strcpy(variosLibros.Libros[4].autoria, "Henning Mankell");
        strcpy(variosLibros.Libros[4].editorial, "Tusquets");
        strcpy(variosLibros.Libros[4].formato, "papel");
        variosLibros.Libros[4].precio = 52.23;
        variosLibros.Libros[4].fecha.dia = 1;
        variosLibros.Libros[4].fecha.mes = 5;
        variosLibros.Libros[4].fecha.anho = 2009;

        variosLibros.numLibros = 5;
    #endif // LIBROS_PREDETERMINADOS

    // Cargar los libros que podamos haber guardado
    puts("Cargando libros...");
    if (!cargarLibros(ARCHIVO_LIBROS, &variosLibros)) {
        #ifdef LIBROS_PREDETERMINADOS
            puts("Los libros se han restablecido a los predeterminados.");
        #endif // LIBROS_PREDETERMINADOS
    }

    do {
        #ifdef _WIN32
            // Cambiar color de fondo a azul y color de texto a blanco
            system("COLOR 17");
        #endif // _WIN32

        // Mostrar el men� y pedir la opci�n
        opcion = menu();

        #ifdef _WIN32
            // Borrar la pantalla
            system("CLS");
        #endif // _WIN32

        switch (opcion) {
            case 1:
                #ifdef _WIN32
                    system("COLOR 37");
                #endif // _WIN32
                listarLibros(&variosLibros);
                break;
            case 2:
                #ifdef _WIN32
                    system("COLOR 27");
                #endif // _WIN32
                insertarLibro(&variosLibros);
                break;
            case 3:
                #ifdef _WIN32
                    system("COLOR 47");
                #endif // _WIN32
                borrarLibro(&variosLibros);
                break;
            case 4:
                #ifdef _WIN32
                    system("COLOR 57");
                #endif // _WIN32
                busquedaLibroISBN(&variosLibros);
                break;
            case 5:
                #ifdef _WIN32
                    system("COLOR 57");
                #endif // _WIN32
                busquedaLibroTitulo(&variosLibros);
                break;
            case 6:
                #ifdef _WIN32
                    system("COLOR 57");
                #endif // _WIN32
                busquedaLibrosAutor(&variosLibros);
                break;
            case 7:
                #ifdef _WIN32
                    system("COLOR 67");
                #endif // _WIN32
                modificarLibro(&variosLibros);
                break;
            case 8:
                #ifdef _WIN32
                    system("COLOR 70");
                #endif // _WIN32
                cargadoLibros(&variosLibros);
                break;
            case 9:
                #ifdef _WIN32
                    system("COLOR 70");
                #endif // _WIN32
                puts("Est� guardando los libros.");
                guardarLibros(ARCHIVO_LIBROS, &variosLibros);
                break;
            default:
                if (!librosGuardados && leerRespuesta("\nHa hecho modificaciones a los libros. �Desea guardar los cambios? (S/N) ")) {
                    if (!guardarLibros(ARCHIVO_LIBROS, &variosLibros)) {
                        fputs("\nPresione Entrar para salir.", stdout);

                        // Esperar a que se pulse Entrar
                        limpiarStdin();
                    }
                }
                break;
        }

        // Si la opci�n es v�lida y no la salida, esperar a que el usuario presione una tecla para continuar
        if (opcion != 0 && opcion != 10) {
            fputs("\nPresione Entrar para volver al men� principal.", stdout);

            // Esperar a que se pulse Entrar
            limpiarStdin();
        }

        // Borrar de nuevo la pantalla
        #ifdef _WIN32
            system("CLS");
        #endif // _WIN32

    } while (opcion != 10);

    return 0;
}

// Funci�n para preguntarle al usuario qu� operaci�n desea realizar
unsigned short menu() {
    short opcion;

    puts("\n######################################################");
    puts("\n             -- Bienvenido a GesBIBLIO --");
    puts(  "           Su sistema gestor de biblioteca");
    puts("\n######################################################");
    puts("\n�Qu� quiere hacer?");
    puts("\t  1. Listar libros");
    puts("\t  2. Insertar libro");
    puts("\t  3. Eliminar libro");
    puts("\t  4. Buscar libro por ISBN");
    puts("\t  5. Buscar libro por t�tulo");
    puts("\t  6. Buscar libros por autor/a");
    puts("\t  7. Modificar datos de un libro");
    puts("\t  8. Cargar libros");
    puts("\t  9. Guardar libros");
    puts("\t 10. Salir");
    puts("\n######################################################");
    opcion = leerEntero("\nOpci�n: ", true);

    while (opcion < 0 || opcion > 10) {
        opcion = leerEntero("\n La opci�n introducida no es v�lida. Introduzca otra: ", true);
    }

    return opcion;
}
