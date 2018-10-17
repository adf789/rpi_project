#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <softPwm.h>
#include <math.h>

// gyro sensor
#define I2C_ADDR (0x68)
#define PWR_MGMT_1 (0X6B)

// dc motor
#define ENA 30
#define IN1 21
#define IN2 22
#define IN3 23
#define IN4 24
#define ENB 25

int fd;

// motor
void selectMotor(char, char);
void startMotor(int, char);
void initMotor();
void pwmInit();

// gyro sensor
int read_word_2c(int);
int initSensor();
void detectVelocity(int*, int*, int*);

// combine motor and sensor
int controlSpeed(int);

int main(){
	if(wiringPiSetup()==-1)
		return 1;

	// initial pwm
	pwmInit();

	// initial motor
	initMotor();

	// initial gyro sensor
	if(initSensor() == -1){
		printf("Not found I2C device\n");
		return -1;
	}

	while(1)
	{
		int speed;
		int gyroX, gyroY, gyroZ;

		detectVelocity(&gyroX, &gyroY, &gyroZ);

		printf("-------------------------------------------------------\n");
		printf("gyroX : %d, gyroY : %d, gyroZ : %d\n", gyroX, gyroY, gyroZ);
		printf("-------------------------------------------------------\n");

		if(abs(gyroZ) > 100){
			break;
		}

		speed = controlSpeed(gyroY);

		if(speed > 0){
			startMotor(speed, 'f');
		}else if(speed < 0){
			startMotor(-speed, 'b');
		}else {
			startMotor(speed, 's');
		}

		delay(250);


	}

	initMotor();

	return 0;
}

void pwmInit(){
	pinMode(ENA, PWM_OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
	pinMode(ENB, PWM_OUTPUT);

	softPwmCreate(ENA, 0, 200);
	softPwmWrite(ENA, 0);
	softPwmCreate(ENB, 0, 200);
	softPwmWrite(ENB, 0);
}

void selectMotor(char ch, char status){
	if(ch == '1'){
		if(status == 'f'){		// FORWARD
			digitalWrite(IN1, HIGH);
			digitalWrite(IN2, LOW);		
		} else if(status == 'b'){	// BACKWARD
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, HIGH);
		} else if(status == 's'){	// STOP
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, LOW);
		} else{
			printf("wrong status!!\n");			
		}
	} else if(ch == '2'){
		if(status == 'f'){		// FORWARD
			digitalWrite(IN3, HIGH);
			digitalWrite(IN4, LOW);
		} else if(status == 'b'){	// BACKWARD
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, HIGH);
		} else if(status == 's'){	// STOP
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, LOW);
		} else{
			printf("wrong status!!\n");
		}
	} else{
		printf("wrong channel!!\n");
	}
}

void startMotor(int speed, char status){
	softPwmWrite(ENA, speed);
	softPwmWrite(ENB, speed);

	selectMotor('1', status);
	selectMotor('2', status);
}

void initMotor(){
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, LOW);
}

int read_word_2c(int addr){
	int high = wiringPiI2CReadReg8(fd, addr);
	int low = wiringPiI2CReadReg8(fd, addr+1);

	int var = (high << 8) + low;

	if(var >= 0x8000)
		var = -(65536 - var);

	return var;
}

int initSensor(){
	fd = wiringPiI2CSetup(I2C_ADDR);
	if(fd == -1) return -1;

	wiringPiI2CWriteReg16(fd, PWR_MGMT_1, 0);

	printf("set 0x68 = %X\n", wiringPiI2CReadReg8(fd, 0x68));

	return 1;
}

void detectVelocity(int* x, int* y, int* z){
	int gyroX = read_word_2c(0x43);
	int gyroY = read_word_2c(0x45);
	int gyroZ = read_word_2c(0x47);

	int gyroX_s = (gyroX / 131);
	int gyroY_s = (gyroY / 131);
	int gyroZ_s = (gyroZ / 131);

	*x = gyroX_s;
	*y = gyroY_s;
	*z = gyroZ_s;

	return;
}

int controlSpeed(int gyroY){
	int speed = 0, temp;

	temp = gyroY;
	if(temp > 100) temp = 100;
	else if(temp < -100) temp = -100;

	speed = temp * 2;


	return speed;
}
