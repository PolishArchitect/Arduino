#include <Servo.h>

Servo myServo;  // Create servo object
int inputSpeed = 90;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);  // Connect servo signal wire to pin 9
}

void loop() {
    if (Serial.available()) {
        String data = Serial.readStringUntil('\n');  // Read until newline
        inputSpeed = data.toInt();
    }
    myServo.write(inputSpeed);   // Clockwise
}
