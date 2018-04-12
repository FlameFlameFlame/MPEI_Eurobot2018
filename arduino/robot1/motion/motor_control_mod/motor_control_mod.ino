#include <Wire.h>
#define R 3.9f
#define L 30

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
uint8_t VelocityControl1 [7] = {0xFF, 1, 30, 0, 0, 0, 0};
uint8_t VelocityControl2 [7] = {0xFF, 0, 30, 0, 0, 0, 0};
uint8_t VelocityControl3 [7] = {0xFF, 0, 0, 1, 30, 0, 0};
uint8_t VelocityControl4 [7] = {0xFF, 1, 0, 0, 30, 0, 0};
uint8_t VelocityControl5 [7] = {0xFF, 1, 0, 0, 0, 1, 30};
uint8_t VelocityControl6 [7] = {0xFF, 1, 0, 0, 0, 0, 30};
uint8_t VelocityControl7 [7] = {0xFF, 1, 255, 1, 255, 0, 0};

//I2C message request handler
/*void returnMessage()
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
*/
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
      Vy = VelocityControl[4];
     
  if (VelocityControl [5] == 0)
     omega = -VelocityControl [6];
  else
     omega = VelocityControl [6];
 

 //calculation speeds for each motor 
 if (VelocityControl [0] == 0xFF)
 {
   if ((Vx > 0) && (Vy > 0))
   {
  motor_speeds[0] = int(sqrt(pow(Vx,2)+pow(Vy,2)-2*omega*L*(Vy*cos(2.35619)-Vx*sin(2.35619))+pow(omega,2)*pow(L,2)) / R);
  motor_speeds[1] = 0;
  motor_speeds[2] = int(sqrt(pow(Vx,2)+pow(Vy,2)-2*omega*L*(Vy*cos(3.92699)-Vx*sin(3.92699))+pow(omega,2)*pow(L,2)) / R);
  motor_speeds[3] = 0;
   }
   if ((Vx < 0) && (Vy < 0))
   {
   motor_speeds[0] = int(sqrt(pow(Vx,2)+pow(Vy,2)-2*omega*L*(Vy*cos(2.35619)-Vx*sin(2.35619))+pow(omega,2)*pow(L,2)) / R);
   motor_speeds[1] = 0;
   motor_speeds[2] = int(sqrt(pow(Vx,2)+pow(Vy,2)-2*omega*L*(Vy*cos(3.92699)-Vx*sin(3.92699))+pow(omega,2)*pow(L,2)) / R);
   motor_speeds[3] = 0;
   }
   if ((Vx > 0) && (Vy < 0))
   {
   motor_speeds[0] = 0;
   motor_speeds[1] = int(sqrt(pow(Vx,2)+pow(Vy,2)-2*omega*L*(Vy*cos(0.785398)-Vx*sin(0.785398))+pow(omega,2)*pow(L,2)) / R);
   motor_speeds[2] = 0;
   motor_speeds[3] = int(sqrt(pow(Vx,2)+pow(Vy,2)-2*omega*L*(Vy*cos(5.49779)-Vx*sin(5.49779))+pow(omega,2)*pow(L,2)) / R);
   }
   if ((Vx < 0) && (Vy > 0))
   {
   motor_speeds[0] = 0;
   motor_speeds[1] = int(sqrt(pow(Vx,2)+pow(Vy,2)-2*omega*L*(Vy*cos(0.785398)-Vx*sin(0.785398))+pow(omega,2)*pow(L,2)) / R);
   motor_speeds[2] = 0;
   motor_speeds[3] = int(sqrt(pow(Vx,2)+pow(Vy,2)-2*omega*L*(Vy*cos(5.49779)-Vx*sin(5.49779))+pow(omega,2)*pow(L,2)) / R);
   }
   if ((Vx == 0) || (Vy == 0))
   {
  motor_speeds[0] = int(sqrt(pow(Vx,2)+pow(Vy,2)-2*omega*L*(Vy*cos(2.35619)-Vx*sin(2.35619))+pow(omega,2)*pow(L,2)) / R);
  motor_speeds[1] = int(sqrt(pow(Vx,2)+pow(Vy,2)-2*omega*L*(Vy*cos(0.785398)-Vx*sin(0.785398))+pow(omega,2)*pow(L,2)) / R);
  motor_speeds[2] = int(sqrt(pow(Vx,2)+pow(Vy,2)-2*omega*L*(Vy*cos(3.92699)-Vx*sin(3.92699))+pow(omega,2)*pow(L,2)) / R);
  motor_speeds[3] = int(sqrt(pow(Vx,2)+pow(Vy,2)-2*omega*L*(Vy*cos(5.49779)-Vx*sin(5.49779))+pow(omega,2)*pow(L,2)) / R); 
 }
}
 
 for (int i = 0; i < 4; i++) 
   analogWrite (motors[i],map(abs(motor_speeds[i]),0,65,0,255));
   //  Serial.print (motor_speeds[i]); Serial.print (' ');
// }
// Serial.println();


    //rotation directions are fucked up because Timur is a fuckhead and cannot do manual work properly :
    
    digitalWrite(MOTOR_1_DIR, (((Vx == 0) && (Vy > 0)) || ((Vx > 0) && (Vy > 0)) || ((Vx > 0) && (Vy == 0))));
    digitalWrite(MOTOR_2_DIR, (((Vx == 0) && (Vy > 0)) || ((Vx < 0) && (Vy == 0)) || ((Vx < 0) && (Vy > 0))));
    digitalWrite(MOTOR_3_DIR, (((Vx == 0) && (Vy > 0)) || ((Vx > 0) && (Vy > 0)) || ((Vx > 0) && (Vy == 0))));
    digitalWrite(MOTOR_4_DIR, (((Vx == 0) && (Vy > 0)) || ((Vx < 0) && (Vy == 0)) || ((Vx < 0) && (Vy > 0))));
    
    if (VelocityControl [0] == 0)
      for (int i = 0; i < 4; i++)
          digitalWrite (motors[i], LOW);
}



void setup() 
{ 
  //Serial.print(motors_dir[1]);
   for (int i = 0; i < 4; i++)
   {
     pinMode(motors[i], OUTPUT);
     pinMode(motors_dir[i], OUTPUT);
   }   
   Wire.begin(I2C_ADR);
   Serial.begin(9600);
   for (int i=0;i<4;i++){
      Serial.print(motor_speeds[i]); Serial.print(' '); }
      
   Serial.println('\n');
   Motor_control (VelocityControl7);
   //Serial.println("Hi!");
   
//   Wire.onReceive(returnMessage);
//   Wire.onRequest(sendGreeting);
}

void loop() 
{
  
}
