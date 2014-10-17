const int ledPin =  13;
unsigned long previousMillis = 0;
long interval = 1000;
int ledState = LOW;

String serialData;
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
  char serialByte;
  boolean isSerialDataReady = false;    

  while(Serial.available()) {
    serialByte = Serial.read();
    if(serialByte == '['){
      isSerialDataReady = false;
    }
    else if(serialByte == ']') {
      isSerialDataReady = true;      
      break; // Break out of the while loop
    }
    else {
      serialData += String(serialByte); 
      isSerialDataReady = false;
    }
  }

  if(isSerialDataReady){      
    processSerialData();
    makeControlIteration();
    //debugSerial();
  }

  blinker();
}

void processSerialData(){
  for(int i = 0; i < 4; i++){
    int index = serialData.indexOf(",");
    controlVector[i] = atol(serialData.substring(0,index).c_str());
    serialData = serialData.substring(index+1);
  }       
}

void makeControlIteration(){
  interval = controlVector[3]; 
}

void debugSerial(){
  Serial.println(serialData);
  Serial.print(controlVector[0]);  
  Serial.print(',');  
  Serial.print(controlVector[1]);  
  Serial.print(',');  
  Serial.print(controlVector[2]);  
  Serial.print(',');  
  Serial.print(controlVector[3]);  
  Serial.print('\n'); 
}

void blinker(){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {    
    previousMillis = currentMillis; 
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;    
    digitalWrite(ledPin, ledState);
  }
}














