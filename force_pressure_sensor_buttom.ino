const int led_pin = 6;
const int fsr_pin = A0;
int stage = 0; 

void setup()
{
  pinMode(fsr_pin, INPUT);
  pinMode(led_pin, OUTPUT);
}

void loop()
{
  int fsr_value = analogRead(fsr_pin);
  if(fsr_value == 0 and stage == 0){
      
  }
  else if(fsr_value != 0 and stage == 0){
      int led_value = map(fsr_value, 0, 1023, 0, 255); 
      Serial.print("Force pressure analog read: ");
      Serial.println(fsr_value);
      Serial.print("Mapping analog write: ");
      Serial.println(led_value);
      Serial.println("data transmit !");
      analogWrite(led_pin, led_value); 
      stage = 1;
   }
  else if(fsr_value != 0 and stage == 1){
      int led_value = map(fsr_value, 0, 1023, 0, 255); 
      Serial.print("Force pressure analog read: ");
      Serial.println(fsr_value);
      Serial.print("Mapping analog write: ");
      Serial.println(led_value);
      Serial.println("data transmit !");
      analogWrite(led_pin, led_value); 
   }
   else if(fsr_value == 0 and stage == 1){
      Serial.println("Force pressure value kept");
      Serial.println("No data transmit");
      stage = 2;
  }
  else if(fsr_value != 0 and stage == 2){
      Serial.println("Force pressure releasing");
      Serial.println("No data transmit");
      stage = 3;
  }
  else if(fsr_value == 0 and stage == 3){
      Serial.println("Force pressure released");
      Serial.println("data transmit");
      analogWrite(led_pin, 0);
      stage = 0; 
  }
  delay(300);
}
