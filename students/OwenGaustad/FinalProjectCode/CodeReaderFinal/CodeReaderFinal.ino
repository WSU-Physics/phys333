#include <SPI.h>
#include <SD.h>

const int chipSelect = 10; // Chip select pin for the SD card

void setup() {
  Serial.begin(9600);
  if (!SD.begin(chipSelect)) {
    Serial.println("Initialization failed!");
    return;
  }

  // Open the file for reading:
  File myFile = SD.open("PASSWORD.txt");
  if (myFile) {
    const int MAX_CHARACTERS = 5; // Adjust the maximum number of characters as needed
    char data[MAX_CHARACTERS];
    int index = 0;

    // Read each character from the file until we reach the end or the maximum number of characters
    while (myFile.available() && index < MAX_CHARACTERS - 1) {
      char c = myFile.read();
      // Store the character in the array
      data[index] = c;
      index++;
    }
    // Null-terminate the array to make it a valid C-string
    data[index] = '\0';

    // Close the file
    myFile.close();


    // Print out the data stored in the array
    Serial.println("");
    for (int i = 0; i < MAX_CHARACTERS - 1; i++){
      Serial.println(data[i]);
    }

  } else {
    // If the file didn't open, print an error:
    Serial.println("Error opening PASSWORD.txt");
  }
}

void loop() {
  // Nothing to do here
}