
#ifndef MANEJODEARCHIVOS_H_INCLUDED
#define MANEJODEARCHIVOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"

int abrirArchivo(const char *nombreArchivo, const char *modo);
int cerrarArchivo(FILE *archivo);
int leerVehiculo(FILE *archivo, Vehiculo *vehiculo);
int escribirVehiculo(FILE *archivo, Vehiculo vehiculo);
int leerPersona(FILE *archivo, Persona *persona);
int escribirPersona(FILE *archivo, Persona persona);
int leerAlquiler(FILE *archivo, Alquiler *alquiler);
int escribirAlquiler(FILE *archivo, Alquiler alquiler);

#endif // MANEJODEARCHIVOS_H_INCLUDED
