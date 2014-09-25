////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// PolyStarBrush.h
//
// The header file for Poly Star Brush. 
//

#ifndef POLYSTARBRUSH_H
#define POLYSTARBRUSH_H

#include "../ImpBrush.h"

class PolyStarBrush : public ImpBrush
{
public:
	PolyStarBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const ImpPoint source, const ImpPoint target);
	void BrushMove(const ImpPoint source, const ImpPoint target);
	void BrushEnd(const ImpPoint source, const ImpPoint target);
	char* BrushName(void);
	int extra(void);
private:
	int size;
	int angle;
	int sides;
};

#endif