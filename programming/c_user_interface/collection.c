

/**CFile***********************************************************************

  Fichero     [obligatorio]
  collection.c
  Resumen     [obligatorio]

  Fichero donde se maneja una colección de procesos (items). Incluye:
  -Funciones para inicializar o limpiar la coleccion
  -Funciones para añadir o eliminar un proceso de la colección
  -Funcion auxiliares para encontrar un proceso o el pid del mismo
  -Funcion para ordenar la colección
  -Funcion guardar y cargar fichero
  -Manejo de procesos (Menu9)

  Se han utilizado como referencia las transparencias otorgadas por los profesores
  para la creacion de algunas funciones pertenecientes a la primera parte.

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
int CC=0;

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

#include "collection.h"
#include "item.h"
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>



struct collection initialize_collection(int * error){ 
  struct collection col;
  *error = 0;
  errno = 0;
  col.array = (struct item *) malloc (5 * sizeof(struct item));
  if (col.array == NULL){
    *error = errno;
    return col;
  }
  col.total_capacity = 5;
  col.number_occupied = 0;
  return col;
}

struct collection clean_collection(struct collection col){ 
  if(col.array != NULL){
    for(int i = 0; i<col.number_occupied; i++){
      free_item(col.array[i]);
    }
    free(col.array);
    memset(&col, 0 ,sizeof(struct collection));
  }
  col.array=NULL;
  col.number_occupied=0;
  return col;
}

int find_pid(struct collection col, int pid,int *error){ //BUSCA PROCESO EN BASE A PID
  *error=0;
  int s=-2;
  if(col.number_occupied==0){
    *error=-1; //Vacio
    s= -1;
  }

  for(int i=0; i<col.number_occupied; i++){
    if(col.array[i].pid==pid){
      s= i;
    }
  }
  return s;
}

int find_item(struct collection col, char* name, long p, long C){  //BUSCA UN OBJETO EN BASE A NOMBRE-P-C
  int s=-1;
  if(col.number_occupied==0){
    s= -1;//vacio
  }

  
  for(int i=0; i<col.number_occupied; i++){
    if(col.array[i].data.C==C &&  col.array[i].data.p==p && (strcmp(col.array[i].data.name,name)==0)){ 
      return i;
    }
  }
  return s;
}
  

struct collection add_item(struct collection col, char* name, long  p , long  C ,int rep, int *error){ //AÑADE PROCESO
  *error=0;
  int errorIn=0;
  int errorCr=0;

  if(rep==0){//rep será distinto de 0 cuando se añada un proceso ya existente, por lo que ya no se necesitará comprobar si ya existe el proceso.
    int i = find_item(col,name,p,C);
    if(i !=-1){
      *error=-2; //Ya está en la coleccion
      return col;
    }
  }
  
  if(col.number_occupied==col.total_capacity){
    if(col.number_occupied==0){
      col=initialize_collection(&errorIn);
      if(errorIn){
	return col;
      }
    }else{
      int new_capacity=col.total_capacity*2;
      size_t pedir= new_capacity * sizeof(struct item);
      struct item *tmp;
      tmp=(struct item *) realloc(col.array, pedir);
      if(tmp==NULL){
	*error=errno;//No hay espacio
	free(tmp);
	return col;
      }	
      col.array=tmp;
      col.total_capacity = new_capacity;
    }
  }
    
  struct item new_item = create_item(name,p,C,&errorCr);
  col.array[col.number_occupied]=new_item;
    
  if(*error){
    return col;
  }
    
  col.number_occupied++;
  return col;

}



struct collection delete_item(struct collection col,int pid, int *error){
  *error = 0;
  if (col.number_occupied == 0){
    *error = -2;//Vacío
    clean_collection(col);
    return col;
  }
  int i = find_pid(col, pid,error);
  
  if ((i == -2) || (*error)) {
    *error =-3;//No se ha encontrado
    return col;
  }
  
  free_item(col.array[i]);
   col.number_occupied--;
 
  
  if ((col.number_occupied) &&(i != col.number_occupied)){
    memcpy(&(col.array[i]),&(col.array[col.number_occupied]),sizeof(struct item));
  }
  
  
  return col;   
}

void print_header(){
  printf("%5s %5s %5s %5s %11s %19s\n","POS","PID","P","C","STAT","OWNER");
}

void print_all(struct collection col){
  if(col.number_occupied==0){
    printf("Lista de Procesos Vacia\n"); //up
  }else{
    print_header();
    for(int i=0;i<col.number_occupied;i++){
      printf("%5i ", i+1);
      print_item(col.array[i]);
    }
  }
}

struct collection sort_collection(struct collection col, int (*compare)(const void*, const void*), int*error){
  *error = 0;
  if(col.number_occupied != 0){
    qsort(col.array, col.number_occupied, sizeof(struct item),compare);
  }
  else{
    *error=-1;//Vacio
  }
  return col;
}





/*-------------------------------FICHEROS---------------------------------------*/


