
//Fabiolus
//the_fabiolous@hotmail.com
//2020/09/28
/*
    DRV8833. This motor driver chip is a nice alternative to the TB6612 driver. Like that chip,
    you get 2 full H-bridges, but this chip is better for low voltage uses (can run from 2.7V up to 10.8V
    motor power) and has built in current limiting capability. We set it up for 1A current limiting
    so you don't get more than 2A per chip, but you can also disable the current limiting, or change
    it to a different limit!

    That means you can drive two DC motors bi-directionally, or one stepper motor.
    Just make sure they're good for about 1.2 Amp or less of current, since
    that's the limit of this chip. They do handle a peak of 2A but that's just
    for a short amount of time, if you turn off the current limiting we set.
    What we like most about this particular driver is that it comes with built
    in kick-back diodes internally so you dont have to worry about the inductive
    kick damaging your project or driver! You also don't have to worry as much
    about burning out the chip with overdriving since there is current limiting.
*/


// global variables
#define ain1  5  // Motor A input 1
#define ain2  6  // Motor A input 2
#define bin1  9 // Motor B input 1
#define bin2  3 // Motor B input 2
#define slp  4  // DRV8833 sleep/enable
#define flt  2   // overcurrent/overheat fault

// Define Joystick Connections
#define joyX A0
#define joyY A1

int joyposX = 512;
int joyposY = 512;

int MotorSpeed1 = 0;
int MotorSpeed2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(ain1, OUTPUT);
  pinMode(ain2, OUTPUT);
  pinMode(bin1, OUTPUT);
  pinMode(bin2, OUTPUT);
  pinMode(slp, OUTPUT);
  pinMode(flt, INPUT_PULLUP);
  digitalWrite(ain1, LOW);
  digitalWrite(ain2, LOW);
  digitalWrite(bin1, LOW);
  digitalWrite(bin2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  joyposX = analogRead(joyX);
  joyposY = analogRead(joyY);


  Serial.println(joyposX);
  //Serial.println(joyposY);

  // check for a fault
  if (digitalRead(flt) != LOW) {




    if (joyposX > 510)
    {
      // enable DRV8833
      digitalWrite(slp, HIGH);
      MotorSpeed1 = map(joyposX, 510, 1023, 0, 255);
      MotorSpeed2 = map(joyposX, 510, 1023, 0, 255);

      // This is forward
      digitalWrite(ain1, LOW);
      analogWrite(ain2, MotorSpeed1);
      analogWrite(bin1, MotorSpeed2);
      digitalWrite(bin2, LOW);

    }

    else if (joyposX < 480)
    {
      // enable DRV8833
      digitalWrite(slp, HIGH);
      MotorSpeed1 = map(joyposX, 480, 0, 0, 255);
      MotorSpeed2 = map(joyposX, 480, 0, 0, 255);

      // This is forward
      analogWrite(ain1, MotorSpeed1);
      digitalWrite(ain2, LOW);
      digitalWrite(bin1, LOW);
      analogWrite(bin2, MotorSpeed2);

    }
    else  if (joyposY < 505)
    {
      // enable DRV8833
      digitalWrite(slp, HIGH);
      MotorSpeed1 = map(joyposY, 505, 0, 0, 255);
      MotorSpeed2 = map(joyposY, 505, 0, 0, 255);

      // This is forward
      analogWrite(ain1, MotorSpeed1);
      digitalWrite(ain2, LOW);
      analogWrite(bin1, MotorSpeed2);
      digitalWrite(bin2, LOW);

    }
    else  if (joyposY > 520)
    {
      // enable DRV8833
      digitalWrite(slp, HIGH);
      MotorSpeed1 = map(joyposY, 520, 1023, 0, 255);
      MotorSpeed2 = map(joyposY, 520, 1023, 0, 255);

      // This is forward
      digitalWrite(ain1, LOW);
      analogWrite(ain2, MotorSpeed1);
      digitalWrite(bin1, LOW);
      analogWrite(bin2, MotorSpeed2);

    }
    else {
      digitalWrite(ain1, LOW);
      digitalWrite(ain2, LOW);
      digitalWrite(bin1, LOW);
      digitalWrite(bin2, LOW);
      // disable DRV8833, conserve power
      digitalWrite(slp, LOW);
    }
  }

  delay(500);
}
