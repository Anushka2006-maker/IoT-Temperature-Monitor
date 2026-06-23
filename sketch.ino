/**
 * IoT Temperature Monitoring System
 * ESP32 + DHT22 + ThingSpeak + LED Alerts
 * Platform: Wokwi
 * Author: Anushka Dubey
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

// ============================================================
// PIN DEFINITIONS
// ============================================================
#define DHTPIN 15          // DHT22 data pin (GPIO 15)
#define GREEN_PIN 12       // Green LED (GPIO 12)
#define RED_PIN 13         // Red LED (GPIO 13)

#define DHTTYPE DHT22
#define TEMP_LIMIT 30.0    // Temperature threshold in Celsius

// ============================================================
// WIFI CONFIGURATION (Wokwi Default)
// ============================================================
const char* ssid = "Wokwi-GUEST";      // Wokwi's built-in WiFi
const char* password = "";

// ============================================================
// THINGSPEAK CONFIGURATION
// ============================================================
// ⚠️ REPLACE WITH YOUR ACTUAL THINGSPEAK VALUES ⚠️
String apiKey = "YOUR_WRITE_API_KEY_HERE";   // From ThingSpeak → API Keys
const char* thingSpeakURL = "http://api.thingspeak.com/update";

// ============================================================
// OBJECT INITIALIZATION
// ============================================================
DHT dht(DHTPIN, DHTTYPE);

// ============================================================
// SETUP FUNCTION
// ============================================================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("========================================");
  Serial.println("  Temperature Monitoring System v1.0");
  Serial.println("========================================\n");
  
  // Initialize LEDs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  
  Serial.println("✅ LEDs initialized");
  Serial.println("   Green ON = Normal | Red ON = Alarm\n");
  
  // Initialize DHT22
  dht.begin();
  Serial.println("✅ DHT22 Sensor initialized on pin 15\n");
  
  // Connect to WiFi
  Serial.print("📡 Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi Connected!");
    Serial.print("   IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ WiFi Connection Failed!");
  }
  
  Serial.print("\n📊 Temperature Threshold: ");
  Serial.print(TEMP_LIMIT);
  Serial.println(" °C");
  Serial.println("   Alarm triggers when temperature exceeds this limit\n");
  Serial.println("========================================\n");
  Serial.println("🔄 System is now monitoring...\n");
}

// ============================================================
// LOOP FUNCTION
// ============================================================
void loop() {
  // Read DHT22 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  // Validate sensor reading
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("❌ Failed to read from DHT22 sensor!");
    Serial.println("   Check sensor connections");
    delay(2000);
    return;
  }
  
  // Display readings
  Serial.print("🌡️ Temperature: ");
  Serial.print(temperature, 1);
  Serial.print(" °C  |  💧 Humidity: ");
  Serial.print(humidity, 1);
  Serial.println(" %");
  
  // LED Alert Logic
  if (temperature > TEMP_LIMIT) {
    digitalWrite(RED_PIN, HIGH);    // Red LED ON
    digitalWrite(GREEN_PIN, LOW);   // Green OFF
    Serial.println("⚠️⚠️⚠️ WARNING: Temperature exceeds limit! ⚠️⚠️⚠️");
    Serial.println("🔴 ALERT: Overheat condition detected!\n");
  } else {
    digitalWrite(RED_PIN, LOW);     // Red LED OFF
    digitalWrite(GREEN_PIN, HIGH);  // Green ON
    Serial.println("✅ Status: Temperature Normal\n");
  }
  
  // Send to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(thingSpeakURL) + 
                 "?api_key=" + apiKey +
                 "&field1=" + String(temperature) +
                 "&field2=" + String(humidity) +
                 "&field3=" + String((temperature > TEMP_LIMIT) ? 1 : 0);
    
    http.begin(url);
    int httpCode = http.GET();
    
    if (httpCode == 200) {
      Serial.println("📤 Data sent to ThingSpeak successfully!");
    } else {
      Serial.print("❌ ThingSpeak Error: HTTP ");
      Serial.println(httpCode);
    }
    http.end();
  } else {
    Serial.println("❌ WiFi not connected - Data not sent");
  }
  
  Serial.println("----------------------------------------\n");
  delay(15000);  // ThingSpeak rate limit (15 seconds minimum)
}
