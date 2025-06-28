#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// LED Control Variables
const int LED_PIN = 8;  // Built-in LED pin (D8 on ESP32-C3-MINI)
#define LED_ON    LOW   // LED is ON when pin is LOW (common for built-in LEDs)
#define LED_OFF   HIGH  // LED is OFF when pin is HIGH

// Heartbeat pattern: on/off durations in milliseconds for the heartbeat effect
const int HEARTBEAT_PATTERN[] = {100, 100, 100, 500};  // short-short-long pause
const int HEARTBEAT_PATTERN_LENGTH = 4;
int heartbeatStep = 0;
unsigned long previousHeartbeatMillis = 0;
bool isConnected = false;

// WiFi credentials
const char* ssid = "12345678";
const char* password = "12345678";

// Server details
const char* serverName = "http://192.168.123.111:5003/api/data";
const int serverPort = 5003;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n[ESP32-C3 WiFi Debug Start]");
    
    // Initialize LED
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LED_OFF);  // Start with LED off

    // Wi-Fi 모듈 초기화 확인
    Serial.println("[1] WiFi Mode 설정");
    WiFi.mode(WIFI_STA);  // 스테이션 모드 설정
  
    // 스캔 테스트
    Serial.println("[2] 주변 WiFi 스캔 시작");
    int n = WiFi.scanNetworks();
    if (n == 0) {
      Serial.println("  ⚠️ WiFi 네트워크를 찾을 수 없음");
    } else {
      Serial.printf("  ✅ %d개의 네트워크 발견:\n", n);
      for (int i = 0; i < n; ++i) {
        Serial.printf("    %d: %s (%ddBm) %s\n", i + 1,
          WiFi.SSID(i).c_str(),
          WiFi.RSSI(i),
          (WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "Open" : "Secured");
      }
    }
  
    delay(1000);
  
    // Wi-Fi 캐시 정보 삭제 (꼭 필요!)
    WiFi.disconnect(true);  // NVS에 저장된 SSID/비번 초기화
    delay(500);

    // 연결 시도
    Serial.printf("[3] SSID: %s 에 연결 중...\n", ssid);
    WiFi.begin(ssid, password);
    
    // Start heartbeat LED pattern while connecting
    digitalWrite(LED_PIN, LED_OFF);
    unsigned long connectionStartTime = millis();
    const unsigned long CONNECTION_TIMEOUT = 20000; // 20 seconds timeout
    

    // Print detailed WiFi information
    printWiFiDetails();

    while (WiFi.status() != WL_CONNECTED && (millis() - connectionStartTime) < CONNECTION_TIMEOUT) {
      // Handle heartbeat pattern
      unsigned long currentMillis = millis();
      if (currentMillis - previousHeartbeatMillis >= HEARTBEAT_PATTERN[heartbeatStep]) {
        previousHeartbeatMillis = currentMillis;
        digitalWrite(LED_PIN, (heartbeatStep % 2 == 0) ? LED_ON : LED_OFF);
        heartbeatStep = (heartbeatStep + 1) % HEARTBEAT_PATTERN_LENGTH;
      }
      
      // Small delay to prevent watchdog issues
      delay(10);
      
      // Print connection progress
      if (millis() % 1000 < 10) {  // About once per second
        Serial.print(".");
      }
    }
    
    // Print detailed WiFi information
    printWiFiDetails();
  
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\n  ✅ WiFi 연결 성공!");
      Serial.print("  IP 주소: ");
      Serial.println(WiFi.localIP());
      // Blink LED once when connected
      digitalWrite(LED_PIN, LED_ON);
      delay(500);
      digitalWrite(LED_PIN, LED_OFF);
      delay(500);
    } else {
      Serial.println("\n  ❌ WiFi 연결 실패!");
      Serial.printf("  WiFi Status Code: %d\n", WiFi.status());
      printWiFiStatus(WiFi.status());
      // Rapid blink when not connected
      for(int i = 0; i < 3; i++) {
        digitalWrite(LED_PIN, LED_ON);
        delay(100);
        digitalWrite(LED_PIN, LED_OFF);
        delay(100);
      }
    }
  }
  
  void printWiFiDetails() {
    Serial.println("📡 [Wi-Fi 상세 정보]");
    
    // 현재 연결된 SSID
    Serial.print("  ▶ SSID: ");
    Serial.println(WiFi.SSID());
  
    // IP 주소
    Serial.print("  ▶ IP 주소: ");
    Serial.println(WiFi.localIP());
  
    // MAC 주소
    Serial.print("  ▶ MAC 주소: ");
    Serial.println(WiFi.macAddress());
  
    // Hostname
    Serial.print("  ▶ Hostname: ");
    Serial.println(WiFi.getHostname());
  
    // 신호 세기 (RSSI)
    Serial.print("  ▶ 신호 세기 (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  
    // BSSID (접속된 공유기의 MAC)
    Serial.print("  ▶ BSSID: ");
    Serial.println(WiFi.BSSIDstr());
  
    // 채널
    Serial.print("  ▶ 채널: ");
    Serial.println(WiFi.channel());
  
    // 연결 상태 코드
    Serial.print("  ▶ 상태 코드: ");
    Serial.println(WiFi.status());
  }
  
  
  void printWiFiStatus(wl_status_t status) {
    switch (status) {
      case WL_NO_SHIELD: Serial.println("  ❌ WiFi 모듈 없음"); break;
      case WL_IDLE_STATUS: Serial.println("  ⏳ WiFi 대기 중"); break;
      case WL_NO_SSID_AVAIL: Serial.println("  ❌ SSID 찾을 수 없음(WL_NO_SSID_AVAIL)"); break;
      case WL_SCAN_COMPLETED: Serial.println("  ✅ 스캔 완료"); break;
      case WL_CONNECTED: Serial.println("  ✅ 연결됨"); break;
      case WL_CONNECT_FAILED: Serial.println("  ❌ 연결 실패(WL_CONNECT_FAILED)"); break;
      case WL_CONNECTION_LOST: Serial.println("  ❌ 연결 끊김"); break;
      case WL_DISCONNECTED: Serial.println("  ❌ 연결 안 됨"); break;
      default: Serial.println("  ❓ 알 수 없는 상태"); break;
    }
  }
  
  
  void loop() {
    unsigned long currentMillis = millis();
    int wifiStatus = WiFi.status();
    
    if (wifiStatus == WL_CONNECTED) {
      if (!isConnected) {
        // Just connected
        isConnected = true;
        // Blink quickly 3 times to indicate connection
        for (int i = 0; i < 3; i++) {
          digitalWrite(LED_PIN, LED_ON);
          delay(100);
          digitalWrite(LED_PIN, LED_OFF);
          delay(100);
        }
        Serial.println("\n✅ WiFi 연결 성공!");
        Serial.print("IP 주소: ");
        Serial.println(WiFi.localIP());
      }
      
      // Steady blink when connected (1 second on, 1 second off)
      if (currentMillis - previousHeartbeatMillis >= 1000) {
        previousHeartbeatMillis = currentMillis;
        digitalWrite(LED_PIN, (digitalRead(LED_PIN) == LED_OFF) ? LED_ON : LED_OFF);
      }
    } else {
      // Not connected - show heartbeat pattern
      isConnected = false;
      if (currentMillis - previousHeartbeatMillis >= HEARTBEAT_PATTERN[heartbeatStep]) {
        previousHeartbeatMillis = currentMillis;
        digitalWrite(LED_PIN, (heartbeatStep % 2 == 0) ? LED_ON : LED_OFF);
        heartbeatStep = (heartbeatStep + 1) % HEARTBEAT_PATTERN_LENGTH;
      }
    }
    
    // 상태 체크 반복 (10초마다)
    static unsigned long lastCheck = 0;
    if (currentMillis - lastCheck > 10000) {
      lastCheck = currentMillis;
      Serial.printf("[WiFi 상태] Status: %d (%s)\n", 
                   wifiStatus,
                   wifiStatus == WL_CONNECTED ? "Connected" : "Not Connected");
    }
  }