#ifndef DEBUG_SERIAL_H
#define DEBUG_SERIAL_H

#include <Arduino.h>

class DebugSerial {
public:
    // Initialize serial communication
    static void begin(unsigned long baudrate = 115200, int ledPin = -1);
    
    // Wait for serial connection with timeout (in milliseconds)
    static bool waitForConnection(unsigned long timeout = 10000);
    
    // Print system information
    static void printSystemInfo();
    
    // Print a debug message with timestamp
    static void printDebug(const String& message);
    
    // Print a debug message with timestamp and newline
    static void printlnDebug(const String& message);
    
    // Blink LED pattern (for visual feedback)
    static void blinkPattern(int times = 1, int onTime = 100, int offTime = 100);
    
private:
    static int _ledPin;
    static bool _ledActive;
    
    static void _blinkLED(int times = 1, int onTime = 100, int offTime = 100);
};

#endif // DEBUG_SERIAL_H
