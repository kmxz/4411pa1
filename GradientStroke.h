////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#ifndef GRADIENTSTROKE_H
#define GRADIENTSTROKE_H

#include "StrokeDirection.h"

class GradientStroke :
	public StrokeDirection
{
public:
	GradientStroke(ImpressionistDoc* pDoc, int type);
	void StrokeDirectionBegin(const Point source, const Point target);
	void StrokeDirectionMove(const Point source, const Point target);
	void StrokeDirectionEnd(const Point source, const Point target);
	int getAngle(void);
};

#endif