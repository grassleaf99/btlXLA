// buaOpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

int main()
{
	

	//*****************************************************************************************************************************

	Mat lane = imread("E:\\Visual Studio Project\\buaOpenCV\\lane.jpg");
	Mat grayLane;
	cvtColor(lane, grayLane, CV_BGR2GRAY);
	imshow("Lane", lane);
	imshow("Gray lane", grayLane);
	cv::Mat laneHSV, hsv[3];
	cv::cvtColor(lane, laneHSV, cv::COLOR_BGR2HSV);	// ảnh scrHSV là ảnh scr biến đổi từ BGR sang HSV
	// Tách các kênh màu hsv[0] = H, hsv[1] = S, hsv[2] = V
	cv::split(laneHSV, hsv);
	cv::imshow("HSV image", laneHSV);
	Mat maskYellow, maskWhite, mask, processed;
	inRange(grayLane, Scalar(20, 100, 100), Scalar(30, 255, 255), maskYellow);
	inRange(grayLane, Scalar(150, 150, 150), Scalar(255, 255, 255), maskWhite);
	bitwise_or(maskYellow, maskWhite, mask); 
	//Combine the two masks 
	bitwise_and(grayLane, mask, processed);
	imshow("Anh duong den trang", processed);
	Mat grayGB;
	const Size kernelSize = Size(9, 9);
	GaussianBlur(processed, grayGB, kernelSize, 0);
	imshow("Anh duong sau gaussian blur", grayGB);
	Mat grayCanny;
	Canny(grayGB, grayCanny, 110, 210);
	imshow("Anh duong sau canny", grayCanny);
	waitKey(0);

	//*****************************************************************************************************************************
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
