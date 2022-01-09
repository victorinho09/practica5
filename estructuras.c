//Este fichero contiene las estructuras y constantes necesarias para la practica

#define FILAS 6
#define TAMANO_CADENA 200
#define NOMBRE_FICHERO_SORTEO "historico.dat"

int vecesSorteo;

typedef struct
{   int dia,mes,ano;
    int vecesSorteo;
    int quiniela[FILAS];
    double premios[5];
    
} infoSorteo;

typedef struct 
{
    double aciertos[7];
    int numSorteo;
    char fechaSorteo[100];
    double recaudacion;
    int quiniela[FILAS];
} lineaSorteo;

typedef struct estructuras
{
    int combinacion[FILAS];
    char codigoIdentificador[10];
    int jornada;
} lineaApuesta;
