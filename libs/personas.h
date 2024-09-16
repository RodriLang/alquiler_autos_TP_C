#ifndef PERSONAS_H_INCLUDED
#define PERSONAS_H_INCLUDED
#include "estructuras.h"
#include "interfazUsuario.h"
#include "utilidades.h"

/** ================================================== PROTOTIPADOS ========================================================*/
void mostrarCliente(Cliente cliente, int y);
void cargarArchivoClienteMenu();
void modificarRegistroClienteMenu();
void modificarCliente (int modificado);
void mostrarRegistrosClientesMenu();
Cliente* obtenerClientesDesdeArchivo(int* cantidadClientes);
int cantidadClientes();
void verListadoClientes(int inicio, int cantidadPagina, int numeroDeColor);
void menuListadoClientes();
void parteSuperiorInferiorAgregarCli(int X,int Y,int where,int yGotoxy,int segundo);
void parteSuperiorInferiorCli(int X,int Y,int where,int yGotoxy,int segundo);
void alternarEstadoClientePorDni();
void subMenuAdmnistracionClientes();
void cargarArregloAdministracionClientes(OpcionMenu arregloMenu[]);
int dniYaExiste(int dni);

///Funciones Usuario:
Usuario cargaUsuario();
void ArchivoUsuario (char nombreArchivo[]);
void modificarRegistroUsuario (char nombreArchivo[], Usuario usuario);
void mostrarUsuario(Usuario usuario);
Cliente buscarUsuarioPorDNI (char nombreArchivo[], Usuario usuario);

#endif // PERSONAS_H_INCLUDED
