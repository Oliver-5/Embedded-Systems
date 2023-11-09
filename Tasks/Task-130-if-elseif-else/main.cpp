#include "uop_msb.h"
using namespace uop_msb;

//DigitalIn ButtonA(PG_0); //Button A
//DigitalIn ButtonB(PG_1); //Button B
//DigitalIn ButtonC(PG_2, PullDown); //Button C
//DigitalIn ButtonD(PG_3, PullDown); //Button D

DigitalOut redLED(TRAF_RED1_PIN);       //Red Traffic 1
DigitalOut yellowLED(TRAF_YEL1_PIN);    //Yellow Traffic 1
DigitalOut greenLED(TRAF_GRN1_PIN);     //Green Traffic 1
BusIn bus(PG_0, PG_1);
int swVal;
//Dual Digit 7-segment Display
LatchedLED disp(LatchedLED::SEVEN_SEG);

int main()
{
    int count = 0;

    //Turn ON the 7-segment display
    disp.enable(true);

    //Update display
    disp = count;

    while (true) {
        
        //Read button without blocking
        //int btnA = PG_0;    //Local to the while-loop  
        //int btnB = PG_1;
        swVal = bus;
        //Test Button A
        if (bus[0] == 1) {
            redLED = !redLED;    //Toggle RED led
            count = count + ((count<99) ? 1 : 0);            //Increment count
            disp = count;       //Update display
        }

        if (bus[1] == 1) {
            redLED = !redLED;
            count = count - ((count>0) ? 1 : 0);
            disp = count;
        }

        if (bus[0] == 1 && bus[1] == 1) {
        count = 0;
        }

        // Slow it down a bit (and debounce the switches)
        wait_us(100000);  
    }
}


