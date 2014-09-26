////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////
# pragma comment (lib, "opencv_core249.lib")
# pragma comment (lib, "opencv_highgui249.lib")
# pragma comment (lib, "opencv_imgproc249.lib")

#include "GradientStroke.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

using namespace std;
using namespace cv;

GradientStroke::GradientStroke(ImpressionistDoc* pDoc, int type):
	StrokeDirection(pDoc, type)
{
	src = NULL;
}

void GradientStroke::StrokeDirectionBegin(const ImpPoint source, const ImpPoint target){
	ImpressionistDoc* pDoc = GetDocument();
	
	if (src) {
		delete src;
	}

	src = new Mat(Size(pDoc->m_nWidth, pDoc->m_nHeight), CV_8UC3);

	
	//int baseIndex = 0;
	for (int i = 0; i < pDoc->m_nHeight; i++) {
		for (int j = 0; j < pDoc->m_nWidth; j++) {
			src->at<Vec3b>(i, j) = Vec3b(*(pDoc->GetOriginalPixel(j, pDoc->m_nHeight - i)),
				*(pDoc->GetOriginalPixel(j, pDoc->m_nHeight - i) + 1),
				*(pDoc->GetOriginalPixel(j, pDoc->m_nHeight - i) + 2));
			//baseIndex = baseIndex + 3;
		}
	}
	cvtColor(*src, *src, CV_RGB2GRAY);
	/// Load an image
	//src = imread(pDoc->getImageName(), CV_LOAD_IMAGE_GRAYSCALE);
	//printf("filename:%s\n", pDoc->getImageName());
	Sobel(*src, Dx, CV_64F, 1, 0, 3);
	//convertScaleAbs(Dx,Dx);
	Sobel(*src, Dy, CV_64F, 0, 1, 3);
	//convertScaleAbs(Dy, Dy);
	//printf("src:%dx%d\n", src->size().width, src->size().height);
	//printf("Dx:%dx%d\n", Dx.size().width, Dx.size().height);
	//printf("Dy:%dx%d\n", Dy.size().width, Dy.size().height);
	//imshow("Display window", *src);
	//imshow("x", *Dx);
	//imshow("y", *Dy);
	//StrokeDirectionBegin(source, target);
	//Mat grad;
	//addWeighted(Dx, 0.5, Dy, 0.5, 0, grad);
	//imshow("grad", grad);
}
void GradientStroke::StrokeDirectionMove(const ImpPoint source, const ImpPoint target)
{
	ImpressionistDoc* pDoc = GetDocument();
	Scalar x = Dx.at<double>(pDoc->m_nHeight - source.y - 1, source.x);
	Scalar y = Dy.at<double>(pDoc->m_nHeight - source.y - 1, source.x);
	//printf("Dx:%d\n", x.val);
	//printf("Dy:%d\n", y.val);
	//printf("x:%d y:%d\n", source.x, source.y);
	double directionRAD = atan2(x.val[0], y.val[0]);
	c_pAngle = ((int)(180.0 + directionRAD / M_PI * 180.0))% 360;
}
void GradientStroke::StrokeDirectionEnd(const ImpPoint source, const ImpPoint target){}

int GradientStroke::getAngle(void) {
	// TODO
	return c_pAngle;
}