#include <Servo.h>
#include <SoftwareSerial.h>

const int SERVO_PIN = 9;
const int LDR_PIN = A0;
const int TILT_PIN = 10;
const int BUZZER_PIN = 11;
const int LED_PIN = 4;

int LIGHT_THRESHOLD = 100;

Servo lidServo;
bool isLidOpen = false;
bool isBinTilted = false;
bool lastLDRState = false;

SoftwareSerial mySerial(2, 3);

void setup() {
  pinMode(TILT_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  lidServo.attach(SERVO_PIN);
  lidServo.write(0);
  Serial.begin(9600);
  mySerial.begin(9600);
  lastLDRState = (analogRead(LDR_PIN) > LIGHT_THRESHOLD);
}

void loop() {
  // LDR monitoring
  int lightValue = analogRead(LDR_PIN);
  bool currentLDRState = (lightValue > LIGHT_THRESHOLD);

  // Print lid status: 1 for open, 0 for closed
  Serial.print("P:");
  Serial.println(currentLDRState ? 1 : 0);
  

  // LED control
  digitalWrite(LED_PIN, currentLDRState ? HIGH : LOW);

  // Tilt monitoring
  isBinTilted = (digitalRead(TILT_PIN) == HIGH);

  // Print tilt status: 1 for tilted, 0 for not tilted
  Serial.print("T:");
  Serial.println(isBinTilted ? 1 : 0);
  

  if (isBinTilted) {
    tone(BUZZER_PIN, 1000);
  } else {
    noTone(BUZZER_PIN);
  }
  
  if (mySerial.available()) {
    String msg = mySerial.readStringUntil('\n');
    Serial.println(msg);
  }

  delay(100);
}
