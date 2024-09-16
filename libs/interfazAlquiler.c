#include "interfazAlquiler.h"
#include "interfazUsuario.h"


///Muestra todos los datos de un alquiler
void mostrarAlquiler(Alquiler alqui, int x, int y)
{
    gotoxy(x,y);
    printf("                                                                      ");
    gotoxy(x+1,y);
    printf("%.4d", alqui.id);
    gotoxy(x+8,y);
    printf("%s", fechaToString(alqui.fechaInicio));
    gotoxy(x+23,y);
    printf("%s", fechaToString(alqui.fechaFin));
    gotoxy(x+41,y);
    printf("%s %s", alqui.vehiculo.letras, alqui.vehiculo.numeros);//patenteToString(alqui.vehiculo)
    gotoxy(x+55,y);
    printf("%i", alqui.dniCliente);
    gotoxy(x+70,y);
    printf("           ");
    gotoxy(x+70,y);
    printf("$%.2f", alqui.precioTotal);
}

void cargarListaAlquileresActivos()
{
    int cantidad=0;
    Alquiler *arregloAlquilerDinamico;
    int cantBotones=4;
    OpcionMenu botones[cantBotones];
    char opciones[][15]= {"MODIFICAR", "FINALIZAR", "ELIMINAR ", "CANCELAR "};
    int colores[]= {COLOR_VERDE, COLOR_ROJO, COLOR_ROJO, COLOR_AZUL};

    cargarArregloBotones(botones,opciones, colores, cantBotones);
    botones[0].funcionApertura=ingresarDatosAlquilerExistente;
    botones[1].funcionApertura=confirmarFinalizar;
    botones[2].funcionApertura=confirmarEliminar;

    arregloAlquilerDinamico=listarAlquileres(&cantidad, 1);
    recorrerListaAlquileres(arregloAlquilerDinamico, cantidad, 31, 8, botones, cantBotones, cargarListaAlquileresActivos);
}

void cargarListaAlquileresFinalizados()
{
    int cantidad=0;
    Alquiler *arregloAlquilerDinamico;
    int cantBotones=3;
    OpcionMenu botones[cantBotones];
    char opciones[][15]= {"   REACTIVAR  ","   ELIMINAR   ","   CANCELAR   "};
    int colores[]= {COLOR_VERDE, COLOR_ROJO, COLOR_AZUL};
    cargarArregloBotones(botones,opciones, colores, cantBotones);
    botones[0].funcionApertura=confirmarReactivar;
    botones[1].funcionApertura=confirmarEliminar;

    arregloAlquilerDinamico=listarAlquileres(&cantidad, 0);
    recorrerListaAlquileres(arregloAlquilerDinamico, cantidad, 31, 8, botones, cantBotones, cargarListaAlquileresFinalizados);
}

void cargarListaAlquileresPorPersona(int dni)
{
    int cantidad=0;
    Alquiler *arregloAlquilerDinamico;
    int cantBotones=3;
    OpcionMenu botones[cantBotones];
    char opciones[][15]= {"   REACTIVAR  ","   ELIMINAR   ","   CANCELAR   "};
    int colores[]= {COLOR_VERDE, COLOR_ROJO, COLOR_AZUL};
    cargarArregloBotones(botones,opciones, colores, cantBotones);
    botones[0].funcionApertura=confirmarReactivar;
    botones[1].funcionApertura=confirmarEliminar;

    arregloAlquilerDinamico=listarAlquileres(&cantidad, 0);
    recorrerListaAlquileres(arregloAlquilerDinamico, cantidad, 31, 8, botones, cantBotones, cargarListaAlquileresFinalizados);
}

void cargarListaAlquileresEliminados()
{
    int cantidad=0;
    Alquiler *arregloAlquilerDinamico;
    int cantBotones=2;
    OpcionMenu botones[cantBotones];
    char opciones[][15]= {"   RESTAURAR  ","   CANCELAR   "};
    int colores[]= {COLOR_AZUL, COLOR_AZUL};
    cargarArregloBotones(botones,opciones, colores, cantBotones);
    botones[0].funcionApertura=confirmarRestaurar;


    arregloAlquilerDinamico=listarAlquileresEliminados(&cantidad);
    recorrerListaAlquileres(arregloAlquilerDinamico, cantidad, 31, 8, botones, cantBotones, cargarListaAlquileresEliminados);
}

void informacionEmergente(char mensaje[])
{
    int cantBotones=1;
    OpcionMenu botones[cantBotones];
    char opciones[][15]= {"    ACEPTAR   "};
    int colores[]= {COLOR_VERDE};
    cargarArregloBotones(botones,opciones, colores, cantBotones);
    int ancho=27;
    int alto=8;
    int x=(ANCHO-X_PANEL)+X_PANEL-ancho/2;
    int y=13;
    menuOpcionesEmergentes(mensaje, botones, cantBotones, NULL, NULL);
    borrarContenido();
}


