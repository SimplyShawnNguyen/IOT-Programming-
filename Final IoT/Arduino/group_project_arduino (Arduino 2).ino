#include <DHT.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//OLED display
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, OLED_RESET);

//Temperature sensor
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);





const float MIN_DISTANCE = 2.0;    // Closest for 100%
const float MAX_DISTANCE = 30.0;   // Farthest for 0%

bool fanRunning = false;
float lastDistance = -1;

//ultrasocnic AND FAN
const int FAN_PIN = 10;
const int TRIG_PIN = 3;
const int ECHO_PIN = 2;


void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(FAN_PIN, OUTPUT);

  Serial.begin(9600);
  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED init failed"));
    while (true); 
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  float temp = dht.readTemperature();
  float distance = getDistance();
  int fillPercent = mapDistanceToPercent(distance);

  display.clearDisplay();
  display.setCursor(0, 0);


    String input = Serial.readStringUntil('\n');
    Serial.print("input is: ----->>> ");
    Serial.println(input);
    if(input.startsWith("f:")){
      int running = input.substring(2).toInt();
      fanRunning = running == 1;
      Serial.print("Fan running? ");
      Serial.println(fanRunning);
    }



  if (!isnan(temp)) {
    display.print("Temp: ");
    display.print(temp);
    display.println(" °C");

    if (temp > 30.0 || fanRunning){
      digitalWrite(FAN_PIN, HIGH);
    } else {
      digitalWrite(FAN_PIN, LOW);
    }

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");
    delay(1700);
    
  } else {
    display.println("Temp Read Fail");
    Serial.println("Failed to read from DHT11");

  }

  if (distance >= 0) {
    display.print("Distance: ");
    display.print(distance);
    display.println(" cm");

    display.print("Fill: ");
    display.print(fillPercent);
    display.println(" %");

    if (abs(distance - lastDistance) >= 1.0) {
      lastDistance = distance;
      Serial.print("Percen_capa: ");
      Serial.println(fillPercent);
      

    }
  } else {
    display.println("No Distance Read");
  }

  display.display();
  delay(1000);


}

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;

  return duration * 0.034 / 2.0;
}

//Change distance into percentage
int mapDistanceToPercent(float distance) {
  if (distance < 0) return 0;
  if (distance <= MIN_DISTANCE) return 100;
  if (distance >= MAX_DISTANCE) return 0;

  float ratio = (distance - MIN_DISTANCE) / (MAX_DISTANCE - MIN_DISTANCE);
  return 100 - (ratio * 100);
}


