#include <Servo.h>
//servo ft1017M
Servo myservo;

int servoPin = 6;     // 
int analogPin = 0;  // Le potentiomètre est connecté à la broche analogue A0
int val = 0;        // la variable qui stocke la valeur lue est mise à 0

void setup()
{
    myservo.attach(servoPin);
    Serial.begin(9600);
}

void loop()
{   int analogValue = analogRead(analogPin);
    val = analogValue*1.80/10.23 ;  //lecture de la valeur analogue (potentiomètre)

   // Serial.print("Analog:");
    //Serial.println(analogRead(analogPin));
    myservo.write(val); 
    //Serial.print("Val:");
    //Serial.println(val);
    
    delay(50); // Attendez 1 seconde
}