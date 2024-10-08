/*
  Use the Marquee function to make an LED-sign type display

  This marquee function scrolls in all directions, random distances for each
  direction. If you edit the code in the "switch" statement below then you can
  make a simpler marquee that only scrolls in one direction.
*/
#include <stdlib.h>
#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>

#define DISPLAYS_WIDE 2
#define DISPLAYS_HIGH 1

SoftDMD dmd(DISPLAYS_WIDE,DISPLAYS_HIGH);
DMD_TextBox box(dmd, 0, 2, 64, 32);

void drawCenterText(char * word) {
  dmd.clearScreen();
  int lenWord = strlen(word);
  Serial.println(lenWord);
  if (lenWord <= 8){
    Serial.println("1 Line");
    int startX = ((32*DISPLAYS_WIDE) - dmd.stringWidth(word)) / 2;
    int startY = ((16*DISPLAYS_HIGH) - SYSTEM5x7_HEIGHT) / 2;
    dmd.drawString(startX, startY,word);
  } else {
    Serial.println("2 Line");

    // create variable for char line 1 & 2
    char* line1 = new char[8];
    char* line2 = new char[lenWord - 7];
    
    // split word
    strncpy(line1, word, 8);
    strncpy(line2, word + 8, lenWord - 7);

    // calculate start x y
    int startX1 = ((32*DISPLAYS_WIDE) - dmd.stringWidth(line1)) / 2;
    int startY1 = 0;
    // Serial.println(line1);
    dmd.drawString(startX1, startY1,line1);

    // calculate start x y
    int startX2 = ((32*DISPLAYS_WIDE) - dmd.stringWidth(line2)) / 2;
    int startY2 = 8;
    // Serial.println(line2);
    dmd.drawString(startX2, startY2,line2);
    delete[] line1;
    delete[] line2;
    // substr word
    // int halfLength = length / 2;

    // String firstHalf = word.substr(0, halfLength);
    // String secondHalf = word.substr(halfLength);

  }
}

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  dmd.setBrightness(100);
  dmd.selectFont(SystemFont5x7);
  dmd.begin();
  dmd.clearScreen();
  box.clear();
  Serial.println("Start");
}

// Initialized veriable to store received data
char incomingCharArray[50]; // Create a char array to store the incoming data
char* incomingString; 

void loop() {
  Serial.flush();
  if (Serial.available() > 0) { // Check if data is available on the serial monitor
    int incomingCharCount = Serial.readBytesUntil('\n', incomingCharArray, 50); // Read the incoming data into the char array
    incomingCharArray[incomingCharCount] = '\0'; // Add the null character to the end of the char array
    incomingString = new char[incomingCharCount+1]; // Allocate memory for the char pointer
    strcpy(incomingString, incomingCharArray); // Convert the char array to a char pointer using the strcpy() function
    // Serial.println(incomingString); // Print the converted string to the serial monitor
    drawCenterText(incomingString); // Draw LED pin
    delete[] incomingString; // Free the memory allocated for the char pointer
  }
  delay(100);
}
