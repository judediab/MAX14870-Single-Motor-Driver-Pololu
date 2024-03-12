#pragma once

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || \
    defined(__AVR_ATmega328PB__) || defined (__AVR_ATmega32U4__)
  #define SingleMAX14870MotorDriver_TIMER1_AVAILABLE
#endif

#include <Arduino.h>

class SingleMAX14870MotorDriver
{
  public:
    SingleMAX14870MotorDriver();
    SingleMAX14870MotorDriver(uint8_t DIR, uint8_t PWM);

    void setSpeed(int16_t speed);
    void flip(bool flip);

  private:
    void initPinsAndMaybeTimer();

    uint8_t _DIR;
    uint8_t _PWM;
    static const uint8_t _PWM_TIMER1_PIN = 9;

    bool _flip = false;

    bool initialized = false;

    inline void init()
    {
      if (!initialized)
      {
        initialized = true;
        initPinsAndMaybeTimer();
      }
    }
};
