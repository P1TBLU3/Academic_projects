/**CHeaderFile*****************************************************************

  Fichero     [obligatorio]
  collection.h
  Resumen     [obligatorio]
  Declaracion de la estructura collection, la cual contiene la capacidad y el numero de procesos
  de la misma, ademas de el array dinámico donde se alojan dichos procesos

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
#ifndef COLLECTION_H
#define COLLECTION_H
#include "item.h"
#include <unistd.h>
#include <stdio.h>

struct collection{
  int total_capacity;
  int number_occupied;
  struct item *array; //Creacion array dinámico
};



/*---------------------------------------------------------------------------*/
/* Declaración de variables                                                  */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Declaración de macros                                                     */
/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/
/* Protitpos de las funciones                                                */
/*---------------------------------------------------------------------------*/
struct collection initialize_collection(int * error);

struct collection clean_collection(struct collection col);

int find_pid(struct collection col,int pid, int* error);

int find_item(struct collection col, char* name,long p, long C);

struct collection add_item(struct collection col, char* name, long  p , long C,int rep, int *error);

struct collection delete_item(struct collection col,int pid, int *errnum);

void print_header();

void print_all(struct collection col);

struct collection sort_collection(struct collection col, int (*compare)(const void*, const void*), int*error);

struct collection load_file(char* name, int* error);

void save_file(struct collection col,char* namef, int* error);

void my_signals (int s);

struct collection process_exec (struct collection col, int*error);

#endif
