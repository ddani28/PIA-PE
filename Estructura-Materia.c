#include <stdio.h>

struct Materias 
{
	int clave, semestre;
	char nombre[20], descripcion[50];	
};


main()
{
	struct Materias materia;
}

int validarClaveMaterias(struct Materias materia)
{	
	printf("Ingrese la clave de la materia: ");
	scanf("%d", &materia.clave);
	if (materia.clave > 0)
	{
		printf("Agregado correctamente");
		return materia.clave;
	}
	else
	{
		printf("Ingrese una clave mayor a cero");
		scanf("%d", &materia.clave);
	}
}

int validarSemestreMaterias(struct Materias materia)
{
	printf("Ingrese el semestre de la materia: ");
	scanf("%d", &materia.semestre);
	if (materia.clave > 0 && materia.clave <= 10)
	{
		printf("Agregado correctamente");
		return materia.semestre;
	}
	else
	{
		printf("Ingrese un semestre entre cero y diez");
		scanf("%d", &materia.semestre);
	}
}

void validarNombre(struct Materias materia)
{
	//No este vacia la cadena
}

void validarDescripcionMateria(struct Materias materia)
{
	//No este vacia la cadena
}




