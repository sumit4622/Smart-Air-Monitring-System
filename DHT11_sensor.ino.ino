#include <LiquidCrystal.h>
#include <DHT.h>

LiquidCrystal lcd(3, 4, 5, 6, 7, 8);
#define dhtpin A0  // Output pin of DHT11
DHT dht(dhtpin, DHT11);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();  // Initialize the DHT sensor
}

void loop() {
  // Read sensor data
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);  // Display temperature with one decimal place
  lcd.print((char)223);       // Degree symbol
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity, 1);  // Display humidity with one decimal place
  lcd.print("%");

  delay(2000);  // Wait for a moment before taking the next reading
  lcd.clear();  // Clear the LCD screen for the next reading
}