# 드론 제어용 데이터 구조 정리표

드론 제어를 위한 완전한 데이터 구조를 정의했습니다. 15개 모든 항목을 빠짐없이 포함한 완전한 JSON 데이터 구조를 생성했습니다.

## 15개 주요 카테고리:

1. **시스템 식별 및 시간 정보** - 드론 ID, 타임스탬프
2. **비행 상태 관리** - 비행 단계, 모드, 안전 상태
3. **위치 정보** - 로컬/글로벌/홈 포지션
4. **속도 정보** - 3축 속도, 지상/대기 속도
5. **자세 정보** - pitch/roll/yaw (라디안/도)
6. **각속도 정보** - 3축 각속도
7. **센서 데이터** - IMU, GPS, 기압계, 자력계, 거리센서, 옵티컬플로우
8. **전력 관리** - 메인/백업 배터리, 전력 소비량
9. **모터 제어** - 4개 모터 개별 상태 및 설정
10. **제어 시스템** - 설정값, PID 제어 출력
11. **미션 관리** - 웨이포인트 기반 자율비행
12. **통신 상태** - RC, 텔레메트리, WiFi, 블루투스
13. **시스템 건강성** - 상태 체크, 진동, 온도, 리소스 사용량
14. **설정 및 구성** - 기체 타입, 제한값, 지오펜스, 안전 설정
15. **로그 관리** - 로깅 설정 및 상태

## 고급 기능:

- **페이로드 관리** - 카메라, 짐벌, 센서, 배송 시스템
- **날씨 정보** - 바람, 강수, 시정, 대기 조건
- **내비게이션** - EKF, 나침반, GPS 융합
- **유지보수** - 비행시간, 점검 항목, 정비 일정

**약 300개 이상의 필드**를 포함하며, 상용 드론 시스템에서 요구되는 모든 데이터를 망라합니다. 실제 드론 제어 소프트웨어 개발 시 이 구조를 기반으로 필요한 부분만 선택적으로 구현할 수 있습니다. 이 구조는 상업용 드론 플랫폼에서 사용되는 수준의 완전한 데이터 모델로, 모니터링부터 고급 자율비행까지 모든 제어 시나리오를 지원할 수 있습니다.

## 1. 시스템 식별 및 시간 정보

| 필드명         | 타입   | 단위         | 설명                     | 예시값                     |
| -------------- | ------ | ------------ | ------------------------ | -------------------------- |
| drone_id       | string | -            | 드론 고유 식별자         | "DRONE_001"                |
| timestamp      | string | ISO 8601     | 드론 시스템 시간         | "2025-06-22T21:37:07.244Z" |
| recv_time      | string | ISO 8601     | 데이터 수신 시간         | "2025-06-22T21:37:07.250Z" |
| system_time_ms | number | milliseconds | 시스템 부팅 후 경과 시간 | 1719088627244              |

## 2. 비행 상태 관리

| 필드명                           | 타입    | 값                                                         | 설명                 | 예시값   |
| -------------------------------- | ------- | ---------------------------------------------------------- | -------------------- | -------- |
| flight_status.phase              | string  | IDLE/TAKEOFF/HOVER/FLYING/LANDING/EMERGENCY                | 현재 비행 단계       | "IDLE"   |
| flight_status.mode               | string  | MANUAL/STABILIZE/ALTITUDE_HOLD/POSITION_HOLD/AUTO/RTL/LAND | 비행 모드            | "MANUAL" |
| flight_status.armed              | boolean | true/false                                                 | 모터 활성화 상태     | false    |
| flight_status.can_arm            | boolean | true/false                                                 | 무장 가능 여부       | true     |
| flight_status.emergency_stop     | boolean | true/false                                                 | 비상 정지 상태       | false    |
| flight_status.failsafe_triggered | boolean | true/false                                                 | 페일세이프 작동 여부 | false    |
| flight_status.home_set           | boolean | true/false                                                 | 홈 포지션 설정 여부  | true     |

## 3. 위치 정보

### 3.1 로컬 위치

| 필드명           | 타입   | 단위   | 설명               | 예시값 |
| ---------------- | ------ | ------ | ------------------ | ------ |
| position.local.x | number | meters | 로컬 X 좌표        | 0.0    |
| position.local.y | number | meters | 로컬 Y 좌표        | 0.0    |
| position.local.z | number | meters | 로컬 Z 좌표 (고도) | 0.0    |

### 3.2 글로벌 위치

| 필드명                       | 타입   | 단위    | 설명             | 예시값   |
| ---------------------------- | ------ | ------- | ---------------- | -------- |
| position.global.latitude     | number | degrees | GPS 위도         | 37.5665  |
| position.global.longitude    | number | degrees | GPS 경도         | 126.9780 |
| position.global.altitude_msl | number | meters  | 해수면 기준 고도 | 50.0     |
| position.global.altitude_rel | number | meters  | 상대 고도        | 0.0      |

