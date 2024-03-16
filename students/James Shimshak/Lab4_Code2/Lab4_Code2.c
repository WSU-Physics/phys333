// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#define LED_DDR_L               (DDRD)
#define LED_PORT_L              PORTD
#define DELAYTIME 85
#define LED_DDR_R               (DDRD)
#define LED_PORT_R              PORTD
#define LED_PORT_LB              (PORTD)
#define BUTTON_LB                  PB2
#define LED0_LB                   PD7
#define BUTTON_PORT_LB             PORTB
#define BUTTON_PIN_LB              PINB
#define BUTTON_DDR_LB              DDRB
#define LED_PORT_RB              (PORTD)
#define BUTTON_RB                  PB4
#define LED0_RB                   PD0
#define BUTTON_PORT_RB             PORTB
#define BUTTON_PIN_RB              PINB
#define BUTTON_DDR_RB              DDRB
#include <util/delay.h>
uint8_t debounce_L(void) {
  if (bit_is_clear(BUTTON_PIN_LB, BUTTON_LB)) {        
    _delay_us(DELAYTIME);
    if (bit_is_clear(BUTTON_PIN_LB, BUTTON_LB)) {            
      return (1);}}
  return 0;}
  uint8_t debounce_R(void) {
  if (bit_is_clear(BUTTON_PIN_RB, BUTTON_RB)) {      
    _delay_us(DELAYTIME);
    if (bit_is_clear(BUTTON_PIN_RB, BUTTON_RB)) {            
      return (1);}}
  return 0;}
int main(void){
  uint8_t I = 0;
  LED_DDR_L = 0xff;  
  LED_DDR_R = 0xff;  
  uint8_t buttonWasPressed_L = 0;                                 
  BUTTON_DDR_LB &= ~(1 << BUTTON_LB);      
  BUTTON_PORT_LB |= (1 << BUTTON_LB);     
  uint8_t buttonWasPressed_R = 0;                                 
  BUTTON_DDR_RB &= ~(1 << BUTTON_RB);      
  BUTTON_PORT_RB |= (1 << BUTTON_RB);     
  while (1) {    
    if (debounce_L()) {                       
    while(1){
      if (buttonWasPressed_L == 0) {             
        while(I < 9) {
          LED_PORT_L = (1 << I);
          _delay_ms(DELAYTIME);
          I = I + 1;}
        while( I >= 9){   
          I = 0;         
          LED_PORT_L = (1 << I);}} 
      if(debounce_L()) {
        return 0;}}}
    if (debounce_R()) {                        
    while(1) {
      if (buttonWasPressed_R == 0) {     
        I = 9;
        while(I > 0) {
          LED_PORT_R = (1 << I);
          _delay_ms(DELAYTIME);
          I = I - 1;}
        while( I <= 0){
          I = 9;
          LED_PORT_R = (1 << I);}}
        if (debounce_R())
{           return 0;}}}}}

