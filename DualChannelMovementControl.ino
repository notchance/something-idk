/**
 * Two Channel Receiver
 * Author: Shawn Hymel (SparkFun Electronics)
 * Date: Aug 24, 2017
 * 
 * Connect a TB6612FNG and RC (PWM) receiver to the Arduino.
 * Mixes two channels for arcade drive.
 * 
 * This code is beerware; if you see me (or any other SparkFun 
 * employee) at the local, and you've found our code helpful, 
 * please buy us a round! 
 * Distributed as-is; no warranty is given.
 */

// Controller pins
const int CH_1_PIN = 10;
const int CH_2_PIN = 11;

// Motor driver pins
const int STBY_PIN = 9;
const int AIN1_PIN = 2;
const int AIN2_PIN = 4;
const int APWM_PIN = 5;
const int BIN1_PIN = 7;
const int BIN2_PIN = 8;
const int BPWM_PIN = 6;

// Parameters
const int deadzone = 20;  // Anything between -20 and 20 is stop

void setup() {

  // Configure pins
  pinMode(STBY_PIN, OUTPUT);
  pinMode(AIN1_PIN, OUTPUT);
  pinMode(AIN2_PIN, OUTPUT);
  pinMode(APWM_PIN, OUTPUT);
  pinMode(BIN1_PIN, OUTPUT);
  pinMode(BIN2_PIN, OUTPUT);
  pinMode(BPWM_PIN, OUTPUT);

  // Enable motor driver
  digitalWrite(STBY_PIN, HIGH);
}

void loop() {

  // Read pulse width from receiver
  int y = pulseIn(CH_2_PIN, HIGH, 25000); \\This reads the highest pulse signal from the throttle Channel
  int x = pulseIn(CH_1_PIN, HIGH, 25000); \\This reads the highest pulse signal from the direction Channel

  // Convert to PWM value (-255 to 255)
  y = pulseToPWM(y); \\ This converts the pulse signal to PWM signal
  x = pulseToPWM(x); \\ This converts the pulse signal to PWM signal

  // Mix for arcade drive
  int left = y + x;
  int right = y - x;

  // Drive motor
  drive(left, right); 
  /*
  This a the drive function being called; The function is defined below.
  The values for left & right are passed into the function and are registered
  to the variables
    speed_a
    speed_b
*/

  delay(5);
}

// Positive for forward, negative for reverse
void drive(int speed_a, int speed_b) { //The DriveFunction is define here & it takes 2 arguments

  // Limit speed between -255 and 255
  speed_a = constrain(speed_a, -255, 255);
  speed_b = constrain(speed_b, -255, 255);
  // This constrains the values for speed_a & speed_b to be between -255 & +255

  // Set direction for motor A
  if ( speed_a == 0 ) {
    digitalWrite(AIN1_PIN, LOW);
    digitalWrite(AIN2_PIN, LOW);
  } else if ( speed_a > 0 ) {
    digitalWrite(AIN1_PIN, HIGH);
    digitalWrite(AIN2_PIN, LOW);
  } else {
    digitalWrite(AIN1_PIN, LOW);
    digitalWrite(AIN2_PIN, HIGH);
  }
/*
*****
What determines the actions of the motor is not the quantity of the value, but
whether the value is negative or Positive
*****
*/

/*
This IF statment will choose one of the following statements
If the value for speed_a is equal to 0
    then motor A will stop
If the value for speed_a is more than 0 (Positive value)
    then motor A will spin in one direction
If the value for speed_a is less than 0 (negative value)
    then motor A will spin in the opposite direction to the direction above
*/
 

  // Set direction for motor B
  if ( speed_b == 0 ) {
    digitalWrite(BIN1_PIN, LOW);
    digitalWrite(BIN2_PIN, LOW);
  } else if ( speed_b > 0 ) {
    digitalWrite(BIN1_PIN, HIGH);
    digitalWrite(BIN2_PIN, LOW);
  } else {
    digitalWrite(BIN1_PIN, LOW);
    digitalWrite(BIN2_PIN, HIGH);
  }
/*
*****
What determines the actions of the motor is not the quantity of the value, but
whether the value is negative or Positive
*****
*/

/*
This IF statment will choose one of the following statements
If the value for speed_a is equal to 0
    then motor B will stop
If the value for speed_a is more than 0 (Positive value)
    then motor B will spin in one direction
If the value for speed_a is less than 0 (negative value)
    then motor B will spin in the opposite direction to the direction above
*/


  // Set speed
  analogWrite(APWM_PIN, abs(speed_a));
  analogWrite(BPWM_PIN, abs(speed_b));
}
/* The speed of the motors is controlled by the quantity of the following values
    motor A - speed_a
    motor B - speed_b
*/

// Convert RC pulse value to motor PWM value; the pulseToPWM function is being defined
int pulseToPWM(int pulse) {
  
  // If we're receiving numbers, convert them to motor PWM
  if ( pulse > 1000 ) {
    pulse = map(pulse, 1000, 2000, -500, 500);
    pulse = constrain(pulse, -255, 255);
  } else {
    pulse = 0;
  }

  // Anything in deadzone should stop the motor
  if ( abs(pulse) <= deadzone ) {
    pulse = 0;
  }

  return pulse;
}