### 3.3 홈 포지션

| 필드명                  | 타입    | 단위    | 설명         | 예시값   |
| ----------------------- | ------- | ------- | ------------ | -------- |
| position.home.latitude  | number  | degrees | 홈 위도      | 37.5665  |
| position.home.longitude | number  | degrees | 홈 경도      | 126.9780 |
| position.home.altitude  | number  | meters  | 홈 고도      | 50.0     |
| position.home.set       | boolean | -       | 홈 설정 여부 | true     |

## 4. 속도 정보

| 필드명                | 타입   | 단위 | 설명      | 예시값 |
| --------------------- | ------ | ---- | --------- | ------ |
| velocity.x            | number | m/s  | X축 속도  | 0.0    |
| velocity.y            | number | m/s  | Y축 속도  | 0.0    |
| velocity.z            | number | m/s  | Z축 속도  | 0.0    |
| velocity.ground_speed | number | m/s  | 지상 속도 | 0.0    |
| velocity.air_speed    | number | m/s  | 대기 속도 | 0.0    |

## 5. 자세 정보

| 필드명             | 타입   | 단위    | 설명               | 예시값                 |
| ------------------ | ------ | ------- | ------------------ | ---------------------- |
| attitude.pitch_rad | number | radians | 피치 각도 (라디안) | -0.002991304775874326  |
| attitude.roll_rad  | number | radians | 롤 각도 (라디안)   | -0.0013466579489843841 |
| attitude.yaw_rad   | number | radians | 요 각도 (라디안)   | -0.14631682824333206   |
| attitude.pitch_deg | number | degrees | 피치 각도 (도)     | -0.171                 |
| attitude.roll_deg  | number | degrees | 롤 각도 (도)       | -0.077                 |
| attitude.yaw_deg   | number | degrees | 요 각도 (도)       | -8.381                 |

## 6. 각속도 정보

| 필드명                      | 타입   | 단위  | 설명        | 예시값    |
| --------------------------- | ------ | ----- | ----------- | --------- |
| angular_velocity.pitch_rate | number | rad/s | 피치 각속도 | -0.002    |
| angular_velocity.roll_rate  | number | rad/s | 롤 각속도   | -0.002    |
| angular_velocity.yaw_rate   | number | rad/s | 요 각속도   | -0.006212 |

## 7. 센서 데이터

### 7.1 IMU - 가속도계

| 필드명                                | 타입   | 단위    | 설명       | 예시값    |
| ------------------------------------- | ------ | ------- | ---------- | --------- |
| sensors.imu.accelerometer.x           | number | m/s²    | X축 가속도 | 0.002649  |
| sensors.imu.accelerometer.y           | number | m/s²    | Y축 가속도 | -0.008638 |
| sensors.imu.accelerometer.z           | number | m/s²    | Z축 가속도 | 9.7995    |
| sensors.imu.accelerometer.temperature | number | celsius | 센서 온도  | 25.0      |
| sensors.imu.accelerometer.status      | string | -       | 센서 상태  | "OK"      |

### 7.2 IMU - 자이로스코프

| 필드명                            | 타입   | 단위    | 설명       | 예시값    |
| --------------------------------- | ------ | ------- | ---------- | --------- |
| sensors.imu.gyroscope.x           | number | rad/s   | X축 각속도 | -0.002    |
| sensors.imu.gyroscope.y           | number | rad/s   | Y축 각속도 | -0.002    |
| sensors.imu.gyroscope.z           | number | rad/s   | Z축 각속도 | -0.006212 |
| sensors.imu.gyroscope.temperature | number | celsius | 센서 온도  | 25.0      |
| sensors.imu.gyroscope.status      | string | -       | 센서 상태  | "OK"      |

### 7.3 자력계

| 필드명                           | 타입   | 단위    | 설명       | 예시값 |
| -------------------------------- | ------ | ------- | ---------- | ------ |
| sensors.magnetometer.x           | number | gauss   | X축 자기장 | 0.1234 |
| sensors.magnetometer.y           | number | gauss   | Y축 자기장 | 0.2345 |
| sensors.magnetometer.z           | number | gauss   | Z축 자기장 | 0.3456 |
| sensors.magnetometer.declination | number | degrees | 자기 편각  | 7.5    |
| sensors.magnetometer.status      | string | -       | 센서 상태  | "OK"   |

### 7.4 기압계

| 필드명                        | 타입   | 단위    | 설명      | 예시값  |
| ----------------------------- | ------ | ------- | --------- | ------- |
| sensors.barometer.pressure    | number | hPa     | 대기압    | 1013.25 |
| sensors.barometer.temperature | number | celsius | 온도      | 25.0    |
| sensors.barometer.altitude    | number | meters  | 기압 고도 | 50.0    |
| sensors.barometer.status      | string | -       | 센서 상태 | "OK"    |

