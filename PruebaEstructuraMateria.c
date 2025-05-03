#include <stdio.h>

struct Materias 
{
	int clave, semestre;
	char nombre[20], descripcion[20];	
};

main()
{
	struct Materias mt[50];
	int totalMaterias = 0, opcion;
	char op[2];
	
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
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
		{
            case 1:
                
                break;
           
            case 2:
               
                break;
                
            case 3:
            	do
				{
            		ingresarMaterias(&mt[totalMaterias++]);
            		printf("Desea agregar otra materia: ");
            		fgets(op, 2, stdin);
            		if (op == 'No')
            			printf("Regresando al menu principal");	
            	}while(op == 'Si');
            	
                break;
                
            case 4:
               
                break;
                
            case 5:
               
                break;
        	case 6:
               
                break;
            case 7:
               
                break;
            
			case 8:
               
                break;
            
            default:
                printf("Opción no valida.\n");
        }
    } while (opcion != 0);
}

void ingresarMaterias(struct Materias mt[])
{
	int i, clave, semestre;
	char nombre[20], descripcion[30], nombreSinValidar[20], descSinValidar[30];
	/*for (i = 0; i < 2; i++)
	{
		if (mt[i].clave != '\n' && mt[i].semestre != '\n' 
		&& mt[i].nombre != '\n' && mt[i].descripcion != '\n')  //mt[i).clave mt[i).semestre etc
		{*/
			do {
				printf("\nIngresa la clave de la materia: ");
				scanf("%d", &clave);
				if (clave < 0)
					printf("Ingrese una clave mayor a 0");
			}
			while(clave < 0);
			
			mt[i].clave = clave;
				
			do {
				printf("\nIngresa el semestre de la materia: ");
				scanf("%d", &semestre);
				if (semestre < 0 || semestre > 10)
					printf("Ingrese un semestre mayor a 0 y menor a 10");
			}
			while(semestre < 0 || semestre > 10);
			
			mt[i].semestre = semestre;
				
			do {
				printf("\nIngresa el nombre de la materia: ");
				fflush(stdin);
				scanf("%s", &nombreSinValidar);
				//fgets(nombre, 20, stdin);
			if (strlen(nombreSinValidar) == 0) 
			{
        		printf("El nombre no puede estar vacío. Intente de nuevo.\n");
    		}
			}while (strlen(nombreSinValidar) == 0);
			
			strcpy(mt[i].nombre, nombreSinValidar);
			//[Error] assignment to expression with array type mt[i].nombre = nombre;
			
			do {
				printf("\nIngresa la descripcion de la materia: ");
				fflush(stdin);
				scanf("%s", &descSinValidar);
				//fgets(descripcion, 30, stdin);
			if (strlen(descSinValidar) == 0) 
			{
        		printf("El nombre no puede estar vacío. Intente de nuevo.\n");
    		}
			}while (strlen(descSinValidar) == 0);
			
			strcpy(mt[i].descripcion, descSinValidar);
			//[Error] assignment to expression with array type mt[i].descripcion = descripcion;		
	/*	}
			printf("Cupo de Materias lleno");
	}*/
	
}
