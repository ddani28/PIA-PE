#include <stdio.h>
#include <string.h>
#include <time.h>

struct Grupos
{
    int claveGrupo, semestre, claveMateria, numEmpleado;
    char fecha[20], periodoGrupo[20];
};

main()
{
    struct Grupos gp[50];
    int cantidad;

    printf("¿Cuantos grupos desea ingresar? ");
    scanf("%d", &cantidad);

    for (int i = 0; i < cantidad; i++)
	{
        printf("\n--- Ingresando datos para el grupo %d ---\n", i + 1);
        ingresarGrupos(gp, i);
    }

    return 0;
}

void ingresarGrupos(struct Grupos gp[], int i)
{
    int clave, semestre, claveMateria, numEmpleado, dia, mes, anio;
    
    do
	{
        printf("\nIngresa la clave del grupo: ");
        scanf("%d", &clave);
        if (clave < 0)
            printf("Ingrese una clave mayor a 0\n");
    } while (clave < 0);

    gp[i].claveGrupo = clave;

    do
	{
        printf("Ingresa el semestre del grupo: ");
        scanf("%d", &semestre);
        if (semestre <= 0 || semestre > 10)
            printf("Ingrese un semestre mayor a 0 y menor o igual a 10\n");
    } while (semestre <= 0 || semestre > 10);

    gp[i].semestre = semestre;

    do
	{
        printf("Ingresa la clave de la materia: ");
        scanf("%d", &claveMateria);
        if (claveMateria <= 0)
            printf("La clave de la materia debe ser un número mayor a 0\n");
    } while (claveMateria <= 0);

    gp[i].claveMateria = claveMateria;

    do
	{
        printf("Ingresa el numero de empleado: ");
        scanf("%d", &numEmpleado);
        if (numEmpleado <= 0)
            printf("El número de empleado debe ser un numero mayor a 0\n");
    } while (numEmpleado <= 0);

    gp[i].numEmpleado = numEmpleado;

    time_t t = time(NULL);
    struct tm fechaActual = *localtime(&t);

    do {
        printf("Ingrese la fecha del grupo:\n");
        printf("Dia: ");
        scanf("%d", &dia);
        printf("Mes: ");
        scanf("%d", &mes);
        printf("Año: ");
        scanf("%d", &anio);

        if (anio > fechaActual.tm_year + 1900 ||
            (anio == fechaActual.tm_year + 1900 && mes > fechaActual.tm_mon + 1) ||
            (anio == fechaActual.tm_year + 1900 && mes == fechaActual.tm_mon + 1 && dia > fechaActual.tm_mday)) {
            printf("La fecha ingresada es mayor que la fecha actual. Intente nuevamente.\n");
        } else {
            break;
        }

    } while (1);

    sprintf(gp[i].fecha, "%02d/%02d/%04d", dia, mes, anio);

    printf("Fecha registrada: %s\n", gp[i].fecha);
}
