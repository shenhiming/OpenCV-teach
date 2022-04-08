#pragma once
#include "CVImageTools.h"

float sgn(float x);
//--------------------------------
// Soft shrinkage
//--------------------------------
float soft_shrink(float d,float T);
//--------------------------------
// Hard shrinkage
//--------------------------------
float hard_shrink(float d,float T);
//--------------------------------
// Garrot shrinkage
//--------------------------------
float Garrot_shrink(float d,float T);
//--------------------------------
// Wavelet transform
//--------------------------------
static void CVHaarWavelet(Mat &src,Mat &dst,int NIter);
//--------------------------------
//Inverse wavelet transform
//--------------------------------
static void CVInvHaarWavelet(Mat &src,Mat &dst,int NIter, int SHRINKAGE_TYPE=0, float SHRINKAGE_T=50);

int process(VideoCapture& capture);

int Main_HarrWavelet();


