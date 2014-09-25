////**** **** **** **** **** **** **** **** **** **** **** ****////
////    COMP 4411 PA1 (Fall 2014) by {xkong, fxuaa}@ust.hk     ////
////                                                           ////
////                  Please read README.html                  ////
////**** **** **** **** **** **** **** **** **** **** **** ****////

//
// ScatCircleBrush.cpp
//
// The implementation of Scattered Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "../impressionistDoc.h"
#include "../impressionistUI.h"
#include "ScatCircleBrush.h"

extern float frand();

ScatCircleBrush::ScatCircleBrush(ImpressionistDoc* pDoc, char* name) :
CircleBrush(pDoc, name)
{
}

void ScatCircleBrush::BrushMove(const ImpPoint source, const ImpPoint target)
{
	int count = 2 + random() * 3; // randomly choose between 2, 3 or 4 lines
	for (int i = 0; i < count; i++) {
		int dx = (random() - 0.5) * size * 2;
		int dy = (random() - 0.5) * size * 2;
		CircleBrush::BrushMove(ImpPoint(source.x + dx, source.y + dy), ImpPoint(target.x + dx, target.y + dy));
	}
}

void ScatCircleBrush::BrushEnd(const ImpPoint source, const ImpPoint target)
{
	// do nothing so far
}

