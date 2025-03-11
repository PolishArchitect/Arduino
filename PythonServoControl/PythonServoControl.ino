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
    delay(1000);        // Run for 1 second

    myServo.write(90);
    delay(250);

    myServo.write(180-inputSpeed);  // Counter-clockwise
    delay(1000);        // Pause for 0.5 seconds

    myServo.write(90);
    delay(250);
}
