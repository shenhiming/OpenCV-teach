#include "StdAfx.h"
#include "CVMorphlogy.h"
const int nIter = 1;

int Main_Erosion()
{
	Mat img1 = imread( DRIVE_LETTER + ":\\testImages\\data\\box_in_scene.png", CV_LOAD_IMAGE_GRAYSCALE );
	threshold(img1, img1, 0, 255, THRESH_OTSU);
	imshow("otsu", img1);
	Erosion(img1);
	imshow("erode", img1);
	waitKey(0);
	return 0;
}
int Main_Dilation()
{
	Mat img1 = imread( DRIVE_LETTER + ":\\testImages\\data\\box_in_scene.png", CV_LOAD_IMAGE_GRAYSCALE );
	threshold(img1, img1, 0, 255, THRESH_OTSU);
	imshow("otsu", img1);
	Dilation(img1);
	imshow("dilate", img1);
	waitKey(0);
	return 0;
}
int Main_Opening()
{
	Mat img1 = imread( DRIVE_LETTER + ":\\testImages\\data\\box_in_scene.png", CV_LOAD_IMAGE_GRAYSCALE );
	threshold(img1, img1, 0, 255, THRESH_OTSU);
	imshow("otsu", img1);
	Erosion(img1);
	imshow("erode", img1);
	Dilation(img1);
	imshow("opening", img1);
	waitKey(0);
	return 0;
}
int Main_Closing()
{
	Mat img1 = imread( DRIVE_LETTER + ":\\testImages\\data\\box_in_scene.png", CV_LOAD_IMAGE_GRAYSCALE );
	threshold(img1, img1, 0, 255, THRESH_OTSU);
	imshow("otsu", img1);
	Dilation(img1);
	imshow("dilate", img1);
	Erosion(img1);
	imshow("closing", img1);
	waitKey(0);
	return 0;
}

void Erosion(Mat &img1)
{
	IplImage iplMat = img1;
	cvErode(&iplMat, &iplMat, 0, nIter);
	
}

void Dilation(Mat &img1)
{
	IplImage iplMat = img1;
	cvDilate(&iplMat, &iplMat, 0, nIter);
	
}