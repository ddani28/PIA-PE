#include <stdio.h>
#include <string.h>

struct Materias {
    int clave, semestre;
    char nombre[20];	
};

void ingresarMaterias(struct Materias *mt) {
    FILE *f = fopen("materias.txt", "a");
    if (!f) {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    do {
        printf("\nIngresa la clave de la materia: ");
        scanf("%d", &mt->clave);
        if (mt->clave <= 0)
            printf("Ingrese una clave mayor a 0\n");
    } while (mt->clave <= 0);

    do {
        printf("\nIngresa el semestre de la materia: ");
        scanf("%d", &mt->semestre);
        if (mt->semestre <= 0 || mt->semestre > 10)
            printf("Ingrese un semestre entre 1 y 10\n");
    } while (mt->semestre <= 0 || mt->semestre > 10);

    do {
        printf("\nIngresa el nombre de la materia: ");
        scanf(" %19[^\n]", mt->nombre);
        if (strlen(mt->nombre) == 0)
            printf("El nombre no puede estar vacío.\n");
    } while (strlen(mt->nombre) == 0);

    fprintf(f, "%d,%d,%s\n", mt->clave, mt->semestre, mt->nombre);
    fclose(f);
    printf("Materia guardada correctamente.\n");
}

