#include <stdio.h>
#include <string.h>
#include <time.h>

struct Materias {
    int clave, semestre;
    char nombre[20], descripcion[20];
};

struct Grupos {
    int claveGrupo, semestre, numEmpleado;
    char fecha[20], periodoGrupo[20];
    struct Materias claveMateria;
};

struct Inscripcion {
    int folio, grupo, matricula;
    char fecha[20];
    struct Grupos grupoIns;
};

struct Direccion {
    char calle[50], colonia[50], municipio[50], estado[50];
    int numero;
};

struct Fecha {
    int dia, mes, anio;
};

struct Alumno {
    int matricula, semestre;
    float promedios[10];
    char nombre[100], carrera[50], telefono[11], correo[100];
    struct Fecha nacimiento;
    struct Direccion direccion;
};

void obtenerFechaActual(char* buffer) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(buffer, 20, "%Y-%m-%d", tm_info);
}

int existeGrupo(struct Grupos* grupos, int total, int grupoBuscado) {
	int i;
    for (i = 0; i < total; i++) {
        if (grupos[i].claveGrupo == grupoBuscado) return 1;
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

void registrarInscripcion(struct Inscripcion* inscripcion, int folio, struct Grupos* grupos, int totalGrupos, struct Alumno* alumnos, int totalAlumnos) {
    int grupoValido = 0, matriculaValida = 0;

    inscripcion->folio = folio;

    while (!grupoValido) {
        printf("Ingrese numero de grupo: ");
        scanf("%d", &inscripcion->grupo);
        if (existeGrupo(grupos, totalGrupos, inscripcion->grupo)) {
            grupoValido = 1;
        } else {
            printf("Grupo no encontrado. Intente de nuevo.\n");
        }
    }

    while (!matriculaValida) {
        printf("Ingrese matricula del alumno: ");
        scanf("%d", &inscripcion->matricula);
        if (existeAlumno(alumnos, totalAlumnos, inscripcion->matricula)) {
            matriculaValida = 1;
        } else {
            printf("Matricula no encontrada. Intente de nuevo.\n");
        }
    }

    obtenerFechaActual(inscripcion->fecha);
}

void guardarInscripcionesConDatos(struct Inscripcion* inscripciones, int totalInscripciones,
                                   struct Alumno* alumnos, int totalAlumnos,
                                   struct Grupos* grupos, int totalGrupos) {
                                   	int i, j, k;
    FILE* f = fopen("inscripciones.txt", "w");
    if (!f) {
        printf("No se pudo abrir el archivo para escribir.\n");
        return;
    }

    for (i = 0; i < totalInscripciones; i++) {
        char nombreAlumno[100] = "Desconocido";
        char nombreMateria[20] = "Desconocido";
        int alumnoEncontrado = 0, grupoEncontrado = 0;

        for (j = 0; j < totalAlumnos; j++) {
            if (inscripciones[i].matricula == alumnos[j].matricula) {
                strcpy(nombreAlumno, alumnos[j].nombre);
                alumnoEncontrado = 1;
                break;
            }
        }

        for (k = 0; k < totalGrupos; k++) {
            if (inscripciones[i].grupo == grupos[k].claveGrupo) {
                strcpy(nombreMateria, grupos[k].claveMateria.nombre);
                grupoEncontrado = 1;
                break;
            }
        }

        if (alumnoEncontrado && grupoEncontrado) {
            fprintf(f, "%d,%d,%d,%s,%s,%s\n",
                    inscripciones[i].folio,
                    inscripciones[i].grupo,
                    inscripciones[i].matricula,
                    nombreAlumno,
                    nombreMateria,
                    inscripciones[i].fecha);
        } else {
            printf("? No se guardo inscripcion con folio %d. Datos incompletos.\n", inscripciones[i].folio);
        }
    }

    fclose(f);
    printf("? Inscripciones validas guardadas en inscripciones.txt con nombres.\n");
}

main() 
{
    struct Inscripcion inscripciones[50];
    struct Alumno alumnos[50];
    struct Grupos grupo[50];
    int totalInscripciones = 0, totalGrupos = 2, totalAlumnos = 3, i, cantidad;	

    printf("\n¿Cuantas inscripciones desea registrar? ");
    scanf("%d", &cantidad);

    for (i = 0; i < cantidad && totalInscripciones < 50; i++) {
        printf("\n--- Registro %d ---\n", i + 1);
        registrarInscripcion(&inscripciones[totalInscripciones], totalInscripciones + 1, grupo, totalGrupos, alumnos, totalAlumnos);
        totalInscripciones++;
    }
    guardarInscripcionesConDatos(inscripciones, totalInscripciones, alumnos, totalAlumnos, grupo, totalGrupos);
}



