#include <Arduino.h>
#include "DebugSerial.h"
#include "oledDisplayManager.h"

// LED pin configuration
#define LED_PIN 8

// LED 상태 재정의 (ESP32-C3 내장 LED는 Active-Low 동작)
#define LED_ON  LOW
#define LED_OFF HIGH

// Test states
enum TestState {
  TEST_OFF,
  TEST_ON,
  TEST_BLINK,
  TEST_FAST_BLINK,
  TEST_PULSE,
  TEST_TOGGLE,
  TEST_DONE
};

// Global variables
TestState currentTest = TEST_OFF;
unsigned long testStartTime = 0;
bool ledState = false;
unsigned long lastToggleTime = 0;
float pulseValue = 0;
bool pulseDirection = true;

void setup() {
  // Initialize serial
  DebugSerial::begin(115200, -1);
  if (!DebugSerial::waitForConnection(10000)) {
    DebugSerial::printlnDebug("[DEBUG] No serial connection, entering blink mode");
    // If no connection, blink pattern
    while (true) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_PIN, LED_ON);
        DebugSerial::printlnDebug("LED ON");
        delay(100);
        digitalWrite(LED_PIN, LED_OFF);
        DebugSerial::printlnDebug("LED OFF");
        delay(50);
      }
      delay(100);
    }
  }
  DebugSerial::printSystemInfo();

  DebugSerial::printlnDebug("=== Starting LED Test ===");
  
  // Initialize OLED display
  Display.begin();
  Display.clear();
  Display.display4Lines("LED Test", "ESP32-C3", "Starting...", "");
  delay(1000);

  // Initialize LED pin
  DebugSerial::printlnDebug("LED pin initializing to OUTPUT");
  DebugSerial::printDebug("Testing LED on pin: ");
  DebugSerial::printlnDebug(String(LED_PIN));
  pinMode(LED_PIN, OUTPUT);  // 핀 모드 설정
  digitalWrite(LED_PIN, LED_OFF);  // 초기 상태로 설정

  // Test LED with more detailed feedback
  DebugSerial::printlnDebug("--- LED Connection Test ---");
  for (int i = 0; i < 3; i++) {
    DebugSerial::printDebug("Setting LED_PIN ");
    DebugSerial::printDebug(String(LED_PIN));
    DebugSerial::printlnDebug(" ON");
    pinMode(LED_PIN, OUTPUT);  // 핀 모드 설정
    digitalWrite(LED_PIN, LED_ON);
    delay(500);
    
    DebugSerial::printDebug("Setting LED_PIN ");
    DebugSerial::printDebug(String(LED_PIN));
    DebugSerial::printlnDebug(" OFF");
    // pinMode는 이미 설정되었으므로 생략 가능
    digitalWrite(LED_PIN, LED_OFF);
    delay(500);
  }
  
  testStartTime = millis();
}

