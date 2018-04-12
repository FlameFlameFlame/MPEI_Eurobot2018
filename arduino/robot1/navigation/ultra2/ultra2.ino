#include <Ultrasonic.h>
#include <Wire.h>
#define  ULT1Trig 2
#define  ULT1Echo 3
#define  ULT2Trig 4
#define  ULT2Echo 5
#define  ULT3Trig 6
#define  ULT3Echo 7
#define  ULT4Trig 8
#define  ULT4Echo 9

Ultrasonic ultrasonic1(ULT1Trig,ULT1Echo);
Ultrasonic ultrasonic2(ULT2Trig,ULT2Echo);
Ultrasonic ultrasonic3(ULT3Trig,ULT3Echo);
Ultrasonic ultrasonic4(ULT4Trig,ULT4Echo);

byte ultras[4];

void Transfer ()
  {
    Wire.write(ultras, 4);            // отсылаемое значение  
  }

void setup() 
{
  Serial.begin (9600); // подключаем монитор порта
  Wire.begin(5);
  Wire.onRequest(Transfer); 
}

void loop() 
{   
  ultras[0] = map(ultrasonic1.distanceRead(),2,400,0,255);
  ultras[1] = map(ultrasonic2.distanceRead(),2,400,0,255);
  ultras[2] = map(ultrasonic3.distanceRead(),2,400,0,255);
  ultras[3] = map(ultrasonic4.distanceRead(),2,400,0,255);
  for (int i = 0; i < 4; i++)
  {
    Serial.print(ultras[i]);
    Serial.print(' ');
  
  }
  Serial.print('\n');
  delay(100);
}



