#include "StdAfx.h"
#include "CVDct.h"

int Main_DCT()
{
	//---------------------------------------------------------
	//				Load Image from disk
	//---------------------------------------------------------
	//Mat mat = imread("D:\\testImages\\lena.bmp");
	//IplImage iplMat = mat;
	string str = DRIVE_LETTER + ":\\testImages\\lena.bmp";
	IplImage *iplMat = cvLoadImage(str.c_str());	//等價上兩行
	//---------------------------------------------------------------------------------------------
	IplImage *iplGrayImg = cvCreateImage(cvSize(iplMat->width, iplMat->height), iplMat->depth, 1);
	cvCvtColor(iplMat, iplGrayImg, CV_BGR2GRAY);
	cvShowImage("gray", iplGrayImg);
	int nImageFromat = CV_64FC1;
	CvMat* MatY = cvCreateMat(iplGrayImg->height,iplGrayImg->width,nImageFromat);  
	
	CvMat* DCTY = cvCreateMat(iplGrayImg->height, iplGrayImg->width,nImageFromat); 
	CvMat* IDCTY = cvCreateMat(iplGrayImg->height, iplGrayImg->width,nImageFromat);
	cvScale( iplGrayImg, MatY );  


	cvDCT(MatY, DCTY, CV_DXT_FORWARD); //  
	CvMat* DCTY8U = cvCreateMat(iplGrayImg->height, iplGrayImg->width,CV_8UC1);  
	cvConvertScaleAbs(DCTY, DCTY8U);
	cvShowImage("DCT.bmp", DCTY8U);
	waitKey(0);
	
	for(int i=0;i<50;i++)
		for(int j=0;j<50;j++)
			cvmSet(DCTY,i,j,0);
	
	cvDCT(DCTY, IDCTY, CV_DXT_INVERSE);
	CvMat* IDCTY8U = cvCreateMat(iplGrayImg->height, iplGrayImg->width,CV_8UC1);  
	cvConvertScaleAbs(IDCTY, IDCTY8U);
	cvShowImage("IDCT.bmp", IDCTY8U);
	waitKey(0);
	for(int i=0;i<iplGrayImg->width;i++)
	{
		for(int j=0;j<iplGrayImg->height;j++)
		{
			double d = cvmGet(MatY, i, j) + cvmGet(IDCTY, i, j);
			cvmSet(MatY, i, j, d);
		}
	}
	cvNormalize(MatY, MatY, 255, 0);
	cvShowImage("Enhance.bmp", MatY);
	waitKey(0);
	cvReleaseMat(&DCTY8U);
	cvReleaseMat(&IDCTY8U);
	cvReleaseMat(&IDCTY);
	cvReleaseMat(&DCTY);
	cvReleaseMat(&MatY);
	
	cvReleaseImage(&iplGrayImg);
	cvReleaseImage(&iplMat);
	return 0;
	
}