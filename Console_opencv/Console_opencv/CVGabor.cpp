#include "StdAfx.h"
#include "CVGabor.h"
int Main_Gabor()
{
	string str = DRIVE_LETTER + ":\\testImages\\lena.bmp";
	Mat in = imread(str,0);          // load grayscale
	Mat dest;
	Mat src_f;
	in.convertTo(src_f, CV_32F);
	normalize(src_f, src_f, 255, 0);
	imshow("src",src_f);
	waitKey(0);
	
	int kernel_size = 31;
	double sig = 4, thita = 30, lm = 1.0, gm = 0.9, ps = 0;
	Mat kernel = cv::getGaborKernel(cv::Size(kernel_size,kernel_size), sig, thita, lm, gm, ps);
	/*
	Parameters:	
	ksize �V Size of the filter returned.
	sigma �V Standard deviation of the gaussian envelope.
	theta �V Orientation of the normal to the parallel stripes of a Gabor function.
	lambd �V Wavelength of the sinusoidal factor.
	gamma �V Spatial aspect ratio.
	psi �V Phase offset.
	ktype �V Type of filter coefficients. It can be CV_32F or CV_64F .
	*/
	
	cv::filter2D(src_f, dest, CV_32F, kernel);

	cerr << dest(Rect(30,30,10,10)) << endl; // peek into the data

	Mat viz;
	dest.copyTo(viz);
	normalize(viz, viz, 255, 0);
	normalize(kernel, kernel, 255, 0);
	imshow("k",kernel);
	waitKey(0);
	imshow("d",viz);
	waitKey(0);;
	return 0;
}