///Muestra el arreglo de alquileres llamando a mostrarAlquiler por cada uno, los ordena segun parametros y resalta el indice seleccionado
void mostrarListaAlquileres(Alquiler alquileres[], int cantidadAlq, int seleccionado, int x, int y, int sentido, char orden)
{
    ordenarAlquilerRecursividad(alquileres, cantidadAlq, 0, sentido, orden);
    int cantMostrar=15;
    int inicio=0;

    if(cantidadAlq<cantMostrar)
    {
        cantMostrar=cantidadAlq;
    }
    if(seleccionado>=cantMostrar)
    {
        inicio=seleccionado+1-cantMostrar;
    }

    for(int i=0; i<cantMostrar; i++)
    {
        if(i+inicio==seleccionado)
        {
            color(COLOR_RESALTADO);
        }
        else
        {
            if(!alquileres[0].eliminado)
            {

                color(COLOR_BASE);
            }
            else
            {
                color(COLOR_DESABILITADO);
            }
        }
        mostrarAlquiler(alquileres[i+inicio], x, y+2+i);
    }
}

///Recorrer de forma grafica la lista mostrada
void recorrerListaAlquileres(Alquiler *alquileres, int cantidadAlq, int x, int y, OpcionMenu botones[], int cantBotones, void*funcion())
{
    int cantMenu=5;
    hidecursor(0);

    int enEjecucion=1;
    int posicionY=y;
    char teclaPresionada;
    int sentido=-1;
    char orden = 'F';

    while(enEjecucion)
    {
        imprimirOpcionesOrdenamiento();
        cabeceraAlquileres(x,y);
        mostrarListaAlquileres(alquileres, cantidadAlq, posicionY-y, x, y, sentido, orden);
        gotoxy(x,posicionY);
        teclaPresionada=getch();
        teclaPresionada=toupper(teclaPresionada);
        switch(teclaPresionada)
        {
        case 80:///ABAJO
            if(posicionY<cantidadAlq+y-1)
            {
                posicionY++;
            }
            break;
        case 72:///ARRIBA
            if(posicionY>y)
            {
                posicionY--;
            }
            break;
        case 13:///ENTER
            if(cantidadAlq>0)
            {
                menuOpcionesEmergentes("OPCIONES", botones, cantBotones, alquileres[posicionY-y], NULL);
                enEjecucion=0;
                funcion();
            }
            break;
        case 27:///ESC
            borrarSeccion(29,5,ANCHO-29, ALTURA-5);
            enEjecucion=0;
            break;
        case '+':
            sentido=1;
            break;
        case '-':
            sentido=-1;
            break;
        default:///Se considera que se presiono una opcion de ordenamiento
            orden=teclaPresionada;
            break;
        }
    }
}

void menuOpcionesEmergentes(char mensaje[25], OpcionMenu botones[], int cantMenu, void *arg, void *arg2)
{

    int x=botones[0].x-2;
    int y=botones[0].y-3;
    int ancho=botones[0].ancho+4;
    int altura=botones[0].altura*(cantMenu)+4;
    int posicionTexto=(ancho/2-strlen(mensaje)/2)+x;
    pintarRecuadro(x,y, ancho, altura, botones[0].color);
    gotoxy(posicionTexto, y+1);
    printf("%s", mensaje);

    menuVertical(botones, cantMenu, arg, NULL);
    //menuEmergente(botones, cantMenu);
}

int menuConfirmacion(char mensaje[25], OpcionMenu botones[], int cantMenu)
{
    int respuesta=cantMenu-1;
    int x=botones[0].x-2;
    int y=botones[0].y-3;
    int ancho=botones[0].ancho+4;
    int altura=botones[0].altura*(cantMenu)+4;
    int posicionTexto=(ancho/2-strlen(mensaje)/2)+x;
    pintarRecuadro(x,y, ancho, altura, botones[0].color);
    gotoxy(posicionTexto, y+1);
    printf("%s", mensaje);

    respuesta=menuEmergente(botones, cantMenu);

    return respuesta;
}

///NO se esta usando//////////////////////////////////////////////////////////////////////////////////
void menuModificacionAlquilerViejooooooooooooo(Alquiler *alquiler)
{
    char mensaje[]="MODIFICAR DATOS";
    int cantCampos=6;
    OpcionMenu camposModificacion[cantCampos];
    cargarArregloMenuModificacion(camposModificacion);
    int x=camposModificacion[0].x-2;
    int y=camposModificacion[0].y-3;
    int ancho=camposModificacion[0].ancho+4;
    int altura=camposModificacion[0].altura*(cantCampos)+4;
    int posicionTexto=(ancho/2-strlen(mensaje)/2)+x;

    pintarRecuadro(x,y, ancho, altura, camposModificacion[0].color);
    gotoxy(posicionTexto, y+1);
    printf("%s", mensaje);

    menuVertical(camposModificacion, cantCampos, alquiler, NULL);
}

void menuModificacionAlquiler(Alquiler *alquiler)
{
    char mensaje[]="MODIFICAR DATOS";
    int cantCampos=6;
    OpcionMenu camposModificacion[cantCampos];
    cargarArregloMenuModificacion(camposModificacion);
    int x=camposModificacion[0].x-2;
    int y=camposModificacion[0].y-3;
    int ancho=camposModificacion[0].ancho+4;
    int altura=camposModificacion[0].altura*(cantCampos)+4;
    int posicionTexto=(ancho/2-strlen(mensaje)/2)+x;

    pintarRecuadro(x,y, ancho, altura, camposModificacion[0].color);
    gotoxy(posicionTexto, y+1);
    printf("%s", mensaje);

    menuVertical(camposModificacion, cantCampos, alquiler, NULL);
}

