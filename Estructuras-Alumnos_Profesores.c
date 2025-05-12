#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Fecha
{
    int dia, mes, anio;
};

struct Direccion
{
    char calle[50], colonia[50], municipio[50], estado[50];
    int numero;
};

struct Alumno
{
    int matricula, semestre, telefono;
    char nombre[100], carrera[50], correo[100];
    float promedio;
    struct Fecha fechaNacimiento;
    struct Direccion direccion;
};

struct Profesor
{
	int numEmpleado, coordinacion, telefono;
    char nombre[50], correo[30];
    struct Fecha fechaNacimiento;
    struct Direccion direccion;
};

void agregarAlumno();
void agregarProfesor();
int correoValido(const char *correo);
int telefonoValido(int telefono);
int fechaValida(int d, int m, int a);

main()
{
    int opcion;
    
    do
	{
        printf("\n--- Menú ---\n");
        printf("1. Alumno\n");
        printf("2. Profesor\n");
        printf("3. Materias\n");
        printf("4. Grupo\n");
        printf("5. Inscripcion\n");
        printf("6. Actualizar promedio\n");
        printf("7. Reportes\n");
        printf("8. Salir\n");
        scanf("%d", &opcion);

        switch (opcion)
		{
            case 1:
				agregarAlumno();
				break;
				
            case 2:
				agregarProfesor();
				break;
				
            case 3:
				//agregarMateria();
				break;
				
			case 4:
				//Grupo();
				break;
			
			case 5:
				//Inscripcion();
				break;
			
			case 6:
				//Actualizar promedio();
				break;
			
			case 7:
				//Reportes();
				break;
			
			case 8:
				printf("Saliendo...");
				break;
			
			default:
				printf("Opcion invalida.");
				break;
        }
    } while (opcion != 8);
}


void agregarAlumno()
{
    struct Alumno a;
    int i;
    char continuar;
    
    FILE *f = fopen("alumnos.dat", "a");
    if (!f)
        printf("No se pudo abrir el archivo.\n");
    
    do
	{
	    do
		{
	        printf("Ingrese su matricula: ");
	        scanf("%d", &a.matricula);
	        
	        if(a.matricula <= 0)
	        	printf("Matricula invalida.");
	    } while(a.matricula <= 0);
	
	    do
		{
	        printf("Ingrese su nombre: ");
	        scanf(" %[^\n]", a.nombre);
	        
	        if(strlen(a.nombre) == 0)
	        	printf("Nombre invalido.");
	    } while (strlen(a.nombre) == 0);
	
	    printf("Ingrese su carrera: ");
	    scanf(" %[^\n]", a.carrera);
	    
	    do
		{
	    	printf("Ingrese su semestre: ");
	    	scanf("%d", &a.semestre);
	    	
	    	if(a.semestre < 1 || a.semestre > 10)
	    		printf("El semestre ingresado no existe.");
		} while(a.semestre < 1 || a.semestre > 10);
		
		
		for( i=0; i<a.semestre; i++)
		{
			do
			{	
				printf("Ingresar el promedio del semestre %d: ", i+1);
				scanf("%f", &a.promedio);
			
				if(a.promedio < 0 || a.promedio > 100)
					printf("Promedio invalido.");
			}while(a.promedio < 0 || a.promedio > 100);
		}
			
	    do
		{
	        printf("Infrese su fecha de nacimiento: ");
	        scanf("%d %d %d", &a.fechaNacimiento.dia, &a.fechaNacimiento.mes, &a.fechaNacimiento.anio);
	    } while (!fechaValida(a.fechaNacimiento.dia, a.fechaNacimiento.mes, a.fechaNacimiento.anio));
	
	    do
		{
	        printf("Ingrese su telefono: ");
	        scanf("%d", &a.telefono);
	    } while (!telefonoValido(a.telefono));
	
	    do
		{
	        printf("Ingrese su correo: ");
	        scanf(" %[^\n]", a.correo);
	    } while (!correoValido(a.correo));
	
	    printf("---\nIngresar dirección---\n");
	    printf("Calle: ");
	    scanf("%[^\n]", a.direccion.calle);
	    printf("Numero: ");
	    scanf("%d", &a.direccion.numero);
	    printf("Colonia: ");
	    scanf("%[^\n]", a.direccion.colonia);
	    printf("Municipio: ");
	    scanf("%[^\n]", a.direccion.municipio);
	    printf("Estado: ");
	    scanf(" %[^\n]", a.direccion.estado);
	
	    fwrite(&a, sizeof(a), 1, f);
	
	    printf("Alumno guardado correctamente. Desea agregar a otro alumno? (s/n): \n");
	    scanf(" %c", &continuar);
	}while(continuar == 's' || continuar == 'S');
	
	fclose(f);
}

void agregarProfesor()
{
	struct Profesor b;
	int i;
	char continuar;
	
	FILE *f = fopen("profesores.dat", "a");
    if (!f)
        printf("No se pudo abrir el archivo.\n");
    
    do
	{
    	do
		{
	    	printf("Ingrese su numero de empleado: ");
	    	scanf("%d", &b.numEmpleado);
	    	
	    	if(b.numEmpleado < 0)
	    		printf("El numero ingresado no existe.");
		}while(b.numEmpleado < 0);
		
		do
		{
			printf("Ingrese su nombre: ");
	        scanf(" %[^\n]", b.nombre);
	        
	        if(strlen(b.nombre) == 0)
	        	printf("Nombre invalido.");
	    }while(strlen(b.nombre) == 0);
	    
	    do
		{
	    	printf("Ingrese su coordinacion: ");
	    	scanf("%d", &b.coordinacion);
	    	
	    	if(b.coordinacion < 1 || b.coordinacion > 6)
	    		printf("La coordinacion ingresada no existe.");
		}while(b.coordinacion < 1 || b.coordinacion > 6);
		
		do
		{
	        printf("Infrese su fecha de nacimiento: ");
	        scanf("%d %d %d", &b.fechaNacimiento.dia, &b.fechaNacimiento.mes, &b.fechaNacimiento.anio);
	    } while (!fechaValida(b.fechaNacimiento.dia, b.fechaNacimiento.mes, b.fechaNacimiento.anio));
	
	    do
		{
	        printf("Ingrese su telefono: ");
	        scanf("%d", &b.telefono);
	    } while (!telefonoValido(b.telefono));
	
	    do
		{
	        printf("Ingrese su correo: ");
	        scanf(" %[^\n]", b.correo);
	    } while (!correoValido(b.correo));
	    
	    fwrite(&b, sizeof(b), 1, f);
	
	    printf("Profesor guardado correctamente. Desea agregar a otro profesor? (s/n): \n");
	    scanf(" %c", &continuar);
	}while(continuar == 's' || continuar == 'S');
	
	fclose(f);
}

int validarCorreo(char *correo) {
    return (strstr(correo, "@") != NULL && (strstr(correo, ".com") || strstr(correo, ".mx")));
}

int validarFecha(struct Fecha f) {
	int dia, mes, anio;

    time_t t = time(NULL);
    struct tm *ahora = localtime(&t);
    dia = ahora->tm_mday;
    mes = ahora->tm_mon + 1;
    anio = ahora->tm_year + 1900;

    if (f.anio > anio) return 0;
    if (f.anio == anio && f.mes > mes) return 0;
    if (f.anio == anio && f.mes == mes && f.dia > dia) return 0;
    if (f.dia < 1 || f.dia > 31 || f.mes < 1 || f.mes > 12) return 0;
    return 1;
}

int validarTelefono(char *telefono) {
    return strlen(telefono) == 10 && strspn(telefono, "0123456789") == 10;
}
