#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "personas.h"
/// ================================================== FUNCIONES PARA USUARIOS ============================================================== ///
Usuario cargaUsuario()
{
    Usuario usuario;
    char apellido[20];

    printf("Ingrese el nombre:\n");
    scanf("%s", &usuario.nombre);

    printf("Ingrese el apellido:\n");
    fflush(stdin);
    scanf("%s", &apellido);

    usuario.nombre[0]=toupper(usuario.nombre[0]);
    apellido[0]=toupper(apellido[0]);

    strcat(usuario.nombre, " ");
    strcat(usuario.nombre, apellido);

    printf ("Nro de DNI: \n");
    fflush(stdin);
    scanf ("%i", &usuario.dni);

    printf ("Ingresar nickname: \n");
    fflush(stdin);
    scanf ("%s", &usuario.nickname);

    printf ("Ingrese su password: \n");
    fflush(stdin);
    scanf ("%s", &usuario.pass);

    printf ("Usuario: Activo(1) Baja(0)\n");
    fflush(stdin);
    scanf ("%i", &usuario.baja);

    return usuario;
}

void ArchivoUsuario (char nombreArchivo[])
{
    FILE *usu = fopen (nombreArchivo, "ab");

    if (usu)
    {
        Usuario usuario = cargaUsuario();

        fwrite (&usuario, sizeof(Usuario), 1, usu);

        fclose (usu);
    }
}

void modificarRegistroUsuario (char nombreArchivo[], Usuario usuario)
{
    FILE *archi = fopen (nombreArchivo, "ab");
    Usuario nuevo = cargaUsuario();
    int modificado = 0;

    if (archi)
    {
        while (fread(&usuario, sizeof(Usuario), 1, archi)>0 && modificado == 0)
        {
            if (nuevo.dni == usuario.dni)
            {
                fseek(archi, sizeof(Usuario)*(-1), SEEK_CUR);
                modificado = 1;
                fwrite(&nuevo, sizeof(Usuario), 1, archi);
            }

        }
        fclose(archi);

    }
}

Cliente buscarUsuarioPorDNI (char nombreArchivo[], Usuario usuario)
{
    FILE *archi = fopen (nombreArchivo, "r+b");
    int encontrado = 0;

    Usuario aux;

    printf ("Nro de DNI: \n");
    scanf ("%i", &aux.dni);

    if (archi)
    {
        while (fread(&usuario, sizeof(Usuario), 1, archi)>0 && encontrado == 0)
        {
            if (aux.dni == usuario.dni)
            {
                fseek(archi, sizeof(Usuario)*(-1), SEEK_CUR);
                mostrarUsuario(usuario);
                encontrado = 1;

            }
        }
        fclose(archi);
    }
}

void mostrarRegistrosUsuarios (char nombreArchivo[], Usuario usuario)
{

    FILE *archi = fopen (nombreArchivo, "rb");

    if (archi)
    {
        while (fread(&usuario, sizeof(Usuario), 1, archi)>0)
        {
            mostrarUsuario(usuario);
        }
        fclose(archi);
    }
    else
    {
        printf ("\nERROR, no se pudo abrir el archivo.\n");
    }
}

void mostrarUsuario(Usuario usuario)
{
    int x = 40;
    int y = 10;

    gotoxy(x, y);
    printf("_____________________________________\n");
    gotoxy(x, y + 1);
    printf("DNI: %i\n", usuario.dni);
    gotoxy(x, y + 2);
    printf("Nombre y apellido: %s\n", usuario.nombre);
    gotoxy(x, y + 3);
    printf("Nickname: %s\n", usuario.nickname);
    gotoxy(x, y + 4);
    printf("Password: %s\n", usuario.pass);
    gotoxy(x, y + 5);
    printf("Actividad: %i\n", usuario.baja);
    gotoxy(x, y + 6);
    printf("_____________________________________\n");
}

/// ================================================== FUNCIONES PARA CLIENTES ============================================================== ///

Cliente cargaCliente()
{
    int x = 60;
    int y = 10;
    pantallaNegra(55, 10, 8, 40);
    Cliente cliente;
    char apellido[20];
    char dniStr[9];
    char telefonoStr[20];
    char numCalle[10];

    gotoxy(x, y + 1);
    printf("Nro de DNI: ");
    fflush(stdin);
    leerCadenaConLimiteTiempoReal(dniStr, 8);

    // Validación del DNI
    while (!validarDni(dniStr) || dniYaExiste(atoi(dniStr)))
    {
        gotoxy(x + 11, y + 1);
        printf("                 ");
        gotoxy(x, y + 1);
        printf("Nro de DNI: ");
        fflush(stdin);
        leerCadenaConLimiteTiempoReal(dniStr, 8);
    }
    cliente.dni = atoi(dniStr);

    // Validación del nombre
    gotoxy(x, y + 2);
    printf("Ingrese el nombre: ");
    fflush(stdin);
    leerCadenaConLimiteTiempoReal(cliente.nombre, 15);
    while (!validarStringLetras(cliente.nombre))
    {
        gotoxy(x + 16, y + 2);
        printf("                    ");
        gotoxy(x, y + 2);
        printf("Ingrese el nombre: ");
        fflush(stdin);
        leerCadenaConLimiteTiempoReal(cliente.nombre, 15);
    }

    gotoxy(x, y + 3);
    printf("Ingrese el apellido: ");
    fflush(stdin);
    leerCadenaConLimiteTiempoReal(apellido, 15);
    while (!validarStringLetras(apellido))
    {
        gotoxy(x + 18, y + 3);
        printf("                    ");
        gotoxy(x, y + 3);
        printf("Ingrese el apellido: ");
        fflush(stdin);
        leerCadenaConLimiteTiempoReal(apellido, 15);
    }

    cliente.nombre[0] = toupper(cliente.nombre[0]);
    apellido[0] = toupper(apellido[0]);
    strcat(cliente.nombre, " ");
    strcat(cliente.nombre, apellido);

    gotoxy(x, y + 4);
    printf("Numero telefonico: ");
    fflush(stdin);
    leerCadenaConLimiteTiempoReal(telefonoStr, 10);
    while (!validarTelefono(telefonoStr))
    {
        gotoxy(x + 18, y + 4);
        printf("             ");
        gotoxy(x, y + 4);
        printf("Numero telefonico: ");
        fflush(stdin);
        leerCadenaConLimiteTiempoReal(telefonoStr, 10);
    }
    strcpy(cliente.telefono, telefonoStr);

    gotoxy(x, y + 5);
    printf("Calle: ");
    fflush(stdin);
    leerCadenaConLimiteTiempoReal(cliente.direccion, 9);
    while (!validarStringLetras(cliente.direccion))
    {
        gotoxy(x + 7, y + 5);
        printf("                    ");
        gotoxy(x, y + 5);
        printf("Calle: ");
        fflush(stdin);
        leerCadenaConLimiteTiempoReal(cliente.direccion, 9);
    }

    gotoxy(x, y + 6);
    printf("Altura: ");
    fflush(stdin);
    leerCadenaConLimiteTiempoReal(numCalle, 5);
    while (!validarStringNumerico(numCalle))
    {
        gotoxy(x + 7, y + 6);
        printf("        ");
        gotoxy(x, y + 6);
        printf("Altura: ");
        fflush(stdin);
        leerCadenaConLimiteTiempoReal(numCalle, 5);
    }

    cliente.direccion[0] = toupper(cliente.direccion[0]);
    strcat(cliente.direccion, " ");
    strcat(cliente.direccion, numCalle);

    gotoxy(x, y + 7);
    cliente.baja = 1;

    return cliente;
}

void mostrarCliente(Cliente cliente, int y)
{
    int x = 40;
    gotoxy(x, y);
    printf("_____________________________________\n");
    gotoxy(x, y + 1);
    printf("DNI: %i\n", cliente.dni);
    gotoxy(x, y + 2);
    printf("Nombre y apellido: %s\n", cliente.nombre);
    gotoxy(x, y + 3);
    printf("Numero telefonico: %s\n", cliente.telefono);
    gotoxy(x, y + 4);
    printf("Direccion: %s\n", cliente.direccion);
    gotoxy(x, y + 5);
    printf("Actividad: %i\n", cliente.baja);
    gotoxy(x, y + 6);
    printf("_____________________________________\n");

}

///FUNCIONES AUXILIARES(MODULARIZADAS) PARA EL FUNCIONAMIENTO DEL MENU

void escribirClienteEnArchivo(FILE *cli, Cliente cliente)
{
    if (cli == NULL)
    {
        int x = 40;
        int y = 25;
        gotoxy(x, y);
        printf("Error: Archivo no abierto para escritura.");
        return;
    }

    fwrite(&cliente, sizeof(Cliente), 1, cli);
}

void modificarCliente(int modificado)
{
    int x = 10;
    int y = 25;

    if (modificado != 0)
    {
        gotoxy(x, y);
        pantallaNegra(45, 10, 10, 56);
        informacionEmergente("El cliente ha sido actualizado correctamente.\n");
    }
    else
    {
        gotoxy(x, y);
        pantallaNegra(45, 10, 10, 56);
        informacionEmergente("El cliente tiene un alquiler activo o no existe");
        //printf("No se ha encontrado el cliente.\n");
    }
}

void mostrarRegistrosClientesMenu()
{
    int x = 40;
    int y = 6;
    Cliente cliente;
    FILE *archi = fopen(ARCHI_CLIENTES, "rb");

    if (archi != NULL)
    {
        int cantidad = obtenerCantidad(archi);
        fseek(archi, 0, SEEK_SET);

        while(fread(&cliente, sizeof(Cliente), 1, archi)>0)
        {
            mostrarCliente(cliente, y);
            y+=7;
        }

        fclose(archi);

    }
    else
    {
        gotoxy(x,y);
        informacionEmergente("El Archivo no se Abrió Correctamente.\n");
    }
}

Cliente* obtenerClientesDesdeArchivo(int* cantidadClientes)
{
    FILE *archivo;
    Cliente* clientes = NULL;
    int cantidad = 0;

    archivo = fopen(ARCHI_CLIENTES, "rb");
    if (archivo == NULL)
    {
        informacionEmergente("Error al abrir el archivo de clientes.\n");
        return NULL;
    }

    fseek(archivo, 0, SEEK_END);
    cantidad = ftell(archivo) / sizeof(Cliente);
    rewind(archivo);

    clientes = (Cliente*)malloc(cantidad * sizeof(Cliente));
    if (clientes == NULL)
    {
        informacionEmergente("Error de memoria al reservar espacio para los clientes.\n");
        return NULL;
    }

    // Lee los clientes del archivo y los guarda en el arreglo
    fread(clientes, sizeof(Cliente), cantidad, archivo);


    fclose(archivo);

    // Actualiza la cantidad de clientes y devuelve el arreglo
    *cantidadClientes = cantidad;
    return clientes;
}
///FUNCION CON FORMATO PARA EL MENU
void cargarArchivoClienteMenu()
{
    int x = 40;
    int y = 25;
    FILE *cli = fopen(ARCHI_CLIENTES, "ab");

    if (cli == NULL)
    {
        gotoxy(x, y);
        informacionEmergente("Error al abrir el archivo.");
        return;
    }

    Cliente cliente = cargaCliente();

    if (cliente.dni != 0)
    {
        escribirClienteEnArchivo(cli, cliente);
        gotoxy(x, y);
        pantallaNegra(37, 10, 10, 72);
        informacionEmergente("Cliente agregado correctamente al archivo.\n");
    }
    else
    {
        gotoxy(x, y);
        pantallaNegra(37, 10, 10, 72);
        informacionEmergente("Error al cargar el cliente. No se agregó al archivo.\n");
    }

    fclose(cli);
}

void modificarRegistroClienteMenu()
{
    pantallaNegra(45, 10, 10, 56);
    int x = 55;
    int y = 10;
    char dniStr[10];
    int modificado = 0;
    Cliente cliente;

    FILE *archi = fopen(ARCHI_CLIENTES, "r+b");

    if (archi != NULL)
    {
        gotoxy(x, y);
        printf("DNI del cliente a modificar: ");
        fflush(stdin);
        leerCadenaConLimiteTiempoReal(dniStr, 8);
        // Validación del DNI
        while (!validarDni(dniStr))
        {
            gotoxy(x, y);
            printf("                                               ");
            gotoxy(x, y);
            informacionEmergente("asegurese de escribir correctamente el DNI");
            pantallaNegra(45, 10, 10, 56);
            gotoxy(x, y);
            printf("DNI del cliente a modificar: ");
            fflush(stdin);
            scanf("%s", dniStr);
            leerCadenaConLimiteTiempoReal(dniStr, 8);
        }

        int cantidad;
        int* dniAlquileresActivos = listarDniConAlquileresActivos(&cantidad);
        int dniCliente = dniStringToInt(dniStr);
        int alquilando = 0;

        // Verificar si el cliente tiene un alquiler activo
        for (int i = 0; i < cantidad; i++)
        {
            if (dniAlquileresActivos[i] == dniCliente)
            {
                alquilando = 1;
                break;
            }
        }
        free(dniAlquileresActivos);

        if (alquilando)
        {
            //gotoxy(x, y + 1);
            //printf("El cliente con DNI %s tiene un alquiler activo. No se puede modificar.\n", dniStr);
        }
        else
        {
            while (fread(&cliente, sizeof(Cliente), 1, archi) > 0 && !modificado)
            {
                if (cliente.dni == dniCliente)
                {
                    Cliente nuevo = cargaCliente();
                    fseek(archi, -1 * sizeof(Cliente), SEEK_CUR);
                    fwrite(&nuevo, sizeof(Cliente), 1, archi);
                    modificado = 1;
                }
            }
        }
        fclose(archi);
    }
    else
    {
        gotoxy(x, y);
        informacionEmergente("Error al abrir el archivo de clientes.\n");
        pantallaNegra(45, 10, 10, 56);
    }

    modificarCliente(modificado);
}

void verListadoClientes(int inicio, int cantidadPagina, int numeroDeColor)
{
    int yGotoxy = 0;
    int cantidadClientes = 0;
    Cliente *clientes = obtenerClientesDesdeArchivo(&cantidadClientes);
    int X = 37, Y = 10;
    if (cantidadClientes > 0)
    {
        parteSuperiorInferiorCli(X, Y-1, 1, 0, 0);

        for (int i = 0; i < cantidadPagina && inicio + i < cantidadClientes; i++)
        {
            if (inicio + i == numeroDeColor)
            {
                gotoxy(X, (Y + 3) + i);
                yGotoxy = i;
                color(176);
                printf("| %-9d | %-17s | %-10s | %-14s | %-9d |\n",
                       clientes[inicio + i].dni,
                       clientes[inicio + i].nombre,
                       clientes[inicio + i].telefono,
                       clientes[inicio + i].direccion,
                       clientes[inicio + i].baja);
                color(11);
            }
            else
            {
                color(11);
                gotoxy(X, (Y + 3) + i);
                yGotoxy = i;
                printf("| %-9d | %-17s | %-10s | %-14s | %-9d |\n",
                       clientes[inicio + i].dni,
                       clientes[inicio + i].nombre,
                       clientes[inicio + i].telefono,
                       clientes[inicio + i].direccion,
                       clientes[inicio + i].baja);
            }
        }
        parteSuperiorInferior(X, Y-1, 0, yGotoxy, 0);
        free(clientes);
    }
    else
    {
        gotoxy(40, 20);
        informacionEmergente("No hay clientes registrados.\n");
    }
}
void menuListadoClientes()
{
    int enEjecucion = 1, posicionY = 10, posicionX = 38, colorInteractivo = 0, cantidad = cantidadClientes(); // Función para obtener cantidad de clientes disponibles a implementar
    int inicio = 0;
    int cantidadPagina = 4;  // Número de clientes a mostrar por página
    char teclaPresionada;
    pantallaNegra(37, 9, 11, 74);
    while (enEjecucion)
    {
        verListadoClientes(inicio, cantidadPagina, colorInteractivo); // Llamada a la función actualizada para mostrar clientes
        gotoxy(posicionX + 1, posicionY);
        teclaPresionada = getch();
        gotoxy(posicionX - 1, posicionY);
        printf("  ");
        switch (teclaPresionada)
        {
        case 80: // ABAJO
            if (colorInteractivo < cantidad - 1)
            {
                colorInteractivo++;
                if (colorInteractivo >= inicio + cantidadPagina)
                {
                    inicio++;
                }
            }
            break;
        case 72: // ARRIBA
            if (colorInteractivo > 0)
            {
                colorInteractivo--;
                if (colorInteractivo < inicio)
                {
                    inicio--;
                }
            }
            break;
        case 27: // Esc para salir
            enEjecucion = 0;
            borrarSeccion(37, 9, 75, 7 + cantidad);
            gotoxy(0, posicionY + cantidad + 1);
            break;
        }
    }
}

///INTERFAZ
void parteSuperiorInferiorCli(int X,int Y,int where,int yGotoxy,int segundo)
{
    if(where==1)
    {
        gotoxy(X+25,Y);
        color(11);
        printf("Listado de Clientes:\n");
        gotoxy(X,Y+2);
        printf("| %-9s | %-15s | %-10s | %-14s | %-7s |\n", "DNI", "NOMBRE Y APELLIDO", "TELEFONO", "DIRECCION", "ACTIVIDAD");
        for(int i=0; i<75; i++)
        {
            gotoxy(X+i,Y+1);
            printf("%c",196);
            gotoxy(X+i,Y+3);
            printf("%c",196);
        }
    }
    else if(where==0 && segundo!=2)
    {
        gotoxy(X+1,Y+5+yGotoxy+1);
        printf("Para Salir Presione ESC.");
        for(int i=0; i<75; i++)
        {
            gotoxy(X+i,Y+4+yGotoxy+1);
            printf("%c",196);
            gotoxy(X+i,Y+6+yGotoxy+1);
            printf("%c",196);
        }
    }
    else if(where==0 && segundo == 2)
    {
        for(int i=0; i<75; i++)
        {
            gotoxy(X+i,Y+4+yGotoxy+1);
            printf("%c",196);
            gotoxy(X+i,Y+6+yGotoxy+1);
            printf("%c",196);
        }
        gotoxy(X+1,Y+5+yGotoxy+1);
        system("pause");
    }
}

void alternarEstadoClientePorDni()
{
    pantallaNegra(45, 10, 10, 56);
    int x = 45;
    int y = 10;
    char dniStr[10];

    FILE *archi = fopen(ARCHI_CLIENTES, "r+b");
    if (archi == NULL)
    {
        gotoxy(x, y);
        informacionEmergente("Error al abrir el archivo");
        pantallaNegra(45, 10, 10, 56);
        return;
    }
    gotoxy(x, y);
    printf("DNI del cliente a modificar: ");
    fflush(stdin);
    leerCadenaConLimiteTiempoReal(dniStr, 8);
    // Validación del DNI
    while (!validarDni(dniStr))
    {
        gotoxy(x, y);
        printf("                                               ");
        gotoxy(x - 3, y + 14);
        informacionEmergente("asegurese de escribir correctamente el DNI");
        pantallaNegra(45, 10, 10, 56);
        gotoxy(x, y);
        printf("DNI del cliente a dar de baja/activar: ");
        fflush(stdin);
        scanf("%s", dniStr);
        leerCadenaConLimiteTiempoReal(dniStr, 8);
    }
    int cantidad;
    int* dniAlquileresActivos = listarDniConAlquileresActivos(&cantidad);
    int dniCliente = dniStringToInt(dniStr);
    int alquilando = 0;

    // Verificar si el cliente tiene un alquiler activo
    for (int i = 0; i < cantidad; i++)
    {
        if (dniAlquileresActivos[i] == dniCliente)
        {
            alquilando = 1;
            break;
        }
    }
    free(dniAlquileresActivos); // Liberar la memoria

    if (alquilando)
    {
        gotoxy(x, y + 1);
        informacionEmergente("El cliente tiene un alquiler activo.");
        pantallaNegra(45, 10, 10, 56);
        fclose(archi);
        return;
    }

    Cliente cliente;
    int encontrado = 0;

    while (fread(&cliente, sizeof(Cliente), 1, archi))
    {
        if (cliente.dni == dniCliente)
        {
            cliente.baja = cliente.baja == 0 ? 1 : 0; // Alternar estado
            fseek(archi, -sizeof(Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(Cliente), 1, archi);
            encontrado = 1;
            break;
        }
    }

    if (encontrado)
    {
        if (cliente.baja == 0)
        {
            gotoxy(x, y);
            informacionEmergente("El cliente ha sido dado de baja.", dniCliente);
        }
        else
        {
            gotoxy(x, y);
            informacionEmergente("El cliente ha sido activado.", dniCliente);
        }
    }
    else
    {
        gotoxy(x, y);
        informacionEmergente("Cliente no encontrado.", dniCliente);
    }

    fclose(archi);
}

///FUNCION PARA MENU DESPLEGABLE
void subMenuAdmnistracionClientes()
{
    color(3);
    int cantMenu=2;
    OpcionMenu menuAdmPersonas[cantMenu];
    cargarArregloAdministracionClientes(menuAdmPersonas);
    borrarContenido();
    menuAdmPersonas[0].seleccionado=1;
    gotoxy(menuAdmPersonas[0].x, menuAdmPersonas[0].y);
    pintarMenu(menuAdmPersonas, cantMenu);
    menuHorizontal(menuAdmPersonas, cantMenu);
}

///FUNCION DE VERIFICACION PARA PERSONAS
int dniYaExiste(int dni)
{
    FILE *archivo = fopen(ARCHI_CLIENTES, "rb");
    if (archivo == NULL)
    {
        // Si el archivo no se puede abrir, asumimos que el DNI no existe
        return 0;
    }

    Cliente cliente;
    while (fread(&cliente, sizeof(Cliente), 1, archivo) == 1)
    {
        if (cliente.dni == dni)
        {
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}

int obtenerCantidad(FILE *archi)
{
    int cantidad = 0;

    fseek(archi, 0, SEEK_END);
    long fileSize = ftell(archi);
    rewind(archi);

    cantidad = fileSize / sizeof(Cliente);

    return cantidad;
}

int cantidadClientes()
{
    FILE *archivo;
    Cliente cliente;
    int cantidad = 0;


    archivo = fopen(ARCHI_CLIENTES, "rb");
    if (archivo == NULL)

    {
        informacionEmergente("Error al abrir el archivo de clientes");
        return;
    }
    while (fread(&cliente, sizeof(Cliente), 1, archivo) == 1)
    {
        cantidad++;
    }
    fclose(archivo);
    return cantidad;
}
