#pragma once
#include "CVImageTools.h"
#include "HistogramEqualize.h"

void DrawHistogram(Mat &histImage, int histSize, int bin_w, int hist_h, CvHistogram *Histogram1);
void DoHistogram(Mat &mat, Mat &hist, Mat &histImage);
int Main_Histogram();
int Main_Histogram_Equalize();
int Main_CV_Histogram_Equalize();

