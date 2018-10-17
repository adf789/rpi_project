#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>

#define ENA 29
#define IN1 21
#define IN2 22
#define IN3 23
#define IN4 24
#define ENB 25

void pwmInit(){
	pinMode(ENA, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
	pinMode(ENB, OUTPUT);

	digitalWrite(ENA, HIGH);
	digitalWrite(ENB, HIGH);
}

int main(){
	if(wiringPiSetup()==-1)
		return 1;

	printf("start!!\n");
	while(1)
	{
		// #1
		digitalWrite(IN1, HIGH);
		digitalWrite(IN2, LOW);
		digitalWrite(IN3, HIGH);
		digitalWrite(IN4, LOW);
		delay(10);
		printf("#1\n");

		// #2
		digitalWrite(IN1, LOW);
		digitalWrite(IN2, HIGH);
		digitalWrite(IN3, HIGH);
		digitalWrite(IN4, LOW);
		delay(10);
		printf("#2\n");

		// #3
		digitalWrite(IN1, LOW);
		digitalWrite(IN2, HIGH);
		digitalWrite(IN3, LOW);
		digitalWrite(IN4, HIGH);
		delay(10);
		printf("#3\n");

		// #4
		digitalWrite(IN1, HIGH);
		digitalWrite(IN2, LOW);
		digitalWrite(IN3, LOW);
		digitalWrite(IN4, HIGH);
		delay(10);
		printf("#4\n");
		
	}

	return 0;
}
