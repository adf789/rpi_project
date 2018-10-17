#include <stdio.h>
#include <wiringPi.h>

#define TRIGPIN 5
#define ECHOPIN 4

int main(void){
	int distance = 0;

	wiringPiSetup();

	pinMode(TRIGPIN, OUTPUT);
	pinMode(ECHOPIN, INPUT);

	while(1){
		digitalWrite(TRIGPIN, LOW);
		delay(100);
		digitalWrite(TRIGPIN, HIGH);
		delay(10);
		digitalWrite(TRIGPIN, LOW);

		while(digitalRead(ECHOPIN) == LOW);

		long startTime = micros();
		while(digitalRead(ECHOPIN) == HIGH);
		long travelTime = micros() - startTime;

		int distance = travelTime / 58;

		printf("Distance : %dcm\n", distance);
		delay(200);
	}
}
