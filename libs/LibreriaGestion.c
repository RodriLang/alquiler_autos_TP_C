#include "LibreriaGestion.h"
///Pantalla NEGRA
void pantallaNegra(int X,int Y,int alturita,int anchito)
{
    color(15); ///Imprime una pantalla negra (color 15) para poder sobreescribir arriba de esta
    for(int i=0; i<alturita; i++) ///Alturita sera la cantidad de alto q imprimira o sea, de 0 a 5 ej
    {
        for(int j=0; j<=anchito; j++)///El ancho de la pantalla negra
        {
            gotoxy(X+j,Y+i); ///Avanzo con el gotoxy para imprimir la pantalla
            printf(" ");
        }
    }
    color(7); ///Vuelvo al color default
}
///Funcion Extra de Windows
void leerCadenaConLimiteTiempoReal(char* cadena, int limite)
{
    int contador = 0;
    char caracter;
    while (1)
    {
        caracter = _getch();///lee un solo carácter de la consola sin necesidad de presionar Enter.
        ///Esto es útil para capturar entradas de teclado de manera inmediata.
        if (caracter == '\r')///Si lo que presiono el usuario es Enter, Sale del while
        {
            break;
        }
        else if (caracter == '\b')///Backspace o delete, si el usuario ingresa eso por teclado
        {
            ///Borra lo ultimo que se ingreso mediante un printf con un caracter vacio
            if (contador > 0)
            {
                printf("\b \b");///Borra el caracter en la consola
                contador--;
            }
        }
        else if (caracter >= 32 && caracter <= 126)///Caracteres imprimibles
        {
            if (contador < limite) ///Mientras sea menor al limite que se le paso, se ejecuta
            {
                cadena[contador] = caracter; ///Guarda lo que se ingreso pasando por todas esas validaciones
                /// como el enter y el backspace y lo guarda
                printf("%c", caracter);///Muestra el caracter en la consola para simular que es en tiempo real
                contador++; ///Avanza
            }
        }
    }
    cadena[contador] = '\0'; // Termina la cadena y se le agrega el \0;
}
///Funciones De Menu
void menuCarga(int X,int Y)
{
    gotoxy(X,Y);
    menuLineas(X,Y+1,76,2);
    gotoxy(X+4,Y+1);
    printf("Por favor, Complete Los Siguientes Datos para Poder Cargar el Auto.");
    gotoxy(X+10,Y+2);
    printf("!El Ingreso Incorrecto de Datos no se podra guardar!");
    gotoxy(X,Y+3);
    gotoxy(X+7,Y+4);
    printf("Ingrese 3 Letras de La Patente:");
    gotoxy(X+7,Y+5);
    printf("Ingrese 3 Numeros de La Patente:");
    gotoxy(X+7,Y+6);
    printf("Ingrese Marca del Vehiculo:");
    gotoxy(X+7,Y+7);
    printf("Ingrese Modelo del Vehiculo:");
    gotoxy(X+7,Y+8);
    printf("Ingrese Anio del Vehiculo(2014-2024):");
    gotoxy(X+7,Y+9);
    printf("Ingrese KMS del Vehiculo(0-300000):");
    gotoxy(X+7,Y+10);
    printf("Ingrese Precio del Vehiculo:");
    gotoxy(X+7,Y+11);
    printf("Ingrese Tipo de Vehiculo(Auto,Camioneta y Utilitario):");
    for(int i=0; i<76; i++)
    {
        gotoxy(X+i,Y+12);
        printf("%c",196);
    }
}
void menuLineas(int X,int Y,int cantidad,int alturadeY)
{

    for(int i=0; i<cantidad; i++)
    {
        gotoxy(X+i,Y-1);
        printf("%c",196);
        gotoxy(X+i,Y+alturadeY);
        printf("%c",196);
    }
}
void cargaVehiculoControl(char* control)
{
    ///Implementacion de posicionamiento para el S/N
    int X=36,Y=20;
    menuLineas(X,Y+3,76,1);
    gotoxy(X+7,Y+3);
    printf("Desea Cargar Otro Vehiculo?S/N:");
    fflush(stdin);
    leerCadenaConLimiteTiempoReal(control, 1);
}
void mostrarArreglo(Vehiculo* unVehiculo, int validos)
{
    for (int i = 0; i < validos; i++)
    {
        printf("Patente %s %s\n",unVehiculo[i].patente.letras,unVehiculo[i].patente.numeros);
        printf("Marca: %s\n", unVehiculo[i].marca);
        printf("Modelo: %s\n", unVehiculo[i].modelo);
        printf("Anio: %i\n", unVehiculo[i].anio);
        printf("KMS: %i\n", unVehiculo[i].kms);
        printf("Disponibilidad: %i\n", unVehiculo[i].disponibilidad);
        printf("Precio de Alquiler Diario: %.2f\n", unVehiculo[i].precioDeAlquilerDiario);
        printf("Baja: %i\n", unVehiculo[i].baja);
        printf("Tipo de Vehiculo: %s\n", unVehiculo[i].tipoVehiculo);
    }
}
int menuModificacion(int posicionDeLaPatenteBuscada,int X,int Y)
{
    Patente patenteBuscado;
    pantallaNegra(X,Y-1,5,39);
    color(11);
    menuLineas(X,Y,40,3);
    gotoxy(X+1,Y);
    printf("Ingrese La Patente Que Desea Modificar");
    gotoxy(X+1,Y+1);
    printf("Letra de La Patente:");
    gotoxy(X+1,Y+2);
    printf("Numero de La Patente:");
    patenteBuscado=patenteVehiculo(X+21,Y+1,X+22,Y+2);
    posicionDeLaPatenteBuscada=buscarPosicionDeLaPatente(patenteBuscado);
    return posicionDeLaPatenteBuscada;
}
void impresionParaModificar(int X,int Y,Vehiculo unVehiculo)
{
    menuLineas(X-1,Y+1,59,10);
    gotoxy(X,Y+1);
    printf("Patente:%s %s",unVehiculo.patente.letras,unVehiculo.patente.numeros);
    gotoxy(X,Y+2);
    printf("1.Marca:%s", unVehiculo.marca);
    gotoxy(X,Y+3);
    printf("2.Modelo:%s", unVehiculo.modelo);
    gotoxy(X,Y+4);
    printf("3.Anio:%i", unVehiculo.anio);
    gotoxy(X,Y+5);
    printf("4.KMS:%i", unVehiculo.kms);
    gotoxy(X,Y+6);
    printf("5.Disponibilidad:%i", unVehiculo.disponibilidad);
    gotoxy(X,Y+7);
    printf("6.Precio de Alquiler Diario:%.2f", unVehiculo.precioDeAlquilerDiario);
    gotoxy(X,Y+8);
    printf("7.Baja:%i", unVehiculo.baja);
    gotoxy(X,Y+9);
    printf("8.Tipo de Vehiculo:%s", unVehiculo.tipoVehiculo);
    gotoxy(X,Y+10);
    printf("9.Salir");
    gotoxy(X,Y+12);
    printf("Seleccion:");
}
void parteSuperiorInferior(int X,int Y,int where,int yGotoxy,int segundo)
{
    ///WHERE sirve si imprimere lo de arriba o abajo
    if(where==1)
    {
        gotoxy(X+25,Y);
        color(11);
        printf("Listado de Vehiculos:\n");
        gotoxy(X,Y+2);
        printf("| %-15s | %-20s | %-7s | %-10s | %-7s |\n", "Marca", "Modelo", "Patente", "Tipo", "Anio");
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
    else if(where==0 && segundo == 2) ///Esto imprimira cuando le dee enter para ver toda la info
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
void impresionCUADRO(int X,int Y)
{
    pantallaNegra(X,Y,11,40);
    color(11);
    for(int i=0; i<41; i++)
    {
        gotoxy(X+i,Y);
        printf("%c",196);
        gotoxy(X+i,Y+9);
        printf("%c",196);
    }
}
void imprimirTexto1(int X,int Y)
{
    gotoxy(X+1,Y+1);
    printf("Patente:");
    gotoxy(X+1,Y+2);
    printf("Marca:");
    gotoxy(X+1,Y+3);
    printf("Modelo:");
    gotoxy(X+1,Y+4);
    printf("Anio:");
    gotoxy(X+1,Y+5);
    printf("KMS:");
    gotoxy(X+1,Y+6);
    printf("Precio Diario:");
    gotoxy(X+1,Y+7);
    printf("Tipo Vehiculo:");
    gotoxy(X+1,Y+8);
    printf("Disponibilidad:");
}
void imprimirUnVehiculo(Vehiculo unVehiculo)
{

    int X=55,Y=10;
    impresionCUADRO(X,Y);
    imprimirTexto1(X,Y);
    gotoxy(X+17,Y+1);
    printf("%s %s", unVehiculo.patente.letras, unVehiculo.patente.numeros);
    gotoxy(X+17,Y+2);
    printf("%s", unVehiculo.marca);
    gotoxy(X+17,Y+3);
    printf("%s", unVehiculo.modelo);
    gotoxy(X+17,Y+4);
    printf("%d", unVehiculo.anio);
    gotoxy(X+17,Y+5);
    printf("%d", unVehiculo.kms);
    gotoxy(X+17,Y+6);
    printf("%.2f", unVehiculo.precioDeAlquilerDiario);
    gotoxy(X+17,Y+7);
    printf("%s", unVehiculo.tipoVehiculo);
    gotoxy(X+17,Y+8);
    printf("%i", unVehiculo.disponibilidad);
    gotoxy(X+1,Y+10);
    system("pause");
}
void mostrarTodaLaInformacion(int posicion)
{
    Vehiculo unVehiculo;
    FILE *archi=fopen("ArchivoAutos","rb");
    if(archi!=NULL)
    {
        fseek(archi,posicion*sizeof(Vehiculo),SEEK_SET);
        fread(&unVehiculo,sizeof(Vehiculo),1,archi);
        imprimirUnVehiculo(unVehiculo);
        color(176);
        fclose(archi);
    }
    else
    {
        informacionEmergente();
    }
}
///Funciones de validación
void convertirAMayusculas(char *cadena)
{
    for (int i = 0; cadena[i] != '\0'; i++)
    {
        cadena[i] = toupper(cadena[i]);
    }
}
void removerSaltoDeLinea(char *cadena)
{
    int longitud = strlen(cadena);
    if (longitud > 0 && cadena[longitud - 1] == '\n')
    {
        cadena[longitud - 1] = '\0';
    }
}

int esNumeroValido(char* str)
{
    if (str == NULL || *str == '\0' || isspace(*str))///Verifica que no sea vacio,el ultimo verifica que no se
    {
        ///ingrese con un espacio en blanco
        return 0;
    }
    char* endptr;
    strtol(str, &endptr, 10); ///Convertir string a entero base 10
    ///Guarda en endptr lo que no es un numero
    return *endptr == '\0'; ///Si esta vacio, es por q solo hubo letras, y devolvera 0
}

int esNumeroFlotanteValido(char* str)
{
    if (str == NULL || *str == '\0' || isspace(*str))///Verifica que no sea vacio,el ultimo verifica que no se
    {
        ///ingrese con un espacio en blanco
        return 0;
    }
    char* endptr;
    strtof(str, &endptr);///Lo convierte en flotante
    return *endptr == '\0';
}

int esLetra(char *str)
{
    if (strlen(str) != 3) ///Solo necesito 3 letras de la patente, a si que si no es 3, ingreso mal
    {
        return 0;
    }
    for (int i = 0; i < 3; i++)
    {
        if (!isalpha(str[i]))  ///Si no es una letra devuelve 0
        {
            return 0;
        }
    }
    return 1;
}
int validarTipoDeVehiculo(char *tipoDeVehiculo)
{
    if (strcmpi(tipoDeVehiculo, "Auto") == 0 || strcmpi(tipoDeVehiculo, "Camioneta") == 0 || strcmpi(tipoDeVehiculo, "Utilitario") == 0)
    {
        return 1; // Es válido
    }
    return 0; // No es válido
}

int esNumero(char *str)
{
    if (strlen(str) != 3)
    {
        return 0;
    }
    for (int i = 0; i < 3; i++)
    {
        if (!isdigit(str[i])) ///Si no es un numero devuelve 0
        {
            return 0;
        }
    }
    return 1;
}
int esSoloLetrasNumeros(char *str)
{
    ///VERIFICA QUE LA CADENA SOLAMENTE CONTENGA NUMEROS Y LETRAS, NO IMPORTA SI 3 O MAS.
    ///POR ESO ES UNA FUNCION APARTE DE SUS OTRAS 2 CASI IGUALES

    ///Verificar si la cadena es nula o si solo contiene espacios en blanco
    if (str == NULL || str[0] == '\0' || strspn(str, " ") == strlen(str))
    {
        return 0; ///Cadena inválida
    }

    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(str[i]) && !isdigit(str[i]) && str[i] != ' ')
        {
            return 0;///Cadena inválida
        }
    }
    return 1; // Cadena válida
}
void convertirAMayusculaMinuscula(char *cadena)
{
    ///PARA QUE EL TIPO DE AUTO ESTE BIEN ESCRITO

    int i = 0;
    // Convierte la primera letra en mayúscula
    cadena[i] = toupper(cadena[i]);
    i++;
    // Convierte el resto de la cadena en minúsculas
    while (cadena[i] != '\0')
    {
        cadena[i] = tolower(cadena[i]);
        i++;
    }
}
int buscarPosicionDeLaPatente(Patente patenteBuscado)
{
    int indice=0,posicion=-1;
    int cantidad=cantidadDeRegistros("ArchivoAutos");
    Vehiculo *auxiliarVehiculos=(Vehiculo*)malloc(cantidadDeRegistros("ArchivoAutos")*sizeof(Vehiculo));
    FILE *archi=fopen("ArchivoAutos","rb");
    if(archi != NULL)
    {
        fread(auxiliarVehiculos, sizeof(Vehiculo), cantidadDeRegistros("ArchivoAutos"), archi);
        fclose(archi);
    }
    else
    {
        informacionEmergente();
    }
    if (auxiliarVehiculos != NULL)
    {
        while(indice<cantidadDeRegistros("ArchivoAutos"))
        {
            if(strcmpi(auxiliarVehiculos[indice].patente.letras,patenteBuscado.letras)==0&&strcmpi(auxiliarVehiculos[indice].patente.numeros,patenteBuscado.numeros)==0)
            {
                posicion=indice;
                break;
            }
            indice++;
        }
    }
    else
    {
        posicion=-2;
    }
    free(auxiliarVehiculos);
    return posicion;
}
int verificarPatenteEnArchivoYArreglo(char *letras, char *numeros, Vehiculo *vehiculos, int cantidadVehiculos)
{
    FILE *archi = fopen("ArchivoAutos", "rb");
    if (archi != NULL)
    {
        Vehiculo temp;
        while (fread(&temp, sizeof(Vehiculo), 1, archi))
        {
            if (strcmp(temp.patente.letras, letras) == 0 && strcmp(temp.patente.numeros, numeros) == 0)
            {
                fclose(archi);
                return 1; // La patente ya existe en el archivo
            }
        }
        fclose(archi);
    }
    for (int i = 0; i < cantidadVehiculos; i++)
    {
        if (strcmp(vehiculos[i].patente.letras, letras) == 0 && strcmp(vehiculos[i].patente.numeros, numeros) == 0)
        {
            return 1; // La patente ya existe en el arreglo
        }
    }
    return 0; // La patente no existe
}
int cantidadDeRegistros(char nombreDeArchivo[])
{
    long cantidadBytes;
    int cantidad;
    FILE *archi=fopen(nombreDeArchivo,"rb");
    if(archi!=NULL)
    {
        fseek(archi,0,SEEK_END);
        cantidadBytes=ftell(archi);
        cantidad= cantidadBytes / sizeof(Vehiculo);
        fclose(archi);
    }
    else
    {
        informacionEmergente();
    }
    return cantidad;
}
int cantidadDisponible()
{
    FILE *archivo = fopen("ArchivoAutos", "rb");
    if (!archivo)
    {
        informacionEmergente();
        return 0;
    }
    Vehiculo vehiculo;
    int cantidad = 0;

    while (fread(&vehiculo, sizeof(Vehiculo), 1, archivo) > 0)
    {
        if (vehiculo.disponibilidad == 1)
        {
            cantidad++;
        }
    }
    fclose(archivo);
    return cantidad;
}
// Funciones de cargaF
void cargarLetraPatente(char* letras,int X,int Y)
{
    char *entrada = (char *)malloc(10* sizeof(char));
    ///PARA VERIFICAR SI O SI LO TENGO Q PASAR A UNA CADENA A SI ES MAS FACIL
    ///Se realiza usando memoria dinamica.
    do
    {
        gotoxy(X,Y);
        leerCadenaConLimiteTiempoReal(entrada, 3);
        removerSaltoDeLinea(entrada); ///Verificacion por las dudas
        if (strlen(entrada) == 3 && esLetra(entrada)) ///SOLO SI ES TRUE
        {
            convertirAMayusculas(entrada);
            strcpy(letras, entrada);
            break;
        }
        else
        {
            ///SI NO SE PUEDE, VUELVE DONDE EMPEZO A ESCRIBIR EL USUARIO BORRANDO LO ANTERIOR
            gotoxy(X,Y);
            printf("            "); // Borra la línea anterior
            gotoxy(X,Y);
        }
    }
    while (1);
    free(entrada); ///libera la memoria
}

