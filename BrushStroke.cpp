////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#include "BrushStroke.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "math.h"

BrushStroke::BrushStroke(ImpressionistDoc* pDoc, int type) :
StrokeDirection(pDoc, type)
{
}

void BrushStroke::StrokeDirectionBegin(const ImpPoint source, const ImpPoint target)
{
	strokes.push(source);
	//StrokeDirectionMove(source, target);
}

void BrushStroke::StrokeDirectionMove(const ImpPoint source, const ImpPoint target)
{
	ImpPoint p2;
	while (strokes.size() > 1) {
		p2 = strokes.front();
		if (abs(p2.y - source.y) + abs(p2.x - source.x) < 8) { // 8 is 2^3, so should be lucky
			break;
		}
		strokes.pop();
	}
	p2 = strokes.front();
	int theta = ((int)(atan2((double)(p2.y - source.y), p2.x - source.x) / PI * 180 + 360) % 360);
	c_pAngle = theta;
	strokes.push(source);
	if (strokes.size() > 5) {
		strokes.pop();
	}
}

void BrushStroke::StrokeDirectionEnd(const ImpPoint source, const ImpPoint target){}

int BrushStroke::getAngle(void) {
	return c_pAngle;
}