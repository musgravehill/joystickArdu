void setup()  
{ 
  Serial.begin(57600); 
}

void loop() 
{
  String content = "";
  if (Serial.available()) {    
    content = Serial.readStringUntil(']');    

    long data[4];
    for(int i = 0; i < 4; i++){
      int index = content.indexOf(",");
      data[i] = atol(content.substring(0,index).c_str());
      content = content.substring(index+1);
    }    

    Serial.print(data[0]);  
    Serial.print(',');  
    Serial.print(data[1]);  
    Serial.print(',');  
    Serial.print(data[2]);  
    Serial.print(',');  
    Serial.print(data[3]);  
    //Serial.print('\n');  

  }

}







