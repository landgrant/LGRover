

/*
 * Test FlySky IBus interface on an Arduino Mega.
 *  Connect FS-iA6B receiver to Serial1.
 */
//#include <analogWrite.h>

#include "FlySkyIBus.h"


  
int rcCH1 = 0; // Left - Right
int rcCH2 = 0; // Forward - Reverse
int rcCH3 = 0; // Acceleration
int rcCH4 = 0; // Switch Control
int rcCH5 = 0; // Switch Control
int rcCH6 = 0; // Mode Control
int rcCH7 = 0; // Switch Control
int rcCH8 = 0; // Switch Control
int rcCH9 = 0; // Switch Control
int rcCH10 = 0; // Switch Control
int sWC = 0;
// LED Connection
//#define carLED 22
 int led = 13;
#define sWA 6
#define sWB 9
#define vRA 14
#define vRB 15
#define sWCa 10
#define sWCb 11
#define sWD 12

// Motor A Control Connections
#define pwmA 2
#define dir1 23
//#define in2A 14
 
// Motor B Control Connections
#define pwmB 3
#define dir2 22
//#define in2B 18


// Motor C Control Connections
const int pwmC = 4;
const int dir3 = 21;
//#define in2A 14
 
// Motor D Control Connections
const int pwmD =  5;
const int dir4 = 20;
//#define in2B 18

// Motor Speed Values - Start at zero
int MotorSpeedA = 0;
int MotorSpeedB = 0;
int MotorSpeedC = 0;
int MotorSpeedD = 0;
 
// Motor Direction Values - 0 = backward, 1 = forward
int MotorDirA = 1;
int MotorDirB = 1;
int MotorDirC = 1;
int MotorDirD = 1;
float accel = 0;
// Control Motor A
void mControlA(int mspeed, int mdir) {
 
  // Determine direction
  if (mdir == 0) {
    // Motor backward
    digitalWrite(dir1, LOW);
   // digitalWrite(dir2, HIGH);
  } else {
    // Motor forward
    digitalWrite(dir1, HIGH);
  //  digitalWrite(dir2, LOW);
  }
 
  // Control motor
  analogWrite(pwmA, mspeed);
 
}
 
// Control Motor B
void mControlB(int mspeed, int mdir) {
 
  // Determine direction
  if (mdir == 0) {
    // Motor backward
    digitalWrite(dir2, LOW);
   // digitalWrite(in2B, HIGH);
  } else {
    // Motor forward
    digitalWrite(dir2, HIGH);
  //  digitalWrite(in2B, LOW);
  }
 
  // Control motor
  analogWrite(pwmB, mspeed);
 
}


// Control Motor C
void mControlC(int mspeed, int mdir) {
  // Determine direction
  if (mdir == 0) {
    // Motor backward
    digitalWrite(dir3, LOW);
  } else {
    // Motor forward
    digitalWrite(dir3, HIGH);
  }
  // Control motor
  analogWrite(pwmC, mspeed);
 
}
// Control Motor D
void mControlD(int mspeed, int mdir) {
  // Determine direction
  if (mdir == 0) {
    // Motor backward
    digitalWrite(dir4, LOW);
  } else {
    // Motor forward
    digitalWrite(dir4, HIGH);
  }
  // Control motor
  analogWrite(pwmD, mspeed);
 
}

void setup() 
{
  Serial.begin(115200);
  Serial2.begin(115200);
  IBus.begin(Serial2);

    // Set all the motor control pins to outputs
   pinMode(led, OUTPUT);     

  pinMode(sWA, OUTPUT);
  pinMode(sWB, OUTPUT);
  pinMode(sWCa, OUTPUT);
  pinMode(sWCb, OUTPUT);
  pinMode(sWD, OUTPUT);
  pinMode(vRA, OUTPUT);
  pinMode(vRB, OUTPUT);
  //pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(pwmC, OUTPUT);
  pinMode(pwmD, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(dir3, OUTPUT);
  pinMode(dir3, OUTPUT);

  
}

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue) {
  uint16_t ch = IBus.readChannel(channelInput);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
 
}

