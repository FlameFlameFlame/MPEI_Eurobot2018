#include <Wire.h>
#define R 39
#define b 33
#define a 23
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

void Motor_control (int8_t VelocityControl [7]) //proschot uravneniy
{
  if (VelocityControl [2] == "-") 
     VelocityControl [3] = -VelocityControl [3];
     
  if (VelocityControl [4] == "-")
     VelocityControl [5] = -VelocityControl [5];
     
  if (VelocityControl [6] == "-")
     VelocityControl [7] = -VelocityControl [7];
     
 if (VelocityControl [1] == 1)
 {
  Omega_1 = (-b * VelocityControl [7] + VelocityControl [3]) / R;
  Omega_2 = (-a * VelocityControl [7] + VelocityControl [5]) / R;
  Omega_3 = (-a * VelocityControl [7] - VelocityControl [5]) / R;
  Omega_4 = (-b * VelocityControl [7] - VelocityControl [3]) / R;
 }
    analogWrite(MOTOR_1,map(0,Omega_1,0,255));
    analogWrite(MOTOR_2,map(0,Omega_2,0,255));
    analogWrite(MOTOR_3,map(0,Omega_3,0,255));
    analogWrite(MOTOR_4,map(0,Omega_4,0,255));
    digitalWrite(MOTOR_1_DIR, (Omega_1 < 0));
    digitalWrite(MOTOR_2_DIR, (Omega_2 > 0));
    digitalWrite(MOTOR_3_DIR, (Omega_3 < 0));
    digitalWrite(MOTOR_4_DIR, (Omega_4 > 0));
    if (VelocityControl [1] == 2)
      {
            analogWrite(MOTOR_1,0);
            analogWrite(MOTOR_2,0);
            analogWrite(MOTOR_3,0);
            analogWrite(MOTOR_4,0);
      }
}

void setup() 
{
   for (int i = 0; i <= 3; i++)
 {
   pinMode(motors[i], OUTPUT);
   pinMode(motors_dir[i], OUTPUT);
 }  
}
  Wire.begin(8);
  Wire.onReceive(Motor_control) 

}

void loop() 
{
  

}
//void motor_control (bool control, float V_x, float V_y, float omega)





  /*for(int i = 0; i <= 3; i++)
  {
    for(int j = 0; j <= 3; j++) //turning all motors off
    {
      digitalWrite(motors[j], LOW);
      digitalWrite(motors_dir[j], LOW);
    }
    digitalWrite(motors[i], HIGH);
    digitalWrite(motors_dir[i], HIGH);
    delay(1000);
  }*/

/*  //"forward"
  analogWrite(MOTOR_3, LOW);
  analogWrite(MOTOR_2, LOW);
  
  analogWrite(MOTOR_1, POWER);
  digitalWrite(MOTOR_1_DIR, LOW);
  analogWrite(MOTOR_4, POWER);
  digitalWrite(MOTOR_4_DIR, HIGH);
  delay(1000);

  //"left"
  analogWrite(MOTOR_1, LOW);
  analogWrite(MOTOR_4, LOW);
  
  analogWrite(MOTOR_2, POWER);
  digitalWrite(MOTOR_2_DIR, HIGH);
  analogWrite(MOTOR_3, POWER);
  digitalWrite(MOTOR_3_DIR, LOW);
  delay(1000);

  //"backwards"
  analogWrite(MOTOR_2, LOW);
  analogWrite(MOTOR_3, LOW);

  analogWrite(MOTOR_1, POWER)
  ;
  digitalWrite(MOTOR_1_DIR, HIGH);
  analogWrite(MOTOR_4, POWER);
  digitalWrite(MOTOR_4_DIR, LOW);
  delay(1000);

  //"right"
  analogWrite(MOTOR_1, LOW);
  analogWrite(MOTOR_4, LOW);

  analogWrite(MOTOR_3, POWER);
  digitalWrite(MOTOR_2_DIR, LOW);
  analogWrite(MOTOR_2, POWER);
  digitalWrite(MOTOR_3_DIR, HIGH);
  delay(1000);

  //"left-forward"
  digitalWrite(MOTOR_1_DIR, LOW);
  digitalWrite(MOTOR_4_DIR, HIGH);
*/
  
  

