#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <string.h>


#include "funciones.c"

int main()
{

    srand(time(NULL));
    int opcion;
    lineaSorteo leer;

    //Iniciamos el historico.dat para que siempre exista
    iniciaHistorico();
    valorVecesSorteo(NOMBRE_FICHERO_SORTEO,&leer);
    
    do
    {
        opcion = imprimirMenu();

        switch (opcion)
        {

        case 1:
            funcionCaso1();
            break;
        case 2:
            funcionCaso2();    
            break;
        case 3:
            funcionCaso3();
            vecesSorteo++;
            break;
        case 4:
            funcionCaso4();
            break;
        case 5:
            funcionCaso5();
            break;
        case 6:
            funcionCaso6();
            break;
        case 7:
            funcionCaso7();
            break;
        case 0:
            break;
        default:
            printf("\nLa opcion es incorrecta\n\n");
            break;
        }
    } while (opcion != 0);
}