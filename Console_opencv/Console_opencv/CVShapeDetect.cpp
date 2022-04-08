#include "StdAfx.h"
#include "CVShapeDetect.h"
int Main_HoughLineDetector()
{
	

	Mat src = imread(DRIVE_LETTER + ":\\testImages\\data\\Building.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	

	Mat dst, cdst;
	Canny(src, dst, 50, 200, 3);
	cvtColor(dst, cdst, CV_GRAY2BGR);

#if 0
	vector<Vec2f> lines;
	HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );
	//dst: Output of the edge detector. It should be a grayscale image (although in fact it is a binary one)
	//lines: A vector that will store the parameters (r,\theta) of the detected lines
	//rho : The resolution of the parameter r in pixels. We use 1 pixel.
	//theta: The resolution of the parameter \theta in radians. We use 1 degree (CV_PI/180)
	//threshold: The minimum number of intersections to ¡§detect¡¨ a line
	//		   srn and stn: Default parameters to zero. Check OpenCV reference for more info.
	for( size_t i = 0; i < lines.size(); i++ )
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
	}
#else
	vector<Vec4i> lines;
	HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
	if(lines.size() > 0)
	{
		for( size_t i = 0; i < lines.size(); i++ )
		{
			Vec4i l = lines[i];
			line( cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
		}
	}
#endif
	imshow("source", src);
	imshow("detected lines", cdst);

	waitKey();

	return 0;
}
int	Main_HoughCircleDetector()
{
	Mat src, src_gray;

	/// Read the image
	
	src = imread(DRIVE_LETTER + ":\\testImages\\disk.jpg", CV_LOAD_IMAGE_COLOR);

	if( !src.data )
	{ return -1; }

	/// Convert it to gray
	cvtColor( src, src_gray, CV_BGR2GRAY );

	/// Reduce the noise so we avoid false circle detection
	GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

	vector<Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200, 100, 0, 0 );
	/*src_gray: Input image (grayscale)
	circles: A vector that stores sets of 3 values: x_{c}, y_{c}, r for each detected circle.
	CV_HOUGH_GRADIENT: Define the detection method. Currently this is the only one available in OpenCV
	dp = 1: The inverse ratio of resolution
	min_dist = src_gray.rows/8: Minimum distance between detected centers
	param_1 = 200: Upper threshold for the internal Canny edge detector
	param_2 = 100*: Threshold for center detection.
	min_radius = 0: Minimum radio to be detected. If unknown, put zero as default.
	max_radius = 0: Maximum radius to be detected. If unknown, put zero as default*/
	/// Draw the circles detected
	for( size_t i = 0; i < circles.size(); i++ )
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );
		// circle outline
		circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );
	}

	/// Show your results
	namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
	imshow( "Hough Circle Transform Demo", src );

	waitKey(0);

	return 0;
}