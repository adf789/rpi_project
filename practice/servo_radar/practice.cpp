#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>

using namespace cv;

int width = 1000;
int height = 500;

int main(){
	Mat image = Mat::zeros(height, width, CV_8UC3);
	Mat image2 = Mat::zeros(height, width, CV_8UC3);
	Mat resultImg;
	Point center(width/2, height/2);
	int lineType = LINE_AA;

	line(image, center, Point(width/2, 0), Scalar(255, 0, 0), 2, lineType);
	
	// rotate
	Mat rot = getRotationMatrix2D(center, 90, 1);
	warpAffine(image, image2, rot, image.size());
	
	// add
	resultImg = image + image2;

	imshow("test", resultImg);
	while(1){
		waitKey(100);
	}

	return 0;
}