void cargarNumeroPatente(char *numero,int X,int Y)
{
    char *entrada = (char *)malloc(10 * sizeof(char));
    do
    {
        gotoxy(X,Y);
        leerCadenaConLimiteTiempoReal(entrada, 3);
        removerSaltoDeLinea(entrada);
        if (strlen(entrada) == 3 && esNumero(entrada))
        {
            strcpy(numero, entrada);

            break;
        }
        else
        {
            gotoxy(X,Y);
            printf("            "); // Borra la línea anterior
            gotoxy(X,Y);
        }
    }
    while (1);
    free(entrada);
}

Patente patenteVehiculo(int X,int Y,int X2,int Y2)
{
    Patente patenteCarga;
    cargarLetraPatente(patenteCarga.letras,X,Y);
    cargarNumeroPatente(patenteCarga.numeros,X2,Y2);
    return patenteCarga; ///Obtiene el dato patente
}

void marcaVehiculo(char* marca,int X,int Y)
{
    int control=0;
    while(control==0)
    {
        fflush(stdin);
        gotoxy(X,Y);
        leerCadenaConLimiteTiempoReal(marca, 19);
        removerSaltoDeLinea(marca);
        if (esSoloLetrasNumeros(marca)==1)
        {
            control=1;///Se Pudo Leer
        }
        else
        {
            gotoxy(X,Y);
            printf("                               "); // Borra la línea anterior
            gotoxy(X,Y);
        }
    }
    fflush(stdin);
}

