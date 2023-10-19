#include "mbed.h"

DigitalOut redLED(PC_2,1);
DigitalOut yellowLED(PC_3,1);
DigitalOut greenLED(PC_6,1);

int main()
{
    wait_us(1000000);
    redLED = 0;
    yellowLED = 0;
    greenLED = 0;
    wait_us(1000000);

    while (true) {
        int count = 0;

        redLED = 1;
        wait_us(2000000);

        yellowLED = 1;
        wait_us(2000000);
        yellowLED = 0;
        redLED = 0;

        greenLED = 1;
        wait_us(2000000);
        greenLED = 0;

            while (count < 4) {

                yellowLED = 1;
                wait_us(500000);
                yellowLED = 0;
                wait_us(500000);
                count = count + 1;
                 }
        }
    }