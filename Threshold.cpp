
#include <stdio.h>      /* printf */
#include <math.h>       /* pow */
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;


int main()
{
	Mat img = imread("D:/su/document/1st semester/image processing/final assigment 2/111.jpg", CV_LOAD_IMAGE_COLOR); //open and read the image

	if (img.empty()) //if unsuccessful, exit the program
	{
		cout << "image cannot be loaded..!!" << endl;
		return -1;
	}

	Mat gray_img;
	Mat grad;
	cvtColor(img, gray_img, CV_BGR2GRAY);

	int histogram[256];
	// initialize all intensity values to 0
	for (int i = 0; i < 256; i++)
	{
		histogram[i] = 0;

	}

	// calculate the no of pixels for each intensity values
	for (int y = 0; y < gray_img.rows; y++)
	{
		for (int x = 0; x < gray_img.cols; x++)
		{
			histogram[(int)gray_img.at<uchar>(y, x)]++;

		}
	}


	// set threshold and maxvalue
	double thresh = 150;
	double maxvalue = 255;
	int error = 10;
	float sum1 = 0, sum2 = 0;
	float pa1 = 0, pa2 = 0;
	int a1, a2, average;
	while (error > 1)
	{
		for (int i = 0; i < thresh; i++)
		{
			sum1 = sum1 + histogram[i] * i;
			pa1 = pa1 + histogram[i];

		}

		for (int i = thresh; i < 256; i++)
		{

			sum2 = sum2 + histogram[i] * i;
			pa2 = pa2 + histogram[i];

		}

		a1 = sum1 / pa1;
		a2 = sum2 / pa2;
		average = a1*0.5 + a2*0.5;
		error = abs(thresh - average);
		thresh = average;
	}




	// binary threshold
	threshold(gray_img, grad, 200, maxvalue, THRESH_BINARY);

	//create windows
	namedWindow("original image", WINDOW_NORMAL);
	namedWindow("new image", CV_WINDOW_NORMAL);

	//show the image
	imshow("original image", gray_img);
	imshow("new image", grad);


	//imshow("histogram equalized", img_hist_equalized);

	//cout << "max value of bright" << bright << "bright";

	//cout << sizeimage;

	waitKey(0); //wait for key press

	destroyAllWindows(); //destroy all open windows

	return 0;
}


