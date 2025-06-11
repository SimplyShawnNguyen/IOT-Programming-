#include "DHT.h"

const int Green_LED = 5;
const int Yellow_LED = 6;
const int Red_LED = 7;
const int Light_sensor = A0;
const int buzzer = 8;
const int temp_sensor = 3;

#define DHTTYPE DHT22
DHT dht(temp_sensor, DHTTYPE);

// Threshold variables 
float tempThreshold = 24.0;
int lightMin = 10;
int lightMax = 200;

void setup() {
  pinMode(Green_LED, OUTPUT);
  pinMode(Yellow_LED, OUTPUT);
  pinMode(Red_LED, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
  dht.begin();
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();  // Remove whitespace

    int firstComma = input.indexOf(',');
    int secondComma = input.lastIndexOf(',');

    if (firstComma > 0 && secondComma > firstComma) {
      float newTemp = input.substring(0, firstComma).toFloat();
      int newMin = input.substring(firstComma + 1, secondComma).toInt();
      int newMax = input.substring(secondComma + 1).toInt();

      // Update thresholds
      tempThreshold = newTemp;
      lightMin = newMin;
      lightMax = newMax;

      Serial.print("Updated thresholds: Temp=");
      Serial.print(tempThreshold);
      Serial.print(", LightMin=");
      Serial.print(lightMin);
      Serial.print(", LightMax=");
      Serial.println(lightMax);
    }
  }


  int light_val = analogRead(Light_sensor);
  float temperatureC = dht.readTemperature();

  digitalWrite(Green_LED, LOW);
  digitalWrite(Yellow_LED, LOW);
  digitalWrite(Red_LED, LOW);
  digitalWrite(buzzer, LOW);

  if (isnan(temperatureC)) {
    Serial.println("Error, failed to load temperature!");
    return;
  }

  Serial.print("Temp: ");
  Serial.print(temperatureC);
  Serial.print(" | Light: ");
  Serial.println(light_val);


  if (light_val > lightMax) {
    digitalWrite(Red_LED, HIGH);
  } else if (light_val < lightMin) {
    digitalWrite(Yellow_LED, HIGH);
  } else {
    digitalWrite(Green_LED, HIGH);
  }


  if (temperatureC > tempThreshold) {
    digitalWrite(buzzer, HIGH);
  }

  delay(500);
}
