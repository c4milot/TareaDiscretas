#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

typedef struct {
    char nombre[20];
    char pais[20];
    int edad;
    int creadorContenido;
    int numAmigos;
    char** amigos;
    int numIntereses;
    char** intereses;
    bool visitado;
    int distancia;
    int padre;
    int numAristas;
    int* aristas;
} Usuario;

void BFS(int cantidadUsuarios, Usuario* usuarios, int origen){
    int* cola = malloc(sizeof(int) * cantidadUsuarios);
    int frente = 0;
    int final = 0;
    usuarios[origen].visitado = true;
    usuarios[origen].distancia = 0;
    cola[final++] = origen;
    while (frente != final) {
        int actual = cola[frente++];
        Usuario usuarioActual = usuarios[actual];
        for (int i = 0; i < usuarioActual.numAristas; ++i) {
            int vecino = usuarioActual.aristas[i];
            if (!usuarios[vecino].visitado) {
                usuarios[vecino].visitado = true;
                usuarios[vecino].distancia = usuarioActual.distancia + 1;
                usuarios[vecino].padre = actual;
                cola[final++] = vecino;
            }
        }
    }
    printf("tiene %d cuentas de usuarios.\n", final);
    int numCreadores = 0;
    int numUsuarios = 0;
    int menorDistaciaC = -1;
    int menorDistacia = -1;
    for (int i = 0; i < final; ++i)
    {
        if (usuarios[cola[i]].creadorContenido == 1)
        { 
            numCreadores++;
            if (usuarios[cola[i]].distancia < menorDistaciaC || menorDistaciaC == -1)
            {
                menorDistaciaC = usuarios[cola[i]].distancia;
            }
        }else{
            numUsuarios++;
            if (usuarios[cola[i]].distancia < menorDistacia || menorDistacia == -1)
            {
                menorDistacia = usuarios[cola[i]].distancia;
            }
        }
    }

    if (numCreadores == 0)
    {
        printf("Esta comunidad no tiene creadores de contenido ");
    }else{
        printf("Esta comunidad tiene %d creadores de contenido ", numCreadores);
    }
    if (numUsuarios == 0)
    {
        printf("y no tiene usuarios regulares\n");
    }else{
        printf("y tiene %d usuarios regulares\n", numUsuarios);
    }
    if (numCreadores != 0){
        printf("Mejores creadores de contenido:\n");
        for (int i = 0; i < final; ++i)
        {
            if (usuarios[cola[i]].creadorContenido == 1 && (usuarios[cola[i]].distancia == menorDistaciaC || final == 2))
            {
                printf("    %s\n", usuarios[cola[i]].nombre);
            }
        }
    }
    if (numUsuarios != 0){
        printf("Mejores usuarios:\n");
        for (int i = 0; i < final; ++i)
        {       
            if (usuarios[cola[i]].creadorContenido != 1 && (usuarios[cola[i]].distancia == menorDistacia || final == 2))
            {
                printf("    %s\n", usuarios[cola[i]].nombre);
            }
        }
    }
    free(cola);
}

void aplicarFiltros(Usuario* usuarios, int cantidadUsuarios, char* filtropais, int filtroMin, int filtroMax, char* filtrointA){
    for (int i = 0; i < cantidadUsuarios; ++i)
    {
        if (strcasecmp(filtropais, "-1"))
        {
            if(strcasecmp(filtropais, usuarios[i].pais)){
                usuarios[i].visitado = true;
            }
        }
        if (filtroMin != 0)
        {
            if (usuarios[i].edad < filtroMin)
            {
                usuarios[i].visitado = true;
            }
        }
        if (filtroMax < usuarios[i].edad)
        {
            usuarios[i].visitado = true;
        }
        if (strcasecmp(filtrointA, "-1") && !usuarios[i].visitado)
        {
            bool aux = true;
    
            for (int j = 0; j < usuarios[i].numIntereses; ++j)
            {
                if(!strcasecmp(filtrointA, usuarios[i].intereses[j])){
                    aux = false;
                }
            }
            usuarios[i].visitado = aux;
        }
    }
}

void encontrarAristas(int cantidadUsuarios, Usuario* usuarios){
    for (int i = 0; i < cantidadUsuarios; ++i)
    {
        for (int j = 0; j < cantidadUsuarios; ++j)
        {
            for (int k = 0; k < usuarios[i].numAmigos; ++k)
            {
                if (strcasecmp(usuarios[i].amigos[k], usuarios[j].nombre) == 0 && usuarios[j].creadorContenido == 1)
                {
                    usuarios[i].numAristas++;
                    usuarios[i].aristas = realloc(usuarios[i].aristas, sizeof(int)* usuarios[i].numAristas);
                    usuarios[i].aristas[usuarios[i].numAristas-1] = j;
                    usuarios[j].numAristas++;
                    usuarios[j].aristas = realloc(usuarios[j].aristas, sizeof(int)* usuarios[j].numAristas);
                    usuarios[j].aristas[usuarios[j].numAristas-1] = i;
                }else{
                    for (int l = 0; l < usuarios[j].numAmigos; ++l)
                    {
                        if (strcasecmp(usuarios[i].amigos[k], usuarios[j].nombre) == 0 && strcasecmp(usuarios[j].amigos[l], usuarios[i].nombre) == 0 && usuarios[i].creadorContenido == 0)
                        {
                            usuarios[i].numAristas++;
                            usuarios[i].aristas = realloc(usuarios[i].aristas, sizeof(int)* usuarios[i].numAristas);
                            usuarios[i].aristas[usuarios[i].numAristas-1] = j;
                        }
                    }
                }
            }
        }
    }

    int numComunidades = 0;
    for (int i = 0; i < cantidadUsuarios; ++i) {
        if (!usuarios[i].visitado) {
        numComunidades++;
        printf("Comunidad %d\n", numComunidades);
        printf("La comunidad %d tiene ", numComunidades);
        BFS(cantidadUsuarios, usuarios, i);
        }
    }
    if (numComunidades == 0)
    {
        printf("No existen comunidades con los filtros ingresados.\n");
    }
}

    


