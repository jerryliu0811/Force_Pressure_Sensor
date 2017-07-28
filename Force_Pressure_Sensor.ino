#include <Bridge.h>

char pin13[2];
char valueStr[23];
int valueInt;

char incomming[2]={'\0'};
//int previous_incomming_D2=999;
//int previous_incomming_D3=999;
//int previous_incomming_D4=999;
//int previous_incomming_D5=999;
int previous_incomming_D6=999;
//int previous_incomming_D7=999;
//int previous_incomming_D8=999;
//int previous_incomming_D9=999;

char outcome[4];
int outcomming_A0=0;
//int outcomming_A1=0;
//int outcomming_A2=0;
//int outcomming_A3=0;
//int outcomming_A4=0;
//int outcomming_A5=0;

const int fsrPin = A0;
int fsrReading;

void setup() {
  pinMode(13,OUTPUT);
  //pinMode(2,OUTPUT);    
  //pinMode(3,OUTPUT);
  //pinMode(4,OUTPUT);    
  //pinMode(5,OUTPUT);    
  pinMode(6,OUTPUT);    
  //pinMode(7,OUTPUT);
  //pinMode(8,OUTPUT);    
  //pinMode(9,OUTPUT);        
  
  pinMode(fsrPin, INPUT);

  Bridge.begin();   // Pins 0 and 1 should be avoided as they are used by the Bridge library.
}

void loop() {
  Bridge.get("Reg_done",  pin13, 2);
  digitalWrite(13, atoi(pin13));

  Bridge.get("incomming_D6~PWM",  incomming, 2);
  if (atoi(incomming)!=previous_incomming_D6){
    previous_incomming_D6=atoi(incomming);
    Bridge.get("D6~PWM",  valueStr, 5);
    valueStr[4]='\0';
    valueInt = atoi(valueStr);
    analogWrite(6, valueInt); 
    Serial.print("Led Analog output = ");
    Serial.println(valueInt);     // the raw analog reading*/       
    Serial.println("----------");
  }
  
  fsrReading = analogRead(fsrPin);
  Serial.print("Force Pressure Analog reading = ");
  Serial.println(fsrReading);     // the raw analog reading*/
  int led_value = map(fsrReading, 0, 1023, 0, 255);
  itoa(led_value, valueStr, 10); 
  if(led_value > 0){
    Bridge.put("A0", valueStr);
    itoa( (outcomming_A0=outcomming_A0^1), outcome, 10);
    Bridge.put("outcomming_A0", outcome);
  }
  //Bridge.put("A0", valueStr);
  //itoa( (outcomming_A0=outcomming_A0^1), outcome, 10);
  //Bridge.put("outcomming_A0", outcome);

  delay(1000);
}
