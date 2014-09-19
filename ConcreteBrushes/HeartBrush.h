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

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
	int extra(void);
private:
	int size;
	int angle;
	int steps;
};

#endif