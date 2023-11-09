#include "mbed.h"

//DigitalIn ButtonA(PG_0); //Button A
//DigitalIn ButtonB(PG_1); //Button B
//DigitalIn ButtonC(PG_2, PullDown); //Button C
//DigitalIn ButtonD(PG_3, PullDown); //Button D

BusIn bus(PG_0, PG_1, PG_2, PG_3);
int swVal;

DigitalOut redLED(PC_2); //Red Traffic 1

// main() runs in its own thread in the OS
int main()
{
    // Turn OFF the red LED
    redLED = 0;

    bus[2].mode(PinMode::PullDown);
    bus[3].mode(PinMode::PullDown);
    
    while (true) {
        
        //Wait for ALL buttons to be pressed
        do {
            //Read all inputs
            swVal = bus;
        } while (swVal < 15);

        redLED = !redLED;

        //Wait for noise to settle
        wait_us(10000);
        
        //Wait for ALL buttons to be released
        do {
            //Read all inputs
            swVal = bus;
        } while (swVal > 0);

        //Wait for noise to settle
        wait_us(10000);
        

    }
}

