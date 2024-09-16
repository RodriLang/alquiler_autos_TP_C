#ifndef INTERFAZUSUARIO_H_INCLUDED
#define INTERFAZUSUARIO_H_INCLUDED
#include "estructuras.h"
#include "utilidades.h"
#include "reportesEstadisticas.h"
#include "LibreriaGestion.h"
#include "interfazAlquiler.h"
#include <windows.h>
#include <string.h>
#include "gotoxy.h"
#include "personas.h"
#define ANCHO 120
#define ALTURA 30                               //
#define X_PANEL 29                               //
#define Y_PANEL 5                               //
#define COLOR_BASE 176
#define COLOR_ESCRITURA 112
#define COLOR_RESALTADO 151
#define COLOR_DESABILITADO 184
#define COLOR_DESABIL_BLANCO 120
#define COLOR_BTN_LAT 11
#define COLOR_BTN_SUP 139
#define COLOR_BTN_SELEC_LAT 240
#define COLOR_BTN_SELEC_SUP 11
#define COLOR_ERROR 180
#define COLOR_ERROR_BLANCO 116
#define COLOR_VALIDO_BLANCO 122
#define COLOR_AZUL 27
#define COLOR_VERDE 43
#define COLOR_ROJO 75


void definirVentana();
void desactivarMaximizar(HWND consolaWindows);
void centrarVentana(HWND consolaWindows);
void dimensionarVentana(HWND consolaWindows);
void cargarArregloMenu(OpcionMenu arregloMenu[]);
OpcionMenu crearOpcionMenu(char texto[], int x, int y, int selec, int color, int colorSelec, int ancho, int altura, void (*f1)(), void (*f2)(), int fin);
void pintarOpcionMenu(OpcionMenu elemento);
void pintarMenu(OpcionMenu arregloMenu[], int cantidadMenu);
void subMenuAlquiler();
void subMenuVehiculos();
void subMenuReportes();
void borrarSeccion(int x, int y, int ancho, int altura);
void borrarMenu();
void subMenuPersonas();
void cargarListaAlquileres(int activo);
void mostrarAlquiler(Alquiler alq, int x, int y);
void imprimirDatosAlquiler(int x, int y);
void subMenuVehiculosLista();
void ingresarDatosNuevoAlquiler();
void menuVertical(OpcionMenu arregloBotones[], int cantMenu, void* arg, void* arg2);
void confirmarEliminarAlquiler(Alquiler alquiler);
void login();
void validarLogin(Usuario usuario);
void registrarUsuario();
void actualizarDatosLogin(int xCentro, int yUser, int yPass, char user[], char pass[], int claveOculta);
void actualizarDatosRegistro(int xCentro, int yNombre, int yPass2, int yDni, char nombre[], char pass2[], char dni[], int claveOculta);
Fecha obtenerFechaActual();
#endif // INTERFAZUSUARIO_H_INCLUDED
