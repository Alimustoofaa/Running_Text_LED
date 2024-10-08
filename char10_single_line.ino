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
  if (lenWord <= 10) {
    Serial.println("1 Line");
    Serial.println(word);
    int startX = ((32*DISPLAYS_WIDE) - dmd.stringWidth(word)) / 2;
    int startY = ((16*DISPLAYS_HIGH) - SYSTEM5x7_HEIGHT) / 2;
    dmd.drawString(startX+1, startY+1, word);
  } else {
    Serial.println("2 Line");

    // create variable for char line 1 & 2
    char* line1 = new char[10];
    char* line2 = new char[lenWord - 9];
    
    // split word
    strncpy(line1, word, 10);
    strncpy(line2, word + 10, lenWord - 9);

    // calculate start x y
    int startX1 = ((32*DISPLAYS_WIDE) - dmd.stringWidth(line1)) / 2;
    int startY1 = 1;
    // Serial.println(line1);
    dmd.drawString(startX1, startY1,line1);

    // calculate start x y
    int startX2 = ((32*DISPLAYS_WIDE) - dmd.stringWidth(line2)) / 2;
    int startY2 = 9;
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
  

  // Display "READY" at the center
  dmd.clearScreen();  // Clear the screen
  int startX = ((32 * DISPLAYS_WIDE) - dmd.stringWidth("READY")) / 2;  // Center the text horizontally
  int startY = ((16 * DISPLAYS_HIGH) - SYSTEM5x7_HEIGHT) / 2;  // Center the text vertically
  dmd.drawString(startX, startY, "READY");  // Draw the text "READY"
  
  Serial.println("Start");
  delay(3000); 
  dmd.clearScreen();
  box.clear();

}

// Initialized variable to store received data
char incomingCharArray[50]; // Create a char array to store the incoming data
char* incomingString; 

void loop() {
  Serial.flush();
  if (Serial.available() > 0) { // Check if data is available on the serial monitor
    int incomingCharCount = Serial.readBytesUntil('\n', incomingCharArray, 50); // Read the incoming data into the char array
    incomingCharArray[incomingCharCount] = '\0'; // Add the null character to the end of the char array
    incomingString = new char[incomingCharCount+1]; // Allocate memory for the char pointer
    strcpy(incomingString, incomingCharArray); // Convert the char array to a char pointer using the strcpy() function
    drawCenterText(incomingString); // Draw LED pin
    delete[] incomingString; // Free the memory allocated for the char pointer
  }
  delay(100);
}
