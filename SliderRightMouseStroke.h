////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

#ifndef SLIDERRIGHTMOUSESTROKE_H
#define SLIDERRIGHTMOUSESTROKE_H

#include "StrokeDirection.h"

class SliderRightMouseStroke :
	public StrokeDirection
{
public:
	SliderRightMouseStroke(ImpressionistDoc* pDoc, int type);
	void StrokeDirectionBegin(const ImpPoint source, const ImpPoint target);
	void StrokeDirectionMove (const ImpPoint source, const ImpPoint target);
	void StrokeDirectionEnd  (const ImpPoint source, const ImpPoint target);

	int getAngle(void);
};

#endif