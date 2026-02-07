/*
 * Copyright (C) 2014 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 */

/**
 * @file
 * @date 04 Dec, 2014
 * @version 1.0.0
 *
 * @brief XMC4500 Relax kit GPIO toggle example
 *
 * GPIO toggle example flashes the leds of the board with a periodic rate.
 * LED1 is connected to P1.1
 * LED2 is connected to P1.0
 *
 * History <br>
 *
 * Version 1.0.0 Initial <br>
 *
 */


#include <xmc_gpio.h>


//---------------------------------CLOCK CONFIG--------------------------------------------------------------------------

#define TICKS_PER_SECOND 1000
#define REST 5000               // REST AFTER EACH TIME WE SEND THE MSG
#define DOT 100                 //  "" IN MORSE,  ALSO SPACE BETWEEN SIGNS THAT FORM THE SAME LETTER
#define DASH 300                //  "-" IN MORSE, ALSO SPACE BETWEEN LETTERS
#define SLASH 700               //  "/" IN MORSE, SPACE BETEEN WORDS

//---------------------------------GPIO CONFIG---------------------------------------------------------------------------
#define GPIO_LED2     XMC_GPIO_PORT1,  0
#define GPIO_LED1     XMC_GPIO_PORT1,  1
#define GPIO_BUTTON1  XMC_GPIO_PORT1, 14
#define GPIO_BUTTON2  XMC_GPIO_PORT1, 15


//---------------------------------CLOCK CONFIG--------------------------------------------------------------------------
static char button_1_flag=0;
static char button_2_flag=0;
volatile uint32_t ticks = 0;
static uint32_t b1_time1 = 0;
static uint32_t b1_time2 = 0;
static int cnt=0; 


void delay_ms(uint32_t delay){
    delay= delay+ticks;
    while(ticks<=delay){
        
    }
}


void display_msg(void){
  //"I" = ".."
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
 delay_ms(DOT);  
  XMC_GPIO_ToggleOutput(GPIO_LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//3
  delay_ms(DOT);
  //"/" 
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(SLASH);
  //"C" = "-.-."
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//3
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//4
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//5
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//6
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//7
  delay_ms(DOT);
  //" " = "-"
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DASH);
  //"A" = ".-"
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//3
  delay_ms(DASH);
  //" " = "-"
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DASH);
  //"N" = "-."
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//3
  delay_ms(DOT);
  //"/"
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(SLASH);
  //"M" = "--"
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//3
  delay_ms(DASH);
  //" " = "-"
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DASH);
  //"O" ="---"
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//3
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//4
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//5
  delay_ms(DASH);
  //" " = "-"
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DASH);
  //"R" = ".-."
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//3
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//4
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//5
  delay_ms(DOT);
  //" " = "-"
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DASH);
  //"S" = "..."
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DOT);  
  XMC_GPIO_ToggleOutput(GPIO_LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//3
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//4
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(GPIO_LED1);//5
  delay_ms(DOT);
  //" " = "-"
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DASH);
  // "E" = "."
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(DOT);  
  //"END"
  XMC_GPIO_ToggleOutput(GPIO_LED1);//1
  delay_ms(REST);
  
}





void display_number(uint32_t number){
    
    switch(number) {
  
  case 0:  // "-----"
      XMC_GPIO_ToggleOutput(GPIO_LED1);//1
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//2
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//3
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//4
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//5
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//TIME TO WAIT BETWEEN LETTERS/DIFFERENT NUMBERS
      delay_ms(DASH);     
    // code block
    break;
  
  case 1:   //".----"
      XMC_GPIO_ToggleOutput(GPIO_LED1);//1
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//2
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//3
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//4
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//5
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//TIME TO WAIT BETWEEN LETTERS/DIFFERENT NUMBERS
      delay_ms(DASH);
    // code block
    break;
  
  case 2:   //"..---"
      XMC_GPIO_ToggleOutput(GPIO_LED1);//1
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//2
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//3
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//4
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//5
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//TIME TO WAIT BETWEEN LETTERS/DIFFERENT NUMBERS
      delay_ms(DASH);
    // code block
    break;
  
  case 3:   //"...--"
      XMC_GPIO_ToggleOutput(GPIO_LED1);//1
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//2
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//3
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//4
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//5
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//TIME TO WAIT BETWEEN LETTERS/DIFFERENT NUMBERS
      delay_ms(DASH);
    // code block
    break;
  
  case 4: //"....-"
      XMC_GPIO_ToggleOutput(GPIO_LED1);//1
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//2
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//3
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//4
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//5
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//TIME TO WAIT BETWEEN LETTERS/DIFFERENT NUMBERS
      delay_ms(DASH);
    // code block
    break;
  
  case 5:   //"....."
      XMC_GPIO_ToggleOutput(GPIO_LED1);//1
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//2
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//3
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//4
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//5
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//TIME TO WAIT BETWEEN LETTERS/DIFFERENT NUMBERS
      delay_ms(DASH);
    // code block
    break;
  
  case 6:   //"-...."
      XMC_GPIO_ToggleOutput(GPIO_LED1);//1
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//2
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//3
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//4
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//5
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//TIME TO WAIT BETWEEN LETTERS/DIFFERENT NUMBERS
      delay_ms(DASH);
    // code block
    break;
  
  case 7:   //"--..."
      XMC_GPIO_ToggleOutput(GPIO_LED1);//1
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//2
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//3
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//4
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//5
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//TIME TO WAIT BETWEEN LETTERS/DIFFERENT NUMBERS
      delay_ms(DASH);
    // code block
    break;
  
  case 8:   //"---.."
      XMC_GPIO_ToggleOutput(GPIO_LED1);//1
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//2
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//3
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//4
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//5
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//TIME TO WAIT BETWEEN LETTERS/DIFFERENT NUMBERS
      delay_ms(DASH);
    // code block
    break;
  
  case 9: //"----."
      XMC_GPIO_ToggleOutput(GPIO_LED1);//1
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//2
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//3
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//4
      delay_ms(DASH);
      XMC_GPIO_ToggleOutput(GPIO_LED1);
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//5
      delay_ms(DOT);
      XMC_GPIO_ToggleOutput(GPIO_LED1);//TIME TO WAIT BETWEEN LETTERS/DIFFERENT NUMBERS
      delay_ms(DASH);
    // code block
    break;   
  default:
    // code block
    break;
}
    
}


