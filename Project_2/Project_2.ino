#define BLYNK_TEMPLATE_ID "TMPL6E_OYX46l"
#define BLYNK_TEMPLATE_NAME "FinalProjectBurakYagiz"
#define BLYNK_AUTH_TOKEN "D-R62_etP6c_gS_JpkbPNVCakZMMmlKi"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
#define BLYNK_PRINT Serial  //comment this out to disable prints and save space

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const uint16_t IR_RECEIVE_PIN = D2;

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "SUPERONLINE_Wi-Fi_3190"; // WiFi ağınızı buraya girin
char pass[] = "TtCA6XkT7EkQ"; // WiFi şifrenizi buraya girin

#define LED_1 D3
#define LED_2 D4
#define LED_3 D5

// DC motor pins
const int MOTOR_PIN1 = D7;
const int MOTOR_PIN2 = D8;

// Gas sensor pin
const int GAS_SENSOR_PIN = A0;
int gasValue = 0;

IRrecv irReceiver(IR_RECEIVE_PIN);
decode_results irResults;

void sendSensor(){
 
 int gasValue = analogRead(GAS_SENSOR_PIN);
 Blynk.virtualWrite(V0, gasValue);


  
}

BLYNK_WRITE(V1)
{
  // Set incoming value from pin V0 to a variable
  int ledValue = param.asInt();

  // Update state
  if(ledValue==1){
    digitalWrite(D3,HIGH);
  }else{
    digitalWrite(D3,LOW);
  }
}

BLYNK_WRITE(V2) {
  int ledValue = param.asInt();
  if(ledValue==1){
    digitalWrite(D4,HIGH);
  }else{
    digitalWrite(D4,LOW);
  }
}

BLYNK_WRITE(V3) {
  int ledValue = param.asInt();
  if(ledValue==1){
    digitalWrite(D5,HIGH);
  }else{
    digitalWrite(D5,LOW);
  }
}

BLYNK_WRITE(V4) {
  int motorValue = param.asInt();
  if (motorValue == 1) {
    digitalWrite(MOTOR_PIN1, HIGH);
    digitalWrite(MOTOR_PIN2, LOW);
  }else {
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, LOW);
  }
}

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(GAS_SENSOR_PIN,INPUT);
  irReceiver.enableIRIn(); // Kablosuz kızılötesi iletişim modülünü başlat
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2500L, sendSensor);

}

void loop() {
  Blynk.run();
  timer.run();

  
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

    irReceiver.resume(); // Bir sonraki IR kodunu al
  }

  

  int sensorValue = analogRead(GAS_SENSOR_PIN); // Gaz sensöründen analog değeri oku
  // Sensör değerini seri porta yazdır
  Serial.print("Gas Sensor: ");
  Serial.println(sensorValue);

  delay(100); // 100ms gecikme*/
}
