#include "StdAfx.h"
#include "CVImageTools.h"

float ComputeTime(clock_t start_time, clock_t end_time)
{
	float total_time = (float)(end_time - start_time) / CLOCKS_PER_SEC;
	return total_time;
}

CCVImageTools::CCVImageTools(void)
{
}


CCVImageTools::~CCVImageTools(void)
{
}

//======================================================================================
//======================================================================================
// member function of CIplImageTool
//======================================================================================
//======================================================================================
BYTE *CIplImageTool::GetIplImagePixAddr(IplImage *pImg, int x, int y)
{
	int bitCount = pImg->depth * pImg->nChannels;
	if(x>=0 && x<pImg->width && y >=0 && y<pImg->height)
		return (BYTE*) &pImg->imageData[pImg->widthStep * y + x * bitCount / 8];
	else
		return NULL;
}



void CIplImageTool::BYTEStarToIplImage(byte *pImg, IplImage *pIplImg, int width,int height,int bitCount )
{
	if (!pImg )
	{
		return;
	}
	cvZero(pIplImg);
	int nChannel = bitCount / 8;
	long nByteWidth = width * nChannel;
	//確保imgWidth是4的倍數
	int offset = nByteWidth % 4;
	if(offset != 0) offset = 1;
	long lWidthByte = ((nByteWidth / 4) + offset) * 4;

	for(int j=0;j<height;j++)
	{
		for(int i=0;i<width;i++)
		{
			BYTE *pData = CIplImageTool::GetIplImagePixAddr(pIplImg, i, j);
			memcpy(pData, &pImg[(i + j * width) * nChannel], sizeof(BYTE) * nChannel);
		}
	}

	return;
}

void CIplImageTool::IplImageToBYTEStar(IplImage *IplImg, BYTE *dib)
{
	if (!IplImg)
	{
		return;
	}
	int nHeight = IplImg->height;
	int nWidth =IplImg->width;
	int bitCount = IplImg->depth;
	int nChanel = IplImg->nChannels;
	 
	
	BYTE *pData = NULL;
	if (IplImg->origin != 0)	//上下顛倒圖像
	{   //from left-down
		for (int j = 0; j < nHeight;j++)
		{
			for (int i = 0; i< nWidth;i++)
			{
				for (int k =0; k < nChanel;k++)
				{
					//*(pImg+i*nWidth+j*nChanel+k) = *(IplImg->imageData+(nHeight-i-1)*nWidth+j*nChanel+k);
					pData = GetIplImagePixAddr(IplImg, i, nHeight - j - 1) + k;
					dib[j*nWidth*nChanel+i*nChanel+k] = *pData;
				}
    
			}
		}
  
	}
	else	//上下不顛倒圖像
	{ //from left-up 
		for (int j = 0; j < nHeight;j++)
		{
			for (int i = 0; i < nWidth;i++)
			{
				for (int k =0; k < nChanel;k++)
				{
					//*(pImg+i*nWidth+j*nChanel+k) = *(IplImg->imageData+(nHeight-i-1)*nWidth+j*nChanel+k);
					pData = GetIplImagePixAddr(IplImg, i, j) + k;
					dib[j*nWidth*nChanel+i*nChanel+k] = *pData;
				}
    
			}
		}
	}
 
	//pImg = (byte *)IplImg->imageData;
	return;
}

void CIplImageTool::EdgeDetection(IplImage *pInImg, IplImage *pOutImg, vector<Point> *pEdgeVec)
{
	cvZero(pOutImg);
	int width = pInImg->width;
	int height = pInImg->height;
	for(int j=1;j<height - 1;j++)
	{
		for(int i=1;i<width - 1;i++)
		{
			BYTE cG = *GetIplImagePixAddr(pInImg, i, j); 
			BYTE upG = *GetIplImagePixAddr(pInImg, i, j - 1); 
			BYTE downG = *GetIplImagePixAddr(pInImg, i, j + 1); 
			BYTE leftG = *GetIplImagePixAddr(pInImg, i - 1, j); 
			BYTE rightG = *GetIplImagePixAddr(pInImg, i + 1, j);
			
			BYTE *pG = GetIplImagePixAddr(pOutImg, i, j); 
			if(cG == 255 && (cG != upG || cG != downG || cG != leftG || cG != rightG))
			{
				*pG = 255;
				if(pEdgeVec)
				{
					(*pEdgeVec).push_back(Point(i, j));
				}
			}
			else
			{	
				*pG = 0;
			}
		}
	}
}

