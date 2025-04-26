#include <stdio.h>
#include <time.h>

struct Grupos
{
	int claveGrupo, semestre, claveMateria, numEmpleado;
	char fecha[20], periodoGrupo[20];
};

main()
{
	struct Grupos gp[50];
}


void ingresarGrupos(struct Grupos gp[])
{
	int i, clave, semestre, claveMateria, numEmpleado;
	
	do 
	{
		printf("\nIngresa la clave del grupo: ");
		scanf("%d", &clave);
		if (clave < 0)
			printf("Ingrese una clave mayor a 0");
	}while(clave < 0);
			
	gp[i].claveGrupo = clave;
				
	do 
	{	
		printf("\nIngresa el semestre del grupo: ");
		scanf("%d", &semestre);
		if (semestre < 0 || semestre > 10)
			printf("Ingrese un semestre mayor a 0 y menor a 10");
	}while(semestre < 0 || semestre > 10);
			
	gp[i].semestre = semestre;
				
	do 
	{
		printf("\nIngresa la clave de la materia: ");
		fflush(stdin);
		scanf("%s", &claveMateria);
				
		if (strlen(claveMateria) == 0) 
		{
        	printf("La clave no puede estar vacío. Intente de nuevo.\n");
    	}
	}while (strlen(claveMateria) == 0);
			
	strcpy(gp[i].claveMateria, claveMateria);
			
			
	do 
	{
		printf("\nIngresa el numero de empleado: ");
		fflush(stdin);
		scanf("%s", &numEmpleado);
		if (strlen(numEmpleado) == 0) 
		{
        	printf("El numero de empleado no puede estar vacio. Intente de nuevo.\n");
    	}
	}while (strlen(numEmpleado) == 0);
			
	strcpy(gp[i].numEmpleado, numEmpleado);
	
	/*Falta fecha y periodo asi como validar claveMateria y numEmpleado con sus estructuras
	respectivas*/
		
	
}

