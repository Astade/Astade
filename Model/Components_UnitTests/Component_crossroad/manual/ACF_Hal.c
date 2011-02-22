/************************************************************************************
 * Astade Message Passing Framework (ACF)                                           *
 * Copyright (C) 2010  Anders Larsen and Thomas Spitzer                             *
 *                                                                                  *
 * This program is free software: you can redistribute it and/or modify             *
 * it under the terms of Boost Software License 1.0 (BSL1.0)                        *
 *                                                                                  *
 * Permission is hereby granted, free of charge, to any person or                   *
 * organization obtaining a copy of the software and accompanying                   *
 * documentation covered by this license (the "Software") to use,                   *
 * reproduce, display, distribute, execute, and transmit the Software, and          *
 * to prepare derivative works of the Software, and to permit third-parties         *
 * to whom the Software is furnished to do so, all subject to the                   *
 * following:                                                                       *
 *                                                                                  *
 * The copyright notices in the Software and this entire statement,                 *
 * including the above license grant, this restriction and the following            *
 * disclaimer, must be included in all copies of the Software, in whole or          *
 * in part, and all derivative works of the Software, unless such copies or         *
 * derivative works are solely in the form of machine-executable object             *
 * code generated by a source language processor.                                   *
 *                                                                                  *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS          *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF                       *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND                     *
 * NON-INFRINGEMENT. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR ANYONE              *
 * DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY,          *
 * WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN               *
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE                 *
 * SOFTWARE.                                                                        *
 ************************************************************************************/


/* Implement all hardware dependend stuff here */

#include "ACF_Hal.h"
#include <stdio.h>

#if defined(__AVR_ATmega128__)

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <avr/iom128.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 7372800
#endif

char ACF_trace_buffer[800];
volatile unsigned int ACF_next_read = 0;
volatile unsigned int ACF_next_write = 0;
volatile unsigned int ACF_TimeCounter = 0;

ISR (USART0_UDRE_vect)
{
    if (ACF_next_read != ACF_next_write)
    {
        if (UCSR0A & (1<<UDRE))
        {
            UDR0 = ACF_trace_buffer[ACF_next_read++];
            if (ACF_next_read >= sizeof(ACF_trace_buffer))
                ACF_next_read = 0;
        }
    }
    else
        UCSR0B &= ~(1<<UDRIE0);  //Disable data register empty interrupt
}

ISR(TIMER0_COMP_vect)
{
    ++ACF_TimeCounter; 
}

const uint32_t ACF_predivtable[] = {1,8,32,64,128,256,1024};

void ACF_InitTimerTick(uint32_t uLTickFrequenz)
{
	uint8_t i;
	uint32_t teiler;

	for (i=0;i<sizeof(ACF_predivtable)/sizeof(uint32_t);i++)
	{
		teiler =((F_CPU / (uLTickFrequenz * ACF_predivtable[i])) - 1);
		if ( teiler <= 255)
		{
			OCR0 = (uint8_t) teiler;
			TCCR0 = 0x08 | (i + 1);
			return;
		}
	}
}

void ACF_USART0_Init( unsigned long baud )
{
  unsigned int ubrr = (unsigned int) (F_CPU/16uL/ (unsigned long) (baud)) - 1;    //example: ubrr should be 47 at 9600 baud!
    // Set the baud rate registers
    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) ubrr;
    // Enable receiver and transmitter and enable receive and transmit complete interrupts
    UCSR0B = (/*(1<<RXCIE0)|(1<<TXCIE0)|(1<<RXEN)|*/(1<<TXEN));
    // Set frame format: 8data, 1stop bit
    UCSR0C = ((0<<USBS)|(3<<UCSZ0));
}

void ACF_init(void)
{
    ACF_USART0_Init(38400);
    ACF_InitTimerTick(1000);
	TIMSK |= (1<<OCIE0); //Enable tick interrupt
  	sei();
    ACF_trace("Initialisation done!\n");
}

unsigned int ACF_getTimeTick(void)
{
    unsigned int ret;
    cli();
    ret = ACF_TimeCounter;
    sei();
    return ret;
}

void ACF_wait(int ms)
{
}

void ACF_wakeup()
{
}

void ACF_interrupts_off(void)
{
    cli();
}

void ACF_interrupts_on(void)
{
	sei();
}

int8_t ACF_trace_putchar(char ch)
{
    unsigned int next = ACF_next_write + 1;
    if (next >= sizeof(ACF_trace_buffer))
        next = 0;

    if (next == ACF_next_read) // buffer full
    {
        return -1;
    }

    ACF_trace_buffer[ACF_next_write] = ch;

    ACF_next_write = next;
 
    if (UCSR0A & (1<<UDRE))
        UCSR0B |= (1<<UDRIE0);  //Enable data register empty interrupt - force interrupt trigger
 
    return 0;
}

void ACF_trace(const char* string)
{
    while (*string)
    {
        while(ACF_trace_putchar(*string) == -1)
            continue;
        string++;
    }
}

void ACF_traceTimestamp(void)
{
}

#elif defined(__linux__)

#include <time.h>
#include <sys/time.h>
#include <semaphore.h>

sem_t m_Semaphore;
sem_t m_TimeoutSemaphore;

void ACF_init(void)
{
    sem_init(&m_Semaphore, 0, 1);
    sem_init(&m_TimeoutSemaphore, 0, 0); // we implement the timeout semaphone with 0 to block always
    ACF_trace("ACF initialisation done!\n");
}

unsigned int ACF_getTimeTick(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_sec * 1000 + time.tv_usec / 1000; //I want milliseconds
}

void ACF_wait(int ms)
{
	  struct timespec ts;
    struct timeval time;
    gettimeofday(&time, NULL);
    
	  if ((ms < 0) || (ms > 100))
		  ms = 100;
	  
	  ts.tv_sec = time.tv_sec;
	  ts.tv_nsec = time.tv_usec * 1000;
	  
	  ts.tv_sec  +=  ms / 1000;
	  ts.tv_nsec += (ms % 1000) * 1000000;
	  while (ts.tv_nsec >= 1000000000)
	  {
	    ts.tv_nsec -= 1000000000;
	    ts.tv_sec++;
	  }
	  sem_timedwait(&m_TimeoutSemaphore, &ts); //this is better than a sleep, because we can interrupt it when a message is sent.
}

void ACF_wakeup() // this interrupts the sleep (see ACF_wait)
{
  sem_post(&m_TimeoutSemaphore);
}

void ACF_interrupts_off(void)
{
    while (sem_wait(&m_Semaphore)) // sem_wait returns zero unless interrupted by a signal
        ;
}

void ACF_interrupts_on(void)
{
    sem_post(&m_Semaphore);
}

void ACF_trace(const char* string)
{
    fputs(string, stdout);
}

void ACF_traceTimestamp(void)
{
	char buffer[18];
    struct timeval time;
    gettimeofday(&time, NULL);
	snprintf(buffer, sizeof(buffer), "[%ld.%03ld] ", time.tv_sec, time.tv_usec / 1000);
	ACF_trace(buffer);
}

#endif // __linux__

void ACF_tracePtr(const void* x)
{
    char buffer[2*sizeof(int*)+4];
    snprintf(buffer,sizeof(buffer),"%p:",x);
    ACF_trace(buffer);
}
