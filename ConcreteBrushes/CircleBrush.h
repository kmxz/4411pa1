////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// CircleBrush.h
//
// The header file for Circle Brush. 
//

#ifndef CIRCLEBRUSH_H
#define CIRCLEBRUSH_H

#include "../ImpBrush.h"

class CircleBrush : public ImpBrush
{
public:
	CircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const ImpPoint source, const ImpPoint target);
	void BrushMove(const ImpPoint source, const ImpPoint target);
	void BrushEnd(const ImpPoint source, const ImpPoint target);
	char* BrushName(void);
protected:
	int size;
	int steps;
};

#endif