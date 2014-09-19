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

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
	int extra(void);
private:
	int size;
	int angle;
	int sides;
};

#endif