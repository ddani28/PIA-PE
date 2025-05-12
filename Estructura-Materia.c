#include <stdio.h>
#include <string.h>
#include <windows.h>

struct Materias {
    int clave, semestre;
    char nombre[20];	
};

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

