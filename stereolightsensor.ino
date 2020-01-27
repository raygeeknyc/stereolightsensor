// Light Sensor for Code Next Robotics Club
// Trinket M0, CDS Photo Resistor, Piezo Buzzer
// by Raymond Blum, 2020

#include <Adafruit_DotStar.h>
#include <Servo.h>

#define LIGHT_DELTA_THRESHOLD 50
#define BUZZER_PIN 4
#define LEFT_PHOTORESISTOR_PIN A2
#define RIGHT_PHOTORESISTOR_PIN A0
#define SERVO_PIN 3

Adafruit_DotStar strip = Adafruit_DotStar(1, INTERNAL_DS_DATA, INTERNAL_DS_CLK, DOTSTAR_BGR);
Servo servo;
#define SERVO_STOP 92
#define SERVO_LEFT 105
#define SERVO_RIGHT 85

void setup() {
  strip.begin();
  Serial.begin(115200);
  pinMode(SERVO_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
  pinMode(LEFT_PHOTORESISTOR_PIN, INPUT);
  pinMode(RIGHT_PHOTORESISTOR_PIN, INPUT);
}

void loop() {
  int left_light_level = analogRead(LEFT_PHOTORESISTOR_PIN);
  int right_light_level = analogRead(RIGHT_PHOTORESISTOR_PIN);
  Serial.print("light (L): ");
  Serial.print(left_light_level);
  Serial.print(" (R): ");
  Serial.println(right_light_level);
  if ((left_light_level - right_light_level) > LIGHT_DELTA_THRESHOLD) {
    strip.setPixelColor(0, 0, 64, 0);  //green
    servo.write(SERVO_LEFT);
    tone(BUZZER_PIN, 700, 100);
  } else if ((right_light_level - left_light_level) > LIGHT_DELTA_THRESHOLD) {
    strip.setPixelColor(0, 64, 0, 0);  //red
    servo.write(SERVO_RIGHT);
    tone(BUZZER_PIN, 200, 100);
  } else {
    strip.setPixelColor(0, 0, 0, 64);  //blue
    servo.write(SERVO_STOP);
  }
  strip.show();
  delay(500);
}