### 7.5 GPS

| 필드명                 | 타입   | 단위    | 설명                | 예시값   |
| ---------------------- | ------ | ------- | ------------------- | -------- |
| sensors.gps.fix_type   | number | -       | GPS 고정 타입 (0-3) | 3        |
| sensors.gps.satellites | number | count   | 위성 개수           | 12       |
| sensors.gps.hdop       | number | -       | 수평 정밀도         | 1.2      |
| sensors.gps.vdop       | number | -       | 수직 정밀도         | 1.8      |
| sensors.gps.latitude   | number | degrees | 위도                | 37.5665  |
| sensors.gps.longitude  | number | degrees | 경도                | 126.9780 |
| sensors.gps.altitude   | number | meters  | GPS 고도            | 50.0     |
| sensors.gps.speed      | number | m/s     | GPS 속도            | 0.0      |
| sensors.gps.course     | number | degrees | 진행 방향           | 0.0      |
| sensors.gps.status     | string | -       | GPS 상태            | "OK"     |

### 7.6 거리 센서

| 필드명                           | 타입   | 단위   | 설명           | 예시값 |
| -------------------------------- | ------ | ------ | -------------- | ------ |
| sensors.rangefinder.distance     | number | meters | 측정 거리      | 0.0    |
| sensors.rangefinder.max_distance | number | meters | 최대 측정 거리 | 40.0   |
| sensors.rangefinder.min_distance | number | meters | 최소 측정 거리 | 0.2    |
| sensors.rangefinder.status       | string | -      | 센서 상태      | "OK"   |

### 7.7 옵티컬 플로우

| 필드명                               | 타입   | 단위   | 설명          | 예시값     |
| ------------------------------------ | ------ | ------ | ------------- | ---------- |
| sensors.optical_flow.flow_x          | number | rad/s  | X축 플로우    | 0.0        |
| sensors.optical_flow.flow_y          | number | rad/s  | Y축 플로우    | 0.0        |
| sensors.optical_flow.quality         | number | 0-255  | 플로우 품질   | 0          |
| sensors.optical_flow.ground_distance | number | meters | 지면까지 거리 | 0.0        |
| sensors.optical_flow.status          | string | -      | 센서 상태     | "DISABLED" |

## 8. 전력 관리

### 8.1 메인 배터리

| 필드명                         | 타입   | 단위    | 설명        | 예시값 |
| ------------------------------ | ------ | ------- | ----------- | ------ |
| power.battery_main.voltage     | number | volts   | 배터리 전압 | 12.6   |
| power.battery_main.current     | number | amperes | 전류        | 2.5    |
| power.battery_main.remaining   | number | percent | 잔량        | 85     |
| power.battery_main.capacity    | number | mAh     | 용량        | 5000   |
| power.battery_main.cells       | number | count   | 셀 개수     | 3      |
| power.battery_main.temperature | number | celsius | 배터리 온도 | 25.0   |
| power.battery_main.status      | string | -       | 배터리 상태 | "OK"   |

### 8.2 백업 배터리

| 필드명                         | 타입   | 단위    | 설명             | 예시값 |
| ------------------------------ | ------ | ------- | ---------------- | ------ |
| power.battery_backup.voltage   | number | volts   | 백업 배터리 전압 | 5.0    |
| power.battery_backup.remaining | number | percent | 잔량             | 90     |
| power.battery_backup.status    | string | -       | 상태             | "OK"   |

### 8.3 전력 소비

| 필드명                                    | 타입   | 단위  | 설명                  | 예시값 |
| ----------------------------------------- | ------ | ----- | --------------------- | ------ |
| power.power_consumption.total             | number | watts | 총 소비 전력          | 31.5   |
| power.power_consumption.motors            | number | watts | 모터 소비 전력        | 25.0   |
| power.power_consumption.flight_controller | number | watts | 비행 제어기 소비 전력 | 2.0    |
| power.power_consumption.sensors           | number | watts | 센서 소비 전력        | 1.5    |
| power.power_consumption.communication     | number | watts | 통신 소비 전력        | 3.0    |

## 9. 모터 제어

### 9.1 개별 모터 (M1-M4)

| 필드명                    | 타입   | 단위         | 설명      | 예시값 |
| ------------------------- | ------ | ------------ | --------- | ------ |
| motors.m[1-4].pwm         | number | microseconds | PWM 신호  | 1000   |
| motors.m[1-4].rpm         | number | rpm          | 회전 속도 | 0      |
| motors.m[1-4].current     | number | amperes      | 모터 전류 | 0.5    |
| motors.m[1-4].temperature | number | celsius      | 모터 온도 | 25.0   |
| motors.m[1-4].status      | string | -            | 모터 상태 | "OK"   |

### 9.2 모터 설정