void modeloVehiculo(char* modelo,int X,int Y)
{
    int control=0;
    while(control==0)
    {
        fflush(stdin);
        gotoxy(X,Y);
        leerCadenaConLimiteTiempoReal(modelo, 19);
        removerSaltoDeLinea(modelo);
        if (esSoloLetrasNumeros(modelo)==1)
        {
            control=1;///Se Pudo Leer
        }
        else
        {
            gotoxy(X,Y);
            printf("                               "); // Borra la línea anterior
            gotoxy(X,Y);
        }
    }
    fflush(stdin);
}
void anioVehiculo(int* anioCargar,int X,int Y)
{
    char *entrada=(char*)malloc(20*sizeof(char));
    int flag = 0;
    while (flag == 0)
    {
        gotoxy(X,Y);
        leerCadenaConLimiteTiempoReal(entrada, 4);
        removerSaltoDeLinea(entrada);
        if (esNumeroValido(entrada))
        {
            *anioCargar = atoi(entrada); ///Transforma los numeros de la string a un int
            if (*anioCargar >= 2014 && *anioCargar <= 2024)
            {
                flag = 1; ///Si cumple el año sale del bucle
            }
            else
            {
                gotoxy(X,Y);
                printf("     "); // Borra la línea anterior
                gotoxy(X,Y);
            }
        }
        else
        {
            gotoxy(X,Y);
            printf("     "); // Borra la línea anterior
            gotoxy(X,Y);
        }
    }
    free(entrada);
}

