# 드론 센싱 및 데이터 처리 계층 분석

## 1. 물리적 디바이스에서 직접 센싱한 정보 (Raw Sensor Data)

### 1.1 IMU (Inertial Measurement Unit)

| 필드명 | 타입 | 단위 | 설명 | 예시값 |
|--------|------|------|------|--------|
| sensors.imu.accelerometer.x | number | m/s² | X축 가속도 | 0.002649 |
| sensors.imu.accelerometer.y | number | m/s² | Y축 가속도 | -0.008638 |
| sensors.imu.accelerometer.z | number | m/s² | Z축 가속도 | 9.7995 |
| sensors.imu.gyroscope.x | number | rad/s | X축 각속도 | -0.002 |
| sensors.imu.gyroscope.y | number | rad/s | Y축 각속도 | -0.002 |
| sensors.imu.gyroscope.z | number | rad/s | Z축 각속도 | -0.006212 |
| sensors.imu.temperature | number | °C | 센서 온도 | 25.0 |

### 1.2 GPS (Global Positioning System)

| 필드명 | 타입 | 단위 | 설명 | 예시값 |
|--------|------|------|------|--------|
| sensors.gps.latitude | number | degrees | 위도 | 37.5665 |
| sensors.gps.longitude | number | degrees | 경도 | 126.9780 |
| sensors.gps.altitude | number | meters | 고도 | 50.0 |
| sensors.gps.speed | number | m/s | 속도 | 0.0 |
| sensors.gps.course | number | degrees | 방향 | 0.0 |
| sensors.gps.satellites | number | count | 위성 수 | 12 |
| sensors.gps.hdop | number | - | 수평 정밀도 | 1.2 |
| sensors.gps.vdop | number | - | 수직 정밀도 | 1.8 |

### 1.3 기압계 (Barometer)

| 필드명 | 타입 | 단위 | 설명 | 예시값 |
|--------|------|------|------|--------|
| sensors.barometer.pressure | number | hPa | 대기압 | 1013.25 |
| sensors.barometer.temperature | number | °C | 온도 | 25.0 |
| sensors.barometer.altitude | number | meters | 기압 고도 | 50.0 |

### 1.4 자력계 (Magnetometer)
| 필드명 | 타입 | 단위 | 설명 | 예시값 |
|--------|------|------|------|--------|
| sensors.magnetometer.x | number | gauss | X축 자기장 | 0.1234 |
| sensors.magnetometer.y | number | gauss | Y축 자기장 | 0.2345 |
| sensors.magnetometer.z | number | gauss | Z축 자기장 | 0.3456 |
| sensors.magnetometer.declination | number | degrees | 자기 편각 | 7.5 |

### 1.5 거리 센서 (Rangefinder)
| 필드명 | 타입 | 단위 | 설명 | 예시값 |
|--------|------|------|------|--------|
| sensors.rangefinder.distance | number | meters | 측정 거리 | 0.0 |
| sensors.rangefinder.max_distance | number | meters | 최대 측정 거리 | 40.0 |
| sensors.rangefinder.min_distance | number | meters | 최소 측정 거리 | 0.2 |

### 1.6 옵티컬 플로우 (Optical Flow)
| 필드명 | 타입 | 단위 | 설명 | 예시값 |
|--------|------|------|------|--------|
| sensors.optical_flow.flow_x | number | rad/s | X축 플로우 | 0.0 |
| sensors.optical_flow.flow_y | number | rad/s | Y축 플로우 | 0.0 |
| sensors.optical_flow.quality | number | 0-255 | 플로우 품질 | 0 |
| sensors.optical_flow.ground_distance | number | meters | 지면 거리 | 0.0 |

## 2. 1차 가공 정보 (Primary Processed Data)

### 2.1 위치 정보
| 필드명 | 타입 | 단위 | 설명 | 예시값 |
|--------|------|------|------|--------|
| position.local.x | number | meters | 로컬 X 좌표 | 0.0 |
| position.local.y | number | meters | 로컬 Y 좌표 | 0.0 |
| position.local.z | number | meters | 로컬 Z 좌표 | 0.0 |
| position.global.latitude | number | degrees | GPS 위도 | 37.5665 |
| position.global.longitude | number | degrees | GPS 경도 | 126.9780 |
| position.global.altitude_msl | number | meters | 해수면 기준 고도 | 50.0 |
| velocity.x | number | m/s | X축 속도 | 0.0 |
| velocity.y | number | m/s | Y축 속도 | 0.0 |
| velocity.z | number | m/s | Z축 속도 | 0.0 |

