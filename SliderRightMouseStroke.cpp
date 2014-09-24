////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#include "SliderRightMouseStroke.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"

SliderRightMouseStroke::SliderRightMouseStroke(ImpressionistDoc* pDoc , int type):
StrokeDirection(pDoc,type)
{
}

void SliderRightMouseStroke::StrokeDirectionBegin(const Point source, const Point target)
{
	StrokeDirectionMove(source, target);
}

void SliderRightMouseStroke::StrokeDirectionMove(const Point source, const Point target)
{

}
void SliderRightMouseStroke::StrokeDirectionEnd(const Point source, const Point target){}
int SliderRightMouseStroke::getAngle(void) {
	return GetDocument()->m_pUI->m_BrushLineAngleSlider->value();
}