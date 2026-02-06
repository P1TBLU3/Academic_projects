/**CFile***********************************************************************

  Fichero     [obligatorio]
  input_usr.c
  Resumen     [obligatorio]
  Dos funciones:
  -Pedir cadena de texto a usuario
  -Pedir un numero a usuario
  **Si al pedir el numero se introduce un valor negativo o una letra, se devolverá un -1
  **Si al pedir la cadena o el numero se introduce CTRL+D, se asignará al error -2, el cual será 
  manejado en program.c y menu.c
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
#include <errno.h>
#include <string.h>
#include "menu.h"
#include "input_usr.h"
#include <ctype.h>


char* getString(int *error) {

*error=0;
  
char* cadena;
ssize_t num_leidos;
size_t npedidos;
 
errno=0;
npedidos = 0;
cadena=NULL;
 
num_leidos=getline(&cadena, &npedidos, stdin);
 
if(num_leidos==-1){
  if(errno!=0){
    *error=-1;//ERROR
  }else{
    clearerr(stdin);
    *error=-2;//CTRL+D
  }
}
 return cadena;
}

long getInt(int *error) {
  int errorS = 0;
  long num = 0;
  char *ptr = NULL;
  char *cad = getString(&errorS);

  if (errorS != 0) {
    *error = errorS;
    return -1;
  }

  if (cad == NULL) {
    *error = -1;
    return -1;
  }

  for (size_t i = 0; i < strlen(cad); i++) {
    if (isalpha((unsigned char)cad[i]) != 0) {
      free(cad);
      *error = -1;
      return -1;
    }
  }

  errno = 0;
  num = strtol(cad, &ptr, 10);
  free(cad);

  if (errno != 0 || ptr == NULL) {
    *error = -1;
    return -1;
  }

  *error = 0;
  return num;
}

  
/*---------------------------------------------------------------------------*/
/* Definición de las funciones estáticas                                     */
/*---------------------------------------------------------------------------*/

