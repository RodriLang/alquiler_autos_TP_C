#ifndef REPORTESESTADISTICAS_H_INCLUDED
#define REPORTESESTADISTICAS_H_INCLUDED
#include "estructuras.h"
#include "interfazUsuario.h"
///AUTOS NUEVOS
Vehiculo* obtenerVehiculosNuevos(int *cantidadDisponibles);
void verListadoVehiculosNuevos(int inicio, int cantidadPagina, int numeroDeColor,int *cantidad);
void menuListadoVehiculosNuevos();

void solicitarAnioMes(int *anio, int *mes);
float calculaIngresoMes(char archivoAlquileres[], int anio, int mes);
void mostrarIngresoMes();
void muestraUnAlquiler(Alquiler alq);
Alquiler obtenerAlquilerMayorIngreso(char archivoAlquileres[], Alquiler a);
void mostrarAlquilerMayor();
void solicitarDniCliente(int *dni);
void buscarAlquileresCliente(char archivoAlquileres[], Alquiler alq, int dni);
void mostrarAlquilerPorCliente();


#endif // REPORTESESTADISTICAS_H_INCLUDED
