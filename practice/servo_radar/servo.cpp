#include<stdio.h>
#include<wiringPi.h>
#include<softPwm.h>

#define SERVO 1

int main(){
	char str;

	if(wiringPiSetup()==-1)
		return 1;

	pinMode(SERVO, OUTPUT);
	softPwmCreate(SERVO, 0, 200);

	int t = 24;
	bool reverse = false, init = false;
	while(1)
	{
		softPwmWrite(SERVO, t);
		if(!init){
			delay(500);
			init = true;
		}
		if(!reverse){
			t--;
			if(t < 5){
				t = 6;
				reverse = true;
			}
		}
		else {
			t++;
			if(t > 24){
				t = 23;
				reverse = false;
			}
		}
		delay(100);
		
	}

	return 0;
}
