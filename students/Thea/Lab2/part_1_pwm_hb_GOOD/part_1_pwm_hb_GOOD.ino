//homebrew pwm for Lab 2

//constants

const int LED = 9;

const int period = 10000; //us
const int resolution = 10; //us

int dutycycle = 0;         //<-- have duty cycle start at 0

//pwm function
void pwmhb(int pin, double duty, double duration){
  //stuff that the duty cycle input affects 
  duty = constrain(duty, 0, 255);
  //on and off times
  int tON = (duty / 255) * period;
  int tOFF = period - tON;

  //stuff that the duration time (in seconds) input affects --> number of cycles 
  int cycles = (duration * 1000000) / period;

  //put this in here instead of outside because not picking the pin until using the function
  pinMode(pin, OUTPUT);

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

  //tell arduino to do the function with the arguments chosen
  //pwmhb(9, 0.25, 0.1); //<-- example given in lab handout
  pinMode(LED, OUTPUT);
}



void loop() {

  for (dutycycle = 0; dutycycle < 256; dutycycle++){
    digitalWrite(LED, dutycycle);
    delayMicroseconds(7800);      //<-- 2 s / 256 steps = ~7.8 ms/step

    pwmhb(LED, dutycycle, 2);        //<-- does this need to be in here or outside of the for loop?

  }

  digitalWrite(LED, 0);
  delay(10);                  //<-- small delay for drop

  //pwmhb(LED, duty, 2);
}
