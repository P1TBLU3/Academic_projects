
import java.util.*;
import java.util.concurrent.Semaphore;
 
public class Alchemist extends Thread{
    private int me;
    protected static int direccion;//0 nadie dentro, 1 izda-dcha, 2 dcha
    private Random rnd;
    private Semaphore barreraEntrada;
    private static boolean esperoEntrada;
    private Semaphore mutexBarreraEntrada,mutexEsperaEntrada; 
    private Semaphore semTotal,semAntecamara, semGrupo,semPermisoPasillo,barreraPasillo,semPasillo, semGuarida;
    
    private static int numAntecamara, numGrupo;
    
    protected static int numPasillo,numGuarida;
    protected static int capGuarida=25;
    
    private Semaphore  mutexAntecamara, mutexGrupo,mutexDireccion,mutexBarreraPasillo,mutexPasillo ,mutexGuarida,mutexCap;
   
	private Semaphore semNegro,semPequeno1,semPequeno2,semEsperaPorDragon;//barrera para que entren los dragones
    private Semaphore mutexEsperaPorDragon,mutexDragones,mutexColaNegro,mutexColaPequeno1,mutexColaPequeno2;//cola dragones
    
    Alchemist(int me,Random rnd,Semaphore barreraEntrada,Semaphore mutexBarreraEntrada,Semaphore mutexEsperaEntrada
    		,Semaphore semTotal,Semaphore semAntecamara, Semaphore semGrupo,Semaphore barreraPasillo,Semaphore semPermisoPasillo,Semaphore semPasillo,Semaphore semGuarida 
    		,Semaphore mutexAntecamara,Semaphore mutexGrupo,Semaphore mutexDireccion,Semaphore mutexBarreraPasillo,Semaphore mutexPasillo, Semaphore mutexGuarida,Semaphore mutexCap
    		,Semaphore semNegro,Semaphore semPequeno1,Semaphore semPequeno2,Semaphore semEsperaPorDragon
    		,Semaphore mutexEsperaPorDragon,Semaphore mutexDragones,Semaphore mutexColaNegro,Semaphore mutexColaPequeno1,Semaphore mutexColaPequeno2){
	        
    	this.me=me;
        this.rnd=rnd;
        this.barreraEntrada=barreraEntrada;
        this.mutexBarreraEntrada=mutexBarreraEntrada;
        this.mutexEsperaEntrada=mutexEsperaEntrada;
        
        
        this.semTotal=semTotal;
       	this.semAntecamara = semAntecamara;
   	    this.semGrupo = semGrupo;
       	this.semPermisoPasillo = semPermisoPasillo;
       	this.barreraPasillo= barreraPasillo;
       	this.semPasillo = semPasillo;
       	this.semGuarida = semGuarida;
       	
       	this.mutexAntecamara = mutexAntecamara;
       	this.mutexGrupo = mutexGrupo;
       	this.mutexDireccion = mutexDireccion;
       	this.mutexBarreraPasillo=mutexBarreraPasillo;
       	this.mutexPasillo = mutexPasillo;
       	this.mutexGuarida =mutexGuarida;
       	this.mutexCap=mutexCap;
       	
       	this.semNegro = semNegro;
       	this.semPequeno1 = semPequeno1;
       	this.semPequeno2 = semPequeno2;
       	this.semEsperaPorDragon=semEsperaPorDragon;
       	
       	this.mutexEsperaPorDragon=mutexEsperaPorDragon;
       	this.mutexDragones=mutexDragones;
       	this.mutexColaNegro = mutexColaNegro;
       	this.mutexColaPequeno1 = mutexColaPequeno1;
       	this.mutexColaPequeno2 = mutexColaPequeno2;
       	
    }


    private void antecamaraIn(){
    	try {mutexBarreraEntrada.acquire();} catch (Exception e) {}
        try {mutexAntecamara.acquire();} catch (Exception e) {}
        
        if(numAntecamara>=4) {
        	
        	try {mutexEsperaEntrada.acquire();} catch (Exception e) {}
        	mutexAntecamara.release();
        	esperoEntrada=true;
        	mutexEsperaEntrada.release();
        	try {barreraEntrada.acquire();} catch (Exception e) {}
        	  	
        }else {
        	mutexAntecamara.release();
        }
        
        mutexBarreraEntrada.release();
    	
    	
        try {semTotal.acquire();} catch (Exception e) {}   
        try {semAntecamara.acquire();} catch (Exception e) {}        
        try {mutexAntecamara.acquire();} catch (Exception e) {}
    	numAntecamara++;
    	System.out.println("[ "+ me +" ] I am inside ANTECAMARA FIRST time. There is "
    			   + numAntecamara  + " alchemists");
        mutexAntecamara.release();

    }
    
