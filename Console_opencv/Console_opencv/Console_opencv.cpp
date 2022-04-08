// Console_opencv.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Console_opencv.h"
#include <iostream>
#include <stdlib.h> 
#include <fstream>
#include "CVImageTools.h"
#include "CVHistorgram.h"
#include "CVTemplateMatching.h"
#include "CVHarrisCorner.h"
#include "CVSIFT.h"
#include "CVSURF.h"
#include "CVORB.h"
#include "CVThresholding.h"
#include "CVMorphlogy.h"
#include "CVConnectedComponent.h"
#include "CVDct.h"
#include "CVGabor.h"
#include "HaarWavelet.h"
#include "CVShapeDetect.h"



enum METHOD_TYPE
{
	MT_SOBEL = 1, MT_MYSOBEL,											// Edge detector
	MT_TEMPLATE_MATCHING,												// Template matching by pixel
	MT_HISTOGRAM, MT_HISTOGRAM_EQUALIZE, MT_CV_HISTOGRAM_EQUALIZE,		// Template matching by historgram
	MT_HARRIS_CORNER, MT_SIFT, MT_SURF, MT_ORB,							// Feature detector
	MT_THRESHOLDING, MT_EROSION, MT_DILATION, MT_OPENING, MT_CLOSING,	// Thresholding & Morphlogy
	MT_CONNECTED_COMPONENT,												// Contours
	MT_DCT, MT_WAVELET, MT_GABOR,										// Frequency domain transform
	MT_HOUGH_LINE_DETECTOR, MT_HOUGH_CIRCLE_DETECTOR					// Shaple detector

};




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
using namespace cv;
int Main_Sobel(void);
int Main_MySobel(void);


int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			test();
			/*
			int nItem = -1;
			int nSubItem = -1;
			bool bStop = false;
			while(!bStop)
			{
				printf("Function list:\n");
				printf("1) Sobel\n");
				printf("2) MySobel\n");
				printf("3) TemplateMatching\n");
				printf("4) Histogram\n");
				printf("5) Histogram_Equalize\n");
				printf("6) CV_Histogram_Equalize\n");
				printf("7) HarrisCorner\n");
				printf("8) SIFT\n");
				printf("9) SURF\n");
				printf("10) ORB\n");
				printf("11) CV_Thresholding\n");
				printf("12) CV_Erosion\n");
				printf("13) CV_Dilation\n");
				printf("14) CV_Opening\n");
				printf("15) CV_Closing\n");
				printf("16) CV_ConnectedComponent\n");
				printf("17) CV_DCT\n");
				printf("18) HarrWavelet\n");
				printf("19) CVGabor\n");
				printf("20) CV_Hough_Line_Detector\n");
				printf("21) CV_Hough_Circle_Detector\n");
				printf("22) EXIT\n");
				printf("\nPlease select an item:\n");
				scanf("%d", &nItem);
				switch(nItem)
				{
				case MT_SOBEL:
					Main_Sobel();
					break;
				case MT_MYSOBEL:
					Main_MySobel();
					break;
				case MT_TEMPLATE_MATCHING:
					Main_TemplateMatching();
					break;
				case MT_HISTOGRAM:
					Main_Histogram();
					break;
				case MT_HISTOGRAM_EQUALIZE:
					Main_Histogram_Equalize();
					break;
				case MT_CV_HISTOGRAM_EQUALIZE:
					Main_CV_Histogram_Equalize();
					break;
				case MT_HARRIS_CORNER:
					CVHarrisCorner::Main_HarrisCorner();
					break;
				case MT_SIFT:
					Main_SIFT();
					break;
				case MT_SURF:
					Main_SURF();
					break;
				case MT_ORB:
					Main_ORB();
					break;
				case MT_THRESHOLDING:
					Main_Thresholding();
					break;
				case MT_EROSION:
					Main_Erosion();
					break;
				case MT_DILATION:
					Main_Dilation();
					break;
				case MT_OPENING:
					Main_Opening();
					break;
				case MT_CLOSING:
					Main_Closing();
					break;
				case MT_CONNECTED_COMPONENT:
					printf("1)InternalContourLabeling\n");
					printf("2)InternalContourList\n");
					printf("3)ExternalContourLabeling\n");
					printf("4)ExternalContourLabeling + RotateRect\n");
					printf("\nPlease select an item:\n");
					scanf("%d", &nSubItem);
					Main_ConnectedComponent(nSubItem);
					break;
				case MT_DCT:
					Main_DCT();
					break;
				case MT_WAVELET:
					Main_HarrWavelet();
					break;
				case MT_GABOR:
					Main_Gabor();
					break;
				case MT_HOUGH_LINE_DETECTOR:
					Main_HoughLineDetector();
					break; 
				case MT_HOUGH_CIRCLE_DETECTOR:
					Main_HoughCircleDetector();
					break;
				default:
					bStop = true;
					break;
				}
			}
			*/
			system("pause");
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}



