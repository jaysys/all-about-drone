#include <Arduino.h>
#include <Wire.h>
#include "DebugSerial.h"
#include "maqueenWheelManager.h"

// Wheel speed (0-255)
#define WHEEL_SPEED 150

// LED pin configuration
#define LED_PIN 8
#define LED_ON  LOW
#define LED_OFF HIGH

// Movement timing
unsigned long lastStateChange = 0;
const unsigned long MOVE_DURATION = 2000;  // 2 seconds per movement

// Movement states
enum class MovementState {
  STOP,
  FORWARD,
  BACKWARD,
  TURN_LEFT,
  TURN_RIGHT,
  ROTATE_LEFT,
  ROTATE_RIGHT
};

MovementState currentState = MovementState::STOP;

void setup() {
  // Initialize serial
  DebugSerial::begin(115200, -1);
  
  if (!DebugSerial::waitForConnection(10000)) {
    DebugSerial::printlnDebug("[DEBUG] No serial connection, entering blink mode");
    while (true) {
      for (int i = 0; i < 3; i++) {
        digitalWrite(LED_PIN, LED_ON);
        delay(100);
        digitalWrite(LED_PIN, LED_OFF);
        delay(50);
      }
      delay(100);
    }
  }
  
  DebugSerial::printSystemInfo();
  
  // Initialize LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LED_OFF);
  
  // Initialize Maqueen wheel manager
  // I2C address: 0x10, SDA: 5, SCL: 6 for ESP32-C3
  Maqueen.begin(0x10, 5, 6);
  
  DebugSerial::printlnDebug("Maqueen Wheel Manager initialized");
  
  // Initial delay to ensure everything is ready
  delay(1000);
  
  // Start with stop state
  currentState = MovementState::STOP;
  lastStateChange = millis();
}

void loop() {
  unsigned long currentTime = millis();
  
  // Change movement state every MOVE_DURATION milliseconds
  if (currentTime - lastStateChange >= MOVE_DURATION) {
    lastStateChange = currentTime;
    
    // Move to next state
    switch (currentState) {
      case MovementState::STOP:
        DebugSerial::printlnDebug("Moving FORWARD");
        Maqueen.forward(WHEEL_SPEED);
        currentState = MovementState::FORWARD;
        digitalWrite(LED_PIN, LED_ON);
        break;
        
      case MovementState::FORWARD:
        DebugSerial::printlnDebug("Moving BACKWARD");
        Maqueen.backward(WHEEL_SPEED);
        currentState = MovementState::BACKWARD;
        break;
        
      case MovementState::BACKWARD:
        DebugSerial::printlnDebug("Turning LEFT");
        Maqueen.turnLeft(WHEEL_SPEED);
        currentState = MovementState::TURN_LEFT;
        break;
        
      case MovementState::TURN_LEFT:
        DebugSerial::printlnDebug("Turning RIGHT");
        Maqueen.turnRight(WHEEL_SPEED);
        currentState = MovementState::TURN_RIGHT;
        break;
        
      case MovementState::TURN_RIGHT:
        DebugSerial::printlnDebug("Rotating LEFT");
        Maqueen.rotateLeft(WHEEL_SPEED);
        currentState = MovementState::ROTATE_LEFT;
        break;
        
      case MovementState::ROTATE_LEFT:
        DebugSerial::printlnDebug("Rotating RIGHT");
        Maqueen.rotateRight(WHEEL_SPEED);
        currentState = MovementState::ROTATE_RIGHT;
        digitalWrite(LED_PIN, LED_OFF);
        break;
        
      case MovementState::ROTATE_RIGHT:
        DebugSerial::printlnDebug("STOPPING");
        Maqueen.stop();
        currentState = MovementState::STOP;
        delay(1000);  // Pause at stop state
        break;
    }
  }
  
  // Small delay to prevent watchdog issues
  delay(10);
}