void kmsVehiculo(int* kmsCargado,int X,int Y)
{
    char *entrada=(char*)malloc(20*sizeof(char));
    int flag = 0;
    while (flag == 0)
    {
        gotoxy(X,Y);
        leerCadenaConLimiteTiempoReal(entrada, 6);
        removerSaltoDeLinea(entrada);
        if (esNumeroValido(entrada))
        {
            *kmsCargado = atoi(entrada);
            if (*kmsCargado >= 0 && *kmsCargado <= 300000)
            {
                flag = 1;
            }
            else
            {
                gotoxy(X,Y);
                printf("        "); // Borra la línea anterior
                gotoxy(X,Y);
            }
        }
        else
        {
            gotoxy(X,Y);
            printf("        "); // Borra la línea anterior
            gotoxy(X,Y);
        }
    }
    free(entrada);
}

void precioVehiculo(float* precioDiario,int X,int Y)
{
    char *entrada=(char*)malloc(15*sizeof(char));
    int flag = 0;
    while (flag == 0)
    {
        gotoxy(X,Y);
        leerCadenaConLimiteTiempoReal(entrada, 10);
        removerSaltoDeLinea(entrada);
        if (esNumeroFlotanteValido(entrada))
        {
            *precioDiario = strtof(entrada, NULL);
            if (*precioDiario >= 0.0 && *precioDiario <= 1000000.0)
            {
                flag = 1;
            }
            else
            {
                gotoxy(X,Y);
                printf("          "); // Borra la línea anterior
                gotoxy(X,Y);
            }
        }
        else
        {
            gotoxy(X,Y);
            printf("          "); // Borra la línea anterior
            gotoxy(X,Y);
        }
    }
}
void obtenerTipoDeVehiculo(char *tipoDeVehiculo,int X,int Y)
{
    char *entrada=(char*)malloc(15*sizeof(char));
    int valido = 0;
    while (valido==0)
    {
        gotoxy(X,Y);
        leerCadenaConLimiteTiempoReal(entrada, 10);
        removerSaltoDeLinea(entrada);
        // Transforma la primera letra en mayúscula y el resto en minúsculas
        valido = validarTipoDeVehiculo(entrada);
        if (valido==1)
        {
            convertirAMayusculaMinuscula(entrada);
            strcpy(tipoDeVehiculo,entrada);
        }
        else
        {
            gotoxy(X,Y);
            printf("            "); // Borra la línea anterior
            gotoxy(X,Y);
        }
    }
}
void disponibilidadVehiculo(int* disponibilidad,int X,int Y)
{
    char entrada[2];
    int temp;
    do
    {
        gotoxy(X,Y);
        leerCadenaConLimiteTiempoReal(entrada, 1);
        if (entrada[0] != '1' && entrada[0] != '0' || entrada[0]=='\0')
        {
            gotoxy(X,Y);
            printf("   ");
            gotoxy(X,Y);
        }
    }
    while (entrada[0] != '1' && entrada[0] != '0'||entrada[0]=='\0');
    temp = atoi(entrada);
    *disponibilidad = temp;
}
void bajaVehiculo(int* bajaCarga,int X,int Y)
{
    char entrada[2];///Consideramos solo un carácter más el terminador nulo
    int temp;
    do
    {
        gotoxy(X,Y);
        leerCadenaConLimiteTiempoReal(entrada, 1); ///Lee solo un carácter
        if (entrada[0] != '1' && entrada[0] != '0' || entrada[0]=='\0')
        {
            ///Borra la línea anterior
            gotoxy(X,Y);
            printf("   ");
            gotoxy(X,Y);
        }
    }
    while (entrada[0] != '1' && entrada[0] != '0'||entrada[0]=='\0');
    temp = atoi(entrada);
    *bajaCarga = temp;
}
Vehiculo cargarUnVehiculo()
{
    int X=36,Y=8; ///Posicion general del gotoxy,
    pantallaNegra(X,Y,13,75);
    Vehiculo unVehiculo;
    color(11);
    menuCarga(X,Y);
    unVehiculo.patente = patenteVehiculo(X+38,Y+4,X+39,Y+5);
    marcaVehiculo(unVehiculo.marca,X+34,Y+6);
    modeloVehiculo(unVehiculo.modelo,X+35,Y+7);
    anioVehiculo(&unVehiculo.anio,X+44,Y+8);
    kmsVehiculo(&unVehiculo.kms,X+42,Y+9);
    precioVehiculo(&unVehiculo.precioDeAlquilerDiario,X+35,Y+10);
    obtenerTipoDeVehiculo(unVehiculo.tipoVehiculo,X+61,Y+11);
    unVehiculo.disponibilidad = 1;
    unVehiculo.baja = 1;
    return unVehiculo;
}

