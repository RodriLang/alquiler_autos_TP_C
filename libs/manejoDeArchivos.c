#include "manejoDeArchivos.h"

int abrirArchivo(const char *nombreArchivo, const char *modo) {
    FILE *archivo = fopen(nombreArchivo, modo);
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return -1;
    }
    return archivo;
}

int cerrarArchivo(FILE *archivo) {
    if (fclose(archivo) != 0) {
        perror("Error al cerrar el archivo");
        return -1;
    }
    return 0;
}

int leerVehiculo(FILE *archivo, Vehiculo *vehiculo) {
    return fread(vehiculo, sizeof(Vehiculo), 1, archivo);
}

int escribirVehiculo(FILE *archivo, Vehiculo vehiculo) {
    return fwrite(&vehiculo, sizeof(Vehiculo), 1, archivo);
}

int leerPersona(FILE *archivo, Persona *persona) {
    return fread(persona, sizeof(Persona), 1, archivo);
}

int escribirPersona(FILE *archivo, Persona persona) {
    return fwrite(&persona, sizeof(Persona), 1, archivo);
}

int leerAlquiler(FILE *archivo, Alquiler *alquiler) {
    return fread(alquiler, sizeof(Alquiler), 1, archivo);
}

int escribirAlquiler(FILE *archivo, Alquiler alquiler) {
    return fwrite(&alquiler, sizeof(Alquiler), 1, archivo);
}
