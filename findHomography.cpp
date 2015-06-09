
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"

using namespace std;
using namespace cv;

static void psMatMulF(float *src1, float *src2, float *dst, int rows, int mid, int cols)
{
	int i, j, k;

	for (j = 0; j < rows; j++)
	{
		for (i = 0; i < cols; i++)
		{
			dst[j * cols + i] = 0;
			for (k = 0; k < mid; k++)
			{
				dst[j * cols + i] += src1[j * mid + k] * src2[i + k * cols];
			}
		}
	}
	return;
}



void main()
{
	vector<Point2f> gndPt;
	vector<Point2f> imagePt;
	int width = 800;
	int height = 480;
	int len;
	int fix = 1;
	
	// 第1对, 0.3m
	Point2f p1, p2, pi1, pi2;
	p1.x = -1;
	p1.y = 0.3;
	p2.x = 1;
	p2.y = 0.3;
	pi1.x = 108;
	pi1.y = 359;
	pi2.x = 683;
	pi2.y = 374;
	if (fix)
	{
	pi1.y = (pi1.y + pi2.y) / 2;
	pi2.y = pi1.y;
	len = (abs(pi1.x - pi2.x)) * 0.5f;
	pi1.x = (800 - 1) * 0.5f - len;
	pi2.x = (800 - 1) * 0.5f + len;
	}

	gndPt.push_back(p1);
	gndPt.push_back(p2);
	imagePt.push_back(pi1);
	imagePt.push_back(pi2);

	// 第2对,1m
	p1.x = -1;
	p1.y = 1;
	p2.x = 1;
	p2.y = 1;
	pi1.x = 220;
	pi1.y = 258;
	pi2.x = 577;
	pi2.y = 268;
	if (fix)
	{
	pi1.y = (pi1.y + pi2.y) / 2;
	pi2.y = pi1.y;
	len = (abs(pi1.x - pi2.x)) * 0.5f;
	pi1.x = (800 - 1) * 0.5f - len;
	pi2.x = (800 - 1) * 0.5f + len;
	}
	gndPt.push_back(p1);
	gndPt.push_back(p2);
	imagePt.push_back(pi1);
	imagePt.push_back(pi2);

	// 第3对, 2m
	p1.x = -1;
	p1.y = 2;
	p2.x = 1;
	p2.y = 2;
	pi1.x = 289;
	pi1.y = 200;
	pi2.x = 515;
	pi2.y = 207;
	if (fix)
	{
	pi1.y = (pi1.y + pi2.y) / 2;
	pi2.y = pi1.y;
	len = (abs(pi1.x - pi2.x)) * 0.5f;
	pi1.x = (800 - 1) * 0.5f - len;
	pi2.x = (800 - 1) * 0.5f + len;
	}
	gndPt.push_back(p1);
	gndPt.push_back(p2);
	imagePt.push_back(pi1);
	imagePt.push_back(pi2);

	// 第4对, 1m, 2m宽
	p1.x = -2;
	p1.y = 1;
	p2.x = 2;
	p2.y = 1;
	pi1.x = 64;
	pi1.y = 251;
	pi2.x = 735;
	pi2.y = 269;
	if (fix)
	{
	pi1.y = (pi1.y + pi2.y) / 2;
	pi2.y = pi1.y;
	len = (abs(pi1.x - pi2.x)) * 0.5f;
	pi1.x = (800 - 1) * 0.5f - len;
	pi2.x = (800 - 1) * 0.5f + len;
	}

	gndPt.push_back(p1);
	gndPt.push_back(p2);
	imagePt.push_back(pi1);
	imagePt.push_back(pi2);

	Mat H = findHomography(gndPt, imagePt);
	FILE *fp = fopen("mat.txt", "wt");
	int i;
	float hh[9], temp1[3], temp2[3];
	for (i = 0; i < 3; i++)
	{
		fprintf(fp, "%f, %f, %f,\n", H.at<double>(i, 0),
			H.at<double>(i, 1), H.at<double>(i, 2));
		hh[i * 3 + 0] = H.at<double>(i, 0);
		hh[i * 3 + 1] = H.at<double>(i, 1);
		hh[i * 3 + 2] = H.at<double>(i, 2);
	}
	fclose(fp);

	temp1[0] = gndPt[0].x;
	temp1[1] = gndPt[0].y;
	temp1[2] = 1;

	psMatMulF(hh, temp1, temp2, 3, 3, 1);
	temp2[0] = temp2[0] / temp2[2];
	temp2[1] = temp2[1] / temp2[2];
	return;

}