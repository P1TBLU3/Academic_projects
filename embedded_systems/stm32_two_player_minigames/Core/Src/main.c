/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include "stm32l152c_discovery.h"
#include "stm32l152c_discovery_glass_lcd.h"
#include "string.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

LCD_HandleTypeDef hlcd;

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
/*short botUser = 0;
 short juego = 1;
 short pulsacion = 0;
 int espera_cuenta_atras = 2;
 short pulsacion_j1 = 0; //Para el juego 2
 short pulsacion_j2 = 0; //Para el juego 2
 int ganador = 0;
 int tiempo_espera = 0;
 short reinicio = 0;

 */

unsigned char cadena[6];
//PARA ANTES DE ELEGIR JUEGO
short juego = 1;
short reinicio = 0;

//JUGADORES
short jugador1 = 0; //DICE SI EL JUGADOR 1 LE HA DADO AL BOTON
short jugador2 = 0; //DICE SI EL JUGADOR 2 LE HA DADO AL BOTON
int tiempo1; //TIEMPO DEL JUGADOR 1
int tiempo2; //TIEMPO DEL JUGADOR 2
int prueba = 12345;
short ganador = 0; //DICE QUIEN HA GANADO

//EXCLUSIVO DEL JUEGO 2
short limite_pantalla = 30; //EST�? PUESTO A 15 SEGUNDOS PARA QUE CUANDO LOS SOBREPASE SE TERMINE EL JUEGO 2
short limite_rnd = 10; //POR DEFAULT LO PONEMOS
short signo = 0;
int num_ant = 0;
int num = 0;
int potenciometro = 0;
short escalado = 0;
int tiempo_total = 0;
short DC = 1;
short melodia = 0;
//Una vez haya acabado el juego para reiniciar
short juego_acabado = 0;

//PARA LIMITAR EL PASO DEL PROGRAMA

short contador_espera = 0;
short espera = 0;
short limite = 6;
short paso = 0; //Va a actuar como barrera para limitar el paso del programa
int tiempo_excedido = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
static void MX_LCD_Init(void);
static void MX_TS_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
/*void EXTI9_5_IRQHandler(void) { // El PC salta aquí en cuanto se produzca la EXTI2
 if (botUser == 0) {
 botUser = 1;
 } else if (botUser == 1) {
 botUser = 0;
 }
 EXTI->PR |= 0x0080; // Borro el flag
 }
 */

void Bin2Ascii(short numero, unsigned char *cadena) {
	uint8_t ind;
	uint32_t div = 10000, resto = numero;

	for (ind = 1; ind < 6; ind++) {
		cadena[ind] = resto / div + '0';
		resto = numero % div;
		div = div / 10;
	}

}

void TIM4_IRQHandler(void) {
	if ((TIM4->SR & 0x0004) != 0) {
		tiempo1 = TIM4->CCR2;
		jugador1 = 1;

	} else if ((TIM4->SR & 0x0002) != 0) {
		tiempo2 = TIM4->CCR1;
		jugador2 = 1;
	}
	TIM4->SR = 0x0000;
}

void TIM3_IRQHandler(void) {
	if ((TIM3->SR & 0x0002) != 0) {
		contador_espera++;
		if (contador_espera == limite) {
			espera++;
		}
		TIM3->CNT = 0;
	}
	// TIM3->CCR1 += tiempo; // Actualizo el valor de la comparación incrementándolo en
	// 1000 pasos = 1 segundo

	TIM3->SR = 0x0000; // Limpio los flags del contador
}