void loop() {
  unsigned long currentTime = millis();
  
  // Change test every 10 seconds
  if (currentTime - testStartTime >= 10000) {
    testStartTime = currentTime;
    lastToggleTime = currentTime;
    
    // Move to next test state
    currentTest = (TestState)((int)currentTest + 1);
    
    if (currentTest > TEST_DONE) {
      currentTest = TEST_OFF;
      digitalWrite(LED_PIN, LED_OFF);
      ledState = false;
      DebugSerial::printlnDebug("--- TEST CYCLE RESTARTED ---");
    }
    
    // 디버그 정보 출력
    String debugMsg = "\n[DEBUG] Current Test: ";
    debugMsg += String((int)currentTest);
    debugMsg += " (";
    switch(currentTest) {
      case TEST_OFF: debugMsg += "OFF"; break;
      case TEST_ON: debugMsg += "ON"; break;
      case TEST_BLINK: debugMsg += "BLINK"; break;
      case TEST_FAST_BLINK: debugMsg += "FAST_BLINK"; break;
      case TEST_PULSE: debugMsg += "PULSE"; break;
      case TEST_TOGGLE: debugMsg += "TOGGLE"; break;
      case TEST_DONE: debugMsg += "DONE"; break;
      default: debugMsg += "UNKNOWN";
    }
    debugMsg += ")";
    DebugSerial::printlnDebug(debugMsg);
    
    // LED 핀 상태 디버그
    debugMsg = "[DEBUG] Before change - LED_PIN: ";
    debugMsg += (digitalRead(LED_PIN) == LED_ON) ? "ON" : "OFF";
    debugMsg += ", ledState: ";
    debugMsg += ledState ? "ON" : "OFF";
    DebugSerial::printlnDebug(debugMsg);
    
    // Initialize the new test
    char lineBuffer[16];  // Buffer for display lines
    switch (currentTest) {
      case TEST_OFF:
        pinMode(LED_PIN, OUTPUT);  // 핀 모드 설정
        digitalWrite(LED_PIN, LED_OFF);
        ledState = false;
        DebugSerial::printlnDebug("--- TEST: LED OFF ---");
        debugMsg = "[DEBUG] LED should be OFF - LED_PIN: ";
        debugMsg += (digitalRead(LED_PIN) == LED_ON) ? "ON" : "OFF";
        DebugSerial::printlnDebug(debugMsg);
        snprintf(lineBuffer, sizeof(lineBuffer), "Pin: %d", LED_PIN);
        Display.display4Lines("OFF", "LED: Off", lineBuffer, "Active Low");
        break;
        
      case TEST_ON:
        pinMode(LED_PIN, OUTPUT);  // 핀 모드 설정
        digitalWrite(LED_PIN, LED_ON);
        ledState = true;
        DebugSerial::printlnDebug("--- TEST: LED ON ---");
        debugMsg = "[DEBUG] LED should be ON - LED_PIN: ";
        debugMsg += (digitalRead(LED_PIN) == LED_ON) ? "ON" : "OFF";
        DebugSerial::printlnDebug(debugMsg);
        snprintf(lineBuffer, sizeof(lineBuffer), "Pin: %d", LED_PIN);
        Display.display4Lines("ON", "LED: On", lineBuffer, "Active Low");
        break;
        
      case TEST_BLINK:
        pinMode(LED_PIN, OUTPUT);  // 핀 모드 설정
        digitalWrite(LED_PIN, LED_OFF);
        ledState = false;
        DebugSerial::printlnDebug("\n--- TEST: BLINK (500ms) ---");
        snprintf(lineBuffer, sizeof(lineBuffer), "Pin: %d", LED_PIN);
        Display.display4Lines("BLINK", "Interval: 500ms", lineBuffer, "Active Low");
        break;
        
      case TEST_FAST_BLINK:
        pinMode(LED_PIN, OUTPUT);  // 핀 모드 설정
        digitalWrite(LED_PIN, LED_OFF);
        ledState = false;
        DebugSerial::printlnDebug("\n--- TEST: FAST BLINK (200ms) ---");
        snprintf(lineBuffer, sizeof(lineBuffer), "Pin: %d", LED_PIN);
        Display.display4Lines("FAST BLINK", "Interval: 200ms", lineBuffer, "Active Low");
        break;
        
      case TEST_PULSE:
        pinMode(LED_PIN, OUTPUT);  // 핀 모드 설정
        pulseValue = 0;
        pulseDirection = true;
        DebugSerial::printlnDebug("\n--- TEST: PULSE (fade in/out) ---");
        snprintf(lineBuffer, sizeof(lineBuffer), "Pin: %d", LED_PIN);
        Display.display4Lines("PULSE", "Fade In/Out", "PWM Control", lineBuffer);
        break;
        
      case TEST_TOGGLE:
        pinMode(LED_PIN, OUTPUT);  // 핀 모드 설정
        digitalWrite(LED_PIN, LED_OFF);
        ledState = false;
        DebugSerial::printlnDebug("\n--- TEST: TOGGLE (500ms) ---");
        snprintf(lineBuffer, sizeof(lineBuffer), "Pin: %d", LED_PIN);
        Display.display4Lines("TOGGLE", "Interval: 1s", lineBuffer, "Active Low");
        break;
        
      case TEST_DONE:
        pinMode(LED_PIN, OUTPUT);  // 핀 모드 설정
        digitalWrite(LED_PIN, LED_OFF);
        ledState = false;
        DebugSerial::printlnDebug("\n--- ALL TESTS COMPLETE! ---");
        Display.display4Lines("CYCLE", "COMPLETE", "Restarting...", "");
        break;
    }
  }
  
  // Update current test
  switch (currentTest) {
    case TEST_BLINK:
      if (currentTime - lastToggleTime >= 500) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? LED_ON : LED_OFF);
        lastToggleTime = currentTime;
      }
      break;
      
    case TEST_FAST_BLINK:
      if (currentTime - lastToggleTime >= 200) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? LED_ON : LED_OFF);
        lastToggleTime = currentTime;
      }
      break;
      
    case TEST_PULSE:
      if (pulseDirection) {
        pulseValue += 5;
        if (pulseValue >= 255) {
          pulseValue = 255;
          pulseDirection = false;
        }
      } else {
        pulseValue -= 5;
        if (pulseValue <= 0) {
          pulseValue = 0;
          pulseDirection = true;
        }
      }
      analogWrite(LED_PIN, (int)pulseValue);
      break;
      
    case TEST_TOGGLE:
      if (currentTime - lastToggleTime >= 1000) {  // Changed to 1 second for better visibility
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState ? LED_ON : LED_OFF);
        DebugSerial::printDebug("[TOGGLE] LED_PIN set to: ");
        DebugSerial::printlnDebug(ledState ? "ON" : "OFF");
        DebugSerial::printDebug("[TOGGLE] Reading back from pin: ");
        DebugSerial::printlnDebug((digitalRead(LED_PIN) == LED_ON) ? "ON" : "OFF");
        lastToggleTime = currentTime;
      }
      break;
      
    default:
      // No action needed for other states
      break;
  }
  
  // Small delay to prevent watchdog issues
  delay(10);
}
