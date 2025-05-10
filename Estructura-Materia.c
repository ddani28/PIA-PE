#include <stdio.h>

struct Materias 
{
	int clave, semestre;
	char nombre[20];	
};


void ingresarMaterias(struct Materias mt)
{
	do 
	{
		printf("\nIngresa la clave de la materia: ");
		scanf("%d", &mt->clave);
				
		if (mt->clave < 0)
			printf("Ingrese una clave mayor a 0");
			
	}while(mt->clave < 0);
		
	do 
	{
		printf("\nIngresa el semestre de la materia: ");
		scanf("%d", &mt->semestre);
		
		if (mt->semestre < 0 || mt->semestre > 10)
			printf("Ingrese un semestre mayor a 0 y menor a 10");
			
	}while(mt->clave < 0 || mt->semestre > 10);
							
	do 
	{
		printf("\nIngresa el nombre de la materia: ");
		fflush(stdin);
		scanf("%s", &mt->nombre);
		if (strlen(mt->nombre) == 0) 
        		printf("El nombre no puede estar vacio. Intente de nuevo.\n");
        		
	}while (strlen(mt->nombre) == 0);
}



