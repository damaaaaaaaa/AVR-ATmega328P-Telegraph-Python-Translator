#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <stdbool.h>

#define BAUD 9600                         //velocita'
#define UBRR (F_CPU / 16 / BAUD) - 1      // BAUD convertita in linguaggio che capisce atmega32

volatile unsigned long millisecondi = 0;

void UART_init (unsigned int ubrr) {

    UBRR0H = (unsigned char)(ubrr >> 8);    //high
    UBRR0L = (unsigned char)ubrr;           //low

    UCSR0B = (1 << TXEN0);                  // arduino trasmette

    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // formato per inviare caratteri

}   

void UART_transmit (unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));       //se bit e' 1 la cassetta e' vuota
    UDR0 = data;                            //non salva solo il dato ma lo consegna a un altro macchinario
                                            //porta d'ingresso
}   

void UART_print (const char* str) { 
    while (*str) {
        UART_transmit (*str++);
    }
}   

ISR (TIMER0_COMPA_vect) {
    millisecondi++;
}

void TIMER_init () {

    // (F_CPU / (64 * 1000)) - 1
    OCR0A = 249;      //registro di confronto dell'output, del timer 0, canale A
    TCNT0 = 0;

    TCCR0A = (1 << WGM01);                  //ctc, obbliga TCNT0 a scontrarsi contro OCR0A e poi a resettarsi
    TCCR0B = (1 << CS01) | (1 << CS00);     //prescaler attivato con 64

    TIMSK0 = (1 << OCIE0A);                 // abilita interrupt quando sbatte contro OCR0A
    // va a vedere cosa fa la funzione ISR
}

int main () {

    UART_init (UBRR);
    TIMER_init ();
    sei ();

    DDRB |= (1 << DDB5) | (1 << DDB4); 
    DDRD &= ~(1 << DDD2);

    bool premuto                 = false;
    unsigned long tempo_premuto  = 0;
    unsigned long tempo_rilascio = 0;

    while (1) {
        if (PIND & (1 << PIND2)) {
            if (!premuto) {
                tempo_premuto = millisecondi;
                premuto = true;
            }
            PORTB |= (1 << PORTB5);  

            PORTB |= (1 << PORTB4);  
            _delay_us(500);           
            PORTB &= ~(1 << PORTB4);  
            _delay_us(500);

        } else {
            if (premuto) {
                tempo_rilascio = millisecondi - tempo_premuto;
                premuto = false;
                PORTB &= ~((1 << PORTB5) | (1 << PORTB4));
    
                if (tempo_rilascio < 30);
                else if (tempo_rilascio < 200) {
                    UART_print (".");
                }
                else if (tempo_rilascio > 200 && tempo_rilascio < 1000) {
                    UART_print ("-");
                }
                else if (tempo_rilascio > 1000 && tempo_rilascio < 3000) {
                    UART_print (" ");
                }
                else if (tempo_rilascio > 3000 && tempo_rilascio < 10000) {
                    UART_print (" / ");
                }
                else if (tempo_rilascio > 10000) {
                    UART_print ("\n");
                }
            }
        }
    }
}