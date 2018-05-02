/* FINAL CODE
 * File:   state_of_machine.c
 * Author: philip
 * version 16.4.18.1
 * Created on 16 April 2018, 14:44
 */
#include <xc.h>
#include "config.h"
#include "clear_oled.h"
#include "write_character.h"
#include "bar_graph.h"
#include "get_digit.h"
#include "split_digits.h"
#include "mute.h"
#include "setup_vol_scrn.h"
#include "input.h"
#include "select_ip.h"
#include "state_of_machine.h"



void state_of_machine(int *c_state) // *c_state is initially == VOL state
{ 
    switch (*c_state)
    {
        case VOL:                   // initial state of machine
            if(SWIP == HI)          // SWIP not pressed  - path 0 on state diagram
            {
                *c_state = VOL;     // stay in VOL state
                VOL_LED = 1;
                MUTE_LED = 0;
                INPUT_LED = 0;
                SELECT_IP_LED = 0;
                time_out = 0;
                 T1CONbits.TMR1ON = 0;
            }
            else if(SWIP == LO)          // SWIP pressed - path 1 on state diagram
            {
               
                T1CONbits.TMR1ON = 1;   // start TMR1 counting up from zero
                while(SWIP == LO);      // wait for SWIP to be released to see if a long push has happened
            if (time_out >= 10 && time_out <=20)    // long press
            {
                *c_state = MUTE;     // move from VOL to MUTE state path 1 on state diagram
                VOL_LED = 0;
                MUTE_LED = 1;
                INPUT_LED = 0;
                SELECT_IP_LED = 0;
                time_out = 0;
                T1CONbits.TMR1ON = 0;
            }
                
                
            }
            if (time_out >= 2 && time_out <=9)   // short press
            {
                while(SWIP == LO);
                *c_state = INPUT;     // SWIP pressed short so move from VOL to  INPUT state - path 6 on state diagram
                VOL_LED = 0;
                MUTE_LED = 0;
                INPUT_LED = 1;
                SELECT_IP_LED = 0;
                time_out = 0; 
                T1CONbits.TMR1ON = 0;//move from VOL to INPUT state path 6 on state diagram
            }
            break;
            
        case MUTE:
            if(SWIP == HI)
            {
                *c_state = MUTE;     // SWIP not pressed so stay in MUTE state - path 2 on state diagram
                VOL_LED = 0;
                MUTE_LED = 1;
                INPUT_LED = 0;
                SELECT_IP_LED = 0;
                time_out = 0;
            }
            else if(SWIP == LO)
            {
                T1CONbits.TMR1ON = 1;   // start TMR1 counting up from zero
                while(SWIP == LO);      // wait for SWIP to be released to see if a long push has happened
            }
            if(time_out >= 10 && time_out <=20)     // long press
            {
                *c_state = VOL;     // SWIP pressed so check if long press and move back to VOL state - path 3 on state diagram
                VOL_LED = 1;
                MUTE_LED = 0;
                INPUT_LED = 0;
                SELECT_IP_LED = 0;
                time_out = 0;
                T1CONbits.TMR1ON = 0;
            }
            if (time_out >= 2 && time_out <=9)   // short press
            {
                while(SWIP == LO);
                *c_state = INPUT;     // SWIP pressed short so move from VOL to  INPUT state - path 6 on state diagram
                VOL_LED = 0;
                MUTE_LED = 0;
                INPUT_LED = 1;
                SELECT_IP_LED = 0;
                time_out = 0; 
                T1CONbits.TMR1ON = 0;//move from VOL to INPUT state path 6 on state diagram
            }
            break;
            
        case INPUT:
            if(SWIP == HI)
            {
                *c_state = INPUT;     // SWIP not pressed so stay in INPUT state - path 5 on state diagram
                VOL_LED = 0;
                MUTE_LED = 0;
                INPUT_LED = 1;
                SELECT_IP_LED = 0;
                time_out = 0;
            }
            else if(SWIP == LO)
            {
                T1CONbits.TMR1ON = 1;   // start TMR1 counting up from zero
            }
            if(time_out >= 2 && time_out <=9)     // short press
            {
                *c_state = SELECT_IP;     // SWIP pressed so check if short press and move  to SELECT_IP state - path 7 on state diagram
                VOL_LED = 0;
                MUTE_LED = 0;
                INPUT_LED = 0;
                SELECT_IP_LED = 1;
                time_out = 0;
                T1CONbits.TMR1ON = 0;
            }
            break;
            
        case SELECT_IP:
            if(SWIP == HI)
            {
                *c_state = SELECT_IP;     // SWIP not pressed so stay in SELECT_IP state - path 8 on state diagram
                VOL_LED = 0;
                MUTE_LED = 0;
                INPUT_LED = 0;
                SELECT_IP_LED = 1;
                time_out = 0;
            }
            else if(SWIP == LO)
            {
                T1CONbits.TMR1ON = 1;   // start TMR1 counting up from zero
            }
            if(time_out >= 2 && time_out <=9)     // short press
            {
                *c_state = VOL;     // SWIP pressed so check if short press and move  to SELECT_IP state - path 7 on state diagram
                VOL_LED = 1;
                MUTE_LED = 0;
                INPUT_LED = 0;
                SELECT_IP_LED = 0;
                time_out = 0;
                T1CONbits.TMR1ON = 0;
            }
            break;
               
    }
    
}
           

