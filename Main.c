main()
{
	int opcion, cantidad;
	struct Inscripcion inscripciones[50];
	struct Alumno alumnos;
    int totalInscripciones = 0;
    int totalGrupos = 2;
    int totalAlumnos = 3;
    
    struct Profesor profesores;
             
    struct Materias mt;
    
    
    struct Grupos gp;
    
   
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
				ingresarMaterias(&mt);
                break;
                
            case 4:
               //Funcion grupo
               ingresarGrupos(&gp);
                break;
                
            case 5:
               //Funcion Inscripciones
               printf("\n¿Cuantas inscripciones desea registrar? ");
    			scanf("%d", &cantidad);

    			for (int i = 0; i < cantidad && totalInscripciones < 50; i++) {
        			printf("\n--- Registro %d ---\n", i + 1);
       				registrarInscripcion(&inscripciones[totalInscripciones], totalInscripciones + 1, grupo, totalGrupos, alumnos, totalAlumnos);
       				totalInscripciones++;
    			}
               guardarInscripcionesConDatos(inscripciones, totalInscripciones, alumnos, totalAlumnos, grupo, totalGrupos);

                break;
        	case 6:
               //funcion promedio
                break;
            case 7:
               //Funcion reportes
               mostrarMaterias();
                mostrarGrupos();
                break;
            
			case 8:
               //Salir
                break;
            
            default:
                printf("Por favor ingrese una opcion valida.\n");
        }
    } while (opcion != 0);
}
