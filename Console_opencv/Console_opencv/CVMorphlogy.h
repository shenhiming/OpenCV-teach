#pragma once
#include "CVImageTools.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
int Main_Erosion();
int Main_Dilation();
int Main_Opening();
int Main_Closing();
void Erosion(Mat &img1);
void Dilation(Mat &img1);