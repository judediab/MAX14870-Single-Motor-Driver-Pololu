#include "SingleMAX14870MotorDriver.h"

// Constructors ////////////////////////////////////////////////////////////////

SingleMAX14870MotorDriver::SingleMAX14870MotorDriver() :
  _M1DIR(7), _M1PWM(9)
{
}

SingleMAX14870MotorDriver::SingleMAX14870MotorDriver(uint8_t M1DIR,
                                                 uint8_t M1PWM                                             
                                                 ) :
  _M1DIR(M1DIR), _M1PWM(M1PWM)
{
}


void SingleMAX14870MotorDriver::initPinsAndMaybeTimer()
{
  pinMode(_M1PWM, OUTPUT);
  digitalWrite(_M1PWM, LOW);
  pinMode(_M1DIR, OUTPUT);
  digitalWrite(_M1DIR, LOW);

#ifdef SingleMAX14870MotorDriver_TIMER1_AVAILABLE
  if (_M1PWM == _M1PWM_TIMER1_PIN)
  {
    // timer 1 configuration
    // prescaler: clockI/O / 1
    // outputs enabled
    // phase-correct PWM
    // top of 400
    //
    // PWM frequency calculation
    // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
    TCCR1A = 0b10100000;
    TCCR1B = 0b00010001;
    ICR1 = 400;
  }
#endif
}

// speed should be a number between -400 and 400
void SingleMAX14870MotorDriver::setM1Speed(int16_t speed)
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
  if (_M1PWM == _M1PWM_TIMER1_PIN )
  {
    OCR1A = speed;
  }
  else
  {
    analogWrite(_M1PWM, speed * 51 / 80); // map 400 to 255
  }
#else
  analogWrite(_M1PWM, speed * 51 / 80); // map 400 to 255
#endif

  if (reverse ^ _flipM1) // flip if speed was negative or _flipM1 setting is active, but not both
    digitalWrite(_M1DIR, HIGH);
  else
    digitalWrite(_M1DIR, LOW);
}


  init(); // initialize if necessary

  boolean reverse = 0;

  if (speed < 0)
  {
    speed = -speed;  // make speed a positive quantity
    reverse = 1;  // preserve the direction
  }
  if (speed > 400)  // max PWM duty cycle
    speed = 400;



// set speed for both motors
// speed should be a number between -400 and 400
void SingleMAX14870MotorDriver::setSpeeds(int16_t m1Speed)
{
  setM1Speed(m1Speed);

}

void SingleMAX14870MotorDriver::flipM1(bool flip)
{
  _flipM1 = flip;
}