| 필드명                          | 타입   | 단위         | 설명            | 예시값 |
| ------------------------------- | ------ | ------------ | --------------- | ------ |
| motors.configuration.min_pwm    | number | microseconds | 최소 PWM        | 1000   |
| motors.configuration.max_pwm    | number | microseconds | 최대 PWM        | 2000   |
| motors.configuration.idle_pwm   | number | microseconds | 유휴 PWM        | 1100   |
| motors.configuration.spin_armed | number | microseconds | 무장시 최소 PWM | 1050   |

## 10. 제어 시스템

### 10.1 설정값 (Setpoints)

| 필드명                           | 타입   | 단위    | 설명        | 예시값 |
| -------------------------------- | ------ | ------- | ----------- | ------ |
| control.setpoints.position.x     | number | meters  | 목표 X 위치 | 0.0    |
| control.setpoints.position.y     | number | meters  | 목표 Y 위치 | 0.0    |
| control.setpoints.position.z     | number | meters  | 목표 Z 위치 | 0.0    |
| control.setpoints.velocity.x     | number | m/s     | 목표 X 속도 | 0.0    |
| control.setpoints.velocity.y     | number | m/s     | 목표 Y 속도 | 0.0    |
| control.setpoints.velocity.z     | number | m/s     | 목표 Z 속도 | 0.0    |
| control.setpoints.attitude.pitch | number | radians | 목표 피치   | 0.0    |
| control.setpoints.attitude.roll  | number | radians | 목표 롤     | 0.0    |
| control.setpoints.attitude.yaw   | number | radians | 목표 요     | 0.0    |
| control.setpoints.throttle       | number | 0-1     | 스로틀      | 0.0    |

### 10.2 PID 제어 출력 - 위치

| 필드명                               | 타입   | 설명         | 예시값 |
| ------------------------------------ | ------ | ------------ | ------ |
| control.pid_output.position.x.p      | number | P 제어값     | 0.0    |
| control.pid_output.position.x.i      | number | I 제어값     | 0.0    |
| control.pid_output.position.x.d      | number | D 제어값     | 0.0    |
| control.pid_output.position.x.output | number | 총 출력값    | 0.0    |
| control.pid_output.position.y.\*     | number | Y축 PID 값들 | 0.0    |
| control.pid_output.position.z.\*     | number | Z축 PID 값들 | 0.0    |

### 10.3 PID 제어 출력 - 자세

| 필드명                               | 타입   | 설명          | 예시값 |
| ------------------------------------ | ------ | ------------- | ------ |
| control.pid_output.attitude.pitch.\* | number | 피치 PID 값들 | 0.0    |
| control.pid_output.attitude.roll.\*  | number | 롤 PID 값들   | 0.0    |
| control.pid_output.attitude.yaw.\*   | number | 요 PID 값들   | 0.0    |

### 10.4 PID 제어 출력 - 각속도

| 필드명                           | 타입   | 설명            | 예시값 |
| -------------------------------- | ------ | --------------- | ------ |
| control.pid_output.rate.pitch.\* | number | 피치 각속도 PID | 0.0    |
| control.pid_output.rate.roll.\*  | number | 롤 각속도 PID   | 0.0    |
| control.pid_output.rate.yaw.\*   | number | 요 각속도 PID   | 0.0    |

## 11. 미션 관리

| 필드명                   | 타입    | 설명              | 예시값 |
| ------------------------ | ------- | ----------------- | ------ |
| mission.active           | boolean | 미션 활성화 여부  | false  |
| mission.current_waypoint | number  | 현재 웨이포인트   | 0      |
| mission.total_waypoints  | number  | 총 웨이포인트 수  | 0      |
| mission.waypoints        | array   | 웨이포인트 목록   | []     |
| mission.mission_type     | string  | 미션 타입         | "NONE" |
| mission.auto_continue    | boolean | 자동 계속 여부    | false  |
| mission.rtl_altitude     | number  | RTL 고도 (meters) | 20.0   |

## 12. 통신 상태

### 12.1 RC 채널

| 필드명                            | 타입   | 단위         | 설명       | 예시값 |
| --------------------------------- | ------ | ------------ | ---------- | ------ |
| communication.rc_channels.ch[1-8] | number | microseconds | RC 채널 값 | 1500   |

### 12.2 RC 상태

| 필드명                                 | 타입    | 단위    | 설명            | 예시값 |
| -------------------------------------- | ------- | ------- | --------------- | ------ |
| communication.rc_status.connected      | boolean | -       | RC 연결 상태    | true   |
| communication.rc_status.rssi           | number  | dBm     | 신호 강도       | -45    |
| communication.rc_status.signal_quality | number  | percent | 신호 품질       | 100    |
| communication.rc_status.failsafe       | boolean | -       | 페일세이프 상태 | false  |

### 12.3 텔레메트리