void EXTI0_IRQHandler(void) { // El PC salta aquí en cuanto se produzca la EXTI0
	reinicio = 1;
	EXTI->PR = 0x0001; // Borro el flag
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_ADC_Init();
	MX_LCD_Init();
	MX_TS_Init();
	MX_TIM2_Init();
	MX_TIM3_Init();
	MX_TIM4_Init();

	BSP_LCD_GLASS_Init();
	BSP_LCD_GLASS_BarLevelConfig(0);
	BSP_LCD_GLASS_Clear();
	/* USER CODE BEGIN 2 */
	//LED VERDE
	GPIOA->MODER &= ~(1 << (12 * 2 + 1));
	GPIOA->MODER |= (1 << (12 * 2));
	GPIOA->OTYPER &= ~(1 << 12);
	GPIOA->OSPEEDR &= ~(1 << (12 * 2 + 1));
	GPIOA->OSPEEDR &= ~(1 << (12 * 2));

	//LED AMARILLO
	GPIOD->MODER &= ~(1 << (2 * 2 + 1));
	GPIOD->MODER |= (1 << (2 * 2));
	GPIOD->OTYPER &= ~(1 << 2);
	GPIOD->OSPEEDR &= ~(1 << (2 * 2 + 1));
	GPIOD->OSPEEDR &= ~(1 << (2 * 2));
	//REGISTROS BOTON USER
	SYSCFG->EXTICR[0] &= ~((1 << (4 * 0 + 0)) | (1 << (4 * 0 + 1))
			| (1 << (4 * 0 + 2)) | (1 << (4 * 0 + 3))); //Exti_0 GPIOA_0
	GPIOA->PUPDR |= (1 << (2 * 0 + 1));
	GPIOA->PUPDR &= ~(1 << (2 * 0)); //Configura Pull_UP
	EXTI->FTSR |= (1 << 0); //Habilita flanco de subida
	EXTI->RTSR &= ~(1 << 0); //Deshabilita flanco bajada
	EXTI->IMR |= (1 << 0); //desenmascara exti_0
	NVIC->ISER[0] |= (1 << 6); //Habilita IRQ de exti0

	//REGISTROS BOTON 1   PB6 COMO ENTRADA DE TIM4 CH1
	GPIOB->MODER |= (1 << (2 * 6 + 1));
	GPIOB->MODER &= ~(1 << (2 * 6));
	//GPIOB->6 Funcion alternativa PARA TIMER
	GPIOB->AFR[0] &=
			~((1 << (4 * 6)) | (1 << (4 * 6 + 2)) | (1 << (4 * 6 + 3)));
	GPIOB->AFR[0] |= (1 << (4 * 6 + 1));
	//Funcion alternativa de GPIOx->Puerto_6  ES PARA TIMER 4 ch1
	GPIOB->PUPDR |= (1 << (2 * 6));
	GPIOB->PUPDR &= ~(1 << (2 * 6 + 1));
	//Boton 1 a Pull_UP (PB6)

	//REGISTROS PB7 COMO FUNCION ALTERNATIVA
	GPIOB->MODER &= ~(1 << (7 * 2));
	GPIOB->MODER |= (1 << (7 * 2 + 1));
	GPIOB->AFR[0] |= (1 << ((7 * 4) + 1));
	GPIOB->AFR[0] &= ~((1 << (7 * 4)) | (1 << ((7 * 4) + 2))
			| (1 << ((7 * 4) + 3)));
	GPIOB->PUPDR |= (1 << (2 * 7));
	GPIOB->PUPDR &= ~(1 << (2 * 7 + 1));
	//HITO 1
	/*SYSCFG->EXTICR[1] &= ~((1 << (4 * 3 + 1)) | (1 << (4 * 3 + 2))| (1 << (4 * 3 + 3)));
	 SYSCFG->EXTICR[1] |= (1 << (4 * 3 + 0));
	 EXTI->FTSR |= (1 << 7);
	 EXTI->RTSR &= ~(1 << 7);
	 EXTI->IMR |= (1 << 7);*/

	TIM4->CR1 = 0;
	TIM4->CR2 = 0;
	TIM4->SMCR = 0; //SIEMPRE A 0

	//PONEMOS EL COMPARE MODE REGISTER A TIC 01
	TIM4->CCMR1 |= 0x0101;

	//PONEMOS EL ENABLE REGISTER A FLANCO DE BAJADA 0 1
	TIM4->CCER |= (1 << (4 * 0 + 1)); //BIT CC1P A 1
	TIM4->CCER &= ~(1 << (4 * 0 + 3)); //BIT CC1NP A 0
	TIM4->CCER |= (1 << (4 * 1 + 1)); //BIT CC2P A 1
	TIM4->CCER &= ~(1 << (4 * 1 + 3)); //BIT CC2NP A 0

	TIM4->CCER |= (1 << (4 * 0)); //OUTPUT ENABLE A 1 (canal 1)
	TIM4->CCER |= (1 << (4 * 1)); //OUTPUT ENABLE A 1 (canal 2)

	TIM4->CNT = 0; //INICIALIZAMOS CONTADOR A 0
	TIM4->PSC = 32000; //PREESCALADO 32000 ->1 TIK = 1000 PASOS POR SEGUNDO
	TIM4->ARR = 0xFFFF; //Valor maxijmo para ARR ->el ciclo del timer son xxx segundos
	TIM4->EGR |= 0x0001;

	TIM4->DIER = 0x0006;
	TIM4->SR = 0x00;
	NVIC->ISER[0] |= (1 << 30); //hABILITA LA INTERRUPCIÓN POR toc DEL TIMER 4
	TIM4->CR1 |= 0x01; //Arranca el timer

	TIM3->CR1 = 0x0000; // ARPE = 0 -> No es PWM, es TOC
	// CEN = 0; Contador apagado
	TIM3->CR2 = 0x0000; // Siempre "0" en este curso
	TIM3->SMCR = 0x0000;
	TIM3->PSC = 32000; // Preescalado = 32000 -> Frecuencia del contador = 32000000/32000
	// = 1000 pasos por segundo
	TIM3->CNT = 0; // Inicializo el valor del contador a cero
	TIM3->ARR = 0xFFFF; // Valor recomendado = FFFF
	TIM3->CCR1 = 500; // Registro donde se guarda el valor que marca la comparación existosa
	// en TOC.
	// Lo inicializo al valor que quiero llegar = 1000 pasos = 1 sg
	TIM3->DIER = 0x0002;	//DESENMASCARAMOS INTERRRUPCIONES CANAL 1 TIMER 3
	// Modo de salida del contador
	TIM3->CCMR1 = 0x0000; // CCyS = 0 (TOC)
	// OCyM = 000 (no hay salida por el pin HW asociado al TIM4)
	// OCyPE = 0 (sin precarga)
	TIM3->CCER = 0x0000; // CCyP = 0 (siempre en TOC)
	// CCyE = 0 (desactivada la salida hardware)
	// Habilitación de contador
	TIM3->CR1 |= 0x0001; // CEN = 1 -> Arranco el contador
	TIM3->EGR |= 0x0001; // UG = 1 -> Se genera evento de actualización
	TIM3->SR = 0; // Limpio los flags del contador

	// Habilitación de la interrupción TIM3_IRQ en el NVIC (posición 30).
	NVIC->ISER[0] |= (1 << 29);
	TIM3->CR1 |= 0x01; //Arranca el timer*/

	// ADC Configuration
	GPIOA->MODER |= 0x00000300; // PA4 as analog
	ADC1->CR2 &= ~(0x00000001); // ADON = 0 (ADC powered off)
	ADC1->CR1 = 0x00000000; // OVRIE = 0 (overrun IRQ disabled)
	// RES = 00 (resolution = 12 bits)
	// SCAN = 0 (scan mode disabled)
	// EOCIE = 0 (EOC IRQ disabled)
	ADC1->CR2 = 0x00000412; // EOCS = 1 (EOC is activated after each conversion)
	// DELS = 001 (delay till data is read)
	// CONT = 1 (continuous conversion)
	ADC1->SQR1 = 0x00000000; // 1 channel in the sequence
	ADC1->SQR5 = 0x00000004; // The selected channel is AIN4
	ADC1->CR2 |= 0x00000001; // ADON = 1 (ADC powered on)
	while ((ADC1->SR & 0x0040) == 0)
		; // If ADCONS = 0, I wait till converter is ready
	ADC1->CR2 |= 0x40000000;

	//CONF PWM ASOCIADO A TIMER 2
	GPIOA->MODER |= 1 << (2 * 5 + 1); // MODER = 10 (AF) para el bit 5 del puerto A
	GPIOA->MODER &= ~(1 << (2 * 5));
	GPIOA->AFR[0] &= ~(1 << (4 * 5 + 3));
	GPIOA->AFR[0] &= ~(1 << (4 * 5 + 2));
	GPIOA->AFR[0] &= ~(1 << (4 * 5 + 1));
	GPIOA->AFR[0] |= (1 << (4 * 5)); // AFR[0] para decir que el PA5 tiene la AF1 (TIM2)
	//CONF TIMER 2
	TIM2->CR1 = 0x0080; // ARPE = 1 -> Es PWM; CEN = 0; Contador apagado
	TIM2->CR2 = 0x0000; // Siempre "0" en este curso
	TIM2->SMCR = 0x0000; // Siempre "0" en este curso
	TIM2->PSC = 32000; // Preescalado=32000 -> f_contador=32000000/32000 = 1000 pasos/segundo
	TIM2->CNT = 0; // Inicializo el valor del contador a cero

	TIM2->ARR = 0;
	TIM2->CCR1 = 0; // Pongo una frecuencia PWM de 100 Hz y sólo cuento 10 pasos
	TIM2->CCR2 = 1; // EL DUTY CYCLE VA A SER EL MISMO
	TIM2->DIER = 0x0000;
	TIM2->CCMR1 = 0x0068; // CCyS = 0 (TOC, PWM)
	TIM2->CCMR2 = 0x0000;
	TIM2->EGR |= 0x01;
	TIM2->CR1 |= 0x0001;
	// OCyM = 110 (PWM con el primer semiciclo a 1)
	// OCyPE = 1 (con precarga)
	TIM2->CCER = 0x0001; // CCyP = 0 (siempre en PWM)
	// CCyE = 1 (activada la salida hardware)

	/* USER CODE END 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		if (reinicio == 1) {
			juego_acabado = 1;
			reinicio = 0;
			if (juego == 1) {
				juego = 2;
				//CONFIGURAMOS LO QUE HAGA FALTA DEL JUEGO 2
			} else {
				juego = 1;
				//CONFIGURAMOS LO QUE HAGA FALTA DEL JUEGO 1
			}
		}

		if (juego_acabado == 1) {
			TIM2->CCER = 0;
			GPIOA->BSRR |= (1 << 28);
			GPIOD->BSRR |= ((1 << 2) << 16);
			jugador1 = 0; //DICE SI EL JUGADOR 1 LE HA DADO AL BOTON
			jugador2 = 0; //DICE SI EL JUGADOR 2 LE HA DADO AL BOTON
			ganador = 0; //DICE QUIEN HA GANADO
			juego_acabado = 0;
			paso = 0;
			espera = 0;
			tiempo_excedido = 0;
			TIM4->CNT = 0;
			potenciometro = ADC1->DR;
			escalado = 0;
			tiempo_total = 0;
			melodia = 0;
		}

		switch (juego) {
		case (1):

			if (paso == 0) {
				BSP_LCD_GLASS_DisplayString((uint8_t*) "JUEGO1");
				TIM3->CNT = 0;
				limite = rand() % 8 + 2;
				; //ESPERAMOS ENTRE 1 Y 5  SEGUNDOS A ENCENDER EL LED
				contador_espera = 0;
				espera = 0;
				paso++;
			}

			if (paso > 0 && espera > 0) {

				if (paso == 1) {
					TIM4->CNT = 0;
					GPIOA->BSRR |= (1 << 12); //ENCENDEMOS LED
					TIM3->CNT = 0;
					contador_espera = 0;
					espera = 1;
					paso++;
					jugador1 = 0;
					jugador2 = 0;
					limite = 6;
				}

				if ((jugador1 == 1 || jugador2 == 1) && tiempo_excedido == 0) { //pulsacion

					if (ganador == 0) { //NO SE HA DECIDIDO EL GANADOR
						GPIOA->BSRR |= (1 << 28);
						if (jugador1 == 1) {
							ganador = 1;
						} else if (jugador2 == 1) {
							ganador = 2;
						}
					}

					if (ganador == 1) {
						if (paso == 2) {
							Bin2Ascii((short) (tiempo1), cadena);
							BSP_LCD_GLASS_Clear();
							cadena[0] = '1';
							paso++;
							TIM3->CNT = 0;
							contador_espera = 0;
							espera = 2;
						}

					} else if (ganador == 2) {
						if (paso == 2) {
							Bin2Ascii((short) (tiempo2), cadena);
							BSP_LCD_GLASS_Clear();
							cadena[0] = '2';
							paso++;
							TIM3->CNT = 0;
							contador_espera = 0;
							espera = 2;
						}

					}

					BSP_LCD_GLASS_DisplayString((uint8_t*) cadena);
					//MOSTRAMOS EL MENSAJE 3 SEGUNDOS
					if (espera == 3) {
						juego_acabado = 1;
					}
					//SE TERMINA EL JUEGO Y VUELTA A EMPEZAR

				} else if (espera == 2 || tiempo_excedido == 1) { //HAN PASADO 3 SEGUNDOS Y NADIE LE HA DADO AL BOTON
					tiempo_excedido = 1;
					GPIOA->BSRR |= (1 << 28);
					if (paso == 2) {
						TIM3->CNT = 0;
						contador_espera = 0;
						espera = 2;
						paso++;
						BSP_LCD_GLASS_Clear();
					}

					BSP_LCD_GLASS_DisplayString((uint8_t*) "-----");
					//MOSTRAMOS EL MENSAJE POR 3 SEGUNDOS
					if (espera == 3) {
						juego_acabado = 1;
					}
					//SE TERMINA EL JUEGO Y VUELTA A EMPEZAR
				}

			}

			break;

		case (2):
			/*(paso == 0) {
			 paso++;
			 Bin2Ascii((short) (prueba - 10000), cadena);
			 cadena[0] = '2';
			 BSP_LCD_GLASS_DisplayString((uint8_t*) " JUG_1");
			 //espera2SEG;
			 BSP_LCD_GLASS_DisplayString((uint8_t*) cadena);
			 BSP_LCD_GLASS_DisplayString((uint8_t*) "-");
			 }*/

			if (paso == 0) {
				potenciometro = ADC1->DR;
				if (potenciometro < 900) {
					escalado = 1;
					tiempo_total = 5000;
				} else if (potenciometro > 3500) {
					escalado = 4;
					tiempo_total = 20000;
				} else {
					escalado = 2;
					tiempo_total = 10000;
				}
				BSP_LCD_GLASS_DisplayString((uint8_t*) "JUEGO2");
				TIM3->CNT = 0;
				limite = 6; //MOSTRAMOS MENSAJE POR PANTALLA DURANTE 3 SEGUNDOS
				contador_espera = 0;
				espera = 0;
				paso++;

			}

			if (paso > 0 && espera > 0 && paso < 3) {
				if (paso == 1) {
					limite = escalado;
					paso++;
					limite_rnd = rand() % 8 + 1; //ENTRE 1 Y 9
					contador_espera = 0;
					num_ant = 0;
					num = 0;
					BSP_LCD_GLASS_Clear();
					BSP_LCD_GLASS_DisplayString((uint8_t*) "    10");
					TIM4->CNT = 0;

				}

				if (espera >= 1 && espera <= 15) {
					num = (espera - 1);
					if (num_ant != num) {
						limite += escalado;
						num_ant = num;
						if (espera <= limite_rnd) {
							Bin2Ascii((short) (10 - num), cadena);
							cadena[0] = ' ';
							cadena[1] = ' ';
							cadena[2] = ' ';
							cadena[3] = ' ';
							BSP_LCD_GLASS_DisplayString((uint8_t*) cadena);
						} else {
							BSP_LCD_GLASS_Clear();
						}

					}

				}
				if (paso < 3) {
					//GANADOR
					if (jugador1 == 1 && jugador2 == 1 && juego_acabado == 0) { //PULSAN AMBOS JUGADORES
						if (paso == 2) {
							paso++;
							if (tiempo1 < tiempo_total
									&& tiempo2 < tiempo_total) { //LOS DOS ANTES DE10
								if (tiempo1 > tiempo2) {
									ganador = 1;
									tiempo1 = tiempo_total - tiempo1;
								} else {
									ganador = 2;
									tiempo2 = tiempo_total - tiempo2;
								}
								signo = 1;
							} else if (tiempo1 > tiempo_total
									&& tiempo2 < tiempo_total) { //J1 DESPUES J2 ANTES DE 10 SEG
								if ((tiempo1 - tiempo_total)
										< (tiempo_total - tiempo2)) {
									ganador = 1;
									signo = 0;
									tiempo1 = tiempo1 - tiempo_total;
								} else {
									ganador = 2;
									signo = 1;
									tiempo2 = tiempo_total - tiempo2;
								}

							} else if (tiempo1 < tiempo_total
									&& tiempo2 > tiempo_total) { //J1 ANTES J2 DESPUES DE 10 SEG
								if ((tiempo_total - tiempo1)
										< (tiempo2 - tiempo_total)) {
									ganador = 1;
									signo = 1;
									tiempo1 = tiempo_total - tiempo1;
								} else {
									ganador = 2;
									signo = 0;
									tiempo2 = tiempo2 - tiempo_total;
								}

							} else { //LOS DOS DESPUES DE 10 SEG
								signo = 0;
								if (tiempo1 < tiempo2) {
									ganador = 1;
									tiempo1 = tiempo1 - tiempo_total;

								} else {
									ganador = 2;
									tiempo2 = tiempo2 - tiempo_total;
								}
							}

						}

					} else if (espera == 13) {

						if (paso == 2) {
							paso++;
							if (jugador1 == 1) { //SOLO HA PULSADO JUGADOR 1
								ganador = 1;
								if (tiempo1 < tiempo_total) {
									signo = 1;
									tiempo1 = tiempo_total - tiempo1;
								} else {
									signo = 0;
									tiempo1 = tiempo1 - tiempo_total;
								}
							} else if (jugador2 == 1) { //SOLO HA PULSADO JUGADOR 2
								ganador = 2;
								if (tiempo1 < tiempo_total) {
									signo = 1;
									tiempo2 = tiempo_total - tiempo2;
								} else {
									signo = 0;
									tiempo2 = tiempo2 - tiempo_total;
								}
							} else { //NO HA PULSADO NINGUN JUGADOR
								BSP_LCD_GLASS_DisplayString((uint8_t*) " FIN ");
								paso = 5;
								espera = 14;
								TIM3->CNT = 0;
								contador_espera = 0;
								limite = 6;
							}
						}

					}
				}

			}
			if (paso == 3) { //YA SE HA DECIDIO LA PARTIDA
				if (signo == 1) {
					TIM2->ARR = 8; //SI BEMOL PARA JUGADOR 2
					TIM2->CCR1 = 4;
				} else {
					TIM2->ARR = 4; //SI BEMOL PARA JUGADOR 2
					TIM2->CCR1 = 2; //DESPUES
				}
				if (ganador == 1) {

					BSP_LCD_GLASS_DisplayString((uint8_t*) " JUG_1");
					Bin2Ascii((short) (tiempo1), cadena);
					GPIOA->BSRR |= (1 << 12);
				} else if (ganador == 2) {

					BSP_LCD_GLASS_DisplayString((uint8_t*) " JUG_2");
					Bin2Ascii((short) (tiempo2), cadena);
					GPIOD->BSRR |= (1 << 2);
				}
				TIM2->CCER = 0X0001;
				TIM2->EGR |= 0x0001; // UG = 1 ->
				TIM2->CR1 |= 0x0001; // CEN = 1 ->

				paso++;
				TIM3->CNT = 0;
				espera = 13;
				contador_espera = 0;
				limite = 6;
			} //MUESTRA 2 SEGUNDOS QUIEN HA GANADO


			if (espera == 14 && paso > 3) {
				if (paso == 4) {
					if (signo == 1) {
						cadena[0] = '-';
					} else {
						cadena[0] = ' ';
					}
					BSP_LCD_GLASS_DisplayString((uint8_t*) cadena);
					contador_espera = 0;
					TIM3->CNT = 0;
					paso++;
				}
				//MOSTRAMOS EL MENSAJE 3 SEGUNDOS

			} //MUESTRA 2 SEGUNDOS EL TIEMPO
			if (espera == 15) {
				juego_acabado = 1;
			}

			break;

		default:
			BSP_LCD_GLASS_Clear();
			break;
		}

	}
}
/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
	RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI
			| RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.LSEState = RCC_LSE_ON;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
	RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		Error_Handler();
	}
	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_LCD;
	PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
	PeriphClkInit.LCDClockSelection = RCC_RTCCLKSOURCE_LSE;

	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief ADC Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC_Init(void) {

	/* USER CODE BEGIN ADC_Init 0 */

	/* USER CODE END ADC_Init 0 */

	ADC_ChannelConfTypeDef sConfig = { 0 };

	/* USER CODE BEGIN ADC_Init 1 */

	/* USER CODE END ADC_Init 1 */

	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
	 */
	hadc.Instance = ADC1;
	hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	hadc.Init.Resolution = ADC_RESOLUTION_12B;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	hadc.Init.LowPowerAutoWait = ADC_AUTOWAIT_DISABLE;
	hadc.Init.LowPowerAutoPowerOff = ADC_AUTOPOWEROFF_DISABLE;
	hadc.Init.ChannelsBank = ADC_CHANNELS_BANK_A;
	hadc.Init.ContinuousConvMode = DISABLE;
	hadc.Init.NbrOfConversion = 1;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T2_CC3;
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
	hadc.Init.DMAContinuousRequests = DISABLE;
	if (HAL_ADC_Init(&hadc) != HAL_OK) {
		Error_Handler();
	}

	/** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
	 */
	sConfig.Channel = ADC_CHANNEL_4;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN ADC_Init 2 */

	/* USER CODE END ADC_Init 2 */

}

