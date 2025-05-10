#include <stdio.h>
#include <string.h>
#include <time.h>

struct Materias 
{
	int clave, semestre;
	char nombre[20], descripcion[20];	
};
struct Grupos
{
	int claveGrupo, semestre, numEmpleado; 
	char fecha[20], periodoGrupo[20];
	struct Materias claveMateria;
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

struct Fecha
{
    int dia, mes, anio;
};

struct Alumno
{
    int matricula, semestre;
    float promedios[10]; // Máximo 10 promedios
    char nombre[100], carrera[50], telefono[11], correo[100];
    struct Fecha nacimiento;
    struct Direccion direccion;
};

main()
{
    struct Inscripcion inscripciones[50];
    struct Alumno alumnos[50];
    struct Grupos grupo[50];
    int totalInscripciones = 0;
    int totalGrupos = 3;
    int totalAlumnos = 5;
    int i;

    int cantidad;
    printf("�Cuantas inscripciones desea registrar? ");
    scanf("%d", &cantidad);

    for (i = 0; i < cantidad && totalInscripciones < 50; i++)
    {
        printf("\n--- Registro %d ---\n", i + 1);
        registrarInscripcion(&inscripciones[totalInscripciones], totalInscripciones + 1, grupo, totalGrupos, alumnos, totalAlumnos);
        totalInscripciones++;
    }

    printf("\nInscripciones registradas:\n");
    for (i = 0; i < totalInscripciones; i++)
    {
        printf("Folio: %d | Grupo: %d | Matrícula: %d | Fecha: %s\n",
               inscripciones[i].folio,
               inscripciones[i].grupo,
               inscripciones[i].matricula,
               inscripciones[i].fecha);
    }
}


int existeGrupo(struct Grupos* gp[], int total, int grupoBuscado) {
	int i;
    for (i = 0; i < total; i++) {
        if (gp[i].claveGrupo == grupoBuscado)
			return 1;
    }
    return 0;
}

int existeAlumno(struct Alumno* alumnos, int total, int matriculaBuscada) {
    int i;
	for (i = 0; i < total; i++) {
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
