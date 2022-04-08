#include "StdAfx.h"
#include "CVConnectedComponent.h"



void Main_ConnectedComponent(int nSubItem)
{
	Mat mat = imread(DRIVE_LETTER + ":\\testImages\\4ab733ca63d52.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	threshold(mat, mat, 0, 255, THRESH_OTSU);
	imshow("otsu", mat);
	IplImage iplMat = mat;
	IplImage *iplMatResult = cvCreateImage(cvSize(iplMat.width, iplMat.height), 8, 3);
	for(int i=0;i<iplMat.width;i++)
	{
		for(int j=0;j<iplMat.height;j++)
		{
			BYTE *pSrc = CIplImageTool::GetIplImagePixAddr(&iplMat, i, j);
			BYTE *pDst = CIplImageTool::GetIplImagePixAddr(iplMatResult, i, j);
			*pDst = *(pDst + 1) = *(pDst + 2) = *pSrc;
		}
	}
	
	vector<vector<Point>> contourVec;//vector<Point>:a contour, Point:a edge
	vector<CRect> rectVec;
	int areaTh = 20;
	
	switch(nSubItem)
	{
	case CCT_INTERAL_LABELING:
		GetInternalContourLabeling(&iplMat, iplMatResult, rectVec, areaTh);
		break;
	case CCT_INTERNAL_LIST:
		GetInternalContourList(&iplMat, iplMatResult, rectVec, areaTh, &contourVec);
		break;
	case CCT_EXTERNAL_LABELING:
		GetExternalContourLabeling(&iplMat, iplMatResult, rectVec, areaTh, &contourVec);
		break;
	case CCT_INTERNAL_LIST_ROTATERECT:
		GetInternalContourList(&iplMat, iplMatResult, rectVec, areaTh, &contourVec);
		Main_RotateRect(iplMat, contourVec);
	default:
		break;
	}
	
	cvShowImage("ConnectedComponent", iplMatResult);
	waitKey(0);
	cvReleaseImage(&iplMatResult);

}

void Main_RotateRect(IplImage &iplMat, vector<vector<Point>> &contourVec)
{
	IplImage *iplMatResult = cvCreateImage(cvSize(iplMat.width, iplMat.height), 8, 3);
	for(int i=0;i<iplMat.width;i++)
	{
		for(int j=0;j<iplMat.height;j++)
		{
			BYTE *pSrc = CIplImageTool::GetIplImagePixAddr(&iplMat, i, j);
			BYTE *pDst = CIplImageTool::GetIplImagePixAddr(iplMatResult, i, j);
			*pDst = *(pDst + 1) = *(pDst + 2) = *pSrc;
		}
	};
	int size = static_cast<int>(contourVec.size());
	
	if(size <= 0) return;
	for(int i=0;i<size;i++)// for each contour
	{
		cv::RotatedRect rRect = minAreaRect(contourVec[i]);
		// drawing
		Scalar color = Scalar(0, 255, 255);
		Point2f rect_points[4]; 
		rRect.points( rect_points );
		for( int j = 0; j < 4; j++ )
			cvLine( iplMatResult, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );
	
	}
	cvShowImage("minAreaRect", iplMatResult);

	waitKey(0);
	cvReleaseImage(&iplMatResult);
}