/**
 * @brief LCD Initialization Function
 * @param None
 * @retval None
 */
static void MX_LCD_Init(void) {

	/* USER CODE BEGIN LCD_Init 0 */

	/* USER CODE END LCD_Init 0 */

	/* USER CODE BEGIN LCD_Init 1 */

	/* USER CODE END LCD_Init 1 */
	hlcd.Instance = LCD;
	hlcd.Init.Prescaler = LCD_PRESCALER_1;
	hlcd.Init.Divider = LCD_DIVIDER_16;
	hlcd.Init.Duty = LCD_DUTY_1_4;
	hlcd.Init.Bias = LCD_BIAS_1_4;
	hlcd.Init.VoltageSource = LCD_VOLTAGESOURCE_INTERNAL;
	hlcd.Init.Contrast = LCD_CONTRASTLEVEL_0;
	hlcd.Init.DeadTime = LCD_DEADTIME_0;
	hlcd.Init.PulseOnDuration = LCD_PULSEONDURATION_0;
	hlcd.Init.MuxSegment = LCD_MUXSEGMENT_DISABLE;
	hlcd.Init.BlinkMode = LCD_BLINKMODE_OFF;
	hlcd.Init.BlinkFrequency = LCD_BLINKFREQUENCY_DIV8;
	if (HAL_LCD_Init(&hlcd) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN LCD_Init 2 */

	/* USER CODE END LCD_Init 2 */

}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void) {

	/* USER CODE BEGIN TIM2_Init 0 */

	/* USER CODE END TIM2_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM2_Init 1 */

	/* USER CODE END TIM2_Init 1 */
	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 0;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 65535;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM2_Init 2 */

	/* USER CODE END TIM2_Init 2 */

}

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM3_Init(void) {

	/* USER CODE BEGIN TIM3_Init 0 */

	/* USER CODE END TIM3_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM3_Init 1 */

	/* USER CODE END TIM3_Init 1 */
	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 0;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 65535;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim3) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM3_Init 2 */

	/* USER CODE END TIM3_Init 2 */

}

