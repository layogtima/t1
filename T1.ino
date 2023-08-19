// 
// T1 by Kailash (kaliash@ampere.works), Amit (amit@absurd.industries) and Amartha (amartha@absurd.industries)
// Based off of GxEPD2_HelloWorld.ino by Jean-Marc Zingg
//
//
//

#include <ESP32Time.h>
#include <WiFi.h>
#include <GxEPD2_BW.h>
#include "w3_ip28pt7b.h" // https://www.dafont.com/w3usdip.font?text=01%3A07+Friday+15th+August&back=theme
#include "w3_ip18pt7b.h" 
#include "w3_ip14pt7b.h" 
#include <Preferences.h> // https://github.com/espressif/arduino-esp32/blob/master/libraries/Preferences/src/Preferences.h

#define uS_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 60          /* Time ESP32 will go to sleep (in seconds) */

String ssid;      
String password;

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600 * 5.5;
const int daylightOffset_sec = 3600 * 0;

GxEPD2_BW<GxEPD2_154_GDEY0154D67, GxEPD2_154_GDEY0154D67::HEIGHT> display(GxEPD2_154_GDEY0154D67(/*CS=5*/ 5, /*DC=*/20, /*RST=*/21, /*BUSY=*/9));  // GDEY0154D67 200x200, SSD1681, (FPC-B001 20.05.21)
ESP32Time rtc(0);

RTC_DATA_ATTR int bootCount = 0;
Preferences preferences;

void storeWiFiCredentials(const char* ssid, const char* password) {
  preferences.begin("wifi", false);
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  preferences.end();
}

void retrieveWiFiCredentials() {
  preferences.begin("wifi", false);
  ssid = preferences.getString("ssid", "");
  password = preferences.getString("password", "");
  preferences.end();
}

void storeTime() {
  preferences.begin("time", false);
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  preferences.end();
}

void connectToWiFi() {
  retrieveWiFiCredentials(); // Fetch stored credentials
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
}

void setRTC() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    rtc.setTimeStruct(timeinfo);
  }
}

void activateMemory() {
  preferences.begin("t1", false);
  preferences.putInt("epoch", 42);  // Or other relevant value
  preferences.end();
}

int retrieveFromMemory() {
  preferences.begin("t1", false);
  int epoch = preferences.getInt("epoch", 0);
  return epoch;
}

void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0: Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1: Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER: Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD: Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP: Serial.println("Wakeup caused by ULP program"); break;
    default: Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
  }
}

void setup() {
  // Basic initialization
  Serial.begin(115200);
  // print_wakeup_reason();
  // esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  
  // Connecting to WiFi and setting RTC
  // storeWiFiCredentials("@manjusstudio", "wifi2020!");
  connectToWiFi();
  setRTC();
  activateMemory();
}

void displayTime() {
  display.setRotation(0);
  display.setFont(&w3_ip28pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(7, y - 40);
    display.println(rtc.getTime("%H:%M")); // 22:23
    
    display.setFont(&w3_ip18pt7b);
    display.setCursor(0, y - 13);
    display.println("---------"); // 22:23
    display.setCursor(7, y + 14);
    display.println(rtc.getTime("%A"));    // Wednesday 
    
    display.setFont(&w3_ip14pt7b);
    display.setCursor(7, y + 60);
    display.println(rtc.getTime("%d"));    // 14 
    display.setCursor(7, y + 88);
    display.println(rtc.getTime("%B"));  // Sep 

    // display.setCursor(56, 30);
    // display.println(rtc.getTime(""));   
  } while (display.nextPage());
}

void loop() {
  display.init(115200, true, 2, false);
  displayTime();
  display.hibernate();
  
  delay(10000);
  // esp_deep_sleep_start();
}
