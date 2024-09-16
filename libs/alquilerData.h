#ifndef ALQUILERDATA_H_INCLUDED
#define ALQUILERDATA_H_INCLUDED
#include "estructuras.h"

Alquiler generarAlquiler(int dniCliente, Fecha fechaInicio, Fecha fechaFin, Patente patente);
int registrarAlquiler(Alquiler alquiler);
void AlquileresPorVehiculo(Patente patente, Alquiler *alquileres);
Alquiler buscarAlquiler(Fecha fechaInicio, Patente patente);
Alquiler buscarAlquilerPorId(int id);
int modificarAlquiler(Alquiler alquiler);
int posicionAlquilerPorId(int idAlquiler);
int finalizarAlquiler(Alquiler alquiler);
int reactivarAlquiler(Alquiler alquiler);
int eliminarAlquiler(Alquiler alquiler);
int restaurarAlquiler(Alquiler alquiler);
int cantidadDeAlquileresActivos(int estado);
int cantidadDeAlquileresEliminados();
int* listarDniConAlquileresActivos(int *cantidad);
Alquiler* listarAlquileresActivos(int *cantidadAlquileres);
Alquiler* listarAlquileres(int *cantidadAlquileres, int estado);
Alquiler* listarAlquileres(int *cantidadAlquileres, int dni);
Patente* listarPatentesConAlquileresActivos(int *cantidadPatentes);
/// VEHICULOS ///
Vehiculo obtenerVehiculPorPatente(Patente patente, char *nombreArchivo);
int modificarDisponibilidadVehiculo(Patente patente, int disponible);
float obtenerPrecioVehiculo(Patente patente, char *nombreArchivo, float *precio);
void ordenarAlquilerRecursividad(Alquiler *alquileres, int cantidadAlquiler, int inicio, int sentido, char orden);

/// PERSONAS ///
Cliente buscarClienteDni (int dni);
int existeDniCliente(int dni);
int validarNicknameUsuario(char nick[], Usuario *usuario);
int existeNicknameUsuario(char nick[]);
int existeDniUsuario(int dni);
int guardarUsuario(Usuario usuario);

#endif // ALQUILERDATA_H_INCLUDED
