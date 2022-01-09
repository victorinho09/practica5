// Este fichero contiene las funciones necesarias para la practica



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#include "estructuras.c"

// Leemos el formato de una linea del fichero de los sorteos
void scanLineaSorteo(char *linea,lineaSorteo *leer)
{
    // Utilizamos la funcion scanf, pero para strings para leer una parte concreta de la linea
    // Guardamos los premios
    sscanf(linea,"%d %s %d-%d-%d-%d-%d-%d %lf %lf %lf %lf %lf",
        &(leer->numSorteo),
        leer->fechaSorteo,
        &(leer->quiniela[0]),
        &(leer->quiniela[1]),
        &(leer->quiniela[2]),
        &(leer->quiniela[3]),
        &(leer->quiniela[4]),
        &(leer->quiniela[5]),
        &(leer->recaudacion),
        &(leer->aciertos[6]),
        &(leer->aciertos[5]),
        &(leer->aciertos[4]),
        &(leer->aciertos[3])
        );
        printf("");
}

// Leemos la ultima linea del fichero de los sorteos
void leerUltimoSorteo(char *nombreFichero,lineaSorteo *leer)
{
    FILE *fd = fopen(nombreFichero,"r");
    if (fd == NULL) {
        printf("Error, el fichero llamado %s no existe.",nombreFichero);
        exit(0);
    }
    char linea[TAMANO_CADENA];
    char lineaTemporal[ TAMANO_CADENA];
    // Introducimos en la variable linea el contenido de la ultima combinacion del fichero
    while(1)
    {
        if (fgets(lineaTemporal,TAMANO_CADENA,fd) ==NULL)
        {
            break;
        }
        strcpy(linea,lineaTemporal);
    }
    scanLineaSorteo(linea,leer);
    fclose(fd);
}
// Obtenemos el valor de la jornada al iniciar el programa
void valorVecesSorteo(char *nombreFichero,lineaSorteo *leer)
{
    FILE *fd = fopen(nombreFichero,"r");
    if (fd == NULL) {
        printf("Error, el fichero llamado %s no existe.",nombreFichero);
        exit(0);
    }
    char linea[TAMANO_CADENA]={0};
    char lineaTemporal[TAMANO_CADENA];
    // Introducimos en la variable linea el contenido de la ultima combinacion del fichero
    while(1)
    {   // Salimos del bucle cuando hayamos leido la ultima linea del fichero
        if (fgets(lineaTemporal,TAMANO_CADENA,fd) ==NULL)
        {
            break;
        }
        // Necesitamos guardar la penultima linea leida, ya que la ultima es una cadena vacia
        strcpy(linea,lineaTemporal);
    }
    // Vemos si existe algun sorteo en el fichero, si no le damos el valor inicial 
    if( strcmp(linea,"")==0  )
    {
        vecesSorteo=1;
    } else {
        scanLineaSorteo(linea,leer);
        vecesSorteo = leer->numSorteo + 1;
    }
    fclose(fd);
}

int imprimirMenu()
{
    int opcion;
    // Creamos un menu
    printf("** APUESTAS - SORTEO PRIMITIVA Nº %02i **\n", vecesSorteo);
    printf("-------------------------------------------\n");
    printf("    1.- Generar quiniela aleatoria\n");
    printf("    2.- Generar apuestas múltiples\n");
    printf("    3.- Realizar sorteo\n");
    printf("    4.- Comprobar quiniela manualmente\n");
    printf("    5.- Comprobar apuestas múltiples\n");
    printf("    6.- Consultar sorteo actual\n");
    printf("    7.- Consultar histórico\n");
    printf("    0.- Salir\n\n");
    printf("Elige una opcion:");
    scanf("%i", &opcion);
    printf("\n");

    return opcion;
}

