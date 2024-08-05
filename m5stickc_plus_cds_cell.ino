#include <M5StickCPlus.h>
#include "AXP192.h"

float barcolor = GREEN;

// Define the pin where the CDS photocell is connected
#define CDS_PIN 36 // The pin number may vary depending on your wiring

void setup() {
  // Initialize the M5StickC
  M5.begin();
  
  // Initialize the LCD
  M5.Lcd.begin();
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(3);
  pinMode(32, OUTPUT);  // Set pin 32 to output mode.  设置32号引脚为输出模式
  pinMode(33, OUTPUT);

  // Initialize the analog pin for the CDS photocell
  pinMode(CDS_PIN, INPUT);
}

void loop() {
  // Read the value from the CDS photocell
  int lightLevel = analogRead(CDS_PIN);
//map the value from the cds to 1-100
  lightLevel = map(lightLevel, 0, 4095, 0, 100);


//this section is for use when not remapping the cds cell output
// Read the value from the CDS photocell
//  int lightLevel = analogRead(CDS_PIN);
//  if (lightLevel > 2000)digitalWrite(32, HIGH);
//  else digitalWrite(32, LOW);

//    if (lightLevel > 3500)digitalWrite(33, HIGH);
//  else digitalWrite(33, LOW);


//this section is for the mapped values
  if ((lightLevel > 20) && (lightLevel < 50)) {
      digitalWrite(32, HIGH),
        M5.Lcd.setTextColor(BLUE);
  } else digitalWrite(32, LOW),
    M5.Lcd.setTextColor(GREEN);

    if ((lightLevel > 70) && (lightLevel < 95)) {
      digitalWrite(33, HIGH),
        M5.Lcd.setTextColor(RED);
  } else digitalWrite(33, LOW);

  // Display the light level on the screen
  M5.Lcd.fillRect(160, 20, 70, 30, BLACK);
  M5.Lcd.setCursor(160, 20);
  M5.Lcd.printf("%d", lightLevel);
  M5.Lcd.setCursor(5, 20);
  M5.Lcd.printf("Pressure");


//display battery level
  M5.Lcd.fillRect(100, 67, 70, 5, BLACK);
  M5.Lcd.fillRect(100, 67, ((M5.Axp.GetBatVoltage() - 3.0) * 70.0), 5, barcolor);
  M5.Lcd.fillRect(10, 57, 70, 30, BLACK);
  M5.Lcd.setCursor(10, 57);
  M5.Lcd.setTextSize(3);
  M5.Lcd.printf("%.2f", M5.Axp.GetBatVoltage());


  // Add a small delay to avoid flooding the screen with updates
  delay(100);
}
