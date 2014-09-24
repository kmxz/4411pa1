////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#include "GradientStroke.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

GradientStroke::GradientStroke(ImpressionistDoc* pDoc, int type):
	StrokeDirection(pDoc, type)
{
}

void GradientStroke::StrokeDirectionBegin(const Point source, const Point target){}
void GradientStroke::StrokeDirectionMove(const Point source, const Point target){}
void GradientStroke::StrokeDirectionEnd(const Point source, const Point target){}

int GradientStroke::getAngle(void) {
	// TODO
	return 0;
}