// Pedimos una cadena para que el usuario la introduzca por teclado
char *pedirCadena(char *frase)
{
    char *cadena;
    // Reservamos memoria en el heap, para que cuando salgamos de la funcion las variables que 
    // hemos utilizado no se destruyan
    cadena = (char *) malloc(TAMANO_CADENA);
    if(cadena==NULL)
    {
        printf("No hay memoria suficiente\n");
        exit (1);
    }
    if(strcmp(frase,"") != 0)
    {
        printf("%s: ",frase);
    }
    
    while(1)
    {   
        // Comprobamos que la cadena se ha leido correctamente
        if (fgets(cadena,TAMANO_CADENA,stdin) ==NULL)
        {
            continue;
        } 
        // Comprobamos que la cadena no esta vacia 
        if( (strcmp(cadena,"") == 0) ||  (strcmp(cadena,"\n") == 0) )
        {
            continue;
        }
        // Si viene con retorno de linea necesitamos eliminarlo para que lo imprima bien
        if(cadena[strlen(cadena)-1] == '\n')
        {
            cadena[strlen(cadena)-1] = 0;
        }
        break;
    }
    return cadena;
}

void vaciarBufferStdin() {
    
    int ch;
    while ( (ch = getchar() ) != '\n' && ch != EOF);

}

// Iniciamos el fichero de los sorteos al principio del programa
void iniciaHistorico()
{
    FILE *fd = fopen(NOMBRE_FICHERO_SORTEO,"a+");
     if (fd == NULL)
    {
        printf("Error, el fichero llamado %s no existe",NOMBRE_FICHERO_SORTEO);
        exit(0);
    }
    fclose(fd);
}

// Generar 6 numeros aleatorios. Le pasamos por argumento un puntero que contiene enteros y una variable que indica el tamaño del array
// correspondiente al puntero,ya que necesitamos que la función devuelva los valores en la variable indicada. 
void generarQuiniela(int *valorAleatorio, int tamano)
{
    int i, j;
    int repetir;

    for (i = 0; i < tamano; i++)
    {

        do
        {
            repetir = 0;
            valorAleatorio[i] = rand() % 49 + 1;
            // Comprobación de que no haya números repetidos
            for (j = 0; j < i; j++)
            {

                if (valorAleatorio[i] == valorAleatorio[j])
                {
                    repetir = 1;      
                }
            }

        } while (repetir);
    }
}

// Ordenar los números del array mediante quicksort
// Para ello creo la función cmpfunc que me permite comparar los datos del array
// Esta me devuelve 0 si son iguales, >0 si a es mayor y <0 si b es mayor
int cmpfunc (const void * a, const void * b) 
{
   return ( *(int*)a - *(int*)b );
}
void ordenarQuiniela(int *valorAleatorio, int tamano)
{
    qsort(valorAleatorio,tamano,sizeof(int),cmpfunc);
}

// Generar codigo identificador de cada apuesta
void generarIdentificador(int *valorAleatorio)
{

    int i, j;
    int repetir;

    for (i = 0; i < 10; i++)
    {

        do
        {
            repetir = 0;
            valorAleatorio[i] = rand() % 10;
            // Comprobación de que no haya números repetidos
            for (j = 0; j < i; j++)
            {

                if (valorAleatorio[i] == valorAleatorio[j])
                {
                    repetir = 1;
                }
            }

        } while (repetir);
    }
}

// Pedimos que el usuario introduzca un numero positivo por teclado
int pedirNumeroPositivo(char *frase)
{
    int numeroApuestas = 1;
    while(1)
    {
        printf("%s: ",frase);
        // Comprobamos que es un numero positivo
        if( (scanf("%d", &numeroApuestas) != 1) || numeroApuestas <1)
        {
            printf("No ha introducido el número correctamente\n");
            vaciarBufferStdin();

        }  else {
            break;
        }
    }
    return numeroApuestas;
}

void funcionCaso1()
{
    int quiniela[FILAS];
    int i;

    generarQuiniela(quiniela, FILAS);
    ordenarQuiniela(quiniela, FILAS);
    for (i = 0; i < FILAS; i++)
    {
        if (i > 0)
        {
            printf("-");
        }
        printf("%d", quiniela[i]);
    }
    printf("\n\n");
}

