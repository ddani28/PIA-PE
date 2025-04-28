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
	int i, clave, semestre, claveMateria, numEmpleado, dia, mes, anio;
	
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
        	printf("La clave no puede estar vacío. Intente de nuevo.\n");
		
	}while (strlen(claveMateria) == 0);
			
	strcpy(gp[i].claveMateria, claveMateria);
			
			
	do 
	{
		printf("\nIngresa el numero de empleado: ");
		fflush(stdin);
		scanf("%s", &numEmpleado);
		if (strlen(numEmpleado) == 0) 
        	printf("El numero de empleado no puede estar vacio. Intente de nuevo.\n");
		
	}while (strlen(numEmpleado) == 0);
			
	strcpy(gp[i].numEmpleado, numEmpleado);
	
	
	time_t t = time(NULL);
	struct tm fechaActual = *localtime(&t);

	do
	{
		printf("Ingrese su fecha de grupo:\n");
		printf("Dia: ");
		scanf("%d", &dia);
		printf("Mes: ");
		scanf("%d", &mes);
		printf("Año: ");
		scanf("%d", &anio);
		
		if( dia > fechaActual.tm_mday || mes > fechaActual.tm_mon + 1 || anio > fechaActual.tm_year + 1900)
			printf("La fecha ingresada es mayor que la fecha actual. Intente nuevamente.\n");
		
	}while (dia < fechaActual.tm_mday && mes < fechaActual.tm_mon + 1 && anio < fechaActual.tm_year + 1900)
		
    sprintf(gp[i].fecha, "%02d/%02d/%04d", dia, mes, anio);
	/*Falta fecha y periodo asi como validar claveMateria y numEmpleado con sus estructuras
	respectivas*/
		
	
}

