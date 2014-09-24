////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#include "BrushStroke.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "math.h"

Point lastPoint;
long num = 0;

BrushStroke::BrushStroke(ImpressionistDoc* pDoc, int type) :
StrokeDirection(pDoc, type)
{
}

void BrushStroke::StrokeDirectionBegin(const Point source, const Point target)
{
	lastPoint = source;
	//StrokeDirectionMove(source, target);
}
void BrushStroke::StrokeDirectionMove(const Point source, const Point target)
{
	Point p1 = lastPoint;
	Point p2 = source;
	int theta = c_pAngle;


	if ((p2.x - p1.x != 0) && (abs(p2.y-p1.y)+abs(p2.x-p1.x))>5)
		theta = ((int)(atan((p2.y - p1.y + 0.0) / (p2.x - p1.x)) / PI * 180 + 360) % 360);

	//pDoc->m_pUI->m_BrushLineAngleSlider->value(theta);
	c_pAngle = theta;
	if (num++ % 10 == 0){
		lastPoint = source;
		printf("%d %d %d %d %d\n", p1.x, p1.y, p2.x, p2.y,theta);
	}
	num %= 1000000;
}
void BrushStroke::StrokeDirectionEnd(const Point source, const Point target){}
int BrushStroke::getAngle(void) {
	return c_pAngle;
}