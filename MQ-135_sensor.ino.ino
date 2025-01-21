#include <LiquidCrystal.h>

int sensorValue;
int digitalValue;
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);  // RS, EN, D4, and D5 pins
int MQ135_A0 = A0;                        // Analog pin for MQ-135 sensor

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  lcd.begin(16, 2);
}

void loop() {
  // Read sensor values
  sensorValue = analogRead(MQ135_A0);  // Read MQ-135 sensor connected to A0
  digitalValue = digitalRead(2);

  // Display sensor values on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Analog: ");
  lcd.print(sensorValue);

  lcd.setCursor(0, 1);
  lcd.print("Digital: ");
  lcd.print(digitalValue);

  // Additional code for MQ-135 sensor
  float voltage = (sensorValue / 1023.0) * 5.0;  // Convert analog reading to voltage
  float ppm = (voltage - 0.1) * 200;             // Convert voltage to ppm (adjust the formula based on your MQ-135 datasheet)

  lcd.setCursor(0, 1);
  lcd.print("Gas (PPM): ");
  lcd.print(ppm);

  // Control the LED based on sensor value
  if (sensorValue > 400) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  // Print sensor values to serial monitor
  Serial.print("Analog: ");
  Serial.println(sensorValue);
  Serial.print("Digital: ");
  Serial.println(digitalValue);
  Serial.print("Gas (PPM): ");
  Serial.println(ppm);

  delay(1000);  // Wait for 1 second before the next reading
}