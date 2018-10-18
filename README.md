# rpi_project

SERVO-RADAR

![radar](https://user-images.githubusercontent.com/23645514/47135089-06057000-d2ea-11e8-81b7-8ce27ef3593c.jpg)

Raspberry Pi 3 - Servo Motor

            5V - VCC
            
           GND - GND
           
     GPIO 12번 - data
     
     
Raspberry Pi 3 - Echo Sensor

            5V - VCC
            
           GND - GND
           
     GPIO 18번 - Trig
     
     GPIO 16번 - Echo (3.3v 로 입력해야 함, 위 그림에서는 저항 1kΩ, 2kΩ 을 이용하여 3.3v 에 가깝게 만듬)
     
     
     
메인 프로그램

            radar.cpp
 
 
 
 
 
 
 
 
 
BALANCING_ROBOT

![balancing](https://user-images.githubusercontent.com/23645514/47135091-06057000-d2ea-11e8-83de-bee8aba274ea.jpg)

Raspberry Pi 3 - L298n (모터 드라이버)
           
           GND - GND
     GPIO 37번 - ENB
     GPIO 35번 - IN4
     GPIO 33번 - IN3
     GPIO 31번 - IN2
     GPIO 29번 - IN1
     GPIO 27번 - ENA
     
Raspberry Pi 3 - MPU-6050 (자이로, 가속도 센서)
            
            5V - VCC
           GND - GND
    GPIO 3번(SDA) - SDA
    GPIO 5번(SCL) - SCL
 
Battery - MPU-6050
※배터리의 전압은 모터의 전압과 동일하게 한다.
   
            VCC - +12V
            GND - GND
    
DC Motor - L298n
※각각 L298n의 MotorA, MotorB에 연결한다.

메인 프로그램

            main.cpp
