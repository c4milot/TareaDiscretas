#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[20];
    char pais[20];
    int edad;
    int creadorContenido;
    int numAmigos;
    char** amigos;
    int numIntereses;
    char** intereses;
} Usuario;

int main(int argc, char const* argv[]) {
    int cantidadUsuarios;
    char nombreArchivo[200];
    char buff[200];

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

    // Prints de prueba
    printf("Cantidad de usuarios: %d\n", cantidadUsuarios);
    for (int i = 0; i < cantidadUsuarios; ++i) {
        printf("Nombre: %s\n", usuarios[i].nombre);
        printf("País: %s\n", usuarios[i].pais);
        printf("Edad: %d\n", usuarios[i].edad);
        printf("Creador de contenido: %d\n", usuarios[i].creadorContenido);
        printf("Número de amigos: %d\n", usuarios[i].numAmigos);
        printf("Amigos:\n");
        for (int j = 0; j < usuarios[i].numAmigos; ++j) {
            printf("- %s\n", usuarios[i].amigos[j]);
        }

        printf("Número de intereses: %d\n", usuarios[i].numIntereses);
        printf("intereses:\n");
        for (int j = 0; j < usuarios[i].numIntereses; ++j) {
            printf("- %s\n", usuarios[i].intereses[j]);
        }
        printf("\n");


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
