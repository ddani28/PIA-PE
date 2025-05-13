#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_PROFESORES 50
#define MAX_MATERIAS 100

struct Fecha {
    int dia, mes, anio;
};

struct Direccion {
    char calle[50];
    int numero;
    char colonia[50];
    char ciudad[50];
    char estado[50];
};

struct Profesor {
    int numEmpleado;
    int totalMaterias;
    int coordinacion;
    char nombre[100];
    char correo[100];
    char telefono[11];
    char clavesMaterias[10][20];
    struct Fecha nacimiento;
    struct Direccion direccion;
};
int validarNumeroEmpleado(int num) {
    return num > 0;
}

int validarNombre(const char* nombre) {
    return strlen(nombre) > 0;
}

int validarCoordinacion(int c) {
    return c >= 1 && c <= 6;
}

int validarFechaP(struct Fecha f) {
    time_t t = time(NULL);
    struct tm *actual = localtime(&t);

    if (f.anio < 1900 || f.anio > actual->tm_year + 1900) return 0;
    if (f.mes < 1 || f.mes > 12) return 0;
    if (f.dia < 1 || f.dia > 31) return 0;

    if (f.anio == actual->tm_year + 1900) {
        if (f.mes > actual->tm_mon + 1) return 0;
        if (f.mes == actual->tm_mon + 1 && f.dia > actual->tm_mday) return 0;
    }

    return 1;
}

int validarCorreo(const char* correo) {
    return (strchr(correo, '@') != NULL) && (strchr(correo, '.') != NULL);
}

int validarTelefono(const char* telefono) {
    if (strlen(telefono) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(telefono[i])) return 0;
    }
    return 1;
}

int existeMateria(const char clavesMaterias[][20], int totalMaterias, const char* clave) {
    for (int i = 0; i < totalMaterias; i++) {
        if (strcmp(clavesMaterias[i], clave) == 0) return 1;
    }
    return 0;
}
void capturarProfesor(struct Profesor *p, const char clavesMaterias[][20], int totalMaterias) {
    do {
        printf("Número de empleado: ");
        scanf("%d", &p->numEmpleado);
        if (!validarNumeroEmpleado(p->numEmpleado)) printf("ERROR: debe ser mayor a cero.\n");
    } while (!validarNumeroEmpleado(p->numEmpleado));

    do {
        printf("Nombre: ");
        fflush(stdin);
        gets(p->nombre);
        if (!validarNombre(p->nombre)) printf("ERROR: nombre inválido.\n");
    } while (!validarNombre(p->nombre));

    do {
        printf("Coordinación (1-6): ");
        scanf("%d", &p->coordinacion);
        if (!validarCoordinacion(p->coordinacion)) printf("ERROR: fuera de rango.\n");
    } while (!validarCoordinacion(p->coordinacion));

    do {
        printf("Fecha de nacimiento (DD MM AAAA): ");
        scanf("%d %d %d", &p->nacimiento.dia, &p->nacimiento.mes, &p->nacimiento.anio);
        if (!validarFechaP(p->nacimiento)) printf("ERROR: fecha inválida o futura.\n");
    } while (!validarFechaP(p->nacimiento));

    do {
        printf("Correo: ");
        fflush(stdin);
        gets(p->correo);
        if (!validarCorreo(p->correo)) printf("ERROR: correo inválido.\n");
    } while (!validarCorreo(p->correo));

    do {
        printf("Teléfono (10 dígitos): ");
        fflush(stdin);
        gets(p->telefono);
        if (!validarTelefono(p->telefono)) printf("ERROR: teléfono inválido.\n");
    } while (!validarTelefono(p->telefono));

    printf("¿Cuántas materias imparte? (máx 10): ");
    scanf("%d", &p->totalMaterias);
    while (p->totalMaterias < 0 || p->totalMaterias > 10) {
        printf("ERROR: cantidad inválida.\n");
        scanf("%d", &p->totalMaterias);
    }

    for (int i = 0; i < p->totalMaterias; i++) {
        char clave[20];
        do {
            printf("Clave de materia #%d: ", i + 1);
            fflush(stdin);
            gets(clave);
            if (!existeMateria(clavesMaterias, totalMaterias, clave))
                printf("ERROR: clave no existe en materias.\n");
        } while (!existeMateria(clavesMaterias, totalMaterias, clave));
        strcpy(p->clavesMaterias[i], clave);
    }
    printf("Dirección:\n");
    printf("  Calle: "); fflush(stdin); gets(p->direccion.calle);
    printf("  Número: "); scanf("%d", &p->direccion.numero);
    printf("  Colonia: "); fflush(stdin); gets(p->direccion.colonia);
    printf("  Ciudad: "); fflush(stdin); gets(p->direccion.ciudad);
    printf("  Estado: "); fflush(stdin); gets(p->direccion.estado);
}

void guardarProfesores(struct Profesor profesores[], int total) {
    FILE *f = fopen("profesores.dat", "a");
    if (f) {
        fwrite(profesores, sizeof(struct Profesor), total, f);
        fclose(f);
    } else {
        printf("ERROR al guardar archivo.\n");
    }
}

int cargarProfesores(struct Profesor profesores[]) {
    FILE *f = fopen("profesores.dat", "rb");
    int total = 0;
    if (f) {
        while (fread(&profesores[total], sizeof(struct Profesor), 1, f) && total < MAX_PROFESORES) {
            total++;
        }
        fclose(f);
    }
    return total;
}

