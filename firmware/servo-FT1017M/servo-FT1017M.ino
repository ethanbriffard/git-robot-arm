#include <Servo.h>
//servo ft1017M
Servo myservo;

int servoPin = 6;     // 
int analogPin = 0;  // Le potentiomètre est connecté à la broche analogue A0
float val = 0;        // la variable qui stocke la valeur lue est mise à 0
bool forward = true;
unsigned long debounce = 0;
void setup()
{
    myservo.attach(servoPin);
    

}

void loop()
{   
  if(forward) {
    if ((millis() - debounce) > 100){
      val = val + 1;
      myservo.write(val); 
      debounce = millis();
      if(val>130) {
        forward = false;
      }
    }
    }
    else {
      if((millis() - debounce) > 100){
      val = 5;
      myservo.write(val); 
      debounce = millis();
      if(val<10) {
        //forward = true;
      }
    }
    }
  
  
    //int analogValue = analogRead(analogPin);
    //val = analogValue*1.80/10.23 ;  //lecture de la valeur analogue (potentiomètre)
    //myservo.write(val); 
    //delay(50); // Attendez 1 seconde
}