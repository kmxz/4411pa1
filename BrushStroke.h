////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#ifndef BRUSHSTROKE_H
#define BRUSHSTROKE_H

#include "StrokeDirection.h"
#include "ImpBrush.h"
#include <queue>

class BrushStroke :
	public StrokeDirection
{
public:
	BrushStroke(ImpressionistDoc* pDoc, int type);
	void StrokeDirectionBegin(const ImpPoint source, const ImpPoint target);
	void StrokeDirectionMove(const ImpPoint source, const ImpPoint target);
	void StrokeDirectionEnd(const ImpPoint source, const ImpPoint target);
	int getAngle(void);
private:
	int	c_pAngle;
	std::queue<ImpPoint> strokes;
};

#endif