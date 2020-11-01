
#include "default_config.h"
#include <Arduino.h>
#include <Wire.h>

#include "types.h"
#include "wireutils.h"
#include "smoother.h"

#include "timer.h"

u16_t xC;
u16_t yC;
u16_t xS;
u16_t yS;
uint8_t windowSize = 27;
Smoother smootherX(windowSize);
Smoother smootherY(windowSize);

bool led;
IntervalTimer timer;
uint32_t loopCounter;

void onTimer();

// -----------------------------------------------------------------------------
void requestEvent()
// -----------------------------------------------------------------------------
{
    WireUtils::write16(xS); // 2  i:0
    WireUtils::write16(yS); // 2  i:2
    //                                     -------
    //                                        4
}

// -----------------------------------------------------------------------------
void receiveEvent(int howMany)
// -----------------------------------------------------------------------------
{
    //Serial.print(F("receiveEvent n:"));
    //Serial.println(howMany);
    /*
    for(uint8_t i=0; i<howMany; ++i){
        Serial.print("  ");
        Serial.println(Wire.read());
    } 
    */

    u8_t temp;
    WireUtils::read8(temp);
    led = temp.uint8 & 0x01;

    // remove all pending data because it would suppress next call of this function
    while (Wire.available() > 0)
    {
        Wire.read();
    }
}
// -----------------------------------------------------------------------------
void setup()
// -----------------------------------------------------------------------------
{
    // Joystick
    // as fast as possible switch reference from Vcc (5V) to external
    analogReference(EXTERNAL); // connect aref to 3.3V of joystick

    // Serial port
    Serial.begin(115200);

    // LEDs
    pinMode(LED_JOYSTICK_PIN, OUTPUT);
    digitalWrite(LED_JOYSTICK_PIN, false);

    // I²C
    Wire.begin(I2C_ADDRESS);
    Wire.onRequest(requestEvent);
    Wire.onReceive(receiveEvent);
    Serial.print("I²C-Address: 0x");
    Serial.println(I2C_ADDRESS, HEX);


    // Timer
    loopCounter = 0;
    timer.onTimer(&onTimer);
    timer.start(1000, false);

    Serial.println(F("################### START ###################"));
}

void onTimer()
{
    Serial.print("C: ");
    Serial.print(xC.int16);
    Serial.print(", ");
    Serial.print(yC.int16);
    Serial.print(" / S:");
    Serial.print(xS.int16);
    Serial.print(", ");
    Serial.print(yS.int16);
    Serial.println();

    Serial.print("LoopsPerSecond: ");
    Serial.print(loopCounter);
    Serial.print(", JoyInterval: ");
    Serial.print(loopCounter/windowSize);
    Serial.println("Hz");
    loopCounter = 0;
}

// -----------------------------------------------------------------------------
void loop()
// -----------------------------------------------------------------------------
{
    xC.int16 = analogRead(JOYSTICK_X_PIN);
    yC.int16 = analogRead(JOYSTICK_Y_PIN);
    smootherX.addValue(xC);
    smootherY.addValue(yC);
    xS = smootherX.getValue();
    yS = smootherY.getValue();
    loopCounter++;
    timer.loop();
    // Serial.print("X:");
    // Serial.print(x.int16);
    // Serial.print(" Y:");
    // Serial.print(y.int16);
    // Serial.println();
}
