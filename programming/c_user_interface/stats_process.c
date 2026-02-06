/**CFile***********************************************************************

  Fichero     [obligatorio]
  stats_process.c
  Resumen     [obligatorio]
  Programa que recibe los datos de ejecucion procedentes de collection.c
  Para crear el FIFO y ayudarlo me ha sido de ayuda el siguiente video:
  https://www.youtube.com/watch?v=--r9XYsj2ew
  
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


/*---------------------------------------------------------------------------*/
/* Definición de las funciones estáticas                                     */
/*---------------------------------------------------------------------------*/
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "collection.h"
#include "item.h"

int main(){
  
  int fd;
  
  mkfifo("MYFIFO",0666);
  
  fd=open("MYFIFO",O_RDONLY);
  

  int numP=0;
  read(fd,&numP,sizeof(int));//Leemos cuantos procesos hay
  
  int r_pid[numP];
  int r_p[numP];
  int r_state[numP];
  int r_robin_loop[numP];
  int r_s;

  read(fd,r_pid,sizeof(r_pid));
  read(fd,r_p,sizeof(r_p));
  read(fd,r_state,sizeof(r_state));
  read(fd,r_robin_loop,sizeof(r_robin_loop));
  read(fd,&r_s,sizeof(int));

  printf("RESUMEN EJECUCION\n");
  printf("%s %6s  %10s %13s %12s\n","PID"," REAL-PID","STAT","NUM-EXEC","END-STATUS");
  char *stat = "UNKNOWN";
  for(int l=0; l < numP ; l++){
    if(r_state[l] == 0)
      stat="READY";
    else if (r_state[l] == 1)
      stat="RUNNING";
    else if (r_state[l]==2)
      stat="TERMINATED";
     
    printf("%2i %9i %13s %8i %10i \n", r_pid[l] , r_p[l] , stat , r_robin_loop[l],r_s);
  }
  printf("\n");

  
  close(fd);
  
  return 0;
}
