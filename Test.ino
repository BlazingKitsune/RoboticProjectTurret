#include <Stepper.h>
#include "SR04.h"
#include <Servo.h>

#define TRIG_PIN 12
#define ECHO_PIN 10 

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int rolePerMinute = 15;
const int X_pin = 1; // analog pin connected to X output
const int button1pin = 6;
const int button2pin = 7;
int button1State = 0;
int button2State = 0;
int state = 1;
int count = 0;

Servo myservo;
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

Stepper myStepper(stepsPerRevolution, 2, 4, 3, 5);
void setup() {
  myStepper.setSpeed(rolePerMinute);
  pinMode(button1pin, INPUT);
  pinMode(button2pin, INPUT);
  Serial.begin(9600);
  delay(1000);
  myservo.attach(9);//connect pin 9 with the control line(the orange line of Servo) 
  myservo.write(map(0,-60,60,0,100));
}

void loop() {
  button1State = digitalRead(button1pin);
  button2State = digitalRead(button2pin);
  if(button1State == HIGH)
  {
    while(button1State == HIGH)
    {
      button1State = digitalRead(button1pin);
    }
    if(state == 1)
    {
      state = 2;
    }
    else
    {
      state = 1;
    }

  }
  if(button2State == HIGH)
  {
    while(button2State == HIGH)
    {
      button2State = digitalRead(button2pin);
    }
    Serial.println("SHOOOOOT!!!!!!!!!\n");
    myservo.write(map(180,-60,100,0,100));
    delay(1000);
    myservo.write(map(0,-60,60,0,100));
    delay(1000);
    
  }

  if(state == 2)
  {
    int a = analogRead(X_pin);
    if (a > 400 && a < 520)
    {
      for (int i = 2; i < 6; i++)
      {
        digitalWrite(i, LOW);
      }
    }
    else if (a < 400)
    {
      Serial.println("Opening..");
      myStepper.setSpeed(rolePerMinute);
      myStepper.step(-30);
    }
    else if (a > 530)
    {
      Serial.println("Opening..");
      myStepper.setSpeed(rolePerMinute);
      myStepper.step(30);
    }
  }

  if(state == 1)
  {
      count = 0;
      while(count <10)
      {
        if(button1State == HIGH)
        {
          while(button1State == HIGH)
          {
            button1State = digitalRead(button1pin);
          }
          if(state == 1)
          {
            state = 2;
          }
          else
          {
            state = 1;
          }

        }
        myStepper.setSpeed(rolePerMinute);
        myStepper.step(-30);
        delay(5);
        count++;
        if (sr04.Distance() < 30) 
        {
          Serial.println("SHOOOOOT!!!!!!!!!\n");
          myservo.write(map(180,-60,100,0,100));
          delay(1000);
          myservo.write(map(0,-60,60,0,100));
          delay(1000);
        } 
        a=sr04.Distance();
        Serial.print(a);
        Serial.println(" centimetres");//The difference between "Serial.print" and "Serial.println" 
        
      }
      
      count = 0;
      while(count <10)
      {
        if(button1State == HIGH)
        {
          while(button1State == HIGH)
          {
            button1State = digitalRead(button1pin);
          }
          if(state == 1)
          {
            state = 2;
          }
          else
          {
            state = 1;
          }

        }
        myStepper.setSpeed(rolePerMinute);
        myStepper.step(30);
        delay(5);
        count++;
        if (sr04.Distance() < 30) 
        {
          Serial.println("SHOOOOOT!!!!!!!!!\n");
          myservo.write(map(180,-60,100,0,100));
          delay(1000);
          myservo.write(map(0,-60,60,0,100));
          delay(1000);
        } 
        a=sr04.Distance();
        Serial.print(a);
        Serial.println(" centimetres");//The difference between "Serial.print" and "Serial.println" 
      }
    
  }
 
}

