#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

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

struct Profesor
{
    int numEmpleado, totalMaterias, coordinacion; //Entre 1 y 6
    char nombre[100], correo[100], telefono[11], clavesMaterias[10][20];
    struct Fecha nacimiento;
    struct Direccion direccion;
};

// ---------- VARIABLES GLOBALES ----------
char carreras[][50] = {
    "Actuaria",
    "Ciencias Computacionales",
    "Fisica",
    "Multimedia y Animacion Digital",
    "Matematicas",
    "Seguridad"
};

char materiasDisponibles[][10] = {
    "MAT101", "FIS102", "COM103", "ACT104", "SEG105",
    "ANI106", "MAT201", "FIS202", "COM203", "ACT204"
};

int esTextoValido(char *texto);
int validarCarrera(char *carrera);
int validarFecha(struct Fecha f);
int validarCorreo(char *correo);
int validarTelefono(char *telefono);
int validarMateria(char *clave);

void capturarFecha(struct Fecha *f);
void capturarDireccion(struct Direccion *d);
void agregarAlumno(struct Alumno *a);
void agregarProfesor(struct Profesor *p);

main()
{
    struct Alumno alumnos[20];
    struct Profesor profesores[10];
    int totalAlumnos = 0, totalProfesores = 0, opcion;

    do
    {
        printf("\n----- MENU PRINCIPAL -----\n");
        printf("1. Agregar alumno\n");
        printf("2. Agregar profesor\n");
        printf("3. Ver total de alumnos/profesores\n");
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
            case 1:
                if (totalAlumnos < 20)
                    agregarAlumno(&alumnos[totalAlumnos++]);
                else
                    printf("Limite de alumnos alcanzado.\n");
                break;
            case 2:
                if (totalProfesores < 10)
                    agregarProfesor(&profesores[totalProfesores++]);
                else
                    printf("Limite de profesores alcanzado.\n");
                break;
            case 3:
                printf("Total de alumnos: %d\n", totalAlumnos);
                printf("Total de profesores: %d\n", totalProfesores);
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no valida.\n");
        }
    } while (opcion != 0);
}

// ---------- FUNCIONES DE VALIDACIÓN ----------
int i;
int esTextoValido(char *texto) {
    for (i = 0; texto[i]; i++)
    {
        if (!isalpha(texto[i]) && texto[i] != ' ')
            return 0;
    }
    return 1;
}

int i;
int validarCarrera(char *carrera) {
    for (i = 0; i < 6; i++)
    {
        if (strcmp(carrera, carreras[i]) == 0)
            return 1;
    }
    return 0;
}

int validarFecha(struct Fecha f) {
    time_t t = time(NULL);
    struct tm *ahora = localtime(&t);
    int dia = ahora->tm_mday;
    int mes = ahora->tm_mon + 1;
    int anio = ahora->tm_year + 1900;

    if (f.anio > anio) return 0;
    if (f.anio == anio && f.mes > mes) return 0;
    if (f.anio == anio && f.mes == mes && f.dia > dia) return 0;
    if (f.dia < 1 || f.dia > 31 || f.mes < 1 || f.mes > 12) return 0;
    return 1;
}

int validarCorreo(char *correo) {
    return (strstr(correo, "@") != NULL && (strstr(correo, ".com") || strstr(correo, ".mx")));
}

int validarTelefono(char *telefono) {
    return strlen(telefono) == 10 && strspn(telefono, "0123456789") == 10;
}

int i;
int validarMateria(char *clave) {
    for (i = 0; i < 10; i++)
    {
        if (strcmp(clave, materiasDisponibles[i]) == 0)
            return 1;
    }
    return 0;
}

// ---------- FUNCIONES DE CAPTURA ----------
void capturarFecha(struct Fecha *f) {
    do
    {
        printf("Fecha de nacimiento (DD MM AAAA): ");
        scanf("%d %d %d", &f->dia, &f->mes, &f->anio);
        if (!validarFecha(*f))
            printf("Fecha invalida.\n");
    } while (!validarFecha(*f));
}

void capturarDireccion(struct Direccion *d) {
    printf("Calle: ");
    getchar(); fgets(d->calle, 50, stdin); strtok(d->calle, "\n");
    printf("Numero: ");
    scanf("%d", &d->numero);
    printf("Colonia: ");
    getchar(); fgets(d->colonia, 50, stdin); strtok(d->colonia, "\n");
    printf("Municipio: ");
    fgets(d->municipio, 50, stdin); strtok(d->municipio, "\n");
    printf("Estado: ");
    fgets(d->estado, 50, stdin); strtok(d->estado, "\n");
}


int i;
void agregarAlumno(struct Alumno *a) {
    do
    {
        printf("Ingresar matricula: ");
        scanf("%d", &a->matricula);
    } while (a->matricula <= 0);

    do
    {
        printf("Ingrese su nombre: ");
        getchar(); fgets(a->nombre, 100, stdin); strtok(a->nombre, "\n");
    } while (!esTextoValido(a->nombre));

    do
    {
        printf("Ingrese su carrera: ");
        fgets(a->carrera, 50, stdin); strtok(a->carrera, "\n");
    } while (!validarCarrera(a->carrera));

    do
    {
        printf("Ingrese su semestre (1-10): ");
        scanf("%d", &a->semestre);
    } while (a->semestre < 1 || a->semestre > 10);

    capturarFecha(&a->nacimiento);

    do
    {
        printf("Ingresar su numero de telefono: ");
        scanf("%s", a->telefono);
    } while (!validarTelefono(a->telefono));

    for (i = 0; i < a->semestre; i++)
    {
        do
        {
            printf("Promedio semestre %d: ", i + 1);
            scanf("%f", &a->promedios[i]);
        } while (a->promedios[i] < 0 || a->promedios[i] > 100);
    }

    do
    {
        printf("Ingresar su correo electronico: ");
        scanf("%s", a->correo);
    } while (!validarCorreo(a->correo));

    capturarDireccion(&a->direccion);

    printf("Alumno agregado correctamente.\n\n");
}


int i;
void agregarProfesor(struct Profesor *p) {
    do
    {
        printf("Numero de empleado: ");
        scanf("%d", &p->numEmpleado);
    } while (p->numEmpleado <= 0);

    do
    {
        printf("Ingresar su nombre: ");
        getchar(); fgets(p->nombre, 100, stdin); strtok(p->nombre, "\n");
    } while (!esTextoValido(p->nombre));

    do
    {
        printf("Ingresar su coordinacion (1-6): ");
        scanf("%d", &p->coordinacion);
    } while (p->coordinacion < 1 || p->coordinacion > 6);

    capturarFecha(&p->nacimiento);

    do
    {
        printf("Ingresar su numero de telefono: ");
        scanf("%s", p->telefono);
    } while (!validarTelefono(p->telefono));

    do
    {
        printf("Ingresar su correo electronico: ");
        scanf("%s", p->correo);
    } while (!validarCorreo(p->correo));

    capturarDireccion(&p->direccion);

    do
    {
        printf("¿Cuantas materias imparte? (máximo 10): ");
        scanf("%d", &p->totalMaterias);
    } while (p->totalMaterias < 0 || p->totalMaterias > 10);

    for (i = 0; i < p->totalMaterias; i++)
    {
        do
        {
            printf("Ingrese la clave materia %d: ", i + 1);
            scanf("%s", p->clavesMaterias[i]);
        } while (!validarMateria(p->clavesMaterias[i]));
    }

    printf("Profesor agregado correctamente.\n\n");
}
