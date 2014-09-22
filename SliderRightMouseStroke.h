#ifndef SLIDERRIGHTMOUSESTROKE_H
#define SLIDERRIGHTMOUSESTROKE_H

#include "StrokeDirection.h"

class SliderRightMouseStroke :
	public StrokeDirection
{
public:
	SliderRightMouseStroke(ImpressionistDoc* pDoc, int type);
	void StrokeDirectionBegin(const Point source, const Point target);
	void StrokeDirectionMove (const Point source, const Point target);
	void StrokeDirectionEnd  (const Point source, const Point target);

	int getAngle(void);
};

#endif