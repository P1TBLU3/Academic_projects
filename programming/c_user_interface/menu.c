/**CFile***********************************************************************

  Fichero     [obligatorio]
  menu.c
  Resumen     [obligatorio]
  Es el motor de program.c. Se manejan todas las funciones declaradas en collection con
  el fin de realizar la funcion pedida por el usuario.

  Descripción [opcional]

  Ver también [opcional]

  Autor       [opcional]

  Copyright   [Copyright (c) 2012 Universidad Carlos III de Madrid

  Se concede, sin necesidad de acuerdo por escrito y sin ningún tipo de derechos
  de autor, permiso para utilizar, copiar, modificar y distribuir este programa
  y su documentación para cualquier propósito siempre y cuando esta advertencia
  y los siguientes dos párrafos aparezcan en las copias.

  EN NINGÚN CASO SE RECONOCERÁ A LA UNIVERSIDAD CARLOS III DE MADRID RESPONSABLE
  DIRECTA, INDIRECTA, ESPECIAL, O SUBSIDIARIA DE LOS POSIBLES DAÑOS Y PERJUICIOS
  QUE PUEDAN DERIVARSE DEL USO DE ESTE PROGRAMA Y DE SU DOCUMENTACIÓN, INCLUSO
  EN EL CASO DE QUE LA UNIVERSIDAD CARLOS III DE MADRID HAYA SIDO ADVERTIDA DE
  TALES DAÑOS Y PERJUICIOS.

  LA UNIVERSIDAD CARLOS III DE MADRID ESPECÍFICAMENTE SE DESENTIENDE DE TODO
  TIPO DE GARANTÍAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÍCITAS
  DE LA COMERCIALIZACIÓN Y ADECUACIÓN PARA CUALQUIER PROPÓSITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÓN ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/

/*---------------------------------------------------------------------------*/
/* Declaración de constantes                                                 */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Declaración de tipos                                                      */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Declaración de estructuras                                                */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Declaración de variables                                                  */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Declaración de macros                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Prototipos de las funciones estáticas                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Definición de las funciones                                               */
/*---------------------------------------------------------------------------*/
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "menu.h"
#include "input_usr.h"
#include "item.h"
#include "collection.h"
#include <unistd.h>
#include <ctype.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>




void Menu(){ 
  printf("\n"); 
  printf("Seleccione una de las siguientes opciones:\n");
  printf("\n");
  printf("1. Añadir un nuevo proceso a la planificación\n"); 
  printf("2. Borrar un proceso determinado de la planificación\n"); 
  printf("3. Información acerca de un proceso\n"); 
  printf("4. Mostrar toda la planificación\n"); 
  printf("5. Borrar la planificación actual\n");
  printf("6. Ordenar la planificación según un criterio\n");
  printf("7. Cargar un fichero\n");
  printf("8. Guardar en fichero\n");
  printf("9. Ejecutar Planificación\n");
  printf("10. Ayuda\n"); 
  printf("0. Salir\n");
  printf("\n"); 
  printf("Si introduce CTRL+D:\n");
  printf("-En este menú, el programa terminará de manera controlada.\n");
  printf("-En un submenú, el programa volverá a este menú.\n");
  }

struct collection Menu1(struct collection l, int* error){
  
  *error=0;
  int error0=0;
  int errorS=0;
  int errorI=0;
  
  printf("\n");
  printf("-Añadiendo un nuevo proceso-\n");
  printf("Introduzca el nombre de la propretaria:\n");
  char* name = getString(&errorS);
  printf("Introduzca la prioridad del proceso:\n");
  long  p = getInt(&errorI);
  printf("Introduzca el tiempo de ejecucion:\n");
  long  C = getInt(&errorI);