| 필드명                            | 타입    | 단위    | 설명            | 예시값 |
| --------------------------------- | ------- | ------- | --------------- | ------ |
| communication.telemetry.connected | boolean | -       | 텔레메트리 연결 | true   |
| communication.telemetry.rssi      | number  | dBm     | 신호 강도       | -50    |
| communication.telemetry.noise     | number  | dBm     | 노이즈 레벨     | -90    |
| communication.telemetry.tx_buffer | number  | percent | 송신 버퍼       | 0      |
| communication.telemetry.rx_errors | number  | count   | 수신 오류       | 0      |
| communication.telemetry.tx_rate   | number  | Hz      | 송신 속도       | 100    |
| communication.telemetry.rx_rate   | number  | Hz      | 수신 속도       | 100    |

### 12.4 WiFi

| 필드명                             | 타입    | 단위 | 설명           | 예시값          |
| ---------------------------------- | ------- | ---- | -------------- | --------------- |
| communication.wifi.connected       | boolean | -    | WiFi 연결 상태 | true            |
| communication.wifi.ssid            | string  | -    | 연결된 SSID    | "DRONE_WIFI"    |
| communication.wifi.signal_strength | number  | dBm  | 신호 강도      | -40             |
| communication.wifi.ip_address      | string  | -    | IP 주소        | "192.168.1.100" |

## 13. 시스템 건강성

### 13.1 전체 상태

| 필드명                | 타입   | 설명             | 예시값 |
| --------------------- | ------ | ---------------- | ------ |
| health.overall_status | string | 전체 시스템 상태 | "OK"   |
| health.warnings       | array  | 경고 목록        | []     |
| health.errors         | array  | 오류 목록        | []     |

### 13.2 시스템 체크

| 필드명                             | 타입   | 설명            | 예시값 |
| ---------------------------------- | ------ | --------------- | ------ |
| health.system_checks.sensors       | string | 센서 상태       | "OK"   |
| health.system_checks.actuators     | string | 액추에이터 상태 | "OK"   |
| health.system_checks.power         | string | 전원 상태       | "OK"   |
| health.system_checks.communication | string | 통신 상태       | "OK"   |
| health.system_checks.navigation    | string | 내비게이션 상태 | "OK"   |

### 13.3 진동

| 필드명             | 타입   | 단위 | 설명     | 예시값 |
| ------------------ | ------ | ---- | -------- | ------ |
| health.vibration.x | number | m/s² | X축 진동 | 0.1    |
| health.vibration.y | number | m/s² | Y축 진동 | 0.1    |
| health.vibration.z | number | m/s² | Z축 진동 | 0.15   |

### 13.4 시스템 리소스

| 필드명               | 타입   | 단위    | 설명            | 예시값 |
| -------------------- | ------ | ------- | --------------- | ------ |
| health.cpu_usage     | number | percent | CPU 사용률      | 25.0   |
| health.memory_usage  | number | percent | 메모리 사용률   | 45.0   |
| health.storage_usage | number | percent | 저장공간 사용률 | 60.0   |

### 13.5 온도

| 필드명                         | 타입   | 단위    | 설명      | 예시값 |
| ------------------------------ | ------ | ------- | --------- | ------ |
| health.temperature.cpu         | number | celsius | CPU 온도  | 45.0   |
| health.temperature.imu         | number | celsius | IMU 온도  | 25.0   |
| health.temperature.environment | number | celsius | 환경 온도 | 20.0   |

## 14. 설정 및 구성

### 14.1 기본 설정

| 필드명                         | 타입   | 설명                  | 예시값                       |
| ------------------------------ | ------ | --------------------- | ---------------------------- |
| configuration.frame_type       | string | 기체 타입             | "QUAD_X"                     |
| configuration.firmware_version | string | 펌웨어 버전           | "1.14.0"                     |
| configuration.hardware_version | string | 하드웨어 버전         | "2.1"                        |
| configuration.flight_modes     | array  | 사용 가능한 비행 모드 | ["MANUAL", "STABILIZE", ...] |
| configuration.current_mode     | string | 현재 비행 모드        | "MANUAL"                     |

### 14.2 지오펜스

| 필드명                              | 타입    | 단위   | 설명            | 예시값 |
| ----------------------------------- | ------- | ------ | --------------- | ------ |
| configuration.geofence.enabled      | boolean | -      | 지오펜스 활성화 | true   |
| configuration.geofence.max_altitude | number  | meters | 최대 고도       | 120.0  |
| configuration.geofence.max_distance | number  | meters | 최대 거리       | 500.0  |
| configuration.geofence.action       | string  | -      | 위반시 행동     | "RTL"  |

### 14.3 제한값

| 필드명                                    | 타입   | 단위    | 설명             | 예시값 |
| ----------------------------------------- | ------ | ------- | ---------------- | ------ |
| configuration.limits.max_velocity         | number | m/s     | 최대 속도        | 15.0   |
| configuration.limits.max_acceleration     | number | m/s²    | 최대 가속도      | 5.0    |
| configuration.limits.max_angular_velocity | number | rad/s   | 최대 각속도      | 3.14   |
| configuration.limits.max_tilt_angle       | number | radians | 최대 기울기 각도 | 0.785  |

