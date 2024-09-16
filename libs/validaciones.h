#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED
#include "estructuras.h"

int validarStringNumerico(char string[]);
int validarStringLetras(char string[]);
int validarDni(char dni[]);
int validarTelefono(char telefono[]);
int validarNombre(char nombre[]);
int esBisiesto(int anio);
int validarFecha(Fecha f);
int validarFormatoFecha(char fecha[]);
#endif
