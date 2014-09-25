////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// MaskBrush.h
//
// The header file for Filter Brush. 
//

#ifndef MASKBRUSH_H
#define MASKBRUSH_H

#include "../ImpBrush.h"

class MaskBrush : public ImpBrush
{
public:
	MaskBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const ImpPoint source, const ImpPoint target);
	void BrushMove(const ImpPoint source, const ImpPoint target);
	void BrushEnd(const ImpPoint source, const ImpPoint target);
	char* BrushName(void);
	int extra(void);
	bool init(void);
	double atPosition(int x, int y);
private:
	char fileName[256];
	unsigned char* data;
	int	width, height;
};

#endif