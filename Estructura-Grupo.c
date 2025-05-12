#include <stdio.h>
#include <string.h>
#include <time.h>

// Función para verificar si un año es bisiesto
int esBisiesto(int anio) {
    return (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
}

// Función para validar la fecha
int esFechaValida(int dia, int mes, int anio) {
    // Meses con 31 días
    int diasPorMes[] = {31, (esBisiesto(anio) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Validar si el mes está en el rango 1-12
    if (mes < 1 || mes > 12) {
        return 0;  // Fecha inválida
    }

    // Validar si el día está en el rango válido para el mes
    if (dia < 1 || dia > diasPorMes[mes - 1]) {
        return 0;  // Fecha inválida
    }

    return 1;  // Fecha válida
}

struct Fecha {
    int dia, mes, anio;
};

struct Grupos {
    int claveGrupo, semestre, claveMateria;
    char numEmpleado[10];
    char periodoGrupo[20], fecha[11];
    struct Fecha fh;
};

int numEmpleadoYaExiste(const char *numBuscado) {
    FILE *f = fopen("grupos.txt", "r");
    if (!f) return 0;

    struct Grupos temp;
    while (fscanf(f, "%d,%d,%d,%9[^,],%19[^,],%10[^\n]\n",
           &temp.claveGrupo, &temp.semestre, &temp.claveMateria,
           temp.numEmpleado, temp.periodoGrupo, temp.fecha) == 6) {
        if (strcmp(temp.numEmpleado, numBuscado) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void ingresarGrupos(struct Grupos *gp) {
    FILE *f = fopen("grupos.txt", "a");
    if (!f) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    // Clave del grupo
    do {
        printf("\nIngresa la clave del grupo: ");
        scanf("%d", &gp->claveGrupo);
        if (gp->claveGrupo <= 0)
            printf("Ingrese una clave mayor a 0\n");
    } while (gp->claveGrupo <= 0);

    // Semestre
    do {
        printf("\nIngresa el semestre del grupo: ");
        scanf("%d", &gp->semestre);
        if (gp->semestre <= 0 || gp->semestre > 10)
            printf("Ingrese un semestre entre 1 y 10\n");
    } while (gp->semestre <= 0 || gp->semestre > 10);

    // Clave de la materia
    printf("\nIngresa la clave de la materia: ");
    scanf("%d", &gp->claveMateria);

    // Número de empleado con validación
    do {
        printf("\nIngresa el número de empleado: ");
        scanf(" %9[^\n]", gp->numEmpleado);
        if (strlen(gp->numEmpleado) == 0) {
            printf("El número de empleado no puede estar vacío.\n");
        } else if (numEmpleadoYaExiste(gp->numEmpleado)) {
            printf("El número de empleado '%s' ya está registrado. Ingrese otro.\n", gp->numEmpleado);
            gp->numEmpleado[0] = '\0';
        }
    } while (strlen(gp->numEmpleado) == 0);

    // Periodo del grupo
    printf("\nIngresa el periodo del grupo (ej. 2025-1): ");
    scanf(" %19[^\n]", gp->periodoGrupo);

    // Fecha actual
    time_t t = time(NULL);
    struct tm fechaActual = *localtime(&t);

    // Ingreso de fecha válida (no futura)
    do {
        printf("Ingrese la fecha del grupo (no mayor a la actual):\n");
        printf("Dia: ");
        scanf("%d", &gp->fh.dia);
        printf("Mes: ");
        scanf("%d", &gp->fh.mes);
        printf("Anio: ");
        scanf("%d", &gp->fh.anio);

        if (gp->fh.anio > fechaActual.tm_year + 1900 ||
            (gp->fh.anio == fechaActual.tm_year + 1900 && gp->fh.mes > fechaActual.tm_mon + 1) ||
            (gp->fh.anio == fechaActual.tm_year + 1900 && gp->fh.mes == fechaActual.tm_mon + 1 && gp->fh.dia > fechaActual.tm_mday)) {
            printf("La fecha ingresada es mayor que la fecha actual. Intente nuevamente.\n");
        } else if (!esFechaValida(gp->fh.dia, gp->fh.mes, gp->fh.anio)) {
            printf("Fecha inválida. Verifique el día y el mes (especialmente en años bisiestos).\n");
        } else {
            break; // Fecha válida
        }

    } while (1);

    // Guardar fecha como texto
    sprintf(gp->fecha, "%02d/%02d/%04d", gp->fh.dia, gp->fh.mes, gp->fh.anio);

    // Guardar en archivo como texto plano
    fprintf(f, "%d,%d,%d,%s,%s,%s\n",
            gp->claveGrupo, gp->semestre, gp->claveMateria,
            gp->numEmpleado, gp->periodoGrupo, gp->fecha);

    fclose(f);
    printf("Grupo guardado correctamente.\n");
}


