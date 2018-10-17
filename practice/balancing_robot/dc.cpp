#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>

#define ENA 30
#define IN1 21
#define IN2 22
#define IN3 23
#define IN4 24
#define ENB 25



void selectMotor(char, char);
void initMotor();

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

int main(){
	if(wiringPiSetup()==-1)
		return 1;

	pwmInit();

	while(1)
	{
		int speed = 0;
		char ch, status;
		printf("\nselect channel (1, 2) : ");
		scanf(" %c", &ch);

		// after use scanf, flush buffer
		printf("\nselect motor status (s (stop), f (forward), b (backward)) : ");
		scanf(" %c", &status);

		if(status != 'f' && status != 'b' && status != 's') break;

		printf("\n select motor speed (0 - 200) : ");
		scanf(" %d", &speed);

		if(speed < 0) speed = 0;
		if(speed > 200) speed = 200;
		softPwmWrite(ENA, speed);
		softPwmWrite(ENB, speed);

		initMotor();	
		selectMotor(ch, status);

		delay(1000);


	}

	initMotor();

	return 0;
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

void initMotor(){
	digitalWrite(IN1, LOW);
	digitalWrite(IN2, LOW);
	digitalWrite(IN3, LOW);
	digitalWrite(IN4, LOW);
}