void funcionCaso2()
{
    int numeroApuestas;
    char *nombre;
    int i;
    int contador;
    int identificador[10];
    int quiniela[FILAS];
    
    numeroApuestas = pedirNumeroPositivo("Introduzca el número de apuestas a realizar (>1) ");
    nombre = pedirCadena("Introduzca el nombre del fichero");
    
    FILE *fd;
    fd = fopen(nombre, "w");
    if (fd == NULL)
    {
        printf("Error, el fichero llamado %s no existe", nombre);
        exit(0);
    }

    for (contador = 1; contador <= numeroApuestas; contador++)
    {
        generarQuiniela(quiniela, FILAS);
        ordenarQuiniela(quiniela, FILAS);
        for (i = 0; i < FILAS; i++)
        {
            if (i > 0)
            {
                fprintf(fd, "-");
            }
            fprintf(fd, "%d", quiniela[i]);
        }
        fprintf(fd, " ");
        generarIdentificador(identificador);
        for (i = 0; i < 10; i++)
        {
            fprintf(fd, "%d", identificador[i]);
        }
        fprintf(fd, " %d", vecesSorteo);
        fprintf(fd, "\n");
    }
    fflush(fd);
    fclose(fd);
    printf("\n*** GENERACION APUESTAS MULTIPLES ***\n");
    printf("Introduzca el nombre del fichero para apuestas: %s\n", nombre);
    printf("Indique el número de apuestas a generar (> 1): %d\n", numeroApuestas);
    printf("Fichero “%s” con %d apuestas generado correctamente\n\n", nombre, numeroApuestas);
    free(nombre);
}

int contarLineas( char *nombreFichero)

{   
    char linea[TAMANO_CADENA];
    int contador=0;
    FILE *fd = fopen(nombreFichero,"r");
    if (fd == NULL)
    {
        printf("Error, el fichero llamado %s no existe", nombreFichero);
        exit(0);
    }
    while(1)
    {
        if (fgets(linea,200,fd)==NULL)
        {
            break;
        }
        // Cada vez que leamos una linea del fichero aumentamos la variable contador
        contador++;
    }    
    fclose(fd);
    // Nos devuelve el numero de lineas del fichero
    return contador;
} 

// Eliminamos la primera linea del fichero para poder añadir una nueva al final del fichero,
// ya que el número de sorteos máximos que se pueden guardar es 52 y necesitamos conservar los 
// sorteos que hayamos hecho anteriormente
void maximo52Lineas(char *nombreFichero)
{
    if (rename(nombreFichero,"historico.temporal")!=0)
    {
        //Ha habido error
        printf("Error al renombrar fichero\n");
        exit(0);
    } 
    
    FILE *fd1 = fopen("historico.temporal","r");
    if (fd1 == NULL)
    {
        printf("Error, el fichero llamado \"historico.temporal\"  no existe");
        exit(0);
    }
    FILE *fd2 = fopen(nombreFichero,"w");
    if (fd2 == NULL)
    {
        printf("Error, el fichero llamado %s  no existe",nombreFichero);
        exit(0);
    }
    char linea[200];
    int leidaPrimeraLinea = 0;
    while(1)
    {   //Leemos las lineas del fichero1
        if (fgets(linea,200,fd1)==NULL)
        {
            break;
        }
        //Para no copiar la primer línea, así copiamos solo las 51 restantes
        if(leidaPrimeraLinea == 0) {
            leidaPrimeraLinea = 1;
            continue;
        }
        //Copiamos todas las lineas del fichero 1 excepto la primera
        if(fputs(linea,fd2)<=0)
        {
            printf("Error al escribir en %s",nombreFichero);
            break;
        }

    }

    fclose(fd1);
    fflush(fd2);
    fclose(fd2);
    
    

}

