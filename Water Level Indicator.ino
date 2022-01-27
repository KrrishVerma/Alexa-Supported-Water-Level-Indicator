//Code Written By Krrish Verma
//Make sure to give credits
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

 
char auth[] = "";//Enter your Auth token
char ssid[] = "";//Enter your WIFI name
char pass[] = "";//Enter your WIFI password

// Keep this flag not to re-sync on every reconnection
bool isFirstConnect = true;

// This function will run every time Blynk connection is established
BLYNK_CONNECTED() {
  if (isFirstConnect) {
    // Request Blynk server to re-send latest values for all pins
    Blynk.syncAll();
    isFirstConnect = false;
  }
}
 
BlynkTimer timer;
bool pinValue = 0;
 
#define trig D7
#define echo D8

BLYNK_WRITE(V0) {
  pinValue = param.asInt();
}


 
void setup() {
  int duration,distance,percentage,heightTank;
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}
 
void loop() {
  Blynk.run();
  timer.run();
  int duration,distance,percentage,heightTank,deviation;
  heightTank=11;
  deviation=2;
  digitalWrite(trig,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo, HIGH);
  distance=(duration/2)/29.1;
  percentage=100-(((distance-deviation)*100)/heightTank);
  Blynk.virtualWrite(V1, percentage);
  Serial.println(distance);
  Serial.println(percentage);
  delay(1000);
}
