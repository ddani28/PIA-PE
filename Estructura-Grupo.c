#include <stdio.h>
#include <string.h>
#include <time.h>

int esBisiesto(int anio) {
    return (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
}

int esFechaValida(int dia, int mes, int anio) {
    int diasPorMes[] = {31, (esBisiesto(anio) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1 || dia > diasPorMes[mes - 1]) return 0;
    return 1;
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

void ingresarGrupos(struct Grupos *gp, FILE *f) {
    do {
        printf("\nIngresa la clave del grupo: ");
        scanf("%d", &gp->claveGrupo);
        if (gp->claveGrupo <= 0)
            printf("\033[1;31mIngrese una clave mayor a 0\033[0m\n");
    } while (gp->claveGrupo <= 0);

    do {
        printf("\nIngresa el semestre del grupo: ");
        scanf("%d", &gp->semestre);
        if (gp->semestre <= 0 || gp->semestre > 10)
            printf("\033[1;31mIngrese un semestre entre 1 y 10\033[0m\n");
    } while (gp->semestre <= 0 || gp->semestre > 10);

    printf("\nIngresa la clave de la materia: ");
    scanf("%d", &gp->claveMateria);

    do {
        printf("\nIngresa el número de empleado: ");
        scanf(" %9[^\n]", gp->numEmpleado);
        if (strlen(gp->numEmpleado) == 0) {
            printf("\033[1;31mEl número de empleado no puede estar vacío.\033[0m\n");
        } else if (numEmpleadoYaExiste(gp->numEmpleado)) {
            printf("\033[1;31mEl número de empleado '%s' ya está registrado. Ingrese otro.\033[0m\n", gp->numEmpleado);
            gp->numEmpleado[0] = '\0';
        }
    } while (strlen(gp->numEmpleado) == 0);

    printf("\nIngresa el periodo del grupo (ej. 2025-1): ");
    scanf(" %19[^\n]", gp->periodoGrupo);

    time_t t = time(NULL);
    struct tm fechaActual = *localtime(&t);

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
            printf("\033[1;31mLa fecha ingresada es mayor que la fecha actual.\033[0m\n");
        } else if (!esFechaValida(gp->fh.dia, gp->fh.mes, gp->fh.anio)) {
            printf("\033[1;31mFecha inválida. Verifique el día y el mes (especialmente en años bisiestos).\033[0m\n");
        } else {
            break;
        }

    } while (1);

    sprintf(gp->fecha, "%02d/%02d/%04d", gp->fh.dia, gp->fh.mes, gp->fh.anio);

    fprintf(f, "%d,%d,%d,%s,%s,%s\n",
            gp->claveGrupo, gp->semestre, gp->claveMateria,
            gp->numEmpleado, gp->periodoGrupo, gp->fecha);

    printf("\033[1;32mGrupo guardado correctamente.\033[0m\n");
}

void mostrarGrupos() {
    FILE *f = fopen("grupos.txt", "r");
    if (!f) {
        printf("\033[1;31mNo se pudo abrir el archivo o no hay grupos guardados.\033[0m\n");
        return;
    }

    struct Grupos temp;
    printf("\n%-10s %-9s %-10s %-12s %-15s %-12s\n",
           "ClaveGrp", "Semestre", "ClaveMat", "NumEmpleado", "Periodo", "Fecha");
    printf("--------------------------------------------------------------------------\n");

    while (fscanf(f, "%d,%d,%d,%9[^,],%19[^,],%10[^\n]\n",
           &temp.claveGrupo, &temp.semestre, &temp.claveMateria,
           temp.numEmpleado, temp.periodoGrupo, temp.fecha) == 6) {
        printf("%-10d %-9d %-10d %-12s %-15s %-12s\n",
               temp.claveGrupo, temp.semestre, temp.claveMateria,
               temp.numEmpleado, temp.periodoGrupo, temp.fecha);
    }

    fclose(f);
}
