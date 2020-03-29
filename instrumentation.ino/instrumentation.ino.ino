/*
 * instrumentation.ino
 * #0x05 
 *
 * Created : 02/01/2020
 * Author  : lialia
 * Email   : 074bex409.basanta@pcampus.edu.np
 */

 //Indicator LEDs
 #define indicator_wet  6
 #define indicator_cry  7
 #define indicator_notcry  8
 #define indicator_emergency  9

 //Motor Control
 #define motor  A0

 //Moisture Sensor
 #define moisture_sensor A4

 //Pi Interface
 #define from_pi 4 

 //Temp variables
 int i = 0;

void setup() {

  //Initialize Indicators
  pinMode(indicator_wet,OUTPUT);
  pinMode(indicator_cry,OUTPUT);
  pinMode(indicator_notcry,OUTPUT);
  pinMode(indicator_emergency,OUTPUT);
  digitalWrite(indicator_wet,LOW);
  digitalWrite(indicator_cry,LOW);
  digitalWrite(indicator_notcry,HIGH);
  digitalWrite(indicator_emergency,LOW);

  //Initialize Moisture Sensor
  pinMode(moisture_sensor,OUTPUT);

  //Initialize Motor
  pinMode(motor,OUTPUT);

  //Initialize Pi Interface
  pinMode(from_pi,INPUT);

  Serial.begin(9600);
}

void loop() {
  if(digitalRead(from_pi))
  {
    digitalWrite(indicator_cry,HIGH);
    digitalWrite(indicator_notcry,LOW);
    digitalWrite(motor,HIGH);
    Serial.println("Baby is Crying");
    i++;
    if(i>3) 
    {
      i=0;
      digitalWrite(indicator_emergency,HIGH);
      Serial.println("Alert!!! Its Emerency");
    }
    
    while(digitalRead(from_pi)) {}
    
    digitalWrite(indicator_cry,LOW);
    digitalWrite(indicator_notcry,HIGH);
    digitalWrite(motor,LOW);
    Serial.println("Baby is Not Crying");
  }
}

bool isMoist()
{
//  Serial.println("moist");
  unsigned int cnt1 = 0;
  unsigned int cnt0 = 0;
  while(!digitalRead(moisture_sensor)) {}
  while(digitalRead(moisture_sensor))
  {
    if(cnt1<200) cnt1++;
  }
  while(!digitalRead(moisture_sensor))
  {
    if(cnt0<200) cnt0++;
  }
  if(cnt1+cnt0 != 400) return true;
  else                 return false;
}
