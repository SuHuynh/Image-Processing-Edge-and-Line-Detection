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
	cvtColor(img, gray_img, CV_BGR2GRAY);

	int sizeimage = img.rows*img.cols;
	
	int a, b, c;

	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	//mat new_image = img.clone();
	//mat new_image;
	//for (int y = 0; y < img.rows; y++)
	//{
	//	for (int x = 0; x < img.cols; x++)
	//	{
	//		vec3b intensity = img.at<vec3b>(point(x, y));
			
			//new_image.at<vec3b>(point(x, y))[0] = saturate_cast<uchar>(a_r[intensity.val[0]] * 255);
			//new_image.at<vec3b>(point(x, y))[1] = saturate_cast<uchar>(a_g[intensity.val[1]] * 255);
			//new_image.at<vec3b>(point(x, y))[2] = saturate_cast<uchar>(a_b[intensity.val[2]] * 255);




		//}
	//}
	/*
	for (int r = 0; r < gray_img.rows-2; r++)
	{
		for (int c = 0; c < gray_img.cols-2; c++)
		{
			int pixel = grayimage.at<uchar>(r, c);

			//sobel mask for x - direction:
			int gx = ((2 * grayimage.at<uchar>(i + 2, j + 1) + grayimage.at<uchar>(i + 2, j) + grayimage.at<uchar>(i + 2, j + 2)) - (2 * grayimage.at<uchar>(i, j + 1) + c(i, j) + grayimage.at<uchar>(i, j + 2)));
			//sobel mask for y - direction:
			int gy = ((2 * grayimage.at<uchar>(i + 1, j + 2) + grayimage.at<uchar>(i, j + 2) + grayimage.at<uchar>(i + 2, j + 2)) - (2 * grayimage.at<uchar>(i + 1, j) + c(i, j) + grayimage.at<uchar>(i + 2, j)));

			//the gradient of the image
				//b(i, j) = abs(gx) + abs(gy);
			//b(i, j) = sqrt(gx. ^ 2 + gy. ^ 2);



		}
		
	}
	*/

	//namedwindow(window_name, cv_window_autosize);

	/// generate grad_x and grad_y
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	Mat grad;

	/// gradient x
	//scharr( src_gray, grad_x, ddepth, 1, 0, scale, delta, BORDER_DEFAULT  );
	Sobel(gray_img, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);

	/// gradient y
	//scharr( src_gray, grad_y, ddepth, 0, 1, scale, delta, border_default );
	Sobel(gray_img, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);

	/// total gradient (approximate)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);



	imwrite("D:/su/document/1st semester/image processing/final assigment 2/Edge_map.jpg", grad);

	//create windows
	namedWindow("original image", WINDOW_NORMAL);
	namedWindow("new image", CV_WINDOW_NORMAL);

	//show the image
	imshow("original image", img);
	imshow("new image", grad);


	//imshow("histogram equalized", img_hist_equalized);

	//cout << "max value of bright" << bright << "bright";

	//cout << sizeimage;

	waitKey(0); //wait for key press

	destroyAllWindows(); //destroy all open windows

	return 0;
} 
