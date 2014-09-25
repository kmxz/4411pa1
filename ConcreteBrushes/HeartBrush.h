////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// HeartBrush.h
//
// The header file for Heart Brush. 
//

#ifndef HEARTBRUSH_H
#define HEARTBRUSH_H

#include "../ImpBrush.h"

class HeartBrush : public ImpBrush
{
public:
	HeartBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const ImpPoint source, const ImpPoint target);
	void BrushMove(const ImpPoint source, const ImpPoint target);
	void BrushEnd(const ImpPoint source, const ImpPoint target);
	char* BrushName(void);
	int extra(void);
private:
	int size;
	int angle;
	int steps;
};

#endif