#ifndef AAPTR_H_INCLUDED
#define AAPTR_H_INCLUDED

/// ARRAYS CON PUNTEROS
// Unidimensionales
int *crearVectorEnteros(int tam);
void llenarVectorEnteros(int *ptrVec, int tam);
void mostrarVectorEnteros(int *ptrVec, int tam);
char *asignarMemoriaCadena(int cantLetras);

// Bidimensionales
int **crearMatrizEnteros(int filas, int columnas);
void llenarMatrizEnteros(int **ptrMatriz, int filas, int columnas);
void liberarMemoriaMatrizEnteros(int **ptrMatriz, int filas);

// Strings
char **crearArrayStrings(int cantLineas, int cantLetras);
void mostrarArrayStrings(char **cadenas, int cantLineas);
void liberarMemoriaArrayStrings(char **cadenas, int cantLineas);


/// MANIPULACION DE ARCHIVOS
int contarLineasArchivo(char *nombreArchivo);
void leerArchivoCompleto(char *nombreArchivo);
void agregarLineaAlFinal(char *nombreArchivo, char *nuevaLinea);
void recuperarLineas(char *nombreArchivo, char **cadenas, int cantLetras);
void sobrescribirLinea(
    char *nombreArchivo,
    int cantLetras,
    int nroLineaBuscada,
    char *nuevaLinea
);
void insertarLineaEn(
    char *nombreArchivo,
    int posicionLinea,
    int cantLetras,
    char *nuevaLinea
);
void eliminarUltimaLinea(char *nombreArchivo, int cantLetras);
void eliminarPrimerLinea(char *nombreArchivo, int cantLetras);
void eliminarLinea(char *nombreArchivo, int cantLetras, int nroLinea);

/// EJEMPLOS CON ESTRUCTURAS
// Estructura de ejemplo
typedef struct {
    char nombre[20];
    char apellido[20];
    int nroCamiseta;
    float promedioGoles;
    char club[20];
} Jugador;

void txtAEstructuras(int cantMaxLetras, char *nombreArchivo, Jugador *jugadores);
void estructurasATxt(
    int cantMaxLetras,
    char *nombreArchivo,
    Jugador *jugadores,
    int cantJugadores
);
Jugador llenarEstructura();
void llenarArrayEstructuras(int cantJugadores, Jugador *jugadores);
void mostrarEstructura(Jugador jugador);
void mostrarArrayEstructuras(int cantJugadores, Jugador *jugadores);

/// ALEATORIOS
void eliminarSaltoDeLinea(char *cadena);
void ordenamientoBurbujaAsc(int *v, int tam);
void ordenamientoBurbujaDesc(int *v, int tam);

#endif // AAPTR_H_INCLUDED
