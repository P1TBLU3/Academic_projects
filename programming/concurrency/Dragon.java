
import java.util.*;
import java.util.concurrent.Semaphore;

public class Dragon extends Thread{
	
	protected  static boolean colaNegro,colaPequeno1,colaPequeno2;
	private Semaphore mutexColaNegro,mutexColaPequeno1,mutexColaPequeno2;
	
	private Semaphore semNegro,semPequeno1,semPequeno2;//barrera para que entren
	
	protected boolean dentroNegro,dentroPequeno1,dentroPequeno2;//autoinicializados a false
	private Semaphore mutexDentroNegro,mutexDentroPequeno1,mutexDentroPequeno2;
	
	private Random rnd;
	private String name;
	private int iteraciones;//numero de veces que cada dragon hace su ciclo
	
	private Semaphore semEsperaPorDragon;//barrera para los Alquimistas
	protected static int numDragones;
	private Semaphore mutexDragones,mutexDireccion,mutexPasillo,mutexGuarida,mutexCap;
	

	
	
	
	public Dragon(Random rnd,String name,int iteraciones,Semaphore mutexColaNegro,Semaphore mutexColaPequeno1,Semaphore mutexColaPequeno2,Semaphore semNegro,Semaphore semPequeno1,Semaphore semPequeno2
			, Semaphore mutexDentroNegro,Semaphore mutexDentroPequeno1,Semaphore mutexDentroPequeno2,Semaphore semEsperaPorDragon
			,Semaphore mutexDragones,Semaphore mutexDireccion,Semaphore mutexPasillo, Semaphore mutexGuarida,Semaphore mutexCap) {

		this.rnd=rnd;
		this.name=name;
		this.iteraciones=iteraciones;
		this.mutexColaNegro=mutexColaNegro;
		this.mutexColaPequeno1=mutexColaPequeno1;
		this.mutexColaPequeno2=mutexColaPequeno2;
		this.semNegro=semNegro;
		this.semPequeno1=semPequeno1;
		this.semPequeno2=semPequeno2;
		this.mutexDentroNegro=mutexDentroNegro;
		this.mutexDentroPequeno1=mutexDentroPequeno1;
		this.mutexDentroPequeno2=mutexDentroPequeno2;
		this.semEsperaPorDragon=semEsperaPorDragon;
		this.mutexDragones=mutexDragones;
		this.mutexDireccion=mutexDireccion;
		this.mutexPasillo=mutexPasillo;
		this.mutexGuarida=mutexGuarida;
		this.mutexCap=mutexCap;
				
	}
	
	
	public void GuaridaIn() {
		if(name.equals("Drogon")) {
			
			try {mutexDireccion.acquire();} catch (Exception e) {}
			try {mutexPasillo.acquire();} catch (Exception e) {}
	    	try {mutexGuarida.acquire();} catch (Exception e) {}
	    	
	    	if(Alchemist.direccion==2) {
	    		
	    		try {mutexColaNegro.acquire();} catch (Exception e) {}
	    		
	    		if(Alchemist.numGuarida>0) {//Se pone a esperar
		    		
		    		colaNegro=true;
		    		
		    	}
		    	mutexGuarida.release();
		    	mutexPasillo.release();
		    	mutexDireccion.release();
		    	
		    	if(colaNegro) {
	    			
	    			mutexColaNegro.release();
	    			try {semNegro.acquire();} catch (Exception e) {}
	    			try {mutexColaNegro.acquire();} catch (Exception e) {}
	    		
	    		}
		    	
	    		colaNegro=false;
	    		mutexColaNegro.release();
		    	try {mutexCap.acquire();} catch (Exception e) {}
		    	try {mutexDragones.acquire();} catch (Exception e) {}	    	
		    	try {mutexDentroNegro.acquire();} catch (Exception e) {}
		    	Alchemist.capGuarida=0;
		    	numDragones++;
		    	dentroNegro=true;
		    	mutexDentroNegro.release();
		    	mutexDragones.release();
		    	mutexCap.release();
	    		
	    	}else {
	    		
	    		try {mutexColaNegro.acquire();} catch (Exception e) {}

	    		if((Alchemist.numGuarida+Alchemist.numPasillo)>0) {//Se pone a esperar
		    		
		    		colaNegro=true;
		    		
		    	}
		    	
		    	mutexGuarida.release();
		    	mutexPasillo.release();
		    	mutexDireccion.release();
		    	
		    	if(colaNegro) {
	    			
	    			mutexColaNegro.release();
	    			System.out.println("["+name+"]: Waiting to enter");
	    			try {semNegro.acquire();} catch (Exception e) {}
	    			try {mutexColaNegro.acquire();} catch (Exception e) {}
	    		
	    		}
		    	
	    		colaNegro=false;
	    		mutexColaNegro.release();
		    	try {mutexCap.acquire();} catch (Exception e) {}
		    	try {mutexDragones.acquire();} catch (Exception e) {}	    	
		    	try {mutexDentroNegro.acquire();} catch (Exception e) {}
		    	Alchemist.capGuarida=0;
		    	numDragones++;
		    	dentroNegro=true;
		    	mutexDentroNegro.release();
		    	mutexDragones.release();
		    	mutexCap.release();
	    	}
	
	    	
		}else {//Dragones pequenos
		
		/////////////////////////////////////////////////////////////	
	    
	    	try {mutexDentroNegro.acquire();} catch (Exception e) {}
	    	try {mutexDragones.acquire();} catch (Exception e) {}
	    	if(dentroNegro) {//ENTRAN SIN ESPERAR
		    	
	    		if(numDragones==1) {//Grande solo
		    		
		    		try {mutexDentroPequeno1.acquire();} catch (Exception e) {}
		    		dentroPequeno1=true;
		    		numDragones++;
		    		mutexDentroPequeno1.release();
		    	
		    	}else {//Grande y 1 pequeno
		    	
		    		try {mutexDentroPequeno2.acquire();} catch (Exception e) {}
		    		dentroPequeno2=true;
		    		numDragones++;
		    		mutexDentroPequeno2.release();
		    	
		    	}
		    	
	    		mutexDentroNegro.release();
		    		
	    	}else {//Revisan si hay que esperar
	    		
	    		mutexDentroNegro.release();
	    		
	    		if(numDragones==0) {// ningun dragon
	    			
	    			try {mutexDireccion.acquire();} catch (Exception e) {}
	    			try {mutexPasillo.acquire();} catch (Exception e) {}
	    	    	try {mutexGuarida.acquire();} catch (Exception e) {}
	    			
	    			if(Alchemist.direccion==2) {
	    				
	    				try {mutexColaPequeno1.acquire();} catch (Exception e) {}
	    	    		
	    	    		if(Alchemist.numGuarida>10) {//Se pone a esperar
	    		    		
	    	    			colaPequeno1=true;
	    		    		
	    		    	}
	    		    	
	    		    	mutexGuarida.release();
	    		    	mutexPasillo.release();
	    		    	mutexDireccion.release();
	    	    		
	    		    	if(colaPequeno1) {
	    	    			
	    		    		mutexColaPequeno1.release();
	    		    		System.out.println("["+name+"]: Waiting to enter");
	    	    			try {semPequeno1.acquire();} catch (Exception e) {}
	    	    			try {mutexColaPequeno1.acquire();} catch (Exception e) {}
	    	    		
	    	    		}
	    		    	
	    		    	colaPequeno1=false;
	    		    	mutexColaPequeno1.release();
	    		    	try {mutexCap.acquire();} catch (Exception e) {}
	    		    	try {mutexDentroPequeno1.acquire();} catch (Exception e) {}
	    		    	Alchemist.capGuarida=10;
	    		    	numDragones++;
	    		    	dentroPequeno1=true;
	    		    	mutexDentroPequeno1.release();
	    		    	mutexCap.release();
	    				
	    			}else {//los alquimistas del pasillo van hacia la guarida

	    				try {mutexColaPequeno1.acquire();} catch (Exception e) {}
	    	    		
	    	    		if((Alchemist.numGuarida+Alchemist.numPasillo)>10) {//Se pone a esperar
	    		    		
	    	    			colaPequeno1=true;
	    		    		
	    		    	}
	    		    	
	    		    	mutexGuarida.release();
	    		    	mutexPasillo.release();
	    		    	mutexDireccion.release();
	    	    		
	    		    	if(colaPequeno1) {
	    	    			
	    		    		mutexColaPequeno1.release();
	    		    		System.out.println("["+name+"]: Waiting to enter");
	    	    			try {semPequeno1.acquire();} catch (Exception e) {}
	    	    			try {mutexColaPequeno1.acquire();} catch (Exception e) {}
	    	    		
	    	    		}
	    		    	
	    		    	colaPequeno1=false;
	    		    	mutexColaPequeno1.release();
	    		    	try {mutexCap.acquire();} catch (Exception e) {}
	    		    	try {mutexDentroPequeno1.acquire();} catch (Exception e) {}
	    		    	Alchemist.capGuarida=10;
	    		    	numDragones++;
	    		    	dentroPequeno1=true;
	    		    	mutexDentroPequeno1.release();
	    		    	mutexCap.release();
	    			}
	    			
		    	}else {//1 peque
		    		
					try {mutexDireccion.acquire();} catch (Exception e) {}
					try {mutexPasillo.acquire();} catch (Exception e) {}
			    	try {mutexGuarida.acquire();} catch (Exception e) {}
		    		
		    		if(Alchemist.direccion==2) {
		    			
		    			try {mutexColaPequeno2.acquire();} catch (Exception e) {}
	    	    		
	    	    		if(Alchemist.numGuarida>5) {//Se pone a esperar
	    		    		
	    	    			colaPequeno2=true;
	    		    		
	    		    	}
	    		    	
	    		    	mutexGuarida.release();
	    		    	mutexPasillo.release();
	    		    	mutexDireccion.release();
	    	    		
	    		    	if(colaPequeno2) {
	    	    			
	    		    		mutexColaPequeno2.release();
	    		    		System.out.println("["+name+"]: Waiting to enter");
	    	    			try {semPequeno2.acquire();} catch (Exception e) {}
	    	    			try {mutexColaPequeno2.acquire();} catch (Exception e) {}
	    	    		
	    	    		}
	    		    	
	    		    	colaPequeno2=false;
	    		    	mutexColaPequeno2.release();
	    		    	try {mutexCap.acquire();} catch (Exception e) {}
	    		    	try {mutexDentroPequeno2.acquire();} catch (Exception e) {}
	    		    	Alchemist.capGuarida=5;
	    		    	numDragones++;
	    		    	dentroPequeno2=true;
	    		    	mutexDentroPequeno2.release();
	    		    	mutexCap.release();
		    			
		    		}else {
		    	    	
		    			try {mutexColaPequeno2.acquire();} catch (Exception e) {}
	    	    		
	    	    		if((Alchemist.numGuarida+Alchemist.numPasillo)>5) {//Se pone a esperar
	    		    		
	    	    			colaPequeno2=true;
	    		    		
	    		    	}
	    		    	
	    		    	mutexGuarida.release();
	    		    	mutexPasillo.release();
	    		    	mutexDireccion.release();
	    	    		
	    		    	if(colaPequeno2) {
	    	    			
	    		    		mutexColaPequeno2.release();
	    		    		System.out.println("["+name+"]: Waiting to enter");
	    	    			try {semPequeno2.acquire();} catch (Exception e) {}
	    	    			try {mutexColaPequeno2.acquire();} catch (Exception e) {}
	    	    		
	    	    		}
	    		    	
	    		    	colaPequeno2=false;
	    		    	mutexColaPequeno2.release();
	    		    	try {mutexCap.acquire();} catch (Exception e) {}
	    		    	try {mutexDentroPequeno2.acquire();} catch (Exception e) {}
	    		    	Alchemist.capGuarida=5;
	    		    	numDragones++;
	    		    	dentroPequeno2=true;
	    		    	mutexDentroPequeno2.release();
	    		    	mutexCap.release();
		    			
		    		}

		    	}
	    			
	    	}
	    	
		mutexDragones.release();
		    
		}
		
	
	}
	
	
	
	
	