void agregarVehiculo()
{
    char control = 's';
    Vehiculo *vehiculos = NULL;
    int cantidadVehiculos = 0;
    while (control == 's' || control == 'S')
    {
        Vehiculo unVehiculo = cargarUnVehiculo();
        /// Verificar si la patente ya existe en el archivo o en el arreglo dinámico
        if (verificarPatenteEnArchivoYArreglo(unVehiculo.patente.letras, unVehiculo.patente.numeros, vehiculos, cantidadVehiculos))
        {
            pantallaNegra(36, 21, 4, 75);
            color(11);
            gotoxy(43, 21);
            printf("La patente ingresada ya existe.");
        }
        else
        {
            vehiculos = realloc(vehiculos, (cantidadVehiculos + 1) * sizeof(Vehiculo));
            vehiculos[cantidadVehiculos] = unVehiculo;
            cantidadVehiculos++;
            pantallaNegra(36, 21, 4, 75);
            color(11);
            gotoxy(43, 21);
            printf("Vehiculo agregado exitosamente.");
        }
        color(11);
        cargaVehiculoControl(&control);
        color(176);
    }
    ///Guardar todos los vehículos en el archivo una vez finalizada la carga
    FILE *archi = fopen("ArchivoAutos", "ab");
    if (archi != NULL)
    {
        fwrite(vehiculos, sizeof(Vehiculo), cantidadVehiculos, archi);
        fclose(archi);
    }
    else
    {
        informacionEmergente();
    }
    free(vehiculos);
    fflush(stdin);
    ///Necesario por q no se puede guardar si no.
    FILE *lectura = fopen("ArchivoAutos", "rb");
    if (lectura != NULL)
    {
        fclose(lectura);
    }
    else
    {
        informacionEmergente();
    }
    borrarSeccion(36,8,76,17);
}
///Funciones de modificacion
Vehiculo seleccionModificacion(int seleccion,Vehiculo unVehiculo)
{
    int X=45,Y=8;
    pantallaNegra(X-1,Y,13,58);
    color(11);
    char seleccionCadena[2]; // Solo necesitamos espacio para un dígito y el terminador nulo
    while(seleccion!=9)
    {
        impresionParaModificar(X,Y,unVehiculo);
        fflush(stdin);
        leerCadenaConLimiteTiempoReal(seleccionCadena, 1);
        sscanf(seleccionCadena, "%i", &seleccion); ///Transforma lo q se ingreso en seleccionCadena
        ///A un entero en seleccion
        fflush(stdin);
        switch(seleccion)
        {
        case 1:
            gotoxy(X+strlen("1.Marca:"), Y+2); // Posición donde está impresa la marca
            printf("                                         "); // Borra el texto de la marca
            fflush(stdin);
            marcaVehiculo(unVehiculo.marca,X+strlen("1.Marca:"),Y+2);
            fflush(stdin);
            break;
        case 2:
            gotoxy(X+strlen("2.Modelo:"), Y+3); // Posición donde está impresa la marca
            printf("                                         "); // Borra el texto de la marca
            fflush(stdin);
            modeloVehiculo(unVehiculo.modelo,X+strlen("2.Modelo:"), Y+3);
            fflush(stdin);
            break;
        case 3:
            gotoxy(X+strlen("3.Anio:"), Y+4); // Posición donde está impresa la marca
            printf("                                         "); // Borra el texto de la marca
            fflush(stdin);
            anioVehiculo(&unVehiculo.anio,X+strlen("3.Anio:"), Y+4);
            break;
        case 4:
            gotoxy(X+strlen("4.KMS:"), Y+5); // Posición donde está impresa la marca
            printf("                                         "); // Borra el texto de la marca
            fflush(stdin);
            kmsVehiculo(&unVehiculo.kms,X+strlen("4.KMS:"), Y+5);
            break;
        case 5:
            gotoxy(X+strlen("5.Disponibilidad:"), Y+6); // Posición donde está impresa la marca
            printf("                     "); // Borra el texto de la marca
            fflush(stdin);
            disponibilidadVehiculo(&unVehiculo.disponibilidad,X+strlen("5.Disponibilidad:"), Y+6);
            break;
        case 6:
            gotoxy(X+strlen("6.Precio de Alquiler Diario:"), Y+7); // Posición donde está impresa la marca
            printf("                     "); // Borra el texto de la marca
            precioVehiculo(&unVehiculo.precioDeAlquilerDiario,X+strlen("6.Precio de Alquiler Diario:"), Y+7);
            break;
        case 7:
            gotoxy(X+strlen("7.Baja:"), Y+8); // Posición donde está impresa la marca
            printf("                                         "); // Borra el texto de la marca
            bajaVehiculo(&unVehiculo.baja,X+strlen("7.Baja:"), Y+8);
            break;
        case 8:
            gotoxy(X+strlen("8.Tipo de Vehiculo:"), Y+9); // Posición donde está impresa la marca
            printf("                     "); // Borra el texto de la marca
            obtenerTipoDeVehiculo(&unVehiculo.tipoVehiculo,X+strlen("8.Tipo de Vehiculo:"), Y+9);
            break;
        case 9:
            return unVehiculo;
        default:
            seleccion=0;
            gotoxy(X+strlen("Seleccion:"), Y+12); // Posición donde está impresa la marca
            printf("                         "); // Borra el texto de la marca
        }
        seleccion=0;
        gotoxy(X+strlen("Seleccion:"), Y+12); // Posición donde está impresa la marca
        printf("                         ");
        fflush(stdin);
    }
}
void modificarVehiculo()
{
    int posicionDeLaPatenteBuscada,X=50,Y=8;
    posicionDeLaPatenteBuscada=menuModificacion(posicionDeLaPatenteBuscada,X,Y);

    if(posicionDeLaPatenteBuscada==-1)
    {
        pantallaNegra(X,Y+4,2,39);
        gotoxy(X+1,Y+4);
        printf("La Patente Ingresada No Existe\n");
        gotoxy(X,Y+5);
        system("pause");
        borrarSeccion(X,Y-1,40,7);
    }
    else if(posicionDeLaPatenteBuscada==-2)
    {
        pantallaNegra(X,Y+4,2,39);
        color(11);
        gotoxy(X+1,Y+4);
        printf("No Hay Vehiculos Cargados\n");
        gotoxy(X,Y+5);
        system("pause");
        borrarSeccion(X,Y-1,40,7);
    }
    else
    {
        borrarSeccion(X,Y-1,40,7);
        FILE *archi=fopen("ArchivoAutos","r+b");
        Vehiculo unVehiculo;
        int seleccion=0;
        if(archi!=NULL)
        {
            fseek(archi,posicionDeLaPatenteBuscada*sizeof(Vehiculo),SEEK_SET);
            fread(&unVehiculo,sizeof(Vehiculo),1,archi);
            unVehiculo=seleccionModificacion(seleccion,unVehiculo);
            fseek(archi,-sizeof(Vehiculo),SEEK_CUR);
            fwrite(&unVehiculo,sizeof(Vehiculo),1,archi);
            borrarSeccion(44,8,59,13);
            fclose(archi);
        }
        else
        {
         informacionEmergente();
        }
    }

}