void funcionCaso3()
{   
    int quiniela[FILAS];
    int i;
    int premios[5];
    // Si ya hay 52 lineas, necesitamos hacer hueco en el fichero para almacenar el sorteo nuevo
    if(contarLineas(NOMBRE_FICHERO_SORTEO)>=52)
    {
        maximo52Lineas(NOMBRE_FICHERO_SORTEO);
    }

    FILE *puntero;
    puntero= fopen(NOMBRE_FICHERO_SORTEO,"a+");
            if (puntero == NULL) {
                perror("Error, el fichero llamado histórico.dat: ");
                exit(0);
            }
            
            generarQuiniela(quiniela, FILAS);
            ordenarQuiniela(quiniela, FILAS);
            printf("*** SORTEO PRIMITIVA JORNADA %02i ***\n",vecesSorteo);
            printf("Combinación ganadora: ");
            for (i = 0; i < FILAS; i++)
            {
                if (i > 0)
                {
                    printf("-");
                }
                    printf("%d", quiniela[i]);
            }
            for(i=0; i < 5;i++)
            {
                if (i==0)
                {
                    premios[i]= (rand() % INT_MAX);
                } else 
                {
                    premios[i]= rand() % (premios[i-1]/7);
                }
            }
            time_t fecha;
            struct tm *info;
            time( &fecha );
            info = localtime( &fecha );
            int mes = ( info->tm_mon +1);
            int ano = ( info->tm_year +1900);
            int dia = info->tm_mday;

            double premios2[5];
            for(i=0;i<5;i++)
            {
                premios2[i]= (premios[i] / 100.7);
            }
            

            printf("\n\n");
            printf("DATOS DEL SORTEO\n");
            printf("Fecha: %d/%d/%d\n",dia,mes,ano);
            printf("Recaudación (en euros): %0.2f\n",premios2[0] );
            printf("Premios\n");
            printf("    6 aciertos: %0.2f\n",premios2[1] );
            printf("    5 aciertos: %0.2f\n",premios2[2] );
            printf("    4 aciertos: %0.2f\n",premios2[3] );
            printf("    3 aciertos: %0.2f\n",premios2[4] );
            printf("Sorteo grabado correctamente en 'histórico.dat'.\n");
            printf("Nueva jornada: %02i\n\n",(vecesSorteo +1));

            fprintf(puntero,"%d %d/%d/%d ",vecesSorteo, dia, mes, ano);
            for (i = 0; i < FILAS; i++)
            {
                if (i > 0)
                {
                    fprintf(puntero, "-");
                } 
                    fprintf(puntero, "%d", quiniela[i]);
            }
            fprintf(puntero," ");
            for(i=0;i<5;i++)
            {
                fprintf(puntero,"%0.2f ",premios2[i] );
            }
            fprintf(puntero,"\n");
            fflush(puntero);
            fclose(puntero);
            

}

// Leemos el formato de una linea del fichero de las apuestas
void scanLineaApuesta(char *linea,lineaApuesta *leer2)
{
    sscanf(linea,"%d-%d-%d-%d-%d-%d %s %d",
    &(leer2->combinacion[0]),
    &(leer2->combinacion[1]),
    &(leer2->combinacion[2]),
    &(leer2->combinacion[3]),
    &(leer2->combinacion[4]),
    &(leer2->combinacion[5]),
    leer2->codigoIdentificador,
    &(leer2->jornada)
    );
    printf("");
}

//Le damos el fichero ya abierto, para que no lo habra cada llamada a funcion
int leerLineaApuesta(FILE *fd2, lineaApuesta *leer2,char *nombreFichero)
{
    if (fd2 == NULL) {
        printf("Error, el fichero llamado %s no existe.",nombreFichero);
        exit(0);
    }
    char linea[TAMANO_CADENA];
    if (fgets(linea,TAMANO_CADENA,fd2) == NULL)
    {
        return 1;
    } else {
        scanLineaApuesta(linea,(lineaApuesta *)leer2);
    }
    return 0;

}

