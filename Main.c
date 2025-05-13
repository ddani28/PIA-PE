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

void textoRojo();
void textoNormal();
void ingresarMaterias(struct Materias *mt, FILE *f);
void mostrarMaterias(FILE *f);
int numEmpleadoYaExiste(const char *numBuscado);
void ingresarGrupos(struct Grupos *gp, FILE *f);
void mostrarGrupos();
int esFechaValida(int dia, int mes, int anio); 
char *buscarNombreMateria(int claveMateria);
void ingresarMaterias(struct Materias *mt, FILE *f);
void mostrarMaterias(FILE *f);
void ingresarGrupos(struct Grupos *gp, FILE *f);
void mostrarGrupos();
void buscarGruposPorPeriodo();
char *buscarNombreMateria(int claveMat);
char *buscarNombreProfesor(const char *numEmpleado);
void ingresarAlumnos(struct Alumno *a, FILE *f);
void textoRojo();
void textoNormal();

main()
{
    int opcion;
    struct Materias mat;
    struct Grupos grupo;
    struct Alumno a;

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

        switch (opcion){
		
            case 1: 
			{
                FILE *f = fopen("alumnos.txt", "a");
                if (!f) {
                    textoRojo(); printf("No se pudo abrir el archivo de alumnos.\n"); textoNormal();
            	}else {
                    ingresarAlumnos(&a, f);
                    fclose(f);
                }
                break;
            }
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
			{
				//c
			    char periodoBuscado[20];
			    printf("\nIngrese el periodo a buscar (ej. 2025-1): ");
			    scanf(" %19[^\n]", periodoBuscado);
			    buscarGruposPorPeriodo(periodoBuscado);
			    break;
			}
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

int esBisiesto(int anio) {
    return (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
}

int esFechaValida(int dia, int mes, int anio) {
    int diasPorMes[] = {31, (esBisiesto(anio) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes < 1 || mes > 12) return 0;
    if (dia < 1 || dia > diasPorMes[mes - 1]) return 0;
    return 1;
}

char *buscarNombreMateria(int claveMat) {
    static char nombre[20];
    FILE *f = fopen("materias.txt", "r");
    if (!f) return "Materia no encontrada";

    int clave, semestre;
    char tempNombre[20];
    while (fscanf(f, "%d,%d,%19[^\n]\n", &clave, &semestre, tempNombre) == 3) {
        if (clave == claveMat) {
            fclose(f);
            strcpy(nombre, tempNombre);
            return nombre;
        }
    }
    fclose(f);
    return "Materia no encontrada";
}

char *buscarNombreProfesor(const char *numEmpleado) {
    static char nombre[100];
    FILE *f = fopen("profesores.txt", "r");
    if (!f) return "Profesor no encontrado";

    struct Profesor temp;
    char linea[300];
    while (fgets(linea, sizeof(linea), f)) {
        if (sscanf(linea, "%d,%[^,],%[^,],%[^,],%d/%d/%d,%[^,],%[^,],%[^,],%[^,],%d",
                   &temp.numEmpleado, temp.nombre, temp.correo, temp.telefono,
                   &temp.nacimiento.dia, &temp.nacimiento.mes, &temp.nacimiento.anio,
                   temp.direccion.calle, temp.direccion.colonia,
                   temp.direccion.municipio, temp.direccion.estado,
                   &temp.direccion.numero) >= 4) {

            char empleadoStr[10];
            sprintf(empleadoStr, "%d", temp.numEmpleado);
            if (strcmp(empleadoStr, numEmpleado) == 0) {
                fclose(f);
                strcpy(nombre, temp.nombre);  // Copiar aquí
                return nombre;
            }
        }
    }

    fclose(f);
    return "Profesor no encontrado";
}

void buscarGruposPorPeriodo() {
    char periodo[20];
    printf("\nIngrese el periodo a buscar (ej. 2025-1): ");
    scanf(" %19[^\n]", periodo);

    FILE *f = fopen("grupos.txt", "r");
    if (!f) {
        textoRojo(); printf("No se pudo abrir el archivo de grupos.\n"); textoNormal();
        return;
    }

    struct Grupos temp;
    int encontrados = 0;

    printf("\n%-10s %-10s %-20s %-20s\n", "Grupo", "Semestre", "Materia", "Profesor");
    printf("--------------------------------------------------------------------------\n");

    while (fscanf(f, "%d,%d,%d,%9[^,],%19[^,],%10[^\n]\n",
           &temp.claveGrupo, &temp.semestre, &temp.claveMateria,
           temp.numEmpleado, temp.periodoGrupo, temp.fecha) == 6) {

        if (strcmp(temp.periodoGrupo, periodo) == 0) {
            char *nombreMateria = buscarNombreMateria(temp.claveMateria);
            char *nombreProfesor = buscarNombreProfesor(temp.numEmpleado);

            printf("%-10d %-10d %-20s %-20s\n",
                   temp.claveGrupo, temp.semestre, nombreMateria, nombreProfesor);
            encontrados = 1;
        }
    }

    if (!encontrados) {
        textoRojo(); printf("No se encontraron grupos para el periodo ingresado.\n"); textoNormal();
    }

    fclose(f);
}

int esFechaValidaA(struct Fecha fecha) {
    time_t t = time(NULL);
    struct tm fecha_actual = *localtime(&t);
    if (fecha.anio < fecha_actual.tm_year + 1900) return 1;
    if (fecha.anio == fecha_actual.tm_year + 1900 && fecha.mes < fecha_actual.tm_mon + 1) return 1;
    if (fecha.anio == fecha_actual.tm_year + 1900 && fecha.mes == fecha_actual.tm_mon + 1 && fecha.dia < fecha_actual.tm_mday) return 1;
    return 0;  
}

int esCorreoValido(char *correo) {
    int i, atCount = 0, dotCount = 0;
    for (i = 0; correo[i] != '\0'; i++) {
        if (correo[i] == '@') atCount++;
        if (correo[i] == '.') dotCount++;
    }
    return (atCount == 1 && dotCount >= 1);  
}

int esTelefonoValido(char *telefono) {
	int i;
    if (strlen(telefono) != 10) return 0;  
    for (i = 0; i < 10; i++) {
        if (!isdigit(telefono[i])) return 0;  
    }
    return 1;
}

void ingresarAlumnos(struct Alumno *a, FILE *f) {
	int i;
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
    while (scanf("%d/%d/%d", &a->nacimiento.dia, &a->nacimiento.mes, &a->nacimiento.anio) != 3 || 
           a->nacimiento.dia < 1 || a->nacimiento.dia > 31 || 
           a->nacimiento.mes < 1 || a->nacimiento.mes > 12 || 
           a->nacimiento.anio < 1900 || !esFechaValidaA(a->nacimiento)) {
        fflush(stdin);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printf("Fecha inválida. Intente de nuevo: ");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    }

    fflush(stdin);
    printf("Promedio general de cada semestre (0-100) [Ingrese 10 promedios]: ");
    for (i = 0; i < 10; i++) {
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
            a->nacimiento.dia, a->nacimiento.mes, a->nacimiento.anio);

    for (i = 0; i < 10; i++) {
        fprintf(f, "%.2f ", a->promedios[i]);
    }

    fprintf(f, ", %s, %s\n", a->correo, a->telefono);

    fclose(f);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    printf("\nAlumno guardado exitosamente.\n");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}


