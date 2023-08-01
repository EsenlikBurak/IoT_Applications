// Sabitlerin tanımlanması
const int led1Pin = D2;   // 1. ledin bağlı olduğu pin
const int led2Pin = D3;   // 2. ledin bağlı olduğu pin
const int led3Pin = D4;   // 3. ledin bağlı olduğu pin
const int sensorPin = A0;   // Gaz sensörünün analog pin

const int threshold1 = 620;   // 1. aralık için eşik değeri
const int threshold2 = 630;   // 2. aralık için eşik değeri
const int threshold3 = 640;   // 3. aralık için eşik değeri

void setup() {
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);   // Gaz sensöründen analog değeri oku

  // Gaz sensörünün değerine göre ledleri kontrol et
  if (sensorValue < threshold1) {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, LOW);
  } else if (sensorValue < threshold2) {
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, LOW);
  } else if (sensorValue < threshold3) {
    digitalWrite(led1Pin, LOW);
    digitalWrite(led2Pin, LOW);
    digitalWrite(led3Pin, HIGH);
  } else {
    digitalWrite(led1Pin, HIGH);
    digitalWrite(led2Pin, HIGH);
    digitalWrite(led3Pin, HIGH);
  }

  // Sensör değerini seri portta göster
  Serial.print("Gaz Sensoru: ");
  Serial.println(sensorValue);

  delay(100);   // 100ms gecikme
}
