#include "oledDisplayManager.h"
#include <string.h>  // for strlen

// Initialize static member variables
constexpr int DisplayManager::width;
constexpr int DisplayManager::height;
constexpr int DisplayManager::xOffset;
constexpr int DisplayManager::yOffset;

// Constructor
DisplayManager::DisplayManager() 
    : u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5) {
}

// Initialize display
void DisplayManager::begin() {
    // Add initial delay after power-up
    delay(100);
    
    // Initialize with lower clock speed
    u8g2.begin();
    
    // Add delay after begin()
    delay(50);
    
    // Set contrast and other parameters
    u8g2.setContrast(150);  // Reduced from 255 for better reliability
    u8g2.setBusClock(100000);  // Reduced from 400kHz to 100kHz
    u8g2.setFont(u8g2_font_ncenB10_tr);
    
    // Optional: Add display clear and buffer reset
    u8g2.clearBuffer();
    u8g2.sendBuffer();
    delay(10);
}

// Clear display
void DisplayManager::clear() {
    u8g2.clearBuffer();
    u8g2.sendBuffer();
}

// Draw frame
void DisplayManager::drawFrame() {
    u8g2.drawFrame(xOffset, yOffset, width, height);
}

// Display 2 lines of text
void DisplayManager::display2Lines(const char* line1, const char* line2, TextAlign align) {
    u8g2.clearBuffer();
    
    // Fill background with white
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, 0, 128, 64);
    
    // Switch to black for text and frame
    u8g2.setDrawColor(0);
    
    // Draw frame
    drawFrame();
    
    // Text output settings
    int lineHeight = 15; // Line spacing
    int textY = yOffset + (height - (lineHeight * 2)) / 2 + lineHeight - 2; // Vertical centering
    int textX;
    
    // First line
    if (line1 && strlen(line1)) {
        switch(align) {
            case ALIGN_CENTER:
                textX = xOffset + (width - u8g2.getStrWidth(line1)) / 2;
                break;
            case ALIGN_RIGHT:
                textX = xOffset + width - u8g2.getStrWidth(line1) - 2; // Right margin 2px
                break;
            case ALIGN_LEFT:
            default:
                textX = xOffset + 2; // Left margin 2px
        }
        u8g2.setCursor(textX, textY - lineHeight/2);
        u8g2.print(line1);
    }
    
    // Second line
    if (line2 && strlen(line2)) {
        switch(align) {
            case ALIGN_CENTER:
                textX = xOffset + (width - u8g2.getStrWidth(line2)) / 2;
                break;
            case ALIGN_RIGHT:
                textX = xOffset + width - u8g2.getStrWidth(line2) - 2; // Right margin 2px
                break;
            case ALIGN_LEFT:
            default:
                textX = xOffset + 2; // Left margin 2px
        }
        u8g2.setCursor(textX, textY + lineHeight/2);
        u8g2.print(line2);
    }
    
    u8g2.sendBuffer();
}

void DisplayManager::display4Lines(const char* line1, const char* line2, const char* line3, const char* line4, TextAlign align) {
    u8g2.clearBuffer();
    
    // Fill background with white
    u8g2.setDrawColor(1);
    u8g2.drawBox(0, 0, 128, 64);
    
    // Switch to black for text and frame
    u8g2.setDrawColor(0);
    
    // Draw frame
    drawFrame();
    
    // Change to smaller font (ncenB08)
    u8g2.setFont(u8g2_font_ncenB08_tr);
    
    // Text output settings
    int fontHeight = 8;      // Font height (pixels)
    int lineSpacing = 2;     // Line spacing (pixels)
    int totalTextHeight = (fontHeight + lineSpacing) * 4 - lineSpacing;  // Total text height
    int startY = yOffset + (height - totalTextHeight) / 2;  // Starting Y position for vertical centering
    
    // Text output for each line
    const char* lines[4] = {line1, line2, line3, line4};
    
    for (int i = 0; i < 4; i++) {
        if (lines[i] && strlen(lines[i])) {
            // Calculate text width (based on current font)
            int textWidth = u8g2.getStrWidth(lines[i]);
            
            // Calculate X position based on alignment
            int textX;
            switch(align) {
                case ALIGN_CENTER:
                    textX = xOffset + (width - textWidth) / 2;
                    break;
                case ALIGN_RIGHT:
                    textX = xOffset + width - textWidth - 2; // Right margin 2px
                    break;
                case ALIGN_LEFT:
                default:
                    textX = xOffset + 2; // Left margin 2px
            }
            
            // Calculate Y position (fixed spacing)
            int textY = startY + (fontHeight + lineSpacing) * i + fontHeight - 1;
            
            // Ensure last line doesn't go outside the frame
            if (textY > yOffset + height - 2) {
                textY = yOffset + height - 2;
            }
            
            u8g2.setCursor(textX, textY);
            u8g2.print(lines[i]);
        }
    }
    
    u8g2.sendBuffer();
    // Restore default font
    u8g2.setFont(u8g2_font_ncenB10_tr);
}
