#include "StdAfx.h"
#include "CVHistorgram.h"

int histSize = 256;
int hist_w = 512; int hist_h = 400;
int bin_w = cvRound( (double) hist_w/histSize );
float range[] = { 0, 256 } ;
const float* histRange = { range };

void DrawHistogram(Mat &histImage, int histSize, int bin_w, int hist_h, Mat &hist)
{
	for( int i = 1; i < histSize; i++ )
	{
		line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
			Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
			Scalar( 255, 255, 255), 2, 8, 0  );
	}
}

void DoHistogram(Mat &mat, Mat &hist, Mat &histImage)
{
	bool uniform = true; 
	bool accumulate = false;
	/// Compute the histograms:
	calcHist( &mat, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate );
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	DrawHistogram(histImage, histSize, bin_w, hist_h, hist);
}

int Main_Histogram()
{
	
	Mat src1, src2;

	/// Load image
	src1 = imread( DRIVE_LETTER + ":\\testImages\\RiverBank.jpg", 0);	//0:Gray, 1: Color
	src2 = imread( DRIVE_LETTER + ":\\testImages\\DarkClouds.jpg", 0);
	Mat hist1, hist2;
	Mat histImage1( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
	Mat histImage2( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	DoHistogram(src1, hist1, histImage1);
	DoHistogram(src2, hist2, histImage2);

	imshow("Image1", src1 );
	imshow("calcHist Demo1", histImage1 );
	imshow("Image2", src2 );
	imshow("calcHist Demo2", histImage2 );
	waitKey(0);

	printf("CV_COMP_CORREL : %.4f\n",compareHist(hist1,hist2,CV_COMP_CORREL));
	printf("CV_COMP_CHISQR : %.4f\n",compareHist(hist1,hist2,CV_COMP_CHISQR));
	printf("CV_COMP_INTERSECT : %.4f\n",compareHist(hist1,hist2,CV_COMP_INTERSECT));
	printf("CV_COMP_BHATTACHARYYA : %.4f\n",compareHist(hist1,hist2,CV_COMP_BHATTACHARYYA));

	return 0;
}


int Main_Histogram_Equalize()
{
	Mat src = imread(DRIVE_LETTER + ":\\testImages\\RiverBank.jpg", 0);	//0:Gray, 1: Color
	imwrite(DRIVE_LETTER + ":\\testImages\\gray.bmp", src);
	BYTE *dib = new BYTE[src.cols * src.rows];
	memset(dib, 0, src.cols * src.rows);
	IplImage Image1 = src;
	CIplImageTool::IplImageToBYTEStar(&Image1, dib);
	Hist_Eq(dib, src.cols, src.rows);
	Mat dst(src.rows, src.cols, CV_8UC1);
	IplImage Image2 = dst;
	CIplImageTool::BYTEStarToIplImage(dib, &Image2, src.cols, src.rows, 8);
	imwrite(DRIVE_LETTER + ":\\testImages\\histogram_eq.bmp", dst);

	Mat hist1, hist2;
	Mat histImage1( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
	Mat histImage2( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	DoHistogram(src, hist1, histImage1);
	DoHistogram(dst, hist2, histImage2);
	imshow("Image1", src );
	imshow("calcHist Demo1", histImage1 );
	imshow("Image2", dst );
	imshow("calcHist Demo2", histImage2 );
	waitKey(0);

	return 0;
	
}

int Main_CV_Histogram_Equalize()
{
	Mat src = imread(DRIVE_LETTER + ":\\testImages\\RiverBank.jpg", 0);	//0:Gray, 1: Color
	imwrite(DRIVE_LETTER + ":\\testImages\\gray.bmp", src);
	Mat dst(src.rows, src.cols, CV_8UC1);
	equalizeHist( src, dst );
	imwrite(DRIVE_LETTER + ":\\testImages\\cv_histogram_eq.bmp", dst);
	Mat hist1, hist2;
	Mat histImage1( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
	Mat histImage2( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

	DoHistogram(src, hist1, histImage1);
	DoHistogram(dst, hist2, histImage2);
	imshow("Image1", src );
	imshow("calcHist Demo1", histImage1 );
	imshow("Image2", dst );
	imshow("calcHist Demo2", histImage2 );
	waitKey(0);
	return 0;
}