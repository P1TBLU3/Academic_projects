/**CFile***********************************************************************

  Fichero     [obligatorio]
  item.c
  Resumen     [obligatorio]
  Manejo de un proceso (item).
  -Crear un proceso
  -Borrar un proceso
  -Imprimir un proceso
  Tambien se declaran cuatro funciones que comparan dos procesos para usarlo en collection.c

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
#define _POSIX_C_SOURCE 200809L
#include "item.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "collection.h"
#include <stdlib.h>
static char *xstrdup(const char *s) {
  if (s == NULL) return NULL;
  size_t n = strlen(s) + 1;
  char *p = (char *)malloc(n);
  if (p == NULL) return NULL;
  memcpy(p, s, n);
  return p;
}

/*---------------------------------------------------------------------------*/
/* Declaración de constantes                                                 */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Declaración de tipos                                                      */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Declaración de estructuras                                                */
/*---------------------------------------------------------------------------*/
struct item create_item(char *name, long  p ,long  C,int *error){
  struct item aux;
  static int pid  = 0;
  
  *error = 0;
  errno = 0;

  aux.data.name = NULL;
  aux.data.name = xstrdup(name);
  if (aux.data.name == NULL){
    *error = errno;
    return aux;
  }
  
  aux.data.p = p;
  aux.data.C = C;
  aux.data.state=0;
 

  pid++;
  aux.pid=pid;
  
  return aux;
}

void free_item(struct item foo){
  if (foo.data.name)
    free(foo.data.name);
}

void print_item(struct item i){
  printf("%5i ", i.pid);
  printf("%5i " , i.data.p);
  printf("%5i " , i.data.C);
  
  if (i.data.state == 0){
    printf("%11s ", "READY");
  }else if(i.data.state==1){
    printf("%11s ","RUNNING");
  }else if(i.data.state==2){
    printf("%11s ", "TERMINATED");
  }
  
  printf("%20s \n", i.data.name);
}

int compare_name(const void *pa, const void *pb){
  struct item *a = (struct item *)pa;
  struct item *b = (struct item *)pb;

  return (strcmp(a-> data.name, b-> data.name));
}

int compare_pid(const void *pa, const void *pb){
  struct item *a = (struct item *)pa;
  struct item *b = (struct item *)pb;

  if(a-> pid == b-> pid)
    return 0;
  if(a-> pid < b->pid)
    return -1;

  return 1;
}

int compare_p(const void *pa, const void *pb){
  struct item *a = (struct item *)pa;
  struct item *b = (struct item *)pb;

  if(a-> data.p == b-> data.p)
    return 0;
  if(a-> data.p < b-> data.p)
    return -1;

  return 1;
}

int compare_C(const void *pa, const void *pb){
  struct item *a = (struct item *)pa;
  struct item *b = (struct item *)pb;

  if(a-> data.C == b-> data.C)
    return 0;
  if(a-> data.C < b-> data.C)
    return -1;

  return 1;
}

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
