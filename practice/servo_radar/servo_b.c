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

	int t = 0;
	while(1)
	{
		fputs("select c, r, l, q : ", stdout);
		scanf("%c", &str);
		getchar();
		if(str=='c'){
			softPwmWrite(SERVO, 15);	// 0 degree
			fputs("\ncenter\n", stdout);
		}
		else if(str=='l'){
			softPwmWrite(SERVO, 24);	// 90 degree
			fputs("\nright\n", stdout);
		}
		else if(str=='r'){
			softPwmWrite(SERVO, 5);		// -90 degree
			fputs("\nleft\n", stdout);
		}
		else if(str=='q'){
			softPwmWrite(SERVO, 0);
			fputs("\nquit\n", stdout);
			return 0;
		}
	}

	return 0;
}
