//
// CircleBrush.h
//
// The header file for Circle Brush. 
//

#ifndef CIRCLEBRUSH_H
#define CIRCLEBRUSH_H

#ifndef PI
#define PI 3.14159265359
#endif

#include "../ImpBrush.h"

class CircleBrush : public ImpBrush
{
public:
	CircleBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
protected:
	int size;
	int steps;
};

#endif