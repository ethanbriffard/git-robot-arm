//be carefull some wires are not working well




// Include the Arduino Stepper.h library:
#include "Stepper.h"

// Define number of steps per rotation:
const int stepsPerRevolution = 2048;

// Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver

// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

bool motorState = false;
int motorDirection = 1;

const int buttonPin2 = 2;
const int buttonPin3 = 3;

unsigned long debounce2=0;
unsigned long debounce3=0;



void setup() {
  // Set the speed between 4 and 12 rpm included:
  myStepper.setSpeed(10);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);
}

void loop() {
  // Step one revolution in one direction:
  //Serial.println("clockwise");
  //myStepper.step(stepsPerRevolution/8);
  //delay(500);
  
  // Step one revolution in the other direction:
  //Serial.println("counterclockwise");
  //myStepper.step(-stepsPerRevolution/8);
  //delay(500);

  if (digitalRead(buttonPin2) == LOW && (millis() - debounce2) > 500) {
    motorState = !motorState;
    debounce2 = millis();
    Serial.println(motorState ? "Motor ON" : "Motor OFF");
    }
  if (motorState) {
    myStepper.step(motorDirection);
  }
  else{
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }

if (digitalRead(buttonPin3) == LOW && (millis() - debounce3) > 500) {
    motorDirection = -motorDirection;
    debounce3 = millis();
    Serial.print("Motor direction = ");
    Serial.println(motorDirection);
  }
}