void leerLineaConcretaSorteo(char *nombreFichero,lineaSorteo *leer, int jornada)
{
    int i;
    FILE *fd = fopen(NOMBRE_FICHERO_SORTEO,"r");
    if (fd == NULL) {
        printf("Error, el fichero llamado historico.dat no existe.");
        exit(0);
    }
    char linea[TAMANO_CADENA];
    int quiniela[FILAS];

    // Necesitamos leer una linea concreta que nos ha dicho el usuario
    for(i=0;i<jornada;i++)
    {
        fgets(linea,TAMANO_CADENA,fd);
    }
    
    scanLineaSorteo(linea,leer);
    fclose(fd);
}

void comprobarApuestasManualmente(char *nombreFichero)
{
    int apuestas = 0;
    int apuestasPremio = 0;
    int totalGanancias = 0;
    int jornada;
    int i;
    int j;
    int numeroAciertos = 0; 
    lineaSorteo leer;
    lineaApuesta leer2;
    char linea[200];
    if(vecesSorteo>=2)
    {
        //Vamos a leer del fichero sorteo la combinacion de la ultima linea guardada
        leerUltimoSorteo(NOMBRE_FICHERO_SORTEO,&leer);
        
        //Vamos a leer del fichero de apuestas
        FILE *fd2 = fopen(nombreFichero,"r");
        while(1)
        {
            leerLineaApuesta(fd2,&leer2,nombreFichero);

            //Debemos comprobar si alguno de los numeros de las combinaciones son iguales 
            for(i=0;i<FILAS;i++)
            {
                for(j=0;j<FILAS;j++)
                {
                    if(leer.quiniela[i]==leer2.combinacion[j])
                    {
                        numeroAciertos++;
                    }
                }
            }
        }   
    } else {
        printf("No se ha realizado un sorteo previo");
        exit(0);
    }
}

void funcionCaso4()
{
    int combinacion[FILAS];
    int i;
    int j;
    int numeroEspacios = 0;
    int numeroAciertos = 0; 
    lineaSorteo leer;

    //Comprobamos que no ha habido un sorteo previamente
    if(vecesSorteo>=2)
    {
        printf("*** COMPROBACION QUINIELA MANUAL JORNADA %d ***\n",vecesSorteo);
        printf("Introduzca combinacion (1-49): ");
        for(i=0;i < FILAS;i++)
        {
            scanf("%d",(combinacion + i));
        }
        printf("\n");
        //Vamos a leer del fichero la combinacion de la ultima linea guardada
        leerUltimoSorteo(NOMBRE_FICHERO_SORTEO,&leer);
        for(i=0;i<FILAS;i++)
        {
            for(j=0;j<FILAS;j++)
            {
                if(leer.quiniela[i]==combinacion[j])
                {
                    numeroAciertos++;
                }
            }
        }
        printf("Total aciertos: %d\n",numeroAciertos);
        if(numeroAciertos>2)
        {
            printf("Premio obtenido: %0.2f\n",leer.aciertos[numeroAciertos]);

        } else {
            printf("Premio obtenido: 0 euros\n");
        }

    } else {
        printf("No se ha realizado ningún sorteo todavía\n");
    }
}

