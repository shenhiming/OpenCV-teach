#include "StdAfx.h"
#include "CVThresholding.h"
void Main_Thresholding()
{
	string str = DRIVE_LETTER + ":\\testImages\\data\\box_in_scene.png";
	Mat img1 = imread( str, CV_LOAD_IMAGE_GRAYSCALE );
	threshold(img1, img1, 0, 255, THRESH_OTSU);
	imshow("otsu", img1);
	waitKey(0);
}