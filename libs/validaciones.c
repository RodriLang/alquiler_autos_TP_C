#include <string.h>
#include  <ctype.h>
#include "validaciones.h"

int validarStringNumerico(char string[])
{
    int validado=1;
    for(int i=0; i<strlen(string); i++)
    {
        if(!isdigit(string[i]))
        {
            validado=0;
        }
    }
    return validado;
}

int validarStringLetras(char string[])
{
    int validado=1;
    for(int i=0; i<strlen(string); i++)
    {
        if((string[i]<65||string[i]>90)&&(string[i]<97||string[i]>122)&&string[i]!=32)
        {
            validado=0;
        }
    }
    return validado;
}

int validarDni(char dni[])
{
    int longitud = strlen(dni);

    return validarStringNumerico(dni)&&longitud>=7&&longitud<=8&&dni[0]!='0';
}

int validarFormatoFecha(char fecha[])
{
    int validada=0;
    if(isdigit(fecha[0])&&isdigit(fecha[1])&&fecha[2]==47&&isdigit(fecha[3])&&isdigit(fecha[4])&&fecha[5]==47&&isdigit(fecha[6])&&isdigit(fecha[7])&&isdigit(fecha[8])&&isdigit(fecha[9])&&fecha[10]=='\0')
    {
        validada=1;
    }
    return validada;
}

int validarFecha(Fecha f)
{
    int fechaValida=0;
    if(f.anio>2014&&f.anio<=obtenerAnioActual()+5)
    {
        if(f.mes>=1&&f.mes<=12)
        {
            if(f.dia>0&&f.dia<=cantDiasSegunMes(f.mes, f.anio))
            {
                fechaValida=1;
            }
        }
    }
    return fechaValida;
}

int cantDiasSegunMes(int mes, int anio)
{
    int diasMaximos=0;
    switch(mes)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        diasMaximos=31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        diasMaximos=30;
        break;
    case 2:
        if(esBisiesto(anio))
        {
            diasMaximos=29;
        }
        else
        {
            diasMaximos=28;
        }
        break;
    }
    return diasMaximos;
}

int esBisiesto(int anio)
{
    return (anio%4==0 && anio%100!=0 || anio%100==0 && anio%400!=0);
}

int validarTelefono(char telefono[])
{
    return validarStringNumerico (telefono)&&strlen(telefono)==10;
}

int validarNombre(char nombre[])
{
    int validado=0;
    int longitud= strlen(nombre);
    if(longitud>=5&&validarStringLetras(nombre))
    {
        validado =1;
    }
    return validado;
}

void validarEntradaDni(char string[], char tecla)
{
    if(tecla>47&&tecla<58)
    {
        if(strlen(string)<8)
        {
            string[strlen(string)]=tecla;
        }
    }
    else if (tecla == '\b')
    {
        if (strlen(string) > 0)
        {
            string[strlen(string) - 1] = '\0';
        }
    }
}

void validarEntradaLetras(char string[], char tecla)
{

    if ((tecla >= 'a' && tecla <= 'z') || (tecla >= 'A' && tecla <= 'Z') || tecla == ' ')
    {
        if (strlen(string) < 30)
        {
            string[strlen(string)] = tecla;
        }
    }
    else if (tecla == '\b')
    {
        if (strlen(string) > 0)
        {
            string[strlen(string) - 1] = '\0';
        }
    }
}

void validarEntradaUser(char string[], char tecla)
{
    if ((tecla >= 'a' && tecla <= 'z') || (tecla >= 'A' && tecla <= 'Z') || tecla == ' '||isdigit(tecla))
    {
        if (strlen(string) < 29)
        {

            string[strlen(string)] = tecla;
        }
    }
    else if (tecla == '\b')
    {
        if (strlen(string) > 0)
        {
            string[strlen(string) - 1] = '\0';
        }
    }
}

int validarPass(char pass[])
{
    int validado=0;
    int longitud= strlen(pass);
    if(longitud>=5)
    {
        validado =1;
    }
    return validado;
}

int validarPassDuplicado(char pass[], char pass2[])
{
    int validado=0;
    if(validarPass(pass)&&validarPass(pass2)&&strcmp(pass,pass2)==0)
    {
        validado=1;
    }
    return validado;
}

void validarEntradaPass(char string[], char tecla)
{
    if ((tecla >=32 && tecla <=125))
    {
        if (strlen(string) < 8)
        {
            string[strlen(string)] = tecla;
        }
    }
    else if (tecla == '\b')
    {
        if (strlen(string) > 0)
        {
            string[strlen(string) - 1] = '\0';
        }
    }
}


