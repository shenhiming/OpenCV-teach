#include "StdAfx.h"
#include "HistogramEqualize.h"

/********************************************/
/*  HISTOGRAM EQUALIZATION of A GRAY IMAGE  */
/********************************************/
int Hist_Eq(BYTE *img_data, int width, int height)
{

	double s_hist_eq[256]={0.0}, sum_of_hist[256]={0.0};
	long i, j, k, n, state_hst[256]={0};

	n = width * height;
	memset(s_hist_eq, 0, sizeof(double) * 256);

	//²Î­phistogram
	for(i=0;i<width;i++)
	{
		for(j=0;j<height;j++)
		{
			s_hist_eq[img_data[i + j * width]] += 1 / (double)n;
		}
	}


	sum_of_hist[0] = s_hist_eq[0];
	for (i=1;i<256;i++)        // cdf of image
	{
		sum_of_hist[i] = sum_of_hist[i-1] + s_hist_eq[i];
	}

	for(i=0;i<width;i++)
	{
		for(j=0;j<height;j++)
		{
			k = img_data[i + j * width];
			img_data[i + j * width] = (BYTE) floor( sum_of_hist[k] * 255.0 );
		}
	}

	return 0;
}