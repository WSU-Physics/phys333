/*
   -------------------------------------------------------------------------------------
   HX711_ADC
   Arduino library for HX711 24-Bit Analog-to-Digital Converter for Weight Scales
   Olav Kallhovd sept2017
   -------------------------------------------------------------------------------------
*/

/*
   This example file shows how to calibrate the load cell and optionally store the calibration
   value in EEPROM, and also how to change the value manually.
   The result value can then later be included in your project sketch or fetched from EEPROM.

   To implement calibration in your project sketch the simplified procedure is as follow:
       LoadCell.tare();
       //place known mass
       LoadCell.refreshDataSet();
       float newCalibrationValue = LoadCell.getNewCalibration(known_mass);
*/



//#include <HX711_ADC.h>
#if defined(ESP8266)|| defined(ESP32) || defined(AVR)
#include <EEPROM.h>
#endif

/*
   -------------------------------------------------------------------------------------
   HX711_ADC
   Arduino library for HX711 24-Bit Analog-to-Digital Converter for Weight Scales
   Olav Kallhovd sept2017 
   -------------------------------------------------------------------------------------
*/

#ifndef HX711_ADC_h
#define HX711_ADC_h

#include <Arduino.h>
//#include "config.h"

/*
   -------------------------------------------------------------------------------------
   HX711_ADC
   Arduino library for HX711 24-Bit Analog-to-Digital Converter for Weight Scales
   Olav Kallhovd sept2017
   -------------------------------------------------------------------------------------
*/

/*
HX711_ADC configuration

Allowed values for "SAMPLES" is 1, 2, 4, 8, 16, 32, 64 or 128.
Higher value = improved filtering/smoothing of returned value, but longer setteling time and increased memory usage
Lower value = visa versa

The settling time can be calculated as follows:
Settling time = SAMPLES + IGN_HIGH_SAMPLE + IGN_LOW_SAMPLE / SPS

Example on calculating settling time using the values SAMPLES = 16, IGN_HIGH_SAMPLE = 1, IGN_LOW_SAMPLE = 1, and HX711 sample rate set to 10SPS:
(16+1+1)/10 = 1.8 seconds settling time.

Note that you can also overide (reducing) the number of samples in use at any time with the function: setSamplesInUse(samples).

*/

#ifndef HX711_ADC_config_h
#define HX711_ADC_config_h

//number of samples in moving average dataset, value must be 1, 2, 4, 8, 16, 32, 64 or 128.
#define SAMPLES 					16		//default value: 16

//adds extra sample(s) to the dataset and ignore peak high/low sample, value must be 0 or 1.
#define IGN_HIGH_SAMPLE 			1		//default value: 1
#define IGN_LOW_SAMPLE 				1		//default value: 1

//microsecond delay after writing sck pin high or low. This delay could be required for faster mcu's.
//So far the only mcu reported to need this delay is the ESP32 (issue #35), both the Arduino Due and ESP8266 seems to run fine without it.
//Change the value to '1' to enable the delay.
#define SCK_DELAY					0		//default value: 0

//if you have some other time consuming (>60μs) interrupt routines that trigger while the sck pin is high, this could unintentionally set the HX711 into "power down" mode
//if required you can change the value to '1' to disable interrupts when writing to the sck pin.
#define SCK_DISABLE_INTERRUPTS		0		//default value: 0

#endif


/*
Note: HX711_ADC configuration values has been moved to file config.h
*/

#define DATA_SET 	SAMPLES + IGN_HIGH_SAMPLE + IGN_LOW_SAMPLE // total samples in memory

#if (SAMPLES  != 1) & (SAMPLES  != 2) & (SAMPLES  != 4) & (SAMPLES  != 8) & (SAMPLES  != 16) & (SAMPLES  != 32) & (SAMPLES  != 64) & (SAMPLES  != 128)
	#error "number of SAMPLES not valid!"
#endif

#if (SAMPLES  == 1) & ((IGN_HIGH_SAMPLE  != 0) | (IGN_LOW_SAMPLE  != 0))
	#error "number of SAMPLES not valid!"
#endif

#if 		(SAMPLES == 1)
#define 	DIVB 0
#elif 		(SAMPLES == 2)
#define 	DIVB 1
#elif 		(SAMPLES == 4)
#define 	DIVB 2
#elif  		(SAMPLES == 8)
#define 	DIVB 3
#elif  		(SAMPLES == 16)
#define 	DIVB 4
#elif  		(SAMPLES == 32)
#define 	DIVB 5
#elif  		(SAMPLES == 64)
#define 	DIVB 6
#elif  		(SAMPLES == 128)
#define 	DIVB 7
#endif

#define SIGNAL_TIMEOUT	100

class HX711_ADC
{	
		
