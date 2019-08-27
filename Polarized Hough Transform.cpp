#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include <string>
#include <map>
#include <iostream>
#include <math.h>

#define DEG2RAD 0.017453293f

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	// Declare the output variables
	Mat dst, cdst, cdstP;
	Mat img_blur;
	//const char* default_file = "../../../data/sudoku.png";
	//const char* filename = argc >= 2 ? argv[1] : default_file;
	// Loads an image
	Mat src = imread("D:/su/document/1st semester/image processing/final assigment 2/in.png", CV_LOAD_IMAGE_COLOR); //open and read the image

	if (src.empty()) //if unsuccessful, exit the program
	{
		cout << "image cannot be loaded..!!" << endl;
		return -1;
	}
	// Edge detection

	cv::blur(src, img_blur, cv::Size(5, 5));
	Canny(img_blur, dst, 100, 150, 3);
	// Copy edges to the images that will display the results in BGR
	//cvtColor(dst, cdst, COLOR_GRAY2BGR);

	int w = dst.cols;
	int h = dst.rows;

	int _img_w = w;
	int _img_h = h;

	//Create the accu  
	double hough_h = ((sqrt(2.0) * (double)(h>w ? h : w)) / 2.0);
	int _accu_h = hough_h * 2.0; // -r -> +r  
	int _accu_w = 180;
	unsigned int *_accu = (unsigned int*)calloc(_accu_h * _accu_w, sizeof(unsigned int));
	int window[7][7];
	int sum = 0;
	for (int r = 3; r < dst.rows - 3; r++)
	{
		for (int c = 3; c < dst.cols - 3; c++)
		{
			int pixel = dst.at<uchar>(r, c);
			if (pixel == 1)
			{
				for (int y = -3; y < 3; y++)
				{
					for (int x = -3; x < 3; x++)
					{
						window[y][x] = dst.at<uchar>(r + y, c + x);
					}
				}
			}
			//sobel mask for x - direction:
			//int gx = ((2 * grayimage.at<uchar>(i + 2, j + 1) + grayimage.at<uchar>(i + 2, j) + grayimage.at<uchar>(i + 2, j + 2)) - (2 * grayimage.at<uchar>(i, j + 1) + c(i, j) + grayimage.at<uchar>(i, j + 2)));
			//sobel mask for y - direction:
			//int gy = ((2 * grayimage.at<uchar>(i + 1, j + 2) + grayimage.at<uchar>(i, j + 2) + grayimage.at<uchar>(i + 2, j + 2)) - (2 * grayimage.at<uchar>(i + 1, j) + c(i, j) + grayimage.at<uchar>(i + 2, j)));

			//the gradient of the image
			//b(i, j) = abs(gx) + abs(gy);
			//b(i, j) = sqrt(gx. ^ 2 + gy. ^ 2);



		}

	}



	//unsigned int *img_data = (unsigned int*)calloc(_accu_h * _accu_w, sizeof(unsigned int));

	//for (int y = 0; y < h; y++)
	//{
	//	for (int x = 0; x < w; x++)
	//	{
	//		img_data[(y*w) + x] = (uint)cdst.at<uchar>(y, x);

	//	}
	//}

	/*
	double center_x = w / 2;
	double center_y = h / 2;

	for (int y = 0; y<h; y++)
	{
		for (int x = 0; x<w; x++)
		{
			if (dst.data[(y*w) + x] > 250)
			{
				for (int t = 0; t<180; t++)
				{
					double r = (((double)x - center_x) * cos((double)t * DEG2RAD)) + (((double)y - center_y) * sin((double)t * DEG2RAD));
					_accu[(int)((round(r + hough_h) * 180.0)) + t]++;
				}
			}
		}
	}
	*/

	std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > lines;

	//if (_accu == 0)
	//	return lines;

	int threshold = 270;

	for (int r = 0; r<_accu_h; r++)
	{
		for (int t = 0; t<_accu_w; t++)
		{
			if ((int)_accu[(r*_accu_w) + t] >= threshold)
			{
				//Is this point a local maxima (9x9)
				int max = _accu[(r*_accu_w) + t];
				for (int ly = -4; ly <= 4; ly++)
				{
					for (int lx = -4; lx <= 4; lx++)
					{
						if ((ly + r >= 0 && ly + r<_accu_h) && (lx + t >= 0 && lx + t<_accu_w))
						{
							if ((int)_accu[((r + ly)*_accu_w) + (t + lx)] > max)
							{
								max = _accu[((r + ly)*_accu_w) + (t + lx)];
								ly = lx = 5;
							}
						}
					}
				}
				if (max >(int)_accu[(r*_accu_w) + t])
					continue;


				int x1, y1, x2, y2;
				x1 = y1 = x2 = y2 = 0;

				if (t >= 45 && t <= 135)
				{
					//y = (r - x cos(t)) / sin(t)
					x1 = 0;
					y1 = ((double)(r - (_accu_h / 2)) - ((x1 - (_img_w / 2)) * cos(t * DEG2RAD))) / sin(t * DEG2RAD) + (_img_h / 2);
					x2 = _img_w - 0;
					y2 = ((double)(r - (_accu_h / 2)) - ((x2 - (_img_w / 2)) * cos(t * DEG2RAD))) / sin(t * DEG2RAD) + (_img_h / 2);
				}
				else
				{
					//x = (r - y sin(t)) / cos(t);
					y1 = 0;
					x1 = ((double)(r - (_accu_h / 2)) - ((y1 - (_img_h / 2)) * sin(t * DEG2RAD))) / cos(t * DEG2RAD) + (_img_w / 2);
					y2 = _img_h - 0;
					x2 = ((double)(r - (_accu_h / 2)) - ((y2 - (_img_h / 2)) * sin(t * DEG2RAD))) / cos(t * DEG2RAD) + (_img_w / 2);
				}

				lines.push_back(std::pair< std::pair<int, int>, std::pair<int, int> >(std::pair<int, int>(x1, y1), std::pair<int, int>(x2, y2)));

			}
		}
	}

	if (threshold == 0)
		threshold = w>h ? w / 4 : h / 4;

	//threshold = 20;

	while (1)
	{

		Mat img_res = src.clone();

		//Search the accumulator
		//std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > > lines = hough.GetLines(threshold);

		//Draw the results
		std::vector< std::pair< std::pair<int, int>, std::pair<int, int> > >::iterator it;
		for (it = lines.begin(); it != lines.end(); it++)
		{
			cv::line(img_res, cv::Point(it->first.first, it->first.second), cv::Point(it->second.first, it->second.second), cv::Scalar(0, 0, 255), 2, 8);
		}

		//Visualize all
		int aw, ah, maxa;
		aw = ah = maxa = 0;
		aw = _accu_w;
		ah = _accu_h;
		//const unsigned int* accu = hough.GetAccu(&aw, &ah);
		const unsigned int* accu = _accu;

		for (int p = 0; p<(ah*aw); p++)
		{
			if ((int)accu[p] > maxa)
				maxa = accu[p];
		}
		double contrast = 1.0;
		double coef = 255.0 / (double)maxa * contrast;

		Mat img_accu(ah, aw, CV_8UC3);

		for (int p = 0; p<(ah*aw); p++)
		{
			unsigned char c = (double)accu[p] * coef < 255.0 ? (double)accu[p] * coef : 255.0;
			img_accu.data[(p * 3) + 0] = 255;
			img_accu.data[(p * 3) + 1] = 255 - c;
			img_accu.data[(p * 3) + 2] = 255 - c;
		}


		//create windows
		namedWindow("original image", WINDOW_NORMAL);
		namedWindow("new image", CV_WINDOW_NORMAL);
		namedWindow("new image 1", CV_WINDOW_NORMAL);
		//cvMoveWindow("new image", 1350, 10);

		//show the image
		imshow("original image", src);
		imshow("new image", dst);
		imshow("new image 1", img_res);

		// Wait and Exit
		//waitKey();
		//return 0;

		char c = cv::waitKey(360000);
		if (c == '+')
			threshold += 5;
		if (c == '-')
			threshold -= 5;
		if (c == 27)
			break;
	}


}