## 15. 로그 관리

| 필드명                | 타입    | 단위    | 설명          | 예시값 |
| --------------------- | ------- | ------- | ------------- | ------ |
| log.logging_enabled   | boolean | -       | 로깅 활성화   | true   |
| log.log_level         | string  | -       | 로그 레벨     | "INFO" |
| log.log_rate          | number  | Hz      | 로깅 주기     | 100    |
| log.storage_remaining | number  | percent | 저장공간 잔량 | 75.0   |

---

**총 필드 수: 약 200개**  
**주요 카테고리: 15개**  
**데이터 타입: number, string, boolean, array**

```json
{
  "drone_id": "DRONE_001",
  "timestamp": "2025-06-22T21:37:07.244Z",
  "recv_time": "2025-06-22T21:37:07.250Z",
  "system_time_ms": 1719088627244,

  "flight_status": {
    "phase": "IDLE",
    "mode": "MANUAL",
    "armed": false,
    "can_arm": true,
    "emergency_stop": false,
    "failsafe_triggered": false,
    "home_set": true
  },

  "position": {
    "local": {
      "x": 0.0,
      "y": 0.0,
      "z": 0.0
    },
    "global": {
      "latitude": 37.5665,
      "longitude": 126.978,
      "altitude_msl": 50.0,
      "altitude_rel": 0.0
    },
    "home": {
      "latitude": 37.5665,
      "longitude": 126.978,
      "altitude": 50.0,
      "set": true
    }
  },

  "velocity": {
    "x": 0.0,
    "y": 0.0,
    "z": 0.0,
    "ground_speed": 0.0,
    "air_speed": 0.0
  },

  "attitude": {
    "pitch_rad": -0.002991304775874326,
    "roll_rad": -0.0013466579489843841,
    "yaw_rad": -0.14631682824333206,
    "pitch_deg": -0.171,
    "roll_deg": -0.077,
    "yaw_deg": -8.381
  },

  "angular_velocity": {
    "pitch_rate": -0.002,
    "roll_rate": -0.002,
    "yaw_rate": -0.006212
  },

  "sensors": {
    "imu": {
      "accelerometer": {
        "x": 0.002649,
        "y": -0.008638,
        "z": 9.7995,
        "temperature": 25.0,
        "status": "OK"
      },
      "gyroscope": {
        "x": -0.002,
        "y": -0.002,
        "z": -0.006212,
        "temperature": 25.0,
        "status": "OK"
      }
    },
    "magnetometer": {
      "x": 0.1234,
      "y": 0.2345,
      "z": 0.3456,
      "declination": 7.5,
      "status": "OK"
    },
    "barometer": {
      "pressure": 1013.25,
      "temperature": 25.0,
      "altitude": 50.0,
      "status": "OK"
    },
    "gps": {
      "fix_type": 3,
      "satellites": 12,
      "hdop": 1.2,
      "vdop": 1.8,
      "latitude": 37.5665,
      "longitude": 126.978,
      "altitude": 50.0,
      "speed": 0.0,
      "course": 0.0,
      "status": "OK"
    },
    "rangefinder": {
      "distance": 0.0,
      "max_distance": 40.0,
      "min_distance": 0.2,
      "status": "OK"
    },
    "optical_flow": {
      "flow_x": 0.0,
      "flow_y": 0.0,
      "quality": 0,
      "ground_distance": 0.0,
      "status": "DISABLED"
    }
  },

  "power": {
    "battery_main": {
      "voltage": 12.6,
      "current": 2.5,
      "remaining": 85,
      "capacity": 5000,
      "cells": 3,
      "temperature": 25.0,
      "status": "OK"
    },
    "battery_backup": {
      "voltage": 5.0,
      "remaining": 90,
      "status": "OK"
    },
    "power_consumption": {
      "total": 31.5,
      "motors": 25.0,
      "flight_controller": 2.0,
      "sensors": 1.5,
      "communication": 3.0
    }
  },

  "motors": {
    "m1": {
      "pwm": 1000,
      "rpm": 0,
      "current": 0.5,
      "temperature": 25.0,
      "status": "OK"
    },
    "m2": {
      "pwm": 1000,
      "rpm": 0,
      "current": 0.5,
      "temperature": 25.0,
      "status": "OK"
    },
    "m3": {
      "pwm": 1000,
      "rpm": 0,
      "current": 0.5,
      "temperature": 25.0,
      "status": "OK"
    },
    "m4": {
      "pwm": 1000,
      "rpm": 0,
      "current": 0.5,
      "temperature": 25.0,
      "status": "OK"
    },
    "configuration": {
      "min_pwm": 1000,
      "max_pwm": 2000,
      "idle_pwm": 1100,
      "spin_armed": 1050
    }
  },

  "control": {
    "setpoints": {
      "position": {
        "x": 0.0,
        "y": 0.0,
        "z": 0.0
      },
      "velocity": {
        "x": 0.0,
        "y": 0.0,
        "z": 0.0
      },
      "attitude": {
        "pitch": 0.0,
        "roll": 0.0,
        "yaw": 0.0
      },
      "throttle": 0.0
    },
    "pid_output": {
      "position": {
        "x": {
          "p": 0.0,
          "i": 0.0,
          "d": 0.0,
          "output": 0.0
        },
        "y": {
          "p": 0.0,
          "i": 0.0,
          "d": 0.0,
          "output": 0.0
        },
        "z": {
          "p": 0.0,
          "i": 0.0,
          "d": 0.0,
          "output": 0.0
        }
      },
      "attitude": {
        "pitch": {
          "p": 0.0,
          "i": 0.0,
          "d": 0.0,
          "output": 0.0
        },
        "roll": {
          "p": 0.0,
          "i": 0.0,
          "d": 0.0,
          "output": 0.0
        },
        "yaw": {
          "p": 0.0,
          "i": 0.0,
          "d": 0.0,
          "output": 0.0
        }
      },
      "rate": {
        "pitch": {
          "p": 0.0,
          "i": 0.0,
          "d": 0.0,
          "output": 0.0
        },
        "roll": {
          "p": 0.0,
          "i": 0.0,
          "d": 0.0,
          "output": 0.0
        },
        "yaw": {
          "p": 0.0,
          "i": 0.0,
          "d": 0.0,
          "output": 0.0
        }
      }
    }
  },

  "mission": {
    "active": false,
    "current_waypoint": 0,
    "total_waypoints": 0,
    "waypoints": [
      {
        "seq": 0,
        "lat": 37.5665,
        "lon": 126.978,
        "alt": 20.0,
        "command": "WAYPOINT",
        "param1": 0.0,
        "param2": 0.0,
        "param3": 0.0,
        "param4": 0.0,
        "autocontinue": true
      }
    ],
    "mission_type": "NONE",
    "auto_continue": false,
    "rtl_altitude": 20.0,
    "land_mode": "PRECISION"
  },

  "communication": {
    "rc_channels": {
      "ch1": 1500,
      "ch2": 1500,
      "ch3": 1000,
      "ch4": 1500,
      "ch5": 1000,
      "ch6": 1000,
      "ch7": 1000,
      "ch8": 1000,
      "ch9": 1000,
      "ch10": 1000,
      "ch11": 1000,
      "ch12": 1000,
      "ch13": 1000,
      "ch14": 1000,
      "ch15": 1000,
      "ch16": 1000
    },
    "rc_status": {
      "connected": true,
      "rssi": -45,
      "signal_quality": 100,
      "failsafe": false,
      "rx_loss_count": 0,
      "frame_drops": 0
    },
    "telemetry": {
      "connected": true,
      "rssi": -50,
      "noise": -90,
      "tx_buffer": 0,
      "rx_errors": 0,
      "tx_rate": 100,
      "rx_rate": 100,
      "packet_loss": 0,
      "link_quality": 100
    },
    "wifi": {
      "connected": true,
      "ssid": "DRONE_WIFI",
      "signal_strength": -40,
      "ip_address": "192.168.1.100",
      "mac_address": "AA:BB:CC:DD:EE:FF",
      "channel": 6,
      "frequency": 2437
    },
    "bluetooth": {
      "connected": false,
      "paired_devices": [],
      "discoverable": false
    }
  },

  "health": {
    "overall_status": "OK",
    "warnings": [],
    "errors": [],
    "system_checks": {
      "sensors": "OK",
      "actuators": "OK",
      "power": "OK",
      "communication": "OK",
      "navigation": "OK",
      "payload": "OK",
      "weather": "OK"
    },
    "vibration": {
      "x": 0.1,
      "y": 0.1,
      "z": 0.15,
      "total": 0.2,
      "threshold": 0.5
    },
    "cpu_usage": 25.0,
    "memory_usage": 45.0,
    "storage_usage": 60.0,
    "network_usage": 15.0,
    "temperature": {
      "cpu": 45.0,
      "imu": 25.0,
      "environment": 20.0,
      "motors": 28.0,
      "battery": 25.0,
      "electronics": 30.0
    },
    "uptime": 3600,
    "boot_time": "2025-06-22T20:37:07.244Z",
    "last_heartbeat": "2025-06-22T21:37:07.244Z"
  },

  "configuration": {
    "frame_type": "QUAD_X",
    "firmware_version": "1.14.0",
    "hardware_version": "2.1",
    "serial_number": "DRN001234567890",
    "manufacturer": "DroneFactory",
    "model": "DF-X4-Pro",
    "flight_modes": [
      "MANUAL",
      "STABILIZE",
      "ALTITUDE_HOLD",
      "POSITION_HOLD",
      "AUTO",
      "RTL",
      "LAND",
      "GUIDED",
      "CIRCLE",
      "BRAKE"
    ],
    "current_mode": "MANUAL",
    "available_modes": [
      "MANUAL",
      "STABILIZE",
      "ALTITUDE_HOLD",
      "POSITION_HOLD"
    ],
    "geofence": {
      "enabled": true,
      "max_altitude": 120.0,
      "max_distance": 500.0,
      "min_altitude": -10.0,
      "action": "RTL",
      "breach_action": "LAND",
      "warning_distance": 450.0
    },
    "limits": {
      "max_velocity": 15.0,
      "max_acceleration": 5.0,
      "max_angular_velocity": 3.14,
      "max_tilt_angle": 0.785,
      "max_climb_rate": 5.0,
      "max_descent_rate": 3.0,
      "max_yaw_rate": 1.57
    },
    "flight_parameters": {
      "takeoff_altitude": 2.5,
      "landing_speed": 0.5,
      "hover_throttle": 0.5,
      "cruise_speed": 5.0,
      "loiter_radius": 10.0
    },
    "safety": {
      "low_battery_action": "RTL",
      "low_battery_threshold": 20.0,
      "critical_battery_threshold": 10.0,
      "gps_loss_action": "LAND",
      "rc_loss_action": "RTL",
      "datalink_loss_action": "RTL",
      "emergency_disarm": false
    }
  },

  "log": {
    "logging_enabled": true,
    "log_level": "INFO",
    "log_rate": 100,
    "storage_remaining": 75.0,
    "current_log_file": "LOG_001.bin",
    "log_file_size": 1024000,
    "max_log_files": 10,
    "auto_delete_old_logs": true,
    "log_on_arm": true,
    "log_disarm_delay": 5.0,
    "logged_messages": [
      "ATTITUDE",
      "POSITION",
      "VELOCITY",
      "IMU",
      "GPS",
      "BATTERY",
      "MOTORS",
      "RC",
      "SYSTEM"
    ]
  },

  "payload": {
    "camera": {
      "available": true,
      "active": false,
      "recording": false,
      "resolution": "1920x1080",
      "fps": 30,
      "storage_remaining": 85.0,
      "sd_card_present": true,
      "gimbal": {
        "pitch": 0.0,
        "roll": 0.0,
        "yaw": 0.0,
        "mode": "FOLLOW"
      }
    },
    "sensors": {
      "lidar": {
        "available": false,
        "active": false,
        "range": 0.0,
        "status": "DISABLED"
      },
      "thermal": {
        "available": false,
        "active": false,
        "temperature": 0.0,
        "status": "DISABLED"
      }
    },
    "delivery": {
      "available": false,
      "payload_attached": false,
      "max_payload_weight": 2.0,
      "current_payload_weight": 0.0,
      "release_mechanism": "SERVO"
    }
  },

  "weather": {
    "wind": {
      "speed": 2.5,
      "direction": 180.0,
      "gusts": 3.0
    },
    "precipitation": {
      "detected": false,
      "intensity": 0.0,
      "type": "NONE"
    },
    "visibility": {
      "distance": 10000.0,
      "conditions": "CLEAR"
    },
    "atmospheric": {
      "pressure": 1013.25,
      "humidity": 65.0,
      "temperature": 20.0,
      "density_altitude": 50.0
    }
  },

  "navigation": {
    "ekf": {
      "healthy": true,
      "position_variance": 0.1,
      "velocity_variance": 0.05,
      "attitude_variance": 0.02,
      "terrain_estimate": 50.0
    },
    "compass": {
      "healthy": true,
      "declination": 7.5,
      "deviation": 0.5,
      "heading": 351.619
    },
    "gps_fusion": {
      "primary_gps": 0,
      "gps_blend_ratio": 1.0,
      "num_sats_blended": 12
    },
    "position_estimate": {
      "accuracy_horizontal": 1.2,
      "accuracy_vertical": 1.8,
      "confidence": 95.0
    }
  },

  "maintenance": {
    "flight_hours": 125.5,
    "flight_cycles": 450,
    "motor_hours": {
      "m1": 125.5,
      "m2": 125.3,
      "m3": 125.7,
      "m4": 125.4
    },
    "last_maintenance": "2025-06-01T10:00:00.000Z",
    "next_maintenance": "2025-07-01T10:00:00.000Z",
    "maintenance_items": [
      {
        "item": "PROPELLER_INSPECTION",
        "due_hours": 150.0,
        "due_cycles": 500,
        "status": "OK"
      },
      {
        "item": "MOTOR_INSPECTION",
        "due_hours": 200.0,
        "due_cycles": 750,
        "status": "OK"
      }
    ]
  }
}
```
