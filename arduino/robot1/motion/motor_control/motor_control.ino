#include <Wire.h>
#define R 3.9f
#define b 33
#define a 23

#define I2C_ADR 4

#define MOTOR_1 3
#define MOTOR_1_DIR 4
#define MOTOR_2 6 
#define MOTOR_2_DIR 7
#define MOTOR_3 9
#define MOTOR_3_DIR 8
#define MOTOR_4 11
#define MOTOR_4_DIR 12


int motors[4] = {MOTOR_1, MOTOR_2, MOTOR_3, MOTOR_4}; //zadaem massiv nomerov motorov
int motors_dir[4] = {MOTOR_1_DIR, MOTOR_2_DIR, MOTOR_3_DIR, MOTOR_4_DIR}; //zadaem massiv napravlenia 
int motor_speeds[4] = { 0, 0, 0, 0 };

uint8_t inbyte;
uint8_t msg[7];

//I2C message request handler
void returnMessage()
{
  int i = 0;
  while(0 < Wire.available())
  {
    inbyte = Wire.read();
    if (inbyte == 0xAA && i == 0)
      break;
    if (i >= 7)
    {
      Serial.println("Too many bytes in one message!");
      break;
    }
    msg[i] = inbyte;
    i++;
  }
  Motor_control (msg);
}

//Greeting Master by sending him 0xAA back
void sendGreeting()
{
  if (inbyte == 0xAA) {
     Wire.write(0xAA);
     Serial.println ("Connection established!");

     for (int i = 0; i < 4; i++)
         motor_speeds[i] = 0;
  }
  else
    Serial.println ("Master requested data, but I have no data to send!");
}

//Alpha and Omega
void Motor_control (uint8_t VelocityControl [7]) 
{
  int Vx, Vy, omega;  
  if (VelocityControl [1] == 0) 
      Vx = -VelocityControl [2];
  else
      Vx = VelocityControl [2];   
     
  if (VelocityControl [3] == 0)
     Vy = -VelocityControl [4];
  else
     Vx = VelocityControl[4];
     
  if (VelocityControl [5] == 0)
     omega = -VelocityControl [6];
  else
     omega = VelocityControl [6];
 

 //calculation speeds for each motor 
 if (VelocityControl [0] == 0xFF)
 {
  motor_speeds[0] = int((-b * omega + Vx) / R);
  motor_speeds[1] = int((-a * omega + Vy) / R);
  motor_speeds[2] = int((-a * omega - Vy) / R);
  motor_speeds[3] = int((-b * omega - Vx) / R);
 }

 
 for (int i = 0; i < 4; i++) {
     analogWrite (motors[i],abs(motor_speeds[i]));
     Serial.print (motor_speeds[i]); Serial.print (' ');
 }
 Serial.println();


    //rotation directions are fucked up because Timur is a fuckhead and cannot do manual work properly :)
    digitalWrite(MOTOR_1_DIR, (motor_speeds[0] < 0));
    digitalWrite(MOTOR_2_DIR, (motor_speeds[1] > 0));
    digitalWrite(MOTOR_3_DIR, (motor_speeds[2] < 0));
    digitalWrite(MOTOR_4_DIR, (motor_speeds[3] > 0));
    
    if (VelocityControl [0] == 0)
      for (int i = 0; i < 4; i++)
          digitalWrite (motors[i], LOW);
}



void setup() 
{
   for (int i = 0; i < 4; i++)
   {
     pinMode(motors[i], OUTPUT);
     pinMode(motors_dir[i], OUTPUT);
   }  

   
   Wire.begin(I2C_ADR);
   Serial.begin(9600);
   Serial.println("Hi!");
   
   Wire.onReceive(returnMessage);
   Wire.onRequest(sendGreeting);
}

void loop() 
{
  

}

