#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t IR_RECEIVE_PIN = D2;

#define LED_1 D3
#define LED_2 D4
#define LED_3 D5

IRrecv irReceiver(IR_RECEIVE_PIN);

decode_results irResults;

void setup() {
  Serial.begin(115200);
  Serial.println("test");
  irReceiver.enableIRIn();

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
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
    else if (irCode == "44")
      digitalWrite(LED_1, LOW);
    else if (irCode == "40")
      digitalWrite(LED_2, LOW);
    else if (irCode == "43")
      digitalWrite(LED_3, LOW);

    irReceiver.resume();
  }
}