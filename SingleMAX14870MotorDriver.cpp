#include "SingleMAX14870MotorDriver.h"

// Constructors ////////////////////////////////////////////////////////////////

SingleMAX14870MotorDriver::SingleMAX14870MotorDriver() :
  _DIR(8), _PWM(9)
{
}

SingleMAX14870MotorDriver::SingleMAX14870MotorDriver(uint8_t DIR,
                                                     uint8_t PWM) :
  _DIR(DIR), _PWM(PWM)
{
}

void SingleMAX14870MotorDriver::initPinsAndMaybeTimer()
{
  pinMode(_PWM, OUTPUT);
  digitalWrite(_PWM, LOW);
  pinMode(_DIR, OUTPUT);
  digitalWrite(_DIR, LOW);

#ifdef SingleMAX14870MotorDriver_TIMER1_AVAILABLE
  if (_PWM == _PWM_TIMER1_PIN)
  {
    // Timer 1 configuration if needed
  }
#endif
}

// speed should be a number between -400 and 400
void SingleMAX14870MotorDriver::setSpeed(int16_t speed)
{
  init(); // initialize if necessary

  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed; // make speed a positive quantity
    reverse = 1;    // preserve the direction
  }
  if (speed > 400)  // max
    speed = 400;

#ifdef SingleMAX14870MotorDriver_TIMER1_AVAILABLE
  if (_PWM == _PWM_TIMER1_PIN)
  {
    // Timer 1 specific code if needed
  }
  else
#endif
  {
    analogWrite(_PWM, speed * 51 / 80); // map 400 to 255
  }

  if (reverse) // flip if speed was negative
    digitalWrite(_DIR, HIGH);
  else
    digitalWrite(_DIR, LOW);
}

// Other functions (e.g., setSpeeds, flip, etc.) remain unchanged
