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

    void encontrarAristas(int cantidadUsuarios, Usuario* usuarios){
        for (int i = 0; i < cantidadUsuarios; ++i)
        {
            for (int j = 0; j < cantidadUsuarios; ++j)
            {
                for (int k = 0; k < usuarios[i].numAmigos; ++k)
                {
                    if (strcmp(usuarios[i].amigos[k], usuarios[j].nombre) == 0 && usuarios[j].creadorContenido == 1)
                    {
                        usuarios[i].numAristas++;
                        usuarios[i].aristas = realloc(usuarios[i].aristas, sizeof(int)* usuarios[i].numAristas);
                        usuarios[i].aristas[usuarios[i].numAristas-1] = j;
                        usuarios[j].numAristas++;
                        usuarios[j].aristas = realloc(usuarios[j].aristas, sizeof(int)* usuarios[j].numAristas);
                        usuarios[j].aristas[usuarios[j].numAristas-1] = i;
                        printf("el usuario %s esta unido a %s \n", usuarios[i].nombre, usuarios[j].nombre);
                    }
                }
            }
        }
    }
    
    void DFS(){

    }

    int main(int argc, char const* argv[]) {
        int cantidadUsuarios;
        char nombreArchivo[200];
        char buff[200];
        char filtropais[20];
        int filtropaisB = -2;
        int filtroMin = -1;
        int filtroMax = -1;
        char filtrointA[20];
        int filtrointB = -2;

        FILE* archivo = NULL;

        // Asigna el nombre automáticamente para ahorrar tiempo de pruebas
        archivo = fopen("red.txt", "r");

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
        
        while (filtropaisB < -1 || 0 < filtropaisB) {
            printf("Ingrese el pais (-1 si no importa): ");
            scanf("%s", filtropais);
            if(strcmp(filtropais, "-1") == 0){
                filtropaisB = -1;
            }else{
                filtropaisB = 0;
            }
        }

        while (filtroMin < 0 || 120 < filtroMin) {
            printf("Ingrese la edad minima (0 si no importa): ");
            scanf(" %d", &filtroMin);
            while( getchar() != '\n' );
        }
        
        while (filtroMax < 0 || 120 < filtroMax) {
            printf("Ingrese la edad maxima (120 si no importa): ");
            scanf(" %d", &filtroMax);
            while( getchar() != '\n' );
        }

        while (filtrointB < -1 || 0 < filtrointB) {
            printf("Ingrese el interes (-1 si no importa): ");
            scanf("%s", filtrointA);
            if(strcmp(filtrointA, "-1") == 0){
                filtrointB = -1;
            }else{
                filtrointB = 0;
            }
        }

        
        printf("Parametros: %d %d %d %d \n", filtropaisB, filtroMin, filtroMax, filtrointB);
        printf("Parametros: %s   %s \n", filtropais, filtrointA);

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

            usuarios[i].visitado = false;
            usuarios[i].distancia = -1;
            usuarios[i].padre = -1;
            usuarios[i].numAristas = 0;
        }

        encontrarAristas(cantidadUsuarios, usuarios);
        

        // Prints de prueba
        printf("Cantidad de usuarios: %d\n", cantidadUsuarios);
        for (int i = 0; i < cantidadUsuarios; ++i) {
            printf("Nombre: %s\n", usuarios[i].nombre);
            printf("Pais: %s\n", usuarios[i].pais);
            printf("Edad: %d\n", usuarios[i].edad);
            printf("Creador de contenido: %d\n", usuarios[i].creadorContenido);
            printf("Numero de amigos: %d\n", usuarios[i].numAmigos);
            printf("Amigos:\n");
            for (int j = 0; j < usuarios[i].numAmigos; ++j) {
                printf("- %s\n", usuarios[i].amigos[j]);
            }

            printf("Numero de intereses: %d\n", usuarios[i].numIntereses);
            printf("intereses:\n");
            for (int j = 0; j < usuarios[i].numIntereses; ++j) {
                printf("- %s\n", usuarios[i].intereses[j]);
            }

            printf("aristas:\n");
            for (int j = 0; j < usuarios[i].numAristas; ++j)
            {
                printf("%d\n", usuarios[i].aristas[j]);
            }
            printf("\n");
        }

        printf("Cantidad de usuarios: %d\n", cantidadUsuarios);
        for (int i = 0; i < cantidadUsuarios; ++i) {
            printf("%s", usuarios[i].nombre);
            if(i<cantidadUsuarios-1) printf(", ");
        }

        printf("\nParametros: %d %d %d %d \n", filtropaisB, filtroMin, filtroMax, filtrointB);
        printf("Parametros: %s   %s \n", filtropais, filtrointA);
    
        //Test del filtro
        for (int i = 0; i < cantidadUsuarios; ++i) {
            
            if(strcmp(filtropais, "-1") == 0){           //Si no hay filtro pais
                if(filtroMin < usuarios[i].edad && usuarios[i].edad < filtroMax){
                    if(filtrointB == -1){ //Si no hay filtro interes
                      printf("%s ", usuarios[i].nombre);
                    }else if(filtrointB == 0){ //Si hay filtro interes
                        int tam = sizeof(usuarios[i].intereses) / sizeof(usuarios[i].intereses[0]);
                        for(int j = 0; j < tam; ++j){
                            if(strcmp(filtrointA, usuarios[i].intereses[j]) == 0){
                                printf("%s ", usuarios[i].nombre);
                                j = tam-1;
                            }
                        }
                    }
                }
            }else if(strcmp(filtropais, "-1") != 0){     //Si hay filtro pais
                if(strcmp(usuarios[i].pais, filtropais) == 0){
                    if(filtroMin < usuarios[i].edad && usuarios[i].edad < filtroMax){
                        if(filtrointB == -1){ //Si no hay filtro interes
                          printf("%s ", usuarios[i].nombre);
                        }else if(filtrointB == 0){ //Si hay filtro interes
                            int tam = sizeof(usuarios[i].intereses) / sizeof(usuarios[i].intereses[0]);
                            for(int j = 0; j < tam; ++j){
                                if(strcmp(filtrointA, usuarios[i].intereses[j]) == 0){
                                    printf("%s ", usuarios[i].nombre);
                                    j = tam-1;
                                }
                            }
                        }
                    }
                }
            }
        }
        //idealmente añadir los nombres a un arreglo de strings lo que no me acuerdo como se hacia ahora mismo

        
        for (int i = 0; i < cantidadUsuarios; ++i) {
            //hacer que busque caminos entre los usuarios y que vea cuando no existe caminos entre los grupos
            for(int j = 0; j < cantidadUsuarios; ++j){
                for(int k = 0; k< cantidadUsuarios; ++k){
                    strcmp(usuarios[i].nombre, usuarios[j].amigos[k]);
                }
            }
        }


        // Liberar la memoria asignada
        for (int i = 0; i < cantidadUsuarios; ++i) {
            for (int j = 0; j < usuarios[i].numAmigos; ++j) {
                free(usuarios[i].amigos[j]);
            }
            free(usuarios[i].amigos);
        }

        // Liberar la memoria asignada
        for (int i = 0; i < cantidadUsuarios; ++i) {
            for (int j = 0; j < usuarios[i].numIntereses; ++j) {
                free(usuarios[i].intereses[j]);
            }
            free(usuarios[i].intereses);
        }
        free(usuarios);

        fclose(archivo);

        return 0;
    }
