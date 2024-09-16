#include "alquilerData.h"

#include <stdio.h>
#include <stdlib.h>

int registrarAlquiler(Alquiler alquiler)
{
    int registrado;
    FILE *archivo=fopen(ARCHIVO_ALQUILERES, "ab");
    if(archivo!=NULL)
    {
        alquiler.id=obtenerIdAlquiler();
        alquiler.activo=1;
        alquiler.eliminado=0;
        registrado=fwrite(&alquiler, sizeof(Alquiler), 1, archivo);
        fclose(archivo);
    }
    if(registrado)
    {
        modificarDisponibilidadVehiculo(alquiler.vehiculo, 0);
    }
    return registrado;
}

void AlquileresPorVehiculo(Patente patente, Alquiler *alquileres)
{
    Alquiler alquiler;
    int indice=0;
    FILE *archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    if(archivo!=NULL)
    {
        while(fread(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            if(strcmpi(alquiler.vehiculo.letras, patente.letras)&&strcmpi(alquiler.vehiculo.numeros, patente.numeros))
            {
                alquileres[indice]=alquiler;
                indice++;
            }
        }
    }
}

int cantidadDeAlquileresActivos(int estado)
{
    FILE *archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    long cantBytes=0;
    int cantRegistros=0;
    Alquiler alquiler;
    if(archivo!=NULL)
    {
        while(fread(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            if(alquiler.activo==estado&&!alquiler.eliminado)
            {
                cantRegistros++;
            }
        }
        fclose(archivo);
    }
    return cantRegistros;
}

int cantidadDeAlquileresEliminados()
{
    FILE *archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    long cantBytes=0;
    int cantRegistros=0;
    Alquiler alquiler;
    if(archivo!=NULL)
    {
        while(fread(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            if(alquiler.eliminado)
            {
                cantRegistros++;
            }
        }
        fclose(archivo);
    }
    return cantRegistros;
}

int cantidadDeAlquileresTotal(int dimensionEstructura)
{
    FILE *archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    long cantBytes=0;
    int cantRegistros=0;
    if(archivo!=NULL)
    {
        fseek(archivo, 0, SEEK_END);
        cantBytes=ftell(archivo);
        if(cantBytes%dimensionEstructura==0)
        {
            cantRegistros=cantBytes/dimensionEstructura;
        }
        fclose(archivo);
    }
    return cantRegistros;
}

int cantidadDeAlquileres()
{
    FILE *archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    long cantBytes=0;
    int cantRegistros=0;
    Alquiler alquiler;
    if(archivo!=NULL)
    {
        while(fread(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            if(alquiler.eliminado)
            {
                cantRegistros++;
            }
        }
        fclose(archivo);
    }
    return cantRegistros;
}

Alquiler buscarAlquiler(Fecha fechaInicio, Patente patente)
{
    Alquiler alquiler;
    int encontrado=0;
    FILE *archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    if(archivo!=NULL)
    {
        while(fread(&alquiler, sizeof(Alquiler), 1, archivo)>0&&! encontrado)
        {
            if(compararFecha(alquiler.fechaInicio, fechaInicio)==0&&compararPatente(alquiler.vehiculo, patente)==0)
            {
                encontrado=1;
            }
        }
        fclose(archivo);
    }
    return alquiler;
}

Alquiler buscarAlquilerPorId(int idAlquiler)
{
    Alquiler alquiler;
    Alquiler aux;
    int encontrado=0;
    FILE *archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    if(archivo!=NULL)
    {
        while(fread(&aux, sizeof(Alquiler), 1, archivo)>0&&! encontrado)
        {
            if(aux.id==idAlquiler)
            {
                encontrado=1;
                alquiler=aux;
            }
        }
        fclose(archivo);
    }
    return alquiler;
}

int modificarAlquiler(Alquiler alquiler)
{
    int modificado=0;
    int posicion=posicionAlquilerPorId(alquiler.id);
    FILE * archivo = fopen(ARCHIVO_ALQUILERES, "r+b");

    if(archivo!=NULL)
    {
        fseek(archivo, sizeof(Alquiler)*(posicion), SEEK_SET);
        if(fwrite(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            modificado=1;
        }
        fclose(archivo);
    }
    return modificado;
}

int finalizarAlquiler(Alquiler alquiler)
{
    int modificado=0;
    int posicion=posicionAlquilerPorId(alquiler.id);
    alquiler.activo=0;

    FILE * archivo = fopen(ARCHIVO_ALQUILERES, "r+b");

    if(archivo!=NULL)
    {
        fseek(archivo, sizeof(Alquiler)*(posicion), SEEK_SET);
        if(fwrite(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            modificado=1;
            modificarDisponibilidadVehiculo(alquiler.vehiculo, 1);
        }
        fclose(archivo);
    }
    return modificado;
}

int reactivarAlquiler(Alquiler alquiler)
{
    int modificado=0;
    int posicion=posicionAlquilerPorId(alquiler.id);
    alquiler.activo=1;

    FILE * archivo = fopen(ARCHIVO_ALQUILERES, "r+b");

    if(archivo!=NULL)
    {
        fseek(archivo, sizeof(Alquiler)*(posicion), SEEK_SET);
        if(fwrite(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            modificado=1;
            modificarDisponibilidadVehiculo(alquiler.vehiculo, 0);
        }
        fclose(archivo);
    }
    return modificado;
}

int eliminarAlquiler(Alquiler alquiler)
{
    int modificado=0;
    int posicion=posicionAlquilerPorId(alquiler.id);
    alquiler.eliminado=1;

    FILE * archivo = fopen(ARCHIVO_ALQUILERES, "r+b");

    if(archivo!=NULL)
    {
        fseek(archivo, sizeof(Alquiler)*(posicion), SEEK_SET);
        if(fwrite(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            modificado=1;
            modificarDisponibilidadVehiculo(alquiler.vehiculo, ! alquiler.activo);
        }
        fclose(archivo);
    }
    return modificado;
}

void eliminarAlquileresActivosDeUnapersona(int dni)
{
    Alquiler alquiler;
    FILE * archivo = fopen(ARCHIVO_ALQUILERES, "r+b");
    if(archivo!=NULL)
    {
        while(fread(archivo, sizeof(Alquiler), 1, archivo)>0)
        {
            if(alquiler.dniCliente==dni&&alquiler.activo)
            {
                eliminarAlquiler(alquiler);
            }
        }
        fclose(archivo);
    }
}

int restaurarAlquiler(Alquiler alquiler)
{
    int modificado=0;
    int posicion=posicionAlquilerPorId(alquiler.id);
    alquiler.eliminado=0;

    FILE * archivo = fopen(ARCHIVO_ALQUILERES, "r+b");

    if(archivo!=NULL)
    {
        fseek(archivo, sizeof(Alquiler)*(posicion), SEEK_SET);
        if(fwrite(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            modificado=1;
            modificarDisponibilidadVehiculo(alquiler.vehiculo, !alquiler.activo);
        }
        fclose(archivo);
    }
    return modificado;
}


int posicionAlquilerPorId(int idAlquiler)
{
    Alquiler alquiler;
    int encontrado=0;
    int posicion=0;
    FILE *archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    if(archivo!=NULL)
    {
        while(fread(&alquiler, sizeof(Alquiler), 1, archivo)>0&&!encontrado)
        {
            if(alquiler.id==idAlquiler)
            {
                encontrado=1;
            }
            else
            {
                posicion++;
            }
        }
        fclose(archivo);
    }
    return posicion;
}

Alquiler* listarAlquileres(int *cantidadAlquileres, int estado)
{
    *cantidadAlquileres=cantidadDeAlquileresActivos(estado);
    Alquiler *alquileres = (Alquiler *)malloc(*cantidadAlquileres * sizeof(Alquiler));
    Alquiler alquiler;
    int indice=0;
    FILE * archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    if(archivo!=NULL)
    {
        while(fread(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            if(alquiler.activo==estado&&!alquiler.eliminado)
            {
                alquileres[indice]=alquiler;
                indice++;
            }
        }
        fclose(archivo);
    }
    *cantidadAlquileres=indice;
    return alquileres;
}

Alquiler* listarAlquileresPorPersona(int *cantidadAlquileres, int dni)
{
    *cantidadAlquileres=10;
    Alquiler *alquileres = (Alquiler *)malloc(*cantidadAlquileres * sizeof(Alquiler));
    Alquiler alquiler;
    int indice=0;
    FILE * archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    if(archivo!=NULL)
    {
        while(fread(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            if(!alquiler.eliminado&&alquiler.dniCliente==dni)
            {
                alquileres[indice]=alquiler;
                indice++;
            }
            if(indice==*cantidadAlquileres)
            {
                Alquiler *aux=(Alquiler*)realloc(alquileres, sizeof(Alquiler)*(*cantidadAlquileres)+10);
                (*cantidadAlquileres)+=10;
                if(aux)
                {
                    free(alquileres);
                    alquileres=aux;
                    free(aux);
                }
            }
        }
        fclose(archivo);
    }
    *cantidadAlquileres=indice;
    return alquileres;
}

int* listarDniConAlquileresActivos(int *cantidad)
{
    *cantidad=cantidadDeAlquileresActivos(1);

    int *dniPersonas = (int *)malloc(*cantidad * sizeof(int));
    Alquiler alquiler;
    int indice=0;
    FILE * archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    if(archivo!=NULL)
    {
        while(fread(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            if(alquiler.activo&&!alquiler.eliminado)
            {
                dniPersonas[indice]=alquiler.dniCliente;
                indice++;
            }
        }
        fclose(archivo);
    }
    *cantidad=indice;
    return dniPersonas;
}

Patente* listarPatentesConAlquileresActivos(int *cantidadPatentes)
{
    *cantidadPatentes=cantidadDeAlquileresActivos(1);

    Patente *patentes = (Patente *)malloc(*cantidadPatentes * sizeof(Patente));
    Alquiler alquiler;
    int indice=0;
    FILE * archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    if(archivo!=NULL)
    {
        while(fread(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            if(alquiler.activo&&!alquiler.eliminado)
            {
                patentes[indice]=alquiler.vehiculo;
                indice++;
            }
        }
        fclose(archivo);
    }
    *cantidadPatentes=indice;
    return patentes;
}

int verificarPersonaAlquiler(int dni)
{
    int encontrado=0;
    Alquiler alquiler;
    FILE * archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    if(archivo!=NULL)
    {
        while(fread(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            if(alquiler.activo&&alquiler.dniCliente==dni)
            {
                encontrado=1;
            }
        }
        fclose(archivo);
    }
    return encontrado;
}
int verificarPatenteAlquiler(Patente patente)
{
    int encontrado=0;
    Alquiler alquiler;
    FILE * archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    if(archivo!=NULL)
    {
        while(fread(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            if(alquiler.activo&&compararPatente(alquiler.vehiculo,patente)==0)
            {
                encontrado=1;
            }
        }
        fclose(archivo);
    }
    return encontrado;
}

Alquiler* listarAlquileresEliminados(int *cantidadAlquileres)
{
    *cantidadAlquileres=cantidadDeAlquileresEliminados();
    Alquiler *alquileres = (Alquiler *)malloc(*cantidadAlquileres * sizeof(Alquiler));
    Alquiler alquiler;
    int indice=0;
    FILE * archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    if(archivo!=NULL)
    {
        while(fread(&alquiler, sizeof(Alquiler), 1, archivo)>0)
        {
            if(alquiler.eliminado)
            {
                alquileres[indice]=alquiler;
                indice++;
            }
        }
        fclose(archivo);
    }
    *cantidadAlquileres=indice;
    return alquileres;
}

int obtenerIdAlquiler()
{
    int id=0;
    int dimensionEstructura=sizeof(Alquiler);
    Alquiler alquiler;
    FILE *archivo=fopen(ARCHIVO_ALQUILERES, "rb");
    if(archivo!=NULL)
    {
        if(fseek(archivo, dimensionEstructura*(-1), SEEK_END)==0)
        {
            fread(&alquiler, dimensionEstructura, 1, archivo);
            id=alquiler.id;
        }
        fclose(archivo);
    }
    id++;
    return id;
}

void ordenarAlquilerFecha(Alquiler *alquileres, int cantidadAlquiler, int orden)//recibe 1 para orden ascendente y -1 para orden descendente
{
    Alquiler alquilerAux;
    int posicionMenor=0;
    for(int i=0; i<cantidadAlquiler; i++)
    {
        if(orden>0)
        {
            posicionMenor=posicionAlquilerMasReciente(alquileres, cantidadAlquiler, i);
        }
        else
        {
            posicionMenor=posicionAlquilerMasAntiguo(alquileres, cantidadAlquiler, i);
        }
        alquilerAux=alquileres[i];
        alquileres[i]=alquileres[posicionMenor];
        alquileres[posicionMenor]=alquilerAux;
    }
}

int posicionAlquilerMasReciente(Alquiler *alquileres, int cantidadAlquiler, int inicio)
{
    Fecha fechaMayor=alquileres[inicio].fechaInicio;
    int indice=inicio;
    for(int i=inicio+1; i<cantidadAlquiler; i++)
    {
        if(compararFecha(alquileres[i].fechaInicio, fechaMayor)>0)
        {
            fechaMayor=alquileres[i].fechaInicio;
            indice=i;
        }
    }
    return indice;
}

/// //////////////////////////////IPLEMENTANDO RECURSIVIDAD////////////////////////////////////////////////////////
void ordenarAlquilerRecursividad(Alquiler *alquileres, int cantidadAlquiler, int inicio, int sentido, char orden)//recibe 1 para orden ascendente y -1 para orden descendente
{
    Alquiler alquilerAux;
    int posicionMenor=inicio;

    if(inicio<cantidadAlquiler) ///condicion de corte
    {
        switch(orden)
        {
        case 'I':
            if(sentido>0)
            {
                posicionMenor=posicionMayorImporte(alquileres, cantidadAlquiler, inicio);
            }
            else
            {
                posicionMenor=posicionMenorImporte(alquileres, cantidadAlquiler, inicio);
            }
            break;
        case 'D':
            if(sentido>0)
            {
                posicionMenor=posicionMayorDni(alquileres, cantidadAlquiler, inicio);
            }
            else
            {
                posicionMenor=posicionMenorDni(alquileres, cantidadAlquiler, inicio);
            }
            break;
        case 'V':
            if(sentido>0)
            {
                posicionMenor=posicionMayorPatente(alquileres, cantidadAlquiler, inicio);
            }
            else
            {
                posicionMenor=posicionMenorPatente(alquileres, cantidadAlquiler, inicio);
            }
            break;
        case 'F':
            if(sentido>0)
            {
                posicionMenor=posicionAlquilerMasReciente(alquileres, cantidadAlquiler, inicio);
            }
            else
            {
                posicionMenor=posicionAlquilerMasAntiguo(alquileres, cantidadAlquiler, inicio);
            }
            break;
        }

        alquilerAux=alquileres[inicio];
        alquileres[inicio]=alquileres[posicionMenor];
        alquileres[posicionMenor]=alquilerAux;

        ordenarAlquilerRecursividad(alquileres, cantidadAlquiler, inicio+1, sentido, orden);   ///llamada recursiva
    }
}

int posicionAlquilerMasAntiguo(Alquiler *alquileres, int cantidadAlquiler, int inicio)
{
    Fecha fechaMenor=alquileres[inicio].fechaInicio;
    int indice=inicio;
    for(int i=inicio+1; i<cantidadAlquiler; i++)
    {
        if(compararFecha(alquileres[i].fechaInicio, fechaMenor)<0)
        {
            fechaMenor=alquileres[i].fechaInicio;
            indice=i;
        }
    }
    return indice;
}

int posicionMenorPatente(Alquiler *alquileres, int cantidadAlquiler, int inicio)
{
    Patente patenteMenor=alquileres[inicio].vehiculo;
    int indice=inicio;
    for(int i=inicio+1; i<cantidadAlquiler; i++)
    {
        if(compararPatente(alquileres[i].vehiculo, patenteMenor)<0)
        {
            patenteMenor=alquileres[i].vehiculo;
            indice=i;
        }
    }
    return indice;
}

int posicionMayorPatente(Alquiler *alquileres, int cantidadAlquiler, int inicio)
{
    Patente patenteMayor=alquileres[inicio].vehiculo;
    int indice=inicio;
    for(int i=inicio+1; i<cantidadAlquiler; i++)
    {
        if(compararPatente(alquileres[i].vehiculo, patenteMayor)>0)
        {
            patenteMayor=alquileres[i].vehiculo;
            indice=i;
        }
    }
    return indice;
}

int posicionMenorDni(Alquiler *alquileres, int cantidadAlquiler, int inicio)
{
    int dniMenor=alquileres[inicio].dniCliente;
    int indice=inicio;
    for(int i=inicio+1; i<cantidadAlquiler; i++)
    {
        if(alquileres[i].dniCliente<dniMenor)
        {
            dniMenor=alquileres[i].dniCliente;
            indice=i;
        }
    }
    return indice;
}

int posicionMayorDni(Alquiler *alquileres, int cantidadAlquiler, int inicio)
{
    int dniMayor=alquileres[inicio].dniCliente;
    int indice=inicio;
    for(int i=inicio+1; i<cantidadAlquiler; i++)
    {
        if(alquileres[i].dniCliente>dniMayor)
        {
            dniMayor=alquileres[i].dniCliente;
            indice=i;
        }
    }
    return indice;
}

int posicionMayorImporte(Alquiler *alquileres, int cantidadAlquiler, int inicio)
{
    float importeMayor= alquileres[inicio].precioTotal;
    int indice=inicio;
    for(int i=inicio+1; i<cantidadAlquiler; i++)
    {
        if(alquileres[i].precioTotal>importeMayor)
        {
            importeMayor=alquileres[i].precioTotal;
            indice=i;
        }
    }
    return indice;
}

int posicionMenorImporte(Alquiler *alquileres, int cantidadAlquiler, int inicio)
{
    float importeMenor= alquileres[inicio].precioTotal;
    int indice=inicio;
    for(int i=inicio+1; i<cantidadAlquiler; i++)
    {
        if(alquileres[i].precioTotal<importeMenor)
        {
            importeMenor=alquileres[i].precioTotal;
            indice=i;
        }
    }
    return indice;
}

Alquiler generarAlquiler(int dniCliente, Fecha fechaInicio, Fecha fechaFin, Patente patente)
{
    Alquiler alquiler;
    float precioTotal;
    calcularValorAlquiler(patente, fechaInicio, fechaFin, &precioTotal);
    alquiler.precioTotal=precioTotal;
    alquiler.dniCliente=dniCliente;
    alquiler.fechaFin=fechaFin;
    alquiler.fechaInicio=fechaInicio;
    alquiler.vehiculo=patente;

    return alquiler;
}

/// VEHICULOS ///

int modificarDisponibilidadVehiculo(Patente patente, int disponible)
{
    int modificado=0;
    int posicion=buscarPosicionDeLaPatente(patente);
    Vehiculo vehiculo;
    FILE * archivo = fopen(ARCHI_VEHICULOS, "r+b");
    if(archivo!=NULL)
    {
        fseek(archivo, sizeof(Vehiculo)*(posicion), SEEK_SET);
        fread(&vehiculo, sizeof(Vehiculo), 1, archivo);
        vehiculo.disponibilidad=disponible;
        fseek(archivo, sizeof(Vehiculo)*(-1), SEEK_CUR);
        if(fwrite(&vehiculo, sizeof(Vehiculo), 1, archivo)>0)
        {
            modificado=1;
        }
        fclose(archivo);
    }
    return modificado;
}

float obtenerPrecioVehiculo(Patente patente, char *nombreArchivo, float *precio)
{
    Vehiculo vehiculo;
    int encontrado=0;
    FILE *archivo = fopen(nombreArchivo, "rb");

    if(archivo!=NULL)
    {
        while(fread(&vehiculo, sizeof(Vehiculo), 1, archivo)>0&&!encontrado)
        {
            if(compararPatente(patente, vehiculo.patente)==0)
            {
                encontrado=1;
                *precio=vehiculo.precioDeAlquilerDiario;
            }
        }
        fclose(archivo);
    }
    return *precio;
}

/// PERSONAS ///

Cliente buscarClienteDni (int dni)
{
    FILE *archivo = fopen (ARCHI_CLIENTES, "rb");
    int encontrado = 0;
    Cliente cliente;
    cliente.dni=0;
    if (archivo)
    {
        while (fread(&cliente, sizeof(Cliente), 1, archivo)>0&&!encontrado)
        {
            if (cliente.dni==dni&&cliente.baja)
            {
                encontrado=1;
            }
        }
        fclose(archivo);
    }
    return cliente;
}

int existeDniCliente(int dni)
{
    int y=20;
    FILE *archivo = fopen (ARCHI_CLIENTES, "rb");
    int encontrado = 0;
    Cliente cliente;
    cliente.dni=0;
    if (archivo)
    {
        while (fread(&cliente, sizeof(Cliente), 1, archivo)>0&&!encontrado)
        {
            encontrado=1;
        }
    }
    fclose(archivo);
return encontrado;
}

int existeDniUsuario(int dni)
{
    FILE *archivo = fopen (ARCHI_USUARIOS, "rb");
    int encontrado = 0;
    Usuario usuario;
    usuario.dni=0;
    if (archivo)
    {
        while (fread(&usuario, sizeof(Usuario), 1, archivo)>0&&!encontrado)
        {
            if (usuario.dni==dni&&usuario.baja)
            {
                encontrado=1;
            }
        }
        fclose(archivo);
    }
    return encontrado;
}

int validarNicknameUsuario(char nick[], Usuario *usuario)
{
    FILE *archivo = fopen (ARCHI_USUARIOS, "rb");
    int encontrado = 0;
    Usuario aux;
    if (archivo)
    {
        while (fread(&aux, sizeof(Usuario), 1, archivo)>0&&!encontrado)
        {
            if (strcmp(aux.nickname,nick)==0&&aux.baja)
            {
                *usuario=aux;
                encontrado=1;
            }
        }
        fclose(archivo);
    }
    return encontrado;
}

int existeNicknameUsuario(char nick[])
{
    FILE *archivo = fopen (ARCHI_USUARIOS, "rb");
    int encontrado = 0;
    Usuario usuario;
    if (archivo)
    {
        while (fread(&usuario, sizeof(Usuario), 1, archivo)>0&&!encontrado)
        {
            if (strcmp(usuario.nickname,nick)==0&&usuario.baja)
            {
                usuario=usuario;
                encontrado=1;
            }
        }
        fclose(archivo);
    }
    return encontrado;
}

int guardarUsuario(Usuario usuario)
{
    int registrado=0;
    FILE *archivo=fopen(ARCHI_USUARIOS, "ab");
    if(archivo!=NULL)
    {
        usuario.baja=1;
        registrado=fwrite(&usuario, sizeof(Usuario), 1, archivo);
        fclose(archivo);
    }
    return registrado;
}
