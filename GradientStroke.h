////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#ifndef GRADIENTSTROKE_H
#define GRADIENTSTROKE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "StrokeDirection.h"

using namespace cv;

class GradientStroke :
	public StrokeDirection
{
public:
	GradientStroke(ImpressionistDoc* pDoc, int type);
	void StrokeDirectionBegin(const ImpPoint source, const ImpPoint target);
	void StrokeDirectionMove(const ImpPoint source, const ImpPoint target);
	void StrokeDirectionEnd(const ImpPoint source, const ImpPoint target);
	int getAngle(void);

private:
	int	c_pAngle=0;
	Mat* src;
	Mat Dx;
	Mat Dy;
};

#endif