  if(p==-1||C==-1){
    *error=-1;
    return l;
  }else{
  
    l=add_item(l,name,p,C,0,&error0);
    if(error0==0){
      printf("Proceso añadido a la planificacion en la posicion : %i",l.number_occupied);
    }
    else if(error0 ==-2){
      printf("Hay un proceso con esos datos en la planificacion\n");
      printf("¿Desea añadirlo de todos modos?Responda S o N\n");
      char* ASK;
      char SoN;
     
      do{
	ASK = getString(&errorS);
	SoN= ASK[0];
	if(SoN=='S'||SoN=='s'){
	  l=add_item(l,name,p,C,1,&error0);
	  printf("Proceso añadido a la planificacion en la posicion : %i\n",l.number_occupied);
	  return l;
	  break;
	}else if (SoN== 'N'||SoN=='n'){
	  printf("Entendido\n");
	  break;
	}else{
	  printf("No le he entendido\n");
	}
      }while(SoN !='S' || SoN!='N'|| SoN!='n' || SoN!='s');
      free(ASK);
    }
  }
  free(name);
  printf("\n");

  return l;
}

struct collection Menu2(struct collection l,int * error){
  *error=0;
  int errorD=0;
  int errorI=0;
  
  printf("\n");
  printf("-Borrando un proceso-\n");
  printf("Introduzca el pid del proceso a borrar: ");
  long pidI= getInt(&errorI);
  printf("\n");
  l=delete_item(l,pidI,&errorD);
  if(errorD==0){
  printf("Proceso borrado\n");
  }
  else if(errorD==-2){
    *error=-2;
    return l;
  }
  else if(errorD==-3){
    *error=-3;
     return l;
  }

  return l;
  
}

void Menu3(struct collection l, int*error){
  *error=0;
  int errorD=0;
  int errorI=0;
  printf("\n");

  if(l.number_occupied==0){
    *error=-2;
  }else{
    printf("-Información de un proceso-\n");
    printf("Introduzca el pid del proceso a mostrar\n");
    long pidI=getInt(&errorI);
 
    int donde = find_pid(l,pidI,&errorD);
    if(donde==-2){
      *error=-1;//No existe
    }else{
      printf(" %5s %4s %5s %11s %19s\n","PID","P","C","STAT","OWNER");
      print_item(l.array[donde]);
    }
  }
  
}
 
void Menu4(struct collection l){  
  printf("\n");
  printf("-Mostrando toda la planificación-\n");
  printf("\n");
  print_all(l);
}

struct collection Menu5(struct collection l, int *error){
  *error=0;
  int errorS;
  if(l.number_occupied==0){
    *error=-1;
    printf("\n");
    return l;
  }else{
    printf("\n");
    printf("¿Quiere borrar toda la informacion?[S/N]\n");
    char* ASK;
    char SoN;
  
    do{  
      ASK = getString(&errorS);
      SoN = ASK[0];
      if(SoN=='S'|| SoN=='s'){
	printf("Borrando toda la planificación\n");
	l=clean_collection(l);
	free(ASK);
	return l;
	break;
      }else if(SoN=='N'|| SoN=='n'){
	printf("Borrado abortado.\n");
	free(ASK);
	return l;
	break;
      }else{
	printf("No le he entendido\n");
      }
    }while(SoN !='S' ||SoN !='N'|| SoN=='s'|| SoN=='n');
    free(ASK);
    return l;
  }
}

struct collection Menu6(struct collection l, int* error){
  *error=0;
  int errorI=0;
  int errorM=0;
  printf("\n");
  printf("Ordenando la planificacion por PID(1), P(2), C(3), OWNER(4)\n");
  
  printf("Introduzca una de las 4 opciones:\n");
  long choice=0;
  while(choice != 1 && choice != 2 && choice != 3 && choice != 4){
    choice = getInt(&errorI);
    if(choice != 1 && choice != 2 && choice != 3 && choice != 4){
      printf("Dato incorrecto\n");
    }
  }

  if(choice==1){
    l=sort_collection(l,compare_pid,&errorM);
  }else if(choice==2){
    l=sort_collection(l,compare_p,&errorM);
  }else if(choice==3){
    l=sort_collection(l,compare_C,&errorM);
  }else if(choice==4){
    l=sort_collection(l,compare_name,&errorM);
  }

  if(errorM==-1){
    *error=-4;//Vacio
  }

  printf("Coleccion ordenada\n");
  return l;
}


/*-------------------------FICHEROS-------------------------------*/

