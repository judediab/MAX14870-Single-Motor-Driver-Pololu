# MAX14870-Single-Motor-Driver-Pololu
An adaptation to the Pololu DUALMAX14870MOTORSHIELD for the single-motor driver. I have created this for in a wheeled robot with 4 independently controlled wheels, so please note that the code assumes you have connected EN pins to a common pin on the microcontroller (this effectively acts as a handbrake and stops all wheels from turning when pulled HIGH).

When using it I have created 4 instances SingleMAX14870MotorShield_RB, SingleMAX14870MotorShield_LB, SingleMAX14870MotorShield_LF, SingleMAX14870MotorShield_RF

The original repository can be found here:
https://github.com/pololu/dual-max14870-motor-shield

The Single Driver can be viewed and orderd on the manufacturer's website here:
https://www.pololu.com/product/2961 
