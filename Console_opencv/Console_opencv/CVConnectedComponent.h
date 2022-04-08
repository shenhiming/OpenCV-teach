#pragma once
#include "CVImageTools.h"


enum CONNECTED_COMP_TYPE{CCT_INTERAL_LABELING = 1, CCT_INTERNAL_LIST, CCT_EXTERNAL_LABELING, CCT_INTERNAL_LIST_ROTATERECT};

void Main_ConnectedComponent(int nSubItem);

void Main_RotateRect(IplImage &iplMat, vector<vector<Point>> &contourVec);