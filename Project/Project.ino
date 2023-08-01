#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t IR_RECEIVE_PIN = D2;

#define LED_1 D3
#define LED_2 D4
#define LED_3 D5

// DC motor pins
const int MOTOR_PIN1 = D7;
const int MOTOR_PIN2 = D8;

// Gas sensor pin
const int GAS_SENSOR_PIN = A0;

IRrecv irReceiver(IR_RECEIVE_PIN);
decode_results irResults;

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  irReceiver.enableIRIn(); // Start the infrared wireless communication module
  Serial.begin(9600);
}

void loop() {
  if (irReceiver.decode(&irResults)) {
    String irCode = String(irResults.command, HEX);
    Serial.println(irCode);

    if (irCode == "45")
      digitalWrite(LED_1, HIGH);
    else if (irCode == "46")
      digitalWrite(LED_2, HIGH);
    else if (irCode == "47")
      digitalWrite(LED_3, HIGH);
    else if (irCode == "44") {
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
    } else if (irCode == "40") {
      digitalWrite(MOTOR_PIN1, HIGH);
      digitalWrite(MOTOR_PIN2, LOW);
    } else if (irCode == "43") {
      digitalWrite(MOTOR_PIN1, LOW);
      digitalWrite(MOTOR_PIN2, HIGH);
    } else if (irCode == "7") {
      digitalWrite(MOTOR_PIN1, LOW);
      digitalWrite(MOTOR_PIN2, LOW);
    }

    irReceiver.resume(); // Receive the next IR code
  }

  int gasValue = analogRead(GAS_SENSOR_PIN); // Read gas sensor value

  if (gasValue > 490) {
    // If gas level is high, perform necessary actions
    // For example, turn off the motor and all LEDs
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, LOW);
  }

  int sensorValue = analogRead(GAS_SENSOR_PIN); // reading analog value from gas sensor
  // Sensör değerini seri portta göster
  Serial.print("Gaz Sensoru: ");
  Serial.println(sensorValue);

  delay(100); // 100ms gecikme
}
