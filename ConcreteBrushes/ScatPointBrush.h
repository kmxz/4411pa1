////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// ScatPointBrush.h
//
// The header file for Scattered Point Brush. 
//

#ifndef SCATPOINTBRUSH_H
#define SCATPOINTBRUSH_H

#include "../ImpBrush.h"

class ScatPointBrush : public ImpBrush
{
public:
	ScatPointBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const ImpPoint source, const ImpPoint target);
	void BrushMove(const ImpPoint source, const ImpPoint target);
	void BrushEnd(const ImpPoint source, const ImpPoint target);
	char* BrushName(void);
};

#endif