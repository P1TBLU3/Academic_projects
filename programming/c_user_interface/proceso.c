/**CFile***********************************************************************

  Fichero     [obligatorio]
  proceso.c
  Resumen     [obligatorio]

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
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>



int main(int argc, char* argv[]){
  if(argc!=3){
    printf("ERROR: No hay suficientes argumentos\n");
    exit(EXIT_FAILURE);
  }
  
  int n1=(int)strtol(argv[1],NULL,10);
  int n2=(int)strtol(argv[2],NULL,10);
  if(n1<0||n2<0){
    printf("ERROR: Valor negativo introducido\n");
    exit(EXIT_FAILURE);
  }
  char stars[n2 + 1];
  stars[0] = '\0';
  for (int j = 0; j < n2; j++) {
    stars[j] = '*';
  }
  stars[n2] = '\0';

  unsigned long long i = 0;
  while (1) {
    printf("[%i] Proceso %i %s iter %llu\n", getpid(), n1, stars, i + 1ULL);
    fflush(stdout);
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 500000000L;
    nanosleep(&ts, NULL);
    i++;
  }

return 0;

}

  