void cargarArregloOpciones(OpcionMenu arregloMenu[])
{
    arregloMenu[0]=crearOpcionMenu("MODIFICAR", 0, 57, 14, COLOR_BTN_LAT, COLOR_VERDE, 23, 3, menuModificacionAlquiler, NULL, 1);
    arregloMenu[1]=crearOpcionMenu("FINALIZAR", 0, 57, 17, COLOR_BTN_LAT, COLOR_AZUL, 23, 3, finalizarAlquiler, NULL, 1);
    arregloMenu[2]=crearOpcionMenu("ELIMINAR", 0, 57, 20, COLOR_BTN_LAT, COLOR_ROJO, 23, 3, confirmarEliminarAlquiler, NULL, 1);
}

void cargarArregloBotones(OpcionMenu arregloMenu[], char textoOpciones[][15], int colores[], int cantidad)
{
    int anchoBtn=23;
    int altoBtn=3;
    int x=(ANCHO-X_PANEL)/2+X_PANEL-(anchoBtn/2);
    int y=(ALTURA-Y_PANEL)/2+Y_PANEL-(altoBtn*(cantidad))/2;
    for(int i=0; i<cantidad; i++)
    {
        arregloMenu[i]=crearOpcionMenu(textoOpciones[i], 0, x, y+(i*altoBtn), COLOR_BTN_LAT, colores[i], anchoBtn, altoBtn, NULL, NULL, 1);
    }
}

void cargarArregloOpcionesInactivos(OpcionMenu arregloMenu[])
{
    arregloMenu[0]=crearOpcionMenu("ACTIVAR", 0, 57, 14, COLOR_BTN_LAT, COLOR_VERDE, 23, 3, menuModificacionAlquiler, NULL, 1);
}

void cargarArregloBotonesConfirmacion(OpcionMenu arregloMenu[])
{
    arregloMenu[0]=crearOpcionMenu("CANCELAR", 0, 57, 14, COLOR_BTN_LAT, COLOR_AZUL, 23, 3, NULL, NULL, 1);
    arregloMenu[1]=crearOpcionMenu("ACEPTAR", 0, 57, 17, COLOR_BTN_LAT, COLOR_ROJO, 23, 3, NULL, NULL, 1);
}

void cargarArregloMenuModificacion(OpcionMenu arregloMenu[])
{
    int x=(ANCHO-X_PANEL)/2+X_PANEL-(23/2);
    arregloMenu[0]=crearOpcionMenu("fecha de inicio", 0, x, 10, COLOR_BTN_SUP, COLOR_AZUL, 23, 3, modificarFechaIn, NULL, 1);
    arregloMenu[1]=crearOpcionMenu("fecha de fin", 0, x, 13, COLOR_BTN_SUP, COLOR_AZUL, 23, 3, NULL, NULL, 1);
    arregloMenu[2]=crearOpcionMenu("DNI del cliente", 0, x, 16, COLOR_BTN_SUP, COLOR_AZUL, 23, 3, NULL, NULL, 1);
    arregloMenu[3]=crearOpcionMenu("patente", 0, x, 19, COLOR_BTN_SUP, COLOR_AZUL, 23, 3, NULL, NULL, 1);
    arregloMenu[4]=crearOpcionMenu("precio", 0, x, 22, COLOR_BTN_SUP, COLOR_AZUL, 23, 3, NULL, NULL, 1);
    arregloMenu[5]=crearOpcionMenu("GUARDAR", 0, x, 25, COLOR_BTN_LAT, COLOR_BTN_SELEC_LAT, 23, 3, NULL, NULL, 1);
}

///imprime la cabecera de la lista de alquileres a mostrar
void cabeceraAlquileres(int x, int y)
{
    color(COLOR_BASE);
    for(int i=0; i<=80; i++)
    {
        gotoxy(x+i,y+1);
        printf("%c", 196);///  ─
        if(i==5||i==20||i==36||i==52||i==67)
        {
            gotoxy(x+i,y);
            printf("%c", 179);/// │
            gotoxy(x+i,y+1);
            printf("%c", 193);///  ┴
        }
        if(i==0)
        {
            gotoxy(x+i,y);
            printf("%c", 179);/// │
            gotoxy(x+i,y+1);
            printf("%c", 192);///  └
        }
        if(i==80)
        {
            gotoxy(x+i,y);
            printf("%c", 179);/// │
            gotoxy(x+i,y+1);
            printf("%c", 217);/// ┘
        }

    }
    gotoxy(x+1,y);
    printf(" Id");
    gotoxy(x+6,y);
    printf(" Fecha inicio");
    gotoxy(x+21,y);
    printf("   Fecha fin");
    gotoxy(x+39,y);
    printf("  Patente");
    gotoxy(x+55,y);
    printf("   DNI");
    gotoxy(x+69,y);
    printf(" Importe");
}

///Muestra la lista del vehiculos disponibles para alquilar
void mostrarListaVehiculosAlquiler(Vehiculo vehiculos[], int cantidadVehi, int seleccionado, int x, int y)
{
    int cantMostrar=8;
    int inicio=0;

    if(cantidadVehi<cantMostrar)
    {
        cantMostrar=cantidadVehi;
    }
    if(seleccionado>=cantMostrar)
    {
        inicio=seleccionado+1-cantMostrar;
    }

    for(int i=0; i<cantMostrar; i++)
    {
        if(i+inicio==seleccionado)
        {
            color(COLOR_BTN_SELEC_SUP);
        }
        else
        {
            color(COLOR_BTN_SUP);
        }
        mostrarListaPatentes(vehiculos[i+inicio], x, y+2+i);
    }
}

void mostrarVehiculoAlquiler(Vehiculo vehiculo, int x, int y)
{
    gotoxy(x+3,y);
    printf("            ");
    gotoxy(x+3,y);
    printf("%s", vehiculo.marca);
    gotoxy(x+20,y);
    printf("            ");
    gotoxy(x+20,y);
    printf("%s", vehiculo.modelo);
    gotoxy(x+38,y);
    printf("            ");
    gotoxy(x+38,y);
    printf("%s", vehiculo.tipoVehiculo);
    gotoxy(x+54,y);
    printf("            ");
    gotoxy(x+54,y);
    printf("%s", patenteToString(vehiculo.patente));
    gotoxy(x+70,y);
    printf("            ");
    gotoxy(x+70,y);
    printf("$%.2f", vehiculo.precioDeAlquilerDiario);
}

void mostrarListaPatentes(Vehiculo vehiculo, int x, int y)
{

    gotoxy(x+11,y);
    printf("            ");
    gotoxy(x+11,y);
    printf("%s", vehiculo.marca);

    gotoxy(x+23,y);
    printf("            ");
    gotoxy(x+23,y);
    printf("%s", vehiculo.modelo);

    gotoxy(x,y);
    printf("         ");
    gotoxy(x,y);
    printf("  %s %s  ", vehiculo.patente.letras, vehiculo.patente.numeros);//patenteToString(alqui.vehiculo)
}

char* recorrerListaVehiculosAlquiler(int cantidadVehi, Vehiculo vehiculos[], int x, int y)
{
    Patente patenteSeleccionada;
    int cantMenu=5;
    hidecursor(0);
    char* patenteStr = (char*)malloc(7 * sizeof(char));
    limpiarString(patenteStr, 7);
    int enEjecucion=1;
    int posicionY=y;
    char teclaPresionada;
    while(enEjecucion)
    {
        mostrarListaVehiculosAlquiler(vehiculos, cantidadVehi, posicionY-y, x, y);
        gotoxy(x,posicionY);
        teclaPresionada=getch();
        switch(teclaPresionada)
        {
        case 80:///ABAJO
            if(posicionY<cantidadVehi+y-1)
            {
                posicionY++;
            }
            break;
        case 72:///ARRIBA
            if(posicionY>y)
            {
                posicionY--;
            }
            break;
        case 13:///ENTER
            patenteSeleccionada=vehiculos[posicionY-y].patente;
            strcpy(patenteStr, patenteToString(patenteSeleccionada));
            enEjecucion=0;
            gotoxy(x,13);
            break;
        case 27:
            enEjecucion=0;
            break;
        }
    }
    borrarSeccion(50,14, ANCHO-50, ALTURA-14);
    gotoxy(50,7);
    return patenteStr;
}

void cabeceraVehiculosAlquiler(int x, int y)
{
    color(COLOR_BASE);
    for(int i=0; i<=80; i++)
    {
        gotoxy(x+i,y+1);
        printf("%c", 196);///  ─

        if(i==16||i==34||i==50||i==67)
        {
            gotoxy(x+i,y);
            printf("%c", 179);/// │
            gotoxy(x+i,y+1);
            printf("%c", 193);///  ┴
        }
        if(i==0)
        {
            gotoxy(x+i,y);
            printf("%c", 179);/// │
            gotoxy(x+i,y+1);
            printf("%c", 192);///  └
        }
        if(i==80)
        {
            gotoxy(x+i,y);
            printf("%c", 179);/// │
            gotoxy(x+i,y+1);
            printf("%c", 217);/// ┘
        }

    }
    gotoxy(x+1,y);
    printf("     Marca");
    gotoxy(x+17,y);
    printf("     Modelo");
    gotoxy(x+35,y);
    printf("      Tipo");
    gotoxy(x+51,y);
    printf("   Patente");
    gotoxy(x+69,y);
    printf(" Importe");
}

void ingresarDatosNuevoAlquiler()
{
    int x=50;
    int y=9;
    imprimirDatosAlquiler(x,y);
    recorrerDatosAlquiler(x, y, NULL);
}

void ingresarDatosAlquilerExistente(Alquiler alq)
{
    int x=50;
    int y=9;
    imprimirDatosAlquiler(x,y);
    recorrerDatosAlquiler(x, y, &alq);
}

void imprimirDatosAlquiler(int x, int y)
{
    color(COLOR_BASE);

    gotoxy(x-17,y);
    printf("FECHA DE INICIO: ");

    gotoxy(x-14,y+2);
    printf("FECHA DE FIN: ");

    gotoxy(x-17,y+4);
    printf("DNI DEL CLIENTE: ");

    gotoxy(x-18,y+6);
    printf("PATENTE DEL AUTO: ");

    gotoxy(x-9,y+8);
    printf("IMPORTE: ");
}

void recorrerDatosAlquiler(int x, int y, void*arg)
{
    hidecursor(1);
    Patente pat;
    Alquiler alqui;
    char fechaIn[11];
    char fechaOut[11];
    char dni[9];
    char patenteStr[8];
    char * patenteSeleccionada;
    float valorAlquiler=0;
    limpiarString(fechaIn, 11);
    limpiarString(fechaOut,11);
    limpiarString(dni, 9);
    limpiarString(patenteStr, 8);

    int indiceFechaIn=0;
    int indiceFechaOut=0;
    int indiceDni=0;

    int enEjecucion=1;
    int posicionY=y;
    int posicionX=x;
    char teclaPresionada;

    int cantVehiculosDisp=0;

    OpcionMenu botonGuardar=crearOpcionMenu("GUARDAR", 0, 31, ALTURA-5, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 29, 3, NULL, NULL, 1);

    while(enEjecucion)
    {
        if(!botonGuardar.seleccionado)
        {
            hidecursor(1);
        }
        else
        {
            hidecursor(0);
        }
        actualizarDatos(fechaIn, &indiceFechaIn, fechaOut, &indiceFechaOut, dni, patenteStr, botonGuardar, valorAlquiler,arg);
        gotoxy(posicionX,posicionY);

        fflush(stdin);
        teclaPresionada=getch();

        switch(teclaPresionada)
        {
        case 80:///ABAJO
            if(posicionY<15)
            {
                posicionY+=2;
            }
            else if(posicionY==15)
            {
                posicionY=botonGuardar.y;
                botonGuardar.seleccionado=1;
            }
            break;
        case 72:///ARRIBA
            if (posicionY==botonGuardar.y)
            {
                posicionY=15;
                botonGuardar.seleccionado=0;
            }
            else if(posicionY>y)
            {
                posicionY-=2;
            }

            break;
        case 13:///ENTER

            if(posicionY==15)
            {
                gotoxy(65,25);
                cantVehiculosDisp=0;
                patenteSeleccionada = recorrerListaVehiculosAlquiler(cantVehiculosDisp, obtenerVehiculosDisponibles(&cantVehiculosDisp), 50,12);
                strcpy(patenteStr, patenteSeleccionada);
            }
            if(botonGuardar.seleccionado)
            {
                if(arg==NULL)
                {
                    if(verificarAlquiler(dniStringToInt(dni), stringToFecha(fechaIn), stringToFecha(fechaOut), stringToPatente(patenteStr)))
                    {
                        pat=stringToPatente(patenteStr);
                        alqui=generarAlquiler(dniStringToInt(dni), stringToFecha(fechaIn), stringToFecha(fechaOut), pat);
                        calcularValorAlquiler(pat, stringToFecha(fechaIn), stringToFecha(fechaOut), &valorAlquiler);
                        alqui.precioTotal=valorAlquiler;
                        confirmarGuardar(alqui);
                        enEjecucion=0;
                    }
                }
                else
                {
                    if(verificarCamposModificadosAlquiler(dniStringToInt(dni), stringToFecha(fechaIn), stringToFecha(fechaOut), stringToPatente(patenteStr),arg)>0)
                    {
                        confirmarModificar(*(Alquiler*)arg);
                        enEjecucion=0;
                    }
                }
            }
            break;
        case 27:///ESC
            borrarContenido();
            hidecursor(0);
            enEjecucion=0;
            break;
        }
        switch(posicionY)
        {
        case 9:///FECHA INICIO
            if(teclaPresionada>47&&teclaPresionada<58)///es un numero
            {
                if(indiceFechaIn<10)
                {
                    fechaIn[indiceFechaIn]=teclaPresionada;
                    indiceFechaIn++;
                }
            }
            else if (teclaPresionada=='\b')
            {
                borrarCaracterFecha(fechaIn, &indiceFechaIn);
            }
            posicionX=x+strlen(fechaIn);
            break;
        case 11:///FECHA FIN
            if(teclaPresionada>47&&teclaPresionada<58)///es un numero
            {
                if(indiceFechaOut<10)
                {
                    fechaOut[indiceFechaOut]=teclaPresionada;
                    indiceFechaOut++;
                }
            }
            else if (teclaPresionada=='\b')
            {
                borrarCaracterFecha(fechaOut, &indiceFechaOut);
            }
            posicionX=x+strlen(fechaOut);
            break;
        case 13:///DNI
            if(teclaPresionada>47&&teclaPresionada<58)///es un numero
            {
                if(indiceDni<8)
                {
                    dni[indiceDni]=teclaPresionada;
                    indiceDni++;
                }
            }
            else if (teclaPresionada=='\b')
            {
                if(strlen(dni)>0)
                {
                    dni[strlen(dni) - 1] = '\0';
                    indiceDni--;
                }
            }
            posicionX=x+strlen(dni);
            break;
        }
    }
}

void actualizarDatos(char fechaIn[], int *indiceFechaIn, char fechaOut[], int *indiceFechaOut, char dni[], char patente[], OpcionMenu botonGuardar, float valorAlquiler, Alquiler *alq)
{
    int x=50;
    int y=9;
    Fecha *fechaInicio=NULL;
    Fecha *fechaFin=NULL;
    if(alq)
    {
        if (alq)
        {
            fechaInicio = &alq->fechaInicio;
            fechaFin = &alq->fechaFin;
        }
    }
    color(COLOR_BASE);
    gotoxy(x,y);
    if(!formatearStringFecha(fechaIn, indiceFechaIn, fechaInicio))
    {
        informarError(x+13, y, "La fecha no es valida", COLOR_ERROR);
    }
    else
    {
        informarError(x+13, y, "                     ", COLOR_ERROR);
    }

    gotoxy(x,y+2);
    if(!formatearStringFecha(fechaOut, indiceFechaOut, fechaFin))
    {
        informarError(x+13, y+2, "La fecha no es valida", COLOR_ERROR);
    }
    else
    {
        informarError(x+13, y+2, "                     ", COLOR_ERROR);
    }

    if(strlen(fechaIn)==10&&strlen(fechaOut)==10)
    {

        if(compararFecha(stringToFecha(fechaOut), stringToFecha(fechaIn))<0)
        {
            strcpy(fechaOut, "");
            limpiarString(fechaOut,10);
            informarError(x+13, y+2, "La fecha de fin debe ser posterior", COLOR_ERROR);
        }
        else
        {
            informarError(x+13, y+2, "                                  ", COLOR_ERROR);
        }
    }
    gotoxy(x,y+4);
    printf("          ");
    gotoxy(x,y+4);
    if(strlen(dni)>0)
    {
        color(COLOR_BASE);
        printf("%s", dni);
    }
    else if(alq!=NULL)
    {
        color(COLOR_DESABILITADO);
        printf("%d", (*alq).dniCliente);
    }
    else
    {
        color(COLOR_DESABILITADO);
        printf("sin puntos");
    }

    gotoxy(x,y+6);
    color(COLOR_BASE);
    printf("            ");
    gotoxy(x,y+6);

    if(strlen(patente)>0)
    {
        printf("%s", patente);
    }
    else if(alq!=NULL)
    {
        color(COLOR_DESABILITADO);
        printf("%s", patenteToString((*alq).vehiculo));
    }
    else
    {
        color(COLOR_DESABILITADO);
        printf("<PATENTE>");
    }

    calcularValorAlquiler(stringToPatente(patente), stringToFecha(fechaIn), stringToFecha(fechaOut), &valorAlquiler);

    gotoxy(x,y+8);
    color(COLOR_BASE);
    printf("            ");
    if(valorAlquiler>0)
    {
        color(COLOR_BASE);
        gotoxy(x,y+8);
        printf("$ %.2f", valorAlquiler);
    }
    else if(alq!=NULL)
    {
        color(COLOR_DESABILITADO);
        gotoxy(x,y+8);
        printf("$ %.2f", (*alq).precioTotal);
    }
    else
    {
        color(COLOR_DESABILITADO);
        gotoxy(x,y+8);
        printf("$ %.2f", valorAlquiler);
    }


    pintarOpcionMenu(botonGuardar);
}

int verificarAlquiler(int dniCliente, Fecha fechaInicio, Fecha fechaFin, Patente patente)
{
    int fechaInicioValida=0;
    int fechaFinValida=0;
    int dniValido=0;
    int patValida=0;
    if(validarFecha(fechaInicio))
    {
        fechaInicioValida=1;
        informarError(62, 9, " ", COLOR_ERROR);
    }
    else
    {
        informarError(62, 9, "X", COLOR_ERROR);
    }

    if(validarFecha(fechaFin))
    {
        fechaFinValida=1;
        informarError(62, 9, " ", COLOR_ERROR);
    }
    else
    {
        informarError(62, 11, "X", COLOR_ERROR);
    }

    if(existeDniCliente(dniCliente))
    {
        dniValido=1;
        informarError(63, 13, "                      ", COLOR_ERROR);
    }
    else
    {
        informarError(63, 13, "Cliente no encontrado", COLOR_ERROR);
    }

    if(strlen(patente.letras)==3)
    {
        patValida=1;
    }
    else
    {
        informarError(63, 15, "Seleccione una patente", COLOR_ERROR);
    }

    return (fechaFinValida&&fechaInicioValida&&patValida&&dniValido);
}

int verificarCamposModificadosAlquiler(int dniCliente, Fecha fechaInicio, Fecha fechaFin, Patente patente, Alquiler *alq)
{



    int camposModificados=0;
//    Fecha inicioAlquiler=(*alq).fechaInicio;
//    Fecha finAlquiler=(*alq).fechaFin;

    if(validarFecha(fechaInicio))
    {
        informarError(62, 9, " ", COLOR_ERROR);
        (*alq).fechaInicio=fechaInicio;
        camposModificados++;
    }
    else
    {
        informarError(62, 9, "X", COLOR_ERROR);
    }
    //(*alq).fechaInicio=inicioAlquiler;
    if(validarFecha(fechaFin))
    {
        if(compararFecha(fechaFin,(*alq).fechaFin)>=0)
        {
//        gotoxy(0,25);
//        printf("%s", fechaToString(inicioAlquiler));
//        gotoxy(0,26);
//        printf("%s", fechaToString(fechaFin));
            informarError(62, 9, " ", COLOR_ERROR);
            (*alq).fechaFin=fechaFin;
            camposModificados++;
        }
    }
    else
    {
        informarError(62, 11, "X", COLOR_ERROR);
    }

    if(existeDniCliente(dniCliente)&&dniCliente>0)
    {
        informarError(63, 13, "                      ", COLOR_ERROR);
        (*alq).dniCliente=dniCliente;
        camposModificados++;
    }
    else
    {
        informarError(63, 13, "Cliente no encontrado", COLOR_ERROR);
    }

    if(strlen(patente.letras)==3)
    {
        (*alq).vehiculo=patente;
        camposModificados++;
    }
    else
    {
        informarError(63, 15, "Seleccione una patente", COLOR_ERROR);
    }
    gotoxy(0,23);
    printf("In ingre %s", fechaToString(fechaInicio));
    gotoxy(0,24);
    printf("Out ingre %s", fechaToString(fechaFin));
    gotoxy(0,25);
    printf("In guar %s", fechaToString((*alq).fechaInicio));
    gotoxy(0,26);
    printf("Out guar %s", fechaToString((*alq).fechaFin));

    return camposModificados;
}

///Imprime la cabecera con instrucciones de ordenamiento
void imprimirOpcionesOrdenamiento()
{
    int x=29;
    int y=5;
    pintarRecuadro(x,y, ANCHO-x, 3, COLOR_BTN_SELEC_SUP);

    gotoxy(x+1, y+1);
    printf("ORDEN | <F> fecha| <V> Vehiculo | <D> dni | <I> importe |<+> ascendente|<-> descendente");
}


void confirmarGuardar(Alquiler alquiler)
{
    int cantBotones=2;
    OpcionMenu botones[cantBotones];
    char textos[][15]= {"      NO      ", "      SI      "};
    int colores[]= {COLOR_AZUL,COLOR_VERDE};
    cargarArregloBotones(botones, textos, colores, cantBotones);
    if(menuConfirmacion("GUARDAR ALQUILER?", botones, cantBotones))
    {

        if(registrarAlquiler(alquiler))
        {
            informacionEmergente("ALQUILER REGISTRADO");
        }
        else
        {
            informacionEmergente("ERROR AL GUARDAR");
        }
    }
}

int confirmarRegistrarUsuario(Usuario usuario)
{
    int guardado=0;
    int cantBotones=2;
    OpcionMenu botones[cantBotones];
    char textos[][15]= {"      SI      ", "      NO      "};
    int colores[]= {COLOR_VERDE,COLOR_ROJO};
    cargarArregloBotones(botones, textos, colores, cantBotones);
    if(!menuConfirmacion("REGISTRAR USUARIO?", botones, cantBotones))
    {
        agregarMayusculas(usuario.nombre);
        borrarMenu();
        if(guardarUsuario(usuario))
        {
            informacionEmergente("USUARIO REGISTRADO");
            guardado=1;
        }
        else
        {
            informacionEmergente("ERROR AL GUARDAR");
        }
    }
    return guardado;
}

void confirmarModificar(Alquiler alquiler)
{
    int cantBotones=2;
    OpcionMenu botones[cantBotones];
    char textos[][15]= {"      NO      ", "      SI      "};
    int colores[]= {COLOR_AZUL,COLOR_VERDE};
    cargarArregloBotones(botones, textos, colores, cantBotones);
    if(menuConfirmacion("MODIFICAR ALQUILER?", botones, cantBotones))
    {
        if(modificarAlquiler(alquiler))
        {
            informacionEmergente("ALQUILER MODIFICADO");
        }
        else
        {
            informacionEmergente("ERROR AL GUARDAR");
        }
    }
}

void confirmarEliminarAlquiler(Alquiler alquiler)
{
    if(mensajeConfirmacion("SE ELIMINARA EL ALQUILER "))
    {
        eliminarAlquiler(alquiler);
    }
}

void confirmarEliminar(Alquiler alquiler)
{
    int cantBotones=2;
    OpcionMenu botones[cantBotones];
    char textos[][15]= {"      NO      ", "      SI      "};
    int colores[]= {COLOR_AZUL,COLOR_ROJO};
    cargarArregloBotones(botones, textos, colores, cantBotones);
    if(menuConfirmacion("ESTA SEGURO?", botones, cantBotones))
    {
        eliminarAlquiler(alquiler);
    }
}

void confirmarRestaurar(Alquiler alquiler)
{
    int cantBotones=2;
    OpcionMenu botones[cantBotones];
    char textos[][15]= {"      NO      ", "      SI      "};
    int colores[]= {COLOR_AZUL,COLOR_ROJO};
    cargarArregloBotones(botones, textos, colores, cantBotones);
    if(menuConfirmacion("ESTA SEGURO?", botones, cantBotones))
    {
        if(restaurarAlquiler(alquiler))
        {
            informacionEmergente("ALQUILER RESTAURADO");
        }
    }
}

