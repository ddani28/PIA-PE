#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct Materias 
{
	int clave, semestre;
	char nombre[20];	
};

struct Fecha
{
    int dia, mes, anio;
};

struct Grupos
{
	int claveGrupo, semestre, numEmpleado; 
	char periodoGrupo[20];
	struct Materias claveMateria;
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


main()
{
	int opcion;
	
	struct Alumno alumnos[20];
    int totalAlumnos = 0;
    
    struct Profesor profesores[10];
    int totalProfesores;
               
    struct Materias mt[10];
    int totalMaterias;
    
    struct Grupos gp[50];
    
	
	do
	{
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
        
        
        switch (opcion)
		{
            case 1:
                //Funcion alumnos
                if (totalAlumnos < 20)
                    agregarAlumno(&alumnos[totalAlumnos++]);
                else
                    printf("Limite de alumnos alcanzado.\n");
                break;
           
            case 2:
               //Funcion profesores
               if (totalProfesores < 10)
                    agregarProfesor(&profesores[totalProfesores++]);
                else
                    printf("Limite de profesores alcanzado.\n");
                break;
                
            case 3:
            	//Funcion materias
				if(totalMaterias < 10)
            		agregarMaterias(&mt[totalMaterias++]);
            	else
            		printf("Limite de materias alcanzado");
                break;
                
            case 4:
               //Funcion grupo
                break;
                
            case 5:
               //Funcion Inscripciones
                break;
        	case 6:
               //funcion promedio
                break;
            case 7:
               //Funcion reportes
                break;
            
			case 8:
               //Salir
                break;
            
            default:
                printf("Por favor ingrese una opcion valida.\n");
        }
    } while (opcion != 0);
}

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

int esTextoValido(char *texto) {
    int i;
	for (i = 0; texto[i]; i++)
    {
        if (!isalpha(texto[i]) && texto[i] != ' ')
            return 0;
    }
    return 1;
}

int validarCarrera(char *carrera) {
    int i;
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

int validarMateria(char *clave) {
    int i;
	for (i = 0; i < 10; i++)
    {
        if (strcmp(clave, materiasDisponibles[i]) == 0)
            return 1;
    }
    return 0;
}


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


void agregarAlumno(struct Alumno *a) {
    int i;
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

void agregarProfesor(struct Profesor *p) {
    int i;
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

void ingresarGrupos(struct Grupos *gp)
{
	int i;
	do 
	{
		printf("\nIngresa la clave del grupo: ");
		scanf("%d", &gp->claveGrupo);
		if (gp->claveGrupo < 0)
			printf("Ingrese una clave mayor a 0");
	}while(gp->claveGrupo < 0);
				
	do 
	{	
		printf("\nIngresa el semestre del grupo: ");
		scanf("%d", &gp->semestre);
		if (gp->semestre < 0 || gp->semestre > 10)
			printf("Ingrese un semestre mayor a 0 y menor a 10");
		
	}while(gp->semestre < 0 || gp->semestre > 10);
				
	do 
	{
		printf("\nIngresa la clave de la materia: ");
		fflush(stdin);
		scanf("%s", &gp->claveMateria);
				
		if (strlen(gp->claveMateria) == 0) 
        	printf("La clave no puede estar vacío. Intente de nuevo.\n");
		
	}while (strlen(gp->claveMateria) == 0);
			
	do 
	{
		printf("\nIngresa el numero de empleado: ");
		fflush(stdin);
		scanf("%s", &gp->numEmpleado);
		if (strlen(gp->numEmpleado) == 0) 
        	printf("El numero de empleado no puede estar vacio. Intente de nuevo.\n");
		
	}while (strlen(gp->numEmpleado) == 0);
	
	time_t t = time(NULL);
	struct tm fechaActual = *localtime(&t);

	do
	{
		printf("Ingrese su fecha de grupo:\n");
		printf("Dia: ");
		scanf("%d", &gp->fh->dia);
		printf("Mes: ");
		scanf("%d", &gp->fh->mes);
		printf("Anio: ");
		scanf("%d", &gp->fh->anio);
		
		if( gp->fh->dia > fechaActual.tm_mday || gp->fh->mes > fechaActual.tm_mon + 1 || gp->fh->anio > fechaActual.tm_year + 1900)
			printf("La fecha ingresada es mayor que la fecha actual. Intente nuevamente.\n");
		
	}while (gp->fh->dia < fechaActual.tm_mday && gp->fh->mes < fechaActual.tm_mon + 1 && gp->fh->anio < fechaActual.tm_year + 1900);
	
	/*Falta periodo asi como validar claveMateria y numEmpleado con sus estructuras
	respectivas*/
}

