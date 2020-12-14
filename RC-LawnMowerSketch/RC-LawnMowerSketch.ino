/* 
L298N H-Bridge driving DC motor on Arduino
*/

int ENA = 11; // Arduino PWM Pin 10 to ENA on L298n Board
int IN1 = 13;  //  Arduino Digital Pin 13 to IN1 on L298n Board 
int IN2 = 12;  // Arduino Digital Pin 12 to IN2 on L298n Board



void setup()
{

  pinMode(ENA, OUTPUT); //Set all the L298n Pin to output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void DRIVEONE()
{
  // Run the motors on both direction at fixed speed
  digitalWrite(IN1, HIGH); // Turn HIGH motor A
  digitalWrite(IN2, LOW);
  digitalWrite(ENA, HIGH); 

  
  // Changing the direction of the motor
  
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);  
  // delay(2000);
  // Delay to 2 seconds
   
}

void loop()
{
  DRIVEONE(); 
  delay(1000);
}
