#include "mbed.h"

DigitalOut myLED(LED1);
int main(){

while (1)
{
    myLED = 1;

wait_us(2000000);

myLED.write(0);

wait_us(2000000);
}
}