	public:
		HX711_ADC(uint8_t dout, uint8_t sck); 		//constructor
		void setGain(uint8_t gain = 128); 			//value must be 32, 64 or 128*
		void begin();								//set pinMode, HX711 gain and power up the HX711
		void begin(uint8_t gain);					//set pinMode, HX711 selected gain and power up the HX711
		void start(unsigned long t); 					//start HX711 and do tare 
		void start(unsigned long t, bool dotare);		//start HX711, do tare if selected
		int startMultiple(unsigned long t); 			//start and do tare, multiple HX711 simultaniously
		int startMultiple(unsigned long t, bool dotare);	//start and do tare if selected, multiple HX711 simultaniously
		void tare(); 								//zero the scale, wait for tare to finnish (blocking)
		void tareNoDelay(); 						//zero the scale, initiate the tare operation to run in the background (non-blocking)
		bool getTareStatus();						//returns 'true' if tareNoDelay() operation is complete
		void setCalFactor(float cal); 				//set new calibration factor, raw data is divided by this value to convert to readable data
		float getCalFactor(); 						//returns the current calibration factor
		float getData(); 							//returns data from the moving average dataset 

		int getReadIndex(); 						//for testing and debugging
		float getConversionTime(); 					//for testing and debugging
		float getSPS();								//for testing and debugging
		bool getTareTimeoutFlag();					//for testing and debugging
		void disableTareTimeout();					//for testing and debugging
		long getSettlingTime();						//for testing and debugging
		void powerDown(); 							//power down the HX711
		void powerUp(); 							//power up the HX711
		long getTareOffset();						//get the tare offset (raw data value output without the scale "calFactor")
		void setTareOffset(long newoffset);			//set new tare offset (raw data value input without the scale "calFactor")
		uint8_t update(); 							//if conversion is ready; read out 24 bit data and add to dataset
		bool dataWaitingAsync(); 					//checks if data is available to read (no conversion yet)
		bool updateAsync(); 						//read available data and add to dataset 
		void setSamplesInUse(int samples);			//overide number of samples in use
		int getSamplesInUse();						//returns current number of samples in use
		void resetSamplesIndex();					//resets index for dataset
		bool refreshDataSet();						//Fill the whole dataset up with new conversions, i.e. after a reset/restart (this function is blocking once started)
		bool getDataSetStatus();					//returns 'true' when the whole dataset has been filled up with conversions, i.e. after a reset/restart
		float getNewCalibration(float known_mass);	//returns and sets a new calibration value (calFactor) based on a known mass input
		bool getSignalTimeoutFlag();				//returns 'true' if it takes longer time then 'SIGNAL_TIMEOUT' for the dout pin to go low after a new conversion is started
		void setReverseOutput();					//reverse the output value

	protected:
		void conversion24bit(); 					//if conversion is ready: returns 24 bit data and starts the next conversion
		long smoothedData();						//returns the smoothed data value calculated from the dataset
		uint8_t sckPin; 							//HX711 pd_sck pin
		uint8_t doutPin; 							//HX711 dout pin
		uint8_t GAIN;								//HX711 GAIN
		float calFactor = 1.0;						//calibration factor as given in function setCalFactor(float cal)
		float calFactorRecip = 1.0;					//reciprocal calibration factor (1/calFactor), the HX711 raw data is multiplied by this value
		volatile long dataSampleSet[DATA_SET + 1];	// dataset, make voltile if interrupt is used 
		long tareOffset = 0;
		int readIndex = 0;
		unsigned long conversionStartTime = 0;
		unsigned long conversionTime = 0;
		uint8_t isFirst = 1;
		uint8_t tareTimes = 0;
		uint8_t divBit = DIVB;
		const uint8_t divBitCompiled = DIVB;
		bool doTare = 0;
		bool startStatus = 0;
		unsigned long startMultipleTimeStamp = 0;
		unsigned long startMultipleWaitTime = 0;
		uint8_t convRslt = 0;
		bool tareStatus = 0;
		unsigned int tareTimeOut = (SAMPLES + IGN_HIGH_SAMPLE + IGN_HIGH_SAMPLE) * 150; // tare timeout time in ms, no of samples * 150ms (10SPS + 50% margin)
		bool tareTimeoutFlag = 0;
		bool tareTimeoutDisable = 0;
		int samplesInUse = SAMPLES;
		long lastSmoothedData = 0;
		bool dataOutOfRange = 0;
		unsigned long lastDoutLowTime = 0;
		bool signalTimeoutFlag = 0;
		bool reverseVal = 0;
		bool dataWaiting = 0;
};	

#endif
   


//pins:
const int HX711_dout = 4; //mcu > HX711 dout pin
const int HX711_sck = 5; //mcu > HX711 sck pin

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long t = 0;

void setup() {
  Serial.begin(57600); delay(10);
  Serial.println();
  Serial.println("Starting...");

  LoadCell.begin();
  //LoadCell.setReverseOutput(); //uncomment to turn a negative output value to positive
  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag() || LoadCell.getSignalTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(1.0); // user set calibration value (float), initial value 1.0 may be used for this sketch
    Serial.println("Startup is complete");
  }
  while (!LoadCell.update());
  calibrate(); //start calibration procedure
}

