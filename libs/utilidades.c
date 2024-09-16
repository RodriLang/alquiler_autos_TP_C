#include <ctype.h>
#include "utilidades.h"
#include "interfazUsuario.h"

int obtenerAnioActual()
{
    time_t tiempo_actual = time(NULL);
    struct tm *tm_info = localtime(&tiempo_actual);
    int anio_actual = tm_info->tm_year + 1900;
    return anio_actual;
}

Fecha obtenerFechaActual()
{
    char fechaStr[11];
    // Obtenemos el tiempo actual
    time_t t = time(NULL);
    // Convertimos el tiempo a una estructura tm
    struct tm *tm_info = localtime(&t);

    // Formateamos la fecha en la cadena de caracteres
    strftime(fechaStr, sizeof(fechaStr), "%d/%m/%Y", tm_info);
    // Convertimos a tipo Fecha
    return stringToFecha(fechaStr);
}

int compararFecha(Fecha fecha1, Fecha fecha2) //retorna 1 si el primero es mayor, -1 si el primero es menor, 0 son iguales
{
    int comparacion=0;
    //if(compararNumeros())
    if(fecha1.anio>fecha2.anio)
    {
        comparacion=1;
    }
    else if(fecha1.anio<fecha2.anio)
    {
        comparacion=-1;
    }
    else if(fecha1.mes>fecha2.mes)
    {
        comparacion=1;
    }
    else if(fecha1.mes<fecha2.mes)
    {
        comparacion=-1;
    }
    else if(fecha1.dia>fecha2.dia)
    {
        comparacion=1;
    }
    else if(fecha1.dia<fecha2.dia)
    {
        comparacion=-1;
    }
    return comparacion;
}

int compararNumeros(int e1, int e2) //retorna 1 si el primero es mayor, -1 si el primero es menor, 0 son iguales
{
    int comparacion=0;
    if(e1>e2)
    {
        comparacion=1;
    }
    else if(e1<e2)
    {
        comparacion=-1;
    }
    return comparacion;
}

int diasEntreFechas(Fecha fechaAnt, Fecha fechaPos)
{
    int cantTotalDias=0;
    int diaInicio=fechaAnt.dia;
    int mesInicio=fechaAnt.mes;
    int anioInicio=fechaAnt.anio;
    while(anioInicio<=fechaPos.anio)
    {
        if(anioInicio<fechaPos.anio)
        {
            while(mesInicio<=12)
            {
                while(diaInicio<=cantDiasSegunMes(mesInicio, anioInicio))
                {
                    diaInicio++;
                    cantTotalDias++;
                }
                if(diaInicio>cantDiasSegunMes(mesInicio, anioInicio))
                {
                    diaInicio=1;
                }
                mesInicio++;
            }
        }
        else
        {
            while(mesInicio<=fechaPos.mes&&mesInicio<=12)
            {
                if(mesInicio<fechaPos.mes)
                {
                    while(diaInicio<=cantDiasSegunMes(mesInicio, anioInicio))
                    {
                        diaInicio++;
                        cantTotalDias++;
                    }
                }
                else
                {
                    while(diaInicio<=cantDiasSegunMes(mesInicio, anioInicio)&&diaInicio<fechaPos.dia)
                    {
                        diaInicio++;
                        cantTotalDias++;
                    }
                }
                if(diaInicio>cantDiasSegunMes(mesInicio, anioInicio))
                {
                    diaInicio=1;
                }
                mesInicio++;
            }
        }
        if(mesInicio>12)
        {
            mesInicio=1;
        }
        anioInicio++;
    }
    return cantTotalDias;
}

int compararPatente(Patente p, Patente p2) //retorna 1 si el primero es mayor, -1 si el primero es menor, 0 son iguales
{
    int comparacion=0;
    if(strcmpi(p.letras, p2.letras)>0)
    {
        comparacion=1;
    }
    else if(strcmpi(p.letras, p2.letras)<0)
    {
        comparacion=-1;
    }
    else if(strcmpi(p.numeros, p2.numeros)>0)
    {
        comparacion=1;
    }
    else if(strcmpi(p.numeros, p2.numeros)<0)
    {
        comparacion=-1;
    }
    return comparacion;
}

Fecha stringToFecha(char fechaString[])
{
    Fecha fecha;
    if(validarFormatoFecha(fechaString))
    {
        fecha.dia=(fechaString[0]-48)*10+(fechaString[1]-48);
        fecha.mes=(fechaString[3]-48)*10+(fechaString[4]-48);
        fecha.anio=(fechaString[6]-48)*1000+(fechaString[7]-48)*100+(fechaString[8]-48)*10+(fechaString[9]-48);
    }
    return fecha;
}

