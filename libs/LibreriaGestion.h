#ifndef LIBRERIAGESTION_H_INCLUDED
#define LIBRERIAGESTION_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include "estructuras.h"
#define DIM1 4
#define DIM2 20
#define DIM3 50
#define DIM4 100
///Funciones Extra
void pantallaNegra(int X,int Y,int alturita,int anchito);
void leerCadenaConLimiteTiempoReal(char* cadena, int limite);
///PRINTF
void menuCarga(int X,int Y);
void menuLineas(int X,int Y,int cantidad,int alturadeY);
void cargaVehiculoControl(char* control);
void mostrarArreglo(Vehiculo* unVehiculo, int validos);
int menuModificacion(int posicionDeLaPatenteBuscada,int X,int Y);
void impresionParaModificar(int X,int Y,Vehiculo unVehiculo);
void parteSuperiorInferior(int X,int Y,int where,int yGotoxy,int segundo);
void impresionCUADRO(int X,int Y);
void imprimirTexto1(int X,int Y);
void imprimirUnVehiculo(Vehiculo unVehiculo);
void mostrarTodaLaInformacion(int posicion);
///VALIDACIONES
void convertirAMayusculas(char *cadena);
void removerSaltoDeLinea(char *cadena);
int esNumeroValido(char* str);
int esNumeroFlotanteValido(char* str);
int esLetra(char *str);
int validarTipoDeVehiculo(char *tipoDeVehiculo);
int esNumero(char *str);
int esSoloLetrasNumeros(char *str);
void convertirAMayusculaMinuscula(char *cadena);
///Funciones de BUSQUEDA o de Utilidad
int buscarPosicionDeLaPatente(Patente patenteBuscado);
int verificarPatenteEnArchivoYArreglo(char *letras, char *numeros, Vehiculo *vehiculos, int cantidadVehiculos);
int cantidadDeRegistros(char nombreDeArchivo[]);
int cantidadDisponible();
// Funciones de carga
void cargarLetraPatente(char* letras,int X,int Y); ///Carga Letra de la patente
void cargarNumeroPatente(char *numero,int X,int Y); ///Carga Numero
Patente patenteVehiculo(int X,int Y,int X2,int Y2); ///Devuelve la patente cargada
void marcaVehiculo(char* marca,int X,int Y); ///Carga la marca
void modeloVehiculo(char* modelo,int X,int Y); ///Carga el modelo
void anioVehiculo(int* anioCargar,int X,int Y); ///CARGA EL ANIO
void kmsVehiculo(int* kmsCargado,int X,int Y); ///CARGA LOS KMS
void precioVehiculo(float* precioDiario,int X,int Y); ///CARGA EL PRECIO
void obtenerTipoDeVehiculo(char *tipoDeVehiculo,int X,int Y); ///Carga el tipo
void disponibilidadVehiculo(int* disponibilidad,int X,int Y); ///Carga la disponibilidad
void bajaVehiculo(int* bajaCarga,int X,int Y); ///Carga la baja
Vehiculo cargarUnVehiculo(); ///Retorna el vehiculo cargado
void agregarVehiculo(); ///Carga de vehiculo controlado por el usuario
///Funciones de modificacion
Vehiculo seleccionModificacion(int seleccion, Vehiculo unVehiculo); ///SELECCION
//MODIFICACION Y DEVUELVE LO MODIFICADO
void modificarVehiculo(); ///Control de modificacion por el usuario
///Funciones Listado
void verListadoVehiculos(int numeroDeColor, int inicio, int cantidad); ///Imprime el listado de TODOS
void menuListadoVehiculos(); ///Navegacion del anterior
Vehiculo* obtenerVehiculosDisponibles(int *cantidadDisponibles); ///Obtencion de un arreglo de VEHICULOS
// CON DISPONIBILIDAD 1
void verListadoVehiculosDisponibles(int inicio, int cantidadPagina, int numeroDeColor);///Impresion de solo autos disponibles
void menuListadoVehiculosDisponibles();///Navegacion del anterior
#endif // LIBRERIAGESTION_H_INCLUDED
