#ifndef OLED_DISPLAY_MANAGER_H
#define OLED_DISPLAY_MANAGER_H

#include <U8g2lib.h>
#include <Wire.h>

// 텍스트 정렬 옵션
enum TextAlign { ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT };

class DisplayManager {
public:
    // 싱글톤 인스턴스 반환
    static DisplayManager& getInstance() {
        static DisplayManager instance;
        return instance;
    }

    // 초기화
    void begin();

    // 2줄 텍스트 표시 함수
    void display2Lines(const char* line1, const char* line2, TextAlign align = ALIGN_LEFT);
    
    // 4줄 텍스트 표시 함수
    void display4Lines(const char* line1, const char* line2, const char* line3 = "", 
                      const char* line4 = "", TextAlign align = ALIGN_LEFT);

    // 화면 크기 접근자
    static constexpr int width = 72;
    static constexpr int height = 40;

    // 화면 지우기
    void clear();

private:
    // 생성자/소멸자 private로 선언하여 싱글톤 패턴 유지
    DisplayManager();
    ~DisplayManager() = default;
    DisplayManager(const DisplayManager&) = delete;
    DisplayManager& operator=(const DisplayManager&) = delete;

    // U8G2 인스턴스
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
    
    // 화면 오프셋
    static constexpr int xOffset = 28;  // = (132-width)/2 - 2 (왼쪽으로 2픽셀 이동)
    static constexpr int yOffset = 24;  // = (64-height)/2 + 12 (아래로 10픽셀 이동)

    // 프레임 그리기
    void drawFrame();
};

inline DisplayManager& Display = DisplayManager::getInstance();

#endif