bool CheckBoundary(int x, int w)
{
	return (x >= 0 && x < w);
}
Point2d RotatePoint(double xc, double yc, double x, double y, double angle)
{
	Point2d pt;
	angle = angle / 180 * M_PI;
	pt.x = (x - xc) * cos(angle) - (y - yc) * sin(angle) + xc;
	pt.y = (x - xc) * sin(angle) + (y - yc) * cos(angle) + yc;

	return pt;
}

Rect ComputeAfterRotateBoundary(Point2d pt1, Point2d pt2, Point2d pt3, Point2d pt4)
{
	Rect rect;
	double minX = min(min(pt1.x, pt2.x), min(pt3.x, pt4.x));
	double minY = min(min(pt1.y, pt2.y), min(pt3.y, pt4.y));
	double maxX = max(max(pt1.x, pt2.x), max(pt3.x, pt4.x));
	double maxY = max(max(pt1.y, pt2.y), max(pt3.y, pt4.y));
	rect.x = static_cast<int>(minX);
	rect.y = static_cast<int>(minY);
	rect.width = static_cast<int>(fabs(maxX - minX));
	rect.height = static_cast<int>(fabs(maxY - minY));
	return rect;
}

void GetExternalContourLabeling(IplImage *pIPL_DEPTH_8U1CImg, IplImage *pIPL_DEPTH_8U3CImg, vector<CRect> &contourRectArray, int areaTh, vector<vector<Point>> *pContourVec) 
{
	CvMemStorage * storage = cvCreateMemStorage(0); 
	CvSeq * contour = 0;


	cvFindContours( pIPL_DEPTH_8U1CImg, storage, &contour, sizeof(CvContour), 
		CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE , cvPoint(0,0));


	vector<Point> ptVec;

	int imgWidth = pIPL_DEPTH_8U1CImg->width;
	int imgHeight = pIPL_DEPTH_8U1CImg->height;
	CvRect roiRect;
	roiRect.width = imgWidth; 
	roiRect.height = imgHeight;
	int i=0; 
	for(;contour;contour = contour->h_next) 
	{ 
		CvRect aRect = cvBoundingRect(contour, 0 );

		bool bMatch = aRect.width * aRect.height > areaTh;
		if(bMatch)
		{ 
			ptVec.clear();
			CRect tmpRect(aRect.x, aRect.y, aRect.x + aRect.width, aRect.y + aRect.height);
			cvRectangle( pIPL_DEPTH_8U3CImg, cvPoint(tmpRect.left,tmpRect.top),cvPoint((tmpRect.right), 
				(tmpRect.bottom)),CV_RGB(255,0,0), 3 ); 

			contourRectArray.push_back(tmpRect);

			if(pContourVec)
			{
				int ptSz = contour->first->count;
				for(int i=0;i<ptSz;i++)
				{
					CvPoint * p = CV_GET_SEQ_ELEM(CvPoint,contour, i);

					ptVec.push_back(Point(p->x, p->y));
				}
				(*pContourVec).push_back(ptVec);
			}

		} 
	}
	ptVec.clear();
	cvReleaseMemStorage(&storage);
}
void GetInternalContourLabeling(IplImage *pIPL_DEPTH_8U1CImg, IplImage *pIPL_DEPTH_8U3CImg, vector<CRect> &contourRectArray, int areaTh) 
{
	CvMemStorage * storage = cvCreateMemStorage(0); 
	CvSeq * contour = 0;

	cvFindContours( pIPL_DEPTH_8U1CImg, storage, &contour, sizeof(CvContour), 
		CV_RETR_TREE, CV_CHAIN_APPROX_NONE , cvPoint(0,0));
	int i=0; 
	CvSeq *headContour = contour;

	int nContourLayerCount = 0;
	int currContourLayerCount = 0;
	GetContourLayerCount(contour, areaTh, currContourLayerCount, nContourLayerCount);
	RecursiveContour(contour, pIPL_DEPTH_8U1CImg, pIPL_DEPTH_8U3CImg, contourRectArray, areaTh,  currContourLayerCount, nContourLayerCount);
	cvReleaseMemStorage(&storage);
}
void GetContourLayerCount(CvSeq *contour, int areaTh, int &currContourLayerCount, int &nContourLayerCount)
{
	currContourLayerCount++;
	if(currContourLayerCount > nContourLayerCount)
	{
		nContourLayerCount = currContourLayerCount;
	}
	while(contour)
	{
		if(contour->v_next)
		{
			GetContourLayerCount(contour->v_next, areaTh, currContourLayerCount, nContourLayerCount);
		}
		contour = contour->h_next;
	}
	currContourLayerCount--;
}
int RecursiveContour(CvSeq *contour, IplImage *pIPL_DEPTH_8U1CImg, IplImage *pIPL_DEPTH_8U3CImg, vector<CRect> &contourRectArray, int areaTh, int &currContourLayerCount, int nContourLayerCount)
{
	int ret = 0;
	currContourLayerCount++;
	
	while(contour)
	{
		
		if(contour->v_next)
		{
			int retCode = RecursiveContour(contour->v_next, pIPL_DEPTH_8U1CImg, pIPL_DEPTH_8U3CImg, contourRectArray, areaTh, currContourLayerCount, nContourLayerCount);
			if(retCode == 1)
			{
				CvRect aRect = cvBoundingRect( contour, 0 ); 
				if((aRect.width*aRect.height)>areaTh)
				{
					CRect tmpRect(aRect.x, aRect.y, aRect.x + aRect.width, aRect.y + aRect.height);
					cvRectangle( pIPL_DEPTH_8U3CImg, cvPoint(tmpRect.left,tmpRect.top),cvPoint((tmpRect.right), 
						(tmpRect.bottom)),CV_RGB(255,0,0), 3 ); 

					contourRectArray.push_back(tmpRect);
				}
			}
		}
		else
		{
			CvRect aRect = cvBoundingRect( contour, 0 );
				CvPoint2D32f pt;
				float cx = 0;
				float cy = 0;
				int ptSz = contour->first->count;
				for(int i=0;i<ptSz;i++)
				{
					CvPoint * p = CV_GET_SEQ_ELEM(CvPoint,contour, i);
					cx += p->x / (float) ptSz;
					cy += p->y / (float) ptSz;
				}
				pt.x = cx;
				pt.y = cy;
				double isPtInContour = cvPointPolygonTest(contour, pt, false);
				if(isPtInContour > 0)
				{
					BYTE d = *CIplImageTool::GetIplImagePixAddr(pIPL_DEPTH_8U1CImg, static_cast<int>(cx), static_cast<int>(cy));
					if(d == 0)
					{
						if(currContourLayerCount == nContourLayerCount)
						{
							ret = 1;
							break;	
						}	// end of if((aRect.width*aRect.height)>areaTh)  
					}
				}

				if((aRect.width*aRect.height)>areaTh) 
				{
					CRect tmpRect(aRect.x, aRect.y, aRect.x + aRect.width, aRect.y + aRect.height);
					cvRectangle( pIPL_DEPTH_8U3CImg, cvPoint(tmpRect.left,tmpRect.top),cvPoint((tmpRect.right), 
							(tmpRect.bottom)),CV_RGB(255,0,0), 3 ); 

					contourRectArray.push_back(tmpRect);
					
				}	// end of if(currContourLayerCount == nContourLayerCount)
		}	// end of else of if(contour->v_next)
		contour = contour->h_next;
	}
	currContourLayerCount--;
	return ret;
	
}
void GetInternalContourList(IplImage *pIPL_DEPTH_8U1CImg, IplImage *pIPL_DEPTH_8U3CImg, vector<CRect> &contourRectArray, int areaTh, vector<vector<Point>> *pContourVec)
{
	CvMemStorage * storage = cvCreateMemStorage(0); 
    CvSeq * contour = 0;
	
    cvFindContours( pIPL_DEPTH_8U1CImg, storage, &contour, sizeof(CvContour), 
                    CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE , cvPoint(0,0));

	int imgWidth = pIPL_DEPTH_8U1CImg->width;
	int imgHeight = pIPL_DEPTH_8U1CImg->height;
	//CRect constMaskRect(imgWidth / 3, imgHeight / 3, imgWidth * 0.66, imgHeight * 0.66);
    int i=0; 
	vector<Point> ptVec;
    for(;contour;contour = contour->h_next) //for each contour
    { 
        CvRect aRect = cvBoundingRect( contour, 0 );
		
        if((aRect.width*aRect.height)>areaTh) //contour area > threshold
        { 
			ptVec.clear();
			CRect tmpRect(aRect.x, aRect.y, aRect.x + aRect.width, aRect.y + aRect.height);
			cvRectangle( pIPL_DEPTH_8U3CImg, cvPoint(tmpRect.left,tmpRect.top),cvPoint((tmpRect.right), 
					(tmpRect.bottom)),CV_RGB(255,0,0), 3 ); 
			contourRectArray.push_back(tmpRect);

			if(pContourVec)
			{
				int ptSz = contour->first->count;	//edge num
				for(int i=0;i<ptSz;i++)//for each edge
				{
					CvPoint * p = CV_GET_SEQ_ELEM(CvPoint,contour, i);

					ptVec.push_back(Point(p->x, p->y));// save edge
				}
			}
			(*pContourVec).push_back(ptVec);//save contour
        } 
    }
	
	ptVec.clear();
	cvReleaseMemStorage(&storage);
}