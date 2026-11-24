#include <Servo.h>
#include "Stepper.h"

Servo servo_hand;
int servo_hand_pin = 9;     // 

Servo servo_arm;

int servo_arm_pin = 6;


bool forward = true;



// Define number of steps per rotation:
const int stepsPerRevolution = 2048;

// Wiring:
// Pin 10 to IN1 on the ULN2003 driver
// Pin 11 to IN2 on the ULN2003 driver
// Pin 12 to IN3 on the ULN2003 driver
// Pin 13 to IN4 on the ULN2003 driver

// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepsPerRevolution, 10, 12, 11, 13);
bool serv_arm_dir = 0;
float serv_arm_val = 9;
unsigned long serv_arm_deb = 0;

bool serv_hand_dir = 0;
float serv_hand_val = 2; 
unsigned long serv_hand_deb = 0;

bool motorState = false;
int motorDirection = 1;

const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int buttonPin4 = 4;
const int buttonPin5 = 5;




unsigned long debounce2 = 0;
unsigned long debounce3 = 0;
unsigned long debounce4 = 0;
unsigned long debounce5 = 0;




void setup() {
      Serial.begin(9600);
      servo_hand.attach(servo_hand_pin);
      //
      
      servo_arm.attach(servo_arm_pin);

      servo_arm.write(serv_arm_val);
      servo_hand.write(serv_hand_val);

      myStepper.setSpeed(5);
      pinMode(buttonPin2, INPUT_PULLUP); //change direction of servo-arm
      pinMode(buttonPin3, INPUT_PULLUP);  //change direction of servo-hand
      pinMode(buttonPin4, INPUT_PULLUP);  //stop the stepmotor
      pinMode(buttonPin5, INPUT_PULLUP);  //change direction of stepmotor

}

void loop() {

  //code for servo_arm
   if (digitalRead(buttonPin2) == LOW && (millis() - debounce2) > 500) {
    serv_arm_dir = !serv_arm_dir;
    debounce2 = millis();
    Serial.println(serv_arm_dir ? "Serv_arm forward" : "Serv_arm backward");
    }
    if(serv_arm_val<130 and serv_arm_dir){
      if ((millis() - serv_arm_deb) > 100){
      serv_arm_val = serv_arm_val + 2;
      servo_arm.write(serv_arm_val);
   
      serv_arm_deb = millis();
    }
    }
    if(serv_arm_val>10 and !serv_arm_dir){
      if ((millis() - serv_arm_deb) > 100){
      serv_arm_val = serv_arm_val - 2;
      servo_arm.write(serv_arm_val); 
      

      serv_arm_deb = millis();
    }
    }
    //code for servo_hand
   if (digitalRead(buttonPin3) == LOW && (millis() - debounce3) > 500) {
    serv_hand_dir = !serv_hand_dir;
    debounce3 = millis();
    Serial.println(serv_hand_dir ? "Serv_hand opening" : "Serv_hand closing");
    }
    if(serv_hand_val <= 110 and serv_hand_dir){
      if ((millis() - serv_hand_deb) > 100){
      serv_hand_val = serv_hand_val + 2;
      servo_hand.write(serv_hand_val); 
      serv_hand_deb = millis();
    }
    }

    if(serv_hand_val >= 2 and !serv_hand_dir){
      if ((millis() - serv_hand_deb) > 100){
      serv_hand_val = serv_hand_val - 2;
      servo_hand.write(serv_hand_val);
      serv_hand_deb = millis();
    }
    }


    //code for stepmotor
    if (digitalRead(buttonPin4) == LOW && (millis() - debounce4) > 500) {
    motorState = !motorState;
    debounce4 = millis();
    Serial.println(motorState ? "Motor ON" : "Motor OFF");
    }
    if (motorState) {
      myStepper.step(motorDirection);
    }
    else{
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
  }

    if (digitalRead(buttonPin5) == LOW && (millis() - debounce5) > 500) {
      motorDirection = -motorDirection;
      debounce5 = millis();
    }


}
