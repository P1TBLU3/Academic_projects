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

#define TICKS_PER_SECOND 1000
#define REST 5000               // REST AFTER EACH TIME WE SEND THE MSG
#define DOT 100                 //  "" IN MORSE,  ALSO SPACE BETWEEN SIGNS THAT FORM THE SAME LETTER
#define DASH 300                //  "-" IN MORSE, ALSO SPACE BETWEEN LETTERS
#define SLASH 700               //  "/" IN MORSE, SPACE BETEEN WORDS


#define LED1 P1_1
#define LED2 P1_0

 volatile uint32_t ticks = 0;
void SysTick_Handler(void){

  ticks++;
  
  
  }

void delay_ms(uint32_t delay){
    uint32_t aux= delay+ticks;
    while(ticks<=aux){
 
    }
}  

/*





*/

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


int main(void)
{
  XMC_GPIO_CONFIG_t config;

  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;

  XMC_GPIO_Init(LED1, &config);
/*
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  XMC_GPIO_Init(LED2, &config);
*/
  /* System timer configuration */
  SysTick_Config(SystemCoreClock / TICKS_PER_SECOND);

  while(1)
  {
  
  //"I" = ".."
  XMC_GPIO_ToggleOutput(LED1);//1
 delay_ms(DOT);  
  XMC_GPIO_ToggleOutput(LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//3
  delay_ms(DOT);
  //"/" 
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(SLASH);
  //"C" = "-.-."
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//3
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//4
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//5
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(LED1);//6
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//7
  delay_ms(DOT);
  //" " = "-"
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DASH);
  //"A" = ".-"
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//3
  delay_ms(DASH);
  //" " = "-"
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DASH);
  //"N" = "-."
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//3
  delay_ms(DOT);
  //"/"
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(SLASH);
  //"M" = "--"
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//3
  delay_ms(DASH);
  //" " = "-"
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DASH);
  //"O" ="---"
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//3
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(LED1);//4
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//5
  delay_ms(DASH);
  //" " = "-"
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DASH);
  ticks=0;
  //"R" = ".-."
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//3
  delay_ms(DASH);
  XMC_GPIO_ToggleOutput(LED1);//4
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//5
  delay_ms(DOT);
  //" " = "-"
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DASH);
  //"S" = "..."
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DOT);  
  XMC_GPIO_ToggleOutput(LED1);//2
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//3
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//4
  delay_ms(DOT);
  XMC_GPIO_ToggleOutput(LED1);//5
  delay_ms(DOT);
  //" " = "-"
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DASH);
  // "E" = "."
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(DOT);  
  //"END"
  XMC_GPIO_ToggleOutput(LED1);//1
  delay_ms(REST); 
  ticks=0;
  //TO AVOID "ticks" OVERFLOW
  
  
	  
  
  
    /* Infinite loop */
  }
}
