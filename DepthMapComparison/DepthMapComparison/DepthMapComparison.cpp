#include <stdio.h>
#include <stdlib.h>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <cv.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"




using namespace std;

void on_mouse(int EVENT, int x, int y, int flags, void* Image);


int main(int argc, char *argv[])
{

	char LImagePath[255];
	char RImagePath[255];
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--LImage") && i + 1 < argc) {
			strcpy(LImagePath, argv[++i]);
			printf("Left Image is:%s\t", LImagePath);
		}
		else if (!strcmp(argv[i], "--RImage") && i + 1 < argc) {
			strcpy(RImagePath, argv[++i]);
			printf("Right Image is:%s\n", RImagePath);
		}
		else {
			return -1;
		}
	}

	printf("\n\n");


	cv::namedWindow("DEPTH_COMPARISON", CV_WINDOW_AUTOSIZE);
	cv::Mat leftImage;
	cv::Mat rightImage;

	leftImage = cv::imread(LImagePath, CV_LOAD_IMAGE_UNCHANGED);
	rightImage = cv::imread(RImagePath, CV_LOAD_IMAGE_UNCHANGED);

	//leftImage = cv::imread("gt.png",CV_LOAD_IMAGE_UNCHANGED);
	//rightImage = cv::imread("lf.png", CV_LOAD_IMAGE_UNCHANGED);

	cv::Size size(leftImage.cols + rightImage.cols, MAX(leftImage.rows, rightImage.rows));
	cv::Mat img_merge(size.height, size.width, CV_8U);
	cv::Mat outImg_left, outImg_right;

	img_merge = cv::Scalar::all(0);

	outImg_left = img_merge(cv::Rect(0, 0, leftImage.cols, leftImage.rows));
	outImg_right = img_merge(cv::Rect(leftImage.cols, 0, rightImage.cols, rightImage.rows));

	leftImage.copyTo(outImg_left);
	rightImage.copyTo(outImg_right);

	cv::setMouseCallback("DEPTH_COMPARISON", on_mouse, &img_merge);

	while (1)
	{
		cv::imshow("DEPTH_COMPARISON", img_merge);
		cv::waitKey(30);
	}

	return 0;

}


void on_mouse(int EVENT, int x, int y, int flags, void* Image)
{
	cv::Mat depth;
	depth = *(cv::Mat*)Image;
	cv::Point p(x, y);
	switch (EVENT)
	{
	case cv::EVENT_LBUTTONDOWN:
	{
		if (p.x < depth.cols / 2)
		{
			cv::Point rightPos(p.x + depth.cols / 2, p.y);

			cv::circle(depth, p, 2, cv::Scalar(0));
			cv::circle(depth, rightPos, 2, cv::Scalar(255));

			
			printf("L_Depth = %d\n", depth.at<uchar>(p));
			printf("R_Depth = %d\n", depth.at<uchar>(rightPos));

			printf("-------------------------------------\n");
		}
		else
		{
			cv::Point leftPos(p.x - depth.cols / 2, p.y);

			cv::circle(depth, leftPos, 2, cv::Scalar(0));
			cv::circle(depth, p, 2, cv::Scalar(255));

			printf("L_Depth = %d\n", depth.at<uchar>(leftPos));
			printf("R_Depth = %d\n", depth.at<uchar>(p));

			printf("-------------------------------------\n");

		}

	}
	break;
	}
}