void loop() {
  static boolean newDataReady = 0;
  const int serialPrintInterval = 0; //increase value to slow down serial print activity

  // check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t + serialPrintInterval) {
      float i = LoadCell.getData();
      Serial.print("Load_cell output val: ");
      Serial.println(i);
      newDataReady = 0;
      t = millis();
    }
  }

  // receive command from serial terminal
  if (Serial.available() > 0) {
    char inByte = Serial.read();
    if (inByte == 't') LoadCell.tareNoDelay(); //tare
    else if (inByte == 'r') calibrate(); //calibrate
    else if (inByte == 'c') changeSavedCalFactor(); //edit calibration value manually
  }

  // check if last tare operation is complete
  if (LoadCell.getTareStatus() == true) {
    Serial.println("Tare complete");
  }

}

void calibrate() {
  Serial.println("***");
  Serial.println("Start calibration:");
  Serial.println("Place the load cell an a level stable surface.");
  Serial.println("Remove any load applied to the load cell.");
  Serial.println("Send 't' from serial monitor to set the tare offset.");

  boolean _resume = false;
  while (_resume == false) {
    LoadCell.update();
    if (Serial.available() > 0) {
      if (Serial.available() > 0) {
        char inByte = Serial.read();
        if (inByte == 't') LoadCell.tareNoDelay();
      }
    }
    if (LoadCell.getTareStatus() == true) {
      Serial.println("Tare complete");
      _resume = true;
    }
  }

  Serial.println("Now, place your known mass on the loadcell.");
  Serial.println("Then send the weight of this mass (i.e. 100.0) from serial monitor.");

  float known_mass = 0;
  _resume = false;
  while (_resume == false) {
    LoadCell.update();
    if (Serial.available() > 0) {
      known_mass = Serial.parseFloat();
      if (known_mass != 0) {
        Serial.print("Known mass is: ");
        Serial.println(known_mass);
        _resume = true;
      }
    }
  }

  LoadCell.refreshDataSet(); //refresh the dataset to be sure that the known mass is measured correct
  float newCalibrationValue = LoadCell.getNewCalibration(known_mass); //get the new calibration value

  Serial.print("New calibration value has been set to: ");
  Serial.print(newCalibrationValue);
  Serial.println(", use this as calibration value (calFactor) in your project sketch.");
  Serial.print("Save this value to EEPROM adress ");
  Serial.print(calVal_eepromAdress);
  Serial.println("? y/n");

  _resume = false;
  while (_resume == false) {
    if (Serial.available() > 0) {
      char inByte = Serial.read();
      if (inByte == 'y') {
#if defined(ESP8266)|| defined(ESP32)
        EEPROM.begin(512);
#endif
        EEPROM.put(calVal_eepromAdress, newCalibrationValue);
#if defined(ESP8266)|| defined(ESP32)
        EEPROM.commit();
#endif
        EEPROM.get(calVal_eepromAdress, newCalibrationValue);
        Serial.print("Value ");
        Serial.print(newCalibrationValue);
        Serial.print(" saved to EEPROM address: ");
        Serial.println(calVal_eepromAdress);
        _resume = true;

      }
      else if (inByte == 'n') {
        Serial.println("Value not saved to EEPROM");
        _resume = true;
      }
    }
  }

  Serial.println("End calibration");
  Serial.println("***");
  Serial.println("To re-calibrate, send 'r' from serial monitor.");
  Serial.println("For manual edit of the calibration value, send 'c' from serial monitor.");
  Serial.println("***");
}

void changeSavedCalFactor() {
  float oldCalibrationValue = LoadCell.getCalFactor();
  boolean _resume = false;
  Serial.println("***");
  Serial.print("Current value is: ");
  Serial.println(oldCalibrationValue);
  Serial.println("Now, send the new value from serial monitor, i.e. 696.0");
  float newCalibrationValue;
  while (_resume == false) {
    if (Serial.available() > 0) {
      newCalibrationValue = Serial.parseFloat();
      if (newCalibrationValue != 0) {
        Serial.print("New calibration value is: ");
        Serial.println(newCalibrationValue);
        LoadCell.setCalFactor(newCalibrationValue);
        _resume = true;
      }
    }
  }
  _resume = false;
  Serial.print("Save this value to EEPROM adress ");
  Serial.print(calVal_eepromAdress);
  Serial.println("? y/n");
  while (_resume == false) {
    if (Serial.available() > 0) {
      char inByte = Serial.read();
      if (inByte == 'y') {
#if defined(ESP8266)|| defined(ESP32)
        EEPROM.begin(512);
#endif
        EEPROM.put(calVal_eepromAdress, newCalibrationValue);
#if defined(ESP8266)|| defined(ESP32)
        EEPROM.commit();
#endif
        EEPROM.get(calVal_eepromAdress, newCalibrationValue);
        Serial.print("Value ");
        Serial.print(newCalibrationValue);
        Serial.print(" saved to EEPROM address: ");
        Serial.println(calVal_eepromAdress);
        _resume = true;
      }
      else if (inByte == 'n') {
        Serial.println("Value not saved to EEPROM");
        _resume = true;
      }
    }
  }
  Serial.println("End change calibration value");
  Serial.println("***");
}
