#include <WiFi.h>
#include <SPIFFS.h>
#include <FS.h>
#include <EEPROM.h>
#include <esp_ota_ops.h>

// LED pin definition for ESP32-C3-MINI
const int LED_PIN = 8;  // Built-in LED pin
unsigned long previousMillis = 0;
const long interval = 500;  // Blink interval in milliseconds
bool ledState = false;      // Track LED state

// 파티션 상태를 출력하는 함수
void printPartitionStatus() {
  // 1. 프로그램 공간 상태 확인 (nvs, ota, app, spiffs 등)
  Serial.println("==== 파티션 상태 ====");

  // 전체 플래시 정보 출력
  Serial.printf("총 플래시 크기: %d 바이트\n", ESP.getFlashChipSize());
  // 플래시 페이지 크기와 블록 크기는 ESP32-C3에서 사용할 수 없음
  // Serial.printf("플래시 페이지 크기: %d 바이트\n", ESP.getFlashChipSectorSize());
  // Serial.printf("플래시 블록 크기: %d 바이트\n", ESP.getFlashChipBlockSize());
  // Serial.printf("플래시 쓰기 횟수 제한: %d\n", ESP.getFlashChipEraseCycles());

  // NVS 파티션 상태 (Wi-Fi, BLE 설정 저장)
  size_t nvs_total = ESP.getFlashChipSize() / 2; // 가정: NVS 영역 절반
  size_t nvs_used = 0; // 실제 사용량을 얻을 수 없으므로 예시로 설정
  Serial.printf("NVS 파티션 - 총 크기: %d 바이트, 사용된 크기: %d 바이트\n", nvs_total, nvs_used);

  // SPIFFS 상태
  if (SPIFFS.begin(true)) {
    uint32_t total_spiffs = SPIFFS.totalBytes();
    uint32_t used_spiffs = SPIFFS.usedBytes();
    Serial.printf("SPIFFS - 총 크기: %d 바이트, 사용된 크기: %d 바이트\n", total_spiffs, used_spiffs);
  } else {
    Serial.println("SPIFFS 초기화 실패");
  }

  // OTA 파티션 상태
  size_t ota_total = ESP.getFlashChipSize() / 4;  // 예시로 4분의 1 크기 할당
  size_t ota_used = 0; // 실제 사용량은 추정하기 어려움
  Serial.printf("OTA 파티션 - 총 크기: %d 바이트, 사용된 크기: %d 바이트\n", ota_total, ota_used);

  // 애플리케이션 프로그램 공간 확인 (app0, app1)
  size_t app_total = ESP.getFlashChipSize() / 2;  // 예시로 프로그램 공간의 절반 크기
  size_t app_used = 0;  // 실제 사용량 추정 불가
  Serial.printf("애플리케이션 - 총 크기: %d 바이트, 사용된 크기: %d 바이트\n", app_total, app_used);

  // EEPROM 상태 확인 (기본적으로 512 바이트)
  EEPROM.begin(512);
  Serial.printf("EEPROM - 총 크기: 512 바이트, 사용된 크기: %d 바이트\n", EEPROM.length());

  // 2. 시스템 정보
  Serial.println("==== 시스템 정보 ====");
  Serial.printf("칩 모델: %s\n", ESP.getChipModel());
  Serial.printf("칩 리비전: %d\n", ESP.getChipRevision());
  Serial.printf("CPU 주파수: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("SDK 버전: %s\n", ESP.getSdkVersion());
  Serial.printf("플래시 크기: %d 바이트\n", ESP.getFlashChipSize());
  Serial.printf("플래시 속도: %d MHz\n", ESP.getFlashChipSpeed() / 1000000);
  Serial.printf("힙 전체 크기: %d 바이트\n", ESP.getHeapSize());
  Serial.printf("남은 힙: %d 바이트\n", ESP.getFreeHeap());
  Serial.printf("최소 남은 힙: %d 바이트\n", ESP.getMinFreeHeap());
  Serial.printf("PSRAM 크기: %d 바이트\n", ESP.getPsramSize());
  Serial.printf("프리 PSRAM: %d 바이트\n", ESP.getFreePsram());
  Serial.printf("업타임: %d일 %02d:%02d:%02d\n", 
              (millis() / 86400000), 
              (millis() / 3600000) % 24, 
              (millis() / 60000) % 60, 
              (millis() / 1000) % 60);

  // 3. Wi-Fi 설정 정보 (NVS 사용)
  Serial.println("==== Wi-Fi 설정 ====");
  Serial.printf("Wi-Fi SSID: %s\n", WiFi.SSID().c_str());
  Serial.printf("Wi-Fi 상태: %s\n", WiFi.status() == WL_CONNECTED ? "연결됨" : "연결 안됨");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("로컬 IP: %s\n", WiFi.localIP().toString().c_str());
    Serial.printf("게이트웨이 IP: %s\n", WiFi.gatewayIP().toString().c_str());
    Serial.printf("서브넷 마스크: %s\n", WiFi.subnetMask().toString().c_str());
    Serial.printf("DNS IP: %s\n", WiFi.dnsIP().toString().c_str());
    Serial.printf("RSSI: %d dBm\n", WiFi.RSSI());
    Serial.printf("MAC 주소: %s\n", WiFi.macAddress().c_str());
  }

  // 4. OTA 관련 정보
  Serial.println("==== OTA 상태 ====");
  const esp_partition_t *running = esp_ota_get_running_partition();
  const esp_partition_t *configured = esp_ota_get_boot_partition();
  
  if (running != NULL && configured != NULL) {
    Serial.printf("현재 실행 파티션: %s\n", running->label);
    Serial.printf("부팅 설정 파티션: %s\n", configured->label);
    
    if (running == configured) {
      Serial.println("부팅 설정과 일치하는 파티션에서 실행 중");
    } else {
      Serial.println("경고: 부팅 설정과 다른 파티션에서 실행 중!");
    }
    
    // 추가 파티션 정보
    Serial.printf("파티션 타입: %d, 서브타입: %d\n", running->type, running->subtype);
    Serial.printf("파티션 주소: 0x%x, 크기: %d 바이트\n", running->address, running->size);
  }
}

void setup() {
    // Initialize Serial
    Serial.begin(115200);
    while (!Serial);  // Wait for USB CDC to be ready
    
    // Initialize WiFi in station mode
    WiFi.mode(WIFI_STA);
    
    // Set the hostname using chip model and MAC address
    String chipModel = String(ESP.getChipModel());
    chipModel.toLowerCase();
    String hostname = chipModel + "-" + String((uint32_t)ESP.getEfuseMac(), HEX);
    WiFi.setHostname(hostname.c_str());
    
    // Initialize LED
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);  // Start with LED off
    
    Serial.println("ESP32 Ready!!! ");
    Serial.print("Hostname: ");
    Serial.println(hostname);

    printPartitionStatus();

  }
  
  void loop() {
    // Handle serial input
    if (Serial.available()) {
      String input = Serial.readStringUntil('\n');
      input.trim();
      if (input == "hostname" || input == "whoami") {
        Serial.print("Hostname: ");
        Serial.println(WiFi.getHostname());
      } else {
        Serial.print("Echo: ");
        Serial.print(input);
        Serial.print(" (Sent from ");
        Serial.print(WiFi.getHostname());
        Serial.println(")");
      }
    }
    
    // Blink the LED
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    }
  }
  