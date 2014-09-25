////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// StarBrush.h
//
// The header file for Star Brush. 
//

#ifndef STARBRUSH_H
#define STARBRUSH_H

#include "../ImpBrush.h"

class StarBrush : public ImpBrush
{
public:
	StarBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const ImpPoint source, const ImpPoint target);
	void BrushMove(const ImpPoint source, const ImpPoint target);
	void BrushEnd(const ImpPoint source, const ImpPoint target);
	char* BrushName(void);
	int extra(void);
private:
	int size;
	int angle;
	static double coords[10][2];
};

#endif