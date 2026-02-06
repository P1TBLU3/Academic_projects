import java.util.*;
import java.util.concurrent.Semaphore;

public class Dungeon {

    public static void main(String[] args) {

	Alchemist a;
	Semaphore barreraEntrada, mutexBarreraEntrada, mutexEsperaEntrada;
	Semaphore semTotal,semAntecamara, semGrupo,semPermisoPasillo,semAuxPasillo,semPasillo, semGuarida;
	Semaphore  mutexAntecamara, mutexGrupo,mutexDireccion,mutexBarreraPasillo,mutexPasillo ,mutexGuarida,mutexCap;
    Semaphore semNegro,semPequeno1,semPequeno2,semEsperaPorDragon;
    Semaphore mutexEsperaPorDragon,mutexDragones,mutexColaNegro,mutexColaPequeno1,mutexColaPequeno2;
    Semaphore mutexDentroNegro,mutexDentroPequeno1,mutexDentroPequeno2;
    
    
    
    barreraEntrada=new Semaphore(0);
    mutexBarreraEntrada=new Semaphore(1);
    mutexEsperaEntrada=new Semaphore(1);
    
	semTotal= new Semaphore(24);//Numero maximo de gente que puede haber dentro de la dungeon sin que haya deathblock //sin tener en cuenta dragones
	semAntecamara = new Semaphore(5);
	semGrupo = new Semaphore(3);
	semPermisoPasillo= new Semaphore(0);
	semAuxPasillo=new Semaphore(1);
	semPasillo= new Semaphore(9);
	semGuarida = new Semaphore(20);
	
	mutexAntecamara = new Semaphore(1);
	mutexGrupo= new Semaphore(1);
	mutexDireccion=new Semaphore(1);
	mutexBarreraPasillo=new Semaphore(1);
	mutexPasillo = new Semaphore(1);
	mutexGuarida = new Semaphore(1);
	mutexCap= new Semaphore(1);
	
	semNegro = new Semaphore(0);
   	semPequeno1 = new Semaphore(0);
   	semPequeno2 = new Semaphore(0);
   	semEsperaPorDragon=new Semaphore(0);
   	
   	mutexEsperaPorDragon=new Semaphore(1);
   	mutexDragones=new Semaphore(1);
   	mutexColaNegro = new Semaphore(1);
   	mutexColaPequeno1 = new Semaphore(1);
   	mutexColaPequeno2 = new Semaphore(1);
   	
   	mutexDentroNegro = new Semaphore(1);
   	mutexDentroPequeno1 = new Semaphore(1);
   	mutexDentroPequeno2 = new Semaphore(1);
   	
   	Dragon Drogon,Viserion,Rhaegal;
   	int iteraciones =5;//numero de veces que cada dragon hace su ciclo
	Random rnd=new Random();
   	
	Drogon=new Dragon( rnd, "Drogon", iteraciones, mutexColaNegro, mutexColaPequeno1, mutexColaPequeno2, semNegro, semPequeno1, semPequeno2
			,  mutexDentroNegro, mutexDentroPequeno1, mutexDentroPequeno2, semEsperaPorDragon
			, mutexDragones, mutexDireccion, mutexPasillo,  mutexGuarida, mutexCap);
   	
   	Viserion=new Dragon( rnd, "Viserion", iteraciones, mutexColaNegro, mutexColaPequeno1, mutexColaPequeno2, semNegro, semPequeno1, semPequeno2
			,  mutexDentroNegro, mutexDentroPequeno1, mutexDentroPequeno2, semEsperaPorDragon
			, mutexDragones, mutexDireccion, mutexPasillo,  mutexGuarida, mutexCap);
   
   	
   	Rhaegal=new Dragon( rnd, "Rhaegal", iteraciones, mutexColaNegro, mutexColaPequeno1, mutexColaPequeno2, semNegro, semPequeno1, semPequeno2
			,  mutexDentroNegro, mutexDentroPequeno1, mutexDentroPequeno2, semEsperaPorDragon
			, mutexDragones, mutexDireccion, mutexPasillo,  mutexGuarida, mutexCap);
   	
   	
	for (int i=0; i <39; i++){
	    a = new Alchemist(i, rnd, barreraEntrada, mutexBarreraEntrada, mutexEsperaEntrada
	    		, semTotal, semAntecamara,  semGrupo, semAuxPasillo, semPermisoPasillo, semPasillo, semGuarida 
	    		, mutexAntecamara, mutexGrupo, mutexDireccion, mutexBarreraPasillo,mutexPasillo,  mutexGuarida, mutexCap
	    		, semNegro, semPequeno1, semPequeno2,semEsperaPorDragon
	    		, mutexEsperaPorDragon, mutexDragones, mutexColaNegro, mutexColaPequeno1, mutexColaPequeno2);
	    
	    if(i==0) {
	       	Drogon.start();
	        Viserion.start();
	    	Rhaegal.start();
	    }
	    
	    a.start();
	}
    }

    }