void setSwitch(int ch,int s){
  if(ch==sWC){
       if(s==0){
      digitalWrite(sWCa,HIGH);
      digitalWrite(sWCb,HIGH);
    } else if(s==1){
       digitalWrite(sWCa,LOW);
      digitalWrite(sWCb,HIGH);
    } else if (s==2){
      
       digitalWrite(sWCa,HIGH);
      digitalWrite(sWCb,LOW);
    }
  
  } else {
  if(s==0){
    digitalWrite(ch,HIGH);
  } else {
     digitalWrite(ch,LOW);
  }
}
  

}

// Read the channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue) {
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void loop() 
{
   digitalWrite(led, HIGH);  
  IBus.loop();
// Cycle through first 5 channels and determine values
  // Print values to serial monitor
  // Note IBusBM library labels channels starting with "0"
/*
  for (byte i = 0; i < 4; i++) {
    int value = readChannel(i, -100, 100, 0);
    Serial.print("Ch");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(value);
    Serial.print(" | ");
  }

  // Print channel 6 (switch) boolean value
  Serial.print("Ch5: ");
  Serial.print(readSwitch(4, false));
  Serial.print(" | Ch6: ");
  Serial.print(readSwitch(5, false));
  Serial.println();
*/

// Get RC channel values
  rcCH1 = readChannel(0, -255, 255, 0);
  rcCH2 = readChannel(1, -255, 255, 0);
  rcCH3 = readChannel(2, 0, 100, 0);
  rcCH4 = readChannel(3, -100, 100, 0);
  rcCH5 =readChannel(4, 0, 155, 0);
  rcCH6 = readChannel(5, 0, 155, 0);
  rcCH7 = readChannel(6, 0, 1, 0);
  rcCH8 = readChannel(7, 0, 1, 0);
  rcCH9 = readChannel(8,0,2,0);

  rcCH10 = readChannel(9,0,1,0);
  

  //  Serial.println(rcCH9);
  // Print values to serial monitor for debugging
  
  Serial.print("Ch1 = ");
  Serial.print(rcCH1);
 
  Serial.print(" Ch2 = ");
  Serial.print(rcCH2);
 
  Serial.print(" Ch3 = ");
  Serial.print(rcCH3);
 
  Serial.print(" Ch4 = ");
  Serial.print(rcCH4);
  Serial.print(" ||| ");
 /*
  Serial.print(" Ch5 = ");
  Serial.print(rcCH5);
  //Serial.print(map(IBus.readChannel(4), 1000, 2000, 0, 100));
  Serial.print(" Ch6 = ");
  //Serial.print(map(IBus.readChannel(5), 1000, 2000, 0, 100));
  Serial.print(rcCH6);
  Serial.print(" Ch7 = ");
  Serial.print(rcCH7);
  Serial.print(" Ch8 = ");
  Serial.print(rcCH8);
  Serial.print(" Ch9 = ");
   Serial.print(rcCH9);
 
  Serial.print(" Ch10 = ");
  Serial.print(rcCH10);

  Serial.print(" ACTUALS: ");


  Serial.print("Ch1 = ");
  Serial.print(IBus.readChannel(0));
 
  Serial.print(" Ch2 = ");
  Serial.print(IBus.readChannel(1));
 
  Serial.print(" Ch3 = ");
  Serial.print(IBus.readChannel(2));
 
  Serial.print(" Ch4 = ");
  Serial.print(IBus.readChannel(3));
 
  Serial.print(" Ch5 = ");
  Serial.print(IBus.readChannel(4));
  Serial.print(" Ch6 = ");
  Serial.print(IBus.readChannel(5));
  Serial.print(" Ch7 = ");
  Serial.print(IBus.readChannel(6));
  Serial.print(" Ch8 = ");
  Serial.print(IBus.readChannel(7));
  Serial.print(" Ch9 = ");
  Serial.print(IBus.readChannel(8));
 
  Serial.print(" Ch10 = ");
  Serial.println(IBus.readChannel(9));

  */
  // Serial.println(IBus.readChannel(8), DEC);

  setSwitch(sWA,rcCH7);
  setSwitch(sWB,rcCH8);
  setSwitch(sWC,rcCH9);
  setSwitch(sWD,rcCH10);

  // Set speeds with channel 3 value
  if(abs(rcCH2)>0){
  MotorSpeedA = accel/100 * abs(rcCH2);
    MotorSpeedB = accel/100 * abs(rcCH2);
    MotorSpeedC = accel/100 * abs(rcCH2);
    MotorSpeedD = accel/100 * abs(rcCH2);
  } else {
    MotorSpeedA = 0;
  MotorSpeedB = 0;
  MotorSpeedC = 0;
  MotorSpeedD = 0;
  }
  // Normal Mode
 
    
   
    // Set forward/backward direction with channel 2 value
    if (rcCH2 >= 0) {
      //Forward
      MotorDirA = 1;
      MotorDirB = 0;
      MotorDirC = 1;
      MotorDirD = 0;
    //  Serial.println("Forward");
    } else {
      //Backward
      MotorDirA = 0;
      MotorDirB = 1;
      MotorDirC = 0;
      MotorDirD = 1;
  //    Serial.println("Backward");
    }
 
    // Add channel 2 speed
    accel = rcCH3;
    Serial.print("Accel=  ");
    Serial.print(accel/100);
    Serial.print(" | ");
  

       if (rcCH1 > 0) {
      if(rcCH1 >90 && abs(rcCH2) <10 ){
      //Right
      MotorDirA = 1;
      MotorDirB = 1;
      MotorDirC = 1;
      MotorDirD = 1;
     // Serial.println("Right");
     MotorSpeedA = MotorSpeedA + accel/100 * rcCH1;
    MotorSpeedB = MotorSpeedB + accel/100 * rcCH1;
    MotorSpeedC = MotorSpeedC + accel/100 * rcCH1;
    MotorSpeedD = MotorSpeedD + accel/100 * rcCH1;
      } else {
      MotorSpeedA = MotorSpeedA - rcCH1/100;
   MotorSpeedB = MotorSpeedB * .8069;
    MotorSpeedB = MotorSpeedB -  rcCH1/1001;
    MotorSpeedD = MotorSpeedD * .8069;
      }
    } 
    
       if (rcCH1 < 0) {
         if(abs(rcCH1) >90 && abs(rcCH2) <10 ){
      //Left
      MotorDirA = 0;
      MotorDirB = 0;
      MotorDirC = 0;
      MotorDirD = 0;
   //   Serial.println("Left");
      MotorSpeedA = MotorSpeedA - accel/100 * rcCH1;
    MotorSpeedB = MotorSpeedB - accel/100 * rcCH1;
    MotorSpeedC = MotorSpeedC - accel/100 * rcCH1;
    MotorSpeedD = MotorSpeedD - accel/100 * rcCH1;
         }  else {
   // MotorSpeedA = MotorSpeedA * .8069;
     MotorSpeedA = MotorSpeedA + rcCH1/100;
   // MotorSpeedC = MotorSpeedC * .8069;
    MotorSpeedB = MotorSpeedB + rcCH1/100;
         }
    }
    // Set left/right offset with channel 1 value
   // MotorSpeedA = MotorSpeedA - rcCH1;
   // MotorSpeedB = MotorSpeedB + rcCH1;
// MotorSpeedA = MotorSpeedA / 100 * 255;
 
  // Ensure that speeds are between 0 and 255
  MotorSpeedA = constrain(MotorSpeedA, 0, 255);
  MotorSpeedB = constrain(MotorSpeedB, 0, 255);
  MotorSpeedC = constrain(MotorSpeedC, 0, 255);
  MotorSpeedD = constrain(MotorSpeedD, 0, 255);
 
  //Drive Motors
  mControlA(MotorSpeedA, MotorDirA);
  mControlB(MotorSpeedB, MotorDirB);
  mControlC(MotorSpeedC, MotorDirC);
  mControlD(MotorSpeedD, MotorDirD);
 
  // Print speed values to serial monitor for debugging
  Serial.print("A Speed = ");
  Serial.print(MotorSpeedA);
  Serial.print(" | B Speed = ");
  Serial.print(MotorSpeedB);
  Serial.print(" | C Speed = ");
  Serial.print(MotorSpeedC);
  Serial.print(" | D Speed = ");
  Serial.print(MotorSpeedD);
  Serial.print(" | SWA = ");
  Serial.print(rcCH5);
  Serial.print(" | SWB = ");
  Serial.println(rcCH6);
  // Slight delay
  
  delay(50);
  //digitalWrite(led, LOW); 
  }
