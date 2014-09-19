#ifndef GRADIENTSTROKE_H
#define GRADIENTSTROKE_H

#include "StrokeDirection.h"

class GradientStroke :
	public StrokeDirection
{
public:
	GradientStroke(ImpressionistDoc* pDoc, int type);
	void StrokeDirectionBegin(const Point source, const Point target);
	void StrokeDirectionMove(const Point source, const Point target);
	void StrokeDirectionEnd(const Point source, const Point target);
};

#endif