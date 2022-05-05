#include <IRremote.h>
int receiver_pin = 8;   

IRrecv receiver(receiver_pin); 
decode_results output;
 
void setup()
{
  Serial.begin(9600);
  receiver.enableIRIn();
  }
 
void loop() {
  if (receiver.decode(&output)) {
    unsigned int value = output.value;
    Serial.println(value); 
    receiver.resume(); 
  }
}
