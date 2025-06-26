#include "oledDisplayManager.h"
#include <Wire.h>

// 전역 DisplayManager 인스턴스 생성
DisplayManager& display = DisplayManager::getInstance();

// I2C 주소 (Maqueen V3 기본 주소)
#define MAQUEEN_I2C_ADDR 0x10

// 모터 속도 (0-255)
#define MOTOR_SPEED 100
#define TURN_DELAY 1000  // 회전 시 지연 시간 (ms)

// 모터 제어 명령어
#define MOTOR_STOP 0x02
#define MOTOR_MOVE 0x00
#define MOTOR_LEFT 0x00
#define MOTOR_RIGHT 0x02

// 모터 상태 열거형
enum MotorState {
  STOP,
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

// 현재 모터 상태
MotorState currentState = STOP;

// I2C로 모터 제어
void setMotor(uint8_t motor, uint8_t dir, uint8_t speed) {
  Wire.beginTransmission(MAQUEEN_I2C_ADDR);
  Wire.write(motor);
  Wire.write(dir);
  Wire.write(speed);
  Wire.endTransmission();
}

void setup() {
  // 시리얼 통신 시작
  Serial.begin(115200);
  
  // I2C 초기화 (Maqueen V3는 I2C로 제어됨)
  Wire.begin(6, 5);  // SDA=6, SCL=5 (ESP32-C3 기본 핀)
  
  // 디스플레이 초기화
  display.begin();
  display.display2Lines("Maqueen V3", "Ready!");
  
  Serial.println("Maqueen V3 초기화 완료");
  delay(1000);
}

// 모터 제어 함수
void controlMotors(MotorState state) {
  switch (state) {
    case FORWARD:
      // display.display2Lines(":", "FORWARD");  
      // delay(500);
      setMotor(0x00, 0x00, MOTOR_SPEED);  // Left motor forward
      setMotor(0x02, 0x00, MOTOR_SPEED);  // Right motor forward

      break;
      
    case BACKWARD:
      // display.display2Lines(":", "BACKWARD");
      // delay(500);
      setMotor(0x00, 0x01, MOTOR_SPEED);  // Left motor backward
      setMotor(0x02, 0x01, MOTOR_SPEED);  // Right motor backward

      break;
      
    case LEFT:
      // display.display2Lines(":", "LEFT");
      // delay(500);
      setMotor(0x00, 0x01, MOTOR_SPEED);  // Left motor backward
      setMotor(0x02, 0x00, MOTOR_SPEED);  // Right motor forward

      break;
      
    case RIGHT:
      // display.display2Lines(":", "RIGHT");
      // delay(500);
      setMotor(0x00, 0x00, MOTOR_SPEED);  // Left motor forward
      setMotor(0x02, 0x01, MOTOR_SPEED);  // Right motor backward

      break;
      
    case STOP:
    default:
      // display.display2Lines(":", "STOP");
      setMotor(0x00, 0x00, 0);  // Stop left motor
      setMotor(0x02, 0x00, 0);  // Stop right motor
      break;
  }
  currentState = state;
}

void loop() {
  // 정지 상태에서 시작
  if (currentState != STOP) {
    controlMotors(STOP);
    delay(1000);
  }
  
  // 전진
  controlMotors(FORWARD);
  delay(2000);
  controlMotors(STOP);
  delay(1000);
  
  // 후진
  controlMotors(BACKWARD);
  delay(2000);
  controlMotors(STOP);
  delay(1000);
  
  // 좌회전
  controlMotors(LEFT);
  delay(TURN_DELAY);
  controlMotors(STOP);
  delay(1000);
  
  // 우회전
  controlMotors(RIGHT);
  delay(TURN_DELAY);
  controlMotors(STOP);
  delay(1000);
  
  // 4줄로 상태 표시
  char speedStr[20];
  sprintf(speedStr, "Speed: %d", MOTOR_SPEED);
  display.display4Lines("Maqueen V3", "Status:", speedStr, "Running...");
  delay(2000);

}