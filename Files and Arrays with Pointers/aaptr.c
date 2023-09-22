#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "aaptr.h"

/// ARRAYS CON PUNTEROS

// Unidimensionales
int *crearVectorEnteros(int tam) {
    int *ptr = (int *) malloc(tam * sizeof(int));
    return ptr;
}

void llenarVectorEnteros(int *ptrVec, int tam) {
    for(int i=0; i<tam; i++) {
        ptrVec[i] = 10+rand()%90;
    }
}

void mostrarVectorEnteros(int *ptrVec, int tam) {
    for(int i=0; i<tam; i++) {
        printf("[%d]", ptrVec[i]);
    }
    printf("\n");
}

char *asignarMemoriaCadena(int cantLetras) {
    char *cadena = (char *) malloc(cantLetras * sizeof(char));
    return cadena;
}

// Bidimensionales
int **crearMatrizEnteros(int filas, int columnas) {
    int **matriz = (int **) malloc(filas * sizeof(int *));

    for (int i=0; i<filas; i++) {
        matriz[i] = (int *) malloc(columnas * sizeof(int));
    }
    return matriz;
}

void llenarMatrizEnteros(int **ptrMatriz, int filas, int columnas) {
    for(int f=0; f<filas; f++) {
        for(int c=0; c<columnas; c++) {
            ptrMatriz[f][c] = 10+(rand()%90);
        }
    }
}

void mostrarMatrizEnteros(int **ptrMatriz, int filas, int columnas) {
    for(int f=0; f<filas; f++) {
        for(int c=0; c<columnas; c++) {
            printf("[%d]", ptrMatriz[f][c]);
        }
        printf("\n");
    }
}

void liberarMemoriaMatrizEnteros(int **ptrMatriz, int filas) {
    for(int f=0; f<filas; f++) {
        free(ptrMatriz[f]);
    }

    free(ptrMatriz);
}

// Strings
char **crearArrayStrings(int cantLineas, int cantLetras) {
    char **arrayStrings = (char **) malloc(cantLineas * sizeof(char *));

    for(int i=0; i<cantLineas; i++) {
        arrayStrings[i] = (char *) malloc(cantLetras * sizeof(char));
    }
    return arrayStrings;
}

void mostrarArrayStrings(char **cadenas, int cantLineas) {
    for(int i=0; i<cantLineas; i++) {
        printf("%s\n", cadenas[i]);
    }
}

void liberarMemoriaArrayStrings(char **cadenas, int cantLineas){
    for(int i=0; i<cantLineas; i++) {
        free(cadenas[i]);
    }

    free(cadenas);
}


/// MANIPULACION DE ARCHIVOS