void SysTick_Handler(void)
{
  ticks++;
  /*if (ticks == limit){
    XMC_GPIO_ToggleOutput(LED1);
    ticks = 0;
    
  }*/
  
}
/*
2.1 A dash is equal to three dots.
2.2 The space between the signals forming the same letter is equal to one dot.
2.3 The space between two letters is equal to three dots.
2.4 The space between two words is equal to seven dots*/

/*
"I CAN MORSE"
 .. / -.-. .- -. / -- --- .-. ... .
 3 DOTS 1/
 I
 ..
 C          A           N
 -.-.       .-          -.
 M          O           R           S           E
 --         ---         .-.         ...         .
 */
 


//---------------------------------GPIO CONFIG---------------------------------------------------------------------------

const XMC_GPIO_CONFIG_t out_config = \
      {.mode=XMC_GPIO_MODE_OUTPUT_PUSH_PULL,\
       .output_level=XMC_GPIO_OUTPUT_LEVEL_LOW,\
       .output_strength=XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE};
const XMC_GPIO_CONFIG_t in_config = \
      {.mode=XMC_GPIO_MODE_INPUT_TRISTATE,\
       .output_level=XMC_GPIO_OUTPUT_LEVEL_LOW,\
       .output_strength=XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE};

       
int main(void)
{
  /*GPIO CONFIG IN VOID*/
  XMC_GPIO_Init(GPIO_LED1,     &out_config);
  XMC_GPIO_Init(GPIO_LED2,     &out_config);
  XMC_GPIO_Init(GPIO_BUTTON1,  &in_config);
  XMC_GPIO_Init(GPIO_BUTTON2,  &in_config);
  /* System timer configuration */
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  char flag=0;
  uint32_t i=0;
  uint32_t diff=0;
  uint32_t aux=0;
  
  while (1) {

    while(XMC_GPIO_GetInput(GPIO_BUTTON1) == 0) {//BUTTON 1 IS PRESSED AND LOCKS OUT BUTTON 2 UNTIL RELEASED
        if(button_1_flag==0){//ONLY DOES ONCE, WHEN PRESSED DOWN
            b1_time1=b1_time2;
            b1_time2=ticks;
            cnt++;
            display_msg();//CALL "I CAN MORSE" FUNCTION        
            
        }
      button_1_flag=1;      
    }
    button_1_flag=0;
    
    while(XMC_GPIO_GetInput(GPIO_BUTTON2) == 0) {//BUTTON 2 IS PRESSED AND LOCKS OUT BUTTON 1 UNTIL RELEASED
        if(button_2_flag==0){//ONLY DOES ONCE, WHEN PRESSED DOWN
            if(cnt==0){
                display_number(0);//FUNCTION TO SEND "0"
            }else{
                //FUNCTION (b1_time2-b1_time1)
                diff=b1_time2-b1_time1;
                i=100000000;
                flag=0;
                while(i>0){
		        aux=diff/i;
		        
		        if(aux==0){
		        	if(flag==1){
		          		display_number(0);
		          	}
		        }else{
		        	flag=1;
		        	display_number(aux);
		        }              
		        	diff= diff - (aux*i);
		        	i=i/10;
                }
                                
            }
            
        }
        button_2_flag=1;
    }
    button_2_flag=0;
      
}






  return 0;
}