	public void GuaridaOut() {
    	try {mutexDragones.acquire();} catch (Exception e) {}
    	try {mutexCap.acquire();} catch (Exception e) {}
		if(name.equals("Drogon")) {//grande
			 
	    	try {mutexDentroNegro.acquire();} catch (Exception e) {}
	    	dentroNegro=false;
	    	mutexDentroNegro.release();
			numDragones--;
			
			if(numDragones==0) {
				
				Alchemist.capGuarida=25;//mayor que la capacidad maxima 
				
			}else if(numDragones==1) {//hay un peque
				
				Alchemist.capGuarida=10;
				
			}else {//hay 2 peques
				
				Alchemist.capGuarida=5;
				
			}
			
		}else {
			try {mutexDentroNegro.acquire();} catch (Exception e) {}

	    	
			numDragones--;
			
			if(numDragones==0) {
				
				try {mutexDentroPequeno1.acquire();} catch (Exception e) {}
				Alchemist.capGuarida=25;//mayor que la capacidad maxima 
				dentroPequeno1=false;
				mutexDentroPequeno1.release();
				
			}else if(numDragones==1) {//solo hay un dragon
				
				if(dentroNegro) {//esta el grande
					
					try {mutexDentroPequeno1.acquire();} catch (Exception e) {}
					dentroPequeno1=false;
					mutexDentroPequeno1.release();
					
				}else {
					
					try {mutexDentroPequeno2.acquire();} catch (Exception e) {}
					Alchemist.capGuarida=10;
					dentroPequeno2=false;
					mutexDentroPequeno2.release();
				}
				
			}else {
				
				try {mutexDentroPequeno2.acquire();} catch (Exception e) {}
				dentroPequeno2=false;
				mutexDentroPequeno2.release();
				
			}

			mutexDentroNegro.release();
		}
		semEsperaPorDragon.release();
		mutexDragones.release();
		mutexCap.release();
		

	}
	
	
	
	
	 public void run(){System.out.println(name);
		 
		 for (int i = 0; i < iteraciones; i++) {
			 
			 try {Thread.sleep(rnd.nextInt(1000));} catch (Exception e) {}
		    	
			    GuaridaIn();
			   try {mutexDragones.acquire();} catch (Exception e) {}
			    try {mutexGuarida.acquire();} catch (Exception e) {}
			    
			    
		    	System.out.println("[ "+ name +" ] I am inside GUARIDA.  "
		 			   + Alchemist.numGuarida  + " alchemists and "+ numDragones+" dragons");
			    
		    	
		    	mutexGuarida.release();
		    	mutexDragones.release();
		    	
		    	try {Thread.sleep(rnd.nextInt(2000));} catch (Exception e) {}
			    GuaridaOut();
			    System.out.println("["+name+"]: Outside the Dungeon.");
			    try {Thread.sleep(rnd.nextInt(1000));} catch (Exception e) {}
			    
			    
		 }
		 
	 }
	
	 
	 
	 
	 
	 
}
