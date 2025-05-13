#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>  
#include <ctype.h>
#include <time.h>
/*Se corrigio en el main*/
struct Fecha {
    int dia, mes, año;
};


struct Alumno {
    int matricula, semestre;
    float promedios[10];
    char nombre[100], carrera[50], telefono[11], correo[100];
    struct Fecha nacimiento;
};


void ingresarAlumnos(struct Alumno *a, FILE *f);

int esFechaValida(struct Fecha fecha) {
    time_t t = time(NULL);
    struct tm fecha_actual = *localtime(&t);
    if (fecha.año < fecha_actual.tm_year + 1900) return 1;
    if (fecha.año == fecha_actual.tm_year + 1900 && fecha.mes < fecha_actual.tm_mon + 1) return 1;
    if (fecha.año == fecha_actual.tm_year + 1900 && fecha.mes == fecha_actual.tm_mon + 1 && fecha.dia < fecha_actual.tm_mday) return 1;
    return 0;  

int esCorreoValido(char *correo) {
    int atCount = 0;
    int dotCount = 0;
    for (int i = 0; correo[i] != '\0'; i++) {
        if (correo[i] == '@') atCount++;
        if (correo[i] == '.') dotCount++;
    }
    return (atCount == 1 && dotCount >= 1);  
}

int esTelefonoValido(char *telefono) {
    if (strlen(telefono) != 10) return 0;  
    for (int i = 0; i < 10; i++) {
        if (!isdigit(telefono[i])) return 0;  
    }
    return 1;
}

void ingresarAlumnos(struct Alumno *a, FILE *f) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); 
    printf("\nCAPTURA DE ALUMNOS\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); 

    f = fopen("alumnos.txt", "a");  
    if (f == NULL) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); 
        printf("Error al abrir el archivo de alumnos.\n");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        return;
    }

    printf("Matrícula (mayor que 0): ");
    while (scanf("%d", &a->matricula) != 1 || a->matricula <= 0) {
        fflush(stdin);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); 
        printf("Matrícula inválida. Debe ser mayor que 0. Intente de nuevo: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); 
    }

    fflush(stdin);
    printf("Nombre del alumno: ");
    fgets(a->nombre, sizeof(a->nombre), stdin);
    strtok(a->nombre, "\n");

    printf("Carrera (Actuaría, Ciencias Computacionales, Física, Multimedia y Animación Digital, Matemáticas y Seguridad): ");
    fgets(a->carrera, sizeof(a->carrera), stdin);
    strtok(a->carrera, "\n");

    while (strcmp(a->carrera, "Actuaría") != 0 && strcmp(a->carrera, "Ciencias Computacionales") != 0 && 
           strcmp(a->carrera, "Física") != 0 && strcmp(a->carrera, "Multimedia y Animación Digital") != 0 && 
           strcmp(a->carrera, "Matemáticas") != 0 && strcmp(a->carrera, "Seguridad") != 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); 
        printf("Carrera inválida. Las opciones son: Actuaría, Ciencias Computacionales, Física, Multimedia y Animación Digital, Matemáticas y Seguridad. Intente de nuevo: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); 
        fgets(a->carrera, sizeof(a->carrera), stdin);
        strtok(a->carrera, "\n");
    }

    printf("Semestre (1-10): ");
    while (scanf("%d", &a->semestre) != 1 || a->semestre < 1 || a->semestre > 10) {
        fflush(stdin);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf("Semestre inválido. Debe estar entre 1 y 10. Intente de nuevo: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }

    fflush(stdin);
    printf("Fecha de nacimiento (dd/mm/yyyy): ");
    while (scanf("%d/%d/%d", &a->nacimiento.dia, &a->nacimiento.mes, &a->nacimiento.año) != 3 || 
           a->nacimiento.dia < 1 || a->nacimiento.dia > 31 || 
           a->nacimiento.mes < 1 || a->nacimiento.mes > 12 || 
           a->nacimiento.año < 1900 || !esFechaValida(a->nacimiento)) {
        fflush(stdin);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf("Fecha inválida. Intente de nuevo: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }

    fflush(stdin);
    printf("Promedio general de cada semestre (0-100) [Ingrese 10 promedios]: ");
    for (int i = 0; i < 10; i++) {
        printf("\nSemestre %d: ", i + 1);
        while (scanf("%f", &a->promedios[i]) != 1 || a->promedios[i] < 0 || a->promedios[i] > 100) {
            fflush(stdin);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); 
            printf("Promedio inválido. Debe estar entre 0 y 100. Intente de nuevo: ");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); 
        }
    }

    fflush(stdin);
    printf("Correo electrónico (debe contener @ y dominio válido): ");
    while (fgets(a->correo, sizeof(a->correo), stdin) && !esCorreoValido(a->correo)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); 
        printf("Correo inválido. Intente de nuevo: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); 
    }

    fflush(stdin);
    printf("Teléfono (10 dígitos): ");
    while (fgets(a->telefono, sizeof(a->telefono), stdin) && !esTelefonoValido(a->telefono)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); 
        printf("Teléfono inválido. Debe tener 10 dígitos. Intente de nuevo: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); 
    }


    fprintf(f, "%d, %s, %s, %d, %02d/%02d/%d, ", a->matricula, a->nombre, a->carrera, a->semestre,
            a->nacimiento.dia, a->nacimiento.mes, a->nacimiento.año);

    for (int i = 0; i < 10; i++) {
        fprintf(f, "%.2f ", a->promedios[i]);
    }

    fprintf(f, ", %s, %s\n", a->correo, a->telefono);

    fclose(f);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    printf("\nAlumno guardado exitosamente.\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

int main() {
    FILE *f;
    struct Alumno alumno;

    ingresarAlumnos(&alumno, f);

    return 0;
}

}
