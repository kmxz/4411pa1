//
// FilterBrush.h
//
// The header file for Poly Star Brush. 
//

#ifndef FILTERBRUSH_H
#define FILTERBRUSH_H

#include "../ImpBrush.h"

class FilterBrush : public ImpBrush
{
public:
	FilterBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
	int extra(void);
};

#endif