struct collection load_file(char* name, int* error){
  FILE *f= fopen(name,"r");
  size_t leidos=0;
  int errorC=0;
  int errorI=0;
  
  int i=0;
  
  struct collection col=initialize_collection(&errorI);
  
  while (!feof(f)){
    int len;
    char *name;
    int p;
    int C;
    int state;
    leidos= fread(&len, sizeof(int), 1, f);
    name = (char*)malloc(len+1);
    leidos= fread(name,sizeof(char),len,f);
    name[len] = '\0';
    leidos= fread(&p,sizeof(int),1,f);
    leidos= fread(&C,sizeof(int),1,f);
    leidos= fread(&state,sizeof(int),1,f);
    if (leidos != 1){
      break;
    }
    col=add_item(col,name, p, C,0, &errorC);
    i++;
    free(name);
  }
  
 
  
  if (fclose(f)!=0){
    *error=-2;//No se ha cerrado bien el fichero
  }


  return col;
}

void save_file(struct collection col, char* namef, int * error){
 
  FILE *f = fopen(namef,"w");
  size_t escritos = 0;
  
  for(int i=0; i<col.number_occupied; i++){
    int len = strlen(col.array[i].data.name);
    escritos=fwrite(&len,sizeof(int),1,f);
    escritos=fwrite(col.array[i].data.name,sizeof(char),len,f);
    escritos=fwrite(&col.array[i].data.p,sizeof(int),1,f);
    escritos=fwrite(&col.array[i].data.C,sizeof(int),1,f);
    escritos=fwrite(&col.array[i].data.state,sizeof(int),1,f);
    if(escritos!=1){
      *error=-1;
    }
  }

 
  

  if (fclose(f)!=0){
    *error=-2; //No se ha cerrado bien el fichero
  }

  
 
}
  

/*------------------------PROCESOS---------------------------------*/
/*
void print_exec(struct collection col, int * p, int * r_l, int s){
  printf("%s %6s  %10s %13s %12s\n","PID"," REAL-PID","STAT","NUM-EXEC","END-STATUS");
  int numP=col.number_occupied;
  char * stat;
  for(int l=0; l < numP ; l++){
    int get_pid=col.array[l].pid;
    
    if(col.array[l].data.state == 0)
      stat="READY";
    else if ( col.array[l].data.state == 1)
      stat="RUNNING";
    else if (col.array[l].data.state==2)
      stat="TERMINATED";
     
    printf("%2i %9i %13s %8i %10i \n", get_pid , p[l] , stat , r_l[l], s);
  }
}
*/

void my_signals (int s){
  if(s==SIGALRM){
    alarm(1);
    return;
  }
  if(s==SIGINT){
    CC=1; //Variable global
    return;
  }
  return;
}



struct collection process_exec(struct collection col, int *error){
  int numP=col.number_occupied;  
  int status=0;
  pid_t  p [numP];
  int u;

  printf("Lanzo los procesos hijos\n");

  int get_p=0;
  int get_pid=0;
  
  for(int i=0; i<numP+1 ; i++){
    char n1 [100];
    char n2 [100];
    get_p = col.array[i].data.p;
    get_pid = col.array[i].pid;
    sprintf(n1,"%i",get_pid);
    sprintf(n2,"%i",get_p);
    
    p[i]=fork();
    if(p[i]<0){
      *error=-1; //Error en fork
      _exit(EXIT_FAILURE);
    }
    
    else if (p[i]==0){
      p[i]=getpid();
      execlp("./p", "p",n1,n2,NULL);
      printf("Ejecución del hijo fallida");
      kill(p[i],SIGKILL);
      _exit(EXIT_FAILURE);
    }
  }
  for(int k=0; k<numP +1 ; k++){
    kill(p[k], SIGSTOP);
  }
  printf("He suspendido a todos mis hijos\n");
  
  
  int w_pid[numP];
  int w_state[numP];
  //Arrays para poder escribir luego el pid y los estados en el FIFO
  
