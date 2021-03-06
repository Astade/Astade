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


/* Define all hardware dependent stuff here */

/** The number of messages which can be queued inside the message queue */
#define ACF_MESSAGEQUEUESIZE 20

 /** The number of timeouts which can be queued inside the timer queue */
#define ACF_MAXTIMEOUTS 20

#ifdef __cplusplus
extern "C" {
#endif

/** This function is for initialising the environment */
void ACF_init(void);

/** This function returns an increasing unsigned integer counter.
    The framework uses it to implement all timeouts.
    In a microcontroller system you normally would use
    a hardware timer for this. */
unsigned int ACF_getTimeTick(void);

/** This function waits for the specified number of milliseconds.
    It is called when the scheduler determines that the system is idle.
    In a microcontroller system you might simply wait for the next
    interrupt (or leave the function empty).
    @param ms The number of milliseconds to wait or -1 if no timer is active */
void ACF_wait(int ms);

/** This function terminates the wait.
    It is called when someone writes into the message queue.
    this depends, on hoe you implemented "ACF_wait".
    In a microcontroller system you might not implement it and leave it empty. */
void ACF_wakeup();

/** This function is used to swich off all hardware interrupts. 
    The framework uses this whenever queuing messages
    so it is possible to send messages from an interrupt routine */
void ACF_interrupts_off(void);

/** This function is used to swich on all hardware interrupts. 
    The framework uses this whenever queuing messages
    so it is possible to send messages from an interrupt routine */
void ACF_interrupts_on(void);

/** This function is used for tracing. 
    It should be able to write the trace somewhere.
    If you don't use tracing you can leave this function empty.
    @param string A C-string to append to the trace */
void ACF_trace(const char* string);

/** This function is used for tracing pointers.
    @param ptr A pointer */
void ACF_tracePtr(const void* ptr);

/** This function is used for tracing timestamps.  */
void ACF_traceTimestamp(void);

#ifdef __cplusplus
}
#endif
