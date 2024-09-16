#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED
#include "estructuras.h"
#include <time.h>

int obtenerAnioActual();
Fecha stringToFecha(char fechaString[]);
int compararFecha(Fecha fecha1, Fecha fecha2);
int compararPatente(Patente p1, Patente p2);
int posicionCentral(char texto[], int ancho);
char* fechaToString(Fecha f);
void informarError(int x, int y, char * texto, int colorTexto);
Patente stringToPatente(char *patenteString);
int dniStringToInt(char *dniString);
int diasEntreFechas(Fecha fechaAnt, Fecha fechaPos);
void agregarMayusculas(char nombre[]);
#endif // UTILIDADES_H_INCLUDED