int Main_Sobel()
{
	string str = DRIVE_LETTER + ":\\testImages\\lena.bmp";
	Mat mat = imread(str);
	IplImage iplMat = mat;
	IplImage *iplGrayImg = cvCreateImage(cvSize(mat.cols, mat.rows), iplMat.depth, 1);
	cvCvtColor(&iplMat, iplGrayImg, CV_BGR2GRAY);
	cvShowImage("gray.bmp", iplGrayImg);
	waitKey(0);
	IplImage *iplSobelDxImg16S = cvCreateImage(cvSize(mat.cols, mat.rows), IPL_DEPTH_16S, 1);
	IplImage *iplSobelDyImg16S = cvCreateImage(cvSize(mat.cols, mat.rows), IPL_DEPTH_16S, 1);
	cvSobel(iplGrayImg, iplSobelDxImg16S, 1, 0);
	cvSobel(iplGrayImg, iplSobelDyImg16S, 0, 1);

	IplImage *iplSobelDxImg8U = cvCreateImage(cvSize(mat.cols, mat.rows), IPL_DEPTH_8U, 1);
	IplImage *iplSobelDyImg8U = cvCreateImage(cvSize(mat.cols, mat.rows), IPL_DEPTH_8U, 1);
	cvConvertScaleAbs(iplSobelDxImg16S, iplSobelDxImg8U);
	cvConvertScaleAbs(iplSobelDyImg16S, iplSobelDyImg8U);
	IplImage *iplSobelImg = cvCreateImage(cvSize(mat.cols, mat.rows), IPL_DEPTH_8U, 1);
	double sobelTh = 127;
	for(int i=0;i<mat.cols;i++)
	{
		for(int j=0;j<mat.rows;j++)
		{
			BYTE nSrcDx = *CIplImageTool::GetIplImagePixAddr(iplSobelDxImg8U, i, j);
			BYTE nSrcDy = *CIplImageTool::GetIplImagePixAddr(iplSobelDyImg8U, i, j);
			BYTE *pDst = CIplImageTool::GetIplImagePixAddr(iplSobelImg, i, j);
			if(sqrt(static_cast<double>(nSrcDx * nSrcDx + nSrcDy * nSrcDy)) > sobelTh)
			{
				*pDst = 0;
			}
			else
			{
				*pDst = 255;
			}
		}
	}
	cvShowImage("sobel.bmp", iplSobelImg);
	waitKey(0);
	cvReleaseImage(&iplGrayImg);
	cvReleaseImage(&iplSobelDxImg16S);
	cvReleaseImage(&iplSobelDyImg16S);
	cvReleaseImage(&iplSobelDxImg8U);
	cvReleaseImage(&iplSobelDyImg8U);
	cvReleaseImage(&iplSobelImg);
	
	
	return 0;
}

int Main_MySobel()
{
	const int sobelOp_x[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
	const int sobelOp_y[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
	string str = DRIVE_LETTER + ":\\testImages\\lena.bmp";
	Mat mat = imread(str);
	IplImage iplMat = mat;
	IplImage *iplGrayImg = cvCreateImage(cvSize(mat.cols, mat.rows), iplMat.depth, 1);
	cvCvtColor(&iplMat, iplGrayImg, CV_BGR2GRAY);
	cvShowImage("gray.bmp", iplGrayImg);
	waitKey(0);
	IplImage *iplSobelImg = cvCreateImage(cvSize(mat.cols, mat.rows), IPL_DEPTH_8U, 1);
	cvZero(iplSobelImg);
	double sobelTh = 127;
	BYTE rgnArray[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	for(int i=1;i<mat.cols - 1;i++)
	{
		for(int j=1;j<mat.rows -1;j++)
		{
			rgnArray[0] = *CIplImageTool::GetIplImagePixAddr(iplGrayImg, i - 1, j - 1);
			rgnArray[1] = *CIplImageTool::GetIplImagePixAddr(iplGrayImg, i, j - 1);
			rgnArray[2] = *CIplImageTool::GetIplImagePixAddr(iplGrayImg, i + 1, j - 1);
			rgnArray[3] = *CIplImageTool::GetIplImagePixAddr(iplGrayImg, i - 1, j);
			rgnArray[4] = *CIplImageTool::GetIplImagePixAddr(iplGrayImg, i, j);
			rgnArray[5] = *CIplImageTool::GetIplImagePixAddr(iplGrayImg, i + 1, j);
			rgnArray[6] = *CIplImageTool::GetIplImagePixAddr(iplGrayImg, i - 1, j + 1);
			rgnArray[7] = *CIplImageTool::GetIplImagePixAddr(iplGrayImg, i, j + 1);
			rgnArray[8] = *CIplImageTool::GetIplImagePixAddr(iplGrayImg, i + 1, j + 1);
			int nSrcDx = 0;
			int nSrcDy = 0;
			for(int k=0;k<9;k++)
			{
				nSrcDx += rgnArray[k] * sobelOp_x[k];
				nSrcDy += rgnArray[k] * sobelOp_y[k];
			}
			nSrcDx = abs(nSrcDx);
			nSrcDy = abs(nSrcDy);
			BYTE *pDst = CIplImageTool::GetIplImagePixAddr(iplSobelImg, i, j);
			if(sqrt(static_cast<double>(nSrcDx * nSrcDx + nSrcDy * nSrcDy)) > sobelTh)
			{
				*pDst = 0;
			}
			else
			{
				*pDst = 255;
			}
		}
	}
	cvShowImage("mySobel.bmp", iplSobelImg);
	waitKey(0);
	cvReleaseImage(&iplSobelImg);
	cvReleaseImage(&iplGrayImg);

	
	return 0;
}