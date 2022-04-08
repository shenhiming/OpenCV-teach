#pragma once
#include <vector>
#include "opencv\cv.h"
#include "opencv\opencv2\highgui\highgui.hpp"
#include "opencv\opencv2\core\core.hpp"
#include "opencv\opencv2\imgproc\imgproc.hpp"
#include "opencv\cvaux.h"
#include <time.h>

#define _USE_MATH_DEFINES
#include <math.h>



using namespace std;
using namespace cv;
const string DRIVE_LETTER = "E";	//ºÏºÐ¾÷¥N¸¹
float ComputeTime(clock_t start_time, clock_t end_time);

class CCVImageTools
{
public:
	CCVImageTools(void);
	~CCVImageTools(void);
};

class CIplImageTool
{
public:
	CIplImageTool(){};
	~CIplImageTool(){};

	//----------------------------------------------------------------------------------------------
	static BYTE *GetIplImagePixAddr(IplImage *pImg, int x, int y);
	static void BYTEStarToIplImage(byte *pImg, IplImage *pIplImg, int width,int height,int bitCount);
	static void IplImageToBYTEStar(IplImage *IplImg, BYTE *dib);
	static void EdgeDetection(IplImage *pInImg, IplImage *pOutImg, vector<Point> *pEdgeVec = NULL);


};
bool CheckBoundary(int x, int w);
Point2d RotatePoint(double xc, double yc, double x, double y, double angle);
Rect ComputeAfterRotateBoundary(Point2d pt1, Point2d pt2, Point2d pt3, Point2d pt4);

//--------------------------------------------------------------------------------------------------
//									Contour
//--------------------------------------------------------------------------------------------------
void GetExternalContourLabeling(IplImage *pIPL_DEPTH_8U1CImg, IplImage *pIPL_DEPTH_8U3CImg, vector<CRect> &contourRectArray, int areaTh, vector<vector<Point>> *pContourVec);
void GetInternalContourLabeling(IplImage *pIPL_DEPTH_8U1CImg, IplImage *pIPL_DEPTH_8U3CImg, vector<CRect> &contourRectArray, int areaTh);
void GetContourLayerCount(CvSeq *contour, int areaTh, int &currContourLayerCount, int &nContourLayerCount);
int RecursiveContour(CvSeq *contour, IplImage *pIPL_DEPTH_8U1CImg, IplImage *pIPL_DEPTH_8U3CImg, vector<CRect> &contourRectArray, int areaTh, int &currContourLayerCount, int nContourLayerCount);
void GetInternalContourList(IplImage *pIPL_DEPTH_8U1CImg, IplImage *pIPL_DEPTH_8U3CImg, vector<CRect> &contourRectArray, int areaTh, vector<vector<Point>> *pContourVec);