    private void hacerGrupo(){
    	
        try {semGrupo.acquire();} catch (Exception e) {}
        try {mutexGrupo.acquire();} catch (Exception e) {}
        numGrupo++;
        System.out.println("[ "+ me +" ] I am in a GROUP. We are "
 			   + numGrupo  + " waiting");
        
        if(numGrupo==3){
        	
            semPermisoPasillo.release(3);
            numGrupo=0;
        }

        mutexGrupo.release();
        try {semPermisoPasillo.acquire();} catch (Exception e) {}
    }//PROBLEMA DE GRUPO A PASILLO
    
    
    
    
    
    
    private void pasilloFromAntecamara(){
    	
        try {semGuarida.acquire();} catch (Exception e) {}
        try {mutexBarreraPasillo.acquire();} catch (Exception e) {}
        
        try {mutexPasillo.acquire();} catch (Exception e) {}

        if(numPasillo==0) {
        	
        	mutexPasillo.release();
            try {barreraPasillo.acquire();} catch (Exception e) {}
       
        }else {
        	
            mutexPasillo.release();
        	
        }
        
        mutexBarreraPasillo.release();
        
        try {mutexDireccion.acquire();} catch (Exception e) {}
      
        if(direccion!=1){
        	
            direccion=1;
        
        }
        
        mutexDireccion.release();
        
        try {mutexEsperaPorDragon.acquire();} catch (Exception e) {}
        try {mutexCap.acquire();} catch (Exception e) {}
        try {mutexGuarida.acquire();} catch (Exception e) {}
        try {mutexPasillo.acquire();} catch (Exception e) {}
        
        if((numGuarida+numPasillo)>=capGuarida) {
        	
        	mutexPasillo.release();
        	mutexGuarida.release();
        	mutexCap.release();
        	
            try {semEsperaPorDragon.acquire();} catch (Exception e) {}
  
           
            
        }else {
            mutexPasillo.release();
        	mutexGuarida.release();
        	mutexCap.release();
        }
 

    	mutexEsperaPorDragon.release();
                
        try {semPasillo.acquire();} catch (Exception e) {}
        try {mutexAntecamara.acquire();} catch (Exception e) {}
        numAntecamara--;
        mutexAntecamara.release();
        try {mutexPasillo.acquire();} catch (Exception e) {}
        
        numPasillo++;
        semGrupo.release();
    	System.out.println("[ "+ me +" ] I am inside PASILLO,FIRST time. There is "
 			   + numPasillo  + " alchemists");
    	semAntecamara.release();
        mutexPasillo.release();
    }
    
    
    
    
    