void verListadoVehiculos(int numeroDeColor, int inicio, int cantidad)
{
    int yGotoxy = 0;
    int maximoDeAutosImpresos=4;
    int X = 37, Y = 10;
    if (cantidad > 0)
    {
        Vehiculo *vehiculos = (Vehiculo*)malloc(cantidad * sizeof(Vehiculo));
        FILE *archi = fopen("ArchivoAutos", "rb");
        if (archi != NULL)
        {
            fread(vehiculos, sizeof(Vehiculo), cantidad, archi);
            fclose(archi);
            parteSuperiorInferior(X, Y, 1, 0, 0);
            for (int i = 0; i < maximoDeAutosImpresos && (inicio + i) < cantidad; i++)   ///Inici + i es para
            {
                ///que se imprima de 4 en 4, y avance
                if ((inicio + i) == numeroDeColor)   ///SI coincide se imprime a color
                {
                    gotoxy(X, (Y + maximoDeAutosImpresos) + i);
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
                }
                else
                {
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
            parteSuperiorInferior(X, Y, 0, yGotoxy, 0); ///Gotoxy es para saber en q posicion imprimir la parte inferior

        }
        else
        {
        informacionEmergente();
        }
        free(vehiculos);
    }
    else
    {
        informacionEmergente();
    }
}

void menuListadoVehiculos()
{
    int enEjecucion = 1, posicionY = 10, posicionX = 38, seleccion = 0, colorInteractivo = 0, cantidad = cantidadDeRegistros("ArchivoAutos");
    int inicio = 0;
    char teclaPresionada;
    pantallaNegra(37, 10, 11, 74);
    while (enEjecucion)
    {
        verListadoVehiculos(colorInteractivo, inicio, cantidad); ///Se imprime cada vez el arreglo
        /// y cuando i coincide con color se imprime de color
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
                if (colorInteractivo >= inicio + 4)
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
        case 13: // Enter para seleccionar
            seleccion = colorInteractivo;
            //borrarSeccion(37, 10, 75, 7 + cantidad);
            borrarContenido();
            mostrarTodaLaInformacion(seleccion); ///Seleccion seria la posicion del auto a mostrar
            borrarContenido();
            //borrarSeccion(37, 10, 75, 7 + cantidad);
            pantallaNegra(37, 10, 11, 74);
            break;
        case 27: // Esc para salir
            enEjecucion = 0;
            borrarContenido();
            ///borrarSeccion(37, 10, 75, 7 + cantidad);
            gotoxy(0, posicionY + cantidad + 1);
            break;
        }
    }
}

Vehiculo* obtenerVehiculosDisponibles(int *cantidadDisponibles)
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
                if(vehiculosDisponibles[*cantidadDisponibles].disponibilidad==1&&vehiculosDisponibles[*cantidadDisponibles].baja==1)
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
          informacionEmergente();
             *cantidadDisponibles = 0;
            return NULL;
        }
    }
    else
    {
        informacionEmergente();
        *cantidadDisponibles = 0;
        return NULL;
    }
}