void confirmarFinalizar(Alquiler alquiler)
{
    int cantBotones=2;
    OpcionMenu botones[cantBotones];
    char textos[][15]= {"      NO      ", "      SI      "};
    int colores[]= {COLOR_AZUL,COLOR_ROJO};
    cargarArregloBotones(botones, textos, colores, cantBotones);
    if(menuConfirmacion("ESTA SEGURO?", botones, cantBotones))
    {
        Fecha fechaActual=obtenerFechaActual();

        if(finalizarAlquiler(alquiler))
        {
            informacionEmergente("ALQUILER FINALIZADO");
        }
    }
}

void confirmarReactivar(Alquiler alquiler)
{
    int cantBotones=2;
    OpcionMenu botones[cantBotones];
    char textos[][15]= {"      NO      ", "      SI      "};
    int colores[]= {COLOR_AZUL,COLOR_ROJO};
    cargarArregloBotones(botones, textos, colores, cantBotones);
    if(!verificarPatenteAlquiler(alquiler.vehiculo))
    {
        if(menuConfirmacion("ESTA SEGURO?", botones, cantBotones))
        {
            reactivarAlquiler(alquiler);
        }
    }
    else
    {
        informacionEmergente("VEHICULO NO DISPONIBLE");
    }
}

void modificarFechaIn(Alquiler alquiler)
{
    int cantBotones=2;
    OpcionMenu botones[cantBotones];
    char textos[][15]= {"    ACEPTAR   ", "   CANCELAR   "};
    int colores[]= {COLOR_VERDE, COLOR_AZUL};
    cargarArregloBotones(botones, textos, colores, cantBotones);
    borrarContenido();
    menuIngresoFecha("MODIFICAR FECHA INICIO", botones, cantBotones);

    menuIngresoDatos(botones, cantBotones);
}

int menuIngresoFecha(char mensaje[25], OpcionMenu botones[], int cantMenu)
{
    int respuesta=cantMenu-1;
    int x=botones[0].x-2;
    int y=botones[0].y-6;
    int ancho=botones[0].ancho+4;
    int altura=botones[0].altura*(cantMenu)+7;
    int posicionTexto=(ancho/2-strlen(mensaje)/2)+x;
    pintarRecuadro(x+2,y+3, ancho-4, botones[0].altura, COLOR_ESCRITURA);
    pintarRecuadro(x,y, ancho, altura, botones[0].color);
    gotoxy(posicionTexto, y+1);
    printf("%s", mensaje);

    return respuesta;
}

int menuIngresoDatos(OpcionMenu arregloBotones[], int cantMenu)
{
    hidecursor(0);
    int enEjecucion=1;
    int posicionInicioY=arregloBotones[0].y;
    int posicionY=posicionInicioY;
    int alturaElemento=arregloBotones[0].altura;

    int xFecha=arregloBotones[0].x+1;
    int yFecha=arregloBotones[0].y-2;

    char fechaIn[11];
    int indiceFechaIn=0;

    char teclaPresionada;
    int seleccionado=0;
    while(enEjecucion)
    {
        arregloBotones[(posicionY-arregloBotones[0].y)/alturaElemento].seleccionado=cantMenu-0;
        pintarMenu(arregloBotones, cantMenu);
        actualizarFechaIn(fechaIn, &indiceFechaIn, xFecha, yFecha);
        gotoxy(arregloBotones[0].x+indiceFechaIn,posicionY);
        teclaPresionada=getch();
        switch(teclaPresionada)
        {
        case 80:///ABAJO
            if(posicionY<alturaElemento*(cantMenu-1)+arregloBotones[0].y)
            {
                posicionY+=alturaElemento;
            }
            break;
        case 72:///ARRIBA
            if(posicionY>arregloBotones[0].y)
            {
                posicionY-=alturaElemento;
            }
            break;
        case 13:///ENTER
            seleccionado=(posicionY-posicionInicioY)/alturaElemento;
            enEjecucion=0;
            borrarContenido();
            break;
        case 27:///ESC
            seleccionado=cantMenu-1;
            enEjecucion=0;
            borrarContenido();
            break;
        default:
            if(teclaPresionada>47&&teclaPresionada<58)///es un numero
            {
                if(indiceFechaIn<10)
                {
                    fechaIn[indiceFechaIn]=teclaPresionada;
                    indiceFechaIn++;
                }
            }
            else if (teclaPresionada=='\b')
            {
                borrarCaracterFecha(fechaIn, &indiceFechaIn);
            }
            break;
        }
        for(int i=0; i<cantMenu; i++)
        {
            arregloBotones[i].seleccionado=0;
        }
    }
    return seleccionado;
}

void actualizarFechaIn(char fechaIn[], int *indiceFechaIn, int x, int y)
{
    gotoxy(x,y);
    if(!formatearStringFecha(fechaIn, indiceFechaIn))
    {
        informarError(x, y+1, "La fecha no es valida", COLOR_ERROR);
    }
    else
    {
        informarError(x, y+1, "                     ", COLOR_ERROR);
    }
}
