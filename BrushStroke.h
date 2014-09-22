#ifndef BRUSHSTROKE_H
#define BRUSHSTROKE_H

#include "StrokeDirection.h"

class BrushStroke :
	public StrokeDirection
{
public:
	BrushStroke(ImpressionistDoc* pDoc, int type);
	void StrokeDirectionBegin(const Point source, const Point target);
	void StrokeDirectionMove(const Point source, const Point target);
	void StrokeDirectionEnd(const Point source, const Point target);
	int getAngle(void);
private:
	int	c_pAngle;
};

#endif