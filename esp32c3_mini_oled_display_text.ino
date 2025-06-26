#include <U8g2lib.h>
#include <Wire.h>

// u8g2에는 72x40 생성자가 없으므로 72x40 화면은
// SSD1306 컨트롤러의 132x64 픽셀 버퍼 중앙에 매핑됩니다
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 6, 5);

// 화면 설정
int width = 72;
int height = 40;
int xOffset = 28;  // = (132-width)/2 - 2 (왼쪽으로 2픽셀 이동)
int yOffset = 24;  // = (64-height)/2 + 12 (아래로 10픽셀 이동)

// 텍스트 정렬 옵션
enum TextAlign { ALIGN_LEFT, ALIGN_CENTER, ALIGN_RIGHT };

// 2줄 텍스트 표시 함수 (기본값: 좌측정렬)
void display2Lines(const char* line1, const char* line2, TextAlign align = ALIGN_LEFT) {
  u8g2.clearBuffer();
  
  // 배경을 흰색으로 채우기
  u8g2.setDrawColor(1);
  u8g2.drawBox(0, 0, 128, 64);
  
  // 검은색으로 전환 (텍스트와 프레임용)
  u8g2.setDrawColor(0);
  
  // 프레임 그리기
  u8g2.drawFrame(xOffset, yOffset, width, height);
  
  // 텍스트 출력
  int lineHeight = 15; // 줄 간격
  int textY = yOffset + (height - (lineHeight * 2)) / 2 + lineHeight - 2; // 수직 중앙 정렬
  int textX;
  
  // 첫 번째 줄
  if (line1 && strlen(line1)) {
    switch(align) {
      case ALIGN_CENTER:
        textX = xOffset + (width - u8g2.getStrWidth(line1)) / 2;
        break;
      case ALIGN_RIGHT:
        textX = xOffset + width - u8g2.getStrWidth(line1) - 2; // 우측 여백 2픽셀
        break;
      case ALIGN_LEFT:
      default:
        textX = xOffset + 2; // 좌측 여백 2픽셀
    }
    u8g2.setCursor(textX, textY - lineHeight/2);
    u8g2.print(line1);
  }
  
  // 두 번째 줄
  if (line2 && strlen(line2)) {
    switch(align) {
      case ALIGN_CENTER:
        textX = xOffset + (width - u8g2.getStrWidth(line2)) / 2;
        break;
      case ALIGN_RIGHT:
        textX = xOffset + width - u8g2.getStrWidth(line2) - 2; // 우측 여백 2픽셀
        break;
      case ALIGN_LEFT:
      default:
        textX = xOffset + 2; // 좌측 여백 2픽셀
    }
    u8g2.setCursor(textX, textY + lineHeight/2);
    u8g2.print(line2);
  }
  
  u8g2.sendBuffer();
}

// 4줄 텍스트 표시 함수 (기본값: 좌측정렬)
void display4Lines(const char* line1, const char* line2 = "", const char* line3 = "", const char* line4 = "", TextAlign align = ALIGN_LEFT) {
  u8g2.clearBuffer();
  
  // 배경을 흰색으로 채우기
  u8g2.setDrawColor(1);
  u8g2.drawBox(0, 0, 128, 64);
  
  // 검은색으로 전환 (텍스트와 프레임용)
  u8g2.setDrawColor(0);
  
  // 프레임 그리기
  u8g2.drawFrame(xOffset, yOffset, width, height);
  
  // 더 작고 가는 폰트로 변경 (ncenB08)
  u8g2.setFont(u8g2_font_ncenB08_tr);
  
  // 텍스트 출력 설정
  int fontHeight = 8;      // 폰트 높이 (픽셀)
  int lineSpacing = 2;     // 줄 간격 (픽셀)
  int topMargin = 1;        // 상단 여백 (픽셀)
  int totalTextHeight = (fontHeight + lineSpacing) * 4 - lineSpacing;  // 전체 텍스트 높이
  int startY = yOffset + (height - totalTextHeight) / 2;  // 수직 중앙 정렬을 위한 시작 Y 위치
  int textX;
  
  // 각 줄에 대한 텍스트 출력
  const char* lines[4] = {line1, line2, line3, line4};
  
  for (int i = 0; i < 4; i++) {
    if (lines[i] && strlen(lines[i])) {
      // 텍스트 너비 계산 (현재 폰트 기준)
      int textWidth = u8g2.getStrWidth(lines[i]);
      
      // 정렬에 따른 X 위치 계산
      switch(align) {
        case ALIGN_CENTER:
          textX = xOffset + (width - textWidth) / 2;
          break;
        case ALIGN_RIGHT:
          textX = xOffset + width - textWidth - 2; // 우측 여백 2픽셀
          break;
        case ALIGN_LEFT:
        default:
          textX = xOffset + 2; // 좌측 여백 2픽셀
      }
      
      // Y 위치 계산 (고정된 간격 사용)
      int textY = startY + (fontHeight + lineSpacing) * i + fontHeight - 1;
      
      // 마지막 줄이 프레임을 벗어나지 않도록 보정
      if (textY > yOffset + height - 2) {
        textY = yOffset + height - 2;
      }
      
      u8g2.setCursor(textX, textY);
      u8g2.print(lines[i]);
    }
  }
  
  u8g2.sendBuffer();
}

void setup(void) {
  // 시리얼 통신 시작
  Serial.begin(115200);
  
  // 디스플레이 초기화
  delay(1000);
  u8g2.begin();
  u8g2.setContrast(255);  // 대비를 최대로 설정
  u8g2.setBusClock(400000);  // I2C 클럭 400kHz로 설정
  u8g2.setFont(u8g2_font_ncenB10_tr);
  
  Serial.println("OLED 초기화 완료");
}

void loop(void) {
  // 2줄 예제 (좌측정렬 - 기본값)
  display2Lines("Left Align", "Hello!");
  delay(2000);
  
  // 2줄 예제 (가운데정렬)
  display2Lines("Center", "Aligned!", ALIGN_CENTER);
  delay(2000);
  
  // 2줄 예제 (우측정렬)
  display2Lines("Right", "Aligned!", ALIGN_RIGHT);
  delay(2000);
  
  // 4줄 예제 (좌측정렬 - 기본값)
  display4Lines("Line 1", "Left", "Aligned", "Text");
  delay(2000);
  
  // 4줄 예제 (가운데정렬)
  display4Lines("Line 1", "Center", "Aligned", "Text", ALIGN_CENTER);
  delay(2000);
  
  // 4줄 예제 (우측정렬)
  display4Lines("Line 1", "Right", "Aligned", "Text", ALIGN_RIGHT);
  delay(2000);
  
  // 기존 예제 (사이즈 표시)
  char sizeText[20];
  snprintf(sizeText, sizeof(sizeText), "%dx%d", width, height);
  display2Lines("Display Size:", sizeText, ALIGN_CENTER);
  delay(2000);
}