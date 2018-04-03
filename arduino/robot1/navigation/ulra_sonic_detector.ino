#include <Ultrasonic.h>
#include <Wire.h>
#define ir A0 //пин, к которому подключен датчик. Обязательно аналоговый!
#define model 20150 //модель датчика. 1080 для GP2Y0A21Y, 20150 для GP2Y0A02Y

Ultrasonic ULTRAs[ultrasonic1(), ultrasonic2(), ultrasonic3(), ultrasonic4()];

void obstacle_evade (float ULTRAs[4], byte obstacle[4])
  {
    for (int i = 1; i <= 4; i++)
    {
      if ULTRAs[i] < 6
        obstacle[i] = 1;
      else
        obstacle[i] = 0;
    }
  }

void setup() 
{
  byte obstacle[0, 0, 0, 0];
  Serial.begin (9600); // подключаем монитор порта
  Wire.begin(5);
}

void loop() {
  
  
 //  Serial.print("ULTRASONIC: ");
  // Pass INC as a parameter to get the distance in inches
  float ULTRAs[1] = ultrasonic1.digitalRead();
  float ULTRAs[2] = ultrasonic2.digitalRead();
  float ULTRAs[3] = ultrasonic3.digitalRead();
  float ULTRAs[4] = ultrasonic4.digitalRead();
 // Serial.println(ULTRASONIC);
 // Serial.print("AMP: ");  // выводим расстояние в монитор порта
 // Serial.println(AMP);
 // delay(1000);
 obstacle_evade (ULTRAs, obstacle);
 Wire.write (obstacle);
 
}

 