  int robin_loop [numP]; //guardará las veces que ejecutamos un proceso
  int terminated_processes [numP]; /*Array que indica el estado de los procesos:
				     - 0 si no está terminado
				     - 1 si está terminado                   */ 
  
  for(int x=0; x<=numP ;x++){ //Inicializacion de robin_loop y terminated_processes
    robin_loop [x]=0;
    terminated_processes [x] = 0;
  }

  int C [numP];
  for(int c=0; c< numP ; c++){ //Recogida de los tiempos de ejecucion
    C[c]= col .array[c].data.C;
  }
  
  alarm(1);
  int end_loop = 0;
  //end_loop nos permitirá salir del bucle cuando se hayan terminado los procesos
  
  int s=WEXITSTATUS(status);
  
  while(CC!=1 || end_loop != 1){
    for(int j = 0 ; j<numP ; j++){
      if(terminated_processes[j]!=1){ //Solo entramos si el proceso no está terminado
	kill(p[j],SIGCONT);
	robin_loop[j] ++;
	signal(SIGALRM,my_signals);
	signal(SIGINT,my_signals);
	
	if(CC==1){ //CTRL+C detectado
	  CC=0;
	  printf("\n");
	  col.array[j-1].data.state=1;//RUNNING
	  //Recogemos los pid y los estados
	  for(int u=0; u<col.number_occupied; u++){
	    w_pid[u]=col.array[u].pid;
	    w_state[u]=col.array[u].data.state;
	  }
	  //Pasamos a MYFIFO:
	  int fd;
	  fd=open("MYFIFO",O_WRONLY);
  
	  write(fd,&numP,sizeof(int));//Escribimos tambien el numero de procesos
	  write(fd,w_pid,sizeof(w_pid));
	  write(fd,p,sizeof(p));
	  write(fd,w_state,sizeof(w_state));
	  write(fd,robin_loop,sizeof(robin_loop));
	  write(fd,&s,sizeof(int));
	  close(fd);
	 
	  for(int y = 0; y<numP ;  y++){
	    kill(p[y],SIGKILL); //Matamos todos los procesos
	  }
	  return col;
	  break;
	  
	}else{
	  pause();
	  kill(p[j],SIGSTOP);
	  if(robin_loop[j] != C[j]){
	    col.array[j].data.state=0;//READY
	  }else{
	    col.array[j].data.state=2;//TERMINATED
	    kill(p[j],SIGTERM);
	    terminated_processes [j] = 1;
	    end_loop=1; //Salimos del bucle, de momento...
	    for(int t=0; t<numP; t++){  //Comprobamos si podemos salir del bucle
	      if(terminated_processes [t]!=1){ 
		end_loop=0;  //Los procesos no han terminado, end_loop seguirá siendo 0 : no se sale del bucle
	      }
	   
	    }
	  }
	}
      }
    }
    if(end_loop==1){
      break; //Salimos del bucle
    }
  }

 
  //Recogemos los pid y los estados
  for(u=0; u<col.number_occupied; u++){
    w_pid[u]=col.array[u].pid;
    w_state[u]=col.array[u].data.state;
  }
  
 //Pasamos a MYFIFO:
   int fd;
  fd=open("MYFIFO",O_WRONLY);
  
  write(fd,&numP,sizeof(int));
  write(fd,w_pid,sizeof(w_pid));
  write(fd,p,sizeof(p));
  write(fd,w_state,sizeof(w_state));
  write(fd,robin_loop,sizeof(robin_loop));
  write(fd,&s,sizeof(int));
  
  close(fd);
  
  return col;
}




/*---------------------------------------------------------------------------*/
/* Definición de las funciones estáticas                                     */
/*---------------------------------------------------------------------------*/

/*
int main(){
  int error = 0;
  struct collection l = initialize_collection(&error);

  l=add_item(l,"Jose",1,1,0,&error);
  l=add_item(l,"Victor",4,2,0,&error);
  l=add_item(l,"Calin",2,1,0,&error);
  l=add_item(l,"David",1,1,0,&error);
  l=add_item(l,"Marcos",3,3,0,&error);

  process_exec(l,&error);
  
  printf("SUCCESS\n");

  print_all(l);

  

  return 0;
}

*/








