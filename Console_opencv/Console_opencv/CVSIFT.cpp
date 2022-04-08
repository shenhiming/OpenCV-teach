#include "StdAfx.h"
#include "CVSIFT.h"

int Main_SIFT()
{
	//if( argc != 3 )
	//{ readme(); return -1; }

	Mat img1 = imread( DRIVE_LETTER + ":\\testImages\\data\\box.png", CV_LOAD_IMAGE_GRAYSCALE );
	Mat img2 = imread( DRIVE_LETTER + ":\\testImages\\data\\box_in_scene.png", CV_LOAD_IMAGE_GRAYSCALE );

	
	if(img1.empty() || img2.empty())
	{
		printf("Can't read one of the imagesn");
		return -1;
	}

	clock_t start_time = clock();
	// detecting keypoints
	SiftFeatureDetector detector(400);
	vector<KeyPoint> keypoints1, keypoints2;
	detector.detect(img1, keypoints1);
	detector.detect(img2, keypoints2);

	// computing descriptors
	SiftDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;
	extractor.compute(img1, keypoints1, descriptors1);
	extractor.compute(img2, keypoints2, descriptors2);

	// matching descriptors
	BFMatcher matcher(NORM_L2);
	vector<DMatch> matches;
	matcher.match(descriptors1, descriptors2, matches);
	clock_t end_time = clock();
	printf("Execute time = %f sec\n", ComputeTime(start_time, end_time));
	// drawing the results
	namedWindow("matches", 1);
	Mat img_matches;
	drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);
	imshow("matches", img_matches);
	waitKey(0);
	return 0;
}