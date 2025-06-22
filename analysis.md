# 드론 센싱 및 데이터 처리 계층 분석

## 1. 물리적 디바이스에서 직접 센싱한 정보 (Raw Sensor Data)

### 1.1 IMU (Inertial Measurement Unit)

#### 주요 제품

- **InvenSense MPU-6050**: 6축(3축 자이로스코프 + 3축 가속도계) 센서, I2C 통신, 저전력
- **STMicroelectronics LSM6DS3**: 6축 IMU, 디지털 출력, 임베디드 FIFO, 저전력
- **Bosch BMI160**: 6축 IMU, 16비트 해상도, SPI/I2C 인터페이스
- **TDK InvenSense ICM-20948**: 9축(자이로 + 가속도계 + 자력계) 센서, DMP 내장
- **TDK InvenSense ICM-42688-P**: 6축 IMU, 고정밀, 저전력, 스마트폰/드론용

| 필드명                      | 타입   | 단위  | 설명       | 예시값    |
| --------------------------- | ------ | ----- | ---------- | --------- |
| sensors.imu.accelerometer.x | number | m/s²  | X축 가속도 | 0.002649  |
| sensors.imu.accelerometer.y | number | m/s²  | Y축 가속도 | -0.008638 |
| sensors.imu.accelerometer.z | number | m/s²  | Z축 가속도 | 9.7995    |
| sensors.imu.gyroscope.x     | number | rad/s | X축 각속도 | -0.002    |
| sensors.imu.gyroscope.y     | number | rad/s | Y축 각속도 | -0.002    |
| sensors.imu.gyroscope.z     | number | rad/s | Z축 각속도 | -0.006212 |
| sensors.imu.temperature     | number | °C    | 센서 온도  | 25.0      |

### 1.2 GPS (Global Positioning System)

#### 주요 제품

- **U-blox NEO-M8N**: 동시 3개 GNSS(미국 GPS, 러시아 GLONASS, 중국 BDS) 지원, 고감도
- **Quectel L80-R**: 72채널 GPS 수신기, -165dBm 고감도, 초저전력
- **GTop MG-800**: 10Hz 업데이트 속도, RTK 호환, 고정밀 포지셔닝
- **Holybro M8N GPS**: Pixhawk 호환, 나침반 내장, LED 상태 표시
- **Here+ RTK GPS**: 실시간 운동학(RTK) 지원, 센티미터급 정확도

| 필드명                 | 타입   | 단위    | 설명        | 예시값   |
| ---------------------- | ------ | ------- | ----------- | -------- |
| sensors.gps.latitude   | number | degrees | 위도        | 37.5665  |
| sensors.gps.longitude  | number | degrees | 경도        | 126.9780 |
| sensors.gps.altitude   | number | meters  | 고도        | 50.0     |
| sensors.gps.speed      | number | m/s     | 속도        | 0.0      |
| sensors.gps.course     | number | degrees | 방향        | 0.0      |
| sensors.gps.satellites | number | count   | 위성 수     | 12       |
| sensors.gps.hdop       | number | -       | 수평 정밀도 | 1.2      |
| sensors.gps.vdop       | number | -       | 수직 정밀도 | 1.8      |

### 1.3 기압계 (Barometer)

#### 주요 제품

- **Bosch BMP280**: 디지털 기압 센서, ±1hPa 절대 정확도, I2C/SPI 인터페이스
- **MS5611-01BA03**: 고정밀 기압 센서, 10cm 고도 해상도, I2C/SPI 인터페이스
- **TE Connectivity MS5607**: 24비트 ADC, 전력 소비 1μA(대기 모드), -40~85°C 작동
- **Infineon DPS310**: 소형 패키지, 저전력, 고정밀 디지털 기압 센서
- **Garmin LIDAR-Lite v3**: 광학 거리 센서, 40m 측정 거리, I2C/PWM 출력

| 필드명                        | 타입   | 단위   | 설명      | 예시값  |
| ----------------------------- | ------ | ------ | --------- | ------- |
| sensors.barometer.pressure    | number | hPa    | 대기압    | 1013.25 |
| sensors.barometer.temperature | number | °C     | 온도      | 25.0    |
| sensors.barometer.altitude    | number | meters | 기압 고도 | 50.0    |

### 1.4 자력계 (Magnetometer)

#### 주요 제품

