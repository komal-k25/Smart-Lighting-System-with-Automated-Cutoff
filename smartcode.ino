// ------------------- BLYNK TEMPLATE -------------------
#define BLYNK_TEMPLATE_ID "TMPL3mIWtDe1d"
#define BLYNK_TEMPLATE_NAME "Smart Lighting System with
Automated Cutoff"

// ------------------- LIBRARIES -------------------
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// ------------------- BLYNK AUTH & WIFI -------------------
char auth[] = "abc"; // Replace
with your auth token
char ssid[] = "abc"; // Your hotspot SSID
char pass[] = "abc"; // Your hotspot password

// ------------------- VIRTUAL PINS -------------------
#define VIRTUAL_PIN_LDR_GAUGE V1
#define VIRTUAL_PIN_LED_MANUAL_CONTROL V2
#define VIRTUAL_PIN_LED_STATUS V3

// ------------------- HARDWARE PINS -------------------
const int pirPin = 27;
const int ldrPin = 34;
const int ledPin = 26;

// ------------------- SETTINGS -------------------
int lightThreshold = 1000; // Dark threshold
const long turnOffDelay = 10000; // 10 seconds

// ------------------- GLOBAL VARIABLES -------------------
unsigned long lastMotionTime = 0;
bool ledIsOn = false;
bool isManualMode = false;
bool wifiConnected = false;
bool blynkConnected = false;

// BLYNK MANUAL OVERRIDE
BLYNK_WRITE(VIRTUAL_PIN_LED_MANUAL_CONTROL) {
 int switchState = param.asInt();
 if (switchState == 1) {
 isManualMode = true;
 digitalWrite(ledPin, HIGH);
 ledIsOn = true;
 Serial.println("Blynk Manual Override: ON");
 } else {
 isManualMode = false;
 digitalWrite(ledPin, LOW);
 ledIsOn = false;
 lastMotionTime = millis();
 Serial.println("Blynk Manual Override: OFF. Reverting to Automatic
Mode.");
 }
 if(blynkConnected)
Blynk.virtualWrite(VIRTUAL_PIN_LED_STATUS, ledIsOn ? 255 : 0);
}
// AUTOMATIC LIGHTING LOGIC
void handleAutomaticLighting() {
 int pirState = digitalRead(pirPin);
 int ldrValue = analogRead(ldrPin);
 Serial.print("PIR State=");
 Serial.print(pirState ? "HIGH" : "LOW");
Serial.print(", LDR=");
 Serial.print(ldrValue);
 Serial.print(", LED=");
 Serial.print(ledIsOn ? "ON" : "OFF");
 Serial.print(", Mode=");
 Serial.println(isManualMode ? "MANUAL" : "AUTO");
 if (!isManualMode) {
 if (pirState == HIGH) {
 lastMotionTime = millis();
 if (ldrValue < lightThreshold) {
 if (!ledIsOn) {
 digitalWrite(ledPin, HIGH);
 ledIsOn = true;
 if(blynkConnected)
Blynk.virtualWrite(VIRTUAL_PIN_LED_STATUS, 255);
 Serial.println("Automatic: Motion and Dark. LED ON.");
 }
 }
 }
 if (ledIsOn && (millis() - lastMotionTime > turnOffDelay)) {
 digitalWrite(ledPin, LOW);
 ledIsOn = false;
 if(blynkConnected)
Blynk.virtualWrite(VIRTUAL_PIN_LED_STATUS, 0);
 Serial.println("Automatic: Timeout (10 mins). LED OFF.");
}
 }
}

// UPDATE BLYNK WIDGETS
void updateBlynkWidgets() {
 int ldrValue = analogRead(ldrPin);
 if(blynkConnected)
Blynk.virtualWrite(VIRTUAL_PIN_LDR_GAUGE, ldrValue);
 handleAutomaticLighting();
}
// WIFI + BLYNK CONNECT FUNCTION
void connectWiFiAndBlynk() {
 if(WiFi.status() != WL_CONNECTED) {
 Serial.println("Connecting to WiFi...");
 WiFi.begin(ssid, pass);
 unsigned long startAttemptTime = millis();
 while (WiFi.status() != WL_CONNECTED && millis() -
startAttemptTime < 15000) {
 delay(500);
 Serial.print(".");
 }
 if(WiFi.status() == WL_CONNECTED){
Serial.println("\nWiFi connected! IP:");
 Serial.println(WiFi.localIP());
 wifiConnected = true;
 } else {
 Serial.println("\nFailed to connect to WiFi.");
 wifiConnected = false;
 blynkConnected = false;
 return;
 }
 }
 if(!blynkConnected && wifiConnected){
 Serial.println("Connecting to Blynk...");
 Blynk.begin(auth, ssid, pass); // Non-blocking Blynk 2.0
 blynkConnected = true;
 }
}

// SETUP
void setup() {
 Serial.begin(115200);
 pinMode(pirPin, INPUT);
 pinMode(ledPin, OUTPUT);
 digitalWrite(ledPin, LOW);
 connectWiFiAndBlynk(
Serial.println("Smart Light System Initialized.");
}
// LOOP
void loop() {
 // Try reconnecting if disconnected
 if(!wifiConnected || !blynkConnected) connectWiFiAndBlynk();
 if(blynkConnected) Blynk.run();
 updateBlynkWidgets();
 delay(2000);
}