//homebrew pwm for Lab 2

//constants

const int LED = 9;

const int period = 10000; //us
const int resolution = 10; //us

int dutycycle = 0;         //<-- have duty cycle start at 0

//pwm function
void pwmhb(int pin, double duty, double duration){
  //stuff that the duty cycle input affects 
  duty = constrain(duty, 0, 199);
  //on and off times
  int tON = ((float)duty / 199.0) * period;
  int tOFF = period - tON;

  //stuff that the duration time (in seconds) input affects --> number of cycles 
  float cycles = (duration * 1000000) / period;

  //put this in here instead of outside because not picking the pin until using the function
  //pinMode(pin, OUTPUT);

  //repeat cycle based on duration time chosen
  for(int i = 0; i < cycles; i++){

    // turn LED ON
    if (tON > 0){
      digitalWrite(pin, HIGH);
      delayMicroseconds(tON);
    }

    // turn LED OFF
    if (tOFF > 0){
      digitalWrite(pin, LOW);
      delayMicroseconds(tOFF);
    }

  }

  // make it turn off at the end
  digitalWrite(pin, LOW);
}

void setup() {

  pinMode(LED, OUTPUT);
}



void loop() {

  for (dutycycle = 0; dutycycle < 200; dutycycle++){

    pwmhb(LED, dutycycle, 0.01);       //pwm function

  }

  digitalWrite(LED, 0);
  delay(10);                  //<-- small delay for drop

}