- **Honeywell HMC5883L**: 3축 디지털 나침반, 1-2° 정확도, I2C 인터페이스
- **STMicroelectronics LIS3MDL**: 3축 자력계, 4가지 측정 범위(±4~±16 가우스)
- **Bosch BMM150**: 디지털 지자기 센서, 저전력, I2C/SPI 인터페이스
- **Pixart HMC5983**: 3축 디지털 나침반, 12비트 ADC, I2C 호환
- **TDK AK8963**: 3축 전자 나침반, 16비트 ADC, I2C 버스

| 필드명                           | 타입   | 단위    | 설명       | 예시값 |
| -------------------------------- | ------ | ------- | ---------- | ------ |
| sensors.magnetometer.x           | number | gauss   | X축 자기장 | 0.1234 |
| sensors.magnetometer.y           | number | gauss   | Y축 자기장 | 0.2345 |
| sensors.magnetometer.z           | number | gauss   | Z축 자기장 | 0.3456 |
| sensors.magnetometer.declination | number | degrees | 자기 편각  | 7.5    |

### 1.5 거리 센서 (Rangefinder)

#### 주요 제품

- **TeraRanger One**: 광학 TOF(Time-of-Flight) 센서, 0.1-14m, 100Hz
- **Lightware SF11/C**: 초경량 레이저 거리계, 50m, 100Hz, I2C/UART
- **MaxBotix MB1242**: 초음파 거리 센서, 20-765cm, I2C/UART/아날로그 출력
- **Benewake TFmini Plus**: TOF 레이저 거리계, 0.1-12m, 1000Hz, UART/I2C

| 필드명                           | 타입   | 단위   | 설명           | 예시값 |
| -------------------------------- | ------ | ------ | -------------- | ------ |
| sensors.rangefinder.distance     | number | meters | 측정 거리      | 0.0    |
| sensors.rangefinder.max_distance | number | meters | 최대 측정 거리 | 40.0   |
| sensors.rangefinder.min_distance | number | meters | 최소 측정 거리 | 0.2    |

### 1.6 옵티컬 플로우 (Optical Flow)

#### 주요 제품

- **PX4Flow**: 광학 흐름 카메라, 초당 250개 프레임, 초음파 거리계 통합
- **Holybro FLOW v2**: 광학 흐름 센서, 752x480 해상도, 400Hz 업데이트 속도
- **Tindie PMW3901**: 광학 흐름 센서, 120fps, I2C/SPI 인터페이스
- **Intel RealSense T265**: 내부 추적 카메라, 6DoF 추적, 200Hz

#### 실제 드론 센서 장치

- **DJI Inspire 2**: 광학 흐름 센서, 내부 추적 카메라
- **PX4 autopilot**: 광학 흐름 센서, 내부 추적 카메라

| 필드명                               | 타입   | 단위   | 설명        | 예시값 |
| ------------------------------------ | ------ | ------ | ----------- | ------ |
| sensors.optical_flow.flow_x          | number | rad/s  | X축 플로우  | 0.0    |
| sensors.optical_flow.flow_y          | number | rad/s  | Y축 플로우  | 0.0    |
| sensors.optical_flow.quality         | number | 0-255  | 플로우 품질 | 0      |
| sensors.optical_flow.ground_distance | number | meters | 지면 거리   | 0.0    |

### 1.7 ESC (Electronic Speed Controller)

##### 주요 제품

- **BLHeli_32**: 32비트 ESC, DSHOT 지원, 최대 48kHz PWM
- **T-Motor FLAME**: 4-in-1 ESC, 최대 60A 연속 전류
- **Holybro BLHeli32 50A**: 50A 정격, 3-6S 배터리 지원
- **Racerstar BLHeli_S**: 35A, DSHOT600 지원

| 필드명          | 타입   | 단위 | 설명           | 예시값 |
| --------------- | ------ | ---- | -------------- | ------ |
| esc.temperature | number | °C   | ESC 온도       | 45.0   |
| esc.current     | number | A    | 소비 전류      | 12.5   |
| esc.voltage     | number | V    | 입력 전압      | 16.8   |
| esc.rpm         | number | RPM  | 모터 회전 속도 | 12000  |

### 1.8 서보 모터 (Servo Motor)

##### 주요 제품

- **KST DS215MG**: 디지털 서보, 6.0V/12.0kgf·cm
- **MKS HV9767**: 초고토크 서보, 8.4V/40kgf·cm
- **TowerPro MG996R**: 표준 서보, 4.8V/13kgf·cm
- **Blue Bird BMS-2114DMH**: 초고속 디지털 서보

| 필드명              | 타입   | 단위 | 설명                   | 예시값 |
| ------------------- | ------ | ---- | ---------------------- | ------ |
| servo[1-8].position | number | μs   | 서보 위치 (500-2500μs) | 1500   |
| servo[1-8].speed    | number | %    | 서보 속도 (0-100%)     | 50     |
| servo[1-8].load     | number | %    | 서보 부하 (0-100%)     | 25     |