struct collection Menu7(struct collection l, int* error){
  *error=0;
  int errorL=0;
  int errorS=0;
  
  printf("\n");
  printf("-Cargando un fichero a la planificación-\n");
  printf("Indique el nombre del fichero: ");
  char* name = getString(&errorS);
  int existence = access(name, R_OK);
  
  if(existence!=0){
    *error=-1;
    free(name);
    return l;
  }else{
    if(l.number_occupied==0){
      l=load_file(name,&errorL);
      if(errorL==-2){
	*error=-2;
	free(name);
	return l;
      }
      printf("Fichero cargado a la planificación.\n");
      return l;
    }
    else{
      printf("La planificación actual no está vacía\n");
      printf("¿Desea seguir? Responder sí la borrará (S/N):");
      char* ASK ="";
      char SoN;
      do{  
	ASK = getString(&errorS);
	SoN = ASK[0];
	free(ASK);
	if(SoN=='S'|| SoN=='s'){
	  l=clean_collection(l);
	  l=load_file(name,&errorL);
	  if(errorL==-2){
	    *error=-2;
	    free(name);
	    return l;
	  }
	  printf("Fichero cargado a la planificación.\n");
	  free(name);
	  return l;
	  break;
	}else if(SoN=='N'|| SoN=='n'){
	  printf("Entendido.\n");
	  free(name);
	  return l;
	  break;
	}else{
	  printf("No le he entendido\n");
	}
      }while(SoN !='S' ||SoN !='N'|| SoN=='s'|| SoN=='n');
    }
  }

  return l;
}

void Menu8(struct collection l, int * error){
  *error=0;
  int errorL=0;
  int errorS=0;

  
  printf("\n");
  printf("-Guardando la planificación a fichero-\n");
  printf("Indique el nombre del fichero: ");
  char* namef = getString(&errorS);
  
  int can_write = access(namef,W_OK);
  int existence = access(namef,F_OK);
  
  if(existence == 0){
    if(can_write != 0){
      *error=-1;
      free(namef);
      return;
    }else{
      printf("El fichero ya existe, ¿desea sobreescribirlo?(S/N)\n");
      char* ASK;
      char SoN;
      do{  
	ASK = getString(&errorS);
	SoN = ASK[0];
	free(ASK);
	if(SoN=='S'|| SoN=='s'){
	  save_file(l,namef,&errorL);
	  if(errorL==-2){
	    *error=-2;
	    free(namef);
	    return;
	  }
	  printf("Planificación guardada a fichero %s",namef);
	  free(namef);
	  return;
	}else if(SoN=='N'|| SoN=='n'){
	  printf("Entendido.\n");
	  free(namef);
	  return;
	}else{
	  printf("No le he entendido\n");
	}
      }while(SoN !='S' ||SoN !='N' || SoN=='s' || SoN=='n');
    }
  }
  save_file(l,namef,&errorL);
  printf("Planificación guardada a fichero %s\n",namef);
  free(namef);
}


/*-------------------------PROCESOS--------------------------------*/

struct collection Menu9(struct collection l,int *error){
  *error=0;
  int errorE=0;
  printf("\n");
  if(l.number_occupied==0){
    *error=-1;
    return l;
  }else{
    printf("-Ejecutanto procesos-\n");
    print_all(l);
    l=process_exec(l,&errorE);
    if(errorE==-1){
      *error=-2;
    }
    printf("\n");
    printf("Resumen de ejecucion mandado a stats_process \n");
    return l;
  }
  return l;
}




/*-------------------INTRODUCIR OPCION----------------------*/

long askMenu(int * error){
  printf("\n");
  int errorI=0;
  printf("--Por favor, introduzca una opción (ayuda: 10): ");
  long numT= getInt(&errorI);
  
  if(errorI==-1){
    numT=11; 
  }
  else if(errorI==-2){
    *error=-2;
  }
  return numT;
}


/*---------------------------------------------------------------------------*/
/* Definición de las funciones estáticas                                     */
/*---------------------------------------------------------------------------*/


/*
int main(){
  int error=0;
  struct collection l = initialize_collection(&error);
  l=Menu7(l,&error);
  l=Menu9(l,&error);
  
}
*/
