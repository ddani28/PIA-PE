#include <stdio.h>
#include <time.h>

struct Grupos
{
	int claveGrupo, semestre, claveMateria, numEmpleado;
	char periodoGrupo[20];
	struct Fecha fh;
};

main()
{
	struct Grupos gp[50];
}


void ingresarGrupos(struct Grupos gp)
{
	int i;
	do 
	{
		printf("\nIngresa la clave del grupo: ");
		scanf("%d", &gp->claveGrupo);
		if (gp->claveGrupo < 0)
			printf("Ingrese una clave mayor a 0");
	}while(gp->claveGrupo < 0);
				
	do 
	{	
		printf("\nIngresa el semestre del grupo: ");
		scanf("%d", &gp->semestre);
		if (gp->semestre < 0 || gp->semestre > 10)
			printf("Ingrese un semestre mayor a 0 y menor a 10");
		
	}while(gp->semestre < 0 || gp->semestre > 10);
				
	do 
	{
		printf("\nIngresa la clave de la materia: ");
		fflush(stdin);
		scanf("%s", &gp->claveMateria);
				
		if (strlen(gp->claveMateria) == 0) 
        	printf("La clave no puede estar vacío. Intente de nuevo.\n");
		
	}while (strlen(gp->claveMateria) == 0);
			
	do 
	{
		printf("\nIngresa el numero de empleado: ");
		fflush(stdin);
		scanf("%s", &gp->numEmpleado);
		if (strlen(gp->numEmpleado) == 0) 
        	printf("El numero de empleado no puede estar vacio. Intente de nuevo.\n");
		
	}while (strlen(gp->numEmpleado) == 0);
	
	time_t t = time(NULL);
	struct tm fechaActual = *localtime(&t);

	do
	{
		printf("Ingrese su fecha de grupo:\n");
		printf("Dia: ");
		scanf("%d", &gp->fh->dia);
		printf("Mes: ");
		scanf("%d", &gp->fh->mes);
		printf("Anio: ");
		scanf("%d", &gp->fh->anio;
		
		if( dia > fechaActual.tm_mday || mes > fechaActual.tm_mon + 1 || anio > fechaActual.tm_year + 1900)
			printf("La fecha ingresada es mayor que la fecha actual. Intente nuevamente.\n");
		
	}while (dia < fechaActual.tm_mday && mes < fechaActual.tm_mon + 1 && anio < fechaActual.tm_year + 1900)
		
    sprintf(gp[i].fecha, "%02d/%02d/%04d", dia, mes, anio);
	/*Falta periodo asi como validar claveMateria y numEmpleado con sus estructuras
	respectivas*/
}

