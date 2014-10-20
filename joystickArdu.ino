#include <Servo.h> 
String serialData;
long controlVector[4]; //ROVER_THR, ROVER_YAW, CAM_PAN, CAM_TILT

Servo servo_cam_pan;
Servo servo_cam_tilt;

void setup()  
{ 
  Serial.begin(115200);   
  for(int i = 0; i < 4; i++){
    controlVector[i] = 0;
  }
  servo_cam_pan.attach(9);
  servo_cam_tilt.attach(10);
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
    //debugSerial();   
    processSerialData();
    normalizeControlVector();
    //debugControlVector();
    makeControlIteration();    
  }  
}

void processSerialData(){
  for(int i = 0; i < 4; i++){
    int index = serialData.indexOf(",");
    controlVector[i] = atol(serialData.substring(0,index).c_str());
    serialData = serialData.substring(index+1);
  }       
}

void normalizeControlVector(){
  controlVector[0] = map(controlVector[0], 0, 1000, 0, 180); //ROVER_THR  0..180
  controlVector[1] = map(controlVector[1], 0, 1000, 0, 180); //ROVER_YAW  0..180
  controlVector[2] = map(controlVector[2], 0, 1000, 0, 180); //CAM_PAN  0..180
  controlVector[3] = map(controlVector[3], 0, 1000, 0, 180); //CAM_TILT  0..180
}

void makeControlIteration(){

  servo_cam_pan.write(controlVector[2]); 
  servo_cam_tilt.write(controlVector[3]);  
}

void debugSerial(){
  Serial.println(serialData);  
}

void debugControlVector(){
  Serial.print(controlVector[0]);  
  Serial.print(',');  
  Serial.print(controlVector[1]);  
  Serial.print(',');  
  Serial.print(controlVector[2]);  
  Serial.print(',');  
  Serial.print(controlVector[3]);  
  Serial.print('\n');   
}

/*
void blinker(){ //DEBUG  
 const int ledPin =  13; //DEBUG
 unsigned long previousMillis = 0; //DEBUG
 long interval = 1000; //DEBUG
 int ledState = LOW; //DEBUG
 pinMode(ledPin, OUTPUT);   
 
 interval = map(controlVector[3], 0, 180, 0, 3000); //DEBUG
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
 */


















