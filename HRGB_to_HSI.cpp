
#include <stdio.h>      /* printf */
#include <math.h>       /* pow */
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;




void imhist(Mat image, int histogram_red[], int histogram_green[], int histogram_blue[])
{

	// initialize all intensity values to 0
	for (int i = 0; i < 256; i++)
	{
		histogram_red[i] = 0;
		histogram_green[i] = 0;
		histogram_blue[i] = 0;
	}

	// calculate the no of pixels for each intensity values
	for (int y = 0; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			Vec3b intensity = image.at<Vec3b>(Point(x, y));
			histogram_red[(int)intensity.val[0]]++;
			histogram_green[(int)intensity.val[1]]++;
			histogram_blue[(int)intensity.val[2]]++;

		}
	}

	//histogram[(int)image.at<uchar>(y, x)]++;


}


void histDisplay(int histogram[], const char* name)
{
	int hist[256];
	for (int i = 0; i < 256; i++)
	{
		hist[i] = histogram[i];
	}
	// draw the histograms
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / 256);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

	// find the maximum intensity element from histogram
	int max = hist[0];
	for (int i = 1; i < 256; i++){
		if (max < hist[i]){
			max = hist[i];
		}
	}

	// normalize the histogram between 0 and histImage.rows

	for (int i = 0; i < 256; i++){
		hist[i] = ((double)hist[i] / max)*histImage.rows;
	}


	// draw the intensity line for histogram
	for (int i = 0; i < 256; i++)
	{
		line(histImage, Point(bin_w*(i), hist_h),
			Point(bin_w*(i), hist_h - hist[i]),
			Scalar(0, 0, 0), 1, 8, 0);
	}

	// display histogram
	namedWindow(name, CV_WINDOW_AUTOSIZE);
	imshow(name, histImage);
}

// Calculate 
float power_function(float a, float lamda_correction)
{
	float b;
	//b = (256 / pow(255, lamda_correction)) * pow(a, lamda_correction);
	b = pow(a, lamda_correction);
	return b;
}

float choose_lamda_correction(Mat image, int histogram[], int size)
{
	float lamda_correction = 0;
	float sumR = 0;
	for (int i = 0; i < 256; i++)
	{
		sumR = sumR + (float)(i*histogram[i]) / size;
	}


	lamda_correction = log(0.5) / log(sumR / 256);

	return lamda_correction;
}