    private void guaridaIn(){
        
        try {mutexGuarida.acquire();} catch (Exception e) {}
        numGuarida++;
        try {mutexDragones.acquire();} catch (Exception e) {}
        try {mutexPasillo.acquire();} catch (Exception e) {}
        numPasillo--;

	        if(numPasillo==0){
	        	
	            try {mutexDireccion.acquire();} catch (Exception e) {} 
	            direccion=0;//ya no tiene direccion el pasillo
	            barreraPasillo.release();
	            mutexDireccion.release();
	            
	        }
	        
        semPasillo.release();
        mutexPasillo.release();
    	System.out.println("[ "+ me +" ] I am inside GUARIDA.  "
    			   + numGuarida  + " alchemists and "+ Dragon.numDragones+" dragons");
        
        mutexGuarida.release();
        mutexDragones.release();
        
    }
    
    
    private void pasilloFromGuarida(){
    	try {semAntecamara.acquire();} catch (Exception e) {}
    	
    	try {mutexBarreraPasillo.acquire();} catch (Exception e) {}
        try {mutexPasillo.acquire();} catch (Exception e) {}
        
        if(numPasillo==0) {
        	
        	mutexPasillo.release();
            try {barreraPasillo.acquire();} catch (Exception e) {}
       
        }else {
        	
            mutexPasillo.release();
        	
        }

        mutexBarreraPasillo.release();
        

        
        try {mutexDireccion.acquire();} catch (Exception e) {}
     
        if(direccion!=2){
        	
            direccion=2;
        
        }
        
        mutexDireccion.release();
        
        try {semPasillo.acquire();} catch (Exception e) {}
        try {mutexGuarida.acquire();} catch (Exception e) {}
        try {mutexCap.acquire();} catch (Exception e) {}
          
        numGuarida--;
        
        if(numGuarida<capGuarida) {
        	
        	if(numGuarida==0) {
        	
        		try {mutexColaNegro.acquire();} catch (Exception e) {}
        		
        		if(Dragon.colaNegro) {
        			
        			semNegro.release();
        			
        		}
        		
        		mutexColaNegro.release();
        	}else if(numGuarida==5) {
        	
        		try {mutexColaPequeno1.acquire();} catch (Exception e) {}
        		
        		if(Dragon.colaPequeno1) {
        			
        			semPequeno1.release();
        			
        		}
        		
        		mutexColaPequeno1.release();
        	
        	}else if(numGuarida==10) {
        	
        		try {mutexColaPequeno2.acquire();} catch (Exception e) {}
        		
        		if(Dragon.colaPequeno2) {
        			
        			semPequeno2.release();
        			
        		}
        		
        		mutexColaPequeno2.release();
        	}
        	      
        }
        mutexCap.release();
        mutexGuarida.release();
        try {mutexPasillo.acquire();} catch (Exception e) {}
        numPasillo++;
        
        
    	System.out.println("[ "+ me +" ] I am inside PASILLO,SECOND time. There is "
  			   + numPasillo  + " alchemists");
    	
    	semGuarida.release();
        mutexPasillo.release();    
    
    }
    
    
    
    
    
    
    
    private void antecamaraFromPasillo(){
    	
       try {mutexAntecamara.acquire();} catch (Exception e) {}
        numAntecamara++;
        try {mutexPasillo.acquire();} catch (Exception e) {}
        numPasillo--;
        
        if(numPasillo==0){
        	
            try {mutexDireccion.acquire();} catch (Exception e) {} 
            direccion=0;//ya no tiene direccion el pasillo
            barreraPasillo.release();
            mutexDireccion.release();
            
        }
        
        semPasillo.release();
        mutexPasillo.release();
    	System.out.println("[ "+ me +" ] I am inside ANTECAMARA, SECOND TIME. There is "
    			   + numAntecamara  + " alchemists");
    	mutexAntecamara.release(); 
    
    }
        
    
    
    
    private void antecamaraOut(){
    	
        try {mutexAntecamara.acquire();} catch (Exception e) {}
    	numAntecamara--;
    	
    	if(numAntecamara<4) {
    		
    		try {mutexEsperaEntrada.acquire();} catch (Exception e) {}
        	mutexAntecamara.release();
        	
        	if(esperoEntrada) {
        		
        		esperoEntrada=false;
        		mutexEsperaEntrada.release();
        		barreraEntrada.release();
        		
        	}else {
        		
        		mutexEsperaEntrada.release();
        	
        	}
        	        	
    	}
    	
    	mutexAntecamara.release();
    	semAntecamara.release();
        semTotal.release(); 
    	System.out.println("[ "+ me +" ] Outside the Dungeon");
    
    }

    public void run(){
    	
    	try {Thread.sleep(rnd.nextInt(1000));} catch (Exception e) {}
    	antecamaraIn();
    	
    	try {Thread.sleep(1000);} catch (Exception e1) {}
    	hacerGrupo();
    	
    	try {Thread.sleep(1000);} catch (Exception e1) {}
    	pasilloFromAntecamara();
    	
    	try {Thread.sleep(10000);} catch (Exception e1) {}
        guaridaIn();
        
    	try {Thread.sleep(rnd.nextInt(2000));} catch (Exception e2) {}
    	pasilloFromGuarida();
    	
    	try {Thread.sleep(1000);} catch (Exception e3) {}
    	antecamaraFromPasillo();
    	
    	try {Thread.sleep(rnd.nextInt(1000));} catch (Exception e4) {}
        antecamaraOut();
        
    }


}