void verListadoVehiculosDisponibles(int inicio, int cantidadPagina, int numeroDeColor)
{
    int yGotoxy = 0;
    int cantidadDisponible = 0;
    Vehiculo *vehiculos = obtenerVehiculosDisponibles(&cantidadDisponible);
    int X = 37, Y = 10;
    if (cantidadDisponible > 0)
    {
        parteSuperiorInferior(X, Y, 1, 0, 0);
        for (int i = 0; i < cantidadPagina && (inicio + i) < cantidadDisponible; i++)
        {
            if (inicio + i == numeroDeColor)
            {
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
            }
            else
            {
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
    }
    else
    {
        informacionEmergente();
    }
}

void menuListadoVehiculosDisponibles()
{
    int enEjecucion = 1, posicionY = 10, posicionX = 38, colorInteractivo = 0, cantidad = cantidadDisponible();
    int inicio = 0;
    int cantidadPagina = 4;///Número de vehículos a mostrar por página
    char teclaPresionada;
    pantallaNegra(37, 10, 11, 74);
    while (enEjecucion)
    {
        verListadoVehiculosDisponibles(inicio, cantidadPagina, colorInteractivo);
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
            borrarContenido();
            //borrarSeccion(37, 10, 75, 7 + cantidad);
            gotoxy(0, posicionY + cantidad + 1);
            break;
        }
    }
}
