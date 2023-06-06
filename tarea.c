#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char nombre[20];
	char pais[20];
	int edad;
	int creadorContenido;

	
}usuario;

int main(int argc, char const *argv[]){

	int cantidadUsuarios;
	char nombreArchivo[200];
	char buff[200];
	
	FILE *archivo = NULL;

	while(archivo == NULL){
		printf("Ingrese el nombre del archivo: ");
		scanf("%s", nombreArchivo);
		archivo = fopen(nombreArchivo, "r");
		if (archivo==NULL){
			printf("Archivo no encontrado\n");
		}
	}

	fgets(buff, 200, archivo);
	cantidadUsuarios = atoi(buff);

	printf("nuevo %d\n", cantidadUsuarios);

	usuario *usuarios = malloc(sizeof(usuario) * cantidadUsuarios);
	for (int i = 0; i < 1; ++i){
		fscanf(archivo, "%s\n", usuarios[i].nombre);
		fscanf(archivo, "%s\n", usuarios[i].pais);
		fscanf(archivo, "%d\n", &usuarios[i].edad);
		fscanf(archivo, "%d\n", &usuarios[i].creadorContenido);
	}

	for (int i = 0; i < 1; ++i){
		printf("%s\n", usuarios[i].nombre);
		printf("%s\n", usuarios[i].pais);
		printf("%d\n", usuarios[i].edad);
		printf("%d\n", usuarios[i].creadorContenido);
		
	}


	
	
	printf("Primer nombre: %s\n", usuarios[0].nombre);

	return 0;
}