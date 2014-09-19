//
// ScatLineBrush.h
//
// The header file for Scattered Line Brush. 
//

#ifndef SCATLINEBRUSH_H
#define SCATLINEBRUSH_H

#include "LineBrush.h"

class ScatLineBrush : public LineBrush
{
public:
	ScatLineBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif