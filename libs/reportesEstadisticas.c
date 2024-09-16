#include "reportesEstadisticas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#include "gotoxy.h"

#define ESC 27
#define DIM 100

/// AUTOS NUEVOS
Vehiculo* obtenerVehiculosNuevos(int *cantidadDisponibles)
{
    int cantidad = cantidadDeRegistros("ArchivoAutos");
    int indice=0;
    if (cantidad > 0)
    {
        Vehiculo *vehiculosDisponibles = (Vehiculo *)malloc(cantidad * sizeof(Vehiculo));
        FILE *archi = fopen("ArchivoAutos", "rb");
        if (archi != NULL)
        {
            while(fread(&vehiculosDisponibles[*cantidadDisponibles], sizeof(Vehiculo), 1, archi)>0)
            {
                if(vehiculosDisponibles[*cantidadDisponibles].anio>=2019)
                {
                    (*cantidadDisponibles)++;
                }
            }
            fclose(archi);
            vehiculosDisponibles = (Vehiculo*)realloc(vehiculosDisponibles, *cantidadDisponibles * sizeof(Vehiculo));
            return vehiculosDisponibles;
        }
        else
        {
            printf("El Archivo no se Abrio Correctamente.\n");
            *cantidadDisponibles = 0;
            return NULL;
        }
    }
    else
    {
        printf("No hay vehículos registrados.\n");
        *cantidadDisponibles = 0;
        return NULL;
    }
}






void verListadoVehiculosNuevos(int inicio, int cantidadPagina, int numeroDeColor,int *cantidad) {
    int yGotoxy = 0;
    int cantidadDisponible = 0;
    Vehiculo *vehiculos = obtenerVehiculosNuevos(&cantidadDisponible);
    *cantidad=cantidadDisponible;
    int X = 37, Y = 10;
    if (cantidadDisponible > 0) {
        parteSuperiorInferior(X, Y, 1, 0, 0);
        for (int i = 0; i < cantidadPagina && (inicio + i) < cantidadDisponible; i++) {
            if (inicio + i == numeroDeColor) {
                gotoxy(X, (Y + 4) + i);
                yGotoxy = i;
                color(176);
                printf("| %-15s | %-20s | %s %s | %-10s | %-7d |\n",
                       vehiculos[inicio + i].marca,
                       vehiculos[inicio + i].modelo,
                       vehiculos[inicio + i].patente.letras,
                       vehiculos[inicio + i].patente.numeros,
                       vehiculos[inicio + i].tipoVehiculo,
                       vehiculos[inicio + i].anio);
               color(11);
            } else {
                color(11);
                gotoxy(X, (Y + 4) + i);
                yGotoxy = i;
                printf("| %-15s | %-20s | %s %s | %-10s | %-7d |\n",
                       vehiculos[inicio + i].marca,
                       vehiculos[inicio + i].modelo,
                       vehiculos[inicio + i].patente.letras,
                       vehiculos[inicio + i].patente.numeros,
                       vehiculos[inicio + i].tipoVehiculo,
                       vehiculos[inicio + i].anio);
            }
        }
        parteSuperiorInferior(X, Y, 0, yGotoxy, 0);
        free(vehiculos);
    } else {
        printf("No hay vehículos registrados.\n");
    }
}

void menuListadoVehiculosNuevos() {
    int enEjecucion = 1, posicionY = 10, posicionX = 38, colorInteractivo = 0, cantidad = 0;
    int inicio = 0;
    int cantidadPagina = 4;///Número de vehículos a mostrar por página
    char teclaPresionada;
    pantallaNegra(37, 10, 11, 74);
    while (enEjecucion) {
        verListadoVehiculosNuevos(inicio,cantidadPagina, colorInteractivo,&cantidad);
        gotoxy(posicionX + 1, posicionY);
        teclaPresionada = getch();
        gotoxy(posicionX - 1, posicionY);
        printf("  ");
        switch (teclaPresionada) {
            case 80: // ABAJO
                if (colorInteractivo < cantidad - 1) {
                    colorInteractivo++;
                    if (colorInteractivo >= inicio + cantidadPagina) {
                        inicio++;
                    }
                }
                break;
            case 72: // ARRIBA
                if (colorInteractivo > 0) {
                    colorInteractivo--;
                    if (colorInteractivo < inicio) {
                        inicio--;
                    }
                }
                break;
            case 27: // Esc para salir
                enEjecucion = 0;
                borrarContenido();
                gotoxy(0, posicionY + cantidad + 1);
                break;
        }
    }
}
/// Estadisticas
void solicitarAnioMes(int *anio, int *mes)
{
    char input[5];
    int index = 0;
    char ch;

    pintarRecuadro(33, 7, 48, 8, COLOR_BTN_LAT);

    // Solicitar año
    while (1)
    {
        gotoxy(35, 8);
        printf("Ingrese el anio a buscar (2014 a 2024): ");
        index = 0;

        while (1)
        {
            ch = getch();

            if (ch == 13)
            {
                if (index == 4)
                {
                    input[index] = '\0';
                    break;
                }
            }
            else if (ch == 8)
            {
                if (index > 0)
                {
                    index--;
                    printf("\b \b");
                }
            }
            else if (isdigit(ch) && index < 4)
            {
                input[index++] = ch;
                printf("%c", ch);
            }
        }

        *anio = atoi(input);

        if (*anio >= 2014 && *anio <= 2024)
        {
            break;
        }
        else
        {
            gotoxy(35, 8);
            printf("Ingrese el anio a buscar (2014 a 2024):     ");
        }
    }

    // Solicitar mes
    while (1)
    {
        gotoxy(35, 9);
        printf("Ingrese el mes a buscar (1 a 12): ");
        index = 0;
        while (1)
        {
            ch = getch();

            if (ch == 13)
            {
                if (index > 0 && index <= 2)
                {
                    input[index] = '\0';
                    break;
                }
            }
            else if (ch == 8)
            {
                if (index > 0)
                {
                    index--;
                    printf("\b \b");
                }
            }
            else if (isdigit(ch) && index < 2)
            {
                input[index++] = ch;
                printf("%c", ch);
            }
        }

        *mes = atoi(input);

        if (*mes >= 1 && *mes <= 12)
        {
            break;
        }
        else
        {
            gotoxy(35, 9);
            printf("Ingrese el mes a buscar (1 a 12):     ");
        }
    }
}

float calculaIngresoMes(char archivoAlquileres[], int anio, int mes)
{
    Alquiler a;
    float ingresoMensual = 0;

    FILE *archi = fopen(archivoAlquileres, "rb");

    if (archi)
    {
        while (fread(&a, sizeof(Alquiler), 1, archi) > 0)
        {
            if (a.fechaInicio.anio == anio && a.fechaInicio.mes == mes && !a.activo && !a.eliminado)
            {
                ingresoMensual += a.precioTotal;
            }
        }
        fclose(archi);
    }
    return ingresoMensual;
}

void mostrarIngresoMes()
{
    int anio = 0;
    int mes = 0;
    float ingresoMes = 0;

    solicitarAnioMes(&anio, &mes);
    ingresoMes = calculaIngresoMes(ARCHIVO_ALQUILERES, anio, mes);

    gotoxy(35, 11);
    printf("============================================\n");
    gotoxy(35, 12);
    printf("Ingreso en el mes %i/%i: AR$ %.2f\n\n", mes, anio, ingresoMes);
    gotoxy(35, 13);
    printf("============================================\n\n");

    char tecla='a';

    while(tecla!=27)
    {
        tecla=getch();
    }
    borrarSeccion(30, 6, ANCHO-30, ALTURA-6);
}

