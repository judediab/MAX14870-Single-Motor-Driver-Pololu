#pragma once

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__) || \
    defined(__AVR_ATmega328PB__) || defined (__AVR_ATmega32U4__)
  #define SingleMAX14870MotorDriver_TIMER1_AVAILABLE
#endif

#include <Arduino.h>

class SingleMAX14870MotorDriver
{
  public:
    // Constructors
    SingleMAX14870MotorDriver();
    SingleMAX14870MotorDriver(uint8_t M1DIR,
                              uint8_t M1PWM,
                              uint8_t shared_nEN);

    // Methods
    void setM1Speed(int16_t speed);
    void setSpeeds(int16_t m1Speed);
    void flipM1(bool flip);
    bool getFault();
    void enableDrivers();
    void disableDrivers();

  private:
    // Private Methods
    void initPinsAndMaybeTimer();

    // Member Variables
    uint8_t _M1DIR;
    uint8_t _M1PWM;
    uint8_t _shared_nEN;  // Shared nEN pin
    static const uint8_t _M1PWM_TIMER1_PIN = 9;

    bool _flipM1 = false;
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