void leerArchivoCompleto(char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");

    if(archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    char caracter;

    while(!feof(archivo)) {
        caracter = fgetc(archivo);
        printf("%c", caracter);
    }

    fclose(archivo);
}

void agregarLineaAlFinal(char *nombreArchivo, char *nuevaLinea) {
    FILE *archivo = fopen(nombreArchivo, "a");

    if(archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    fprintf(archivo, "\n%s", nuevaLinea);
    fclose(archivo);
}

void recuperarLineas(char *nombreArchivo, char **cadenas, int cantLetras) {
    FILE *archivo = fopen(nombreArchivo, "r");

    if(archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    int i = 0;
    while(fgets(cadenas[i], cantLetras, archivo)) {
        i++;
    }

    fclose(archivo);
}

void sobrescribirLinea(
    char *nombreArchivo,
    int cantLetras,
    int nroLineaBuscada,
    char *nuevaLinea
) {
    FILE *archivo = fopen(nombreArchivo, "r");

    if(archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    int cantLineas = contarLineasArchivo(nombreArchivo);
    char **cadenas = crearArrayStrings(cantLineas, cantLetras);

    if(nroLineaBuscada <= 0 || nroLineaBuscada > cantLineas) {
        liberarMemoriaArrayStrings(cadenas, cantLineas);
        printf("No existe la linea indicada.\n");
        printf("No se pudo modificar el archivo.\n");
        fclose(archivo);
        exit(1);
    }

    int i = 0;
    while(fgets(cadenas[i], cantLetras, archivo)) {
        if(nroLineaBuscada-1 == i) {
            strcpy(cadenas[i], nuevaLinea);
        }
        i++;
    }

    fclose(archivo);

    archivo = fopen(nombreArchivo, "w");

    for(int j=0; j<cantLineas; j++) {
        if(j != nroLineaBuscada-1) {
            fprintf(archivo, "%s", cadenas[j]);
        } else {
            fprintf(archivo, "%s\n", cadenas[j]);
        }
    }

    liberarMemoriaArrayStrings(cadenas, cantLineas);
    fclose(archivo);
}

int contarLineasArchivo(char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");

    if(archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    char caracter;
    int i = 1;
    while(!feof(archivo)) {
        caracter = fgetc(archivo);
        if(caracter == '\n') {
            i++;
        }
    }

    fclose(archivo);

    return i;
}

void insertarLineaEn(
    char *nombreArchivo,
    int posicionLinea,
    int cantLetras,
    char *nuevaLinea
) {
    FILE *archivo = fopen(nombreArchivo, "r");

    if(archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    int cantLineas = contarLineasArchivo(nombreArchivo);
    char **cadenas = crearArrayStrings(cantLineas+1, cantLetras);

    if(posicionLinea <= 0 || posicionLinea > cantLineas) {
        liberarMemoriaArrayStrings(cadenas, cantLineas+1);
        printf("No existe la linea indicada.\n");
        printf("No se pudo modificar el archivo.\n");
        fclose(archivo);
        exit(1);
    }

    int i = 0;
    while(fgets(cadenas[i], cantLetras, archivo)) {
        if(posicionLinea-1 == i) {
            strcpy(cadenas[i+1], cadenas[i]);
            strcpy(cadenas[i], nuevaLinea);
            i++;
        }
        i++;
    }

    fclose(archivo);

    archivo = fopen(nombreArchivo, "w");

    for(int j=0; j<cantLineas+1; j++) {
        if(j != posicionLinea-1) {
            fprintf(archivo, "%s", cadenas[j]);
        } else {
            fprintf(archivo, "%s\n", cadenas[j]);
        }
    }

    liberarMemoriaArrayStrings(cadenas, cantLineas+1);
    fclose(archivo);

}

void eliminarUltimaLinea(char *nombreArchivo, int cantLetras) {

    int cantLineas = contarLineasArchivo(nombreArchivo);
    char **lineas = crearArrayStrings(cantLineas, 50);
    recuperarLineas(nombreArchivo, lineas, 50);

    char **nuevasLineas = crearArrayStrings(cantLineas-1, 50);

    for(int i=0; i<cantLineas-1; i++) {
        eliminarSaltoDeLinea(lineas[i]);
        strcpy(nuevasLineas[i], lineas[i]);
    }

    FILE *archivo = fopen(nombreArchivo, "w");

    if(archivo == NULL) {
        liberarMemoriaArrayStrings(lineas, cantLineas);
        liberarMemoriaArrayStrings(nuevasLineas, cantLineas-1);
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    for(int i=0; i<cantLineas-1; i++) {
        if(i != cantLineas-2) {
            fprintf(archivo, "%s\n", nuevasLineas[i]);
        } else {
            fprintf(archivo, "%s", nuevasLineas[i]);
        }
    }

    liberarMemoriaArrayStrings(lineas, cantLineas);
    liberarMemoriaArrayStrings(nuevasLineas, cantLineas-1);

    fclose(archivo);

}

void eliminarPrimerLinea(char *nombreArchivo, int cantLetras) {

    int cantLineas = contarLineasArchivo(nombreArchivo);
    char **lineas = crearArrayStrings(cantLineas, 50);
    recuperarLineas(nombreArchivo, lineas, 50);

    char **nuevasLineas = crearArrayStrings(cantLineas-1, 50);

    for(int i=1, j=0; i<cantLineas; i++, j++) {
        eliminarSaltoDeLinea(lineas[i]);
        strcpy(nuevasLineas[j], lineas[i]);
    }

    FILE *archivo = fopen(nombreArchivo, "w");

    if(archivo == NULL) {
        liberarMemoriaArrayStrings(lineas, cantLineas);
        liberarMemoriaArrayStrings(nuevasLineas, cantLineas-1);
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    for(int i=0; i<cantLineas-1; i++) {
        if(i != cantLineas-2) {
            fprintf(archivo, "%s\n", nuevasLineas[i]);
        } else {
            fprintf(archivo, "%s", nuevasLineas[i]);
        }
    }

    liberarMemoriaArrayStrings(lineas, cantLineas);
    liberarMemoriaArrayStrings(nuevasLineas, cantLineas-1);

    fclose(archivo);

}

void eliminarLinea(char *nombreArchivo, int cantLetras, int nroLinea) {

    int cantLineas = contarLineasArchivo(nombreArchivo);
    char **lineas = crearArrayStrings(cantLineas, 50);
    recuperarLineas(nombreArchivo, lineas, 50);

    char **nuevasLineas = crearArrayStrings(cantLineas-1, 50);

    int j = 0;
    for(int i=0; i<cantLineas; i++) {
        if(nroLinea-1 != i) {
            eliminarSaltoDeLinea(lineas[i]);
            strcpy(nuevasLineas[j], lineas[i]);
            j++;
        }
    }

    FILE *archivo = fopen(nombreArchivo, "w");

    if(archivo == NULL) {
        liberarMemoriaArrayStrings(lineas, cantLineas);
        liberarMemoriaArrayStrings(nuevasLineas, cantLineas-1);
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    for(int i=0; i<cantLineas-1; i++) {
        if(i != cantLineas-2) {
            fprintf(archivo, "%s\n", nuevasLineas[i]);
        } else {
            fprintf(archivo, "%s", nuevasLineas[i]);
        }
    }

    liberarMemoriaArrayStrings(lineas, cantLineas);
    liberarMemoriaArrayStrings(nuevasLineas, cantLineas-1);

    fclose(archivo);

}

/// EJEMPLOS CON ESTRUCTURAS

void txtAEstructuras(int cantMaxLetras, char *nombreArchivo, Jugador *jugadores) {

    char *linea = asignarMemoriaCadena(cantMaxLetras);
    char *fragmento = asignarMemoriaCadena(cantMaxLetras/3);

    FILE *archivo = fopen(nombreArchivo, "r");

    if(archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    int contLineas = 0;

    while(fgets(linea, cantMaxLetras, archivo)) {
        eliminarSaltoDeLinea(linea);
        fragmento = strtok(linea, ";");
        int contFragmentos = 0;

        while(fragmento != NULL) {
            // printf("Fragmento: %s\n", fragmento); Generico

            switch(contFragmentos) {
                case 0:
                    strcpy(jugadores[contLineas].nombre, fragmento);
                    break;
                case 1:
                    strcpy(jugadores[contLineas].apellido, fragmento);
                    break;
                case 2:
                    jugadores[contLineas].nroCamiseta = atoi(fragmento);
                    break;
                case 3:
                    jugadores[contLineas].promedioGoles = atof(fragmento);
                    break;
                case 4:
                    strcpy(jugadores[contLineas].club, fragmento);
                    break;
                default:
                    printf("Fragmento invalido.\n");
                    break;
            }
            fragmento = strtok(NULL, ";");
            contFragmentos++;
        }
        contLineas++;
    }
    fclose(archivo);

    free(linea);
    free(fragmento);
}

void estructurasATxt(
    int cantMaxLetras,
    char *nombreArchivo,
    Jugador *jugadores,
    int cantJugadores
) {
    FILE *archivo = fopen(nombreArchivo, "w");

    if(archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    for(int i=0; i<cantJugadores; i++) {
        if(i != cantJugadores-1) {
            fprintf(
                archivo,
                "%s;%s;%d;%.2f;%s\n",
                jugadores[i].nombre,
                jugadores[i].apellido,
                jugadores[i].nroCamiseta,
                jugadores[i].promedioGoles,
                jugadores[i].club
            );
        } else {
            fprintf(
                archivo,
                "%s;%s;%d;%.2f;%s",
                jugadores[i].nombre,
                jugadores[i].apellido,
                jugadores[i].nroCamiseta,
                jugadores[i].promedioGoles,
                jugadores[i].club
            );
        }
    }
}

Jugador llenarEstructura() {
    Jugador jugador;

    strcpy(jugador.nombre, "Rodrigo");
    strcpy(jugador.apellido, "Obando");
    strcpy(jugador.club, "NN");
    jugador.nroCamiseta = 5;
    jugador.promedioGoles = 10.5;

    return jugador;
}

void llenarArrayEstructuras(int cantJugadores, Jugador *jugadores) {
    for(int i=0; i<cantJugadores; i++) {
        jugadores[i] = llenarEstructura();
    }
}

void mostrarEstructura(Jugador jugador) {
    printf("Nombre: %s\n", jugador.nombre);
    printf("Apellido: %s\n", jugador.apellido);
    printf("Nro camiseta: %d\n", jugador.nroCamiseta);
    printf("Promedio de goles: %.2f\n", jugador.promedioGoles);
    printf("Club: %s\n\n", jugador.club);
}

void mostrarArrayEstructuras(int cantJugadores, Jugador *jugadores) {
    for(int i=0; i<cantJugadores; i++) {
        mostrarEstructura(jugadores[i]);
    }
}

/// ALEATORIOS

void eliminarSaltoDeLinea(char *cadena) {
    int longitud = strlen(cadena);
    if(longitud > 0 && cadena[longitud - 1] == '\n') {
        cadena[longitud - 1] = '\0'; // Reemplaza el salto de línea con el carácter nulo
    }
}

void ordenamientoBurbujaAsc(int *v, int tam){
    int aux;
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam-1; j++){
            if(v[j] > v[j+1]){
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }
}

void ordenamientoBurbujaDesc(int *v, int tam) {
    int aux;
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam-1; j++){
            if(v[j] < v[j+1]){
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }
}


