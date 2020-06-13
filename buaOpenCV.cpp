// buaOpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	

	//*****************************************************************************************************************************

	Mat lane = imread("E:\\Visual Studio Project\\buaOpenCV\\lane.jpg");
	cout << lane.rows << " " << lane.cols << endl;
	Mat grayLane;
	cvtColor(lane, grayLane, CV_BGR2GRAY);
	imshow("Lane", lane);
	imshow("First gray lane", grayLane);
	for (int i = 0; i < grayLane.rows; i++)
		for (int j = 0; j < grayLane.cols; j++)
			if (grayLane.at<uchar>(i, j) < 225)
				grayLane.at<uchar>(i, j) -= 25;
	imshow("Processed gray lane", grayLane);
	cv::Mat laneHSV, hsv[3];
	cv::cvtColor(lane, laneHSV, cv::COLOR_BGR2HSV);	// ảnh scrHSV là ảnh scr biến đổi từ BGR sang HSV
	// Tách các kênh màu hsv[0] = H, hsv[1] = S, hsv[2] = V
	cv::split(laneHSV, hsv);
	cv::imshow("HSV image", laneHSV);
	Mat maskYellow, maskWhite, mask, processed;
	inRange(grayLane, Scalar(0, 200, 0), Scalar(200, 255, 255), maskWhite);
	inRange(grayLane, Scalar(10, 0, 100), Scalar(40, 255, 255), maskYellow);
	bitwise_or(maskWhite, maskYellow, mask);
	//inRange(grayLane, Scalar(20, 100, 100), Scalar(30, 255, 255), maskYellow);
	//inRange(grayLane, Scalar(150, 150, 150), Scalar(255, 255, 255), maskWhite);
	//bitwise_or(maskYellow, maskWhite, mask);  
	//Combine the two masks 
	bitwise_and(grayLane, mask, processed);
	imshow("Anh duong den trang", processed);
	Mat grayGB;
	const Size kernelSize = Size(7, 7);
	//GaussianBlur(processed, grayGB, kernelSize, 2, 2);
	GaussianBlur(processed, grayGB, kernelSize, 0);
	imshow("Anh duong sau gaussian blur", grayGB);
	Mat grayCanny;
	//Canny(grayGB, grayCanny, 110, 210);
	Canny(grayGB, grayCanny, 70, 140);
	imshow("Anh duong sau canny", grayCanny);

	vector<Vec4i> lines;
	HoughLinesP(grayCanny, lines, 1, CV_PI/180, 20, 20, 10);
	Vec4i l0, l1;
	for (int i = 0; i < lines.size(); i++)
	{
		l1 = lines[i];
		line(lane, Point(l1[0], l1[1]), Point(l1[2], l1[3]), Scalar(0, 255, 0), 1);
	}
	imshow("Lane detection", lane);
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
