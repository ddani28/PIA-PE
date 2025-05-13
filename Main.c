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

void Reportes();
void listarAlumnosPorCarrera();
void listarClasesPorProfesor();

void mostrarMinuta();
void generarArchivoAlumnos();
void generarArchivoProfesores();
void mostrarArchivoTexto();

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
                actualizarPromedio();
                break;

            case 7:
                Reportes();
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
    char continuar;

    if (!f) {
        textoRojo();
        printf("No se pudo acceder al archivo de materias\n");
        textoNormal();
        return;
    }

    do
    {
	do
	{
        	printf("\nIngresa la clave de la materia: ");
        	scanf("%d", &mt->clave);
        	if (mt->clave <= 0) {
            	textoRojo(); printf("Ingrese una clave mayor a 0\n"); textoNormal();
        	}
    	} while (mt->clave <= 0);

    	do
	{
        	printf("Ingresa el semestre de la materia: ");
        	scanf("%d", &mt->semestre);
        	if (mt->semestre <= 0 || mt->semestre > 10) {
            	textoRojo(); printf("Ingrese un semestre entre 1 y 10\n"); textoNormal();
        	}
    	} while (mt->semestre <= 0 || mt->semestre > 10);

    	do
    	{
        	printf("Ingresa el nombre de la materia: ");
        	scanf(" %19[^\n]", mt->nombre);
        	if (strlen(mt->nombre) == 0) {
            	textoRojo(); printf("El nombre no puede estar vacío.\n"); textoNormal();
        	}
    	} while (strlen(mt->nombre) == 0);

    	fprintf(f, "%d,%d,%s\n", mt->clave, mt->semestre, mt->nombre);
    	printf("Materia guardada correctamente. Desea agregar otra materia? (s/n): \n");
	scanf(" %c", &continuar;
    } while ( continuar == 's' || continuar == 'S' );
	
    

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

void actualizarPromedio()
{
    FILE *f = fopen("alumnos.txt", "r+");
    if (!f)
	{
        textoRojo();
        printf("No se pudo abrir el archivo de alumnos.\n");
        textoNormal();
        return;
    	}

    char nombreBuscado[100], continuar;
    float nuevoPromedio;
    int encontrado = 0;
    struct Alumno al;
    long posicion;

    do
    {
	    printf("\nIngrese el nombre completo del alumno: ");
	    scanf(" %99[^\n]", nombreBuscado);
	
	    do
		{
	        printf("Ingrese el nuevo promedio (0 - 10): ");
	        scanf("%f", &nuevoPromedio);
	        if (nuevoPromedio < 0 || nuevoPromedio > 10)
		{
	            textoRojo();
	            printf("Promedio inválido. Debe estar entre 0 y 10.\n");
	            textoNormal();
	        }
	    } while (nuevoPromedio < 0 || nuevoPromedio > 10);
	
	    while (fscanf(f, "%d,%d,%f,%99[^,],%*[^,\n]\n", &al.matricula, &al.semestre, &al.promedios[0], al.nombre) == 4)
	    {
	        if (strcmp(al.nombre, nombreBuscado) == 0)
		{
	            encontrado = 1;
	            al.promedios[0] = nuevoPromedio;
	
	            posicion = ftell(f) - strlen(al.nombre) - 20;
	            fseek(f, posicion, SEEK_SET);
	
	            fprintf(f, "%d,%d,%.2f,%s\n", al.matricula, al.semestre, al.promedios[0], al.nombre);
	
	            printf("\033[1;32mPromedio actualizado exitosamente.\033[0m\n");
	            printf("Grupo: %d | Alumno: %s | Promedio actual: %.2f\n", al.semestre, al.nombre, al.promedios[0]);
	            break;
	        }
	    }
	
	    if (!encontrado)
	    {
	        textoRojo();
	        printf("Alumno no encontrado.\n");
	        textoNormal();
	    }

	    printf("Profesor guardado correctamente. Desea agregar a otro profesor? (s/n): \n");
            scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');
	    
    fclose(f);
}

void Reportes()
{
    char opcion;
    do
    {
        printf("\n--- REPORTES ---\n");
        printf("a) Listado de alumnos por carrera\n");
        printf("b) Lista de clases\n");
        printf("c) Listado de grupos por fecha\n");
        printf("d) Minuta\n");
        printf("e) Generar archivo de alumnos\n");
        printf("f) Generar archivo de profesores\n");
        printf("g) Mostrar archivo de texto\n");
        printf("h) Salir\n");
        printf("Opción: ");
        scanf(" %c", &opcion);

        if (opcion < 'a' || opcion > 'h')
            textoRojo(); printf("Opción no válida. Debe ser entre 'a' y 'h'.\n"); textoNormal();
            
        switch (opcion)
		{
            case 'a':
                listarAlumnosPorCarrera();
                break;
            case 'b':
                listarClasesPorProfesor();
                break;
            case 'c':
                listarGruposPorFecha();
                break;
            case 'd':
                mostrarMinuta();
                break;
            case 'e':
                generarArchivoAlumnos();
                break;
            case 'f':
                generarArchivoProfesores();
                break;
            case 'g':
                mostrarArchivoTexto();
                break;
            case 'h':
                printf("Regresando al menú principal...\n");
                break;
        }
    } while (opcion != 'h');
}


void listarAlumnosPorCarrera()
{
	FILE *f = fopen("alumnos.dat", "r");
    if (!f)
    {
        textoRojo();
        printf("No se pudo abrir el archivo de alumnos.\n");
        textoNormal();
    }

    struct Alumno a;
    char carreraBuscada[50];
    int encontrados = 0;

    printf("Ingrese la carrera a buscar: ");
    scanf(" %[^\n]", carreraBuscada);

    printf("\n%-10s %-20s %-10s %-10s %-15s %-30s\n", "Matricula", "Nombre", "Semestre", "Promedio", "Telefono", "Correo");
    printf("-----------------------------------------------------------------------------------------------\n");

    while (fread(&a, sizeof(struct Alumno), 1, f) == 1)
    {
        if (strcmp(a.carrera, carreraBuscada) == 0)
        {
            printf("%-10d %-20s %-10d %-10.2f %-15d %-30s\n", a.matricula, a.nombre, a.semestre, a.promedio, a.telefono, a.correo);
            encontrados++;
        }
    }

    if (encontrados == 0)
    {
        textoRojo();
        printf("No se encontraron alumnos para la carrera: %s\n", carreraBuscada);
        textoNormal();
    }

    fclose(f);
}

void listarClasesPorProfesor()
{
    int claveProfesor;
    int encontrado = 0;

    printf("Ingrese la clave (número de empleado) del profesor: ");
    scanf("%d", &claveProfesor);

    FILE *fp = fopen("profesores.dat", "rb");
    if (!fp)
	{
        textoRojo();
        printf("No se pudo abrir el archivo de profesores.\n");
        textoNormal();
    }

    struct Profesor prof;
    while (fread(&prof, sizeof(struct Profesor), 1, fp) == 1)
	{
        if (prof.numEmpleado == claveProfesor)
            encontrado = 1;
    }
    fclose(fp);

    if (!encontrado)
	{
        textoRojo();
        printf("No se encontró un profesor con la clave %d.\n", claveProfesor);
        textoNormal();
    }

    FILE *fg = fopen("grupos.txt", "r");
    if (!fg)
	{
        textoRojo();
        printf("No se pudo abrir el archivo de grupos.\n");
        textoNormal();
    }

    struct Grupos grupo;
    encontrado = 0;

    printf("\n%-10s %-10s %-20s %-10s\n", "Grupo", "Semestre", "Materia", "Periodo");
    printf("-------------------------------------------------------------\n");

    while (fscanf(fg, "%d %d %d %19s %d %d %s %d %d %d\n", &grupo.claveGrupo, &grupo.semestre, &grupo.numEmpleado, grupo.periodoGrupo, &grupo.claveMateria.clave, &grupo.claveMateria.semestre, grupo.claveMateria.nombre, &grupo.fh.dia, &grupo.fh.mes, &grupo.fh.anio) == 10)
    {
        if (grupo.numEmpleado == claveProfesor)
		{
            printf("%-10d %-10d %-20s %-10s\n", grupo.claveGrupo, grupo.semestre, grupo.claveMateria.nombre, grupo.periodoGrupo);
            encontrado = 1;
        }
    }

    if (!encontrado)
	{
        textoRojo();
        printf("Este profesor no tiene clases asignadas.\n");
        textoNormal();
    }
    fclose(fg);
}

void mostrarMinuta()
{
    int claveGrupo, claveMateria;
    struct Inscripcion ins;
    struct Alumno alum;
    struct Grupos grupo;
    int encontrado = 0;

    printf("Ingrese la clave del grupo: ");
    scanf("%d", &claveGrupo);

    printf("Ingrese la clave de la materia: ");
    scanf("%d", &claveMateria);

    FILE *fIns = fopen("inscripciones.dat", "r");
    if (!fIns)
        textoRojo(); printf("No se pudo abrir el archivo de inscripciones.\n"); textoNormal();

    FILE *fAlum = fopen("alumnos.dat", "r");
    if (!fAlum)
	{
        textoRojo(); printf("No se pudo abrir el archivo de alumnos.\n"); textoNormal();
        fclose(fIns);
    }

    printf("\n--- MINUTA DEL GRUPO %d, MATERIA %d ---\n", claveGrupo, claveMateria);
    printf("%-10s %-30s %-10s\n", "Matricula", "Nombre", "Promedio");
    printf("----------------------------------------------------------\n");

    while (fread(&ins, sizeof(struct Inscripcion), 1, fIns) == 1)
	{
        if (ins.grupoIns.claveGrupo == claveGrupo && ins.grupoIns.claveMateria.clave == claveMateria)
		{
            rewind(fAlum);
            while (fread(&alum, sizeof(struct Alumno), 1, fAlum) == 1)
			{
                if (alum.matricula == ins.matricula)
				{
                    printf("%-10d %-30s %-10.2f\n", alum.matricula, alum.nombre, alum.promedio);
                    encontrado = 1;
                }
            }
        }
    }

    if (!encontrado)
	{
        textoRojo();
        printf("No se encontraron alumnos inscritos en ese grupo y materia.\n");
        textoNormal();
    }
    fclose(fIns);
    fclose(fAlum);
}

void generarArchivoAlumnos()
{
    FILE *fBin = fopen("alumnos.dat", "r");
    FILE *fTxt = fopen("alumnos.txt", "w");

    if (!fBin || !fTxt)
	{
        textoRojo();
        printf("Error al abrir archivos para lectura/escritura.\n");
        textoNormal();
        if (fBin) fclose(fBin);
        if (fTxt) fclose(fTxt);
    }

    struct Alumno a;

    fprintf(fTxt, "========== LISTADO DE ALUMNOS ==========\n\n");

    while (fread(&a, sizeof(struct Alumno), 1, fBin) == 1)
	{
        fprintf(fTxt, "Matricula: %d\n", a.matricula);
        fprintf(fTxt, "Nombre: %s\n", a.nombre);
        fprintf(fTxt, "Carrera: %s\n", a.carrera);
        fprintf(fTxt, "Semestre: %d\n", a.semestre);
        fprintf(fTxt, "Promedio: %.2f\n", a.promedio);
        fprintf(fTxt, "Telefono: %d\n", a.telefono);
        fprintf(fTxt, "Correo: %s\n", a.correo);
        fprintf(fTxt, "Fecha de Nacimiento: %02d/%02d/%04d\n", a.nacimiento.dia, a.nacimiento.mes, a.nacimiento.anio);
        fprintf(fTxt, "Direccion: %s %d, Col. %s, %s, %s\n", a.direccion.calle, a.direccion.numero, a.direccion.colonia, a.direccion.municipio, a.direccion.estado);
        fprintf(fTxt, "----------------------------------------\n\n");
    }

    fclose(fBin);
    fclose(fTxt);

    printf("\033[1;32mArchivo de alumnos generado exitosamente como 'alumnos.txt'.\033[0m\n");
}

void generarArchivoProfesores()
{
    FILE *fBin = fopen("profesores.dat", "r");
    FILE *fTxt = fopen("profesores.txt", "w");

    if (!fBin || !fTxt)
	{
        textoRojo();
        printf("Error al abrir archivos para lectura/escritura.\n");
        textoNormal();
        if (fBin) fclose(fBin);
        if (fTxt) fclose(fTxt);
    }

    struct Profesor p;

    fprintf(fTxt, "========== LISTADO DE PROFESORES ==========\n\n");

    while (fread(&p, sizeof(struct Profesor), 1, fBin) == 1)
	{
        fprintf(fTxt, "Num. Empleado: %d\n", p.numEmpleado);
        fprintf(fTxt, "Nombre: %s\n", p.nombre);
        fprintf(fTxt, "Coordinación: %d\n", p.coordinacion);
        fprintf(fTxt, "Telefono: %s\n", p.telefono);
        fprintf(fTxt, "Correo: %s\n", p.correo);
        fprintf(fTxt, "Fecha de Nacimiento: %02d/%02d/%04d\n", p.fechaNacimiento.dia, p.fechaNacimiento.mes, p.fechaNacimiento.anio);
        fprintf(fTxt, "Direccion: %s %d, Col. %s, %s, %s\n", p.direccion.calle, p.direccion.numero, p.direccion.colonia, p.direccion.municipio, p.direccion.estado);
        fprintf(fTxt, "-------------------------------------------\n\n");
    }

    fclose(fBin);
    fclose(fTxt);

    printf("\033[1;32mArchivo de profesores generado exitosamente como 'profesores.txt'.\033[0m\n");
}

void mostrarArchivoTexto()
{
    char opcion;
    char linea[256];
    FILE *f;

    printf("¿Qué archivo desea ver?\n");
    printf("a) Alumnos\n");
    printf("b) Profesores\n");
    printf("Seleccione una opción (a/b): ");
    scanf(" %c", &opcion);

    if (opcion == 'a')
	{
        f = fopen("alumnos.txt", "r");
        if (!f)
            textoRojo(); printf("No se pudo abrir el archivo de alumnos.\n"); textoNormal();
        printf("\n--- CONTENIDO DE ALUMNOS.TXT ---\n\n");
    }
    else if (opcion == 'b')
	{
        f = fopen("profesores.txt", "r");
        if (!f)
	{
            textoRojo(); printf("No se pudo abrir el archivo de profesores.\n"); textoNormal();
        printf("\n--- CONTENIDO DE PROFESORES.TXT ---\n\n");
	}
    }
    else
        textoRojo(); printf("Opción no válida.\n"); textoNormal();

    while (fgets(linea, sizeof(linea), f))
        printf("%s", linea);

    fclose(f);
}