## 2. 1차 가공 정보 (Primary Processed Data)

1차 가공 정보는 원시 센서 데이터를 기반으로 계산되거나 변환된 정보들로, 비행 제어에 직접적으로 사용되는 값들입니다.

### 2.1 위치 정보

**생성 방법**:

- **로컬 좌표계(X,Y,Z)**: IMU의 가속도계 데이터를 이중 적분하여 계산되며, 드론의 초기 위치를 원점(0,0,0)으로 하는 상대적 위치를 나타냅니다. 드리프트 오차를 보정하기 위해 주기적으로 GPS나 광학 흐름 센서 데이터로 보정됩니다.
- **글로벌 좌표계(위도,경도,고도)**: GPS 센서에서 수신한 위성 신호를 기반으로 계산되며, WGS84 좌표계를 사용합니다. 고도는 기압계 데이터를 함께 활용하여 더 정확한 값을 계산합니다.
- **속도 벡터(X,Y,Z)**: IMU의 가속도계 데이터를 적분하거나, GPS의 도플러 효과를 이용한 속도 정보를 사용합니다. 저고도에서는 광학 흐름 센서의 속도 정보와 융합됩니다.

| 필드명                       | 타입   | 단위    | 설명             | 예시값   |
| ---------------------------- | ------ | ------- | ---------------- | -------- |
| position.local.x             | number | meters  | 로컬 X 좌표      | 0.0      |
| position.local.y             | number | meters  | 로컬 Y 좌표      | 0.0      |
| position.local.z             | number | meters  | 로컬 Z 좌표      | 0.0      |
| position.global.latitude     | number | degrees | GPS 위도         | 37.5665  |
| position.global.longitude    | number | degrees | GPS 경도         | 126.9780 |
| position.global.altitude_msl | number | meters  | 해수면 기준 고도 | 50.0     |
| velocity.x                   | number | m/s     | X축 속도         | 0.0      |
| velocity.y                   | number | m/s     | Y축 속도         | 0.0      |
| velocity.z                   | number | m/s     | Z축 속도         | 0.0      |

### 2.2 자세 정보

**개요**:

- **피치(Pitch)**: 기체의 앞뒤 기울기. 앞으로 기울이면 양의 각도, 뒤로 기울이면 음의 각도입니다. 비행기의 상하 움직임을 제어합니다.
- **롤(Roll)**: 기체의 좌우 기울기. 오른쪽으로 기울이면 양의 각도, 왼쪽으로 기울이면 음의 각도입니다. 비행기의 좌우 회전을 제어합니다.
- **요(Yaw)**: 기체의 좌우 방향. 오른쪽으로 회전하면 양의 각도, 왼쪽으로 회전하면 음의 각도입니다. 비행기의 진행 방향을 제어합니다.

**생성 방법**:

- **자이로스코프 적분**: IMU의 자이로스코프 데이터를 적분하여 각속도로부터 각도를 계산합니다. 그러나 시간이 지남에 따라 오차가 누적되는 문제가 있습니다.
- **상보 필터(Complementary Filter)**: 자이로스코프의 단기 정확도와 가속도계/자력계의 장기 안정성을 결합한 필터링 기법을 사용합니다.
- **칼만 필터**: 다중 센서(자이로, 가속도계, 자력계)의 데이터를 융합하여 더 정확한 자세 각을 추정합니다. 쿼터니언(Quaternion) 형식으로 변환되어 짐벌 록(Gimbal Lock) 문제를 방지합니다.
- **DMP(Digital Motion Processor)**: 일부 IMU 칩(예: MPU-6050)에 내장된 전용 프로세서가 센서 융합을 수행하여 마이크로컨트롤러의 부하를 줄입니다.

| 필드명             | 타입   | 단위    | 설명      | 예시값   |
| ------------------ | ------ | ------- | --------- | -------- |
| attitude.pitch_rad | number | radians | 피치 각도 | -0.00299 |
| attitude.roll_rad  | number | radians | 롤 각도   | -0.00134 |
| attitude.yaw_rad   | number | radians | 요 각도   | -0.14631 |
| attitude.pitch_deg | number | degrees | 피치 각도 | -0.171   |
| attitude.roll_deg  | number | degrees | 롤 각도   | -0.077   |
| attitude.yaw_deg   | number | degrees | 요 각도   | -8.381   |

### 2.3 제어 출력

**생성 방법**:

