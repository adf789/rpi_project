#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <math.h>
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define SERVO 1
#define TRIGPIN 5
#define ECHOPIN 4
#define PI 3.1415926534897

using namespace cv;

float detectObj(bool*);
void pwmInit();
double getRadian(int num);
void servoControl(int);


float t = 0;

int main(){
	char wndName[] = "Radar Demo";
	const int KEYDELAY = 1;
	int lineType = LINE_AA;
	int curAngle = 180, width = 1000, height = 700, rotSpeed = 9, lineSize = 12;
	int x1 = -width/2, x2 = width*3/2, y1 = -height/2, y2 = height*3/2;
	
	bool reverse = true, detected;
	RNG rng(0xFFFFFFFF);

	Mat image = Mat::zeros(height, width, CV_8UC3);
	Mat image2 = Mat::zeros(height, width, CV_8UC3);

	float distances[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	int angles[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};


	// pwm initialize
	pwmInit();

	while(1){
		// circle
		Point center;
		center.x = 500;
		center.y = 350;
		// repaint
		image = Mat::zeros(height, width, CV_8UC3);
		image2 = Mat::zeros(height, width, CV_8UC3);
		
		circle(image, center, 300, Scalar(125, 125, 125), 2, lineType, 0); 

		// ellipse
		ellipse(image, center, Size(270, 270), 0.0, 180.0, 360.0, Scalar(255, 0, 0), 2, LINE_AA);

		// line
		line(image, Point(230, 350), Point(770, 350), Scalar(255, 0, 0), 2, lineType);
		
		// set status
		for(int j = lineSize - 1; j > 0; j-=2){
			if((j - 2) < 0) break;
			distances[j] = distances[j - 2];
			angles[j] = angles[j - 2];

			if((j - 3) < 0) break;
			distances[j - 1] = distances[j - 3];
			angles[j - 1] = angles[j - 3];
		}
		// check object
		float dis = detectObj(&detected);
		angles[0] = curAngle;
		
		if(!reverse){
			angles[1] = curAngle + rotSpeed / 2;
		}else{
			angles[1] = curAngle - rotSpeed / 2;
		}
		
		distances[0] = dis;
		distances[1] = dis;

		// draw 'lineSize' of detect line
		for(int j = 0; j < lineSize; j++){
			if(angles[j] == -1 || distances[j] == -1) break;
			int alpha = j * 20;
			// red line (basic)
			line(image, center, Point((500 + 270*cos(getRadian(angles[j]))), (350 - 270*sin(getRadian(angles[j])))), Scalar(0, 0, (255 - alpha)), 5, lineType);
		
			// green line (detected)
			line(image, center, Point((500 + (int)(distances[j]*cos(getRadian(angles[j])))), (350 - (int)(distances[j]*sin(getRadian(angles[j]))))), Scalar(0, (255 - alpha), 0), 5, lineType);
			
		}

		// control servo motor
		servoControl(curAngle);

		// angle variation
		// echo line
		if(!reverse){
			curAngle -= rotSpeed;
		}else{
			curAngle += rotSpeed;
		}
		if(curAngle > 171){
			curAngle = 171;
			reverse = false;
		}else if(curAngle < 0){
			curAngle = 0;
			reverse = true;
		}
		

		imshow(wndName, image);
		waitKey(KEYDELAY);

	}
	return 0;
}

void pwmInit(){
	wiringPiSetup();

	pinMode(TRIGPIN, OUTPUT);
	pinMode(ECHOPIN, INPUT);
	pinMode(SERVO, OUTPUT);

	softPwmCreate(SERVO, 0, 200);
}

float detectObj(bool* detect){
	digitalWrite(TRIGPIN, LOW);
	delay(2);
	digitalWrite(TRIGPIN, HIGH);
	delay(1);
	digitalWrite(TRIGPIN, LOW);

	while(digitalRead(ECHOPIN) == LOW);

	long startTime = micros();
	while(digitalRead(ECHOPIN) == HIGH);
	long travelTime = micros() - startTime;

	int distance = travelTime / 58;

	// limit 100cm
	if(distance > 100){
		*detect = false;
		return 270;
	}

	if(distance >= 100) distance = 100; 
	//printf("Distance : %dcm\n", distance);


	*detect = true;

	return ((distance * 270)/100);
}

double getRadian(int num){
	return num * (PI / 180);
}

void servoControl(int angle){
	if(t == ((angle * 19) / 171) + 5) return;

	t = ((angle * 19) / 171) + 5;
	softPwmWrite(SERVO, (int)t);

	delay(30);
}
