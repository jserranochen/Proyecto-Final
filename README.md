# Proyecto ADS1115 con AVR Atmega328p

Proyecto Final Materia Circuitos 4 Universidad Latina de Panamá, Falcultad de Ing. Mecatronica. Estudiantes: Josue Serrano, Angel Fletcher

## Que es el ADS?

El ADS1115 es un conversor analógico digital (ADC) externo que podemos conectar a un procesador para medir señales analógicas. EL cual nos sirve como un rectificar de señal con el cual podemos aplicarlo en motores, sistemas de medicion, sistemas de señales de television ect.

## Desarrollo de la Investigacion

Lo que se quiso lograr con este proyecto fue implementar el ADS con el ATMEGA328P para la medicion de señal exacta mostrada en un DP. el cual se programo el ATMEGA para que cuando la intensidad de la señal fuera variando se comunicara con el ADS mediante I2C para que asi el ADS midiera los valores y los entregara a los puertos de salida del ATMEGA y se mostraran en el DP.

### Materiales

Este proyecto lo realizamos con el simulador Proteus con los siguientes componentes:

- ADS1115
- ATMEGA328P
- BTN
- RESISTORES
- DIODOS COLOR ROJO
- FUENTE DE ALIMENTACION 5V
- POTENCIOMETRO

### Circuito

![Circuito](/image/1.jpg)

### c++

    #define F_CPU 16000000UL
    #include <util/delay.h>
    #include <avr/io.h>
    #include <avr/interrupt.h>
    #include "lcd.h"
    #include <stdio.h>
    #define cli() asm volatile("cli"::)
    #define sei() asm volatile("sei"::)

    ISR(INT0_vect){
    	PORTD ^= (1<<0);
    }
    void AVRInit()
    {
    	 DDRC = 0x02;
    	//DDRC = 0b00000000;

    	// DDRC = 0x00;
    	//PORTC = (1<<PINC3);
    }

    unsigned int analogResult = 0;
    unsigned int binary_weighted_voltage_low;
    unsigned int binary_weighted_voltage_high;

    int main(void)
    {
    	AVRInit();
    	DDRD = 0b00000001;

    	PORTD &= ~(1<<0);// inicia en 0

    	EICRA = 0b00000010;
    	EIMSK = 0b00000001;
    	EIFR = 0b00000000;
    	sei();


    	ADMUX |= (0 << REFS1)|(1 << REFS0)|(0 << ADLAR)|(0 << MUX3)|(0 << MUX2)|(0 << MUX1)|(1 << MUX0);
    	ADCSRA |= (1 << ADEN)|(0 << ADSC)|(0 << ADATE)|(0 << ADIF)|(0 << ADIE)|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);
    	ADCSRB |= (0 << ADTS2)|(0 << ADTS1)|(0 << ADTS0);
    	while (1)
    	{
    		ADCSRA |= (1 << ADSC);
    		while (ADCSRA & (1 << ADSC));
    		binary_weighted_voltage_low = ADCL;
    		binary_weighted_voltage_high = (ADCH << 8);

    		analogResult = binary_weighted_voltage_low | binary_weighted_voltage_high;
    		char k [10];
    		itoa(analogResult,k,10);

    		lcd_init(LCD_DISP_ON);
    		lcd_home();
    		lcd_gotoxy(9,0);
    		lcd_puts(k);
    		_delay_ms (100);
    	}
    }

###End