char* fechaToString(Fecha f)
{
    char* fechaString = (char*)malloc(11 * sizeof(char));

    fechaString[0]=f.dia/10+48;
    fechaString[1]=f.dia%10+48;
    fechaString[2]='/';
    fechaString[3]=f.mes/10+48;
    fechaString[4]=f.mes%10+48;
    fechaString[5]='/';
    fechaString[6]=f.anio/1000+48;
    fechaString[7]=(f.anio/100)%10+48;
    fechaString[8]=(f.anio/10)%10+48;
    fechaString[9]=f.anio%10+48;
    fechaString[10]='\0';

    return fechaString;
}

Patente stringToPatente(char *patenteString)
{
    Patente p;
    char letras[4];
    char numeros[4];
    int indiceLet=0;
    int indiceNum=0;
    limpiarString(letras, 4);
    limpiarString(numeros, 4);

    for(int i=0; i<strlen(patenteString); i++)
    {
        if(patenteString[i]>64&&patenteString[i]<91||patenteString[i]>96&&patenteString[i]<123)
        {
            letras[indiceLet]=patenteString[i];
            indiceLet++;
        }
        if(patenteString[i]>47&&patenteString[i]<58)
        {
            numeros[indiceNum]=patenteString[i];
            indiceNum++;
        }
    }
    strcpy(p.letras, letras);
    strcpy(p.numeros, numeros);
    return p;
}

char* patenteToString(Patente p)
{
    char patenteString[8];
    strcpy(patenteString, p.letras);
    strcat(patenteString, " ");
    return strcat(patenteString, p.numeros);
}

int posicionCentral(char texto[], int ancho)
{
    return (ancho/2)-(strlen(texto)/2);
}

void limpiarString(char string[], int dim)
{
    for(int i=0; i<dim; i++)
    {
        string[i]='\0';
    }
}

int formatearStringFecha(char stringFecha[], int *indice, Fecha *fecha)
{
    int esValida=1;
    int x=whereX();
    int y=whereY();

    printf("           ");
    gotoxy(x,y);
    if(strlen(stringFecha)>0)
    {
        if(strlen(stringFecha)==2||strlen(stringFecha)==5)
        {
            stringFecha[*indice]='/';
            (*indice)++;
        }
        color(COLOR_BASE);
        printf("%s", stringFecha);
    }
    else if(fecha!=NULL)
    {
        color(COLOR_DESABILITADO);
        printf("%s", fechaToString((*fecha)));
        *indice=0;
    }
    else
    {
        color(COLOR_DESABILITADO);
        printf("dd/mm/aaaa");
        *indice=0;
    }
    if(strlen(stringFecha)==10&&!validarFecha(stringToFecha(stringFecha)))
    {
        limpiarString(stringFecha, 11);
        *indice=0;
        esValida=0;
    }
    return esValida;
}

void informarError(int x, int y, char * texto, int colorTexto)
{
    color(colorTexto);
    gotoxy(x,y);
    printf("%s", texto);
}

int dniStringToInt(char *dniString)
{
    int dni=0;
    if(validarDni(dniString))
    {
        for(int i=0; i<strlen(dniString); i++)
        {
            dni=dni*10+(dniString[i]-48);
        }
    }
    return dni;
}

void floatToString(float number, char* buffer, int bufferSize)
{
    snprintf(buffer, bufferSize, "%.2f", number);
}

char* enteroToString(int num)
{
    int cantidadCifras=0;
    char *string;

    while(num>1)
    {
        cantidadCifras++;
        num=num/10;
    }
    string = (char*) malloc(sizeof(char*)*cantidadCifras+1);

    for(int i=cantidadCifras-1; i>=0; i--)
    {
        string[i]=(num%10)+48;
        num/=10;
    }
    string[cantidadCifras]='\0';
    return string;
}

float calcularValorAlquiler(Patente patente, Fecha fechaInicio, Fecha fechaFin, float *valorTotal)
{
    float cantDias=(float)diasEntreFechas(fechaInicio, fechaFin);
    float precioAuto=0;
    obtenerPrecioVehiculo(patente, "ArchivoAutos", &precioAuto);
    *valorTotal=(precioAuto)*cantDias;
    if(*valorTotal==0)
    {
        *valorTotal=precioAuto;
    }
    return *valorTotal;
}

void borrarCaracterFecha(char stringFecha[], int *indice)
{
    if(stringFecha[strlen(stringFecha)-1]=='/')
    {
        (*indice)--;
        stringFecha[*indice]='\0';
    }
    if(*indice>=0)
    {
        stringFecha[strlen(stringFecha)-1] = '\0';
        (*indice)--;
    }
}

void agregarMayusculas(char nombre[])
{
    for(int i=1; i<strlen(nombre); i++)
    {
        nombre[0]=toupper(nombre[0]);
        if(nombre[i]==' ')
        {
            nombre[i+1]=toupper(nombre[i+1]);
        }
    }
}
