/**CFile***********************************************************************

  Fichero     [obligatorio]
  program.c
  Resumen     [obligatorio]
  Programa que se encarga de manejar los menus de menu.c y sus respectivos errores a partir
  de la decision del usuario.
  Los errores manejados en este fichero son aquellos que detienen la funcion a ejecutar.
  Por ejemplo, en el menu1 se imprime el error que impide a menu.c añadir el proceso, pero no el 
  "error" de añadir un proceso existente.
  Se maneja tambien la tecla CTRL+D a través de la variable auxiliar cD que indica 0 si está en 
  el menu principal y 1 si está en un submenu.
  Se sabe si el usuario ha introducido CTRL+D si el error de getInt (errorA) es -2.

  Descripción [opcional]

  Ver también [opcional]

  Autor       [opcional]

  Copyright   [Copyright (c) 2011 Universidad Carlos III de Madrid

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
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "item.h"
#include "collection.h"
#include "input_usr.h"



/*--------------------main---------------------*/

int main(int argc, char **argv){
  printf("\n");
  printf("-PROGRAMA QUE EMULA UN PLANIFICADOR DE PROCESOS-\n");
  int error = 0;
  int errorA=0;
  int cD=0;

  //CREACION DE LA COLECCION
  struct collection lista = initialize_collection(&error);

  Menu();
  long N;

do{

  N=askMenu(&errorA);
  if(errorA==-2){
    if(cD==1){
      N=-1;
      errorA=0;
    }else if(cD==0){
      N=0;
    }
  }
  
  //OPCION MENU
  if(N==-1){
    printf("\n");
    Menu();
    cD=0;
  }
  
  //OPCION SALIR
  else if(N==0){
    printf("\n");
    printf("PROGRAMA TERMINADO\n");
    printf("\n");
    if(lista.number_occupied!=0){
      lista=clean_collection(lista);
    }
    exit(EXIT_SUCCESS);
 }
  
  //OPCION 1
  else if(N==1){
    lista=Menu1(lista,&error);
    
    if(error==-1){
      fprintf(stderr,"Prioridad o Tiempo de ejecución erroneamente introducido.\n");
      fprintf(stderr,"Nada añadido a la coleccion.\n");
    }
    cD=1;     
  }
  
  //OPCION 2
  else if(N==2){
    lista=Menu2(lista,&error);

    if(error==-2){
      fprintf(stderr,"Lista Vacia\n");
    }else if(error==-3){
      fprintf(stderr,"Proceso no encontrado\n");
    }
    cD=1;
  }

  //OPCION 3
  else if(N==3){
    Menu3(lista,&error);

    if(error==-1){
      fprintf(stderr,"No existe el proceso\n");
    }else if(error==-2){
      fprintf(stderr,"Lista Vacía\n");
    }
    cD=1;
  }

  //OPCION 4
  else if(N==4){
    Menu4(lista);
    cD=1;
  }

  //OPCION 5
  else if(N==5){
    lista=Menu5(lista,&error);
    
    if(error==-1){
      fprintf(stderr,"Lista ya vacía\n");
    }
    cD=1;
  }

  //OPCION 6
  else if(N==6){
    lista=Menu6(lista,&error);

    if(error==-4){
      printf("Lista vacía\n");
    }
    cD=1;
  }

  //OPCION 7
  else if(N==7){
    lista=Menu7(lista, &error);
    if(error==-1){
      fprintf(stderr,"El fichero no existe o no se puede leer.\n");
    }else if(error==-2){
      fprintf(stderr,"Error al cerrar el fichero\n");
    }
    cD=1;
  }

  //OPCION 8
  else if(N==8){
    Menu8(lista, &error);
    if(error==-1){
      fprintf(stderr,"El fichero existe pero no se puede escribir.\n");
    }else if(error==-2){
      fprintf(stderr,"Error al cerrar el fichero\n");
    }
    cD=1;
  }

  //OPCION 9
  else if(N==9){
    lista=Menu9(lista,&error);
    
    if(error==-1){
      fprintf(stderr,"Lista Vacía. Nada que ejecutar\n");
    }else if (error==-2){
      fprintf(stderr, "Error en fork()\n");
    }
    cD=1;
  }

  //OPCION AYUDA
  else if(N==10){
    Menu();
    cD=1;
  }

  //DATO INCORRECTO
  else{
    printf("ERROR: Dato incorrecto\n"); 
  }

  
}while(1);
 
  return 0;     
}
