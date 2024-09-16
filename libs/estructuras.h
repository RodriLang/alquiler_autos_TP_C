#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED
#define ARCHIVO_ALQUILERES "alquileres.dat"
#define ARCHI_VEHICULOS "ArchivoAutos"
#define ARCHI_CLIENTES "clientes.txt"
#define ARCHI_USUARIOS  "usuarios.dat"

typedef struct {
    char letras[4];
    char numeros[4];
} Patente;

typedef struct {
    Patente patente;
    char marca[20];
    char modelo[20];
    int anio;
    int kms;
    float precioDeAlquilerDiario;
    char tipoVehiculo[20]; // 1-Auto, 2-Camioneta, 3-Utilitario
    int disponibilidad; // 1-disponible, 0-no disponible
    int baja;
} Vehiculo;

typedef struct
{
    int dni;
    char nombre[50];
    char telefono[11];
    char direccion[100];
    int baja; //<--identificar para saber si esa persona sigue activa en la empresa.
} Cliente;

typedef struct
{
    char nombre[50];
    int dni;
    char nickname[20];
    char pass[20];
    int baja;
} Usuario;

typedef struct {
    int dni;
    char nombre[50];
    char telefono[11];
    char direccion[100];
    char rol[20]; // Cliente o User del Sistema
} Persona;

typedef struct {
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct {
    int id;
    Fecha fechaInicio;
    Fecha fechaFin;
    Patente vehiculo;
    int dniCliente;
    float precioTotal;
    int activo;
    int eliminado;
} Alquiler;

typedef struct {
    char texto[20];
    int seleccionado;//indicador de seleccion para resaltar uno entre varios
    int x;//define el inicio (arriba)
    int y;//define el inicio (izquierda)
    int ancho;
    int altura;
    int color;
    int colorSeleccionado;
    void (*funcionApertura)(void*);  // Puntero a función asociada al botón
    void (*funcionCierre)(void*);  // Recibe un puntero void que puede ser casteado al tipo de parametro que se necesite
    int finaliza;//Algunas opciones tendran el poder de finalizar la ejecucion de un ciclo al ser seleccionadas
} OpcionMenu;
#endif // ESTRUCTURAS_H_INCLUDED
