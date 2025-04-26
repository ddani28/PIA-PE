#include <stdio.h>


main()
{int totalMaterias=0;
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
            	ingresarMaterias(&mt[totalMaterias++]);
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

