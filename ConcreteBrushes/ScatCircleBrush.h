////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// ScatCircleBrush.h
//
// The header file for Scattered Circle Brush. 
//

#ifndef SCATCIRCLEBRUSH_H
#define SCATCIRCLEBRUSH_H

#include "CircleBrush.h"

class ScatCircleBrush : public CircleBrush
{
public:
	ScatCircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushMove(const ImpPoint source, const ImpPoint target);
	void BrushEnd(const ImpPoint source, const ImpPoint target);
	char* BrushName(void);
};

#endif