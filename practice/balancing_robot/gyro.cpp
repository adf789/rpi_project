#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <math.h>

#define I2C_ADDR (0x68)
#define PWR_MGMT_1 (0x6B)

int fd;
int acclX, acclY, acclZ;
int gyroX, gyroY, gyroZ;
double acclX_scaled, acclY_scaled, acclZ_scaled;
double gyroX_scaled, gyroY_scaled, gyroZ_scaled;

int read_word_2c(int addr){
	int high = wiringPiI2CReadReg8(fd, addr);
	int low = wiringPiI2CReadReg8(fd, addr+1);

	int var = (high << 8) + low;

	if(var >= 0x8000)
		var = -(65536 - var);

	return var;
}

int main(){
	fd = wiringPiI2CSetup(I2C_ADDR);
	if(fd == -1){
		printf("Not found I2C device\n");
		return -1;
	}

	// disable sleep mode
	wiringPiI2CWriteReg16(fd, PWR_MGMT_1, 0);

	printf("set 0x68 = %X\n", wiringPiI2CReadReg8(fd, 0x68));

	while(1){
		// Mesure angluar velocity.
		gyroX = read_word_2c(0x43);
		gyroY = read_word_2c(0x45);
		gyroZ = read_word_2c(0x47);

		gyroX_scaled = gyroX / 131.0;
		gyroY_scaled = gyroY / 131.0;
		gyroZ_scaled = gyroZ / 131.0;


		// Mesure acceleration.
		/*acclX = read_word_2c(0x3b);
		acclY = read_word_2c(0x3d);
		acclZ = read_word_2c(0x3f);

		const float scale = 16384.0 / 9.807;

		acclX_scaled = acclX / scale;
		acclY_scaled = acclY / scale;
		acclZ_scaled = acclZ / scale;*/		

		printf("-------------------------------------------------------\n");
		printf("gyroX : %.2f, gyroY : %.2f, gyroZ : %.2f\n", gyroX_scaled, gyroY_scaled, gyroZ_scaled);
		printf("-------------------------------------------------------\n");

		delay(500);
	}

	return 0;
}

