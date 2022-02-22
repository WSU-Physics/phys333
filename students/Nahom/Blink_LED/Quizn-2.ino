const int FSR= 0;
float fsr_read;
float fsr_volt;
float fsr_resis;
float fsr_force;

float R1=10000.0;
float Vc= 5000.0;

void setup(){
  Serial.begin(9600);
  
}

void loop(){
  
  fsr_read=  analogRead(FSR);
  delay(10);
  
  Serial.println(fsr_read);
  
  fsr_volt= (fsr_read * 5000) /1023;
  //fsr_volt= map(fsr_read,0,1023,0,5000);
  
  fsr_resis = (R1*(Vc - fsr_read))/Vc;
  
  fsr_force=8.306/fsr_read;
  fsr_force= pow(fsr_force,0.6052)

  Serial.print("FSR voltage in mV =");
  Serial.println(fsr_volt);
  
  Serial.print("FSR Resistance =");                                   
  Serial.println(fsr_resis);
  
  Serial.print("FSR Force =");                                   
  Serial.println(fsr_force);

  }
