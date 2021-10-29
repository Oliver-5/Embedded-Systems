#include "mbed.h"
#include "uop_msb.h"
#include <iostream>
using namespace uop_msb;
using namespace std;

class PressAndRelease {
private:
    typedef enum {BTN_PRESS=1, BTN_RELEASE=2} ISR_EVENT;
    typedef void(*funcPointer_t)(void);
    Thread t1;
    InterruptIn button;
    DigitalOut gpioOutput;

    void button_rise() {
        t1.flags_set(BTN_PRESS);
    }

    void button_fall() {
        t1.flags_set(BTN_RELEASE);    
    }

    void handler() 
    {
        while (true) {
            ThisThread::flags_wait_all(BTN_PRESS);
            button.rise(NULL);
            gpioOutput = 1;
            onPress();
            ThisThread::sleep_for(50ms);
            ThisThread::flags_clear(BTN_PRESS);
            button.fall(callback(this, &PressAndRelease::button_fall));

            ThisThread::flags_wait_all(BTN_RELEASE);
            button.fall(NULL);
            gpioOutput = 0;
            ThisThread::sleep_for(50ms);
            ThisThread::flags_clear(BTN_RELEASE);
            button.rise(callback(this, &PressAndRelease::button_rise));
        }
    }
    //Hook into the button press
    void(*onPress)(void);

public:
    PressAndRelease(PinName buttonPin = BTN1_PIN, PinName ledPin = TRAF_RED1_PIN, funcPointer_t press = NULL) : button(buttonPin), gpioOutput(ledPin), onPress(press)
    {
        t1.start(callback(this, &PressAndRelease::handler));
        button.rise(callback(this, &PressAndRelease::button_rise));  
    }

    Thread& getThread() {
        return t1;
    }
};

//Globals
DigitalOut led1(LED1);
DigitalOut led2(LED2);

//Event queue for main
EventQueue ledFlashQueue;

//Flash a given LED - parameter passed by reference
void flashLed(DigitalOut& led) {
    led = !led;
}
//Flash on calling thread
void flashLed1() {
    flashLed(led1);
    ledFlashQueue.call(printf, "Flash on calling thread\n");
}
//Flash on main thread
void flashLed2() {
    ledFlashQueue.call(flashLed, led2);
    ledFlashQueue.call(printf, "Flash on main thread\n");
}

int main() {  
    PressAndRelease btnA(BTN1_PIN, TRAF_RED1_PIN, &flashLed1);
    PressAndRelease btnB(BTN2_PIN, TRAF_YEL1_PIN, &flashLed2);
    //Start main queue - dispatch
    ledFlashQueue.dispatch_forever();
}








