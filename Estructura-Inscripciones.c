#include <stdio.h>
#include <string.h>
#include <time.h>

struct Inscripcion 
{
    int folio, grupo, matricula;
    char fecha[20];
};

main()
{
    struct Inscripcion inscripciones[50];
    int totalInscripciones = 0;
    int totalGrupos = 3;
    int totalAlumnos = 5;

    int cantidad;
    printf("¿Cuántas inscripciones desea registrar? ");
    scanf("%d", &cantidad);

    for (int i = 0; i < cantidad && totalInscripciones < 50; i++)
    {
        printf("\n--- Registro %d ---\n", i + 1);
        registrarInscripcion(&inscripciones[totalInscripciones], totalInscripciones + 1, grupo, totalGrupos, alumnos, totalAlumnos);
        totalInscripciones++;
    }

    printf("\nInscripciones registradas:\n");
    for (int i = 0; i < totalInscripciones; i++)
    {
        printf("Folio: %d | Grupo: %d | Matrícula: %d | Fecha: %s\n",
               inscripciones[i].folio,
               inscripciones[i].grupo,
               inscripciones[i].matricula,
               inscripciones[i].fecha);
    }
}


int existeGrupo(struct Grupo* grupos, int total, int grupoBuscado) {
    for (int i = 0; i < total; i++) {
        if (grupos[i].numero == grupoBuscado) return 1;
    }
    return 0;
}

int existeAlumno(struct Alumno* alumnos, int total, int matriculaBuscada) {
    for (int i = 0; i < total; i++) {
        if (alumnos[i].matricula == matriculaBuscada) return 1;
    }
    return 0;
}

void obtenerFechaActual(char* buffer) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(buffer, 20, "%Y-%m-%d", tm_info);
}

void registrarInscripcion(struct Inscripcion* inscripcion, int folio, struct Grupo* grupos, int totalGrupos, struct Alumno* alumnos, int totalAlumnos) {
    int grupoValido = 0;
    int matriculaValida = 0;

    inscripcion->folio = folio;

    while (!grupoValido) {
        printf("Ingrese número de grupo: ");
        scanf("%d", &inscripcion->grupo);
        if (existeGrupo(grupos, totalGrupos, inscripcion->grupo)) {
            grupoValido = 1;
        } else {
            printf("Grupo no encontrado. Intente de nuevo.\n");
        }
    }

    while (!matriculaValida) {
        printf("Ingrese matrícula del alumno: ");
        scanf("%d", &inscripcion->matricula);
        if (existeAlumno(alumnos, totalAlumnos, inscripcion->matricula)) {
            matriculaValida = 1;
        } else {
            printf("Matrícula no encontrada. Intente de nuevo.\n");
        }
    }

    obtenerFechaActual(inscripcion->fecha);
}
