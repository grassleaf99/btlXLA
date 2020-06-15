// buaOpenCV.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

int main()
{
	

	//*****************************************************************************************************************************
	
	// anh goc la anh lane
	Mat lane = imread("E:\\Visual Studio Project\\buaOpenCV\\lane.jpg");
	cout << lane.rows << " " << lane.cols << endl;	// in ra so hang va so cot cua anh lane

	Mat grayLane;
	cvtColor(lane, grayLane, CV_BGR2GRAY);	// anh grayLane la anh lane chuyen sang gray scale

	imshow("Lane", lane);	// hien thi anh lane
	imshow("First gray lane", grayLane);	// hien thi anh grayLane chua qua lam toi
	
	for (int i = 0; i < grayLane.rows; i++)
		for (int j = 0; j < grayLane.cols; j++)
		{
			if(i < (grayLane.rows * 0.6))
				grayLane.at<uchar>(i, j) -= 10;
			else if ((j < (grayLane.cols * 0.15)) || (j > (0.9 * grayLane.cols)))
				grayLane.at<uchar>(i, j) -= 10;
			else if (grayLane.at<uchar>(i, j) < 250)
				grayLane.at<uchar>(i, j) -= 20;
		}
	imshow("Processed gray lane", grayLane);	// hien thi anh grayLane da qua lam toi
	
	// tao mask yellow va mask white de tach phan vach duong vang va trang
	Mat maskYellow, maskWhite, mask, processed;
	//inRange(grayLane, Scalar(0, 200, 0), Scalar(200, 255, 255), maskWhite);
	//inRange(grayLane, Scalar(10, 0, 100), Scalar(40, 255, 255), maskYellow);
	//bitwise_or(maskWhite, maskYellow, mask);
	inRange(grayLane, Scalar(20, 100, 100), Scalar(30, 255, 255), maskYellow);
	inRange(grayLane, Scalar(150, 150, 150), Scalar(255, 255, 255), maskWhite);
	//Combine the two masks
	bitwise_or(maskYellow, maskWhite, mask);  
	// anh processed la ket hop mask yellow + white voi grayLane
	bitwise_and(grayLane, mask, processed);
	imshow("Anh duong den trang", processed);
	
	// loc anh = gaussian blur
	Mat grayGB;
	const Size kernelSize = Size(11, 11);
	//const Size kernelSize = Size(9, 9);	// huong dan link c++
	//const Size kernelSize = Size(7, 7);	// huong dan link python
	//GaussianBlur(processed, grayGB, kernelSize, 2, 2);
	GaussianBlur(processed, grayGB, kernelSize, 0);
	imshow("Anh duong sau gaussian blur", grayGB);
	
	// tim bien vach ke duong = canny
	Mat grayCanny;
	//Canny(grayGB, grayCanny, 110, 210);
	Canny(grayGB, grayCanny, 70, 140);
	imshow("Anh duong sau canny", grayCanny);

	// tim vach ke duong = hough
	vector<Vec4i> lines;
	// tao khung chu nhat chua vach ke duong
	Rect rect = Rect(grayCanny.cols * 0.15, grayCanny.rows * 0.6, 0.75 * grayCanny.cols, 0.4 * grayCanny.rows);
	HoughLinesP(grayCanny(rect), lines, 1, CV_PI/180, 20, 20, 10);
	// to mau vach ke duong tim duoc
	Vec4i l0, l1;
	for (int i = 0; i < lines.size(); i++)
	{
		l1 = lines[i];
		line(lane, Point(l1[0] + grayCanny.cols * 0.15, l1[1] + grayCanny.rows * 0.6), Point(l1[2] + grayCanny.cols * 0.15, l1[3] + grayCanny.rows * 0.6), Scalar(0, 255, 0), 2);
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
