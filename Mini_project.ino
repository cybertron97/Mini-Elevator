#include <SPI.h>
#include "Ultrasonic.h"
#include <Stepper.h>

#define S 10           
#define C 0x40       
#define I 0x00 
#define shift 0x09   

const int stepsPerRevolution =  700;
const int stepsnorevolution =0; 
Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);
Ultrasonic ultrasonic(6);
const int level1 = A3;
const int level2 = A4; 
const int level3 = A2;
const int level1_LED = 7; 
const int level2_LED = 8; 
const int level3_LED = 9; 

 
int level1_state =0; 
int level2_state =0;
int level3_state=0;  
int lev1,lev2,lev3 =0 ;
int l1,l2,l3=0;

void SPIWrite(byte spiRegister, byte value)
{  
  digitalWrite(S,LOW);  
  SPI.transfer(C);  
  SPI.transfer(spiRegister); 
  SPI.transfer(value); 
  digitalWrite(S,HIGH);
  
}
void setup() {
  myStepper.setSpeed(60);
  Serial.begin(9600);
  pinMode(S,OUTPUT);
  digitalWrite(S,HIGH);
  delay(100);
  SPI.begin();
  SPIWrite(I,0x00); // Set all pins to OUTPUT
  SPIWrite(shift,0x00);   // Set all pins LOW
  pinMode(level1, INPUT);
  pinMode(level2, INPUT);
  pinMode(level3, INPUT);
  pinMode(level1_LED, OUTPUT); 
  pinMode(level2_LED, OUTPUT); 
  pinMode(level3_LED, OUTPUT); 
 }
 void clockwise()
 {
  myStepper.step(~stepsPerRevolution);
 }
 void counterclockwise()
 { 
  myStepper.step(stepsPerRevolution);
  
  }
  void stopMotor()
  {
    myStepper.step(00); 
  }

int ult()
{
  long RangeInCentimeters;
  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); 
    delay(100);
return RangeInCentimeters; 
  
  
  }
 void loop() {
   long RangeInCentimeters; 
    RangeInCentimeters=ult();
   level1_state = digitalRead(level1);
level2_state= digitalRead(level2); 
level3_state = digitalRead(level3); 
if (level1_state == HIGH) { lev1 =1; lev2=0; lev3 =0;  } 
if (level2_state == HIGH) { lev2=1;lev1=0; lev3 =0; }
if (level3_state==HIGH) {lev3=1; lev1=0; lev2=0; }
if (RangeInCentimeters >= 13)
{
  SPIWrite(shift,~0x4F);
 if(lev2)
{
  
  digitalWrite(level1_LED, LOW); 
  digitalWrite(level2_LED, HIGH); 
  digitalWrite(level3_LED, LOW);
  clockwise(); 
  if(RangeInCentimeters == 6 and RangeInCentimeters<13)
 {  
      stopMotor();
      SPIWrite(shift,~0x5B);
 }
}

 if(lev1) 
 {
  digitalWrite(level1_LED, HIGH); 
  digitalWrite(level2_LED, LOW); 
  digitalWrite(level3_LED, LOW);
  clockwise(); 
  if(RangeInCentimeters == 1 and RangeInCentimeters ==1)
 {  
      stopMotor();
      SPIWrite(shift,~0x06);
 }
  }
  
}
else if (RangeInCentimeters>=6 and RangeInCentimeters<13)//level2
{
  SPIWrite(shift,~0x5B);
  if(lev3)
{
  
  digitalWrite(level1_LED, LOW); 
  digitalWrite(level2_LED, LOW); 
  digitalWrite(level3_LED, HIGH);
  counterclockwise(); 
  if(RangeInCentimeters >13)
 {  
      stopMotor();
      SPIWrite(shift,~0x4F);
 }
}

 if(lev1) 
 {
  digitalWrite(level1_LED, HIGH); 
  digitalWrite(level2_LED, LOW); 
  digitalWrite(level3_LED, LOW);
  clockwise(); 
  if(RangeInCentimeters == 1 and RangeInCentimeters==1)
 {  
      stopMotor();
      SPIWrite(shift,~0x06);
 }
  }
  
} 
else if (RangeInCentimeters < 6 ) //level1
{
  SPIWrite(shift,~0x06);
   if(lev3)
{
  
  digitalWrite(level1_LED, LOW); 
  digitalWrite(level2_LED, LOW); 
  digitalWrite(level3_LED, HIGH);
  counterclockwise(); 
  if(RangeInCentimeters >13)
 {  
      stopMotor();
      SPIWrite(shift,~0x4F);
 }
}
    if(lev2)
{
  
  digitalWrite(level1_LED, LOW); 
  digitalWrite(level2_LED, HIGH); 
  digitalWrite(level3_LED, LOW);
  counterclockwise(); 
  if(RangeInCentimeters == 6 and RangeInCentimeters<13)
 {  
      stopMotor();
      SPIWrite(shift,~0x5B);
 }
}


}

}
