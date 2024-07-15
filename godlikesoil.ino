#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6sbM848m9"
#define BLYNK_TEMPLATE_NAME "Blynk Car"
#define BLYNK_AUTH_TOKEN "WrKnIEFJQmFQtq3YgXS8mWoU_QOKNXaL"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Godlike AIS_2.4G";
char pass[] = "Godlike999";

int sw1, sw2;
#define dirPin 26   //DIR
#define stepPin 25  //PUL
#define enPin 27    //EN
#define rainPin 18  //Portฝนจะใช้Portไหนเปลี่ยนเอาเด้อ
#define ss 5        //Portฝนจะใช้Portไหนเปลี่ยนเอาเด้อ


void setup() {
  Serial.begin(115200);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(ss, INPUT_PULLUP);
  pinMode(rainPin, INPUT);
  digitalWrite(enPin, LOW);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  int val = digitalRead(rainPin);
  digitalWrite(val, LOW);
  Serial.print(digitalRead(ss));
  Serial.print("\t");
  Serial.println(val);
  
  if (val == 0) {
    sw1 = 1;
  } else {
    sw1 = 0;
   
  }

  Blynk.run();
  if (sw1 == 1) {
    while (digitalRead(5) == 1) step_backward();
  }
  if (sw2 == 1) step_forward(5900);
}

void step_forward(int step) {
  digitalWrite(dirPin, HIGH);
  for (int i = 0; i < step; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
}

void step_backward() {
  digitalWrite(dirPin, LOW);
  for (int i = 0; i < 2; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(500);
  }
}

BLYNK_WRITE(V1) {
  sw1 = param.asInt();
  Serial.print("sw1 value is: ");
  Serial.println(sw1);
}

BLYNK_WRITE(V2) {
  sw2 = param.asInt();
  Serial.print("sw2 Slider value is: ");
  Serial.println(sw2);
}