- **PID 제어기**: 목표값과 실제값의 오차를 기반으로 Proportional(비례), Integral(적분), Derivative(미분) 항을 계산하여 제어 신호를 생성합니다.
  - **P(비례)**: 현재 오차에 비례하는 제어값으로, 오차가 클수록 강한 제어를 가합니다.
  - **I(적분)**: 누적된 오차를 보정하여 정상 상태 오차를 줄입니다.
  - **D(미분)**: 오차의 변화율을 감지하여 오버슈트를 방지하고 시스템의 안정성을 높입니다.
- **모터 믹싱**: 롤, 피치, 요, 스로틀 입력을 각 모터의 회전 속도로 변환합니다. 쿼드콥터의 경우 X자형 또는 +자형 배치에 따라 다른 믹싱 매트릭스가 사용됩니다.
- **ESC 신호 변환**: 계산된 모터 속도 값을 PWM(Pulse Width Modulation) 신호로 변환하여 전자속도제어기(ESC)에 전달합니다. 일반적으로 1000-2000μs의 펄스 폭을 가집니다.

| 필드명                   | 타입   | 단위 | 설명             | 예시값 |
| ------------------------ | ------ | ---- | ---------------- | ------ |
| control_output.motor1    | number | μs   | 모터 1 PWM       | 1100   |
| control_output.motor2    | number | μs   | 모터 2 PWM       | 1100   |
| control_output.motor3    | number | μs   | 모터 3 PWM       | 1100   |
| control_output.motor4    | number | μs   | 모터 4 PWM       | 1100   |
| control_output.pid_roll  | number | -    | 롤 축 PID 출력   | 0.0    |
| control_output.pid_pitch | number | -    | 피치 축 PID 출력 | 0.0    |
| control_output.pid_yaw   | number | -    | 요 축 PID 출력   | 0.0    |

## 3. 2차 가공 정보 (Secondary Processed Data)

### 3.1 비행 상태

| 필드명                       | 타입    | 값                                                         | 설명             | 예시값   |
| ---------------------------- | ------- | ---------------------------------------------------------- | ---------------- | -------- |
| flight_status.phase          | string  | IDLE/TAKEOFF/HOVER/FLYING/LANDING/EMERGENCY                | 비행 단계        | "IDLE"   |
| flight_status.mode           | string  | MANUAL/STABILIZE/ALTITUDE_HOLD/POSITION_HOLD/AUTO/RTL/LAND | 비행 모드        | "MANUAL" |
| flight_status.armed          | boolean | true/false                                                 | 모터 활성화 상태 | false    |
| flight_status.emergency_stop | boolean | true/false                                                 | 비상 정지 상태   | false    |

### 3.2 내비게이션

| 필드명                        | 타입   | 단위    | 설명          | 예시값   |
| ----------------------------- | ------ | ------- | ------------- | -------- |
| navigation.target_lat         | number | degrees | 목표 위도     | 37.5665  |
| navigation.target_lon         | number | degrees | 목표 경도     | 126.9780 |
| navigation.target_alt         | number | meters  | 목표 고도     | 50.0     |
| navigation.distance_to_target | number | meters  | 목표까지 거리 | 0.0      |
| navigation.bearing_to_target  | number | degrees | 목표 방향     | 0.0      |

### 3.3 시스템 상태

| 필드명                          | 타입   | 단위 | 설명          | 예시값 |
| ------------------------------- | ------ | ---- | ------------- | ------ |
| system_status.battery_remaining | number | %    | 배터리 잔량   | 85     |
| system_status.battery_voltage   | number | V    | 배터리 전압   | 12.6   |
| system_status.cpu_load          | number | %    | CPU 사용률    | 15.5   |
| system_status.ram_usage         | number | %    | 메모리 사용량 | 45.2   |
| system_status.disk_usage        | number | %    | 디스크 사용량 | 30.1   |

## 4. 데이터 처리 파이프라인

| 단계                 | 담당 모듈      | 주요 기술             | 출력 예시        |
| -------------------- | -------------- | --------------------- | ---------------- |
| **1. 센서 레이어**   | 드라이버       | ADC, SPI, I2C         | Raw 센서 값      |
| **2. 센서 보정**     | 칼리브레이션   | 오프셋, 스케일 팩터   | 보정된 센서 값   |
| **3. 센서 융합**     | EKF, 칼만 필터 | 다중 센서 데이터 융합 | 추정된 상태 벡터 |
| **4. 제어 알고리즘** | PID, LQR, MPC  | 제어 이론             | 모터 제어 신호   |
| **5. 애플리케이션**  | 비행 컨트롤러  | 비즈니스 로직         | 비행 명령        |