int main(int argc, char const* argv[]) {
    int cantidadUsuarios;
    char nombreArchivo[200];
    char buff[200];    
    int numComunidades = 0;

    FILE* archivo = NULL;

    // Lectura de archivo
    while (archivo == NULL) {
        printf("Ingrese el nombre del archivo: ");
        scanf("%s", nombreArchivo);
        archivo = fopen(nombreArchivo, "r");
        if (archivo == NULL) {
            printf("Archivo no encontrado\n");
        }
    }

    // Lectura y guardado de datos
    fgets(buff, 200, archivo);
        cantidadUsuarios = atoi(buff);

    // Creación de usuarios en memoria dinámica
    Usuario* usuarios = malloc(sizeof(Usuario) * cantidadUsuarios);

    for (int i = 0; i < cantidadUsuarios; ++i) {
        fscanf(archivo, "%s\n", usuarios[i].nombre);
        fscanf(archivo, "%s\n", usuarios[i].pais);
        fscanf(archivo, "%d\n", &usuarios[i].edad);
        fscanf(archivo, "%d\n", &usuarios[i].creadorContenido);
        fscanf(archivo, "%d\n", &usuarios[i].numAmigos);

        usuarios[i].amigos = malloc(sizeof(char*) * usuarios[i].numAmigos);

        for (int j = 0; j < usuarios[i].numAmigos; ++j) {
            usuarios[i].amigos[j] = malloc(sizeof(char) * 20);
            fscanf(archivo, "%s\n", usuarios[i].amigos[j]);
        }

        fscanf(archivo, "%d\n", &usuarios[i].numIntereses);

        usuarios[i].intereses = malloc(sizeof(char*) * usuarios[i].numIntereses);

        for (int j = 0; j < usuarios[i].numIntereses; ++j) {
            usuarios[i].intereses[j] = malloc(sizeof(char) * 20);
            fscanf(archivo, "%s\n", usuarios[i].intereses[j]);
        }
    }

    fclose(archivo);

    do{

        char filtropais[20];
        int filtropaisB = -2;
        int filtroMin = -1;
        int filtroMax = -1;
        char filtrointA[20];
        int filtrointB = -2;

        for (int i = 0; i < cantidadUsuarios; ++i)
        {
            usuarios[i].visitado = false;
            usuarios[i].distancia = -1;
            usuarios[i].padre = -1;
            usuarios[i].numAristas = 0;
        }

        while (filtropaisB < -1 || filtropaisB > 0) {
        printf("Ingrese el pais (-1 si no importa): ");
        scanf("%s", filtropais);
            if (strcasecmp(filtropais, "-1") == 0) {
                filtropaisB = -1;
            } else {
                filtropaisB = 0;
            }
        }

        while (filtroMin < 0 || filtroMin > 120) {
            printf("Ingrese la edad minima (0 si no importa): ");
            scanf("%d", &filtroMin);
            while (getchar() != '\n');
        }

        while (filtroMax < 0 || filtroMax > 120) {
            printf("Ingrese la edad maxima (120 si no importa): ");
            scanf("%d", &filtroMax);
            while (getchar() != '\n');
        }

        while (filtrointB < -1 || filtrointB > 0) {
            printf("Ingrese el interes (-1 si no importa): ");
            scanf("%s", filtrointA);
            if (strcasecmp(filtrointA, "-1") == 0) {
                filtrointB = -1;
            } else {
                filtrointB = 0;
            }
        }

        aplicarFiltros(usuarios, cantidadUsuarios, filtropais, filtroMin, filtroMax, filtrointA);
        encontrarAristas(cantidadUsuarios, usuarios);

        char respuesta[2];
        printf("Desea realizar otra consulta? (S/N)\n");
        scanf("%s", respuesta);
        if (strcasecmp(respuesta, "N") == 0)
        {
            break;
        }
    }while(1);
        

    
    for (int i = 0; i < cantidadUsuarios; ++i) {
        for (int j = 0; j < usuarios[i].numAmigos; ++j) {
            free(usuarios[i].amigos[j]);
        }
        free(usuarios[i].amigos);
    }

    
    for (int i = 0; i < cantidadUsuarios; ++i) {
        for (int j = 0; j < usuarios[i].numIntereses; ++j) {
            free(usuarios[i].intereses[j]);
        }
        free(usuarios[i].intereses);
    }
    free(usuarios);

    return 0;
}