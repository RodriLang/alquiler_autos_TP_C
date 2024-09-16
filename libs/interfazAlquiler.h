#ifndef INTERFAZALQUILER_H_INCLUDED
#define INTERFAZALQUILER_H_INCLUDED

#include "estructuras.h"
#include "interfazUsuario.h"
#include "validaciones.h"
#include "utilidades.h"
#include "alquilerData.h"

void menuModificar();
void mostrarAlquiler(Alquiler alqui, int x, int y);
void mostrarListaAlquileres(Alquiler alquileres[], int cantidadAlq, int seleccionado, int x, int y, int sentido, char orden);
void cargarListaAlquileresActivos();
void cargarListaAlquileresFinalizados();
void cargarListaAlquileresEliminados();
void recorrerListaAlquileres(Alquiler *alquileres, int cantidadAlq, int x, int y, OpcionMenu *botones, int cantBotones, void*funcion());
void cabeceraAlquileres(int x, int y);
void mostrarListaVehiculosAlquiler(Vehiculo vehiculos[], int cantidadVehi, int seleccionado, int x, int y);
void mostrarVehiculoAlquiler(Vehiculo vehiculo, int x, int y);
void mostrarListaPatentes(Vehiculo vehiculo, int x, int y);
char* recorrerListaVehiculosAlquiler(int cantidadVehi, Vehiculo vehiculos[], int x, int y);
void cabeceraVehiculosAlquiler(int x, int y);
void ingresarDatosNuevoAlquiler();
void ingresarDatosAlquilerExistente(Alquiler alq);
void imprimirDatosAlquiler(int x, int y);
void recorrerDatosAlquiler(int x, int y, void*arg);
void actualizarDatos(char fechaIn[], int *indFechaIn, char fechaOut[], int *indFechaOut, char dni[], char pat[], OpcionMenu btn, float valorAlq, Alquiler *alq);
void borrarCaracterFecha(char stringFecha[], int *indice);
float calcularValorAlquiler(Patente patente, Fecha fechaInicio, Fecha fechaFin, float *valorTotal);
int verificarAlquiler(int dniCliente, Fecha fechaInicio, Fecha fechaFin, Patente patente);
int verificarCamposModificadosAlquiler(int dniCliente, Fecha fechaInicio, Fecha fechaFin, Patente patente, Alquiler *alq);
void seleccionarAlquilerModificar(int id);
void mostrarDatosOriginales(int x, int y, Alquiler alquiler);
void menuModificacionAlquiler(Alquiler *alquiler);
int mensajeConfirmacion(char *mensaje);
void confirmarEliminar(Alquiler alquiler);
void confirmarReactivar(Alquiler alquiler);
void confirmarFinalizar(Alquiler alquiler);
void confirmarRestaurar(Alquiler alquiler);
void modificarFechaInicio(Alquiler alquiler);///////
void modificarFechaIn(Alquiler alquiler);

//////////////////////////////////////////////
///PERSONAS
int confirmarRegistrarUsuario(Usuario usuario);
int guardarUsuario(Usuario usuario);
#endif // INTERFAZALQUILER_H_INCLUDED
