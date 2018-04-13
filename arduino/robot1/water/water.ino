#define CLEANSERVO 4
#define DIRTYSERVO 5
#define SHUTTERSERVO 6

#define ENDSTOPS 7
#define ENDSTOPS_ON_CONTACT LOW
#define MYADDRESS 8

#define CONTACT_ANSWER 0xFF;

#include <Servo.h>

Servo clean;
Servo dirty;
Servo shutter;

uint8_t request;

void readCommand()
{
  request = Wire.read();
}

void sendSomething() {
  if (request == 1) {
    while (digitalRead(ENDSTOPS) =! ENDSTOPS_ON_CONTACT) {
      Serial.print("Waiting for a contact. Endstop is ");
      Serial.println(digitalRead(ENDSTOPS));
    }
  byte answer = CONTACT_ANSWER;
  Wire.write(answer);
  }
}

void setup() {
  clean.attach(CLEANSERVO);
  dirty.attach(DIRTYSERVO);
  shutter.attach(SHUTTERSERVO);

  pinMode(ENDSTOPS, input);
  
  Wire.begin(MYADDRESS);
  Wire.onReceive(readCommand);
  Wire.onRequest()
}

void loop() {
  if (request == 0) {
    //TODO: write turning off sequence
  }
  else if (request == 1) { 
    //NOTHING TO DO, EVERYTHING IS WRITTEN IN INTERRUPTIONS
  }
  else if (request == 2) {
    Serial.println("Getting clean water");
    getCleadWater();
  }
  else if (request == 3) {
    Serial.println("Getting mixed water");
    getMixedWater();
  }
  else if (request == 4) {
    Serial.println("Flushing dirty water");
    flushDirtyWater();
  }
  else {
    Serial.println("Unknown command");
  }
}
