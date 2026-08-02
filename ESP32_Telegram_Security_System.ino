#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include "time.h" 


const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";


#define BOT_TOKEN "YOUR_BOT_TOKEN"
#define CHAT_ID "YOUR_CHAT_ID" 


const long gmtOffset_sec = 21600; 
const int daylightOffset_sec = 0; 
const char* ntpServer = "pool.ntp.org";

//Pin Assignment
const int pirPin = 13;  
const int ledPin = 14;  

int motionStatus = 0;
int lastMotionStatus = LOW; 

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);


String getFormattedTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "Unknown Time";
  }
  char timeStringBuff[50];
  
  strftime(timeStringBuff, sizeof(timeStringBuff), "%H:%M:%S", &timeinfo);
  return String(timeStringBuff);
}

void setup() {
  Serial.begin(115200);
  
  pinMode(pirPin, INPUT);     
  pinMode(ledPin, OUTPUT);    


  Serial.print("Connecting to WiFi: ");
  WiFi.begin(ssid, password);
  
  client.setInsecure(); 

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  
  Serial.println("Syncing time with NTP server...");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  
  struct tm timeinfo;
  while (!getLocalTime(&timeinfo)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nTime synced successfully!");

  Serial.println("Waiting for PIR sensor to stabilize...");
  delay(10000); 
  Serial.println("Sensor active!");
  
  bot.sendMessage(CHAT_ID, "ESP32 Security System Online \nTime: " + getFormattedTime(), "");
}

void loop() {
  motionStatus = digitalRead(pirPin);
  
  if (motionStatus != lastMotionStatus) {
    String currentTime = getFormattedTime(); 
    
    if (motionStatus == HIGH) {
      digitalWrite(ledPin, HIGH);  
      Serial.println("--- Motion Detected! ---");
      
      bot.sendMessage(CHAT_ID, "Alert: Motion detected in the room!\n Time: " + currentTime, "");
    } else {
      digitalWrite(ledPin, LOW);   
      Serial.println("No motion.");
      
      bot.sendMessage(CHAT_ID, "Clear: No more motion.\n Time: " + currentTime, "");
    }
    
    lastMotionStatus = motionStatus;
  }
  
  delay(50); 
}
