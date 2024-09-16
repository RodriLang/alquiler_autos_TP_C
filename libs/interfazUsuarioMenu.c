#include "interfazUsuario.h"
#include "gotoxy.h"
#include<stdio.h>

void definirVentana()
{
    // Obtiene el identificador de la ventana de la consola
    HWND consolaWindows = GetConsoleWindow();

    system("color B1");

    desactivarMaximizar(consolaWindows);
    dimensionarVentana(consolaWindows);
    centrarVentana(consolaWindows);

    pintarRecuadro(0, 0, 29, ALTURA, COLOR_BTN_LAT);
}

void desactivarMaximizar(HWND consolaWindows)
{
    LONG style = GetWindowLong(consolaWindows, GWL_STYLE);
    if (style == 0)
    {
        printf("No se pudieron obtener las propiedades de la ventana\n");
        return;
    }
    // Desactiva el botón de maximizar y el redimensionamiento de la ventana
    SetWindowLong(consolaWindows, GWL_STYLE, GetWindowLong(consolaWindows, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
    style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX);
    SetWindowLong(consolaWindows, GWL_STYLE, style);
}

void centrarVentana(HWND consolaWindows)
{
    if (consolaWindows != NULL)
    {
        // Restaura la ventana a su tamaño normal si está maximizada o minimizada
        ShowWindow(consolaWindows, SW_RESTORE);

        // Obtiene el tamaño de la pantalla
        RECT desktopRect;
        const HWND hDesktop = GetDesktopWindow();
        GetWindowRect(hDesktop, &desktopRect);

        // Obtiene el tamaño de la ventana de la consola
        RECT consoleRect;
        GetWindowRect(consolaWindows, &consoleRect);

        // Calcula la nueva posición para centrar la ventana
        int x = (desktopRect.right / 2) - ANCHO*4 ;///4 es la mitad del ancho en pixeles de una columna de la consola
        int y = (desktopRect.bottom / 2) - ALTURA*8 ;///8 es la mitad de la altura en pixeles de una fila de la consola

        // Mueve la ventana de la consola a la nueva posición
        SetWindowPos(consolaWindows, HWND_TOP, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
}

void dimensionarVentana(HWND consolaWindows)
{
    // Obtiene el identificador del buffer de la consola
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Define el tamaño del buffer de la consola
    COORD bufferSize;
    bufferSize.X = ANCHO;
    bufferSize.Y = ALTURA;
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    // Define las dimensiones de la ventana de la consola
    SMALL_RECT windowSize = {0, 0, ANCHO-1, ALTURA - 1};
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    bufferSize.X = (SHORT)ANCHO;
    bufferSize.Y = (SHORT)ALTURA;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
}

void pintarRecuadro(int x, int y, int ancho, int altura, int colorFondo)
{
    color(colorFondo);
    for(int i=0; i<altura; i++)
    {
        gotoxy(x,y);
        for(int j=0; j<ancho; j++)
        {
            printf(" ");
        }
        y++;
    }
}

void pintarOpcionMenu(OpcionMenu elemento)
{
    int y=elemento.y;
    int posicionTexto=(elemento.ancho/2-strlen(elemento.texto)/2)+elemento.x;
    if(elemento.seleccionado)
    {
        color(elemento.colorSeleccionado);
    }
    else
    {
        color(elemento.color);
    }

    for(int i=0; i<elemento.altura; i++)
    {
        gotoxy(elemento.x, y);
        for(int j=0; j<elemento.ancho; j++)
        {
            printf(" ");
        }
        y++;
    }
    gotoxy(posicionTexto,elemento.y+elemento.altura/2);
    printf("%s", elemento.texto);
}


void pintarMenu(OpcionMenu arregloMenu[], int cantidadMenu)
{
    for(int i=0; i<cantidadMenu; i++)
    {
        pintarOpcionMenu(arregloMenu[i]);
    }
}

void cargarArregloSubMenuListaDeVehiculos(OpcionMenu arregloMenu[])
{
    arregloMenu[0]=crearOpcionMenu("LISTA COMPLETA", 0, 46, 5, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 27, 3, menuListadoVehiculos, NULL, 0);
    arregloMenu[1]=crearOpcionMenu("SOLO DISPONIBLES", 0, 73, 5, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 27, 3, menuListadoVehiculosDisponibles, NULL, 0);
}

void cargarArregloMenu(OpcionMenu arregloMenu[])
{
    int ancho=23;
    int altura=3;
    arregloMenu[0]=crearOpcionMenu("VEHICULOS", 0, 3, 7, COLOR_BTN_LAT, COLOR_BTN_SELEC_LAT, 23, 3, subMenuVehiculos, NULL, 0);
    arregloMenu[1]=crearOpcionMenu("CLIENTES", 0, 3, 10, COLOR_BTN_LAT, COLOR_BTN_SELEC_LAT, 23, 3, subMenuPersonas, NULL, 0);
    arregloMenu[2]=crearOpcionMenu("ALQUILERES", 0, 3, 13, COLOR_BTN_LAT, COLOR_BTN_SELEC_LAT, 23, 3, subMenuAlquiler, NULL, 0);
    arregloMenu[3]=crearOpcionMenu("REPORTES", 0, 3, 16, COLOR_BTN_LAT, COLOR_BTN_SELEC_LAT, 23, 3, subMenuReportes, NULL, 0);
    arregloMenu[4]=crearOpcionMenu("SALIR", 0, 3, 19, COLOR_BTN_LAT, COLOR_BTN_SELEC_LAT, 23, 3, borrarMenu, NULL, 0);
}

void cargarArregloMenuAlquiler(OpcionMenu arregloMenu[])
{
    arregloMenu[0]=crearOpcionMenu("REGISTRAR ", 0, 31, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 22, 3, ingresarDatosNuevoAlquiler, NULL, 0);
    arregloMenu[1]=crearOpcionMenu("ALQUILERES ACTIVOS", 0, 53, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 22, 3, cargarListaAlquileresActivos, NULL, 0);
    arregloMenu[2]=crearOpcionMenu("FINALIZADOS ", 0, 75, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 22, 3, cargarListaAlquileresFinalizados, NULL, 0);
    arregloMenu[3]=crearOpcionMenu("ELIMINADOS", 0, 97, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 22, 3, cargarListaAlquileresEliminados, NULL, 0);
}

void cargarArregloMenuVehiculos(OpcionMenu arregloMenu[])
{
    arregloMenu[0]=crearOpcionMenu("AGREGAR VEHICULO", 0, 31, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 29, 3, agregarVehiculo, NULL, 0);
    arregloMenu[1]=crearOpcionMenu("MODIFICAR", 0, 60, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 29, 3, modificarVehiculo, NULL, 0);
    arregloMenu[2]=crearOpcionMenu("VER TODOS ", 0, 89, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 29, 3, subMenuVehiculosLista, NULL, 0);
}

void cargarArregloAdministracionClientes(OpcionMenu arregloMenu[])
{
    arregloMenu[0]=crearOpcionMenu("MODIFICAR CLIENTE", 0, 48, 5, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 27, 3, modificarRegistroClienteMenu, NULL, 0);
    arregloMenu[1]=crearOpcionMenu("DAR DE BAJAR/ACTIVAR", 0, 75, 5, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 27, 3, alternarEstadoClientePorDni, NULL, 0);
}

void cargarArregloMenuReportes(OpcionMenu arregloMenu[])
{
    arregloMenu[0]=crearOpcionMenu("CALCULAR INGRESOS", 0, 31, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 21, 3, mostrarIngresoMes, NULL, 0);
    arregloMenu[1]=crearOpcionMenu("ALQUILER MAYOR", 0, 52, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 21, 3, mostrarAlquilerMayor, NULL, 0);
    arregloMenu[2]=crearOpcionMenu("VEHICULOS NUEVOS", 0, 73, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 21, 3, menuListadoVehiculosNuevos, NULL, 0);
    arregloMenu[3]=crearOpcionMenu("ALQUI POR CLIENTE", 0, 94, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 21, 3, mostrarAlquilerPorCliente, NULL, 0);
}

void cargarArregloMenuPersonas(OpcionMenu arregloMenu[])
{
    arregloMenu[0]=crearOpcionMenu("AGREGAR CLIENTE", 0, 31, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 29, 3, cargarArchivoClienteMenu, NULL, 0);
    arregloMenu[1]=crearOpcionMenu("ADMINISTRACION", 0, 60, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 29, 3, subMenuAdmnistracionClientes, NULL, 0);
    arregloMenu[2]=crearOpcionMenu("MOSTRAR CLIENTES", 0, 89, 1, COLOR_BTN_SUP, COLOR_BTN_SELEC_SUP, 29, 3, menuListadoClientes, NULL, 0);
}

OpcionMenu crearOpcionMenu(char texto[], int seleccionado, int x, int y, int color, int colorSeleccionado, int ancho, int altura, void (*f1)(), void (*f2)(), int fin)
{
    OpcionMenu elementoMenu;
    strcpy(elementoMenu.texto, texto);
    elementoMenu.x=x;
    elementoMenu.y=y;
    elementoMenu.ancho=ancho;
    elementoMenu.altura=altura;
    elementoMenu.seleccionado=seleccionado;
    elementoMenu.color=color;
    elementoMenu.colorSeleccionado=colorSeleccionado;
    elementoMenu.funcionApertura=f1;
    elementoMenu.funcionCierre=f2;
    elementoMenu.finaliza=fin;
    return elementoMenu;
}

void subMenuAlquiler()
{
    color(3);
    int cantMenu=4;
    int activo=1;
    OpcionMenu menuAlquiler[cantMenu];
    cargarArregloMenuAlquiler(menuAlquiler);
    borrarContenido();
    menuAlquiler[0].seleccionado=1;
    gotoxy(menuAlquiler[0].x, menuAlquiler[0].y);
    pintarMenu(menuAlquiler, cantMenu);
    menuHorizontal(menuAlquiler, cantMenu, &activo, NULL);
}

void subMenuPersonas()
{
    color(3);
    int cantMenu=3;
    OpcionMenu menuPersonitas[cantMenu];
    cargarArregloMenuPersonas(menuPersonitas);
    borrarContenido();
    menuPersonitas[0].seleccionado=1;
    gotoxy(menuPersonitas[0].x, menuPersonitas[0].y);
    pintarMenu(menuPersonitas, cantMenu);
    menuHorizontal(menuPersonitas, cantMenu);
}

void subMenuVehiculos()
{
    color(3);
    int cantMenu=3;
    OpcionMenu menuVehiculos[cantMenu];
    cargarArregloMenuVehiculos(menuVehiculos);
    borrarContenido();
    menuVehiculos[0].seleccionado=1;
    gotoxy(menuVehiculos[0].x, menuVehiculos[0].y);
    pintarMenu(menuVehiculos, cantMenu);
    menuHorizontal(menuVehiculos, cantMenu);
}

void subMenuVehiculosLista()
{
    color(3);
    int cantMenu=2;
    OpcionMenu menuAlquiler[cantMenu];
    cargarArregloSubMenuListaDeVehiculos(menuAlquiler);
    borrarContenido();
    menuAlquiler[0].seleccionado=1;
    gotoxy(menuAlquiler[0].x, menuAlquiler[0].y);
    pintarMenu(menuAlquiler, cantMenu);
    menuHorizontal(menuAlquiler, cantMenu);

}

void subMenuReportes()
{
    color(3);
    int cantMenu=4;
    OpcionMenu menuReportes[cantMenu];
    cargarArregloMenuReportes(menuReportes);
    borrarContenido();
    menuReportes[0].seleccionado=1;
    gotoxy(menuReportes[0].x, menuReportes[0].y);
    pintarMenu(menuReportes, cantMenu);
    menuHorizontal(menuReportes, cantMenu);
}

void borrarSeccion(int x, int y, int ancho, int altura)
{
    color(COLOR_BASE);
    for(int i=0; i<altura; i++)
    {
        for(int j=0; j<ancho; j++)
        {
            gotoxy(x+j,y+i);
            printf(" ");
        }
    }
}

void borrarMenu()
{
    color(COLOR_BASE);
    for(int i=0; i<ALTURA; i++)
    {
        for(int j=X_PANEL; j<ANCHO; j++)
        {
            gotoxy(j,i);
            printf(" ");
        }
    }
}

///pinta del color de fondo la zona a la derecha del menu lateral y abajo del menu superior
void borrarContenido()
{
    color(COLOR_BASE);
    for(int i=Y_PANEL; i<ALTURA; i++)
    {
        for(int j=X_PANEL; j<ANCHO; j++)
        {
            gotoxy(j,i);
            printf(" ");
        }
    }
}

void menuPrincipal()
{
    int cantMenu=5;

    definirVentana();
    OpcionMenu menuLateral[cantMenu];
    cargarArregloMenu(menuLateral);
    login();


    menuVertical(menuLateral, cantMenu, NULL, NULL);
}

void login()
{
    int x=45;
    int y=6;
    int anchoLog=60;
    int altoLog=17;
    int altoBtn=3;

    borrarMenu();

    pintarRecuadro(x,y, anchoLog, altoLog, COLOR_BTN_LAT);
    pintarRecuadro(x+2,y+1, anchoLog-4, altoBtn, COLOR_ESCRITURA);
    pintarRecuadro(x+2,y+5, anchoLog-4, altoBtn, COLOR_ESCRITURA);

    char usuario[30];
    char clave[9];

    limpiarString(usuario, 30);
    limpiarString(clave, 9);

    color(COLOR_DESABIL_BLANCO);
    char mensajeUser[]="Ingrese su nombre de usuario";
    char mensajePass[]="Ingrese su clave";
    char mensajeErrorUser[]="minimo 6 caracteres";
    char mensajeErrorPass[]="minimo 8 caracteres";

    gotoxy(anchoLog/2+x-strlen(mensajeUser)/2, y+2);
    printf("%s", mensajeUser);
    gotoxy(anchoLog/2+x-strlen(mensajePass)/2, y+6);
    printf("%s", mensajePass);


    Usuario usuarioIngresado;

    int cantBotones=2;
    OpcionMenu botones[cantBotones];
    botones[0]=crearOpcionMenu("INGRESAR", 0, x+2, y+9, COLOR_BTN_SELEC_SUP, COLOR_VERDE, anchoLog-4, altoBtn, validarLogin, NULL, 1);
    botones[1]=crearOpcionMenu("REGISTRARSE", 0, x+2, y+13, COLOR_BTN_SELEC_SUP, COLOR_AZUL, anchoLog-4, altoBtn, registrarUsuario, NULL, 0);

    int claveOculta=1;

    int posY=y+2;
    int posX=anchoLog/2+x+strlen(usuario)/2;
    int enEjecucion=1;
    char tecla;

    while(enEjecucion)
    {
        if(strlen(usuario)>=6)
        {
            informarError(anchoLog/2+x-strlen(mensajeErrorUser)/2, y+3, mensajeErrorUser, 119);
        }
        if(strlen(clave)>=8)
        {
            informarError(anchoLog/2+x-strlen(mensajeErrorPass)/2, y+7, mensajeErrorPass, 119);
        }

        actualizarDatosLogin(anchoLog/2+x, y+2, y+6, usuario, clave, claveOculta);

        strcpy(usuarioIngresado.nickname,usuario);
        strcpy(usuarioIngresado.pass,clave);

        botones[(posY-botones[0].y)/altoBtn].seleccionado=1;
        pintarMenu(botones, cantBotones);
        gotoxy(posX, posY);
        tecla=getch();

        switch(tecla)
        {
        case '+':
            claveOculta=0;
            break;
        case '-':
            claveOculta=1;
            break;
        case 80:///ABAJO
            if(posY<altoBtn*(cantBotones-1)+botones[0].y+1)
            {
                posY+=altoBtn+1;
                if(posY>12)
                {
                    hidecursor(0);
                }
            }
            break;
        case 72:///ARRIBA
            if(posY>y+2)
            {
                posY-=altoBtn+1;
                if(posY<13)
                {
                    hidecursor(1);
                }
            }
            break;
        case 75:
        case 77:
            break;
        case 13:///ENTER
            if(posY==16)
            {
                informarError(anchoLog/2+x-strlen(mensajeErrorUser)/2, y+3, mensajeErrorUser, 119);
                if(strlen(usuario)>=6)
                {
                    if(strlen(clave)==8)
                    {
                        informarError(anchoLog/2+x-strlen(mensajeErrorPass)/2, y+7, mensajeErrorPass, 119);
                        botones[posY/4-4].funcionApertura(&usuarioIngresado);
                        enEjecucion=0;
                        borrarMenu();
                    }
                    else
                    {
                        informarError(anchoLog/2+x-strlen(mensajeErrorPass)/2, y+7, mensajeErrorPass, COLOR_ERROR_BLANCO);
                    }
                }
                else
                {
                    informarError(anchoLog/2+x-strlen(mensajeErrorUser)/2, y+3, mensajeErrorUser, COLOR_ERROR_BLANCO);
                }
            }
            else if(posY==20)
            {
                botones[posY/4-4].funcionApertura(NULL);
                enEjecucion=0;
                borrarMenu();
            }
            break;
        default:
            switch(posY)
            {
            case 8:
                hidecursor(1);
                validarEntradaUser(usuario, tecla);
                posX=anchoLog/2+x+strlen(usuario)/2;
                break;
            case 12:
                hidecursor(1);
                validarEntradaPass(clave, tecla);
                posX=anchoLog/2+x+strlen(clave)/2;
                break;
            default:
                hidecursor(0);
                break;
            }
            break;
        }
        for(int i=0; i<cantBotones; i++)
        {
            botones[i].seleccionado=0;
        }
    }
}

void validarLogin(Usuario usuarioIngresado)
{
    Usuario usuarioEncontrado;

    if(validarNicknameUsuario(usuarioIngresado.nickname, &usuarioEncontrado))
    {
        color(COLOR_BTN_LAT);
        if(strcmpi(usuarioIngresado.pass,usuarioEncontrado.pass)==0)
        {
            informacionEmergente("LOGUEADO");
            usuarioIngresado=usuarioEncontrado;
            if(strcmp(usuarioEncontrado.nickname, "punterodoble")==0)
            {
                color(22);
            }
            gotoxy(3,1);
            printf("                       ");
            gotoxy(14-strlen(usuarioIngresado.nombre)/2,1);
            printf("%s", usuarioIngresado.nombre);
            if(strcmp(usuarioEncontrado.nickname, "punterodoble")==0)
            {
                color(97);
            }
            gotoxy(3,2);
            printf("                       ");
            if(strcmp(usuarioEncontrado.nickname, "punterodoble")==0)
            {
                color(22);
            }
            gotoxy(3,3);
            printf("                       ");
            gotoxy(14-strlen(usuarioIngresado.nickname)/2,3);
            printf("%s", usuarioIngresado.nickname);
        }
        else
        {
            informacionEmergente("CLAVE INCORRECTA");
            login();
        }
    }
    else
    {
        informacionEmergente("USUARIO INCORRECTO");
        login();
    }
}

void registrarUsuario()
{

    int x=45;
    int y=1;
    int anchoLog=60;
    int altoLog=28;
    int altoBtn=3;

    pintarRecuadro(x,y, anchoLog, altoLog, COLOR_BTN_LAT);

    pintarRecuadro(x+2,y+1, anchoLog-4, altoBtn, COLOR_ESCRITURA);
    pintarRecuadro(x+2,y+5, anchoLog-4, altoBtn, COLOR_ESCRITURA);
    pintarRecuadro(x+2,y+9, anchoLog-4, altoBtn, COLOR_ESCRITURA);
    pintarRecuadro(x+2,y+13, anchoLog-4, altoBtn, COLOR_ESCRITURA);
    pintarRecuadro(x+2,y+17, anchoLog-4, altoBtn, COLOR_ESCRITURA);

    char usuario[30];
    char clave[9];
    char clave2[9];
    char nombre[30];
    int dni[9];

    limpiarString(usuario, 30);
    limpiarString(clave, 9);
    limpiarString(clave2, 9);
    limpiarString(nombre, 30);
    limpiarString(dni, 9);

    color(COLOR_DESABIL_BLANCO);

    int claveOculta=1;

    char mensajeErrorUser[]="minimo 6 caracteres";
    char mensajeErrorPass[]="minimo 8 caracteres";


    Usuario usuarioIngresado;

    int cantBotones=2;
    OpcionMenu botones[cantBotones];
    botones[0]=crearOpcionMenu("REGISTRARSE", 0, x+2, y+21, COLOR_BTN_SELEC_SUP, COLOR_VERDE, anchoLog-4, altoBtn, validarLogin, NULL, 1);
    botones[1]=crearOpcionMenu("CANCELAR", 0, x+2, y+24, COLOR_BTN_SELEC_SUP, COLOR_ROJO, anchoLog-4, altoBtn, registrarUsuario, NULL, 0);


    int posY=y+2;
    int posX=anchoLog/2+x+strlen(usuario)/2;
    int enEjecucion=1;
    char tecla;

    while(enEjecucion)
    {
        if(strlen(usuario)>=6)
        {
            informarError(anchoLog/2+x-strlen(mensajeErrorUser)/2, y+3, mensajeErrorUser, 119);
        }
        if(strlen(clave)>=8)
        {
            informarError(anchoLog/2+x-strlen(mensajeErrorPass)/2, y+7, mensajeErrorPass, 119);
        }

        actualizarDatosLogin(anchoLog/2+x, y+6, y+10, usuario, clave, claveOculta);
        actualizarDatosRegistro(anchoLog/2+x, y+2, y+14, y+18, nombre, clave2, dni, claveOculta);

        strcpy(usuarioIngresado.nickname,usuario);
        strcpy(usuarioIngresado.pass,clave);
        strcpy(usuarioIngresado.nombre, nombre);
        usuarioIngresado.dni=dniStringToInt(dni);

        botones[(posY-botones[0].y)/altoBtn].seleccionado=1;
        pintarMenu(botones, cantBotones);
        gotoxy(posX, posY);
        tecla=getch();

        switch(tecla)
        {
        case '+':
            claveOculta=0;
            break;
        case '-':
            claveOculta=1;
            break;
        case 80:///ABAJO
            if(posY<altoBtn*(cantBotones-1)+botones[0].y+1)
            {
                posY+=altoBtn+1;
                if(posY>19)
                {
                    hidecursor(0);
                }
            }
            break;
        case 72:///ARRIBA
            if(posY>y+2)
            {
                posY-=altoBtn+1;
                if(posY<20)
                {
                    hidecursor(1);
                }
            }
            break;
        case 77:
        case 75:
            _getch();
            break;
        case 13:///ENTER
            switch(posY)
            {
            case 23:
                if(validarRegistro(nombre, usuario, clave, clave2, dni))
                {
                    enEjecucion=0;
                    if(confirmarRegistrarUsuario(usuarioIngresado))
                    {
                        borrarMenu();
                        login();
                    }
                    else
                    {
                        borrarMenu();
                        registrarUsuario();
                    }

                }
                break;
            case 27:
                enEjecucion=0;
                borrarMenu();
                login();
                break;
            }
            break;
        default:
            switch(posY)
            {
            case 3:///Nombre
                hidecursor(1);
                validarEntradaLetras(nombre, tecla);
                posX=anchoLog/2+x+strlen(nombre)/2;
                break;
            case 7:///Usuario
                hidecursor(1);
                validarEntradaUser(usuario, tecla);
                posX=anchoLog/2+x+strlen(usuario)/2;
                break;
            case 11:///CLave
                hidecursor(1);
                validarEntradaPass(clave, tecla);
                posX=anchoLog/2+x+strlen(clave)/2;
                break;
            case 15:///Clave2
                hidecursor(1);
                validarEntradaPass(clave2, tecla);
                posX=anchoLog/2+x+strlen(clave2)/2;
                break;
            case 19:///Dni
                hidecursor(1);
                validarEntradaDni(dni, tecla);
                posX=anchoLog/2+x+strlen(dni)/2;
                break;
            default:
                hidecursor(0);
                break;
            }
            break;
        }
        for(int i=0; i<cantBotones; i++)
        {
            botones[i].seleccionado=0;
        }
    }
}

void actualizarDatosLogin(int xCentro, int yUser, int yPass, char user[], char pass[], int claveOculta)
{
    char mensajeUser[]="Ingrese su nombre de usuario";
    char mensajePass[]="Ingrese su clave  <+>ver  <->ocultar";
    char borrador[]="                                         ";
    color(COLOR_ESCRITURA);
    gotoxy(xCentro-strlen(borrador)/2, yUser);
    printf("%s",borrador);
    if(strlen(user)>0)
    {
        gotoxy(xCentro-strlen(user)/2, yUser);
        printf("%s", user);
    }
    else
    {
        gotoxy(xCentro-strlen(mensajeUser)/2, yUser);
        color(COLOR_DESABIL_BLANCO);
        printf("%s", mensajeUser);
    }

    color(COLOR_ESCRITURA);
    gotoxy(xCentro-strlen(borrador)/2, yPass);
    printf("%s", borrador);
    if(strlen(pass)>0)
    {
        gotoxy(xCentro-strlen(pass)/2, yPass);
        if(claveOculta)
        {
            for(int i=0; i<strlen(pass); i++)
            {
                printf("*");
            }
        }
        else
        {
            printf("%s", pass);
        }
    }
    else
    {
        gotoxy(xCentro-strlen(mensajePass)/2, yPass);
        color(COLOR_DESABIL_BLANCO);
        printf("%s", mensajePass);
    }
}

void actualizarDatosRegistro(int xCentro, int yNombre, int yPass2, int yDni, char nombre[], char pass2[], char dni[], int claveOculta)
{
    char mensajeNombre[]="Ingrese su nombre y apellido";
    char mensajePass2[]="Repita su clave    <+>ver  <->ocultar";
    char mensajeDni[]="Ingrese dni sin puntos ni guiones";
    char borrador[]="                                         ";
    color(COLOR_ESCRITURA);
    gotoxy(xCentro-strlen(borrador)/2, yNombre);
    printf("%s",borrador);
    if(strlen(nombre)>0)
    {
        gotoxy(xCentro-strlen(nombre)/2, yNombre);
        printf("%s", nombre);
    }
    else
    {
        gotoxy(xCentro-strlen(mensajeNombre)/2, yNombre);
        color(COLOR_DESABIL_BLANCO);
        printf("%s", mensajeNombre);
    }

    color(COLOR_ESCRITURA);
    gotoxy(xCentro-strlen(borrador)/2, yPass2);
    printf("%s", borrador);
    if(strlen(pass2)>0)
    {
        gotoxy(xCentro-strlen(pass2)/2, yPass2);

        if(claveOculta)
        {
            for(int i=0; i<strlen(pass2); i++)
            {
                printf("*");
            }
        }
        else
        {
            printf("%s", pass2);
        }
    }
    else
    {
        gotoxy(xCentro-strlen(mensajePass2)/2, yPass2);
        color(COLOR_DESABIL_BLANCO);
        printf("%s", mensajePass2);
    }

    color(COLOR_ESCRITURA);
    gotoxy(xCentro-strlen(borrador)/2, yDni);
    printf("%s", borrador);
    if(strlen(dni)>0)
    {
        gotoxy(xCentro-strlen(dni)/2, yDni);
        printf("%s", dni);
    }
    else
    {
        gotoxy(xCentro-strlen(mensajeDni)/2, yDni);
        color(COLOR_DESABIL_BLANCO);
        printf("%s", mensajeDni);
    }
}

///Recibe un arreglo de OpcionMenu, los pinta en la pantalla y permite recorrerlo de forma vertical
void menuVertical(OpcionMenu arregloBotones[], int cantMenu, void* arg, void* arg2)
{
    hidecursor(0);
    Alquiler alqui;
    int enEjecucion=1;
    int posicionInicioY=arregloBotones[0].y;
    int posicionY=posicionInicioY;
    int alturaElemento=arregloBotones[0].altura;
    char teclaPresionada;
    while(enEjecucion)
    {
        arregloBotones[(posicionY-arregloBotones[0].y)/alturaElemento].seleccionado=1;
        pintarMenu(arregloBotones, cantMenu);
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
            borrarContenido();
            if(arregloBotones[(posicionY-posicionInicioY)/alturaElemento].funcionApertura!=NULL)
            {
                arregloBotones[(posicionY-posicionInicioY)/alturaElemento].funcionApertura(arg);
            }
            enEjecucion=!arregloBotones[(posicionY-posicionInicioY)/alturaElemento].finaliza;
            break;
        case 27:///ESC

            borrarContenido();
            enEjecucion=0;
            gotoxy(0,ALTURA-4);
            break;
        }
        for(int i=0; i<cantMenu; i++)
        {
            arregloBotones[i].seleccionado=0;
        }
    }
}

int validarRegistro(char nombre[], char user[], char pass[], char pass2[], char dni[])
{
    int userValidado=0;
    int nombreValidado=validarNombre(nombre);
    int passValidado=validarPass(pass);
    int pass2Validado=validarPassDuplicado(pass, pass2);
    int dniValidado=0;

    if(!nombreValidado)
    {
        informarError(101, 3, "X", COLOR_ERROR_BLANCO);
    }
    else
    {
        informarError(101, 3, "V", COLOR_VALIDO_BLANCO);
    }

    if(strlen(user)>=6)
    {
        if(!existeNicknameUsuario(user))
        {
            userValidado=1;
            informarError(101, 7, "V", COLOR_VALIDO_BLANCO);
            informarError(66, 8, "                    ", COLOR_ERROR_BLANCO);
        }
        else
        {
            informarError(66, 8, "el usuario ya existe", COLOR_ERROR_BLANCO);
        }
    }
    else
    {
        informarError(101, 7, "X", COLOR_ERROR_BLANCO);
    }
    if(validarDni(dni))
    {
        if(!existeDniUsuario(dniStringToInt(dni)))
        {
            dniValidado=1;
            informarError(101, 19, "V", COLOR_VALIDO_BLANCO);
            informarError(68, 20, "                ", COLOR_ERROR_BLANCO);
        }
        else
        {
            informarError(68, 20, "el dni ya existe", COLOR_ERROR_BLANCO);
        }
    }
    else
    {
        informarError(101, 19, "X", COLOR_ERROR_BLANCO);
    }

    if(!passValidado)
    {
        informarError(101, 11, "X", COLOR_ERROR_BLANCO);
    }
    else
    {
        informarError(101, 11, "V", COLOR_VALIDO_BLANCO);
    }

    if(!pass2Validado)
    {
        informarError(101, 15, "X", COLOR_ERROR_BLANCO);
    }
    else
    {
        informarError(101, 15, "V", COLOR_VALIDO_BLANCO);
    }
    return(userValidado&&nombreValidado&&dniValidado&&passValidado&&pass2Validado);
}


///Recibe un arreglo de OpcionMenu, los pinta en la pantalla y permite recorrerlo de forma horizontal
void menuHorizontal(OpcionMenu arregloBotones[], int cantidadMenu, void *arg, void* arg2)
{
    pintarRecuadro(29,0, ANCHO-29, 5, COLOR_BTN_SUP);
    hidecursor(0);

    int enEjecucion=1;
    int anchoElemento=arregloBotones[0].ancho;
    int posicionX=arregloBotones[0].x;

    char teclaPresionada;
    while(enEjecucion)
    {
        arregloBotones[(posicionX-arregloBotones[0].x)/anchoElemento].seleccionado=1;
        pintarMenu(arregloBotones, cantidadMenu);
        ///gotoxy(posicionX, arregloBotones[0].y);
        teclaPresionada=getch();
        switch(teclaPresionada)
        {
        case 75:///IZQUIERDA
            if(posicionX>arregloBotones[0].x)
            {
                posicionX-=anchoElemento;
            }
            break;
        case 77:///DERECHA

            if(posicionX<arregloBotones[0].x+anchoElemento*(cantidadMenu-1))
            {
                posicionX+=anchoElemento;
            }
            break;
        case 27:///ESC
            enEjecucion=0;
            borrarMenu();
            break;
        case 13:///ENTER
            if(arregloBotones[(posicionX-arregloBotones[0].x)/anchoElemento].funcionApertura)
            {
                arregloBotones[(posicionX-arregloBotones[0].x)/anchoElemento].funcionApertura(arg);
            }
            break;
        }
        for(int i=0; i<cantidadMenu; i++)
        {
            arregloBotones[i].seleccionado=0;
        }
    }
}

int mensajeConfirmacion(char *mensaje)
{
    int respuesta=0;
    int cantBotones=2;
    OpcionMenu botones[cantBotones];

    cargarArregloBotonesConfirmacion(botones);

    int x=botones[0].x-2;
    int y=botones[0].y-3;
    int ancho=botones[0].ancho+4;
    int altura=botones[0].altura*(cantBotones)+4;
    int posicionTexto=(ancho/2-strlen(mensaje)/2)+x;


    pintarRecuadro(x,y, ancho, altura, botones[0].color);

    gotoxy(posicionTexto, y+1);

    printf("%s", mensaje);

    respuesta=menuEmergente(botones, cantBotones);

    return respuesta;
}

int menuEmergente(OpcionMenu arregloBotones[], int cantMenu)
{
    hidecursor(0);
    int enEjecucion=1;
    int posicionInicioY=arregloBotones[0].y;
    int posicionY=posicionInicioY;
    int alturaElemento=arregloBotones[0].altura;

    char teclaPresionada;
    int seleccionado=0;
    while(enEjecucion)
    {
        arregloBotones[(posicionY-arregloBotones[0].y)/alturaElemento].seleccionado=cantMenu-0;
        pintarMenu(arregloBotones, cantMenu);
        gotoxy(arregloBotones[0].x,posicionY);
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
        }
        for(int i=0; i<cantMenu; i++)
        {
            arregloBotones[i].seleccionado=0;
        }
    }
    return seleccionado;
}