/**
 * @brief TIM4 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM4_Init(void) {

	/* USER CODE BEGIN TIM4_Init 0 */

	/* USER CODE END TIM4_Init 0 */

	TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
	TIM_MasterConfigTypeDef sMasterConfig = { 0 };

	/* USER CODE BEGIN TIM4_Init 1 */

	/* USER CODE END TIM4_Init 1 */
	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 0;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 65535;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim4) != HAL_OK) {
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK) {
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig)
			!= HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN TIM4_Init 2 */

	/* USER CODE END TIM4_Init 2 */

}

/**
 * @brief TS Initialization Function
 * @param None
 * @retval None
 */
static void MX_TS_Init(void) {

	/* USER CODE BEGIN TS_Init 0 */

	/* USER CODE END TS_Init 0 */

	/* USER CODE BEGIN TS_Init 1 */

	/* USER CODE END TS_Init 1 */
	/* USER CODE BEGIN TS_Init 2 */

	/* USER CODE END TS_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_12, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, LD4_Pin | LD3_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : PA5 PA12 */
	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pin : PD2 */
	GPIO_InitStruct.Pin = GPIO_PIN_2;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/*Configure GPIO pins : LD4_Pin LD3_Pin */
	GPIO_InitStruct.Pin = LD4_Pin | LD3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
}
/* USER CODE END Error_Handler_Debug */

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