void comprobarApuestasMultiples(char *nombreFichero)
{
    int apuestas = 0;
    int apuestasPremio = 0;
    double totalGanancias = 0;
    int i;
    int j;
    int numeroAciertos = 0; 
    lineaSorteo leer;
    lineaApuesta leer2;
    int retorno;
    if(vecesSorteo>=2)
    {
        //Vamos a leer del fichero sorteo la combinacion de la ultima linea guardada
        leerUltimoSorteo(NOMBRE_FICHERO_SORTEO,&leer);
        
        FILE *fd2 = fopen(nombreFichero,"r");
        while(1)
        {
            numeroAciertos = 0;
            //Vamos a leer del fichero de apuestas
            retorno = leerLineaApuesta(fd2,&leer2,nombreFichero);

            if(retorno == 1)
            {
                break;
            } 
            //Debemos comprobar si alguno de los numeros de las combinaciones son iguales 
            for(i=0;i<FILAS;i++)
            {
                for(j=0;j<FILAS;j++)
                {
                    if(leer.quiniela[i]==leer2.combinacion[j])
                    {
                        numeroAciertos++;
                    }
                }
            }
            if(numeroAciertos>2)
            {
                printf("Código Identificador: %s\n",leer2.codigoIdentificador);
                printf("Apuesta con %d aciertos. Premiada con %0.2f Euros\n",numeroAciertos,leer.aciertos[numeroAciertos]);
                apuestasPremio++;  
                totalGanancias = totalGanancias + leer.aciertos[numeroAciertos];
            }
            apuestas++;
        }
        
        
        printf("--- RESUMEN FICHERO \"%s\" ---\n",nombreFichero);
        printf("Número de apuestas: %d\n",apuestas);
        printf("Total apuestas con premio: %d\n",apuestasPremio);
        printf("Total ganancias: %0.2f\n",totalGanancias);
        
    } else {
        printf("No se ha realizado un sorteo previo\n");
        exit(0);
    }
}

void funcionCaso5()
{   
    char *nombreFichero;
    printf("*** COMPROBACIÓN APUESTAS MÚLTIPLES - JORNADA %02i ***\n",vecesSorteo);
    nombreFichero = pedirCadena("Introduzca Nombre de Fichero: ");
    comprobarApuestasMultiples(nombreFichero);
}

void funcionCaso6()
{ 
    int i;
    lineaSorteo leer;
    if(vecesSorteo>=2)
    {
        //Vamos a leer del fichero la combinacion de la ultima linea guardada
        leerUltimoSorteo(NOMBRE_FICHERO_SORTEO,&leer);
        
        //Vamos a escribir por pantalla las variables guardadas
        printf("*** INFORMACIÓN ÚLTIMO SORTEO - JORNADA %02i ***\n",leer.numSorteo);
        printf("Fecha: %s\n",leer.fechaSorteo);
        printf("Combinación Ganadora: ");
        for(i=0;i<FILAS;i++)
        {
            if(i!=0)
            {
                printf("-");
            } 
            printf("%d",leer.quiniela[i]);
        }
        printf("\nRecaudación (en Euros): %0.2f\n",leer.recaudacion);
        printf("Premios (en Euros):\n");
        for(i=6;i>=3;i--)
        {
            printf("%d aciertos: %0.2f\n",i,leer.aciertos[i]);
        }
        printf("\n");
    } else {
        printf("Error: Todavía no ha tenido lugar ningún sorteo.\n\n");
    }
}

void funcionCaso7()
{
    int jornada;
    int i;
    lineaSorteo leer;

    printf("*** CONSULTA INFORMACIÓN SORTEO ANTERIOR ***\n");
    jornada = pedirNumeroPositivo("Introduzca número de jornada: ");

    if(vecesSorteo>jornada)
    {
        leerLineaConcretaSorteo(NOMBRE_FICHERO_SORTEO,&leer,jornada);

        //Vamos a escribir por pantalla las variables guardadas
        printf("\n*** INFORMACIÓN ÚLTIMO SORTEO - JORNADA %d ***\n",jornada);
        printf("Fecha: %s\n",leer.fechaSorteo);
        printf("Combinación Ganadora: ");
        for(i=0;i<FILAS;i++)
        {
            if(i!=0)
            {
                printf("-");
            } 
            printf("%d",leer.quiniela[i]);
        }
        printf("\nRecaudación (en Euros): %0.2f\n",leer.recaudacion);
        printf("Premios (en Euros):\n");
        for(i=6;i>=3;i--)
        {
            printf("%d aciertos: %0.2f\n",i,leer.aciertos[i]);
        }
        printf("\n");
    } else {
        printf("Error: El sorteo de la jornada seleccionada no ha sido realizado todavía.\n\n");
    }
}

