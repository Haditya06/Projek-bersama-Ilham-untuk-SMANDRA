#define uS_TO_S_FACTOR 1000000
#define TIME_TO_SLEEP 30  

#include <WiFi.h>  
#include <Wire.h>

const int relay = 14;           
const int soilmoisture = 34;    
float persen = 0;

void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW); 

  
  for (int i = 0; i < 5; i++) {
    analogSense();
    delay(200);
  }

  
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Masuk mode tidur...");
  delay(100); 
  esp_deep_sleep_start(); 
}

void loop() {
  
}

void analogSense() {
  int soil = analogRead(soilmoisture);  
  persen = (soil / 4095.0) * 100.0;      

  Serial.print("Nilai kelembaban tanah: ");
  Serial.print(soil);
  Serial.print(" | Persen: ");
  Serial.println(persen);

  if (persen < 25.0) {
    relayON();
  } else if (persen >= 25.0) {
    relayOFF();
  }
}

void relayON() {
  digitalWrite(relay, HIGH);  
  Serial.println("Pompa MENYALA.");
}

void relayOFF() {
  digitalWrite(relay, LOW);   
  Serial.println("Pompa MATI.");
}