### 2.2 자세 정보
| 필드명 | 타입 | 단위 | 설명 | 예시값 |
|--------|------|------|------|--------|
| attitude.pitch_rad | number | radians | 피치 각도 | -0.00299 |
| attitude.roll_rad | number | radians | 롤 각도 | -0.00134 |
| attitude.yaw_rad | number | radians | 요 각도 | -0.14631 |
| attitude.pitch_deg | number | degrees | 피치 각도 | -0.171 |
| attitude.roll_deg | number | degrees | 롤 각도 | -0.077 |
| attitude.yaw_deg | number | degrees | 요 각도 | -8.381 |

### 2.3 제어 출력
| 필드명 | 타입 | 단위 | 설명 | 예시값 |
|--------|------|------|------|--------|
| control_output.motor1 | number | μs | 모터 1 PWM | 1100 |
| control_output.motor2 | number | μs | 모터 2 PWM | 1100 |
| control_output.motor3 | number | μs | 모터 3 PWM | 1100 |
| control_output.motor4 | number | μs | 모터 4 PWM | 1100 |
| control_output.pid_roll | number | - | 롤 축 PID 출력 | 0.0 |
| control_output.pid_pitch | number | - | 피치 축 PID 출력 | 0.0 |
| control_output.pid_yaw | number | - | 요 축 PID 출력 | 0.0 |

## 3. 2차 가공 정보 (Secondary Processed Data)

### 3.1 비행 상태
| 필드명 | 타입 | 값 | 설명 | 예시값 |
|--------|------|----|------|--------|
| flight_status.phase | string | IDLE/TAKEOFF/HOVER/FLYING/LANDING/EMERGENCY | 비행 단계 | "IDLE" |
| flight_status.mode | string | MANUAL/STABILIZE/ALTITUDE_HOLD/POSITION_HOLD/AUTO/RTL/LAND | 비행 모드 | "MANUAL" |
| flight_status.armed | boolean | true/false | 모터 활성화 상태 | false |
| flight_status.emergency_stop | boolean | true/false | 비상 정지 상태 | false |

### 3.2 내비게이션
| 필드명 | 타입 | 단위 | 설명 | 예시값 |
|--------|------|------|------|--------|
| navigation.target_lat | number | degrees | 목표 위도 | 37.5665 |
| navigation.target_lon | number | degrees | 목표 경도 | 126.9780 |
| navigation.target_alt | number | meters | 목표 고도 | 50.0 |
| navigation.distance_to_target | number | meters | 목표까지 거리 | 0.0 |
| navigation.bearing_to_target | number | degrees | 목표 방향 | 0.0 |

### 3.3 시스템 상태
| 필드명 | 타입 | 단위 | 설명 | 예시값 |
|--------|------|------|------|--------|
| system_status.battery_remaining | number | % | 배터리 잔량 | 85 |
| system_status.battery_voltage | number | V | 배터리 전압 | 12.6 |
| system_status.cpu_load | number | % | CPU 사용률 | 15.5 |
| system_status.ram_usage | number | % | 메모리 사용량 | 45.2 |
| system_status.disk_usage | number | % | 디스크 사용량 | 30.1 |

## 4. 데이터 처리 파이프라인

| 단계 | 담당 모듈 | 주요 기술 | 출력 예시 |
|------|-----------|-----------|-----------|
| **1. 센서 레이어** | 드라이버 | ADC, SPI, I2C | Raw 센서 값 |
| **2. 센서 보정** | 칼리브레이션 | 오프셋, 스케일 팩터 | 보정된 센서 값 |
| **3. 센서 융합** | EKF, 칼만 필터 | 다중 센서 데이터 융합 | 추정된 상태 벡터 |
| **4. 제어 알고리즘** | PID, LQR, MPC | 제어 이론 | 모터 제어 신호 |
| **5. 애플리케이션** | 비행 컨트롤러 | 비즈니스 로직 | 비행 명령 |