//int main(int argc, const char** argv)
int main()
{
	Mat img = imread("D:/Su/Document/1st semester/Image Processing/Final Assigment 1/picture4.png", CV_LOAD_IMAGE_COLOR); //open and read the image

	if (img.empty()) //if unsuccessful, exit the program
	{
		cout << "Image cannot be loaded..!!" << endl;
		return -1;
	}





	int sizeImage = img.rows*img.cols;
	int histogram_red[256], histogram_green[256], histogram_blue[256];
	imhist(img, histogram_red, histogram_green, histogram_blue);
	//histDisplay(histogram_red, "Red Histogram");
	//histDisplay(histogram_green, "Green Histogram");
	//histDisplay(histogram_blue, "Blue Histogram");

	float lamda_correction_r = choose_lamda_correction(img, histogram_red, sizeImage);
	float lamda_correction_g = choose_lamda_correction(img, histogram_green, sizeImage);
	float lamda_correction_b = choose_lamda_correction(img, histogram_blue, sizeImage);

	cout << lamda_correction_r << "xxxxxx\n";

	// B contain normalized value of pixels
	float B[256];
	for (int i = 0; i < 256; i++)
	{
		B[i] = (float)i / 255;
	}




	// calculate power function
	float A_r[256];
	float A_g[256];
	float A_b[256];
	for (int i = 0; i < 256; i++)
	{
		//if (B[i] <= 0.5)
		//{

		A_r[i] = power_function(B[i], lamda_correction_r);
		A_g[i] = power_function(B[i], lamda_correction_g);
		A_b[i] = power_function(B[i], lamda_correction_b);
		//A_r[i] = power_function(B[i], lamda_correction_r)*power_function(B[i], lamda_correction_r)*2;
		//A_g[i] = power_function(B[i], lamda_correction_g)*power_function(B[i], lamda_correction_g)*2;
		//A_b[i] = power_function(B[i], lamda_correction_b)*power_function(B[i], lamda_correction_b)*2;

		//}

		/*else
		{
		float xx = power_function(B[i], lamda_correction_r);
		A_r[i] = 1-pow(xx-1,2);
		float yy = power_function(B[i], lamda_correction_g);
		A_g[i] = 1-pow(yy-1,2);
		float zz = power_function(B[i], lamda_correction_b);
		A_b[i] = 1-pow(zz-1,2);
		}*/

	}



	for (int i = 0; i < 256; i++)
	{

		cout << A_r[i] << "\n";
	}



	int a, b, c;
	Mat new_image = img.clone();
	//Mat new_image;
	for (int y = 0; y < img.rows; y++)
	{
		for (int x = 0; x < img.cols; x++)
		{
			Vec3b intensity = img.at<Vec3b>(Point(x, y));
			//Vec3b new_intensity = new_image.at<Vec3b>(Point(x, y));
			//a = power_function((int)intensity.val[0]);
			//b = power_function((int)intensity.val[1]);
			//c = power_function((int)intensity.val[2]);
			////Vec3b new_intensity = new_image.at<Vec3b>(Point(x, y));
			//Vec3b new_intensity = new_image.at<Vec3b>(x, y);
			//new_intensity.val[0] = 0;
			//new_intensity.val[0] = saturate_cast<uchar>(A[intensity.val[0]]);
			//new_intensity.val[1] = 0;
			//new_intensity.val[1] = saturate_cast<uchar>(A[intensity.val[1]]);
			//new_intensity.val[2] = 0;
			//new_intensity.val[2] = saturate_cast<uchar>(A[intensity.val[2]]);

			//new_intensity.val[0] = (uchar)a;
			//new_intensity.val[1] = (uchar)b;
			//new_intensity.val[2] = (uchar)c;
			//

			//new_image.at<Vec3b>(Point(x, y))[0] = saturate_cast<uchar>(A[intensity.val[0]] * 255);
			//new_image.at<Vec3b>(Point(x, y))[1] = saturate_cast<uchar>(A[intensity.val[1]] * 255);
			//new_image.at<Vec3b>(Point(x, y))[2] = saturate_cast<uchar>(A[intensity.val[2]] * 255);

			new_image.at<Vec3b>(Point(x, y))[0] = saturate_cast<uchar>(A_r[intensity.val[0]] * 255);
			new_image.at<Vec3b>(Point(x, y))[1] = saturate_cast<uchar>(A_g[intensity.val[1]] * 255);
			new_image.at<Vec3b>(Point(x, y))[2] = saturate_cast<uchar>(A_b[intensity.val[2]] * 255);

		}
	}




	/*Vec3b intensity = img.at<Vec3b>(Point(0, 0));
	cout << (int)intensity.val[0] << "\n";

	int t = 100;
	Vec3b new_intensity = new_image.at<Vec3b>(Point(0, 0));
	cout << (int)new_intensity.val[0] << "\n";
	new_intensity.val[0] = (uchar)t;
	cout << (int)new_intensity.val[0] << "\n";*/



	int histogram_red_new[256], histogram_green_new[256], histogram_blue_new[256];
	imhist(new_image, histogram_red_new, histogram_green_new, histogram_blue_new);
	histDisplay(histogram_red_new, "Red New Histogram");
	histDisplay(histogram_green_new, "Green New Histogram");
	histDisplay(histogram_blue_new, "Blue New Histogram");



	//create windows
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("New image", CV_WINDOW_AUTOSIZE);

	//show the image
	imshow("Original Image", img);
	imshow("New image", new_image);


	//imshow("Histogram Equalized", img_hist_equalized);

	//cout << "max value of Bright" << Bright << "Bright";

	//cout << sizeImage;

	waitKey(0); //wait for key press

	destroyAllWindows(); //destroy all open windows

	return 0;
}