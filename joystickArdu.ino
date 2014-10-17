const int ledPin =  13;
unsigned long previousMillis = 0;
long interval = 1000;
int ledState = LOW;


long controlVector[4];
void setup()  
{ 
  Serial.begin(57600); 
  pinMode(ledPin, OUTPUT);
  for(int i = 0; i < 4; i++){
    controlVector[i] = 0;
  }
}

void loop() 
{
  String content = "";
  if (Serial.available()) {    
    content = Serial.readStringUntil(']');  

    for(int i = 0; i < 4; i++){
      int index = content.indexOf(",");
      controlVector[i] = atol(content.substring(0,index).c_str());
      content = content.substring(index+1);
    }  
  }
  
  blinker();
}

void processSerialData(){
  interval = controlVector[0];  
}

void debugSerial(){
  Serial.print(controlVector[0]);  
  Serial.print(',');  
  Serial.print(controlVector[1]);  
  Serial.print(',');  
  Serial.print(controlVector[2]);  
  Serial.print(',');  
  Serial.print(controlVector[3]);  
  //Serial.print('\n'); 
}

void blinker(){
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }

}










