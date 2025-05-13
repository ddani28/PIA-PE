#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

struct Materias 
{
	int clave, semestre;
	char nombre[20];	
};

struct Fecha
{
    int dia, mes, anio;
};

struct Grupos {
    int claveGrupo, semestre, claveMateria;
    char numEmpleado[10];
    char periodoGrupo[20], fecha[11];
    struct Fecha fh;
};

struct Inscripcion 
{
    int folio, grupo, matricula;
    char fecha[20];
    struct Grupos grupoIns;
};

struct Direccion
{
    char calle[50], colonia[50], municipio[50], estado[50];
    int numero;
};


struct Alumno
{
    int matricula, semestre;
    float promedios[10];
    char nombre[100], carrera[50], telefono[11], correo[100];
    struct Fecha nacimiento;
    struct Direccion direccion;
};

struct Profesor
{
    int numEmpleado, totalMaterias, coordinacion;
    char nombre[100], correo[100], telefono[11], clavesMaterias[10][20];
    struct Fecha nacimiento;
    struct Direccion direccion;
};

//void ingresarMaterias(struct Materias *mt);

main()
{
    int opcion;
    struct Materias mat;
    struct Grupos grupo;

    do {
        printf("\nMenu principal \n");
        printf("1. Alumnos\n");
        printf("2. Profesores\n");
        printf("3. Materias\n");
        printf("4. Grupo\n");
        printf("5. Inscripcion\n");
        printf("6. Actualizar promedio\n");
        printf("7. Reportes\n");
        printf("8. Salir\n");

        printf("Ingrese la opcion deseada: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // alumnos(&alumno, archivo_alumnos);
                break;

            case 2:
                // profesores(&prof, archivo_profesores);
                break;
        
            case 3: {
                FILE *f = fopen("materias.txt", "a");
                if (!f) {
                    printf("\033[1;31mNo se pudo abrir el archivo de materias.\033[0m\n");
                } else {
                    ingresarMaterias(&mat, f);
                    fclose(f);
                }
                break;
            }

            case 4:{

                int subop;
                printf("\n--- Modulo de Grupos ---\n");
                printf("1. Ingresar grupo\n");
                printf("2. Mostrar grupos\n");
                printf("Seleccione una opcion: ");
                scanf("%d", &subop);
                if (subop == 1) {
                    FILE *f = fopen("grupos.txt", "a");
                    if (!f) {
                        printf("\033[1;31mNo se pudo abrir el archivo.\033[0m\n");
                    } else {
                        ingresarGrupos(&grupo, f);
                        fclose(f);
                    }
                } else if (subop == 2) {
                    mostrarGrupos();
                } else {
                    printf("\033[1;31mOpcion no valida.\033[0m\n");
                }
                break;
}
            case 5:
                // inscripciones(&insc, archivo_inscripciones);
                break;

            case 6:
                // actualizarPromedio();
                break;

            case 7:
                // menuReportes();
                break;

            case 8:
                printf("Saliendo del sistema...\n");
                break;

            default:
                printf("\033[1;31mPor favor ingrese una opcion valida (1-8).\033[0m\n");
        }

    } while (opcion != 8);

    return 0;
}

void textoRojo() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
}

void textoNormal() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void ingresarMaterias(struct Materias *mt, FILE *f) {
    if (!f) {
        textoRojo();
        printf("No se pudo acceder al archivo de materias\n");
        textoNormal();
        return;
    }

    do {
        printf("\nIngresa la clave de la materia: ");
        scanf("%d", &mt->clave);
        if (mt->clave <= 0) {
            textoRojo(); printf("Ingrese una clave mayor a 0\n"); textoNormal();
        }
    } while (mt->clave <= 0);

    do {
        printf("Ingresa el semestre de la materia: ");
        scanf("%d", &mt->semestre);
        if (mt->semestre <= 0 || mt->semestre > 10) {
            textoRojo(); printf("Ingrese un semestre entre 1 y 10\n"); textoNormal();
        }
    } while (mt->semestre <= 0 || mt->semestre > 10);

    do {
        printf("Ingresa el nombre de la materia: ");
        scanf(" %19[^\n]", mt->nombre);
        if (strlen(mt->nombre) == 0) {
            textoRojo(); printf("El nombre no puede estar vacío.\n"); textoNormal();
        }
    } while (strlen(mt->nombre) == 0);

    fprintf(f, "%d,%d,%s\n", mt->clave, mt->semestre, mt->nombre);
    printf("Materia guardada correctamente.\n");
}

void mostrarMaterias(FILE *f) {
    if (!f) {
        textoRojo(); printf("No se pudo abrir el archivo o no hay materias guardadas.\n"); textoNormal();
        return;
    }

    rewind(f);
    int clave, semestre;
    char nombre[20];

    printf("\n%-10s %-10s %-20s\n", "Clave", "Semestre", "Nombre");
    printf("--------------------------------------------\n");

    while (fscanf(f, "%d,%d,%19[^\n]\n", &clave, &semestre, nombre) == 3) {
        printf("%-10d %-10d %-20s\n", clave, semestre, nombre);
    }
}



/*GRUPOSSSSSS*/


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

// ========== FUNCIONES PRINCIPALES ==========

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

