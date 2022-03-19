#include <avr/io.h>
#include <util/delay.h> 

#include <avr/io.h>
#include <util/delay.h> 

//Button 1
#define BUTTON_PIN PINB  
#define BUTTON PB0 
#define LED_DDR DDRB 
#define LED_PORT PORTB
#define BUTTON_PORT PORTB
#define DEBOUNCE_TIME 10


//Button 2 
#define BUTTON_PIN_2 PIND  
#define BUTTON_2 PD2  
#define LED_DDR_2 DDRD 
#define LED_PORT_2 PORTD
#define BUTTON_PORT_2 PORTD
#define DEBOUNCE_TIME 10

// Debounce function for button 1 
uint8_t debounce1(void) {
 if (bit_is_clear(BUTTON_PIN, BUTTON)) { /* button is pressed now */
 _delay_us(DEBOUNCE_TIME);
 if (bit_is_clear(BUTTON_PIN, BUTTON)) { /* still pressed */
 return (1);
 }
 }
 return (0);
}

//Debounce function for part 2 
uint8_t debounce2(void) {
 if (bit_is_clear(BUTTON_PIN_2, BUTTON_2)) { /* button is pressed now */
 _delay_us(DEBOUNCE_TIME);
 if (bit_is_clear(BUTTON_PIN_2, BUTTON_2)) { /* still pressed */
 return (1);
 }
 }
 return (0);
}



int main(void) {
  
  // ------ Inits ------- //
  uint8_t buttonWasPressed; 
  BUTTON_PORT |= (1 << BUTTON); 
  LED_DDR = 0b00111100; 

  uint8_t buttonWasPressed2; 
  BUTTON_PORT_2 |= (1 << BUTTON_2); 
  LED_DDR_2 = 0b11110000;

  int count = 0; 
  int state = 0; 

  //------- Loop --------- // 

  while(1) {

   //button 1 code - runs the left bank of LEDS's 
  if(debounce1()) {
    state = 1; 
    
    if(buttonWasPressed == 0) { 
      
      if(count < 4 && state == 1){

        _delay_ms(1000);

        if(debounce1()){
          state = 2; 
        }

        
      
        //Test each of the lED's
    
        LED_PORT = (0b00000100 << count); 
        _delay_ms(200);

     
        
        count+=1;

    
        }

       else{
        PORTB = 0b00000000; 
        _delay_ms(1000);
        count = 0; 
        }
        
      buttonWasPressed = 1; 
    }
  }
  
  else{
    buttonWasPressed = 0; 
  }

  //button 2 runs the right bank of LEDs

  if(debounce2()) {
    state = 2;
    if(buttonWasPressed2 == 0) {
      if(count < 4 && state == 2){
     
        //Test each of the lED's
    
        LED_PORT_2 = (0b10000000 >> count); 
        _delay_ms(500);
    
        count+=1;
    
        }

       else{
        LED_PORT_2 = 0b00000000; 
        _delay_ms(1000);
        count = 0; 
        }
        
      buttonWasPressed2 = 1; 
    }
  }
  else{
    buttonWasPressed2 = 0; 
  }
      
       
    
    
}


return(0); 

}