void muestraUnAlquiler(Alquiler alq)
{
    gotoxy(50, 12);
    printf("=====================================");
    gotoxy(50, 13);
    printf("        Detalles de Alquiler\n");
    gotoxy(50, 14);
    printf("=====================================\n");
    gotoxy(50, 15);
    printf("Fecha de Inicio:        %i/%i/%i\n", alq.fechaInicio.dia, alq.fechaInicio.mes, alq.fechaInicio.anio);
    gotoxy(50, 16);
    printf("Fecha de Finalizacion:  %i/%i/%i\n", alq.fechaInicio.dia, alq.fechaInicio.mes, alq.fechaInicio.anio);
    gotoxy(50, 17);
    printf("Patente:                %s %s\n", alq.vehiculo.letras, alq.vehiculo.numeros);
    gotoxy(50, 18);
    printf("DNI del cliente:        %i\n", alq.dniCliente);
    gotoxy(50, 19);
    printf("Precio Final:           AR$ %.2f\n", alq.precioTotal);
    gotoxy(50, 20);
    printf("=====================================\n");
}

Alquiler obtenerAlquilerMayorIngreso(char archivoAlquileres[], Alquiler a)
{
    Alquiler alquilerMayor;
    float mayorIngreso = 0;

    FILE *archi = fopen(archivoAlquileres, "rb");

    if (archi)
    {
        while (fread(&a, sizeof(Alquiler), 1, archi))
        {
            if (a.precioTotal > mayorIngreso&&!a.eliminado&&!a.activo)
            {
                mayorIngreso = a.precioTotal;
                alquilerMayor = a;
            }
        }
        fclose(archi);
    }
    return alquilerMayor;
}

void mostrarAlquilerMayor()
{
    Alquiler alq = obtenerAlquilerMayorIngreso(ARCHIVO_ALQUILERES, alq);

    pintarRecuadro(48, 9, 41, 13, COLOR_BTN_LAT);
    gotoxy(56, 10);
    printf("Alquiler con mayor ingreso\n");
    muestraUnAlquiler(alq);

    char tecla = 0;

    while(tecla!=27)
    {
        tecla=getch();
    }
    borrarSeccion(30, 6, ANCHO-30, ALTURA-6);
}

void solicitarDniCliente(int *dni)
{
    char input[9];
    int index = 0;
    char ch;

    pintarRecuadro(31, 6, 76, 3, COLOR_BTN_LAT);

    gotoxy(33, 7);
    printf("Ingrese el DNI del cliente a buscar: ");

    while (1)
    {
        ch = getch();

        if (ch == 13)
        {
            if (index > 0)
            {
                input[index] = '\0';
                break;
            }
        }
        else if (ch == 8)
        {
            if (index > 0)
            {
                index--;
                printf("\b \b");
            }
        }
        else if (isdigit(ch) && index < 8)
        {
            input[index++] = ch;
            printf("%c", ch);
        }
    }
    *dni = atoi(input);

    if (*dni < 10000000 || *dni >= 100000000)
    {
        gotoxy(33, 7);
        solicitarDniCliente(dni);
    }
}

void buscarAlquileresCliente(char archivoAlquileres[], Alquiler alq, int dni)
{
    FILE *archi = fopen(archivoAlquileres, "rb");

    int y = 12;

    if (archi)
    {
        cabeceraAlquileres(31, 10);
        color(COLOR_BTN_LAT);

        while (fread(&alq, sizeof(Alquiler), 1, archi) > 0)
        {
            if (alq.dniCliente == dni)
            {
                mostrarAlquiler(alq, 31, y);
                y++;
            }
        }
        fclose(archi);
    }
    else
    {
        gotoxy(31, 8);
        printf("No se pudo abrir el archivo %s\n", archivoAlquileres);
    }
}

void mostrarAlquilerPorCliente()
{
    int dni = 0;
    char continuar = 0;
    Alquiler alq;

    solicitarDniCliente(&dni);
    buscarAlquileresCliente(ARCHIVO_ALQUILERES, alq, dni);

    char tecla = 0;

    while(tecla!=27)
    {
        tecla=getch();
    }
    borrarSeccion(30, 6, ANCHO-30, ALTURA-6);
}
