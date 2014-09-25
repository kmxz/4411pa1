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

void GradientStroke::StrokeDirectionBegin(const ImpPoint source, const ImpPoint target){
	ImpressionistDoc* pDoc = GetDocument();
	//pDoc->m_ucBitmap
}
void GradientStroke::StrokeDirectionMove(const ImpPoint source, const ImpPoint target){}
void GradientStroke::StrokeDirectionEnd(const ImpPoint source, const ImpPoint target){}

int GradientStroke::getAngle(void) {
	// TODO
	return 0;
}