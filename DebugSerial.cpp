#include "DebugSerial.h"
#include <Arduino.h>

int DebugSerial::_ledPin = -1;
bool DebugSerial::_ledActive = false;

void DebugSerial::begin(unsigned long baudrate, int ledPin) {
    // Initialize serial communication
    Serial.begin(baudrate);
    
    // Set LED pin if provided
    if (ledPin >= 0) {
        _ledPin = ledPin;
        pinMode(_ledPin, OUTPUT);
        _ledActive = true;
        digitalWrite(_ledPin, LOW);
    }
    
    // Visual feedback
    blinkPattern(2, 100, 50);
}

bool DebugSerial::waitForConnection(unsigned long timeout) {
    unsigned long startTime = millis();
    
    // Wait for serial connection with timeout
    while (!Serial && (millis() - startTime < timeout)) {
        _blinkLED(1, 100, 100);
    }
    
    // Connection feedback
    if (Serial) {
        blinkPattern(3, 100, 50);
        return true;
    }
    
    return false;
}

void DebugSerial::printSystemInfo() {
    if (!Serial) return;
    
    Serial.println("\n=================================");
    Serial.println("SYSTEM INFORMATION");
    Serial.println("=================================");
    
#ifdef ESP32
    Serial.print("Chip: ");
    Serial.println(ESP.getChipModel());
    Serial.print("Revision: ");
    Serial.println(ESP.getChipRevision());
    Serial.print("CPU Freq: ");
    Serial.print(ESP.getCpuFreqMHz());
    Serial.println(" MHz");
    Serial.print("Free Heap: ");
    Serial.print(ESP.getFreeHeap() / 1024.0);
    Serial.println(" KB");
    Serial.print("Flash Size: ");
    Serial.print(ESP.getFlashChipSize() / (1024.0 * 1024), 1);
    Serial.println(" MB");
#else
    Serial.println("Board: Arduino");
    Serial.print("Free RAM: ");
    Serial.print(freeMemory() / 1024.0);
    Serial.println(" KB");
#endif
    
    Serial.print("Baud Rate: ");
    Serial.println(Serial.baudRate());
    Serial.println("=================================\n");
    Serial.flush();
}

void DebugSerial::printDebug(const String& message) {
    if (!Serial) return;
    Serial.print("[");
    Serial.print(millis() / 1000.0, 3);
    Serial.print("] ");
    Serial.print(message);
    Serial.flush();
}

void DebugSerial::printlnDebug(const String& message) {
    printDebug(message + "\n");
}

void DebugSerial::blinkPattern(int times, int onTime, int offTime) {
    if (_ledActive) {
        _blinkLED(times, onTime, offTime);
    }
}

void DebugSerial::_blinkLED(int times, int onTime, int offTime) {
    if (!_ledActive) return;
    
    for (int i = 0; i < times; i++) {
        digitalWrite(_ledPin, HIGH);
        delay(onTime);
        digitalWrite(_ledPin, LOW);
        if (i < times - 1) delay(offTime);
    }
}
